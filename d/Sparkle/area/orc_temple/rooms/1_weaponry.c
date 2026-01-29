/*
 *  /d/Sparkle/area/orc_temple/1_weaponry.c
 *
 *  This is an important quest room in the orc dungeons. This is the
 *  weapon storage chamber for the orcs of the temple.
 *
 *  Created August 2010, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

#include <macros.h>   /* for QCTNAME */
#include <time.h>
#include "../defs.h"
#include "/d/Sparkle/sys/quests.h"

inherit ROOMS_DIR + "dungeon_room";


/* Global Variables */
public string      *Locations = ({ "shelves",
                                   "stands",
                                   "racks",
                                   "barrels",
                                   "bins",
                                   "cabinets" });
public string      *Junk = ({
                                   "goo",
                                   "hideous goo",
                                   "poo",
                                   "poop",
                                   "bits",
                                   "metal",
                                   "bits of metal",
                                   "old metal",
                                   "rusted metal",
                                   "old and rusted metal",
                                   "bits of old metal",
                                   "bits of rusted metal",
                                   "bits of old and rusted metal",
                                   "blade",
                                   "blades",
                                   "mess",
                                   "corroded mess",
                                   "horrible mess",
                                   "horrible corroded mess",
                                   "bone",
                                   "bones",
                                   "old bone",
                                   "old bones",
                                   "broken weapon",
                                   "broken weapons",
                                   "weapon",
                                   "weapons",
                                   "skeleton",
                                   "skeletons",
                                   "hobbit",
                                   "hobbits",
                                   "hobbit skeleton",
                                   "hobbit skeletons",
                                   "tar",
                                   "black tar",
                                   "filthy tar",
                                   "filthy black tar",
                                   "ash",
                                   "ashes",
                                   "pile of ash",
                                   "pile of ashes",
                                   "piles of ash",
                                   "piles of ashes",
                                   "spear",
                                   "spears",
                                   "broken spear",
                                   "broken spears",
                                   "filthy spear",
                                   "filthy spears",
                                   "broken and filthy spear",
                                   "broken and filthy spears",
                                        });

public mixed        Searcher = 0; /* Anyone searching the room for stuff. */


/* Prototypes */
public void         create_dungeon_room();
public void         leave_inv(object ob, object dest);
public int          stop_delay_cmd(mixed arg);
public mixed        begin_weapon_search(string where);
public string       end_weapon_search(string where);
public string       search_hint(object who, string where, string *searched);
public int          get_stuff(string arg);
public void         init();
public string       do_search(object pl, string str);
public string       junk_reaction();

/* Definitions */
#define             SEARCHED_FOR    "_orc_temple_weaponry_search"


/*
 * Function name:        create_dungeon_room
 * Description  :        constructor for the room
 */
public void
create_dungeon_room()
{
    set_short("a round room filled with weapon storage");
    set_long("You have entered what appears to be a room used to"
      + " store weaponry. The round walls of this chamber are lined"
      + " with various locations for such storage, though most of what"
      + " you see leaves much to be desired.\n\n");

    add_item( ({ "location", "locations", "container",
                 "containers", "storage", "various locations",
                 "such storage", "weapon storage" }),
        "The room is crowded with all sorts of containers. You see"
      + " shelves along one bit of the wall. A few bins are set up"
      + " against some weapon racks, and there are a number of"
      + " barrels lined beside some stands. A few cabinets are"
      + " placed here and there, too.\n");
    add_item( ({ "round wall", "round walls" }),
        "The chamber is round and rather large.\n");
    add_item( ({ "chamber", "room" }),
        "Look around, you can't miss it.\n");
    add_item( ({ "weapon", "weapons", "weaponry" }),
        "Nothing is in plain view. You'd probably need to search"
      + " a bit through what is here to find anything.\n");
    add_item( ({ "cabinet", "cabinets", "weapon cabinet",
                 "weapon cabinets", "shelf", "shelves",
                 "weapon shelf", "weapon shelves", "bin", "bins",
                 "weapon bin", "weapon bins", "rack", "racks",
                 "weapon rack", "weapon racks", "barrel", "barrels",
                 "weapon barrel", "weapon barrels", "stand", "stands",
                 "weapon stand", "weapon stands" }),
        "From outward appearances, they are very poorly maintained"
      + " and absolutely NEVER cleaned. Hard to tell what searching"
      + " through them might turn up.\n");
    add_item(Junk, junk_reaction);

    add_delay_cmd_item( ({ "stand", "stands", "weapon stand",
                           "weapon stands" }),
                       "search",
                       "searching the weapon stands",
                       10,
                       &begin_weapon_search("stands"),
                       &end_weapon_search("stands"));

    add_delay_cmd_item( ({ "rack", "racks", "weapon rack",
                           "weapon racks" }),
                       "search",
                       "searching the weapon racks",
                       10,
                       &begin_weapon_search("racks"),
                       &end_weapon_search("racks"));

    add_delay_cmd_item( ({ "shelf", "shelves", "weapon shelf",
                           "weapon shelves" }),
                       "search",
                       "searching the weapon shelves",
                       10,
                       &begin_weapon_search("shelves"),
                       &end_weapon_search("shelves"));

    add_delay_cmd_item( ({ "barrel", "barrels", "weapon barrel",
                           "weapon barrels" }),
                       "search",
                       "searching the weapon barrels",
                       10,
                       &begin_weapon_search("barrels"),
                       &end_weapon_search("barrels"));

    add_delay_cmd_item( ({ "bin", "bins", "weapon bin",
                           "weapon bins" }),
                       "search",
                       "searching the weapon bins",
                       10,
                       &begin_weapon_search("bins"),
                       &end_weapon_search("bins"));

    add_delay_cmd_item( ({ "cabinet", "cabinets", "weapon cabinet",
                           "weapon cabinets" }),
                       "search",
                       "searching the weapon cabinets",
                       10,
                       &begin_weapon_search("cabinets"),
                       &end_weapon_search("cabinets"));

    add_dungeon_items();

    add_prop(OBJ_S_SEARCH_FUN, "do_search");
    remove_prop(DOOR_BLOCK_ROOM); /* don't want to create deathtraps */

    add_npc(NPC_DIR + "tough_runt", 3 + (random(2)), &->arm_me());

    set_no_exit_msg( ({ "north", "northeast", "southeast", "south",
                        "southwest", "west", "northwest" }),
        "You boldly stroll directly into a wall. OOOF!\n");

    room_add_object(DOORS_DIR + "1_weapon_w");

    setuid();
    seteuid(getuid());
} /* create_dungeon_room */


/*
 * Function name:       leave_inv
 * Description  :       catch any cupboard searchers leaving. They can't
 *                      do it on their own, but they might be trans'd
 * Arguments    :       object ob -- the departing object
 *                      object dest -- its destination
 */
public void
leave_inv(object ob, object dest)
{
    if (Searcher == ob)
    {
        Searcher = 0;
    }

    ::leave_inv(ob, dest);
} /* leave_inv */


/*
 * Function name:       stop_delay_cmd
 * Description  :       mask parent so that if player does "stop",
 *                      we clear Searcher
 * Arguments    :       mixed arg -- if string, player did "stop"
 *                                -- if object, time ran out or
 *                                    called from leave_inv().
 * Returns      :       0 -- stop is always allowed
 */
public int
stop_delay_cmd(mixed arg)
{
    object      tp;

    if (!objectp(arg))
    {
        /* called from paralyze object when player did "stop" */
        tp = environment(previous_object());
        if (tp == Searcher)
        {
            Searcher = 0;
        }
    }
    return ::stop_delay_cmd(arg);
} /* stop_delay_cmd */


/*
 * Function name:        begin_weapon_search
 * Description  :        Provides a slightly different message when a
 *                       player begins searching the various
 *                       locations available, based on
 *                       whether they have already done so.
 * Arguments    :        string where - the location they are searching
 * Returns      :        mixed: integer -- 0 if command fails,
 *                           or string  -- the "You begin ..." message
 */
public mixed
begin_weapon_search(string where)
{
    if (!Searcher)
    {
        Searcher = this_player();
        say(QCTNAME(Searcher) + " begins searching through the"
          + " weapon " + where + ".\n");

        if (IN_ARRAY(where, this_player()->query_prop(SEARCHED_FOR)))
        {
            return "You start searching through the weapon "
              +  where + " again,"
              + " determined to find something useful.\n";
        }

        return "You start searching through the weapon " + where + ".\n";
    }

    write(Searcher->query_The_name(this_player()) + " is already doing"
      + " that, and is in your way."
      + " You'll have to wait until " + Searcher->query_pronoun()
      + " is finished.\n");
    return 1;
} /* begin_weapon_search */


/*
 * Function name:        end_weapon_search
 * Description  :        Provides the result of having searched the
 *                       weapon.
 * Arguments    :        string where - the location being searched
 * Returns      :        string - message for the player
 */
public string
end_weapon_search(string where)
{
    string    searcher_msg;
    string    other_msg = QCTNAME(Searcher);
    object    c_item;
    string   *searched = this_player()->query_prop(SEARCHED_FOR);
    int       group = ORCTEMPLE_GHOST_GROUP,
              bit =   ORCTEMPLE_GHOST_BIT;
    string   *details = ({
                  "are filled with nothing but broken and filthy"
                + " spears. Totally useless.",
                  "appear to have actually been used as a toilet!",
                  "contain little more than bits of old and rusted"
                + " metal.",
                  "stink of blood and rotting flesh. Peering in, you"
                + " see that the blades on a number of weapons here"
                + " have been left uncleaned after battle, and the"
                + " gore has turned the entire stash into a horrible"
                + " corroded mess.",
                  "are full of old bones, some which still have meat"
                + " on them that has dried and turned black.",
                  "are cluttered with a lot of broken weapons. None"
                + " of them look worth a first glance, let alone"
                + " a second.",
                  "are filled with some hideous goo!",
                  "are crowded with what appear to be the skeletons"
                + " of a number of hobbits.",
                  "are full of filthy black tar.",
                  "contain nothing but piles of ashes.",
                      });
    object  guard = present(ORC_TEMPLE_NPC, this_object());

    if (guard)
    {
        if (Searcher->check_seen(guard))
        {
            tell_room(this_object(), "The " + guard->short() + " notices"
              + " what " + QTNAME(Searcher) + " is doing and shoves "
              + Searcher->query_objective() + " roughly aside!\n",
                Searcher);
            Searcher = 0;
            return "The " + guard->short() + " notices what you are"
              + " doing and shoves you roughly aside!\n";
        }

        write("Hee hee! Looks like the guard didn't notice you!\n\n");
    }
          
    /* The player has already solved the Enchanter's Saga. */
    if  (this_player()->test_bit("Sparkle", group, bit))
    {
        searcher_msg = "Been here. Done that.";
        other_msg += " finishes the search, which looks to have"
                  + " amounted to nothing new.";
    }
    /* The player is not doing this quest, so we don't actually
     * give them anything other than a hint that they should start
     * the quest first.
     */
    else if (!this_player()->query_prop(ORC_TEMPLE_QUEST_PROP))
    {
        searcher_msg = "Your search doesn't show you anything"
          + " particularly interesting. However, you aren't on"
          + " a quest here right now. Perhaps if you were you'd"
          + " know what to look for.";
        other_msg += " finishes the search, but doesn't seem to"
          + " have known what to look for.";
    }
    /* The player has already searched here, but tries again anyway */
    else if (IN_ARRAY(where, searched))
    {
        searcher_msg = "Aaaaaand ... nothing has changed. You don't see"
                  + " anything useful here at all. "
                  + search_hint(this_player(), where, searched);
        other_msg += " finishes searching the weapon " + where
                  + " again, apparently not"
                  + " finding anything of value this time either.";
    }
    /* The player hasn't searched here yet, but hasn't yet searched
     * all three possible locations.
     */
    else if (sizeof(searched) < (sizeof(Locations) - 1))
    {
        if (searched)
        {
            searched += ({ where });
        }
        else
        {
            searched = ({ where });
        }

        this_player()->add_prop(SEARCHED_FOR, searched);

        searcher_msg = "The " + where + " "
                 + one_of_list(details) + " "
                 + search_hint(this_player(), where, searched);
        other_msg += " finishes searching the weapon " + where
                  + ", apparently not"
                  + " finding anything of value.";

    }
    /* Ah ... the player finally searches the third location for the
     * first time. Here, we give them the quest object.
     */
    else
    {
        c_item = clone_object(WEP_DIR + "quest_weapon");

        searcher_msg = "After digging for a short while through the"
          + " weapon " + where + ", you notice a "
          + c_item->short() + " amidst the clutter. You quickly"
          + " grab it!";
        other_msg += " pulls a " + c_item->short() + " from the"
          + " confines of the weapon " + where + "!";

#if LOG_ACTIVITY
        write_file(LOG_DIR + "dagger", 
            TIME2FORMAT(time(), "mm/dd/yyyy")
          + " (" + ctime(time())[11..18] + ") "
          + capitalize(this_player()->query_name())
          + " finds a nullstone dagger.\n");
#endif
    
        if (c_item->move(Searcher))
        {
            searcher_msg += " Oops! You dropped it!";
            other_msg += " Oops! " + capitalize(Searcher->query_pronoun())
              + " dropped it!";
            c_item->move(this_object());
        }

        if (searched)
        {
            searched += ({ where });
        }
        else
        {
            searched = ({ where });
        }

        this_player()->add_prop(SEARCHED_FOR, searched);
    }

    tell_room(this_object(), other_msg + "\n", Searcher);
    Searcher = 0;
    return searcher_msg + "\n";
} /* end_weapon_search */


/*
 * Function name:        search_hint
 * Description  :        Give the searching player a hint about what
 *                       they might want to try instead.
 * Arguments    :        object who   - the player
 *                       string where - where they are currently searching
 *                       string *searched - array of locations the
 *                                          player has already searched
 * Returns      :        string - the hint.
 */
public string
search_hint(object who, string where, string *searched)
{
    string *hint_location = Locations;

    /* What we want to do here is suggest one of the places that the
     * player has not yet searched. As they search more places, the
     * number of things that might be decreases.
     */
    foreach (string place: searched)
    {
        hint_location -= ({ place });
    }

    if (!sizeof(hint_location))
    {
        return "You've pretty much found everything you can here, it"
          + " would seem.";
    }

    return "Maybe try the " + one_of_list(hint_location) + " instead?";
} /* search_hint */


/*
 * Function name:        get_stuff
 * Description  :        allow the player to try to get things that
 *                       are mentioned in the various containers.
 * Arguments    :        string arg - what the player typed
 * Returns      :        int 1 - success, 0 - failure
 */
public int
get_stuff(string arg)
{
    string  txt;
    string *names = Junk;
    string *containers = ({
        "stand", 
        "stands", 
        "rack",
        "racks",
        "shelf",
        "shelves",
        "bin",
        "bins",
        "barrel",
        "barrels",
        "cabinet",
        "cabinets"
                         });

    if (!strlen(arg))
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
        "%p [from] [the] [weapon] %p", names, containers))
    {
        return 0; /* can't process player's syntax choice */
    }

    notify_fail("The " + names[0] + " might just as well be left in the "
      + containers[0] + ". If you want to search around you might"
      + " find something worth taking, though. One never knows!\n");
    return 0;
} /* get_stuff */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(get_stuff, "get");
    add_action(get_stuff, "take");
    add_action(get_stuff, "steal");
} /* init */


/*
 * Function name:        do_search
 * Description  :        Provide a room-specific result for the
 *                       basic <search> command
 * Arguments    :        object pl - the player
 *                       string arg - what was typed
 * Returns      :        string - the result message.
 */
public string
do_search(object pl, string str)
{
    return "Looking around, you don't find much of anything just out"
      + " in plain view. There are quite a number of locations here"
      + " you might try searching a bit more specifically.\n";
} /* do_search */


/*
 * Function name:        junk_reaction
 * Description  :        provide a randomized description for the
 *                       various junk one can find in the room.
 * Returns      :        string - the description 
 */
public string
junk_reaction()
{
    return one_of_list( ({
        "What a terrible use of perfectly good storage space!",
        "Whoever is responsible for this room should be fired.",
        "Ugh! Why is this junk in here?",
        "What the ... who would put this here?",
        "Clearly, someone is not doing their daily chores around here.",
        "Is this really ... oh, for heaven's sake! Who would do this?",
        "Blech!!",
        "Yuck.",
        "Disturbing!",
        "Disgusting!",
        "Revolting!",
        "Not too surprising, considering orcs maintain this area.",
            }) ) + "\n";
} /* junk_reaction */
