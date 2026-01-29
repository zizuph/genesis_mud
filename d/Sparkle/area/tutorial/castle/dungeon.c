/*
 *  /d/Sparkle/area/tutorial/castle/dungeon.c
 *
 *  This dungeon in the castle of Baron von Krolock is actually
 *  a secret passage to his lair.
 *
 *  Created October 2005, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

inherit CASTLE_DIR + "castle_room";

#include <language.h>
#include <macros.h>
#include <stdproperties.h>

/* Prototypes */
public void        create_castle_room();
public int         check_exit(string arg);
public string      describe(string arg);
public string      do_search(object pl, string arg);
public int         mess_with_statue(string arg);
public int         do_climb(string arg);
public void        init();


/*
 * Function name:    create_castle_room
 * Description  :    set up the room
 */
public void
create_castle_room()
{
    add_name("_tutorial_krolock_statue");

    set_short("in a very dark dungeon");
    set_long(describe);

    add_item( ({ "floor", "ground", "down" }),
        "There is not enough light to see much of the ground."
      + " You get the feeling that there are things here you"
      + " do not wish to see.\n");
    add_item( ({ "wall", "walls", }),
        "The walls are engulfed in shadow.\n");
    add_item( ({ "up", "roof", "ceiling" }),
        "There is nothing but blackness above your head.\n");
    add_item( ({ "here", "area", "room", "chamber", "dungeon" }),
        long);
    add_item( ({ "skeleton", "skeletons", "chain", "chains",
                 "wall", "walls", "shadow", "shadows" }),
        "In the shadows, you see the remains of prisoners of"
      + " Baron von Krolock. The chains which held them fast are"
      + " still fastened to their bones.\n");
    add_item( ({ "statue" }), &describe("statue"));
    add_item( ({ "stair", "step", "steps", "stone step",
                 "stone steps" }), &describe("steps"));
    add_item( ({ "foot", "feet", "foot of the statue",
                 "feet of the statue" }), &describe("foot"));
    add_item( ({ "thumb", "thumb of the statue" }),
        &describe("thumb"));
    add_item( ({ "nose", "nose of the statue" }), &describe("nose"));
    add_item( ({ "ear", "ears", "ear of the statue",
                 "ears of the statue" }), &describe("ear"));
    add_item( ({ "hand", "hands", "hand of the statue",
                 "hands of the statue" }), &describe("hand"));
    add_item( ({ "mouth", "mouth of the statue" }),
        &describe("mouth"));
    add_item( ({ "toe", "toes", "toe of the statue",
                 "toes of the statue" }), &describe("toe"));
    add_item( ({ "finger", "fingers", "finger of the statue",
                 "fingers of the statue" }), &describe("finger"));
    add_item( ({ "tooth", "teeth", "tooth of the statue",
                 "teeth of the statue" }), &describe("tooth"));
    add_item( ({ "eye", "eyes", "eye of the statue",
                 "eyes of the statue" }), &describe("eye"));

    add_prop(OBJ_S_SEARCH_FUN, "do_search");
    add_prop(ROOM_I_LIGHT, 0); /* darkness */

    add_exit("hallway_6", "up");
    add_exit("combat_lair", "down", check_exit, 1, &check_exit("invis"));

    reset_room();
} /* create_castle_room */


/*
 * Function name:        check_exit
 * Description  :        see if we allow the player to use the exit,
 *                       or if called from the 5th argument, see if
 *                       the exit is obvious
 * Returns      :        int 1 - block/unobvious, 0 - allow/obvious
 */
public int
check_exit(string arg)
{
    if (strlen(arg))
    {
        if (CHECK_TUTORIAL_BIT(STATUE_BIT))
        {
            return 0;
        }

        return 1;
    }

    if (CHECK_TUTORIAL_BIT(STATUE_BIT))
    {
        write("These stairs are long and difficult. You will need to"
          + " <climb> down them.\n");
        return 1;
    }

    write("There is no obvious exit down.\n");
    return 1;
} /* check_exit */


/*
 * Function name:        describe
 * Description  :        provide a status dependant descriptions
 * Arguments    :        string arg - what are we describing?
 * Returns      :        string - various descriptions of things
 */
public string
describe(string arg)
{
    int     name = strlen(this_player()->query_real_name());
    string  norm = "You see nothing odd about that part of the"
                 + " statue.\n";
    string  missing = "The statue is missing " + LANG_ADDART(arg)
                    + ".\n";
    string  statue =
        "An unnatural terror seizes you as you gaze upon the statue"
      + " which stands amid the darkness of this dungeon. Stark white,"
      + " it stares at you with immovable hatred. Though the eyes"
      + " are nothing but dead stone, this visage of Baron von"
      + " Krolock himself seems to be studying you with great"
      + " interest.\n";
    string  room = "The light can barely illuminate this terrible"
      + " chamber of darkness. You appear to be in a dungeon of some"
      + " kind. In the shadows along the walls you catch glimpses of"
      + " skeletons in chains. ";

    if (!strlen(arg))
    {
        if (CHECK_TUTORIAL_BIT(STATUE_BIT))
        {
            room += "A statue at the center of the room has been"
              + " moved aside to reveal a set of stone steps leading"
              + " down into darkness.";
        }
        else
        {
            room += "But these are almost comforting in comparison"
              + " to the fear you feel toward the statue that stands"
              + " at the center of the room. It fills you with"
              + " horror!";
        }

        return room + "\n\n";
    }

    if (!CHECK_TUTORIAL_BIT(FRAGMENT_BIT))
    {
        missing = "Hmmm ... something seems odd there. Perhaps if"
          + " you searched around a bit, you could notice more.\n";
    }

    switch(arg)
    {
        case "statue":
            if (CHECK_TUTORIAL_BIT(STATUE_BIT))
            {
                return "The statue has somehow moved from where it"
                  + " had originally been standing, revealing a"
                  + " set of stone steps spiraling downward into"
                  + " darkness.\n";
                break;
            }
            return statue;
            break;
        case "steps":
            if (CHECK_TUTORIAL_BIT(STATUE_BIT))
            {
                return "Stone steps spiral down through the floor"
                  + " into darkness.\n";
                break;
            }
            return "You find no steps.\n";
        case "foot":
            if (name == 2)
            {
                return missing;
            }            
            return norm;
        case "thumb":
            if (name == 3)
            {
                return missing;
            }            
            return norm;
        case "nose":
            if (name == 4)
            {
                return missing;
            }            
            return norm;
        case "ear":
            if (name == 5)
            {
                return missing;
            }            
            return norm;
        case "hand":
            if (name == 6)
            {
                return missing;
            }            
            return norm;
        case "mouth":
            if (name == 7)
            {
                return missing;
            }            
            return norm;
        case "toe":
            if (name == 8)
            {
                return missing;
            }            
            return norm;
        case "finger":
            if (name == 9)
            {
                return missing;
            }            
            return norm;
        case "tooth":
            if (name == 10)
            {
                return missing;
            }            
            return norm;
        case "eye":
        default:
            if (name == 11)
            {
                return missing;
            }            
            return norm;
    } /* switch(arg) */
} /* describe */


/*
 * Function name:        do_search
 * Description  :        allow the player to search things in the room
 * Arguments    :        object pl  - the player object,
 *                       string arg - what the player tried to search
 * Returns      :        int 1 - success, 0 - failure
 */
public string
do_search(object pl, string arg)
{
    string  part;

    switch(strlen(pl->query_real_name()))
    {
        case 2:
            part = "foot";
            break;
        case 3:
            part = "thumb";
            break;
        case 4:
            part = "nose";
            break;
        case 5:
            part = "ear";
            break;
        case 6:
            part = "hand";
            break;
        case 7:
            part = "mouth";
            break;
        case 8:
            part = "toe";
            break;
        case 9:
            part = "finger";
            break;
        case 10:
            part = "tooth";
            break;
        case 11:
        default:
            part = "eye";
            break;
    }

    if (!strlen(arg) || (member_array(arg,
        ({ "statue", "the statue", part, part + " of the statue",
           "statue " + part }) ) == -1))
    {
        return "Your search reveals nothing special.\n";
    }

    SET_TUTORIAL_BIT(FRAGMENT_BIT);
    return "You carefully scour every surface of the statue, looking"
      + " for anything out of the ordinary. It is very slow going,"
      + " both because the light is so poor, and the statue is so"
      + " fearful. Eventually, you notice that the statue appears"
      + " to be missing " + LANG_ADDART(part) + ".\n";
} /* do_search */


/*
 * Function name:        mess_with_statue
 * Description  :        allow players to fiddle with the statue
 * Arguements   :        string arg - what was typed after the verb
 * Returns      :        int 1 - success, 0 - otherwise
 */
public int
mess_with_statue(string arg)
{
    if (!strlen(arg))
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[on] [the] 'statue'"))
    {
        return 0; /* bad syntax */
    }

    if (query_verb() == "move" || query_verb() == "lift" ||
        query_verb() == "turn")
    {
        write("How do you intend to do that?\n");
        return 1;
    }

    write("You " + query_verb() + " with all of your might on the"
      + " statue, but it does not budge.\n");
    return 1;
} /* mess_with_statue */


/*
 * Function name:        do_climb
 * Description  :        allow players to climb down the stairs
 * Arguments    :        What the player typed after the verb
 * Returns      :        1 - success, 0 - otherwise
 */
public int
do_climb(string arg)
{
    object  destination;

    if (!CHECK_TUTORIAL_BIT(STATUE_BIT))
    {
        return 0; /* no hints if they haven't moved the statue */
    }

    if (!strlen(arg))
    {
        notify_fail("Climb what?\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[down] [the] [long] [difficult] [dark] 'step' / 'steps' /"
      + " 'stair' / 'stairs' / 'stairway'"))
    {
        if (arg == "down")
        {
            notify_fail("Climb down what?\n");
        }
        return 0; /* bad syntax */
    }

    if (CHECK_TUTORIAL_BIT(DESTROYER_BIT))
    {
        destination = clone_object(CASTLE_DIR + "destroyer_lair");
    }
    else if (CHECK_TUTORIAL_BIT(KROLOCK_BIT))
    {
        destination = clone_object(CASTLE_DIR + "defeat_lair");
    }
    else
    {
        destination = clone_object(CASTLE_DIR + "combat_lair");
    }

    write("You climb carefully down the long stairway to a level"
      + " below.\n\n");

    if (!this_player()->query_prop(LAIR_PROP))
    {
        this_player()->add_prop(LAIR_PROP, destination);
    }

    this_player()->move_living("M",
        this_player()->query_prop(LAIR_PROP)->get_this_object(), 1, 0);
    tell_room(this_object(), QCTNAME(this_player()) + " disappears"
      + " into the darkness.\n");

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

    add_action(mess_with_statue, "pull");
    add_action(mess_with_statue, "push");
    add_action(mess_with_statue, "move");
    add_action(mess_with_statue, "lift");
    add_action(mess_with_statue, "turn");
    add_action(do_climb, "climb");
} /* init */
