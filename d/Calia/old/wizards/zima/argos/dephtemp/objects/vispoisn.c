/* this is a very weak poison object. The object is required in the player */
/* to do the vision quest in rooms/chapel. The player must be poisoned     */
/* with this object to receive a "vision" for the next step. The poison    */
/* is received by getting wine (objects/viswine) in rooms/winery, having   */
/* it blessed in rooms/talis, and drinking the wine.                       */
inherit "/std/poison_effect";
#include <poison_types.h>
#include "defs.h"
 
create_poison_effect()
{
    set_name(({"poison",VDQ_POISON}));
    set_interval(15);
    set_time(2000);
    set_damage(({POISON_HP,2}));
    set_strength(1);
    set_poison_type("standard");
}
