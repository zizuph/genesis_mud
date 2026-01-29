/*
 *  /d/Emerald/blackwall/del_rimmon/lakeside/caves/torque_room.c
 *
 *  This, the final destination of the quest for the Crystal Torque
 *  is as it was hundreds of years ago when Maeltar placed the
 *  enchantments upon it. Still keeping its purpose active, even
 *  he remains in magic form to guide the eager adventurer.
 *
 *  Copyright (c) August 2001, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/d/Emerald/blackwall/delrimmon/legacy/del_rimmon_room";
inherit "/d/Emerald/blackwall/delrimmon/visions";

#include <macros.h>
#include <cmdparse.h>
#include <language.h>
#include <stdproperties.h>
#include "/d/Emerald/quest_handler/quest_handler.h"
#include "/d/Emerald/blackwall/delrimmon/defs.h"

/* definitions */
#define GEM_SETTINGS   ({ ("-encrusted"),\
                          ("-laced"),\
                          ("-studded"),\
                          ("-layered"),\
                       })
#define LOCATION_ARRAY ({ \
            ("within the left point of the Star of Telberin"),\
            ("within the right point of the Star of Telberin"),\
            ("within the top point of the Star of Telberin"),\
            ("within the bottom point of the Star of Telberin"),\
            ("just to the left of the center of the emblem"),\
            ("just to the right of the center of the emblem"),\
            ("right above the center of the emblem"),\
            ("right below the center of the emblem"),\
            ("in the upper portion of the circular band"),\
            ("in the lower portion of the circular band"),\
            ("in the left portion of the circular band"),\
            ("in the right portion of the circular band"),\
                        })

/* prototypes */
public void        create_del_rimmon();
public string      exa_crystal();
public string      exa_gemstones();
public int         touch_crystals(string arg);
public void        init();
public void        create_torque(object player, string gem_type);
public void    mktorque(string for_whom, object player, string gem);
public void    wait_for_desc(string for_whom, int tries, object player);
public void        reset_room();
public int         grab_torque(string arg);
public void        evaporate(object player);
public void        cancel_creation();

/* global variables */
public mixed        Trance = 0; /* is a player currently in a trance? */
public int          Creation_In_Process = 0; /* is a torque being made? */
public string       Gem_Type = ""; /* Gem type for the torque creation */

/*
 * Function name:        create_del_rimmon
 * Description  :        set up the room
 */
public void
create_del_rimmon()
{
    set_short("an eerily lit chamber at the top of the tower");
    set_long("In an eerily lit chamber at the top of"
      + " the tower. There are no windows in the walls here, whose"
      + " borders frame this room in a perfect octagon. Shadows from a"
      + " large, pulsing crystal formation, which rests at the center of"
      + " the black floor, dart and flicker along the roof. You"
      + " find your eyes aching slightly in the presence of the"
      + " odd illumination provided by the crystals, which appear"
      + " to be emitting light of many different colors in random"
      + " patterns and levels of brightness.\n");

    add_item( ({ "agate", "agates", "alexandrite",
             "amber", "ambers", "amethyst", "amethysts",
             "aquamarine", "aquamarines", "beryl", "beryls",
             "red beryl", "red beryls", "bloodstone", "bloodstones",
             "carnelian", "carnelians", "chalcedony", "chalcedonies",
             "chrysophrase", "chrysophrases", "coral", "corals",
             "diamond", "diamonds", "emerald", "emeralds",
             "garnet", "garnets", "jade", "jades",
             "jasper", "jaspers", "lapis", "lapises",
             "moonstone", "moonstones", "onyx", "onyxes",
             "opal", "opals", "pearl", "pearls",
             "black pearl", "black pearls", "peridot", "peridots",
             "pyrite", "pyrites", "quartz", "quartzes",
             "ruby", "rubies", "sapphire", "sapphires",
             "spinel", "spinels", "blue spinel", "blue spinels",
             "red spinel", "red spinels", "topaz", "topazes",
             "yellow topaz", "yellow topazes",
             "tourmaline", "tourmalines",
             "pink tourmaline", "pink tourmalines",
             "turquoise", "turquoises", "alexandrites" }),
        exa_gemstones);
    add_item( ({ "crystal", "crystal formation", "crystal structure",
                 "structure", "formation", "crystals", "cluster",
                 "crystal cluster", "cluster of crystals" }),
        exa_crystal);
    add_item( ({ "sky" }),
        "The sky is not visible from here.\n");
    add_item( ({ "here", "chamber", "room", "area" }),
        "This room appears to be at the top of the tower, yet there"
      + " are no windows and so one can only guess at how high up"
      + " it rests.\n");
    add_item( ({ "tower", "crystal tower" }),
        "This room is distinctly unlike any other part of the tower"
      + " that you have seen. The tower itself almost seems"
      + " inconsequential, as if this room could be anywhere in the"
      + " world.\n");
    add_item( ({ "wall", "walls", "border", "borders" }),
        "The walls of this chamber are comprised of the same stone"
      + " which makes up the rest of the tower. It is inky black,"
      + " and smooth as glass, seemingly formed by some magical"
      + " process. The walls form an octagonal perimeter to the"
      + " room, and all seem focused in on the crystal formation"
      + " in the center of the floor. On the north wall, a stunning"
      + " mosaic depicts the emblem of Telberin.\n");
    add_item( ({ "octagon", "perimeter" }),
        "The octagon shape is perfectly rendered in the dimensions"
      + " of this chamber.\n");
    add_item( ({ "shadow", "shadows" }),
        "The flickering and pulsing of light and color which comes from"
      + " the crystal formation causes many shadows to play on the"
      + " walls and ceiling of this room. With the octagonal shape of"
      + " the walls, the effect is kaleidoscopic.\n");
    add_item( ({ "floor", "black floor", "down", "ground" }),
        "The floor is comprised of the same smooth and beguiling"
      + " black material as the walls of this chamber. At the very"
      + " center of the floor, whose borders are drawn in a perfect"
      + " octagon, is a brilliant pulsing crystal formation. At one"
      + " corner of the room, a stairwell leads down out of the"
      + " area.\n");
    add_item( ({ "corner", "stair", "stairwell", "stairway", "steps",
                 "stairs" }),
        "Stairs lead down out of this chamber from a dark opening"
      + " at one corner of the room.\n");
    add_item( ({ "opening", "dark opening" }),
        "It is difficult to see anything other than the stairway"
      + " beyond the dark opening.\n");
    add_item( ({ "north wall", "northern wall", "north" }),
        "The northern wall is inlaid with many thousands of gems"
      + " which form a beautiful mosaic.\n");
    add_item( ({ "northwest", "west", "southwest", "south",
                 "southeast", "east", "northeast",
                 "northwest wall", "west wall", "southwest wall",
                 "south wall", "southeast wall", "east wall",
                 "northeast wall", "northwestern wall",
                 "western wall", "southwestern wall", "southern wall",
                 "southeastern wall", "eastern wall",
                 "northeastern wall" }),
        "The wall is icy black, and smooth as the most flawless"
      + " mirror. It seems clear that only magic could form walls"
      + " of this nature.\n");
    add_item( ({ "roof", "up", "ceiling", "point" }),
        "There is no actual ceiling to this chamber. Rather, the"
      + " eight sides of the chamber all angle slightly, eventually"
      + " meeting above you in a perfect point directly above the"
      + " crystal formation in the floor. The flashes of shifting"
      + " color and bursts of brilliance from the formation play"
      + " out dazzlingly upon these surfaces, creating a"
      + " kaleidoscopic effect within the room.\n");
    add_item( ({ "light", "illumination", "color", "colour",
                 "colours", "colors", "effect" }),
        "The light emitted from the crystal formation is dazzling"
      + " to your senses. At seemingly random intervals, the colors"
      + " in the room shift completely, throwing singular hues"
      + " in one direction or another. The perfectly flat surfaces of"
      + " the eight walls pick up these colors, and reflect them"
      + " as solid bands which dance on all sides of you. The effect"
      + " is beguiling, and you find your eyes growing fuzzy as you"
      + " attempt to focus on the brilliance for too long.\n");
    add_item( ({ "star", "four-pointed star", "four pointed star",
                 "stars", "star of telberin", "stars of telberin" }),
        "The emblem bears a four-pointed star, the traditional symbol"
      + " of the Order of Telan-Ri from the city of Telberin. The"
      + " star is comprised of gemstones of all shapes and sizes set"
      + " into the north wall in a mosaic pattern.\n");
    add_item( ({ "band", "circle", "circular band" }), 
        "The circular band surrounds the four-pointed star, to complete"
      + " the traditional emblem of Telberin. The circle appears to"
      + " be comprised of many gemstones which glitter in the"
      + " unnatural light of this room.\n");
    add_item( ({ "gem", "gems", "gemstone", "gemstones" }),
        "The emblem on the north wall is a mosaic of thousands of"
      + " gemstones which form the shape of the four-pointed star."
      + " You recognize every manner of precious gem within the"
      + " pattern, from diamond, to ruby, to topaz, to aquamarine."
      + " There is a noticable gap in the mosaic at the very"
      + " center of the star, and there, you see a large empty"
      + " socket in the wall.\n");
    add_item( ({ "center of the star", "gap", "gap in the mosaic",
                 "socket", "empty socket", "large socket",
                 "large empty socket", "center" }),
        "The socket is about the size of an acorn. It looks as"
      + " if one of the gems of the mosaic has been removed.\n");
        
    add_cmd_item( ({ "emblem", "symbol", "symbol of telberin",
                     "standard", "standard of telberin", "mosaic" }),
                  ({ "search" }),
        "Going carefully over the pattern in the mosaic, you"
      + " come across a large empty socket at the direct center"
      + " of the Star of Telberin. It looks as though there is"
      + " a gem missing from the mosaic. Perhaps it was removed,"
      + " or the mosaic was intentionally left incomplete.\n");


    add_cmd_item( ({ "crystal", "crystal formation", "crystal structure",
                     "structure", "formation", "crystals", "cluster",
                     "crystal cluster", "cluster of crystals" }),
                  ({ "search" }),
        "You carefully examine every inch of the crystal formation."
      + " The longer you investigate, the less sure you are what"
      + " substances comprise its bulk. The shifting of colors, and"
      + " pulsing of light seems completely random. Suddenly, you"
      + " feel a strange and sudden urge. It is almost as if some"
      + " strange force is coaxing you, attempting to convince you"
      + " to reach out and touch the crystals.\n");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_M_NO_TELEPORT_TO,
        "A strange force somehow prevents your travel.\n");

    add_exit(DELRIMMON_DIR + "lakeside/caves/tower_entry", "down");

    set_no_exit_msg( ({ "north", "northwest", "west", "southwest",
                        "south", "southeast", "east", "northeast" }),
        "You are fenced in by the walls of the chamber.\n");

    FIX_EUID

    reset_room();
} /* create_del_rimmon */

/*
 * Function name:        exa_crystal
 * Description  :        provide a description of the crystal
 *                       formation. if there is a mortal in a trance,
 *                       then also describe this fact
 * Returns      :        string - the add_item description we want
 */
public string
exa_crystal()
{
    string  txt;

    txt = "Set into the floor at the very center of this small chamber,"
        + " a large asymmetrical formation of crystals appears to be"
        + " the only source of light. The crystals themselves are"
        + " varied in shape and color. Some are quartz-like, branching"
        + " in narrow shards like a snowflake. Others are much"
        + " more rounded, clustered together in tight formations"
        + " akin to the innards of a geode. Shifting colors of light"
        + " emanate from the cluster, making it extremely difficult"
        + " to see what actual material comprises the crystal"
        + " structure. At times, you believe you are looking at"
        + " the worlds largest collection of diamonds. At other"
        + " times the structure looks like a wealth of rubies, or"
        + " emeralds. The dazzling display of light is bewitching"
        + " to your senses. ";

    if (Trance)
    {
        txt += Trance->query_the_name(this_player()) + " has both"
            + " hands placed on the crystal formation, and is"
            + " staring blankly ahead into empty space.";
    }

    if (Creation_In_Process)
    {
        txt += "The cluster is glowing with great brilliance at the"
             + " moment, and a deep throbbing hum emanates from it.";
    }

    return txt + "\n";
} /* exa_crystal */


/*
 * Function name:        exa_gemstones
 * Description  :        allow the player to see a particular
 *                       gemstone present in the mosaic
 * Returns      :        string - a description for the add_item
 */
public string
exa_gemstones()
{
    string  where = ONE_OF_LIST(LOCATION_ARRAY);

    return "Running your eyes across the mosaic, you soon notice"
         + " the unmistakable " + Exa_arg + " nestled "
         + where + ".\n";
} /* exa_gemstones */


/*
 * Function name:        touch_crystals
 * Description  :        allow the player to touch the crystals
 * Arguments    :        string arg - what the player typed
 * Returns      :        int 1 - success, 0 - failure
 */
public int
touch_crystals(string arg)
{
    object       Torque;

    if (!strlen(arg))
    {
        NFN0(query_verb() + " what?");
    }

    if (!parse_command(arg, ({}),
        "[the] [a] [large] [pulsing] 'crystal' / 'crystals'"
      + " / 'formation' / 'cluster' [formation] [of] [crystals]"))
    {
        return 0;
    }

    if (Trance)
    {
        write("You move to touch the crystals, and are stopped by a"
            + " strange magical force. You notice that "
            + Trance->query_the_name(this_player()) + " has both hands"
            + " on the crystal formation, and is staring forward with"
            + " a blank look on " + Trance->query_possessive()
            + " face as if " + Trance->query_pronoun() + " is in a"
            + " trance.\n");
        return 1;
    }

    if (Creation_In_Process)
    {
        write("You do not dare to touch the crystal cluster at this"
            + " time. There is an unnatural glow, and a deep hum"
            + " emanating from the formation. Something very strange"
            + " is taking place.\n");
        return 1;
    }

    if (Torque = present("ctower_torque", this_player()))
    {
        if (Torque->query_bound() == this_player()->query_real_name())
        {
            enter_trance(TP, BOUND_VISION, "crystal formation");
            return 1;
        }

        enter_trance(TP, UNBOUND_VISION, "crystal formation");
    }
    else
    {
        enter_trance(TP, VISION_TEST, "crystal formation");
    }

    return 1;
} /* touch_crystals */


/*
 * Function name:        trance_toggle
 * Description  :        set the value of Trance according to whether
 *                       there is a player having a vision
 * Arguments    :        int player - the player having a trance or 0
 */
public void
trance_toggle(int player)
{
    if (player)
    {
        Trance = player;
        return;
    }

    Trance = 0;
} /* trance_toggle */


/*
 * Function name:        place_gem
 * Description  :        allow the player to set a gem into the
 *                       emblem of Telberin
 * Arguments    :        string arg - what the player typed
 * Returns      :        1 - success, 0 - failure
 */
public int
place_gem(string arg)
{
    mixed   fail;
    mixed  *obj;
    object  gem;
    int num;

    if (!strlen(arg))
    {
        NFN(CAP(QVB) + " what?");
        return 0;
    }

    if (!(parse_command(arg, all_inventory(this_player()),
        "[the] %i 'in' / 'into' [the] 'socket' / 'emblem' / 'symbol'"
      + " / 'mosaic' / 'star' / 'gap' [of] [telberin]", obj)) ||
        !sizeof(obj = NORMAL_ACCESS(obj, 0, 0)))
    {
        return 0;  /* can't parse the player syntax */
    }

    if (Creation_In_Process)
    {
        write("Though the socket remains empty, it appears as if"
            + " someone has already triggered the properties of the"
            + " emblem, and set its process in motion. Some strange"
            + " force prevents you from doing that right now.\n");
        return 1;
    }

    if (sizeof(obj) > 1)
    {
        // Inidicated more than one item....
        return 0;
    }

    if (!obj[0]->query_gem())
    {
        write("You are unable to insert that item into the"
            + " socket.\n");
        return 1;
    }

    gem = obj[0];

    if (gem->num_heap() > 1)
    {
        write("Only one " + gem->singular_short() + " will fit.\n");
        return 1;
    }

    if (fail = gem->query_prop(OBJ_M_NO_DROP))
    {
        if (!stringp(fail))
        {
            fail = "You cannot get rid of " + LANG_THESHORT(gem) + ".\n";
        }

        notify_fail(fail);
        return 0;
    }

    if (present("ctower_torque", this_player()))
    {
        write("A strange voice enters your head suddenly: You already"
          + " possess the Torque. Seek not another!\n");
        return 1;
    }

    if (!QH_QUERY_QUEST_COMPLETED(this_player(), "torque_portal"))
    {
        write("A commanding voice echoes suddenly in your head, saying:"
          + " None shall have the torque who have not proven themselves"
          + " worthy!\n"
          + "Your muscles seize, and your hand stops just short of"
          + " placing the gem into the mosaic.\n");

        return 1;
    }

    if (QH_QUERY_QUEST_COMPLETED(this_player(), "torque_destroy"))
    {
        write("You place your gem into the socket, and hold it in"
          + " place for a moment. Nothing seems to be happening, so"
          + " you try a few more times, with no better luck.\n");
        return 1;
    }

    write("You carefully set " + LANG_THESHORT(gem) + " into the"
        + " socket within the emblem. It snaps firmly into place.\n");

    set_alarm(6.0, 0.0, &create_torque(this_player(), gem->query_name()));

    gem->restore_heap();
    if ((num = gem->num_heap()) <= 1)
    {
        gem->remove_object();
    }
    else
    {
        gem->set_heap_size(num - 1);
    }

    return 1;
} /* place_gem */


/*
 * Function name:        create_torque
 * Description  :        create a torque, and give it to the player
 * Arguments    :        object player - the player object
 */
public void
create_torque(object player, string gem_type)
{
    if (environment(player) != this_object())
    {
        /* the player left, cancel the process */
        return;
    }

    player->catch_msg("With a sudden flash, your " + gem_type
      + " is absorbed into the emblem, and disappears. A great"
      + " humming sound begins to emanate from the crystal formation,"
      + " which has begun to glow fiercely.\n");
    tell_room(this_object(),
        "The emblem in the north wall flashes suddenly, and a deep"
      + " humming sound rises from the crystal formation in the"
      + " center of the room, which has begun to glow fiercely.\n",
         player);

    Creation_In_Process = 1;
    set_alarm(6.0, 0.0, &mktorque(player->query_real_name(),
              player, gem_type));
} /* create_torque */


/*
 * Function name:        mktorque
 * Description  :        the first of two functions responsible for
 *                       creating the crystal torque, assigning it
 *                       a description, and giving it to the player
 * Arguments    :        string for_whom - the name of the player
 *                       object player   - the player object
 *                       string gem      - the gem type
 */
public void mktorque(string for_whom, object player, string gem)
{
    string gem_pattern = gem + ONE_OF_LIST(GEM_SETTINGS);
    for_whom = lower_case(for_whom);

    if (environment(player) != this_object())
    {
        /* the player left, cancel the process */
        cancel_creation();
        return;
    }

    setuid();
    seteuid(getuid());

    CTOWER_TORQUE_MANAGER->mkdesc("$GENERAL "
      + gem_pattern + " $METAL", for_whom);

    // Generating a description can take some time, so we'll wait until it's
    // finished before giving out the torque
    set_alarm(6.0, 0.0, &wait_for_desc(for_whom, 1, player));

    tell_room(this_object(), "As you watch, a tiny shard of " 
      + gem + " separates from the main cluster, and rises into the"
      + " air where it is slowly transformed into a thin circular"
      + " shape.\n");
} /* mktorque */


/*
 * Function name:        wait_for_desc
 * Description  :        the second of two functions responsible for
 *                       creating the crystal torque, assigning it
 *                       a description, and giving it to the player.
 * Arguments    :        string for_whom - the player name
 *                       int    tries    - number of tries to name
 *                       object player   - the player object
 */
public void wait_for_desc(string for_whom, int tries, object player)
{
    if (environment(player) != this_object())
    {
        /* the player left, cancel the process */
        cancel_creation();
        return;
    }

    if (CTOWER_TORQUE_MANAGER->get_torque_desc(for_whom))
    {
        object torque = clone_object(TORQUE_DIR + "torque");
        torque->config_torque(for_whom);
        MANAGER->assign_spell(for_whom);
        torque->set_command_word(MANAGER->query_spell(for_whom));
        torque->move(find_player(for_whom), 1);

        player->catch_msg("There is another intense flash of magic,"
          + " and you see that the transformation is complete. The"
          + " shard has become a jeweled torque headpiece of great"
          + " beauty. You reach out and take it.\n");
        tell_room(this_object(), "There is another intense flash"
          + " of magic, and you see that the transformation is"
          + " complete - the shard is now a jeweled torque headpiece"
          + " of great beauty. " + QCTNAME(player) + " reaches out"
          + " and takes it.\n", player);
        
        Creation_In_Process = 0;

        set_alarm(2.0, 0.0, &evaporate(player));

        return;
    }

    if (tries > 5)
    {
        tell_room(this_object(), "The tower begins to rumble, and you"
          + " sense that a minor earthquake is taking place! As you"
          + " brace yourself, you notice that the shard is disturbed"
          + " in the process of its transformation, and falls to the"
          + " ground where it shatters into tiny fragments.\n");

        Creation_In_Process = 0;

        // Maybe an error generating the description....  Just give up.
        return;
    }

    set_alarm(6.0, 0.0, &wait_for_desc(for_whom, ++tries));

    tell_room(this_object(), "Bright lights swirl around the circular"
      + " shape, as it continues to undergo its transformation.\n");
} /* wait_for_desc */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(grab_torque, "get");
    add_action(touch_crystals, "touch");
    add_action(place_gem, "set");
    add_action(place_gem, "insert");
    add_action(place_gem, "fit");
    add_action(place_gem, "put");
    add_action(place_gem, "place");
    add_action(place_gem, "push");
} /* init */


/*
 * Function name:        reset_room
 * Description  :        clone the emblem into the room
 */
public void
reset_room()
{
    object  emblem;

    if (!present("torque_quest_emblem"))
    {
        emblem = clone_object(DELRIMMON_DIR + "obj/torque_emblem");
        emblem->set_location(1);
        emblem->move(this_object());
    }
} /* reset_room */


/*
 * Function name:        grab_torque
 * Description  :        allow players to try to grab the torque
 * Arguements   :        string arg - what the player typed
 * Returns      :        1 - success, 0 - failure
 */
public int
grab_torque(string arg)
{
    if (!strlen(arg))
    {
        return 0; /* pass it to the mudlib */
    }

    if (!parse_command(arg, ({}),
        "[the] [circular] [tiny] 'shard' / 'shape' / 'torque'"))
    {
        return 0; /* bad syntax */
    }

    if (!Creation_In_Process)
    {
        return 0;
    }

    write("You reach out to take the shard, but a strange force"
      + " stops your hand just short of touching it.\n");

    return 1;
} /* grab_torque */


/*
 * Function name:        evaporate
 * Description  :        once the player has the torque, the stone
 *                       tablets become irrelevant, and should be
 *                       removed from the player's inventory
 */
public void
evaporate(object player)
{
    object fragment;
    int frags = 0;

    if (QH_QUEST_COMPLETED(player, "torque_acquisition"))
    {
        player->catch_tell("\nYou feel more experienced!\n\n");
    }

    while (fragment = present("_del_rimmon_tablet_left", player))
    {
        fragment->remove_object();
        frags++;
    }

    while (fragment = present("_del_rimmon_tablet_right", player))
    {
        fragment->remove_object();
        frags++;
    }

    if (frags > 1)
    {
        write("The stone fragments evaporate into mist, and"
            + " disappear!\n");
    }
    else if (frags == 1)
    {
        write("The stone fragment evaporates into mist, and"
            + " disappears!\n");
    }

    return;
} /* evaporate */


/*
 * Function name:        cancel_creation
 * Description  :        if the player has left the room, we do not
 *                       want to continue with the torque creation,
 *                       so we simply end it. Tough luck for the 
 *                       player if they didn't have extra gems.
 */
public void
cancel_creation()
{
    tell_room(this_object(),
        "There is a sudden pulse of blinding light, immediately followed"
      + " by a drain in the energy in the room. Within seconds, the"
      + " glow of the crystal cluster has returned to normal.\n");

    Creation_In_Process = 0;
    return;
} /* cancel_creation */
