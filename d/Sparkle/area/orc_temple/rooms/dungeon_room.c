/*
 *  /d/Sparkle/area/orc_temple/dungeon_room.c
 *
 *  This is the master room file for the dungeons beneath the Orc Temple
 *  west of Sparkle city.
 *
 *  Created June 2010, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/d/Sparkle/area/city/rooms/delay_room";
inherit "/d/Sparkle/lib/room_tell";

#include <macros.h>
#include <stdproperties.h>
#include <time.h>
#include "../defs.h"

/* Definitions */
#define             HORROR_ATTACK    "_orc_dungeons_in_horror"

/* Global Variables */
static mapping      No_exit_msg = ([]);     /* custom no-exit msgs */
public string       Stair_Climb = "up";     /* dir the stairs lead */

/* Prototypes */
public nomask void  create_room();
public void         create_dungeon_room();
public void         add_dungeon_items();
public void         add_dungeon_tells();
public void         enter_inv(object ob, object from);
public void         set_no_exit_msg(mixed dir, string msg);
public int          unq_no_move(string str);
public int          try_item(mixed names, mixed desc);
public string       exit_blocked_hook(object guard);
public int          check_exit();
public int          climb_stairs(string arg);
public int          climb_down_stair_hook();
public int          climb_up_stair_hook();
public void         add_jail_npcs(int mobs);
public void         yogsothoth();
public int          determine_threat(object who);
public void         horror_attack(object who);
public void         trigger_madness(object who);


public void         set_stair_climb(string s) { Stair_Climb = s; }


/*
 * Function name:        create_room
 * Description  :        the basic constructor for rooms
 */
public nomask void
create_room()
{
    add_name(DUNGEON_ROOM);

    add_prop(ROOM_S_MAP_FILE, "orc_dungeons.txt");
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 1);
    add_prop(DOOR_BLOCK_ROOM, 1); /* default is for guards to block doors */
    add_prop(ROOM_I_NO_ALLOW_STEED, 1); /* no steeds in here. */

    create_dungeon_room();

    set_tell_time(180);
    add_dungeon_tells();

    enable_reset(200);  /* make resets as fast as possible for grinding */
} /* create_room */


/*
 * Function name:        create_merc_room
 * Description  :        dummy function for inheriting rooms to mask
 */
public void
create_dungeon_room()
{
    set_short("a set_short is needed here");
    set_long("A set_long is needed here.\n");
} /* create_dungeon_room */


/*
 * Function name:        add_dungeon_items
 * Description  :        Add items that will work in just about any
 *                       dungeon passage.
 */
public void
add_dungeon_items()
{
    try_item( ({ "mold", "patch of mold", "patches of mold",
                 "patch", "patches" }),
        "Mold clings to the mortar in places along the wall. You even"
      + " glimpse a few fungal blooms now and again.\n");
    try_item( ({ "fungus", "bloom", "fungal bloom", "blooms",
                 "fungal blooms" }),
        "Once in a while, you glimpse a patch of fungus growing between"
      + " the mold and other film which coats these walls. Upon close"
      + " inspection, you are repulsed to find that the odor coming from"
      + " these blooms is almost too much to bear. If a larger specimen"
      + " could be found, it would be a fairly incredible tool of"
      + " torture for those with a delicate nose.\n");
    try_item( ({ "wall", "walls", "dungeon wall", "dungeon walls",
                 "wall of the dungeon", "walls of the dungeon",
                 "brick wall", "brick walls" }),
        "The walls of the dungeon are comprised of brick and"
      + " mortar. Though in fairly good repair, dark stains and"
      + " patches of mold mar the surface of the walls, creating"
      + " an atmosphere of uneasiness and gloom.\n");
    try_item( ({ "brick", "bricks", "red brick", "red bricks" }),
        "The bricks which make up the bulk of the dungeon walls are"
      + " the color of red clay. Moisture coats the surface of the"
      + " bricks, which are in places deeply stained and covered"
      + " with an unsightly film.\n");
    try_item( ({ "surface of the brick", "surface of the bricks",
                 "moisture", "film", "unsightly film" }),
        "In many places, the walls of the dungeons are coated with"
      + " moisture which is of unknown origin. Perhaps it is"
      + " little more than condensation. Perhaps it is moisture from"
      + " the earth which has leaked through from beyond the walls."
      + " In some places it is covering deep stains.\n");
    try_item( ({ "stain", "stains", "deep stain", "deep stains",
                 "dark stain", "dark stains" }),
        "Dark stains mar the surface of the brick walls. Looking"
      + " closer, you notice that the stains are actually a brown"
      + " slimy moss which has grown to coat the mortar and much"
      + " of the bricks themselves.\n");
    try_item( ({ "mortar" }),
        "Though hard as stone, the mortar appears to ooze from"
      + " between the bricks like frosting in a layer cake. It"
      + " would seem that little care for beauty went into the"
      + " construction of these dungeons.\n");
    try_item( ({ "moss", "brown moss", "slimy moss",
                 "slimy brown moss", "brown slimy moss" }),
        "The brown moss is very dense in places, covering entire"
      + " sections of the walls. From afar it looks like dark stains,"
      + " but up close, you notice that it is actually a very"
      + " intricate living organism. In drier areas, it is furry,"
      + " with many tiny fronds extending like a carpet from the"
      + " base of the root mesh. Where the moss is wet, it takes on"
      + " the characteristics of a brown sludge.\n");
    try_item( ({ "dungeon", "dungeons", "area", "here", "system",
                 "dungeon system", "tunnel", "tunnels",
                 "corridor", "corridors" }),
        "You are underground, in a dark and gloomy place. Knowing more"
      + " than this will require exploration.\n");
    try_item( ({ "deeper level", "deeper levels" }),
        "There are probably stairs to the deeper levels"
      + " of the dungeons somewhere in the area.\n");

    try_item( ({ "ceiling", "roof", "up" }),
        "The same bricks which make up the walls of these passages"
      + " were used in the construction of the ceiling. Drips"
      + " of water constantly drop from the ceiling, where"
      + " condensation from the dungeon moisture has formed.\n");
    try_item( ({ "drip", "drips", "drop", "drops",
                 "drip of water", "drips of water",
                 "condensation" }),
        "Perhaps there is a nearby stream which is seeping into this"
      + " underground area.\n");
    try_item( ({ "ground", "floor", "down" }),
        "Heavy stones which have been fitted together appear to make"
      + " up most of the ground here in the dungeons. However, a great"
      + " deal of dirt covers most of the floor.\n");
    try_item( ({ "stone", "stones", "heavy stone", "heavy stones" }),
        "The stones are rough and somewhat uneven, making walking"
      + " in this dank place somewhat difficult. Perhaps this is the"
      + " way orcs like to live. Ugh.\n");
    try_item( ({ "dirt", "great deal of dirt" }),
        "It has probably collected over many years of orc housekeeping."
      + " Orcs don't keep house, in case you hadn't guessed.\n");
    try_item( ({ "place" }),
        "Can you be more specific, perhaps?\n");
    try_item( ({ "dark place" }),
        "Yes, and gloomy.\n");
    try_item( ({ "gloomy place" }),
        "Yep. Dark, too.\n");
    try_item( ({ "dark and gloomy place", "gloomy and dark place" }),
        " This dungeon gained noteriety as runner-up in last year's"
      + " Dark & Gloomy Expo at the Mergula Invitational. Word has it"
      + " that the Sparkle Orcs are still petitioning for a re-vote"
      + " following a corruption charge against the undefeated team"
      + " from Minas Morgul. Good luck next year, guys!\n");
    try_item( ({ "frond", "fronds", "tiny frond", "tiny fronds" }),
        "Fuzzy fuzzy fuzzy ... oo! It tickles.\n");
    try_item( ({ "root mesh", "mesh" }),
        "Taking up botany, are we?\n");
    try_item( ({ "sludge", "brown sludge" }),
        "Bleh.\n");
    try_item( ({ "torch", "torches", "many torches",
                 "flickering torch", "flickering torches",
                 "many flickering torches" }),
        "The torches are held to the walls with crude fastenings.\n");
    add_cmd_item( ({ "torch", "torches", }),
                  ({ "get", "take", "steal" }),
        "The torches are held in place either by magic or some"
      + " mechanic that you fail to comprehend.\n");
    add_cmd_item( ({ "torch", "torches", }),
                  ({ "extinguish" }),
        "You try to extinguish the nearest of the torches that is"
      + " fastened to the wall. It goes out for a moment, but then"
      + " flares back to life.\n");
    try_item( ({ "fastening", "fastenings", "crude fastening",
                 "crude fastenings", "torch stand", "torch stands",
                 "stand", "stands" }),
        "No love went into the construction of these torch stands, that"
      + " much is certain.\n");
    try_item( ({ "fire", "flame", "flames" }),
        "The fire from the torches provides a dim illumination"
      + " throughout the dungeons.\n");
    try_item( ({ "illumination", "light", "dim illumination",
                 "dim light", "torchlight", "flickering light",
                 "flickering torchlight" }),
        "Normally, light would be comforting, but this flickering"
      + " torchlight creates a constant sense of moving shadows which"
      + " play tricks on the mind.\n");
    try_item( ({ "shadow", "shadows" }),
        "There are plenty of them down here.\n");
    try_item( ({ "moving shadow", "moving shadows" }),
        "They're everywhere!\n");
    try_item( ({ "breeze", "wind", "air" }),
        "The air down here moves with a strange and disquieting life"
      + " of its own. It almost feels like the hallways are drawing"
      + " breath with your every footstep.\n");
    try_item( ({ "hall", "hallway", "hallways",
                 "corridor", "corridors" }),
        "They are long, narrow, and dark.\n");
    try_item( ({ "tricks" }),
        "You find no tricks.\nOr do you?\n");
    try_item( ({ "mind tricks" }),
        "You find no mind tricks.\nOr do you?\n");
    try_item( ({ "tricks on the mind" }),
        "You find no tricks on the mind.\nOr do you?\n");
    try_item( ({ "temple", "orc temple" }),
        "The temple is far above you here.\n");
} /* add_dungeon_items */


/*
 * Function name:        add_dungeon_tells
 * Description  :        Provide room tells that are ubiquitous to
 *                       rooms in the dungeon
 *
 * Can be masked if these room tells are not desired for a given room.
 */
public void
add_dungeon_tells()
{
    add_tell("A loud drip echoes through the dungeons.\n");
    add_tell("A muffled scream sounds from somewhere nearby.\n");
    add_tell("What sounds like running feet comes from above, and"
      + " a shower of dust falls as the noise passes.\n");
    add_tell("You hear a creaking sound followed by a crash of metal"
      + " somewhere in the distance.\n");
    add_tell("Footsteps nearby suddenly come to a halt, and you"
      + " hear some guttural whispers.\n");
    add_tell("In the distance, a shadow comes into view. The figure"
      + " freezes as it sees you, and then runs off grunting loudly.\n");
    add_tell("An unnatural breeze tugs suddenly at your clothing.\n");
    add_tell("A nearby torch flickers in a sudden breeze, and then"
      + " flares back to life.\n");
} /* add_dungeon_tells */


/*
 * Function name:        enter_inv
 * Description  :        we mask this to set up the room tells.
 */
public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    start_room_tells(); 

    if (interactive(ob) &&
        determine_threat(ob))
    {
        set_alarm(3.0, 0.0, &horror_attack(ob));
    }
} /* enter_inv */


/*
 * From: /d/Gondor/std/room.c
 *
 * Function name:       set_no_exit_msg
 * Description  :       set the custom no-exit msg for direction(s)
 * Arguments    :       mixed dir -- either a string or an array of strings;
 *                                   each string is a direction for which
 *                                   this room does not have an exit.
 *                      string msg -- the msg for these directions
 *
 * So instead of "There is no obvious exit west.", you can tell
 * players "You wander west among the trees for a bit, then return
 * to the road."
 */
public void
set_no_exit_msg(mixed dir, string msg)
{
    int         i, n;

    if ( pointerp(dir) )
    {
        for ( i = 0, n = sizeof(dir); i < n; ++i )
            No_exit_msg[dir[i]] = msg;
    }
    else if ( stringp(dir) && strlen(dir) )
    {
        No_exit_msg[dir] = msg;
    }
} /* set_no_exit_msg */


/*
 * Function name: unq_no_move
 * Description  : mask parent to do custom msgs for 'normal' but
 *                nonexistant directions.  Here, 'normal'
 *                exits are north, southeast, down, etcetera.
 * Arguments    : string str - the command line argument.
 * Returns      : int 0 - always.
 */
public int
unq_no_move(string str)
{
    string      vb = query_verb();

    if ( strlen(No_exit_msg[vb]) )         /* custom msg */
        notify_fail(No_exit_msg[vb]);
    else                                /* oh, well */
        notify_fail("There is no obvious exit "+vb+".\n");
    return 0;
} /* unq_no_move */


/*
 * Function name:       try_item
 * Description  :       checks to see if an item already exists
 *                      within a given object, and if it does not, it then
 *                      adds it as add_item() would.
 * Arguments    :       mixed names --  string or array of strings, the
 *                                      item name(s).
 *                      mixed desc -- string or function, the description.
 * Returns      :       int -- the number of items added
 */
public int
try_item(mixed names, mixed desc)
{
    int         i;
    string      *exists;

    if (pointerp(names)) 
    { 
        exists = ({});
        foreach (string name : names)
        {
            if (item_id(name)) 
            {
                exists += ({ name });
            }
        }
        names -= exists;
        if (sizeof(names))
        {
            add_item(names, desc);
        }
        i = sizeof(names);
    } 
    else if (!this_object()->item_id(names))
    {
        add_item(names, desc);
        i = 1;
    }
    return i;   // # of items added
} /* try_item */


/*
 * Function name:        exit_blocked_hook
 * Description  :        provide a message that can be customized
 *                       when an npc blocks the path moving in a given
 *                       direction in the dungeons.
 * Arguments    :        object guard - the npc blocking the path
 * Returns      :        string - the message
 */
public string
exit_blocked_hook(object guard)
{
    return "The " + guard->short() + " blocks your path!\n";
} /* exit_blocked_hook */


/*
 * Function name:        check_exit
 * Description  :        In certain places in the dungeon, we will want
 *                       the player to have to kill whatever is guarding
 *                       a room to move onward.
 * Returns      :        int 1 - blocked, 0 - allow
 */
public int
check_exit()
{
    string  txt = "";
    object  guard;

    if (this_player()->id(ORC_TEMPLE_NPC))
    {
        return 0; /* we let orcs in their own temple past, of course. */
    }

    if (objectp(guard = present(ORC_TEMPLE_NPC, this_object())))
    {
        if (CAN_SEE(guard, this_player()))
        {
            txt = exit_blocked_hook(guard);
        }
        else
        {
            write("With your thief skills, you sneak past the "
              + guard->short() + " and make your way onward.\n");
            return 0; /* let them pass */
        }

        if (this_player()->query_wiz_level())
        {
            write(txt + "Since you are a wizard, that doesn't"
              + " matter.\n");
            return 0; /* let wizards pass, regardless */
        }

        write(txt);
        tell_room(this_object(), QCTNAME(this_player()) + " tries to"
          + " move forward, but is blocked by the guard.\n", this_player());
        return 1;
    }

    return 0; /* they can pass */
} /* check_exit */


/*
 * Function name:        climb_stairs
 * Description  :        Allow the player to try to climb stairs here
 * Arguments    :        string arg - what was typed after the verb
 * Returns      :        int 1 - success, 0 - failure
 */
public int
climb_stairs(string arg)
{
    if (!strlen(arg))
    {
        notify_fail("Climb what, the stairs?\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[up] [down] [the] [uneven] [stone] 'step' / 'steps' /"
      + " 'stair' / 'stairs' / 'stairway'") &&
        arg != Stair_Climb)
    {
        notify_fail("You can't climb that! The stairs, perhaps?\n");
        return 0;
    }

    if (this_player()->query_wiz_level())
    {
        notify_fail("Normally, we would move the player " + Stair_Climb
          + " here using command(). Since you're a wizard, that won't"
          + " work, so just type <" + Stair_Climb + "> yourself.\n");

        return 0;
    }

    this_player()->command(Stair_Climb);
    return 1;
} /* climb_stairs */


/*
 * Function name:        climb_down_stair_hook
 * Description  :        message to print to the player when they
 *                       climb down some stairs
 * Returns      :        int 1  - if guarded
 *                       int 0  - if not guarded
 */
public int
climb_down_stair_hook()
{
    if (check_exit())
    {
        return 1;
    }

    tell_room(environment(this_player()), QCTNAME(this_player())
      + " descends the stairs and is lost from view.\n", this_player());
    write("You carefully descend the stairway, moving down to a deeper"
      + " level of the dungeons.\n");

    return 0;
} /* climb_down_stair_hook */


/*
 * Function name:        climb_up_stair_hook
 * Description  :        message to print to the player when they
 *                       climb up some stairs
 * Returns      :        string - the message
 */
public int
climb_up_stair_hook()
{
    if (check_exit())
    {
        return 1;
    }

    tell_room(environment(this_player()), QCTNAME(this_player())
      + " climbs up the stairs out of sight.\n", this_player());
    write("You climb up the stone staircase.\n");

    return 0;
} /* climb_up_stair_hook */


/*
 * Function name:        add_jail_npcs
 * Description  :        add a slightly random configuration of
 *                       npcs to this room, appropriate for the
 *                       jail cells area.
 * Arguments    :        int mobs - how many npcs generally in this room?
 */
public void
add_jail_npcs(int mobs)
{
    int     runts    = 0,
            warriors = 0;

    mobs += random(3);

    while (mobs)
    {
        if (!random(7))
        {
            runts++;
        }
        else
        {
            warriors++;
        }

        mobs--;
    }

    if (runts)
    {
        add_npc(NPC_DIR + "goblin_runt", runts, &->arm_me());
    }

    add_npc(NPC_DIR + "goblin_warrior", warriors, &->arm_me());
} /* add_jail_npcs */


/* 
 * Function name:        do_smell
 * Description  :        Let players sniff the air here
 * Arguments    :        string arg - what was typed after the verb
 * Returns      :        1 - if no arg, 0 - if arg
 */
public int
do_smell(string arg)
{
    if (strlen(arg))
    {
        /* let the mudlib handle it */
        return 0;
    }

    write("You inhale deeply ...\n\n");
    this_player()->command("$exa smell");

    return 1;
} /* do_smell */


/*
 * Function name:        yogsothoth
 * Description  :        The player tries to think about the Arch
 *                       Demon, and pays a price in pain.
 */
public string
yogsothoth()
{
    this_player()->command("$gasp");
    this_player()->command("$glare horror");
    this_player()->command("$tremble");
    this_player()->command("$scream");

    this_player()->heal_hp(-50);

    return " ... ... the face ... of ... the pit ...\n"
         + "You feel less healthy.\n";
} /* yogsothoth */


/*
 * Function name:        add_madness_tells
 * Description  :        Provide room tells that happen as one nears
 *                       Yogsothoth
 */
public void
add_madness_tells()
{
    add_tell("You can sense it ... in the pit ... waiting ..."
      + " knowing you approach ...\n");
    add_tell("A sudden urge to flee slams through your mind!\n");
    add_tell("Horror wells in your throat, like burning acid, and"
      + " you feel your legs weaken.\n");
    add_tell("A distant, deep and throbbing moan sends shudders"
      + " through the walls and floor.\n");
    add_tell("Primal horror claws at your mind, stripping down your"
      + " sanity piece by ragged piece.\n");
    add_tell("A sudden vision appears of eyes ... so many eyes."
      + " Your mind reels in a fit of madness.\n");
    add_tell("A breath catches in your throat, and your frayed"
      + " nerves send you into spasms of coughing.\n");
    add_tell("It can see you. It waits for you. You know this, and"
      + " your mind bleeds terror into your eyes and throat.\n");
} /* add_madness_tells */


/*
 * Function name:        determine_threat
 * Description  :        The power of Yog-Sothoth assesses any player
 *                       who might enter the rooms of the dungeon. If
 *                       they have above a 40 stat average, they are
 *                       driven mad with fear, and are forced to flee
 *                       the dungeon. We roll our own stat-average check
 *                       rather than just using query_average_stat due
 *                       to the fact that the magic amulet that players
 *                       may wear to lower their size and allow entry
 *                       does not change the result of query_average_stat.
 * Arguments    :        object who - the player to check
 * Returns      :        int 1 - the player is a threat
 *                       int 0 - the player is not a threat
 */
public int
determine_threat(object who)
{
    int     i = 0;
    int     n = 0;

    /* Wizards are immune to the effects. */
    if (who->query_wiz_level())
    {
        return 0;
    }

    while (i < 6)
    {
        n += who->query_stat(i);
        i++;
    }

    return ((n/6) > THREAT_THRESHHOLD);
} /* determine_threat */


/*
 * Function name:        horror_attack
 * Description  :        Yog-Sothoth protects its premesis by flaying the
 *                       mind of an intruder it has deemed a threat with
 *                       the full nature of its horror. This forces the
 *                       victim to flee the dungeon in a fit of madness.
 * Arguments    :        object who - the player
 */
public void
horror_attack(object who)
{
    if (who->query_prop(HORROR_ATTACK))
    {
        /* If they ran a few rooms into the dungeon, we want to make
         * sure they only get one horror attack.
         */
        return;
    }

    who->catch_tell("\n\n"
      + "Suddenly, the walls around you vanish and you find yourself"
      + " alone and naked - standing tranfixed before a great amorphous"
      + " form whose many glistening eyes pulse and throb. As each eye"
      + " passes its gaze over you, you feel a layer of flesh ripped"
      + " from you, tearing you down first by the skin, then by the"
      + " fat, then by the muscle, and finally by the bone until only"
      + " your own glistening and tender organs remain. Slowly, you"
      + " feel the portions of you that are left drawn slowly into the"
      + " obvlivion of the horror until only your brain, shaking and"
      + " quivering with terror, remains. Your brain spasms, ripping"
      + " itself open as you hear your own high-pitched screams!\n\n");

    tell_room(environment(who), QCTNAME(who) + " freezes suddenly"
      + " in place. " + capitalize(who->query_possessive()) + " eyes"
      + " widen, and then dialate as " + who->query_possessive()
      + " face slackens and then slowly twists into an expression of"
      + " raw terror.\n", who);

    who->add_prop(HORROR_ATTACK, 1);

    set_alarm(3.0, 0.0, &trigger_madness(who));
} /* horror_attack */



/*
 * Function name:        trigger_madness
 * Description  :        If the player is still standing in a dungeon
 *                       location they are forced to flee now.
 * Arguments    :        object who - the player
 */
public void
trigger_madness(object who)
{
    int    panic = 35;

    who->remove_prop(HORROR_ATTACK);

    if (!environment(who)->id(DUNGEON_ROOM))
    {
        who->catch_tell("You realize that the horrific vision is"
          + " gone, but you still feel like hiding in a hole for"
          + " a few weeks.\n");

        tell_room(environment(who), QCTNAME(who) + " blinks a few"
          + " times and wipes " + who->query_possessive() + " brow"
          + " with trembling fingers.\n", who);

        who->add_panic(panic);
        return;
    }

    who->catch_tell("A rush of sight, sound, and your own labored"
      + " breathing and pounding heart bring you out of the nightmare,"
      + " and you find yourself standing back at the entrance to the"
      + " dungeon, unsure whether you are alive or dead.\n\n");

    tell_room(environment(who), "With a sudden spasm, "
      + QTNAME(who) + " launches out of the room and you hear "
      + who->query_possessive() + " tortured screams fading all the"
      + " way out of the dungeon.\n", who);

    who->move("/d/Genesis/start/human/wild2/orcfort/stair");
    who->add_panic(panic);

#if LOG_ACTIVITY
        write_file(LOG_DIR + "horror", 
            TIME2FORMAT(time(), "mm/dd/yyyy")
          + " (" + ctime(time())[11..18] + ") "
          + capitalize(who->query_name())
          + " flees the dungeon.\n");
#endif
} /* trigger_madness */