/*

    cPathfindingAStar - Class that contain A* path finder algortithm
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

#ifndef CPATHFINDINGASTAR_H
#define CPATHFINDINGASTAR_H

#include <vector>
#include <queue>
#include <iostream>
#include <algorithm>

#include "../core/math/cvector2.h"
#include "../onyx2d_defs.h"

using namespace std;

namespace onyx2d
{

class cPathfindingAStar
{
    public:
        Vector2<int16> StartPosition;
        Vector2<int16> TargetPosition;
        bool PathCorners;

        /** Default constructor */
        cPathfindingAStar();

        /**
            Constructor that accepts the map size
            @param map_size_x Number of horizontal nodes of the map
            @param map_size_y Number of vertical nodes of the map
        */
        cPathfindingAStar(int16 map_size_x, int16 map_size_y );

        /**
            Constructor that accepts the map size
            @param map_size Vector of two integers with the horizontal and vertical number of nodes
        */
        cPathfindingAStar(Vector2<int16> map_size);

        /** Destructor */
        ~cPathfindingAStar();

        /**
            Function that changes the map size
            @param map_size Vector of two integers with the horizontal and vertical number of nodes
        */
        void SetMapSize(Vector2<int16> map_size);

        /**
            Function that clears the map values
        */
        void ClearMapValues();

        /**
            Function that returns the path until the target
            @return Vector with all the positions until the target
        */
        vector< Vector2<int16> > GetPath();

        /**
            Function that returns the next position for arrive to the target
            @return Vector of two integers that represent the next node in the map
        */
        Vector2<int16> GetNextPos();

        /**
            Function that set a node value
            @param x X position of the node in the map
            @param y Y position of the node in the map
            @param value Value of difficuty of crossing (1.0 is a blocked node)
        */
        void SetValue(int16 x, int16 y, float value);



    protected:
    private:
        class Node
        {

            public:
                Node* Parent;
                int G;
                int H;
                float Value;
                Vector2<int16> Pos;

                Node();

                ~Node();

                void Restore();


        };

        /**
            Function that calcule A* Algorithm
            @param <i>true</i> if solution was founded, <i>false</i> in other case
        */
        bool AStarAlgorithm();

        /**
            Function that clears the lists of opened and closed nodes
        */
        void ClearListValues();

        /**
            Function that clears the previous A* values of the node
        */
        void ClearNodeValues();

        /**
            Function that calcule node G and H
            @param node Node that going to be calculated
        */
        void CalculeNode(Node* node);

        /**
            Function that calcule G algorithm paramenter
            @param node Origin node for G calculation
            @param node2 Target node for G calculation
            @return Value of G
        */
        int16 CalculeG(cPathfindingAStar::Node* node, cPathfindingAStar::Node* node2);

        /**
            Function that calcule H algorithm paramenter (Heuristic)
            @param x X position of the node
            @param y Y position of the node
            @return Value of H
        */
        int16 CalculeH(int16 x, int16 y);

        /**
            Function that returns all the valid adjacents nodes
            @param x X position of the node
            @param y Y position of the node
            @return Vector with all adjacents nodes
        */
        vector<Node*> GetAdjacentsNodes(int16 x, int16 y);

        /**
            Function that returns the node with the minimun F value
            @return Node with the minimun F value
        */
        Node*  GetMinFNode();

        Node*** m_aMap;             //! Map of nodes
        Vector2<int16> m_vMapSize;  //! Map Size
        vector<Node*> m_vOpened;    //! List of opened nodes
        vector<Node*> m_vClosed;    //! List of closed nodes
};

}
#endif // CPATHFINDINGASTAR_H
