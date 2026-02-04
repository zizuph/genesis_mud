/*
 * cave04.c
 *
 * The batcave.  Here the player may obtain batshit for the batshit quest.
 *
 * Lucius - Jan 2021
 *   Cleaned up and modernized.
 */
#include "/d/Terel/include/Terel.h"
inherit MOUNTAIN_DIR + "goblincave/cave_room";

public int pick();

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_terel_room()
{
    FIX_EUID;
    ::create_terel_room();

    set_short("batcave");
    set_long(query_long() +
        "High pitched squealing sounds can be heard from the bats "+
        "hanging in the high ceiling. The ground is covered with "+
        "lumps of bat droppings.\n");

    DARK;

    add_item(({"bat droppings", "droppings", "lumps",
            "guano", "bat guano", "lumps of bat droppings"}),
        "There are a lot of small lumps of bat droppings here. "+
        "A more educated person than you would call them bat guano, "+
        "on the other hand that educated person would never try "+
        "picking them either.\n");

    add_item(({"bat", "bats"}),
        "They hang from the ceiling, much too high for you "+
        "to reach them.\n");

    add_cmd_item(({"bat droppings", "droppings", "lumps",
            "guano", "bat guano", "lumps of bat droppings"}),
        "pick", pick);

    add_exit(MOUNTAIN_DIR + "goblincave/cave05", "east");
}

/*
 * Function name: pick
 * Description:   Handle pick action for the batshit cmditem
 * Returns:       1/0
 */
public int
pick()
{
    if (TP->query_prop("picked_shit"))
    {
        NF("You don't find a good piece of batguano, so you stop looking.\n");
        return 0;
    }


    object batshit = clone_object(MOUNTAIN_DIR + "goblincave/obj/batshit");
    batshit->add_prop("_shit_picker", TP->query_name());
    if (batshit->move(TP))
        batshit->move(TP, 1);

    TP->add_prop("picked_shit", 1);
    write("With a wince you pick up a good looking piece of bat guano and "+
          "put it in your pocket.\n");
    say(QCNAME(TP)+" gently picks a lump of bat dropping.\n");
    return 1;
}

/*
 * Function name: hook_smelled
 * Description:   What does the air smell like here?
 * Returns:       The description of the smell
 */
public string
hook_smelled(string str)
{
    if (!strlen(str))
        write("The reek of bats and bat droppings is in the air.\n");
    else if (IN_ARRAY(str, ({"bat droppings", "droppings", "lumps",
            "guano", "bat guano", "lumps of bat droppings" })))
        write("The bat guano smells like shit from a bat.\n");
}
