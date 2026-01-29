/*
 * /d/Gondor/morgul/cellar/tuvale.c
 * A home for the Tuvale
 *
 * Varian, May 2016
 */


inherit "/d/Gondor/morgul/cellar/cellar.c";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/morgul/cellar/cellar_defs.h"

void
create_morgul_cellar_room()
{
    set_level(1);

    set_room_type("dark cell");

    set_extra_long("This cell is rather bare, filled only by the dirt and " +
        "debris scattered across the floor. Several sets of rusty iron " +
        "manacles hang down menacingly along the southern wall. In the " +
        "middle of the cell, a fetid river of brown sludge cuts across the " +
        "black granite floor, leaving behind a shadowy island of stone in " +
        "the northeast corner of the room. A horrible odor rises up from " +
        "the sludge in waves, a relentless assault on the senses of any " +
        "living creature unfortunate enough to be trapped in this cell. " +
        "Providing some relief is the narrow archway which breaks through " +
        "the western wall, leading out towards the gloomy corridor beyond.");

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
        "Peeking through the arch in the western wall, you can see the " +
        "dark shadows falling down an empty corridor.\n");
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
        "There is a narrow archway in the western wall, leading back out " +
        "into a long empty corridor.\n");
    add_item(({"wall","walls"}),
        "These stone walls are covered in a grimy layer of dirt, adding " +
        "to an already unpleasant atmosphere here.\n");
    add_item(({"ceiling","up"}),
        "Obscured in the lingering shadows, the ceiling of this cell is " +
        "rather unremarkable, having been made from the same large blocks " +
        "of granite as the walls and floor.\n");
    add_item(({"cell","here"}),
        "This cell is rather bare, filled only by the dirt and " +
        "debris scattered across the floor. Several sets of rusty iron " +
        "manacles hang down menacingly along the southern wall. In the " +
        "middle of the cell, a fetid river of brown sludge cuts across the " +
        "black granite floor, leaving behind a shadowy island of stone in " +
        "the northeast corner of the room. A horrible odor rises up from " +
        "the sludge in waves, a relentless assault on the senses of any " +
        "living creature unfortunate enough to be trapped in this cell. " +
        "Providing some relief is the narrow archway which breaks through " +
        "the western wall, leading out towards the gloomy corridor beyond.\n");

    add_archway("west");

    set_no_exit_msg(({"north","east"}),
        "The wide river of sludge seems to be a little too deep here, " +
        "you would be better off trying to wade through it to the " +
        "northeast.\n");
    set_no_exit_msg(({"northwest","southwest","south","southeast"}),
        "You walk right up towards a rather solid granite wall, " +
        "quickly understanding that the only way out of this cell is " +
        "through the arch in the western wall.\n");

    add_exit(CELLAR_DIR + "dung_1e3", "west", "@@check_exit@@", 1);
    add_exit(CELLAR_DIR + "tuvale2", "northeast", "@@river@@");

    reset_room();
}

void

init()
{
    ::init();
    add_action("do_clean","clean",0);
    add_action("do_clean","clear",0);
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
    write("You wade through the disgusting mess of slime and sludge as " +
        "you cross the river towards the rest of the cell.\n");
    return 0;
}

