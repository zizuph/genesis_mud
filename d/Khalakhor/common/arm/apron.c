/* A common apron, for the lassies of the villages
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
    set_adj(({"cloth","plaid",col}));
    set_short(col+" checked apron");
    set_long("It is a plain white apron, plaid with "+col+" lines and "+
             "checks.\n");
}
 
void create_armour() {
    set_name("apron");
    set_color("red");
    set_ac(2);
    set_at(A_WAIST);
}
