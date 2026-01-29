/* Cope (ecclesial cape)
**   Coder         Date                Action
** -------------- -------- ----------------------------------------------
** Zima           8/15/97  Created
**/
inherit "/std/armour";
#include <formulas.h>
#include <stdproperties.h>
 
void set_color(string col) {
    set_adj(({"long",col}));
    set_short("long "+col+" cope");
    set_long("It is a long "+col+ " cope, a type of cape worn by elder "+
             "manachs, edged with a gold border. It fastens around the "+
             "neck and hangs over the shoulders and back.\n");
}
 
void create_armour() {
    set_name("cope");
    set_color("purple");
    set_ac(5);
    set_at(TS_TORSO);
}
