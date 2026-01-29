/*
 * deadhen.c
 *
 * Used in npc/hen.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include "defs.h"

void
zap_hen()
{
    tell_room(ENV(TO), "The hen corpse dissolves and you can see a tiny hen " +
              "spirit rising to the sky.\n");
    remove_object();
}

void
create_object()
{
    set_short("dead hen");
    set_name("hen");
    set_adj("dead");
    set_long("It's passed on. This hen is no more. It has ceased to be. " +
             "It's expired and gone to meet its maker. It's a stiff. " +
             "Bereft of life, it rests in peace. " +
             "Its metabolic processes are now history. It's off the twig. " +
             "It's kicked the bucket, it's shuffled off its mortal coil, " +
             "run down the curtain and joined the bleedin' choir invisible. " +
             "This is an ex-hen.\n");

    set_alarm(300.0, 0.0, zap_hen);
}

int
eat(string str)
{
    NF("Eat what?");
    if (!str || str != "hen")
	return 0;

    write("You don't want to eat the hen raw. Maybe you should fry it?\n");
    return 1;
}

int
fry(string str)
{
    object torch, room;

    NF("Fry what?\n");
    if (!str || str != "hen")
	return 0;

    room = ENV(TO);
    while (!room->query_prop(ROOM_I_IS)) room = ENV(room);

    torch = present("torch", TP);
    if ((!torch || !torch->query_prop(OBJ_I_HAS_FIRE)) &&
	!room->query_prop(OBJ_I_HAS_FIRE))
    {
	write("You don't find anywhere to fry the hen.\n");
	return 1;
    }
    
    write("You fry the hen. It looks tasty.\n");
    say(QCTNAME(TP) + " fries a hen.\n");

    seteuid(getuid());
    torch = clone_object(ROKEDIR + "obj/friedhen");
    torch->move(ENV(TO));
    set_alarm(1.0, 0.0, remove_object);
    return 1;
}

void
init()
{
    ::init();
    add_action(eat, "eat");
    add_action(fry, "fry");
}

