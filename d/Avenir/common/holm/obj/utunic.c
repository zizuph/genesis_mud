//-*-C++-*-
// undertunic   /d/Avenir/common/holm/obj/utunic.c
// creator(s):  Lilith, 06 April 1997
// revised:
// purpose:     Part of priests' outfit.
// note:         
// bug(s):
// to-do:
#pragma strict_types

inherit "/std/armour";

#include "../holm.h"
#include <wa_types.h>

void
create_armour()
{
    set_name("undertunic");
    add_name("tunic");
    set_adj(({"slubbed", "silk"}));
    set_short("slubbed silk undertunic");
    set_long("This is an undertunic of rich slubbed silk. "+
        "It is thick and heavy and quite luxurious.\n");
    set_ac(random(2) + 2);
    set_at(A_BODY);
    set_af(this_object());
}

mixed
wear(object ob)
{
    object tp = this_player();

    tp->catch_msg("The silk of the undertunic feels cool and "+
        "smooth as it rustles against your skin.\n");        
    return 0;
}


