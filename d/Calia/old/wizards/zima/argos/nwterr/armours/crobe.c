/* A common robe
**   Coder         Date                Action
** -------------- -------- ----------------------------------------------
** Zima           10/15/96 Created
**/
inherit "/std/armour";
#include <formulas.h>
#include <stdproperties.h>
 
void create_armour() {
    set_name("robe");
    set_adj(({"brown","wool","simple"}));
    set_short("simple brown robe");
    set_long("It is a simple brown robe made of wool, common amongst "+
             "adventurers of many lands.\n");
 
    set_ac(5);
    set_at(TS_ROBE);
    set_am(({-1, 0, 1}));
    add_prop(OBJ_I_WEIGHT, 1300);
    add_prop(OBJ_I_VOLUME, 1000);
}
