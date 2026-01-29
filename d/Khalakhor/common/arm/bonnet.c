/* A common bonnet, for the lassies of the villages
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
    set_adj(({"cloth",col}));
    set_short(col+" bonnet");
    set_long("It is a plain "+col+" bonnet, a headress of a lady with a "+
             "narrow brim and long straps which tie neatly beneath the "+
             "chin.\n");
}
 
void create_armour() {
    set_name("bonnet");
    set_color("white");
    set_ac(2);
    set_at(A_HEAD);
}
