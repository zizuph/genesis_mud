/* Ashlar, 3 Aug 97 */

inherit  "/std/torch";
#include <macros.h>
#include <stdproperties.h>
#include "../local.h"
#include "/d/Ansalon/common/defs.h"

create_torch()
{
    set_name("torch");
    set_pname("torches");
    set_adj("large");
    set_long("A large torch, probably able to illuminate all but the " +
    "darkest of surroundings.\n");
    set_strength(3);
    set_short("large torch");
    set_pshort("large torches");
}

void
drop_me()
{
    object ob = E(TO);

    if (ob && ob->query_prop(LIVE_I_IS) && ob->query_npc())
    {
        tell_room(E(ob), QCTNAME(ob) + " discards the " + short() + ".\n",
            ({ ob }));
    }
    remove_object();
}

void
burned_out()
{    
    ::burned_out();
    set_alarm(2.0, 0.0, drop_me);    
}
