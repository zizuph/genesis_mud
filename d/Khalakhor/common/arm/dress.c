/* A common dress, for the lassies of the villages
**   Coder         Date                Action
** -------------- -------- ----------------------------------------------
** Zima           3/15/98  Created
**/
inherit "/std/armour";
#include <formulas.h>
#include <stdproperties.h>
 
void set_color(string col) {
    string *adjs=query_adj(1);
    if (pointerp(adjs)) remove_adj(adjs);
    set_adj(({"long","wool",col}));
    set_short("long "+col+" dress");
    set_long("It is a long "+col+ " dress made of wool, the common dress "+
             "of the lassies of Khalakhor.\n");
}
 
void create_armour() {
    set_name("dress");
    set_color("brown");
    set_ac(3);
    set_at(TS_ROBE);
}
