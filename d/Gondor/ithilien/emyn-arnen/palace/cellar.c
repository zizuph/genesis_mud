/*
 *	/d/Gondor/ithilien/emyn-arnen/palace/cellar.c
 *
 *	Copyright (c) 1994, 1997 by Christian Markus
 *
 *	Coded 1994 by Olorin
 */
#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/ithilien/emyn-arnen/arnen_defs.h"

#define OTHER_ROOM	(ITH_DIR + "emyn-arnen/palace/well_room")
#define TREASURY	(ITH_DIR + "emyn-arnen/palace/treasury")
#define PASSAGE_DESC	({ "door", "doorway", "passage" })
#define SCABBARD_MASTER	(ITH_DIR + "emyn-arnen/obj/scabbard_master")

void reset_room();

int     collapsed = 0;
object  gate;

void
create_gondor()
{
    set_short("a cellar under the House of the Stewards in Emyn Arnen");
    set_long("A cellar under the House of the Stewards in Emyn Arnen. "
      + "The only feature is a large steel gate in the south wall.\n");

    CELLAR_WALLS
    CELLAR_ROOF
    CELLAR_STONES
    CELLAR_FLOOR

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT,  0);

    add_exit(OTHER_ROOM, "east", 0, 1);

    reset_room();
}

void
remove_dead()
{
    int     i;
    object *o,
           *v;

    o = all_inventory(TO);
    v = filter(o, "filter_living", TO);
    o -= v;
    o -= ({ gate });

    for (i = 0; i < sizeof(o); i++)
        o[i]->remove_object();

    for(i = 0; i < sizeof(v); i++)
    {
        v[i]->catch_msg("You decide to leave this room of desolation.\n");
        v[i]->move_living("east", OTHER_ROOM);
    }
}

void
reset_room()
{
    if (!objectp(gate))
    {
        gate = clone_object(ITH_DIR + "emyn-arnen/obj/trout_door");
        gate->move(TO);
    }

    if (!collapsed)
         return;
 
    collapsed = 0;
    OTHER_ROOM->add_exit(MASTER, "west", 0, 1);
    OTHER_ROOM->remove_item("passage");
    OTHER_ROOM->add_item(({"door", "doorway", "passage"}), BSN(
        "A passage is leading west into another cellar even "
      + "darker than this one."));
}

int
filter_living(object x) { return living(x); }

void
destruct_room()
{
    int     i;
    object *v;

    collapsed = 1;
    OTHER_ROOM->remove_exit("west");
    OTHER_ROOM->remove_item("passage");
    OTHER_ROOM->add_item(({"door", "doorway", "passage"}), BSN(
        "The passage west is blocked by large boulders. It "
      + "looks like the whole cellar west of here has collapsed."));

    tell_room(TO, BSN("Everything happens so fast that you will "
      + "never know what hit you. All you see is that the roof "
      + "of the cellar seems to collapse."));

    v = filter(all_inventory(TO), "filter_living", TO);

    for (i = 0; i < sizeof(v); i++)
    {
        v[i]->heal_hp(-50000);
        if (v[i]->query_wiz_level())
        {
            v[i]->catch_msg("Your wizardhood protects you from death.\n"
              + "But even as a wizard, you have to leave this room now!\n");
            v[i]->move_living("east", OTHER_ROOM);
        }
        log_file("hurin_kills", v[i]->query_name()
          + " ("+v[i]->query_average_stat()
          + ") was killed by the Gates of Hurin, "+ctime(time())+".\n");
        v[i]->do_die(TO);
    }

    set_alarm(1.0, 0.0, remove_dead);
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (!objectp(ob) || !objectp(from) || !interactive(ob))
        return;

    ob->catch_msg(BSN("When you enter the cellar, you feel powerful magic "
      + "emanating from the gate in the wall to the south."));

    if (SCABBARD_MASTER->check_restore(ob))
	set_alarm(1.0, 0.0, &SCABBARD_MASTER->cellar_restore(ob));
}

