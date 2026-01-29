/*
 *  /d/Emerald/common/guild/aod/rooms/start.c
 *
 *  This is the start room for the Army of Darkness.
 *
 *  Created July 2006, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"
#include "/d/Emerald/sys/paths.h"
#include <language.h>

inherit AOD_ROOM_DIR + "cave_room";
inherit AOD_LIB_DIR + "add_spike";

/* definitions */
#define            FALL_LOCATION (AOD_ROOM_DIR + "glow_wep_drop")

/* prototypes */
public void        create_cave_room();
public int         start(string str);
public int         try_sleep(string arg);
public void        init();
public void        enter_inv(object ob, object from);
public void        begin_slide(object ob, object from);
public void        fall_droproom(object ob, object from);


/*
 * Function name:        create_cave_room
 * Description  :        set up the room
 */
public void
create_cave_room()
{
    set_short("the barracks for the Army of Darkness");
    set_em_long("You stand beside a"
      + " gigantic natural ravine in the mountain. A wide ledge"
      + " traces the dropoff, running southeast and south against"
      + " steep walls of rock to the north and east which are"
      + " riddled with many ogre-sized holes. This area seems to be"
      + " functioning as a barracks of sorts for the Army. Things that"
      + " only an Ogre could love are strewn about the area - personal"
      + " effects that have been left at the bedside. But beds are"
      + " nowhere to be seen! Rather, this ledge seems"
      + " to be getting bigger every day as new Ogres arrive and want"
      + " a place to sleep. To stake your territory, simply <kick wall>"
      + " and you will start here from now on. You notice that the"
      + " ledge is sloped slightly. It is likely that anything you"
      + " dropped here would roll off the ledge and fall into the"
      + " depths. Speaking of which ... you notice a crude stair"
      + " leading down into the ravine.\n");

    add_item( ({ "up", "sky", "ceiling", "roof" }),
        "Having been naturally formed, the ravine has no ceiling"
      + " other than the sky, high above, which peeks between the"
      + " distant heights of the ravine walls.\n");
    add_item( ({ "wall", "walls", "ravine walls", "ravine wall" }),
        "The ravine walls are jagged and dark, having been formed"
      + " by natural processes. Here along the ledge of the cliff,"
      + " huge holes have been kicked into them where ogres have"
      + " decided to make a napping area for themselves.\n");
    add_item( ({ "stair", "stairs", "stairway" }),
        "Well ... I suppose you could say they are stairs. They are"
      + " really just massive gouges which have been ripped out of"
      + " the cliff in such a way as to allow someone to stumble"
      + " without (probably) killing themselves down into the"
      + " ravine.\n");
    add_item( ({ "gouge", "gouges", "massive gouge",
                 "massive gouges" }),
        "Totally massive, and rather gouge-like.\n");
    add_item( ({ "cloud", "cloud of energy", "cloud of strange energy",
                 "cloud of purple energy",
                 "cloud of strange purple energy" }),
        "Whoa ...\n");
    add_item( ({ "ravine", "depth", "depths", "droproom" }),
        "Down there is the droproom of the Army - quite literally!"
      + " Anything dropped in this room rolls off the ledge, passing"
      + " through a cloud of strange purple energy (probably"
      + " Darkling magic.) The magic sorts it all properly"
      + " so that it lands in a way that is useful to the Army."
      + " Truly an ogre-inspired system!\n");
    add_item( ({ "slope", "ledge", "floor", "ground", "down" }),
        "The ledge is sloped rather dramatically. Ogres are a"
      + " sure-footed bunch, of course, meaning that it is not a"
      + " danger to them. However, it would probably mean that"
      + " anything you dropped here would end up sliding off the"
      + " ledge into the ravine. Hmmm ... you notice some strange"
      + " purple energy just beneath the ledge, now that you are"
      + " taking the time to look.\n");
    add_item( ({ "purple energy", "strange energy", "energy",
                 "strange purple energy" }),
        "Clearly, there is Darkling magic at work here. Perhaps they"
      + " have engineered this process to create a tidy droproom"
      + " for the Army. Anything that falls off the ledge would"
      + " probably pass through that energy. It is always hard to"
      + " understand the precise mechanics of magic, of course.\n");
    add_item( ({ "magic", "darkling magic" }),
        "Yeah ... PURPLE magic!\n");
    add_item( ({ "purple magic" }),
        "I bet you wish YOU could do purple magic.\n");
    add_item( ({ "barracks", "here", "area" }),
        "This is the Barracks for the Army of Darkness guild. Clearly,"
      + " this place is the home of Ogres.\n");
    add_item( ({ "things", "things that only an ogre could love",
                 "things only an ogre could love", "effects",
                 "effect", "personal effect", "personal effects" }),
        "Scattered about the area you see an odd assortment of personal"
      + " effects - a partially eaten horse here, the broken body of a"
      + " Knight of Solamnia there.\n");
    add_item( ({ "horse", "partially eaten horse", "dead horse",
                 "horse corpse" }),
        "This horse has seen better days. He is missing his head, his"
      + " butt, and most of his legs. Apparently, whichever Ogre has"
      + " been munching on him likes to eat around the center first.\n");
    add_item( ({ "broken body", "body", "knight", "solamnic knight",
                 "knight of solamnia", "broken body of a knight",
                 "body of a knight", "body of a knight of solamina",
                 "broken body of a knight of solamnia" }),
        "The antique platemail of the Knights of Solamina which this"
      + " dead fellow wears has been warped and bent with the body,"
      + " which appears to have been tied in the shape of a pretzel!"
      + " You notice a necklace of some kind in the next hole in"
      + " the wall.\n");
    add_item( ({ "necklace", "brooch", "brooches", "ranger brooch",
                 "ranger brooches", "necklace of ranger brooches" }),
        "Some creative Ogre has strung together twenty or more bloody"
      + " Ranger brooches into a necklace. How cute! You notice a"
      + " chain-wrapped lump in the next hole in the wall.\n");
    add_item( ({ "chain", "chains", "lump", "chain-wrapped lump",
                 "scop member", "scop", "spirit circle cleric",
                 "cleric", "presence", "mandala",
                 "sacred black and gold mandala" }),
        "These chains have been wrapped around some sort of Cleric,"
      + " it seems. Though dead, there is an odd 'presence' to the"
      + " guy. Also, he has a sacred black and gold mandala shoved"
      + " up his nose. In the next hole in the wall, you notice"
      + " a game of tic-tac-toe.\n");
    add_item( ({ "game", "tic tac toe", "tic-tac-toe",
                 "game of tic tac toe", "game of tic-tac-toe",
                 "tic-tac-toe game", "tic tac toe game",
                 "medallion", "calian medallion", "medallions",
                 "calian medallions", "belt", "black belt",
                 "black belts", "wadded-up black belts" }),
        "Lines have been scraped into the ground to form the"
      + " boundaries for a game of tic-tac-toe. Instead of the"
      + " usual X and O symbols, you see Calian Medallions and"
      + " wadded-up black belts. Looks like the Calian player won.\n");
    add_item( ({ "hole in the wall", "hole", "next hole",
                 "next hole in the wall", "holes" }),
        "Some of these holes look fresher than others. Some appear to"
      + " have just been created - by a thundering foot!\n");
    add_item( ({ "bed", "beds", "bedside" }),
        "There are no beds here. Ogres don't use them.\n");

    add_cave_items();
    add_spike("start");

    add_exit("bbroom", "southwest");
    add_exit("glow_wep_drop", "down");
    add_exit("tunnel1", "south");
    
    // Make sure all drop rooms are loaded too
    (AOD_ROOM_DIR + "glow_wep_drop")->telendensanka();
    (AOD_ROOM_DIR + "norm_wep_drop")->telendensanka();
    (AOD_ROOM_DIR + "glow_arm_drop")->telendensanka();
    (AOD_ROOM_DIR + "norm_arm_drop")->telendensanka();
    (AOD_ROOM_DIR + "misc_drop")->telendensanka();
    
} /* create_cave_room */


/*
 * Function name:        start
 * Description  :        Allow guild members to start here
 * Arguments    :        string str -- what was typed following the verb
 * Returns      :        1 -- they tried to start here, 0 -- no arg
 */
public int
start(string str)
{
    notify_fail("Start here? If you want to, just <kick wall>.\n");

    if (!strlen(str))
    {
        return 0;
    }

    if (!parse_command(str, ({}),
        "[a] [hole] [in] [the] 'wall'") && !parse_command(str, ({}),
        "[a] 'hole' [in] [the] [wall]")) 
    {
        return 0;
    }

    if (!this_player()->query_guild_member(GUILD_NAME))
    {
        write("You smash your foot painfully against the rock! You"
          + " pathetic worm, only Ogres may start here!\n");
        return 1;
    }

    if (this_player()->set_default_start_location(AOD_STARTLOC))
    {
        write("Raising your mighty foot, you smash a huge hole through"
          + " the rock wall. It looks just perfect to sleep in! You"
          + " will start here the next time you enter the realms.\n");
    }
    else
    {
        write("Sorry, some problem prevents you from starting here."
          + " Please mail Gorboth at once!\n");
    }

    return 1;
} /* start */


/*
 * Function name:        try_sleep
 * Description  :        Allow players to try to sleep here. It doesn't
 *                       work, but we might as well give the curious
 *                       a decent response.
 * Arguments    :        string arg: What was typed after the verb
 * Returns      :        0 - always fails
 */
public int
try_sleep(string arg)
{
    string  fail = "If you want to sleep here, just <kick> a hole in"
                 + " the wall, and you'll start your travels here.\n";

    notify_fail(fail);

    if (query_verb() == "sleep" || query_verb() == "rest")
    {
        return 0;
    }

    if (!strlen(arg) || !parse_command(arg, ({}),
        "[down] [on] [the] [ground] [ledge]"))
    {
        notify_fail(capitalize(query_verb()) + " how?\n");
        return 0;
    }

    return 0;
} /* try_sleep */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(start, "start");
    add_action(start, "kick");
    add_action(try_sleep, "sleep");
    add_action(try_sleep, "lie");
    add_action(try_sleep, "lay");
    add_action(try_sleep, "rest");
} /* init */


/*
 * Function name:        enter_inv
 * Description  :        Called when objects enter this container or when
 *                       an object has just changed its weight/volume/light
 *                       status. In this case, we want to move anything
 *                       non-living to the droprooms.
 * Arguments    :        ob: The object that just entered this inventory
 *                       from: The object from which it came.
 */
public void
enter_inv(object ob, object from)
{
    set_alarm(1.0, 0.0, &begin_slide(ob, from));
    ::enter_inv(ob, from);
} /* enter_inv */


/*
 * Function name:        begin_slide
 * Description  :        Have the objects begin their slide toward the
 *                       cliff edge.
 * Arguments    :        object ob - the object
 *                       object from - where it came from
 */
public void
begin_slide(object ob, object from)
{
    if (!ob) return;

    if (living(ob) ||
        ob->id("_aod_trophy_spike") ||
        ob->id("coin") ||
        ob->id(AOD_OGRESTOMP_EFFECT) ||
        environment(ob) != this_object())
    {
        return;
    }

    if (!ob->query_no_show_composite())
    {
        tell_room(this_object(), capitalize(LANG_THESHORT(ob))
          + " begins sliding slowly toward the edge of the ravine.\n");
    }

    set_alarm(5.0, 0.0, &fall_droproom(ob, from));
} /* begin_slide */


/*
 * Function name:        fall_droproom
 * Description  :        move the object to the next droproom
 *                       location
 * Arguments    :        object ob - the object
 *                       object from - where it came from
 */
public void
fall_droproom(object ob, object from)
{
    if (!ob)
        return;
    if (environment(ob) != this_object())
    {
        /* someone picked it up before it fell further */
        return;
    }

/*    tell_room(this_object(), capitalize(LANG_ASHORT(ob))
      + " slips over the ledge and disappears into the ravine.\n");
    tell_room(FALL_LOCATION, capitalize(LANG_ASHORT(ob))
      + " tumbles into the area from above.\n");*/
    tell_room(this_object(), capitalize(LANG_THESHORT(ob))
      + " slips over the ledge and disappears into the ravine.\n");
    tell_room(FALL_LOCATION, capitalize(LANG_ASHORT(ob))
      + " tumbles into the area from above.\n");      

    /* set this as a droproom item, to prevent players from looting the
     * droproom to melt down for forge credits.
     */
    ob->add_prop(AOD_RACK_ITEM, 1);
    ob->move(FALL_LOCATION);
} /* fall_droproom */
