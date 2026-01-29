/*
 *  /d/Sparkle/area/orc_temple/rooms/3_chambers.c
 *
 *  These are the personal chambers of the High Priest.
 *
 *  Created November 2010, by Cooper Sherry (Gorboth)
 *
 *  Updated July 2016 by Gronkas: fixed some typos
 */
#pragma strict_types

#include "../defs.h"

inherit ROOMS_DIR + "dungeon_room";

#include <cmdparse.h>
#include <language.h>
#include <macros.h>
#include <time.h>

#include "/d/Sparkle/sys/quests.h"


/* Definitions */
#define FORGE_FILLED    "_sparkle_dungeon_enchanter_forge"
#define INSERTED_TEARS  "_sparkle_dungeon_forge_tears"


/* Prototypes */
public void         create_dungeon_room();
public string       exa_forge();
public int          do_insert(string arg);
public string       exa_shelf();
public int          fill_forge(string arg);
public int          get_reagent(string arg);
public void         init();
public string       exa_reagents(string arg);
public string       room_search(mixed obj, string arg);
public string       exa_furnace();
public int          fit_socket(string arg);
public void         light_tears(object who);
public string       exa_socket(string arg = "socket");


/*
 * Function name:        create_dungeon_room
 * Description  :        constructor for the room
 */
public void
create_dungeon_room()
{
    object   door;

    set_short("a stately chamber");
    set_long("This stately chamber is nothing like the other areas of"
      + " these dungeons. The walls are hung with many fabrics and"
      + " tapestries that hide the ugly brickwork. Rich carpets"
      + " layer every inch of the floor, and an honest to goodness"
      + " bed rests against the far wall. There is an oak desk"
      + " positioned along the southern wall. Beside the desk,"
      + " a candelabra burns with many red candles. A strange"
      + " device of some kind stands before the north wall.\n\n");

    add_item( ({ "wall", "walls" }),
        "The walls of this chamber are mostly covered with various"
      + " types of fabrics or tapestries.\n");
    add_item( ({ "chamber", "stately chamber", "area", "here",
                 "room", "bedroom" }),
        "This does not appear to be the dwelling of an orc!\n");
    add_item( ({ "dwelling", "dwelling of an orc" }),
        "This looks quite civilized, in fact.\n");
    add_item( ({ "other area", "other areas",
                 "other areas of the dungeons",
                 "other area of the dungeons" }),
        "In other words, not this room.\n");
    add_item( ({ "dungeon", "dungeons", "these dungeons" }),
        "In here, you could almost forget you were in an dungeon at"
      + " all.\n");
    add_item( ({ "fabric", "fabrics", "rich fabric", "rich fabrics" }),
        "Velvet, satin, silk ... all in deep purple and red colours.\n");
    add_item( ({ "velvet", "velvet fabric" }),
        "Oooo ... so fuzzy!\n");
    add_item( ({ "satin", "satin fabric" }),
        "Oooo ... so elegant!\n");
    add_item( ({ "silk", "silk fabric" }),
        "Oooo ... so smooth!\n");
    add_item( ({ "purple", "red", "color", "colors",
                 "colour", "colours", "purple color", "red color",
                 "purple colour", "red colour",
                 "purple colors", "red colors",
                 "purple colours", "red colours",
                 "purple and red colours",
                 "purple and red colors" }),
        "This bedroom looks almost royal!\n");
    add_item( ({ "deep purple", "deep purple color",
                 "deep purple colour" }),
        "Smoke on the water ...\n");
    add_item( ({ "tapestry", "tapestries" }),
        "The tapestries appear almost scholarly in nature, containing"
      + " arcane symbols you do not recognize.\n");
    add_item( ({ "symbol", "arcane symbol", "arcane symbols",
                 "symbols" }),
        "They are unknown to you.\n");
    add_item( ({ "brick", "bricks", "brickwork", "ugly brickwork" }),
        "The bricks are mostly obscured by the fabrics and"
      + " tapestries.\n");
    add_item( ({ "ceiling", "roof", "up" }),
        "The ceiling is hung with the same fabrics which cover much of"
      + " the walls.\n");
    add_item( ({ "floor", "ground", "down" }),
        "Rich carpets cover the floor. This chamber is, without question,"
      + " the most comfortable place you have seen down here.\n");
    add_item( ({ "carpet", "carpets", "rich carpet", "rich carpets" }),
        "Oooo ... so plush!\n");
    add_item( ({ "bed", "honest to goodness bed" }),
        "Oooo ... so soft!\n");
    add_item( ({ "far wall", "east wall", "eastern wall" }),
        "The eastern wall has a bed against it. I suppose bedrooms"
      + " do tend to have those.\n");
    add_item( ({ "oak" }),
        "The oak of the desk is actually of very high quality.\n");
    add_item( ({ "desk", "oak desk" }),
        "The desk looks well-used. A gem-encrusted tome rests upon"
      + " its surface. Beside the desk, you notice a small shelf"
      + " filled with glass jars.\n");
    add_item( ({ "surface", "surface of the desk", "desk surface" }),
        "There is a gem-encrusted tome there. Exciting!\n");
    add_item( ({ "southern wall", "south wall" }),
        "The southern wall is distinguished by the desk that sits just"
      + " in front of it.\n");
    add_item( ({ "candle", "candles", "red candle", "red candles" }),
        "Strangely, they do not seem to melt as they burn.\n");
    add_item( ({ "candelabra" }),
        "It looks like it holds about seven or eight candles.\n");
    add_item( ({ "writings" }),
        "The desk does indeed contain many writings on the subject of"
      + " demons.\n");
    add_item( ({ "alcove", "west wall", "western wall" }),
        "An alcove in the western wall contains a door.\n");
    add_item( ({ "north wall", "wall to the north", "northern wall" }),
        "The north wall is covered with the same fabric as the rest of"
      + " the room. However, a strange device is on the floor at the"
      + " foot of this wall.\n");
    add_item( ({ "device", "strange device", "forge",
                 "enchanting forge", "enchanters forge",
                 "enchanter's forge" }),
        "@@exa_forge@@");
    add_item( ({ "cube", "cube-like structure" }),
        "The strange device looks only vaguely like a cube.\n");
    add_item( ({ "shelf", "small shelf", "jar", "jars",
                 "glass jar", "glass jars",
                 "shelf filled with glass jars",
                 "small shelf filled with glass jars", "reagent",
                 "reagents" }),
        "@@exa_shelf@@");
    add_item( ({ "furnace" }), "@@exa_furnace@@");
    add_item( ({ "socket", "sockets", "tear shaped socket",
                 "tear-shaped socket", "eight sockets",
                 "eight tear-shaped sockets",
                 "eight teach shaped sockets",
                 "tear-shaped sockets",
                 "tear shaped sockets", }), "@@exa_socket@@");
    add_item( ({ "tear", "tears", "crystalline tear",
                 "crystalline tears" }), &exa_socket("tear"));
    add_item( ({ "details", "detail" }),
        "The device is extremely complex. The details are many.\n");

    add_item("sandalwood", &exa_reagents("sandalwood"));
    add_item("redcorn", &exa_reagents("redcorn"));
    add_item("dustwing", &exa_reagents("dustwing"));
    add_item("shallowfelt", &exa_reagents("shallowfelt"));
    add_item("firecone", &exa_reagents("firecone"));
    add_item("skyshade", &exa_reagents("skyshade"));
    add_item("bluebark", &exa_reagents("bluebark"));
    add_item("icemoss", &exa_reagents("icemoss"));
    add_item("whitewood", &exa_reagents("whitewood"));
    add_item("marblecone", &exa_reagents("marblecone"));
    add_item("blackbark", &exa_reagents("blackbark"));

    add_cmd_item( ({ "candle", "candles", "red candle", "red candles",
                     "candelabra" }),
                  ({ "extinguish" }),
        "The candles somehow resist your attempts. Perhaps there is some"
      + " magic at work here.\n");

    add_cmd_item( ({ "candle", "candles", "red candle", "red candles",
                     "candelabra" }),
                  ({ "light" }),
        "The candles are already lit.\n");

    add_delay_cmd_item(
        ({ "bed", "beds" }),
        ({ "lie", "sleep", "rest" }),
        "resting on the bed",
        5,
        "You stretch out on the bed ... ah ... that's good!\n",
        "Well, that was nice. Time to keep on adventuring, though!\n");

    add_delay_cmd_item(
        ({ "fabric", "fabrics", "rich fabric", "rich fabrics" }),
        ({ "search" }),
        "searching the fabrics",
        10,
        "You begin searching through the many rich fabrics.\n",
        "Moving the fabrics aside, you find nothing but ugly"
      + " brickwork behind them.\n");

    add_delay_cmd_item(
        ({ "desk", "oak desk" }),
        ({ "search" }),
        "searching the oak desk",
        10,
        "You begin searching through the oak desk.\n",
        "The oak desk contains numerous writings on demon summoning,"
      + " containment, and worship. Beside the desk, you notice a"
      + " shelf containing many glass jars. Other than this, all you"
      + " find is a gem-encrusted tome sitting atop the desk.\n");

    add_delay_cmd_item(
        ({ "carpet", "rich carpet", "carpets", "rich carpets" }),
        ({ "search" }),
        "searching the carpets",
        10,
        "You begin searching under the carpets.\n",
        "Under the carpets you find nothing but the very rough and ugly"
      + " floor of the dungeon. Makes sense that someone would put"
      + " the carpets here, I guess.\n");

    add_cmd_item( ({ "writings", "writings on demon summoning" }),
                  ({ "read" }),
        "The writings describe various pre-conditions that must exist"
      + " for summoning demons. Many mentions of pentagrams, focus"
      + " points, blood offerings, etcetera exist. Nasty stuff!\n");

    add_cmd_item( ({ "jar", "jars", "reagent", "reagents", "glass jar",
                     "glass jars" }),
                  ({ "get", "take", "steal" }),
        "If there were a particular reagent on the shelf that interested"
      + " you, you might be able to take it. That would probably require"
      + " some knowledge of what it was and why you needed it, though.\n");

    add_prop(OBJ_S_SEARCH_FUN, "room_search");

    door = clone_object(DOORS_DIR + "3_priest_e");
    door->move(this_object());

    room_add_object(OBJ_DIR + "priest_journal");

    set_no_exit_msg( ({ "northwest", "north", "northeast", "east",
                        "southeast", "south", "southwest" }),
        "You boldly stroll directly into a wall. OOOF!\n");

    setuid();
    seteuid(getuid());
} /* create_dungeon_room */


/*
 * Function name:        add_dungeon_tells
 * Description  :        Have this room use madness tells.
 */
public void
add_dungeon_tells()
{
    /* No tells in here. Silence for meditation, sleep, etc. */
} /* add_dungeon_tells */


/*
 * Function name:        exa_forge
 * Description  :        Show players a description of the enchanters
 *                       forge, with state-dependant results.
 * Returns      :        string - the description
 */
public string
exa_forge()
{
    string   filled = this_player()->query_prop(FORGE_FILLED);
    string   journal_read = this_player()->query_prop(JOURNAL_REAGENT_PROP);
    int      tear_num = this_player()->query_prop(INSERTED_TEARS);
    string   basic_desc;
    string   tears_desc;
    string   furnace_desc;

    if (!journal_read)
    {
        if (this_player()->test_bit("Sparkle",
                ORCTEMPLE_JOURNAL_GROUP,
                ORCTEMPLE_JOURNAL_BIT))
        {
            return "The device is strange, and highly complex. Though"
              + " you recall at one time learning about how it works,"
              + " you'd probably need to refresh your memory with"
              + " some instructions again before you could remember"
              + " what all the details mean.\n";
        }

        return "The device is strange - unlike anything you have ever"
          + " heard about. It looks vaguely like a cube, but the details"
          + " are confusing to you. You'd probably need to find"
          + " instructions before you understood what you see.\n";
    }

    basic_desc = "From what you have read in the priest's tome, you"
      + " recognize this to be none other than the enchanter's forge"
      + " built by Karkadelt for his brother. An opening atop the"
      + " cube-like structure would allow you to <insert> something"
      + " that you wanted to try to enchant. ";

    tears_desc = "Surrounding the opening are eight tear-shaped"
      + " sockets, ";

    switch (tear_num)
    {
        case 0:
            tears_desc += "all of which are empty. You could"
              + " probably <fit> something into one of the sockets"
              + " if you had the correct item. ";
            break;
        case 8:
            tears_desc += "all of which have been filled with"
              + " crystalline tears. ";
            if (filled && tear_num > 7)
            {
                tears_desc += "The tears pulse with the power of"
                  + " the fuel within the forge. ";
            }
            break;
        case 1:
            tears_desc += "one of which has been filled with a"
              + " crystalline tear. ";
            break;
        default:
            tears_desc += LANG_NUM2WORD(tear_num) + " of which "
              + "have been filled with crystalline tears. ";
            break;
    }

    if (!filled)
    {
        furnace_desc = "Toward the base of the device, you notice"
          + " what must be the furnace, which perhaps you could"
          + " <fuel> with something.";
    }
    else
    {
        furnace_desc = "The forge is lit from within, and resonates"
          + " with warm energies from the " + filled + " in its"
          + " furnace.";
    }

    return basic_desc + tears_desc + furnace_desc + "\n";
} /* exa_forge */


/*
 * Function name:        do_insert
 * Description  :        Allow players to insert something into the
 *                       device
 * Arguments    :        string arg - what was typed after the verb
 * Returns      :        int 1 - success, 0 - failure
 */
public int
do_insert(string arg)
{
    object   obj;
    string   filled = this_player()->query_prop(FORGE_FILLED);
    int      num_tears = this_player()->query_prop(INSERTED_TEARS);

    if (!this_player()->query_prop(JOURNAL_REAGENT_PROP))
    {
        return 0;
    }

    if (!strlen(arg))
    {
        notify_fail("Insert what?\n");
        return 0;
    }

    if (!parse_command(arg, all_inventory(this_player()),
        "[the] %o [in] [into] [the] [enchanter] [enchanters] [enchanter's]"
      + " [strange] 'forge' / 'device' / 'opening'", obj))
    {
        notify_fail("Do you want to <insert> something into the forge,"
          + " perhaps?\n");
        return 0;
    }

    if (obj->id(QUEST_TEAR))
    {
        notify_fail("Perhaps you wish to <fit> the tear into one"
          + " of the sockets?\n");
        return 0;
    }

    if (!obj->id(QUEST_WEAPON))
    {
        write("You insert the " + obj->short() + " into the forge, but"
          + " nothing seems to happen.\n");
        tell_room(environment(this_player()), QCTNAME(this_player())
          + " inserts " + LANG_ADDART(obj->short()) + " "
          + obj->short() + " into the strange device, but nothing"
          + " seems to happen.\n", this_player());

        return 1;
    }

    if (obj->query_imbued())
    {
        write("The " + obj->short() + " has already been imbued. No need"
          + " to fuss with it further. You should return to the enchanter"
          + " and <show> it to him!\n");

        return 1;
    }

    if (!filled || num_tears < 7)
    {
        write("You insert the " + obj->short() + " into the forge. The"
          + " weapon vibrates slightly, but nothing else happens."
          + " Perhaps something has been overlooked?\n");
        return 1;
    }

    if (!this_player()->test_bit("Sparkle",
            ORCTEMPLE_WEAPON_GROUP,
            ORCTEMPLE_WEAPON_BIT))
    {
        write("Just as you are about to go through with it, you pause"
          + " and remember that the Enchanter wanted you to bring this"
          + " to him immediately. Trying to enchant it in the forge"
          + " might not be prudent at this time.\n");
        return 1;
    }

    write("You insert the " + obj->short() + " into the forge. There is"
      + " a powerful flash of light, and as you draw the weapon back"
      + " out, it appears to have changed!\n");
    tell_room(environment(this_player()), QCTNAME(this_player())
      + " inserts " + LANG_ADDART(obj->short()) + " "
      + " into the strange device. There is a powerful"
      + " flash of light, and the weapon appears to have been transformed"
      + " somehow!\n", this_player());

#if LOG_ACTIVITY
        write_file(LOG_DIR + "forge", 
            TIME2FORMAT(time(), "mm/dd/yyyy")
          + " (" + ctime(time())[11..18] + ") "
          + capitalize(this_player()->query_name())
          + " imbues a dagger.\n");
#endif

    set_alarm(2.0, 0.0, &tell_room(this_object(),
        "The energies surrounding the device fade, and are gone.\n"));

    this_player()->remove_prop(INSERTED_TEARS);
    this_player()->remove_prop(FORGE_FILLED);

    obj->set_imbued(this_player()->query_real_name());
    return 1;
} /* do_insert */


/*
 * Function name:        exa_shelf
 * Description  :        Show players a description of the
 *                       shelf, with state-dependant results.
 * Returns      :        string - the description
 */
public string
exa_shelf()
{
    string   filled = this_player()->query_prop(FORGE_FILLED);
    string   journal_read = this_player()->query_prop(JOURNAL_REAGENT_PROP);

    if (!journal_read)
    {
        return "The shelf appears to hold numerous types of reagents"
          + " which must serve some purpose. You don't have any knowledge"
          + " of such things, however, and therefore aren't able to really"
          + " make much sense of what you see.\n";
    }

    if (!filled)
    {
        return "The shelf appears to hold numerous types of reagents"
          + " which must have been collected by the High Priest for"
          + " various purposes. You notice some " + journal_read + " in"
          + " one jar which you could probably <get> if you wished.\n";
    }

    return "The shelf appears to hold numerous types of reagents which"
      + " must have been collected by the High Priest for various"
      + " purposes. You've already taken what you need, however.\n";
} /* exa_shelf */


/*
 * Function name:        fill_forge
 * Description  :        Allow players to put the correct reagent into
 *                       the forge
 * Arguments    :        string arg - what was typed after the verb
 * Returns      :        int 1 - success, 0 - failure
 */
public int
fill_forge(string arg)
{
    string   filled = this_player()->query_prop(FORGE_FILLED);
    string   journal_read = this_player()->query_prop(JOURNAL_REAGENT_PROP);
    object  *obj;
    string   word;

    if (!this_player()->query_prop(JOURNAL_REAGENT_PROP))
    {
        return 0;
    }

    if (!strlen(arg))
    {
        notify_fail("Fuel what?\n");
        return 0;
    }

    if (!parse_command(arg, all_inventory(this_player()),
        "[the] [enchanter] [enchanters] [enchanter's] [strange] 'device'"
      + " / 'forge' / 'furnace' 'with' [the] %i", obj) ||
        !sizeof(obj = NORMAL_ACCESS(obj, 0, 0)))
    {
        if (parse_command(arg, ({}),
        "[the] [enchanter] [enchanters] [enchanter's] [strange] 'device'"
      + " / 'forge' / 'furnace'"))
        {
            notify_fail("Fuel the " + arg + " with what?\n");
            return 0;
        }

        if (parse_command(arg, ({}),
            "[the] [enchanter] [enchanters] [enchanter's] [strange]"
          + " 'device' / 'forge' / 'furnace' 'with' [the] %w", word))
        {
            if (word == "reagent" || word == "reagents")
            {
                notify_fail("Fuel the forge with which reagent?\n");
                return 0;
            }

            notify_fail(capitalize(word)
              + " ... what " + word + "? You possess no such thing!\n");
            return 0;
        }

        notify_fail("Do you want to <fuel> the forge with something?\n");
        return 0;
    }

    if (!journal_read)
    {
        notify_fail("You have no idea what should be used to fuel the"
          + " forge. Better not to guess. Perhaps if you had read some"
          + " instructions on the subject, you'd be more confident.\n");
        return 0;
    }

    if (!obj[0]->id(journal_read))
    {
        notify_fail("That is not something that works as a fuel for the"
          + " forge, apparently.\n");
        return 0;
    }

    if (filled)
    {
        write("You have already fueled the forge. Now it is time for the"
          + " next step, not more fuel.\n");

        return 1;
    }

    write("You fill the small furnace of the forge with the "
      + obj[0]->short() + ". Almost immediately, strange fumes fill the"
      + " room, and an energy surrounds the forge.\n");

#if LOG_ACTIVITY
        write_file(LOG_DIR + "forge", 
            TIME2FORMAT(time(), "mm/dd/yyyy")
          + " (" + ctime(time())[11..18] + ") "
          + capitalize(this_player()->query_name())
          + " puts the correct fuel in the forge.\n");
#endif

    if (this_player()->query_prop(INSERTED_TEARS) > 7)
    {
        set_alarm(2.0, 0.0, &light_tears(this_player()));
    }

    this_player()->add_prop(FORGE_FILLED, journal_read);
    obj[0]->remove_object();
    return 1;
} /* fill_forge */


/*
 * Function name:        get_reagent
 * Description  :        Allow players to get the correct reagent from the
 *                       High Priest's supplies
 * Arguments    :        string arg - what was typed after the verb
 * Returns      :        int 1 - success, 0 - failure
 */
public int
get_reagent(string arg)
{
    string   filled = this_player()->query_prop(FORGE_FILLED);
    string   journal_read = this_player()->query_prop(JOURNAL_REAGENT_PROP);
    object   obj;

    if (!strlen(arg))
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[the] '" + journal_read + "' [from] [the] [small] [glass]"
      + " [shelf] [jar] [jars]"))
    {
        /* The mudlib can handle <get> fails. */
        return 0;
    }

    if (!journal_read)
    {
        notify_fail("You have no idea what these reagents are or what they"
          + " might be used for. Better not to guess. Perhaps if you had"
          + " read some instructions on the subject, you'd be more"
          + " sure of what to look for.\n");
        return 0;
    }

    if (present(journal_read, this_player()))
    {
        write("You've already taken some.\n");
        return 1;
    }

    if (filled)
    {
        write("You have already fueled the forge. No need to get"
          + " more.\n");

        return 1;
    }

    write("Recognizing it as an important reagent for the forge, you"
      + " take some " + journal_read + " from the shelf.\n");
    tell_room(environment(this_player()), QCTNAME(this_player())
      + " stoops and appears to collect something near to the desk.\n",
        this_player());

    obj = clone_object(OBJ_DIR + "reagent");
    obj->configure_reagent(journal_read);
    if (obj->move(this_player())) 
    {
        write("You can't carry the " + obj->short() + " and drop it instead.\n");
        obj->move(this_object(), 1);
    }

#if LOG_ACTIVITY
        write_file(LOG_DIR + "forge", 
            TIME2FORMAT(time(), "mm/dd/yyyy")
          + " (" + ctime(time())[11..18] + ") "
          + capitalize(this_player()->query_name())
          + " gets some " + journal_read + " from the shelf.\n");
#endif

    return 1;
} /* get_reagent */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(get_reagent, "get");
    add_action(get_reagent, "take");
    add_action(get_reagent, "remove");
    add_action(fill_forge, "fuel");
    add_action(do_insert, "insert");
    add_action(fit_socket, "fit");
} /* init */


/*
 * Function name:        exa_reagents
 * Description  :        Show players a description of the
 *                       shelf, with state-dependant results.
 * Arguments    :        string arg - the item to check for
 * Returns      :        string - the description
 */
public string
exa_reagents(string arg)
{
    string   filled = this_player()->query_prop(FORGE_FILLED);
    string   journal_read = this_player()->query_prop(JOURNAL_REAGENT_PROP);

    if (!journal_read || arg != journal_read)
    {
        return "You find no " + arg + ".\n";
    }

    if (!filled)
    {
        return "You spot some " + arg + " on a shelf beside the desk."
          + " You could probably <get> some if you wished.\n";
    }

    return "There is still some on the shelf, but since you've already"
      + " fueled the forge, there is little need for more.\n";
} /* exa_reagents */


/*
 * Function name:        room_search
 * Description  :        Provide some feedback if a player wants to
 *                       search the room.
 * Arguments    :        mixed obj - the searcher
 *                       string arg - what was typed
 * Returns      :        string - the message for the player
 */
public string
room_search(mixed obj, string arg)
{
    switch(arg)
    {
        case "here":
        case "room":
        case "area":
            return "Searching around, you notice a gem-encrusted tome"
              + " sitting on top of the desk. Next to the desk, you also"
              + " see a small shelf containing some glass jars.\n";
            break;
        case "shelf":
        case "small shelf":
            return "Reagents. Lots of them.\n";
            break;
        case "reagent":
        case "reagents":
            return "Do you have a specific reagent in mind? If so,"
              + " perhaps you could just <get> the one you want.\n";
            break;
        case "device":
        case "forge":
        case "strange device":
        case "enchanter forge":
        case "enchanters forge":
        case "enchanter's forge":
            return "The device does not appear to conceal anything"
              + " from view. Perhaps examining it is all that is"
              + " required to understand its properties.\n";
            break;
        default:
            obj->catch_tell("After a thorough search, you discover"
              + " nothing beyond what your eyes could already tell"
              + " you. " + long());
            return " ";
            break;
    }

    return "Your search reveals nothing special.\n";
} /* room_search */


/*
 * Function name:        exa_furnace
 * Description  :        Show players a description of the enchanters
 *                       forge, with state-dependant results.
 * Returns      :        string - the description
 */
public string
exa_furnace()
{
    string   filled = this_player()->query_prop(FORGE_FILLED);
    string   journal_read = this_player()->query_prop(JOURNAL_REAGENT_PROP);

    if (!journal_read)
    {
        return "You find no furnace.\n";
    }

    if (!filled)
    {
        return "The base of the device appears to be the furnace that"
          + " was described in the tome. You could <fuel> it with"
          + " something, perhaps.\n";
    }

    return "The base of the device appears to be the furnace that was"
      + " described in the tome. It currently simmers with the "
      + filled + " that you placed inside it.\n";
} /* exa_furnace */


/*
 * Function name:        fit_socket
 * Description  :        Allow players to try to fit tears into the
 *                       sockets.
 * Arguments    :        string arg - what was typed after the verb
 * Returns      :        int 1 - success, 0 - failure
 */
public int
fit_socket(string arg)
{
    string   filled = this_player()->query_prop(FORGE_FILLED);
    string   journal_read = this_player()->query_prop(JOURNAL_REAGENT_PROP);
    int      tear_num = this_player()->query_prop(INSERTED_TEARS);
    object  *obj;
    string   word;
    int      new_num;
    int      num_left;

    if (!journal_read)
    {
        return 0;
    }

    if (!strlen(arg))
    {
        notify_fail("Fit what?\n");
        return 0;
    }

    if (!parse_command(arg, all_inventory(this_player()),
        "[the] %i [in] [to] [into] [the] [eight] [tear] [shaped]"
      + " [tear-shaped] 'socket' / 'sockets'", obj) ||
        !sizeof(obj = NORMAL_ACCESS(obj, 0, 0)))
    {
        if (parse_command(arg, ({}),
        "[the] [tear] [shaped] [tear-shaped] 'socket' / 'sockets'"))
        {
            notify_fail("Fit what into the socket?\n");
            return 0;
        }

        if (parse_command(arg, ({}),
        "[the] %w [in] [to] [into] [the] [eight] [tear] [shaped]"
      + " [tear-shaped] 'socket' / 'sockets'", word))
        {
            notify_fail(capitalize(word)
              + " ... what " + word + "? You possess no such thing!\n");
            return 0;
        }

        notify_fail("Fit what into where?\n");
        return 0;
    }

    if (!obj[0]->id(QUEST_TEAR))
    {
        notify_fail("That does not seem to fit into the socket.\n");
        return 0;
    }

    if (tear_num > 7)
    {
        notify_fail("All eight of the sockets are already full"
          + ((filled) ? ", and pulse with the energy of the fueled"
          + " forge." : ".") + "\n");
        return 0;
    }

    new_num = tear_num + 1;

    if (tear_num < 7)
    {
        num_left = 8 - new_num;

        write("You insert a crystalline tear into one of the"
          + " sockets, and it snaps firmly into place. There "
          + ((num_left == 1) ? "is" : "are")
          + " now " + LANG_NUM2WORD(num_left) + " empty "
          + ((num_left == 1) ? "socket" : "sockets")
          + " remaining.\n");
        tell_room(this_object(), QCTNAME(this_player())
          + " fusses with the device.\n", this_player());

        this_player()->add_prop(INSERTED_TEARS, new_num);
        obj[0]->remove_object();

#if LOG_ACTIVITY
        write_file(LOG_DIR + "forge", 
            TIME2FORMAT(time(), "mm/dd/yyyy")
          + " (" + ctime(time())[11..18] + ") "
          + capitalize(this_player()->query_name())
          + " inserts a tear into the forge.\n");
#endif

        return 1;
    }

    write("You insert a crystalline tear into the final socket,"
      + " and it snaps firmly into place.\n");

    if (filled)
    {
        set_alarm(2.0, 0.0, &light_tears(this_player()));
    }

    this_player()->add_prop(INSERTED_TEARS, new_num);
    obj[0]->remove_object();

#if LOG_ACTIVITY
        write_file(LOG_DIR + "forge", 
            TIME2FORMAT(time(), "mm/dd/yyyy")
          + " (" + ctime(time())[11..18] + ") "
          + capitalize(this_player()->query_name())
          + " inserts the final tear.\n");
#endif

    return 1;
} /* fit_socket */


/*
 * Function name:        light_tears
 * Description  :        Create a cool effect when the forge is
 *                       fully activated.
 * Arguments    :        object who - this_player()
 */
public void
light_tears(object who)
{
    if (environment(who) == this_object())
    {
        write("\nThe crystalline tears are suddenly filled with a"
          + " brilliant luminescence!\n\n");
    }

    tell_room(this_object(), "The device suddenly becomes much"
      + " brighter!\n", who);

    return;
} /* light_tears */


/*
 * Function name:        exa_socket
 * Description  :        Show players a description of the
 *                       sockets, with state-dependant results.
 * Arguments    :        arg - what was examined here
 * Returns      :        string - the description
 */
public string
exa_socket(string arg = "socket")
{
    string   filled = this_player()->query_prop(FORGE_FILLED);
    string   journal_read = this_player()->query_prop(JOURNAL_REAGENT_PROP);
    int      num_tears = this_player()->query_prop(INSERTED_TEARS);
    string   desc;

    if (!journal_read)
    {
        return "You stare at a part of the device, but it holds no"
          + " meaning to you.\n";
    }

    if (arg == "tear" && !num_tears)
    {
        return "You find no such thing.\n";
    }

    desc = "There are eight tear-shaped sockets surrounding the"
      + " opening on the forge, ";

    switch (num_tears)
    {
        case 0:
            return desc + "all of which are empty.\n";
            break;
        case 8:
            desc += "all of which have been fit with a crystalline"
              + " tear. ";
            break;
        case 1:
            desc += "one of which has been fit with a crystalline"
              + " tear. ";
            break;
        default:
            desc += LANG_NUM2WORD(num_tears) + " of which have been"
              + " fit with a crystalline tear. ";
            break;
    }

    if (filled && num_tears > 7)
    {
        desc += "A brilliant light fills each of the tears,"
          + " surrounding the forge with illumination.";
    }

    return desc + "\n";
} /* exa_socket */
