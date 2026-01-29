/* A sailor's eyepatch
**   Coder         Date                Action
** -------------- -------- ----------------------------------------------
** Zima           3/25/98  Created
**/
inherit "/std/armour";
#include <formulas.h>
#include <stdproperties.h>
 
void create_armour() {
    set_name("eyepatch");
    add_name("patch");
    add_adj("black");
    set_short("black eyepatch");
    set_long(
       "It is a large black eyepatch, sort of a cloth scarf wrapped around "+
       "he head with the patch hanging over the left eye.\n");
    set_ac(1);
    set_at(A_HEAD);
}
