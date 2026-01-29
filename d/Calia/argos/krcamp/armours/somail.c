/* Chainmail of a Kretan Soldier
**
** HISTORY
** Date       Coder     Action
** ---------- --------- -----------------------------------
** 1/25/96    Zima      Created
*/
inherit "/std/armour";
#include <formulas.h>
#include <stdproperties.h>
 
void create_armour() {
    set_name("chainmail");
    add_name("mail");
    set_adj(({"charred","orichalcum","kretan"}));
    set_short("charred orichalcum chainmail");
    set_long("It is suit of orichalcum chainmail which armours the torso "+
             "of its wearer. It has been charred black with a decorative "+
             "breastplate bearing a seven-headed hydra.\n");
    set_ac(25);
    set_at(A_TORSO);
    set_am(({-2,3,-1}));
}
