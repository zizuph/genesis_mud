/* Sword of a Kretan Deuterian Commander
**
** HISTORY
** Date      Action
** --------- -----------------------------------
** 1/30/96    Created
*/
inherit "std/weapon";
#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
 
void create_weapon() {
    set_name("longsword");
    set_adj(({"orichalcum","kretan","silver-hilted"}));
    set_short("silver-hilted orichalcum longsword");
    set_long("It is a longsword made of orichalcum which has been charred "+
             "black. The hilt is made of silver and engraved with a seven-"+
             "headed hydra in a circular inset.\n");
    set_hit(26); set_pen(14);
    set_hands(W_NONE);
    set_wt(W_SWORD);
    set_dt(W_IMPALE | W_SLASH);
}
