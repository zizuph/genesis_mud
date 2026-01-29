/*
 * /d/Gondor/morgul/cellar/tuvale2.c
 * A home for the Tuvale
 *
 * Varian, May 2016
 */


inherit "/d/Gondor/morgul/cellar/cellar.c";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/morgul/cellar/cellar_defs.h"
#include "/d/Gondor/guilds/morgulmage/morgulmage.h"

object shadow;

void give(object ob);
int give_id;

void
create_morgul_cellar_room()
{
    set_level(1);

    set_room_type("dark cell");

    set_extra_long("You are huddled in the cramped northeastern corner " +
        "of a dark cell. The rest of the room is separated by a fetid " +
        "river of brown sludge which cuts in front of you, flowing in " +
        "from a hole in the northern wall and exiting through a similar " +
        "opening in the eastern wall. Scattered bundles of dirty rags are " +
        "draped across the black granite floor, a rudimentary bed for the " +
        "vermin who make their home here. There is also a large " +
        "wooden barrel resting here, slightly battered and filled " +
        "with what appears to be garbage.");

    add_item(({"dirt","dust"}),
        "A thick grimy layer of dirt and dust covers the black granite " +
        "walls and floors of the cell.\n");
    add_item(({"debris","garbage","remains","pile","piles"}),
        "Huddling along the walls of the cell are several small piles " +
        "of garbage. The debris is obviously the leftover remains of " +
        "something better left unexplored.\n");
    add_item(({"floor","down"}),
        "Massive square blocks of black granite have been cut and fit " +
        "to form a relatively smooth and flat floor underneath all of " +
        "the dirt that currently covers it.\n");
    add_item(({"stone","granite","black granite","black stone"}),
        "The walls, floor and even the ceiling have been constructed from " +
        "dozens of large square blocks of black granite.\n");
    add_item(({"block","blocks","square block","square blocks"}),
        "These blocks have been masterfully cut and set. This superior " +
        "construction appears to be characteristic of the cellars down " +
        "here.\n");
    add_item(({"manacles","chains","irons","chain"}),
        "Several sets of iron manacles, old and rusted, hang menacingly " +
        "along the southern wall.\n");
    add_item(({"sludge","sewage"}),
        "This sludge is a yellowish brown colour, and the rotting smell " +
        "is truly offensive.\n");
    add_item(({"river","drain"}),
        "A wide river of sludge creeps out from the northern wall before " +
        "draining out through a hole in the east wall.\n");
    add_item(({"hole","holes","northern hole","eastern hole","opening"}),
        "These low holes break through the northern and eastern walls, " +
        "allowing a disgusting river of sludge to crawl across the cell.\n");
    add_item(({"shadow","shadows"}),
        "Several dark shadows linger in every corner, somehow eminating " +
        "an aura of silent menace.\n");
    add_item(({"island","corner","northeast corner"}),
        "Cut off from the rest of the room by the river, the northeast " +
        "corner of this cell stands in silent shadows. It appears that " +
        "the only way to get there would be to wade through this " +
        "disgusting sludge.\n");
    add_item(({"corridor","hall","hallway"}),
        "You would have to get to the western part of the cell to examine " +
        "the corridor. You are too far away from it here.\n");
    add_item(({"north wall","northern wall"}),
        "The northern wall of this cell is rather bare, aside from the " +
        "low hole which belches out this river of sludge.\n");
    add_item(({"south wall","southern wall"}),
        "The southern wall of this cell has several sets of rusty iron " +
        "manacles hanging down. They are clearly old and no longer in " +
        "working condition, but they still have a menacing aura that " +
        "is somewhat intimidating.\n");
    add_item(({"east wall","eastern wall"}),
        "The eastern wall of this cell is rather dirty, especially around " +
        "the low hole which acts as a drain for this river of sludge. " +
        "Every now and then, larger chunks of garbage get clogged near " +
        "the drain until the river bursts through the hole in a rather " +
        "messy and disgusting splash.\n");
    add_item(({"west wall","western wall"}),
        "You can see an arch opening up in the western wall, but from " +
        "this distance, you cannot examine it any closer.\n");
    add_item(({"wall","walls"}),
        "These stone walls are covered in a grimy layer of dirt, adding " +
        "to an already unpleasant atmosphere here.\n");
    add_item(({"ceiling","up"}),
        "Obscured in the lingering shadows, the ceiling of this cell is " +
        "rather unremarkable, having been made from the same large blocks " +
        "of granite as the walls and floor.\n");
    add_item(({"bundles","bundle","rag","rags","bed"}),
        "Several bundles of rags have been scattered on the ground here, " +
        "apparently providing a rudimentary bed for some unfortunate scum " +
        "to sleep in. You could probably huddle under the rags as well if " +
        "you wanted to do the same thing.\n");
    add_item(({"cell","here"}),
        "You are huddled in the cramped northeastern corner " +
        "of a dark cell. The rest of the room is separated by a fetid " +
        "river of brown sludge which cuts in front of you, flowing in " +
        "from a hole in the northern wall and exiting through a similar " +
        "opening in the eastern wall. Scattered bundles of dirty rags are " +
        "draped across the black granite floor, a rudimentary bed for the " +
        "vermin who make their home here. There is also a large " +
        "wooden barrel resting here, slightly battered and filled " +
        "with what appears to be garbage.\n");

    add_exit(CELLAR_DIR + "tuvale", "southwest", "@@river@@");

    set_no_exit_msg(({"northeast","north","southeast","northwest","east"}),
        "Summoning your strength, you run straight into the solid granite " +
        "wall of the cell.\n\nThat was not productive.\n\n" +
        "You are huddled in the cramped northeastern corner " +
        "of a dark cell. The rest of the room is separated by a fetid " +
        "river of brown sludge which cuts in front of you, flowing in " +
        "from a hole in the northern wall and exiting through a similar " +
        "opening in the eastern wall. Scattered bundles of dirty rags are " +
        "draped across the black granite floor, a rudimentary bed for the " +
        "vermin who make their home here. There is also a large " +
        "wooden barrel resting here, slightly battered and filled " +
        "with what appears to be garbage.\n");
    set_no_exit_msg(({"south","west"}),
        "The wide river of sludge seems to be a little too deep here, " +
        "you would be better off trying to wade through it to the " +
        "southwest.\n");

    clone_object("/d/Gondor/guilds/morgulmage/obj/tbarrel")->move(TO);

    reset_room();
}

init()
{
    ::init();
    add_action("do_clean","clean",0);
    add_action("do_clean","clear",0);
    add_action("huddle_rags","huddle");
    add_action("huddle_rags","sleep");
    add_action("huddle_rags","start");
}

public int
do_clean(string str)
{
    if(!strlen(str))
    {
        notify_fail("Clean what? Were you supposed to clean the sewage?\n");
        return 0;
    }

    if((str != "sludge") && 
        (str != "sewage") && (str != "river") &&
        (str != "river of sludge") && (str != "river of sewage"))
    {
        notify_fail("Clean what? Were you supposed to clean the sewage?\n");
        return 0;
    }

    write("Wading deep into the river of sludge, you reach in and " +
        "start to dig out larger pieces of garbage to help the " +
        "flow move along.\n\nThe river is still not clean enough yet. " +
        "You should try again after a few minutes.\n");
    SAYBB(" wades deep into the river of sludge and begins to dig " +
        "deep in a futile effort to clean it.");
    return 1;
}

int
river()
{
    if(!this_player()->query_messy_shadow()) {
    write("You wade through the disgusting mess of slime and sludge as " +
        "you cross the river towards the rest of the cell.\n");
    give_id = set_alarm(0.1, 0.0, &give(this_player()));
    return 0;
    }
}

give(object ob) 
{
    remove_alarm(give_id);
    shadow = clone_object("/d/Gondor/morgul/cellar/shadow/messy_shadow.c");
    shadow->shadow_me(ob);
    shadow->destruct_dirty_shadow();
}

int huddle_rags(string str)
{
    if ((str != "rags") && (str != "here") && ("under the rags"))
    {
        NF("Huddle under what?\n");
        return 0;
    }
    if (TP->query_wiz_level())
    {
        NF("You are a wizard, you do not need this!\n");
        return 0;
    }
    seteuid(getuid());
    if (TP->query_guild_name_occ() == GUILD_NAME)
    {
        TP->set_default_start_location(file_name(TO));
        write("You find a place to huddle beneath the rags, destined to " +
            "awake in this place from now on.\n");
        return 1;
    }
    else
    {
        NF("A large rat jumps out at you from beneath the rags and bites " +
            "you! You obviously cannot sleep here.\n");
        return 0;
    }
}