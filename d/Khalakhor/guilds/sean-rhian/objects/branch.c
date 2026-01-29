// A configurable branch, broken from a tree; SR entrance quest object
//
// History:
// Date        Coder       Action
//----------   ----------- ----------------------------------
// 6/3/98      Zima        Created
//
inherit "/std/object";
#include <stdproperties.h>
#include "branch.h"
 
void set_branch(int bnum)
{
   string *branch=BRANCH;
   string l="It is a branch of ";
 
   if ((bnum<0)&&(bnum>=NUM_BRANCHES)) return;
 
   add_name(BR_ID_PREF+branch[bnum]);
   add_name(branch[bnum]);
   add_adj(branch[bnum]);
   set_short("branch of "+branch[bnum]);
 
   switch (bnum)
      {
      case 0: l+="an ivy vine, coiled like a serpent";              break;
      case 1: l+="an ash tree";                                     break;
      case 2: l+="a holly tree, with flesh spiny leaves and red berries";
              break;
      case 3: l+="a dogwood tree, with dark bark and pink four-petaled "+
                 "flowers";                                         break;
      case 4: l+="a hazelnut bush";                                 break;
      case 5: l+="a hawthorn bush with long sharp thorns";          break;
      case 6: l+="a willow tree, limp with long leaves";            break;
      case 7: l+="cedar, with rough bark and scales for leaves";    break;
      case 8: l+="wild plum, covered with thorns and small white "+
                 "flowers with a few unripened burgundy colored "+
                 "fruits"; break;
      }
   set_long(l+".\n");
}
 
void create_object()
{
    set_name("branch");
    set_long("It is a branch of a non-descript tree.\n");
 
    add_prop(OBJ_I_VOLUME,500);
    add_prop(OBJ_I_WEIGHT,250);
}
