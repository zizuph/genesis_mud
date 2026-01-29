/* Dalmatic - short tunic-like vestment, symbol of a diaghin
**   Coder         Date                Action
** -------------- -------- ----------------------------------------------
** Zima           8/21/98  Created
**/
inherit "/std/armour";
#include <formulas.h>
#include <stdproperties.h>
 
void create_armour() {
    set_name("dalmatic");
    add_name("vestment");
    set_adj(({"purple","short"}));
    set_short("purple dalmatic");
    set_long("It is a purple dalmatic, a religious vestment worn by "+
             "one who holds the office of diaghin. It is a tunic which "+
             "falls to just above the knees, with half sleeves that "+
             "hang just under the elbows. Its sides are open beneath "+
             "the arms, with a square cut across the bottom in the front "+
             "and back. Both the front and back pieces are adorned with "+
             "thick strips of gold embroidery, two vertically from the "+
             "shoulders and one horizontally across the chest in an 'H' "+
             "pattern.\n");
    set_ac(5);
    set_at(TS_TORSO);
}
