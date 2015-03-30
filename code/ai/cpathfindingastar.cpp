/*

    cPathfindingAStar -Class that contain A* path finder algortithm

    Copyright (C) 2010-2011 Josue Candela Perdomo (josuecp.com)

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

**/

#include "cpathfindingastar.h"

namespace onyx2d
{


cPathfindingAStar::cPathfindingAStar()
{
    cPathfindingAStar(0,0);
}

cPathfindingAStar::cPathfindingAStar(int16 map_size_x, int16 map_size_y )
{

    m_vMapSize.Set(0,0);
    SetMapSize(Vector2<int16>(map_size_x, map_size_y));

    StartPosition.Set(0,0);
    TargetPosition.Set(0,0);

    PathCorners = false;

}

cPathfindingAStar::cPathfindingAStar(Vector2<int16> map_size)
{
    cPathfindingAStar(map_size.x, map_size.y);
}


cPathfindingAStar::~cPathfindingAStar()
{
    ClearMapValues();

}

void cPathfindingAStar::SetMapSize(Vector2<int16> map_size)
{
    ClearMapValues();

    m_vMapSize = map_size;

    m_aMap = new Node**[m_vMapSize.x];
    for (int i=0; i<m_vMapSize.x ; i++)
    {
        m_aMap[i] = new Node*[m_vMapSize.y];
        for (int m=0; m<m_vMapSize.y ; m++)
        {
            m_aMap[i][m] = new Node;
            m_aMap[i][m]->Pos.x = i;
            m_aMap[i][m]->Pos.y = m;
        }
    }


}

void cPathfindingAStar::ClearMapValues()
{

    for(int x=0; x<m_vMapSize.x; x++)
    {
        for(int y=0; y<m_vMapSize.y; y++)
            SAFE_RELEASE(m_aMap[x][y]);
        SAFE_RELEASE(m_aMap[x]);
    }

    SAFE_RELEASE(m_aMap);

    ClearListValues();

}

void cPathfindingAStar::ClearListValues()
{

    for(int x=0; x<m_vOpened.size(); x++)
        SAFE_RELEASE(m_vOpened[x]);

    m_vOpened.clear();

    for(int x=0; x<m_vClosed.size(); x++)
        SAFE_RELEASE(m_vClosed[x]);

    m_vClosed.clear();

}

void cPathfindingAStar::SetValue(int16 x, int16 y, float value)
{
    m_aMap[x][y]->Value = value;
}

vector< Vector2<int16> > cPathfindingAStar::GetPath()
{

    bool resolved = AStarAlgorithm();

    vector< Vector2<int16> > path;

    if (resolved)
    {
        Node *node = m_aMap[TargetPosition.x][TargetPosition.y];
        path.push_back(Vector2<int16>(node->Pos.x, node->Pos.y));
        while (node != m_aMap[StartPosition.x][StartPosition.y])
        {
            node = node->Parent;
            path.push_back(Vector2<int16>(node->Pos.x, node->Pos.y));
            //cout << "("<< node->Pos.x << ","<< node->Pos.y << ") - ";
        }
    }


    //cout << endl;
    return path;
}

void cPathfindingAStar::ClearNodeValues()
{

    for(int x=0; x<m_vMapSize.x; x++)
        for(int y=0; y<m_vMapSize.y; y++)
                m_aMap[x][y]->Restore();


}

bool cPathfindingAStar::AStarAlgorithm()
{
    bool ret = false;

    m_vOpened.clear();
    m_vClosed.clear();

    ClearNodeValues();

    /*--- A* Algorithm ---*/
    //Add the start position node
    m_vOpened.push_back(m_aMap[StartPosition.x][StartPosition.y]);

    while(!m_vOpened.empty())
    {

        Node *node = GetMinFNode();

        //cout << "Obtenemos: (" << node->Pos.x << "," << node->Pos.y << ")"<< endl;

        m_vOpened.erase(find(m_vOpened.begin(), m_vOpened.end(), node));
        m_vClosed.push_back(node);


        //Para cada uno de los vecinos
        vector<Node*> adj_nodes = GetAdjacentsNodes(node->Pos.x, node->Pos.y);
        for (int i=0; i<adj_nodes.size(); i++)
            if (find(m_vClosed.begin(), m_vClosed.end(), adj_nodes[i]) == m_vClosed.end())//Si no existe en la lista cerrada
                if (find(m_vOpened.begin(), m_vOpened.end(), adj_nodes[i]) == m_vOpened.end())//Si no existe en la lista abierta
                {
                    adj_nodes[i]->Parent = node;
                    CalculeNode(adj_nodes[i]);
                    m_vOpened.push_back(adj_nodes[i]);
                }else{
/*
                    if ((CalculeG(node,adj_nodes[i])+adj_nodes[i]->H)>(adj_nodes[i]->G+adj_nodes[i]->H))
                    {
                        adj_nodes[i]->Parent = node;
                        cout << "Cambiamos: (" << adj_nodes[i]->Pos.x << "," << adj_nodes[i]->Pos.y << ")"<< " al padre ";
                        cout << " (" << node->Pos.x << "," << node->Pos.y << ") "<<(CalculeG(node,adj_nodes[i])+adj_nodes[i]->H) << "<" << (adj_nodes[i]->G+adj_nodes[i]->H) << endl;
                    }
*/
                }


        /* If we have the target position in the open list finish the loop*/
        if (find(m_vOpened.begin(), m_vOpened.end(), m_aMap[TargetPosition.x][TargetPosition.y])!=m_vOpened.end())
        {
            m_aMap[TargetPosition.x][TargetPosition.y]->Parent = node;
            ret = true;
            break;
        }

    }

    return ret;
}

cPathfindingAStar::Node*  cPathfindingAStar::GetMinFNode()
{
    if (m_vOpened.size() != 0)
    {

        int min = 0;

        for (int i=1;i<m_vOpened.size(); i++)
            if (m_vOpened[i]->G+m_vOpened[i]->H <m_vOpened[0]->G+m_vOpened[0]->H)
                min = i;

        return m_vOpened[min];

    }else{
        return NULL;
    }
}

vector<cPathfindingAStar::Node*> cPathfindingAStar::GetAdjacentsNodes(int16 x, int16 y)
{
    vector<Node*> nodes;
    if (x>0)
    {
        if (m_aMap[x-1][y]->Value < 1.0f)
            nodes.push_back(m_aMap[x-1][y]);

        /* Left Corners */
        if (PathCorners)
        {

        if (y>0)
            if (m_aMap[x-1][y-1]->Value < 1.0f)
                nodes.push_back(m_aMap[x-1][y-1]);

        if (y<m_vMapSize.y-1)
            if (m_aMap[x-1][y+1]->Value < 1.0f)
                nodes.push_back(m_aMap[x-1][y+1]);

        }
    }

    if (x<m_vMapSize.x-1)
    {
        if (m_aMap[x+1][y]->Value < 1.0f)
            nodes.push_back(m_aMap[x+1][y]);

        /* Right Corners */
        if (PathCorners)
        {

        if (y>0)
            if (m_aMap[x+1][y-1]->Value < 1.0f)
                nodes.push_back(m_aMap[x+1][y-1]);

        if (y<m_vMapSize.y-1)
            if (m_aMap[x+1][y+1]->Value < 1.0f)
                nodes.push_back(m_aMap[x+1][y+1]);

        }
    }

    if (y>0)
        if (m_aMap[x][y-1]->Value < 1.0f)
            nodes.push_back( m_aMap[x][y-1]);

    if (y<m_vMapSize.y-1)
        if (m_aMap[x][y+1]->Value < 1.0f)
            nodes.push_back(m_aMap[x][y+1]);


    return nodes;
}

void cPathfindingAStar::CalculeNode(cPathfindingAStar::Node* node)
{

    node->G = CalculeG(node, node->Parent);
    node->H = CalculeH(node->Pos.x,node->Pos.y);
}

int16 cPathfindingAStar::CalculeG(cPathfindingAStar::Node* node, cPathfindingAStar::Node* node2)
{
    int G;
    if (node->Pos.x != node2->Pos.x && node->Pos.y != node2->Pos.y)
        G = node->Parent->G + 14;
    else
        G = node->Parent->G + 10;

    G = (int)(G + G*node->Value);
   // cout << "x" << node->Pos.x << "y" << node->Pos.y<<":"<< G << endl;
    return G;
}

int16 cPathfindingAStar::CalculeH(int16 x, int16 y)
{
    int16 ret = 0;

    /* Manhattan method */
    while(x!=TargetPosition.x || y!=TargetPosition.y)
    {
        if (TargetPosition.x != x)
        {
            if (TargetPosition.x < x)
                x--;
            else
                x++;
            ret++;
        }

        if (TargetPosition.y != y)
        {
            if (TargetPosition.y < y)
                y--;
            else
                y++;
            ret++;
        }
    }

    return ret*10;
}


Vector2<int16> cPathfindingAStar::GetNextPos()
{
    bool resolved = AStarAlgorithm();

    if (resolved)
    {
        vector< Vector2<int16> > path;
        Node *node = m_aMap[TargetPosition.x][TargetPosition.y];
        path.push_back(Vector2<int16>(node->Pos.x, node->Pos.y));
        while (node != m_aMap[StartPosition.x][StartPosition.y])
        {
            node = node->Parent;
            path.push_back(Vector2<int16>(node->Pos.x, node->Pos.y));
        }

        return path[path.size()-2];
    }else{
        return NULL;
    }

}

cPathfindingAStar::Node::Node()
{
    Pos.Set(0,0);
    Value = 0.0f;
    Restore();
}

cPathfindingAStar::Node::~Node()
{
    SAFE_RELEASE(Parent);
}

void cPathfindingAStar::Node::Restore()
{
    Parent = NULL;
    G = 0;
    H = 0;
}

}
