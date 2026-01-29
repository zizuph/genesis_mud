/* Sword of a Kretan warrior
**
** HISTORY
** Date      Action
** --------- -----------------------------------
** 1/25/96    Created
*/
inherit "std/weapon";
#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
 
void create_weapon() {
    set_name("longsword");
    set_adj(({"polished","orichalcum","kretan"}));
    set_short("polished orichalcum longsword");
    set_long("It is a longsword made of orichalcum, highly polished "+
             "with a circular inset on the hilt cast with a seven-headed "+
             "hydra.\n");
 
    set_hit(28); set_pen(15);
    set_hands(W_NONE);
    set_wt(W_SWORD);
    set_dt(W_IMPALE | W_SLASH);
}
