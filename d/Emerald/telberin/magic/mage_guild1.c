/*
 *  /d/Emerald/telberin/magic/mage_guild1.c
 *
 *  This is the ground floor of the Mage Guild of Telberin. This guild
 *  is reserved mostly for those who have membership in its illustrious
 *  ranks. Though, they often will show favor on people seeking knowledge.
 *
 *  Copyright (c) February 2002, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

inherit TELBERIN_BUILDING;

#include <stdproperties.h>
#include "/d/Emerald/blackwall/delrimmon/defs.h"


/* prototypes */
public void        create_telberin_building();
public int         do_climb(string arg);
public int         check_exit();
public void        init();
public void        reset_room();

/* global variables */
public object       Elf_Mage;



/*
 * Function name:        create_telberin_building
 * Description  :        set up the room
 */
public void
create_telberin_building()
{
    set_short("on the ground floor of the Mage Guild of Telberin");
    set_em_long("This is the ground floor of a very tall tower which"
      + " houses the Mage Guild of Telberin. The architecture here is"
      + " deliberate and clean, yet beguiles the senses in some way"
      + " which is not readily apparent. Twisting staircases ascend"
      + " to higher levels in many corners of the room. Most prominently,"
      + " a very large and straight stairway runs up to another level"
      + " east of here, directly opposite a large archway, which leads"
      + " out on to the street.\n");

    add_item( ({ "ground", "floor", "down" }),
        "The floor of the tower is comprised of smooth polished stone."
      + " Footfalls on its surface echo now and again through the"
      + " chamber.\n");
    add_item( ({ "stone", "polished stone", "smooth stone",
                 "smooth polished stone", "slab", "slabs",
                 "architecture" }),
        "The tower is layered with huge slabs of polished stone. The"
      + " slabs have been cleanly fit together in lines which are"
      + " symmetrical, and yet in some manner queer. It is almost"
      + " as if certain angles bend in on themselves, tricking the"
      + " eye and confusing the sense of proportion.\n");
    add_item( ({ "here", "area", "chamber", "room", "tower",
                 "guild", "tall tower", "very tall tower",
                 "mage guild", "mage guild of telberin" }),
        "This room appears to be the main entry to the tower, serving"
      + " as a point of departure to the many and various chambers"
      + " of the Mage Guild.\n");
    add_item( ({ "stair", "stairs", "staircase", "staircases",
                 "twisting stair", "twisting stairs",
                 "twisting staircase", "twisting staircases",
                 "steps" }),
        "There are numerous staircases tucked into various corners"
      + " of this room, twisting their way towards unknown locations"
      + " in the upper levels of the tower. Most prominently, a large"
      + " and straight stairway leads up to the east.\n");
    add_item( ({ "large stair", "large stairs",
                 "large stairway", "large staircase",
                 "straight stair", "straight stairs",
                 "straight stairway", "straight staircase",
                 "large and straight stair",
                 "large and straight stairs",
                 "large and straight stairway",
                 "large and straight staircase",
                 "east" }),
        "A very large staircase climbs up to the east, passing"
      + " through a square opening in the chamber walls.\n");
    add_item( ({ "up", "roof", "ceiling" }),
        "The smooth polished stone of the ceiling is interrupted in"
      + " various places twisting stairs which pass through openings"
      + " to rise to higher levels of the tower.\n");
    add_item( ({ "higher level", "upper level", "higher levels",
                 "upper levels", "high levels",
                 "higher levels of the tower",
                 "upper levels of the tower" }),
        "One can only guess as to what lies in the higher levels"
      + " of this tower.\n");
    add_item( ({ "sky" }),
        "The sky is not visible from inside the tower.\n");
    add_item( ({ "square opening" }),
        "The square opening leads to the east, into some higher"
      + " chamber in the tower.\n");
    add_item( ({ "opening", "openings" }),
        "There are many openings in the walls of the chamber. The"
      + " two most prominent lead to the east and west. Numerous"
      + " openings in the ceiling yeild to twisting staircases which"
      + " climb through to higher levels.\n");
    add_item( ({ "wall", "walls", "chamber wall", "chamber walls",
                 "walls of the chamber", "stone wall", "stone walls",
                 "walls of stone", "wall of stone" }),
        "The walls of the chamber are comprised of smooth and"
      + " polished stone. They are unadorned, save for a large"
      + " tapestry of a winged Unicorn which hangs in the middle"
      + " of the northern wall.\n");
    add_item( ({ "north wall", "north", "northern wall" }),
        "The northern wall is adorned with a tall and beautiful"
      + " tapestry which depicts a winged Unicorn rising up on its"
      + " hind legs.\n");
    add_item( ({ "unicorn", "white unicorn", "winged unicorn"}),
        "The unicorn is quite lifelike, having been woven with"
      + " great care and skill. Its hide glimmers with threads of"
      + " white and silver.\n");
    add_item( ({ "arch", "archway", "large arch", "large archway",
                 "western opening", "west opening", "west" }),
        "A large archway opens out onto the street to the west.\n");
    add_item( ({ "street", "plaza", "enchanters plaza", "outside" }),
        "The sights and sounds coming from Enchanters Plaza are"
      + " vaguely noticable through the large archway to the west.\n");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_S_EXIT_FROM_DESC,
        "from inside the tower.");

    add_exit("/d/Emerald/telberin/magic/mage_guild2", "east",
             check_exit, 1, 1);
    add_exit("/d/Emerald/telberin/magic/mage_guild2", "up",
             check_exit, 1, 1);
    add_exit("/d/Emerald/telberin/magic/channelers_plaza", "west",
        0, 1, 1);

    reset_room();
} /* create_telberin_building */


/*
 * Function name:        check_exit
 * Description  :        only players who have helped find Rillian
 *                       are allowed into the library
 * Returns      :        1 - not allowed, 0 - allowed
 */
public int
check_exit()
{
    if (MANAGER->query_rillian(this_player()) != "Completed")
    {
        if (this_player()->query_wiz_level())
        {
            write("Since you are a wizard, you are allowed to pass."
                + " However, this room is not open for all mortals.\n");

            return 0;
        }
        write("A strange magical force blocks your path.\n");
        return 1;
    }

    return 0;
} /* check_exit */


/*
 * Function name:        do_climb
 * Description  :        allow players to try to climb the stairs
 * Arguments    :        string arg - what the player typed
 * Returns      :        int 1 - success, 0 - failure
 */
public int
do_climb(string arg)
{
    if (!strlen(arg))
    {
        notify_fail("Climb what?\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[up] [the] [twisting] [large] [and] [straight] [east] [eastern]"
      + " 'stair' / 'stairs' / 'stairway' / 'staircase'"))
    {
        return 0; /* bad syntax on player's behalf */
    }

    if (!parse_command(arg, ({}),
        "[up] [the] 'large' / 'straight' / 'east' / 'eastern'"
      + " [stair] [stairs] [staircase] [stairway]"))
    {
        if (!parse_command(arg, ({}),
            "[up] [the] 'twisting' [stair] [stairs] [staircase]"
          + " [stairway]"))
        {
            write("There are twisting stairways, and also a"
                + " straight stairway leading east. Which do you"
                + " mean?\n");
            return 1;
        }

        write("A strange magical force prevents you from"
            + " ascending the twisting staircases.\n");
        return 1;
    }

    write("You climb up the stairs, and pass to the east.\n");

    if (this_player()->query_wiz_level())
    {
        write("Normally, we would move the player 'east' here, using"
            + " command(). Since you are a wizard, that will not work."
            + " Simply type 'east' yourself.\n");
    }

    this_player()->command("$east");
    return 1;
} /* do_climb */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(do_climb, "climb");
} /* init */


/*
 * Function name:        reset_room
 * Description  :        we want to make sure Feni is here
 */
public void
reset_room()
{
    if (!Elf_Mage)
    {
        setuid();
        seteuid(getuid());

        Elf_Mage = clone_object(
            "/d/Emerald/telberin/magic/npc/satherel");

        Elf_Mage->move(this_object(), 1);
        tell_room(this_object(),
            "A tall regal elf strides into the room.\n");
    }
} /* reset_room */

public mixed
query_location_ids()
{
    return "[the] [great] [mage] [mages] "
      + "'tower' / 'guild' [of] [telberin]";
}

public mixed
query_location_closed()
{
    return 0;
}

public mixed
query_location_desc()
{
    return "To the east stands the Mage Guild of Telberin."
      + " Unlike the other great buildings in the City, this"
      + " one is not highly ornamented, or branching with many"
      + " spires and turrets. Rather, it appears as a single"
      + " great column which narrows as it rises. The only"
      + " features visible upon its sides are narrow windows,"
      + " and a large arched entryway.\n";
}


public string
query_entry_desc()
{
    return "into the tower";
}
