/*
 * fish.c
 *
 * Used in obj/fishing_rod.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

/* a nice fish to sacrify to statues */

#pragma save_binary
#pragma strict_types

inherit "/std/food";

#include <stdproperties.h>

void killit(object h);
void die();

void
create_food()
{
    set_name("fish");
    set_adj("raw");
    set_short("raw fish");
    set_long("The fish has three eyes. You feel that there is a special " +
             "reason for this fish to have three eyes.\n");

    add_prop(OBJ_I_WEIGHT, 180);

    add_prop(OBJ_I_VOLUME, 184);
   
    set_amount(65);
    set_alarm(120.0, 0.0, die);

    add_prop(OBJ_I_VALUE, 5);
}

void
die()
{
    object h;
    if (living(h = environment()))
        h->catch_msg("The fish dies. You realize that it has been in the " +
                     "air too long time.\n");
    killit(h);
}

void
killit(object h)
{
    object e = environment();
    while (e && !e->query_prop(ROOM_I_IS)) e = environment(e);

    if (e) 
        tell_room(e, 
            "Your sensitive mind detects that a fish just died here.\n" +
            "You feel very sad.\n", ({h}));
    set_adj("dead");
    set_short("dead fish");
}
