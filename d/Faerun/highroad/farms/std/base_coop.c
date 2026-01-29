/*
 * Chicken Coop for the Villages
 * Finwe, July 2006
 */
 
#include "/d/Faerun/defs.h"
#include "defs.h"
#include <stdproperties.h>
#include <terrain.h>

//inherit "/d/Faerun/highroad/base_villages.c";
inherit BASE_FARM;
inherit BASE_COMMON;
inherit FAERUN_OUTDOOR_BASE;

void create_coop() {}
 
public void
create_room()
{

    set_short("A clean chicken coop");
    set_long("Inside a chicken coop. It is clean even though chickens " +
        "live here. Straw is scattered across the floor. On a " +
        "shelf are several nests where some hens cluck quietly and sit " +
        "on some eggs.\n");

    add_item(({"nests", "chicken nests", "nest"}),
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
        "full of straw with some hens sitting on them. \n");
    add_item(({"shelf", "wooden shelf"}),
        "It is made of one long plank of wood. It is wide and runs " +
        "alongide the back wall. Nest boxes are set on it.\n");

    set_room_tell_time((ROOM_TELL_TIME + random(60)));
    add_room_tell("Baby chicks chirp from under a mother hen.");
    add_room_tell("A chicken runs out of the chicken coop.");
    add_room_tell("A chicken struts into the chicken coop.");
    add_room_tell("A hen jumps off a nest and walks out of the chicken coop.");
    add_room_tell("A hen struts into the chicken coop and flies up to a " +
        "nest and settles in.");
    set_add_chicken_noises();


    add_prop(OBJ_S_SEARCH_FUN, "do_search");
    set_wood_planks("They are rough from constant pecking of the chickens though.");
    

    reset_room();
    create_coop();
}


void reset_room()
{
    iEggFound = 0;
}

