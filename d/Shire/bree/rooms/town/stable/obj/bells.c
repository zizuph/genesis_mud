/*
 *  /d/Shire/bree/rooms/town/stable/bells.c
 *
 *  The ankle bells for Bree Stable horses
 *
 *  Palmer December, 2002
 */

inherit "/std/object";

#include <stdproperties.h>

#include "../bree_stables.h"

void
create_object()
{
    ::create_object();

    set_name(({"horse bells", "horsebells", "bells"}));
    set_pname("bells");
    set_adj("shiny");
    set_short("horse bells");
    set_long("Sturdy bells attached to thick a thick leather " +
             "strap made to put the jingle in your steed's jangle. " +
             "You can fasten the bells on the steed or unfasten them.\n");
}
