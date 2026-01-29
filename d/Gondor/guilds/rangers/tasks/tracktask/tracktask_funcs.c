/*
 *  /d/Gondor/guilds/rangers/hq/tracktask_funcs.c
 *
 *  Various functions for tracking task rooms
 *
 *  Coded by Alto, 07 December 2002
 *
 *  Modification log:
 *      Added delay code for those wandering off the path.
 *      -- Gwyneth
 */
inherit "/d/Gondor/std/room.c";

#include <files.h>
#include <formulas.h>
#include <macros.h>
#include <options.h>
#include <std.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"
#include "../../rangers.h"

/* Prototypes */

public void         track_add_items();
public int          allowed();

void
track_add_items()
{
    add_item(({"path", "pathway", "forest path"}), "The path here looks "
        + "decidedly untravelled. Perhaps it is because there is little "
        + "of interest in this part of the forest. Perhaps it is because "
        + "something dangerous lurks here. Only one way to find out.\n");
    add_item(({"track", "animal track"}), "The path, in fact, appears to "
        + "be a path made by animals, probably deer as they move through "
        + "the forest.\n");
    add_item(({"ground", "floor"}), "It is littered with most of the things "
        + "you would expect to find on the floor of a forest. A blanket of "
        + "leaves covers the ground, filled with such things as acorns and "
        + "twigs. Here and there you spot evidence that animals have passed "
        + "this way.\n");
    add_item(({"leaf", "leaves"}), "The leaves on the trees are, of course, "
        + "rather green and vary in size and shape depending upon the "
        + "species. Those on the forest floor look rather similar, excepting "
        + "that they are for the most part brown.\n");
    add_item(({"tree", "trees"}), "There are many species of tree growing "
        + "in the Druedain, and all of them seem tall and close. It is plain "
        + "that no axe has cut this wood for many an Age.\n");
    add_item(({"forest", "druedain", "druedain forest"}), "The forest grows "
        + "dense and dark around you. It is filled with many species of "
        + "tree, all of which seem displeased to have an interloper such as "
        + "yourself disturbing their slumber.\n");
    add_item(({"trunk", "trunks", "tree trunk", "tree trunks"}), "The trunks "
        + "of the trees are very tall and exceedingly wide. They support the "
        + "massive boughs with great strength. The bark on most of the "
        + "trees is ancient and moss-covered.\n");
    add_item(({"bark", "tree bark", "bark on the trees"}), "The bark on the "
        + "trees looks old and is covered with a soft growth of moss.\n");
    add_item(({"moss"}), "The moss grows in soft carpets on the tree "
        + "trunks.\n");
    add_item(({"root", "roots"}), "The roots of the great trees in the "
        + "Druedain are knotted and tangled across the path. They look quite "
        + "capable of tripping up even the most experienced in wood lore.\n");
}

public int
allowed()
{
    object delay, who = this_player();

    // Wizards, rabbits and those with rabbits pass.
    if (who->query_wiz_level() || who->query_prop(RANGER_I_RABBIT))
        return 0;

    // Those who are delayed do not pass.
    delay = present("_ranger_track_task_delay", who);
    if (objectp(delay))
    {
        set_alarm(1.0, 0.0, &who->catch_tell(delay->query_no_move() + "\n"));
        return 1;
    }

    // All others pass.
    return 0;
}

public void
enter_inv(object ob, object from)
{
    object delay;
    string name;

    ::enter_inv(ob, from);

    if (!living(ob))
        return;

    name = ob->query_real_name();
    if (ob->query_wiz_level() &&
      SECURITY->query_wiz_dom(name) != "Gondor" &&
      SECURITY->query_wiz_rank(name) <= WIZ_ARCH)
    {
        name = ob->query_real_name();
        clone_object(RANGERS_OBJ + "tracker")->move(ob, 1);
        return;
    }

    if (ob->query_prop(RANGER_I_RABBIT))
        return;

    if (present("rabbit", this_object()))
        return;

    /* The rabbit hasn't been here, or they're backtracking. */
    /* Let's delay them a little bit. */
    if(!sizeof(query_prop(ROOM_S_DIR)) ||
      query_prop(ROOM_S_DIR)[1] != "rabbit")
    { 
        if (!present(RANGER_I_RABBIT, ob) &&
          !present("_ranger_track_task_delay", ob))
        {
            delay = clone_object(RANGERS_OBJ + "delay");
            delay->move(ob, 1);
        }
    }
}

void
leave_inv(object ob, object to)
{
    string name;
    object tracker;

    ::leave_inv(ob, to);

    if (!living(ob) || !ob->query_wiz_level())
        return;

    name = ob->query_real_name();
    if (SECURITY->query_wiz_dom(name) == "Gondor" ||
      SECURITY->query_wiz_rank(name) >= WIZ_ARCH)
        return;

    tracker = present("_ranger_tracker", ob);
    if (objectp(tracker))
        tracker->remove_object();
}

int
query_ranger_room()
{
    return 1;
}
