#include "gen_func.h"

namespace onyx2d
{

    bool FileExist(std::string path)
    {
        FILE *file;
		file = fopen(path.c_str(), "rb");
		if (!file)
		{

			SAFE_RELEASE(file);
			return false;
		}else{
			return true;
		}
    }


    std::string FileExtension(std::string path)
    {
        return StringToUpper(StringSplit(StringSplit(path, "\/").back(),".").back());
    }

    std::string StringToUpper(std::string myString)
    {
      const int length = myString.length();
      for(int i=0; i!=length; ++i)
      {
        myString[i] = toupper(myString[i]);
      }
      return myString;
    }

    std::string StringToLower(std::string myString)
    {
      const int length = myString.length();
      for(int i=0; i!=length; ++i)
      {
        myString[i] = tolower(myString[i]);
      }
      return myString;
    }

    vector<std::string> StringSplit(std::string str, std::string delim)
    {
        vector<string> results;
        int cutAt;
        while( (cutAt = str.find_first_of(delim)) != str.npos )
        {
            if(cutAt > 0)
            {
                results.push_back(str.substr(0,cutAt));
            }
            str = str.substr(cutAt+1);
        }
        if(str.length() > 0)
        {
            results.push_back(str);
        }
        return results;
    }

    int32 Random(int32 low, int32 high)
    {

        int temp;

        /* swap low & high around if the user makes no sense */
        if (low > high)
        {
        temp = low;
        low = high;
        high = temp;
        }

        /* calculate the random number & return it */
        if (low != high)
            temp = rand() % (high - low) + low;
        else
            temp = low;

        return temp;
    }

    double Randomd(double low, double high)
    {

        double temp;

        /* swap low & high around if the user makes no sense */
        if (low > high)
        {
        temp = low;
        low = high;
        high = temp;
        }

        /* calculate the random number & return it */
        if (low != high)
            temp = (rand() / (static_cast<double>(RAND_MAX) + 1.0)) * (high - low) + low;
        else
            temp = low;

        return temp;
    }

    double ToRads(int16 grads)
    {
        return ((grads*PI)/180);
    }

    int16 ToGrads(double rads)
    {
        return ((rads*180)/PI);
    }


}


