/*
 * shaman area entrance room  
 * Boreaulam, JAN 2014
 */
#include "defs.h"
#pragma strict_types

inherit L2_BASE_ROOM;

/*
 * Function name:        create_room
 * Description  :        creates room
 */
void
create_room()
{
    ::create_room();

    set_short("Big cave entrance");
    set_long("You are standing in a very large cave, where a chaotic " +
        "mosaic spreads out across the floor. There are three tunnels " +
        "which lead away from this room to the east, each following a " +
        "trail of decorative stones which branch out from the mosaic " +
        "at your feet. The walls and ceiling here are carved from the " +
        "dull, grey stone of the mountain, all brightly illuminated by " +
        "the torches which have been hung upon the walls here. A small " +
        "hole in the western wall leads back up to the caves you came " +
        "down from.\n\n");
    add_item(({"ceiling", "up"}),
        "The dull grey stone of the ceiling has been roughly chiseled, " +
        "obviously worked by hand to expand what was probably a " +
        "naturally existing cave at first.\n");
    add_item(({"torch", "torches"}),
        "Several torches have been mounted on the north, west and south " +
        "walls here.\n");
    add_item(({"stone", "grey stone", "granite"}),
        "This dull grey stone is the very bones of the mountains you are " +
        "currently beneath. This granite is very hard, but in many places " +
        "it appears that several industrious goblins have chiseled away " +
        "at the walls and ceilings to make these caves more habitable.\n");
    add_item(({"wall", "walls"}),
        "The walls here are made of the same grey stone as everything " +
        "else in these caves. Several torches have been mounted on the " +
        "walls here, providing a reasonable amount of light.\n");
    add_item(({"floor", "down"}),
        "The floor here is covered in a chaotic mosaic of decorative stones. " +
        "There are three colours of stones: black, white and grey, with " +
        "each colour flowing away from the mosaic to lead down its own " +
        "path along one of the western tunnels.\n"); 
    add_item(({"west wall", "western wall"}),
        "The western wall is rather bare, save for a handful of torches " +
        "which have been mounted here to provide some light and a small " +
        "hole which leads back to the caves you just came from.\n"); 
    add_item(({"north wall", "northern wall"}),
        "The northern wall is rather bare, save for a handful of torches " +
        "which have been mounted here to provide some light.\n");
    add_item(({"south wall", "southern wall"}),
        "The southern wall is rather bare, save for a handful of torches " +
        "which have been mounted here to provide some light.\n");
    add_item(({"east wall", "eastern wall"}),
        "There are three corridors tunneling away from this cave in the " +
        "eastern wall. Each of the corridors has a path of decorative " +
        "stones which cover the floor.\n");
    add_item(({"east tunnel", "east corridor", "eastern tunnel",
              "eastern corridor"}),
        "The eastern corridor follows a path of decorative grey stones, " +
        "flowing out of the mosaic at your feet and trailing off down " +
        "the tunnel.\n");
    add_item(({"northeast tunnel", "northeast corridor", "northeastern tunnel",
              "northeastern corridor"}),
        "The northeastern corridor follows a path of decorative white " +
        "stones, flowing out of the mosaic at your feet and trailing off " +
        "down the tunnel.\n");
    add_item(({"southeast tunnel", "southeast corridor", "southeastern tunnel",
            "southeastern corridor"}),
        "The southeastern corridor follows a path of decorative black " +
        "stones, flowing out of the mosaic at your feet and trailing off " +
        "down the tunnel.\n");
    add_item(({"mosaic", "strange mosaic", "floor"}),
        "There is a rather strange and mysterious looking mosaic which " +
        "covers the floor of this large cave. There are decorative stones " +
        "of white, grey and black which swirl around in utter chaos, before " +
        "eventually sorting themselves out as they reach towards the " +
        "eastern wall. Each of " +
        "the three colours of stones follows its own corridor, white to the " +
        "northeast, grey directly to the east and lastly black to the " +
        "southeast.\n");
    add_item(({"corridor", "corridors", "tunnels", "tunnel"}),
        "There are three corridors which lead east out of this cave, " +
        "each with a path of decorative stones covering the ground.\n");
    add_item(({"opening", "hole", "small hole", "small opening"}),
             "There is a small hole in the western wall that you could " +
             "enter to return back up to the other caves.\n");
    add_item(({"trails", "trail", "stones", "decorative stones",
            "decorative stone"}),
        "There are three trails of decorative stones on the floor here, " +
        "each leading into one of the three corridors leading away from " +
        "this cave.\n");

    add_exit("shaman_ne", "northeast");
    add_exit("shaman_e", "east");
    add_exit("shaman_se", "southeast");

} /* create_room */

/*
 * Function name:        init
 * Description  :        on init hook
 */
void
init()
{
    ::init();
    add_action("enter", "enter", 0);
} /* init */

/*
 * Function name:        enter
 * Description  :        enters into opening
 */
int
enter(string s)
{
    if (!strlen(s))
    {
        notify_fail("Enter what?\n");
        return 0;
    }

    if (!parse_command(s, ({}),
        "[in] [to] [into] [the] [small] 'hole' [in] [the] [west]"
      + " [western] [wall]"))
    {
        notify_fail("Where do you want to enter?\n");
        return 0;
    }

    set_dircmd("hole");
    TP->move_living("into the small hole", ROOMS_DIR + "level2/roomd4");
    return 1;
} /* enter */
