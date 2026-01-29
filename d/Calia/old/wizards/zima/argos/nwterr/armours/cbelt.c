/*  A common belt
**
**   Coder         Date                Action
** -------------- -------- ----------------------------------------------
** Zima           10/15/96 Created
**/
inherit "/std/armour";
#include <formulas.h>
#include <stdproperties.h>
 
void create_armour() {
    set_name("belt");
    set_adj(({"brown","leather"}));
    set_short("brown leather belt");
    set_long( "It is a common brown leather belt, with a bright bronze "+
              "buckle.\n");
    set_ac(5);
}
