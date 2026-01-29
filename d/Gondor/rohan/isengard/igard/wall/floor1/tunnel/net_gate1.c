/*
 *  WALL_TUNNEL_ONE + "net_gate1.c"
 *
 *  Tunnel on first floor of Isengard ring wall.
 *
 *  Last modified by Alto, 29 September 2001
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "../../../igard_defs.h"

inherit IGARD_LIB + "igard_funcs.c";
inherit IGARD_LIB + "igate_funcs.c";

public void        create_gondor();
public int         permit_exit();

object             actor;

string
long_desc()
{
    return "You are standing in a broad tunnel within the great "
    + "ring wall of Isengard. The tunnel is extremely wide and could "
    + "accomodate an army in which twenty soldiers marched abreast. "
    + "Firelight flickers off the stone walls and floor from massive "
    + "iron lanterns set into small alcoves along the way. Two mighty "
    + "doors of iron stand to the southwest, set beneath a great stone "
    + "arch, while the tunnel itself leads away to the northeast. Two "
    + "small doorways open to the northwest and southeast.\n";
}


public void
create_gondor()
{
    set_short("Behind the mighty southeastern gate");
    set_long(&long_desc());

    wall_add_items();
    igate_add_items();

    add_item(({"inscription", "weathered inscription"}), &exa_inscription());
    add_cmd_item(({"inscription", "weathered inscription"}), "read",
        &exa_inscription());

    add_item(({"room", "area", "surroundings", "place", "tunnel"}), long_desc);

    add_exit(WALL_TUNNEL_ONE + "net5.c",         "northeast");
    add_exit(WALL_FLOOR_ONE +  "net_guardrm1",   "northwest");
    add_exit(WALL_FLOOR_ONE +  "net_guardrm2",   "southeast");

    add_prop(ROOM_I_INSIDE, 1);

    reset_room();
}


int
permit_exit()
{
    actor = TP;

    write("You push on the massive iron doors with both hands and they "
        + "swing easily upon their hinges. You quickly slip outside as the "
        + "doors close behind you.\n\n");
    tell_room(environment(actor), QCTNAME(actor) + " pushes on the massive "
        + "iron doors with both hands. The doors open effortlessly and "
        +  PRONOUN(actor) + " slips quickly outside.\n"
        + "The doors return to their original position.\n", 
        ({actor}));
    tell_room(IGARD_PLAIN + "northeast_gate", "The great iron doors open "
        + "for a moment and " + QTNAME(TP) + " slips quickly outside.\n"
        + "The doors return to their original position.\n");

    TP->move_living("M", IGARD_PLAIN + "northeast_gate", 1, 0);

    return 1;
}
