#include "collision.h"

bool collision::collide(vector< vector <int> > &theMap, int j, int k)
{
    if(((theMap[-j][-k] == 0) || (theMap[-j][-k] == 10) || (theMap[-j][-k] == 19) || (theMap[-j][-k] == 77) || (theMap[-j][-k] == 158) || (theMap[-j][-k] == 260) || (theMap[-j][-k] == 261) || (theMap[-j][-k] == 264) || (theMap[-j][-k] == 265) || (theMap[-j][-k] == 338) || ((theMap[-j][-k] >= 215) && (theMap[-j][-k] <= 219)) || ((theMap[-j][-k] >= 297) && (theMap[-j][-k] <= 303))))
          return true;
    else
          return false;
}
