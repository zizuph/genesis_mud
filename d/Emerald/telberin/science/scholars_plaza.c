/*
 * /d/Emerald/telberin/arts/scholars_plaza.c
 *
 * The hub of scientific activity in Telberin, this plaza is the major
 * meeting place of those for whom discovery is of primary importance. 
 * It is located at the northern tip of Scholars Way in the Science
 * Quarter of Telberin.
 *
 * Copyright (c) March 2003, by Cooper Sherry (Gorboth)
 */

inherit "/d/Emerald/telberin/telberin_street";
#include <macros.h>


/* prototypes */
public void    create_telberin_street();


/*
 *  Function name:        create_telberin_street
 *  Description  :        set up the room
 */
public void
create_telberin_street()
{
    set_em_long("At the northern end of the elipse which has ringed"
      + " a long reflecting pool to the south, the street widens into"
      + " a circular paved area here. This is Scholars Plaza, the"
      + " main hub of scientific activity in Telberin. To the north,"
      + " a long and formidable building looms over the cobblestones"
      + " of the road. To the west, a great clock tower rises high"
      + " above the plaza. In the middle of the plaza, a large white"
      + " obelisk stands amidst the activity. Scholars Way runs back"
      + " toward the Royal Circle to the southwest and southeast.\n");

    add_item( ({ "paved area", "circular area",
                 "circular paved area" }),
        "The plaza is clearly a central meeting place for many of"
      + " the great minds of Telberin. Evidence of thought and order"
      + " is present everywhere you look.\n");
    add_item( ({ "long building", "formidable building", "library",
                 "long and formidable building", "north", "building",
                 "library of telberin", "telberin library" }),
        "A long and formidable building to the north looks large"
      + " enough to house every person in the City. A sign hangs"
      + " above its arched doorway.\n");
    add_item( ({ "doorway", "arched doorway", "door", "doors",
                 "entry", "entrance" }),
        "An arched doorway leads into the building north of here. Above"
      + " the doors, a large alabaster sign has been hung.\n");
    add_item( ({ "sign", "large sign", "alabaster sign",
                 "large alabaster sign" }),
        "A large sign hangs above the doors of the building. It reads:"
        + " 'The Library of Telberin.'\n");
    add_item( ({ "mound", "small mound", "bed", "beds",
                 "round stones", "multicolored stone", 
                 "multicolored stones",
                 "multicolored round stone",
                 "multicolored round stones",
                 "bed of multicolored round stones",
                 "beds of multicolored round stones" }),
        "The many multicolored stones which make up the bed upon the"
     + " mound look carefully placed. There is an order at work in"
     + " most things here.\n");
    add_item( ({ "obelisk", "large obelisk", "white obelisk",
                 "large white obelisk" }),
        "The obelisk has been erected in the center of the plaza, atop"
      + " a small mound which is decorated with beds of multicolored"
      + " round stones. An image has been painted upon the sides of the"
      + " obelisk in dark gold.\n");

    add_item( ({ "map", "paint", "paintint", "obelisk map",
                 "map of telberin", "street map of telberin",
                 "sides", "sides of the obelisk", "street map",
                 "image", "carved image", "carving", "carved map",
                 "map on the obelisk" }), read_file(
        "/d/Emerald/telberin/science/science_map.txt", 0));

    add_cmd_item( ({ "sign", "large sign", "alabaster sign",
                     "large alabaster sign" }),
                  ({ "read" }),
        "The sign reads: 'The Library of Telberin.'\n");

    config_street_room("Arts",
                       "Cantors Plaza");

    add_exit("/d/Emerald/telberin/scholars_way03", "southeast");

    set_no_exit_msg( ({ "north" }),
        "As you walk towards the door, an elf steps before you, saying:"
      + " Only members of the Scholars Guild of Telberin are"
      + " admitted to the Library at this time.\n");
    set_no_exit_msg( ({ "southwest" }),
        "To the southwest, destruction from recent raids has forced"
      + " Scholars Way to be shut off from transportation. Repair"
      + " work appears to be underway.\n");
} /* create_telberin_street */



/*
 * Function name:        do_enter
 * Description  :        allow players to try to enter the library
 * Arguments    :        string arg - what the player typed
 * Returns      :        int 1 - success, 0 - failure
 */
public int
do_enter(string arg)
{
    if (!strlen(arg))
    {
//      notify_fail("Enter what?\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[the] [long] [long,] [and] [formidable]"
      + " 'library' / 'building' [of] [telberin]"))
    {
        return 0; /* can't parse the player's syntax */
    }

    if (this_player()->query_wiz_level())
    {
        write("Normally, we would move the player 'north' here, using"
          + " 'command.' Since you are a wizard, that won't work. Simply"
          + " go 'north' yourself.\n");
        return 1;
    }

    this_player()->command("north");
    return 1;
} /* do_enter */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(do_enter, "enter");
} /* init */
