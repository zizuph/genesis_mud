/* Surplice - short tunic-like lace vestment, symbol of a Guilley Erin
**   Coder         Date                Action
** -------------- -------- ----------------------------------------------
** Zima           8/21/98  Created
**/
inherit "/std/armour";
#include <formulas.h>
#include <stdproperties.h>
 
void create_armour() {
    set_name("surplice");
    add_name("vestment");
    set_adj(({"white","transparent","lace","short"}));
    set_short("white surplice");
    set_long("It is a white suplice, an almost transparent garment made "+
             "of thin lacy material. It is a tunic which "+
             "falls to just above the knees, with half sleeves that "+
             "hang just under the elbows.\n");
    set_ac(5);
    set_at(TS_TORSO);
}
