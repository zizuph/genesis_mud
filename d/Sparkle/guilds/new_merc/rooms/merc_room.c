/*
 *  /d/Sparkle/guilds/new_merc/rooms/merc_room.c
 *
 *  This is the base file for rooms in the Mercenary Camp for the
 *  Free Mercenary Guild.
 *
 *  Created April 2009, by Cooper Sherry (Gorboth)
 *     Special thanks to Petros for assistance when my own skill
 *     faltered! (as usual)
 */
#pragma strict_types

inherit "/d/Sparkle/area/city/rooms/delay_room";
inherit "/d/Sparkle/lib/room_tell";

#include <const.h>         /* for G_FEMALE           */
#include <macros.h>        /* for QCTNAME, etc       */
#include <stdproperties.h> /* for ROOM_I_INSIDE, etc */
#include "../merc_defs.h"

/* Global Variables */
static mapping     No_exit_msg = ([]);     /* custom no-exit msgs */
public int         Dirty = 0; /* How dirty is the room? We add 1 to
                               * the value each time someone who has
                               * not wiped their feet at the entrance
                               * to the lodge enters this room.
                               */

/* Prototypes */
public void          create_merc_room();
nomask void          create_room();
varargs public mixed long(string str);
public void          add_outdoor_tells();
public void          enter_inv(object ob, object from);
public int           try_item(mixed names, mixed desc);
public void          add_river_view();
public void          add_bridge_view();
public void          add_mill_view();
public void          add_outdoor_view();
public void          add_lodge_view();
public void          add_indoor_view();
public void          add_indoor_lodge_view();
public string        do_wipe_feet();
public string        look_ground(string arg);
public int           check_merc_access();
public void          set_no_exit_msg(mixed dir, string msg);
public int           unq_no_move(string str);
public int           sweep_floor(string arg);
public void          init();
public string        describe_dirt();
public string        show_dirt();
public object        safely_load_master_file(string filename);

public void          set_dirty(int i) { Dirty = i; }
public int           query_dirty() { return Dirty; }

/*
 * Function name:        create_merc_room
 * Description  :        dummy function for inheriting rooms to mask
 */
public void
create_merc_room()
{
    set_short("a set_short is needed here");
    set_long("A set_long is needed here.\n");
} /* create_merc_room */


/*
 * Function name:        create_room
 * Description  :        set up the room
 */
nomask void
create_room()
{
    add_prop(ROOM_S_MAP_FILE, "merc_area.txt");

    create_merc_room();
    try_item( ({ "sparkle", "land of sparkle", "lands of sparkle",
                 "continent" }),
        "Sparkle is all around you - the very continent you are currently"
      + " walking upon.\n");

    set_tell_time(180);

    if (!query_prop(ROOM_I_INSIDE))
    {
        add_outdoor_tells();
        add_prop(ROOM_S_MAP_FILE, "merc_area_outside.txt");
    }
    else
    {
        add_prop(ROOM_S_MAP_FILE, "merc_area_inside.txt");
    }
    
} /* create_room */


/*
 * Function name: long
 * Description:   Describe the room and possibly the exits
 * Arguments:     str: name of item or 0
 * Returns:       A string holding the long description of the room.
 *
 * This mask of the mudlib function is courtesy of Petros (thanks!!)
 * to compensate for my originally very flawed model which broke under
 * VBFC pressure. The purpose is to allow us to display an extra line
 * if the floor is particularly dirty.
 */
varargs public mixed
long(string str)
{
    string long_desc;
    
    long_desc = ::long(str);
    if (!stringp(long_desc))
    {
        // Sometimes long can return an integer, as in when someone types
        // "exa" without any arguments.
        return long_desc;
    }
    
    if (!strlen(str))
    {
        // When str is null, we are getting a room description
        if (strlen(exits_description()))
        {
            // We remove the exits description first if it exists
            string * exit_lines = explode(exits_description(), "\n");
            string * long_lines = explode(long_desc, "\n");
            // We search for the first line that the exit appears. There
            // is code that adds item descriptions after the actual
            // exits in the exits_description() masks.
            int exit_start_index = member_array(exit_lines[0], long_lines);
            if (exit_start_index == 0)
            {
                long_desc = "";
            }
            else if (exit_start_index != -1)
            {
                long_desc = implode(long_lines[..(exit_start_index - 1)], "\n");
            }
            if (strlen(long_desc))
            {
                long_desc += "\n";
            }
        }
        long_desc += show_dirt();
        long_desc += exits_description();
    }    

    return long_desc;
} /* long */


/*
 * Function name:        add_outdoor_tells
 * Description  :        Provide room tells that are ubiquitous to
 *                       outdoor rooms around the camp
 *
 * Can be masked if these room tells are not desired for a given room.
 */
public void
add_outdoor_tells()
{
    add_tell("Birds chirp in the distance.\n");
    add_tell("The sound of a woodpecker echoes in the distance.\n");
    add_tell("A slight breeze blows through the area.\n");
    add_tell("A cloud passes before the sun, casting sudden shade over"
      + " the area.\n");
} /* add_outdoor_tells */


/*
 * Function name:        enter_inv
 * Description  :        we mask this to set up the room tells and to
 *                       create the effect where the Merc indoor rooms
 *                       get dirtier as people who don't wipe their
 *                       feet track dirt around.
 */
public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    start_room_tells();

    if (query_prop(ROOM_I_INSIDE))
    {
        if (ob->query_prop(MERC_WIPED_FEET))
        {
            return;
        }

        Dirty++;
    }   
} /* enter_inv */



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
 * Function name:        add_river_view
 * Description  :        items to add if the river is visible here
 */
public void
add_river_view()
{
    try_item( ({ "river", lower_case(RIVERNAME),
                 lower_case(RIVERNAME) + " river",
                 "river " + lower_case(RIVERNAME), "water" }),
        "The " + RIVERNAME + " River flows gently but steadily a short"
      + " distance to the north, where it provides an easily guarded"
      + " perimeter to the camp.\n");
    try_item( ({ "barrier", "perimeter", "perimeter of the camp" }),
        "The river forms a natural barrier, giving the perimeter guards"
        + " a clear advantage against any would-be invaders.\n");
    try_item( ({ "perimeter guard", "perimeter guards", "guard",
                 "guards" }),
        "Guards are stationed at various locations along the perimeter"
      + " of the camp. Most of them are not visible from here.\n");
} /* add_river_view */


/*
 * Function name:        add_bridge_view
 * Description  :        provide descriptions if the bridge is visible
 *                       from this location
 */
public void
add_bridge_view()
{
    try_item( ({ "bridge", "wooden bridge", "sturdy wooden bridge",
                 "sturdy bridge" }),
        "A sturdy wooden bridge spans the river in the distance,"
      + " providing the only obvious entrance to the camp.\n");
    try_item( ({ "entrance", "obvious entrance" }),
        "There may be other ways into this camp, but the bridge is"
      + " the only one that presents itself clear as daylight.\n");
} /* add_bridge_view */


/*
 * Function name:        add_mill_view
 * Description  :        items to add if the exterior of the sawmill
 *                       is visible from here.
 */
public void
add_mill_view()
{
    try_item( ({ "mill", "sawmill", "small building",
                 "smaller building", "saw mill", "old sawmill" }),
        "At the north edge of the camp, an old sawmill extends out"
      + " over the edge of the river. Though no longer used to mill"
      + " lumber, its slow-turning waterwheel churns endlessly on,"
      + " only its uppermost crest visible where it rises above the"
      + " level of the roof. The path runs right up to an entrance"
      + " on the south face of the building, where a few guards are"
      + " visible.\n");
    try_item( ({ "north edge of the camp" }),
        "A sawmill is visible there before the river.\n");
    try_item( ({ "waterwheel", "wheel", "water wheel",
                 "slow-turning watherwheel" }),
        "The waterwheel is considerably larger than the northern"
      + " face of the sawmill, to which it is attached. It slowly"
      + " turns, providing an endless yet peaceful washing sound to"
      + " compliment the natural sounds provided by the river itself.\n");
    try_item( ({ "northern face of the sawmill" }),
        "It is not visible from here, but even if it were, it would"
      + " be obscured by the waterwheel.\n");
    try_item( ({ "crest", "uppermost crest",
                 "uppermost crest of the waterwheel",
                 "top of the wheel", "top of the waterwheel" }),
        "The top of the waterwheel is all that is visible from here.\n");
    try_item( ({ "roof" }),
        "Which roof do you wish to examine? That of the mill or of"
      + " the lodge?\n");
    try_item( ({ "roof of the mill", "shingle", "shingles",
                 "wooden shingles", "wooden shingle", "mill roof",
                 "sawmill roof", "roof of the sawmill" }),
        "Wooden shingles comprise the roof of the mill, though many of"
      + " these are covered in shaggy moss.\n");
    try_item( ({ "moss", "shaggy moss", "green moss", "brown moss" }),
        "Shaggy moss, some green, some brown, has grown to cover many of"
      + " the wooden shingles which have been used to roof the"
      + " sawmill.\n");
    try_item( ({ "mill guard", "mill guards", "sawmill guard",
                 "sawmill guards" }),
        "A few sturdy guards are posted in front of the sawmill.\n");
    try_item( ({ "south face", "south face of the building",
                 "entrance to the mill", "mill entrance" }),
        "The mill entrance appears to be guarded by a few able-bodied"
      + " mercenaries.\n");
    try_item( ({ "able-bodied guard", "able-bodied guards",
                 "able-bidied mercenary", "able-bodied mercenaries",
                 "capable looking guard", "capable looking guards", }),
        "Seeing such capable looking guards causes one to wonder about"
      + " making a career of being a Mercenary. Perhaps inside that"
      + " mill one might get that chance.\n");
} /* add_mill_view */


/*
 * Function name:        add_outdoor_view
 * Description  :        add items appropriate to all outdoor rooms
 *                       in the camp (or indoor rooms with a view)
 */
public void
add_outdoor_view()
{
    try_item( ({ "guards", "guard" }),
        "Guards are visible throughout the camp. Some patrol along"
      + " the perimeter while others are visible before entrances to"
      + " the buildings.\n");
    try_item( ({ "sky", "up" }),
        one_of_list( ({
            "Bright sunlight streams between clouds to cast a warm"
          + " glow over the camp.\n",
            "A light mist has settled over the camp, though the sun"
          + " is working to burn it off.\n",
            "A few scattered clouds occasionally drift in front of the"
          + " sun, which peers out brightly over the area.\n",
            }) ) );
    try_item( ({ "sun", "sunlight", "sunshine" }),
        "The sun shines brightly above, masked by the occasional"
      + " passing cloud.\n");
    try_item( ({ "cloud", "clouds" }),
        "A number of clouds are visible in the sky, silently drifting"
      + " inland from the sea a ways to the east.\n");
    try_item( ({ "mist" }),
        "A thin mist hangs over the camp.\n");
    try_item( ({ "ground", "down", "terrain" }),
        "The ground is covered by a lawn of grass which is broken up"
      + " by paths which travel throughout the various destinations"
      + " of the camp.\n");
    try_item( ({ "lawn", "grass", "grasses", "natural grasses",
                 "rugged natural grasses", "rugged grass" }),
        "This is no manicured lawn as might be seen in an estate."
      + " Rather, these is the rugged natural grasses that grow in the"
      + " plains of this region which have taken root in and around"
      + " the camp.\n");
    try_item( ({ "manicured lawn" }),
        "That it is not!\n");
    try_item( ({ "path", "paths", "road", "pathway", "pathways",
                 "roadway" }),
        "There are pathways strewn throughout the grounds of the camp,"
      + " most leading up to the entrances of the buildings.\n");
    try_item( ({ "tree", "trees", "forest", "woods" }),
        "The forest has been cleared within a hundred yards of the"
      + " camp in all directions. Stumps from the logging days of the"
      + " camp mark the terrain in various places.\n");
    try_item( ({ "stump", "stumps", "clearing", "clear-cut",
                 "clear cut", "clearcut" }),
        "Stumps are visible around the camp wherever one might choose"
      + " to look. The legacy of the loggers will remain for many long"
      + " years.\n");
    try_item( ({ "camp", "mercenary camp", "logging camp",
                 "mercenary guild", "old logging camp", "guild" }),
        "All around you stands the Mercenary Camp. Once an operation for"
      + " logging efforts in the early years of the construction of"
      + " the City of Sparkle, the camp was long deserted until fairly"
      + " recently when the lodge and old sawmill were turned over"
      + " to the Mercenaries as a sign of gratitude by the City Council"
      + " following the orc raids which threatened to destroy Sparkle,"
      + " in which the Mercenaries played a key role in thwarting. The"
      + " camp seems very alive and hums with the quiet activity of the"
      + " many members of the Mercenary Guild.\n");
    try_item( ({ "mercenary", "mercenaries", "member", "members",
                 "members of the mercenary guild" }),
        "They stroll about the camp. Some coming and going, others as"
      + " guards or providers of training.\n");
    try_item( ({ "building", "buildings" }),
        "There are two buildings in the camp - the mill in the north"
      + " and the lodge in the middle of the camp.\n");
} /* add_outdoor_view */


/*
 * Function name:        add_lodge_view
 * Description  :        provide items if the lodge is visible
 *                       from here
 */
public void
add_lodge_view()
{
    try_item( ({ "lodge", "large building", "large structure",
                 "tall building", "old lodge", "logging lodge",
                 "old logging lodge", "large lodge" }),
        "An old logging lodge rises in the middle of the camp, having"
      + " been converted to act as the main hub for guild activity for"
      + " the Mercenaries. Though massive, it has been built log-cabin"
      + " style, with stripped timbers having been interlocked to form"
      + " the walls of the two-story structure. Many windows look out"
      + " over the grounds.\n");
    try_item( ({ "window", "windows", "many windows" }),
        "The windows have been cut in the sides of the timbers which"
      + " form the walls of the lodge. There are dozens of them.\n");
    try_item( ({ "middle of the camp", "grounds" }),
        "The grounds of the camp mainly surround the large lodge which"
      + " overlooks them.\n");
    try_item( ({ "timber", "timbers", "stripped timber",
                 "stripped timbers" }),
        "They are huge! Were it not for the fact that this was once the"
      + " housing for a logging operation, one would wonder how such"
      + " trees were acquired.\n");
    try_item( ({ "wall", "walls" }),
        "The walls of the lodge are sturdy as stone, though comprised"
      + " of once-living wood.\n");
} /* add_lodge_view */
        

/* 
 * Function name:        add_indoor_view
 * Description  :        items that should be common to all indoor
 *                       rooms
 */
public void
add_indoor_view()
{
    try_item( ({ "sky", "sun", "cloud", "clouds" }),
        "Here indoors the sky is not visible.\n");
    try_item( ({ "river", RIVERNAME + " river", RIVERNAME }),
        "The sounds from the river sometimes trickle in from"
      + " an open window, but you cannot see it from inside.\n");
    try_item( ({ "forest", "woods", "trees", "tree" }),
        "The forest which surrounds this camp cannot be viewed"
      + " from indoors.\n");
} /* add_indoor_view */


/*
 * Function name:        add_indoor_lodge_view
 * Description  :        add items that can be common to rooms
 *                       inside the lodge
 */
public void
add_indoor_lodge_view()
{
    try_item( ({ "ground", "floor", "down" }),
        &look_ground("ground"));
    try_item( ({ "hardwood", "hardwood floor" }),
        &look_ground("hardwood"));
    try_item( ({ "edge", "edges", "clean edge", "clean edges" }),
        "Jointed to near perfection!\n");
    try_item( ({ "line", "lines", "straight line", "straight lintes" }),
        "No slop work went into the construction of this place, that"
      + " much is clear!\n");
    try_item( ({ "slop", "slop work" }),
        "None to be seen!\n");
    try_item( ({ "wall", "walls", "lodge wall", "lodge walls",
                 "wall of the lodge", "walls of the lodge" }),
        "The interior of the lodge is characterized largely by the"
      + " massive stripped timbers which interlock log-cabin style to"
      + " form the walls which frame the entire structure.\n");
    try_item( ({ "interior", "interior of the lodge", "lodge interior" }),
        "Its rather cozy in here.\n");
    try_item( ({ "timber", "timbers", "stripped timber",
                 "stripped timbers", "massive timber", "massive timbers",
                 "massive stripped timber", "massive stripped timbers",
                 "log", "logs", "lumber" }),
        "These logs are mostly uniform in shape, and have been placed"
      + " together with confident precision. They seem a very appropriate"
      + " testimony to the efforts of a logging operation such as once"
      + " was housed by them.\n");
    try_item( ({ "operation", "logging operation" }),
        "Long gone. The Mercenaries are the tennants now.\n");
    try_item( ({ "mercenaries", "mercenary", "guard", "guards" }),
        "Mercenaries, some guards, some merely members of the guild,"
      + " come and go as they please in these halls. You find them"
      + " everywhere you look.\n");
    try_item( ({ "guild", "guildhall", "mercenary guild",
                 "mercenary guildhall", "guild hall",
                 "mercenary guild hall", "guild lodge",
                 "mercenary guild lodge" }),
        "It is the very lodge you stand within!\n");
    try_item( ({ "lodge", "loggers lodge", "logger's lodge",
                 "old loggers lodge", "old lodge", "old logger's lodge",
                 "structure", "large structure", "building" }),
        "No longer a place of logging, this lodge now houses the"
      + " Mercenary Guild.\n");
    try_item( ({ "up", "ceiling", "roof" }),
        "The ceiling is supported by many large beams which connect to"
      + " rafters overhead.\n");
    try_item( ({ "nearby window", "nearby windows" }),
        "Ahh ... its fairly beautiful outside, isn't it?\n");
    try_item( ({ "beam", "beams", "large beam", "large beams",
                 "many beams", "many large beams" }),
        "The beams have been milled from huge trees, and support the"
      + " weight of the rafters.\n");
    try_item( ({ "rafter", "rafters", "overhead rafters",
                 "black rafters", "black rafter" }),
        "The rafters have been painted black. There is a type of"
      + " beauty to the work here.\n");
    try_item( ({ "carpet", "carpets", "rugged carpet", "rugged carpets" }),
        "They appear more functional than decorative, trapping some of"
      + " the dirt that gets tracked in by the many boots.\n");
    try_item( ({ "dirt" }),
        describe_dirt);
    try_item( ({ "runner", "runners" }),
        "There are runners travelling the various hallways of the"
      + " lodge, perhaps to trap the dirt that gets tracked in.\n");
    try_item( ({ "wood" }),
        "You are surrounded by the stuff!\n");
    try_item( ({ "logger", "loggers" }),
        "They haven't used this facility for years. Its all Mercenaries"
      + " these days.\n");
    try_item( ({ "facility" }),
        "It used to be a logging operation, long ago.\n");
    try_item( ({ "corner", "corners", "certain corners" }),
        "I suppose the dirt has to excape the broom somehow.\n");
    try_item( ({ "boot", "boots", "many boots" }),
        "They come and go in here. Did you wipe yours?\n");
    try_item( ({ "window", "windows" }),
        "Windows open onto the grounds around the camp from nearly every"
      + " room in the lodge. The natural light cheers the place up"
      + " considerably.\n");
    try_item( ({ "light", "natural light", "sunlight" }),
        "Windows always make a place seem cheerier, don't they?\n");
    try_item( ({ "grounds", "grounds of the camp", "outside",
                 "camp", "camp outside" }),
        "The grounds of the camp are visible from nearby windows, but"
      + " you'll need to actually go out there to see much of what is"
      + " going on.\n");
    try_item( ({ "feet", "my feet", "boot", "foot", "boots",
                 "my boots", "my boot", "my foot" }),
        "Hmmm ... did you remember to wipe them when you came in?\n");
    try_item( ({ "hallway", "hallways", "passage", "passageways" }),
        "There are hallways throughout the lodge. Perhaps you should"
      + " explore them?\n");

    add_cmd_item( ({ "boot", "boots", "feet", "shoes" }),
                  ({ "wipe" }), do_wipe_feet);
    add_cmd_item( ({ "lodge", "hall", "hallway", "hallways" }),
                  ({ "explore" }),
        "Sure! Go right ahead. Um ... you'll need to actually type"
      + " direction commands to get started.\n");
} /* add_indoor_lodge_view */


/*
 * Function name:        do_wipe_feet
 * Description  :        provide a state-based response when the player
 *                       tries to wipe their feet
 * Returns      :        string - the description to print
 */
public string
do_wipe_feet()
{
    if (this_player()->query_prop(MERC_WIPED_FEET))
    {
        return "Fortunately, you've already wiped your feet on the mat"
          + " back at the entrance. Just don't forget to do it again"
          + " should you go back outside!\n";
    }

    return "You'll need to go find a mat to wipe them on. Wiping them on the"
      + " carpets will only make the lodge that much dirtier! Maybe check"
      + " back at the entrance?\n";
} /* do_wipe_feet */


/*
 * Function name:        look_ground
 * Description  :        provide  for the ground
 *                       descriptions based on how dirty it is
 * Arguments    :        string arg = which thing we want to 
 *                                    describe
 * Returns      :        string - the description
 */
public string
look_ground(string arg)
{
    string  desc;

    switch(arg)
    {
        case "ground":
            desc = "The floor is hardwood, occasionally covered by a rugged"
              + " carpet or runner in certain places. ";
            break;
        case "hardwood":
            desc = "The hardwood floor, though rough due to extreme wear"
              + " over many years of service, displays the straight lines"
              + " and clean edges one would expect from a good lumber"
              + " mill. ";
            break;
    }

    return desc + describe_dirt();
} /* look_ground */


/*
 * Function name:        check_merc_access
 * Description  :        Only allow merc members and wizards to use
 *                       this exit
 * Returns      :        int 1 - don't allow
 *                       int 0 - allow
 */
public int
check_merc_access()
{
    if (IS_MERC(this_player()))
    {
        write("As you proceed forward, a few guards step into view."
          + " Recognizing you as a fellow Mercenary, they usher you"
          + " past, offering you a few curt words of greeting.\n");
        return 0;
    }

    if (this_player()->query_wiz_level())
    {
        write("As you proceed forward, a few guards step into view."
          + " Recognizing you as a wizard, they quickly step back and"
          + " bow respectfully.\n");
        return 0;
    }

    if (this_player()->query_prop(OBJ_I_INVIS) ||
        this_player()->query_prop(OBJ_I_HIDE))
    {
        write("As you proceed forward, a few guards step into view,"
          + " glaring warily around. Though they do not seem to be able"
          + " to see you, they move into a position which blocks"
          + " your further progress. One of them says: Do you smell"
          + " that? I know the musk of my fellow Mercenaries, and that"
          + " odor is not from our kind!\n");
        return 1;
    }

    write("As you proceed forward, a few guards step into view. Seeing"
      + " that you are not a fellow Mercenary, they bring you to a halt"
      + " saying: Members only! Head over to the mill if you want to"
      + " become one of us.\n");
    return 1;
} /* check_merc_access */


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
 * Function name:        sweep_floor
 * Description  :        Allow a player to sweep dirt off the floor
 *                       into an adjascent room - part of a little
 *                       cleaning quest for this area guild area.
 * Arguments    :        string arg - what was typed after the verb
 * Returns      :        int 1 - success, 0 - failure
 */
public int
sweep_floor(string arg)
{
    object    broom;

    if (!strlen(arg))
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[the] 'floor' / 'ground' [with] [the] [broom]"))
    {
        notify_fail("Perhaps you'd like to try to sweep the floor?\n");
    }

    if (!objectp(broom = present("broom", this_player())))
    {
        write("If you want to tackle cleaning the floor in here, you'll"
          + " definitely need a broom first.\n");
        return 1;
    }

    if (broom->query_wielded() != this_player())
    {
        write("You gotta wield that broom first, "
          + ((this_player()->query_gender() != G_FEMALE) ? "man" : "lady")
          + "!\n");
        return 1;
    }

    if (!Dirty)
    {
        write("Looks like the floor in here is pretty clean. No need!\n");
        return 1;
    }

    write("You busy yourself with the broom, sweeping all the dirt in"
      + " the room into a large pile which you gather up and toss out"
      + " a nearby window.\n");
    tell_room(this_object(), QCTNAME(this_player()) + " busies "
      + this_player()->query_objective() + "self with a broom, sweeping"
      + " all the dirt in the room into a large pile which "
      + this_player()->query_pronoun() + " gathers up and tosses out a"
      + " nearby window.\n", this_player());

    Dirty = 0;
    return 1;
} /* sweep_floor */


/*
 * Function name:        init
 * Description  :        add actions to the player
 */
public void
init()
{
    ::init();

    add_action(sweep_floor, "sweep");
    add_action(sweep_floor, "clean");
} /* init */


/*
 * Function name:        describe_dirt
 * Description  :        Tell us how dirty the floor is.
 * Returns      :        string - the description
 */
public string
describe_dirt()
{
    switch (Dirty)
    {
        case 0:
            return "The floor is immaculately swept. Someone obviously"
              + " cares about keeping the place looking nice.\n";
            break;
        case 1..10:
            return "The floor shows a few traces of dirt, but is"
              + " mostly clean.\n";
            break;
        case 11..50:
            return "The floor has a few areas which are a bit"
              + " dirty, probably from all the foot-traffic.\n";
            break;
        case 51..100:
            return "The floor could use a bit of a sweep. Looks like"
              + " not very many people are wiping their feet around"
              + " here, as dirt is starting to pile up.\n";
            break;
        case 101..250:
            return "The floor looks like it hasn't been swept in a"
              + " while. Dirt is piling up all along the walking"
              + " surfaces. People really should learn to wipe their"
              + " feet when they come in!\n";
            break;
        case 251..500:
            return "Oh for heaven's sake ... someone needs to grab a"
              + " broom and get to work in here. Dirt is starting to"
              + " really make the place look bad. Why don't people"
              + " wipe their feet before stomping around in here with"
              + " their dirty boots?\n";
            break;
        default:
            return "Utterly disgraceful! Dirt is everywhere in here!"
              + " Doesn't anyone bother to sweep anymore? What, just"
              + " track dirt from heaven knows where all over the"
              + " guildhall and never think to wipe feet first or at"
              + " least grab a broom and do a bit of upkeep? This just"
              + " won't do!\n";
            break;
    }
} /* describe_dirt */


/*
 * Function name:        show_dirt
 * Description  :        This displays dirt in the actual long
 *                       description for inside rooms, but only if
 *                       the room has gotten really dirty.
 * Returns      :        string - the extra desc for dirty rooms
 */
public string
show_dirt()
{
    if (Dirty < 251)
    {
        return "";
    }
    
    return "The floor is getting really dirty in here.\n";
} /* show_dirt */


/*
 * Function:    safely_load_master_file
 * Description: This safely loads the master file if it hasn't already
 *              been loaded. Otherwise, it just returns the existing
 *              master file. If the file is not loadable, then it
 *              simply returns 0
 * Argument:    filename of the file to load
 */
public object
safely_load_master_file(string filename)
{
    object master_obj;
    if (!objectp(master_obj = find_object(filename)))
    {
        LOAD_ERR(filename);
        master_obj = find_object(filename);
    }
    
    return master_obj;
} /* safely_load_master_file */