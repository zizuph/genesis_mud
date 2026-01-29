/* Broadsword of a Kretan Stratarch
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
    set_name("broadsword");
    set_adj(({"tempered","orichalcum","kretan"}));
    set_short("tempered orichalcum broadsword");
    set_long("It is a large two-handed broadsword made of tempered "+
             "orichalcum. Its massive blade is etched with strange "+
             "lettering and its hilt is decorated with an inescutcheon "+
             "bearing a seven-headed hydra.\n");
 
    set_hit(32); set_pen(32);
    set_hands(W_BOTH);
    set_wt(W_SWORD);
    set_dt(W_BLUDGEON | W_SLASH);
}
