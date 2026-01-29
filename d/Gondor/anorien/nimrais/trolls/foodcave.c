/*
 * /d/Gondor/anorien/nimrais/trolls/foodcave.c
 *
 * Coder: Unknown
 *
 * Modification log:
 * Gwyneth, 10/02/02: Updated and cleaned up. Changed inheritance.
 */
inherit "/d/Gondor/std/room";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
 
int gEggFound = 0;
 
public void
create_gondor()
{
    set_short("the food-storage cave of the hill-troll lair");
    set_long("This is a dark, dry cave in the hill-troll lair. " +
        "The cave is not very large, and it is probably used only for " +
        "storage of food. There are some stone shelves full of food " +
        "here. Two tunnels are leading out of the cave, east and west.\n");
    add_item(({ "shelves", "food", "shelf" }), "The shelves are full of " +
        "all kinds of food. Most of them are more or less spoilt.\n");
    add_item( ({ "ground", "floor", "water", "stream", }),
        "The floor is littered with stones and small rocks. A thin " +
        "stream of water is trickling into the cave east of here.\n");

    add_prop(ROOM_I_INSIDE, 1);
    remove_prop(ROOM_I_LIGHT);
    add_prop(OBJ_S_SEARCH_FUN, "do_search");
    add_exit(NIMRAIS_DIR + "trolls/cave2","west",0,0);
    add_exit(NIMRAIS_DIR + "trolls/prisoncave","east",0,0);
}
 
public void
reset_room()
{
    ::reset_room();

    if (!present("ham"))
        clone_object(FOOD_DIR + "ham")->move(TO);

    if (!present("wine"))
        clone_object(FOOD_DIR + "wine")->move(TO);

    gEggFound = 0;
}
 
mixed
do_search(object searcher, string str)
{
    int awareness;
    object egg;
 
    if (gEggFound)
        return 0;

    if (!strlen(str))
        return 0; 

    if (!parse_command(str, ({}),
      "'food' / 'shelf' / 'shelves' [for] [food]"))
        return 0;
 
    awareness = searcher->query_skill(SS_AWARENESS);
    if ((awareness + random(10)) > 15)
    {
        egg = clone_object(NIMRAIS_DIR + "quest/obj/egg");
        gEggFound = 1;
        say(QCTNAME(searcher) + " finds an egg.\n", searcher);
        if (egg->move(searcher))
        {
            if (egg->move(TO))
                egg->move(TO, 1);
            return "You find an egg in one of the shelves!\n";
        }

        return "You find an egg in one of the shelves, and pick it up!\n";
    }

    return 0;
}
