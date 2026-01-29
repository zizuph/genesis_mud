/*
 *  /d/Gondor/guilds/rangers/ithilien/tunnel/tunnel01.c
 *
 *  A secret tunnel in Ithilien hideout
 *
 *  Coded by Tigerlily, March 25, 2004
 *
 *
 */
inherit "/d/Gondor/std/room.c";


#include <stdproperties.h>
#include <macros.h>

#include "/d/Gondor/defs.h"

#include "../../rangers.h"
#include "../exit.c"
#define RANGER_WAS_STEALTHY "_ranger_was_stealthy"
#define RANGER_WAS_MASKED   "_ranger_was_masked"

int enter_tunnel(string str);
string see_door();
string east_wall();
public int start_stealth();

void
create_gondor()
{
    set_short("narrow tunnel");
    set_long("The rock walls enclose a tunnel that leads " +
        "down into darkness. It appears to be an ancient " +
        "escape route from the hideout, excavated deep into " +
        "the rock under Ithilien. The passage leads " +
        "down to the southwest\n");

    add_item(({"tunnel", "narrow tunnel", "passage"}), &long());
    add_item(({"walls"}), "The solid rock walls surround the tunnel " +
        "to the north and south. The east wall, however, " +
        "is made from unadorned blocks of stone.\n");
    add_item(({"wall", "east wall"}), &east_wall());
    add_item(({"rock", "stone", "blocks"}), "While the tunnel is " +
        "dug into the solid rock, delving deep under Ithilien, the " +
        "east wall of this room is constructed from rough blocks " +
        "of stone that blend in well with the natural cave. Only a " +
        "trained eye can see the faint outline of a door.\n");
    add_item(({"door", "outline of a door", "outline"}), &see_door() );

    add_exit(RANGERS_ITH_TUNNEL + "tunnel02", "southwest", &start_stealth());

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);
    add_prop(ROOM_M_NO_SCRY, 1);
}

string
see_door()
{
    if (!RANGERS_FULL_MEMBER(TP))
        return "You see no door here.\n";
//else
    return "Try pushing it and see where it leads.\n";
}

string
east_wall()
{
    string txt;

    if (!RANGERS_FULL_MEMBER(TP))
        txt = "\n";
    else 
        txt = " The trained eye can see " +
            "what appears to be the outline of a door.\n";
    return "Like much of the underground " +
        "hideout, the walls are made of stone. The east wall is made " +
        "from blocks of unadorned stone." + txt;

}

init()
{
    ::init();
    add_action(&enter_tunnel(), "push");
}

int
enter_tunnel(string str)
{
    object tp = this_player();

    if (!RANGERS_MEMBER(tp))
    {
        notify_fail("You push against the wall " +
            "and work up a sweat, but nothing " +
            "happens.\n");
        return 0;
    }
    if (str != "door" && str != "wall")
    {
        notify_fail("Push door?\n");
        return 0;
    }

    write("You push hard against the wall, and suddenly it " +
        "opens.\n");
    tell_room(environment(tp), QCTNAME(tp) + " pushes " +
        "against the wall and it suddenly swings open.\n", tp);
    tp->move_living("through the wall", 
        RANGERS_ITH_DIR + "passage1", 1, 0);

    if (tp->query_prop("_rangers_mask_closed"))
    {
        tp->add_prop(RANGER_WAS_MASKED, 1);
        tp->command("$unpin cloak");
        tp->command("$unmask me");
    }

    if (tp->query_autosneak())
    {
        tp->set_autosneak(0);
        write("You stop being stealthy as you enter the halls "
            + "of Henneth Annun.\n");
        tp->add_prop(RANGER_WAS_STEALTHY, 1);
    }

    return 1;
}

public int
start_stealth()
{

    int result = 0;
    object tp = this_player();
    object mcloak = present("_mottled_cloak_", tp);


    if (!tp->query_prop("_rangers_incognito") &&
        objectp((present("cloak", tp))->query_worn()))
        tp->command("$hood myself");
    if (objectp(mcloak) && objectp(mcloak->query_worn()) 
       && tp->query_prop(RANGER_WAS_MASKED))
    {
        tp->remove_prop(RANGER_WAS_MASKED);
        tp->command("$mask myself");
        tp->command("$pin cloak");
    }
    if (tp->query_prop(RANGER_WAS_STEALTHY))
    {
        tp->remove_prop(RANGER_WAS_STEALTHY);

        if (tp->query_autosneak() || sizeof(TP->query_team()))
            return result;

        tp->set_autosneak(1);
        write("You prepare to move stealthily again as you were "
            + "when you entered Henneth Annun.\n");
    }


    return 0;
    //if people find there way here, allow them to leave
}
