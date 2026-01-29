/* Doubled Chainmail of a Kretan Soldier
**
** HISTORY
** Date       Coder     Action
** ---------- --------- -----------------------------------
** 1/30/96    Zima      Created
*/
inherit "/std/armour";
#include <formulas.h>
#include <stdproperties.h>
 
void create_armour() {
    set_name("mail");
    add_name("doublemail");
    set_adj(({"polished","double","doubled","orichalcum","kretan"}));
    set_short("polished orichalcum doublemail");
    set_long("It is polished suit of doubled chainmail made of "+
             "orichalcum which armours the torso of its wearer. A circular "+
             "breast plate in the center bears the emblem of a seven-headed "+
             "hydra.\n");
    set_ac(29);
    set_at(A_TORSO);
    set_am(({-1,1,0}));
}
