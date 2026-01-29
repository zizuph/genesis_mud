/* Sword of a Kretan soldier
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
    add_name("sword");
    set_adj(({"charred","orichalcum","kretan"}));
    set_short("charred orichalcum longsword");
    set_long("It is a longsword made of orichalcum, charred black and "+
             "embellished with a seven-headed Hydra on the hilt.\n");
 
    set_hit(25); set_pen(13);
    set_hands(W_NONE);
    set_wt(W_SWORD);
    set_dt(W_IMPALE | W_SLASH);
}
