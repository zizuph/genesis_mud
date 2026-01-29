/*
 * Chicken Coop for the Woodcutters in the Vales of Anduin
 * Finwe, November 2005
 */
 
#include "/d/Shire/sys/defs.h"
#include "local.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

inherit AREA_ROOM;
inherit "/d/Shire/std/room/room_tell";
inherit "/d/Shire/anduin/base_common";
inherit "/d/Shire/anduin/base_villages";
inherit "/lib/commands.c";

int iEggFound = 0, iMaxEggs = 6;

void create_coop() {}
 
public void
create_room()
{
    set_short("A clean chicken coop");
    set_long("Inside a chicken coop. It is clean even though chickens " +
        "live here. Straw is scattered across the floor. On a " +
        "shelf are several nests where some hens cluck quietly and sit " +
        "on some eggs.\n");

    add_item(({"nests", "chicken nests"}),
        "They are made of straw, large, and look well used by hens. The " +
        "nests sit in boxes that are set on a shelf along a wall. Some " +
        "of the nests appear unused and others have hens sitting on them.\n");
    add_item(({"straw"}),
        "The straw is golden colored and scattered around on the floor. " +
        "It's also stuffed into boxes on the shelves and used as material " +
        "for nests.\n");
    add_item(({"chicken coop", "coop", "henhouse", "hen house"}),
        "It's a large building used to house chickens. Along one wall is " +
        "a shelf with several nests. Some of the nests have hens sitting " +
        "on them and clucking quietly as they watch you. The floor is " +
        "covered with straw. Some chickens wander in and out of the " +
        "chicken coop, and wander around inside.\n");
    add_item(({"chickens", "chicken"}),
        "They are large, fat birds with bright feathers. Some are sitting " +
        "on nests, others are walking around or roosting in the chicken " +
        "coop, and others wander in and out of here.\n");
    add_item(({"hens", "hen"}),
        "They are large, drab colored birds. Some are sitting on nests, " +
        "clucking quietly. Some hens are walking around, roosting, or " +
        "wandering in and out of the chicken coop.\n");
    add_item(({"cocks", "cock", "roosters", "rooster"}),
        "They are a little larger than the hens. The roosters are brightly " +
        "colored with striking plumage. They strut around proudly and " +
        "crow periodically.\n");
    add_item(({"walls"}),
        "The walls are made of wood planks. They are weathered and rough " +
        "from the chickens pecking at them all the time.\n");
    add_item(({"ceiling"}),
        "The ceiling is made of wood planks. It is peaked to and protects " +
        "the chickens from the weather outside.\n");
    add_item(({"floor", "ground"}),
        "The floor is made of wood planks. It is rough from constant " +
        "pecking of the birds. Straw covers the floor.\n");
    add_item(({"nest boxes", "boxes", "nest box", "box"}),
        "They are square shaped and sit on a shelf. The boxes are evenly " +
        "spaced out so as not to crowd the hens using them. They are " +
        "full of straw and \n");
    add_item(({"shelf", "wooden shelf"}),
        "It is made of one long plank of wood. It is wide and runs " +
        "alongide the back wall. Nest boxes are set on it.\n");

    set_room_tell_time(random(ROOM_TELL_TIME));
    add_room_tell("A hen clucks quietly.");
    add_room_tell("Baby chicks chirp from under a mother hen.");
    add_room_tell("A hen suddenly squawks loudly.");
    add_room_tell("A chicken runs out of the chicken coop.");
    add_room_tell("A chicken pecks at something on the ground.");
    add_room_tell("A rooster struts around.");
    add_room_tell("A chicken flaps its wings suddenly.");
    add_room_tell("A chicken struts into the chicken coop.");
    add_room_tell("A hen jumps off a nest and walks out of the chicken coop.");
    add_room_tell("A hen struts into the chicken coop and flies up to a " +
        "nest and settles in.");

    add_prop(OBJ_S_SEARCH_FUN, "do_search");
    set_wood_planks("They are rough from constant pecking of the chickens though.");
    

    reset_shire_room();
    create_coop();
}


void reset_shire_room()
{
    iEggFound = 0;
}

mixed
do_search(object searcher, string str)
{
    int awareness;
    object egg;
 
    if (iEggFound >= iMaxEggs)
        return 0;

    if (!strlen(str))
        return 0; 

    if (!parse_command(str, ({}),
       "'nest' / 'nests' [for] [chicken] [egg]"))
        return 0;
 
    awareness = searcher->query_skill(SS_AWARENESS);
    if ((awareness + random(10)) > 15)
    {
        egg = clone_object(OBJ_DIR + "chicken_egg");
        iEggFound = iEggFound + 1;
        say(QCTNAME(searcher) + " finds an egg.\n", searcher);
        if (egg->move(searcher))
        {
            if (egg->move(TO))
                egg->move(TO, 1);
            return "You find an egg in one of the nests!\n";
        }

        return "You find an egg and quickly grab it from a nest!\n";
    }

    return 0;
}
