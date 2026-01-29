/* Leather armour of a Kretan sentry
**
** HISTORY
** Date       Coder     Action
** ---------- --------- -----------------------------------
** 1/25/96    Zima      Created
** 8/22/21    Greneth   Changed AC to 35
*/
inherit "/std/armour";
#include <formulas.h>
#include <stdproperties.h>
 
void create_armour() {
    set_name("mail");
    set_adj(({"black","studded","kretan"}));
    set_short("black studded mail");
    set_long("It is a black studded mail made of leather and orichalcum. "+
             "A thin breastplate bearing a seven-headed hydra decorates "+
             "the breast.\n");
    set_ac(35);
    set_at(A_TORSO);
    set_am(({0,1,-1}));
}
