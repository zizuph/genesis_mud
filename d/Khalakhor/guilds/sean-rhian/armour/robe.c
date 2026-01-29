/* Robe
**   Coder         Date                Action
** -------------- -------- ----------------------------------------------
** Zima           8/15/97  Created
**/
inherit "/std/armour";
#include <formulas.h>
#include <stdproperties.h>
 
void set_color(string col) {
    set_adj(({"cowled",col}));
    set_short("cowled "+col+" robe");
    set_long("It is a long "+col+ " robe with a cowl on the back. Three "+
             "interlocked circles are sewn on the front.\n");
}
 
void create_armour() {
    set_name("robe");
    set_color("white");
    set_ac(5);
    set_at(TS_ROBE);
}
