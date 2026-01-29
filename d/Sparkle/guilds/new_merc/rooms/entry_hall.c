/*
 *  /d/Sparkle/guilds/new_merc/entry_hall.c
 *
 *  This room is the nexus of the main floor of the Mercenary guild,
 *  connecting to all the major rooms on the level.
 *
 *  Created May 2009, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../merc_defs.h"

inherit MERC_ROOM_BASE;

#include <stdproperties.h>

/* Prototypes */
public void        create_merc_room();
public int         check_exit();


/*
 * Function name:        create_merc_room
 * Description  :        set up the room with area presets
 */
public void
create_merc_room()
{
    object   door;

    set_short("in the entry hall on the main floor of the Mercenary Guild");
    set_long("You stand in a wide hall which occupies a large area"
      + " of the ground floor of the lodge. Many rooms look onto this"
      + " central coming and going area which is constantly visited by"
      + " the members of the guild, most of whom arrive from the main"
      + " entrance to the east and head immediately north into the large"
      + " feasting hall. Through an archway to the west, many weapon and"
      + " armour racks are visible.\n\n");

    try_item( ({ "here", "area", "hall", "wide hall", "entry hall",
                 "room" }),
        "This hall has a very spacious feel, opening north onto the"
      + " feasting hall and east onto the entry.\n");
    try_item( ({ "large area", "ground floor",
                 "ground floor of the lodge", "main floor",
                 "main floor of the guild",
                 "main floor of the lodge",
                 "main floor of the mercenary guild" }),
        "The floorspace shared by this entry hall, the feasting area,"
      + " and the main entry to the east comprise much of the area of"
      + " the ground floor of the lodge.\n");
    try_item( ({ "floorspace" }),
        "It always feels good when rooms open onto one another without"
      + " doorways. Gives one a sense of connectivity with the other"
      + " parts of the building.\n");
    try_item( ({ "other parts", "other part",
                 "other part of the building",
                 "other parts of the building" }),
        "There are quite a few of them. Go forth! Explore!\n");
    try_item( ({ "rooms", "many rooms" }),
        "A door leads through the wall to the south. West, you see a"
      + " room that looks to be used for the guild racks. A feasting"
      + " hall is to the north. East lies the main entrance to the"
      + " lodge.\n");
    try_item( ({ "central area", "coming and going area",
                 "central coming and going area" }),
        "People come, people go .. much like you yourself are doing.\n");
    try_item( ({ "member", "members", "guild member", "guild members",
                 "members of the guild", "member of the guild" }),
        "They mostly seem headed somewhere in the lodge, though a few"
      + " occasionally loiter to talk to one another.\n");
    try_item( ({ "loiterer", "loiterers" }),
        "The main loiterer here is you, wouldn't you say?\n");
    try_item( ({ "east", "entrance", "main entrance", "guild entrance",
                 "entry way", "main entry way",
                 "main entrance to the guild", "entry", "guild entry", }),
        "Heading east would take you to the entrance, and outside if you"
      + " decided to keep going.\n");
    try_item( ({ "north", "feasting hall", "large feasting hall",
                 "mess hall", "mess area", "eating area", "eating room",
                 "dining room", "dining area" }),
        "Just to the north the entry hall opens onto a dining room which"
      + " looks like it could host quite the feast.\n");
    try_item( ({ "west", "arch", "archway", "rack room", "rack area",
                 "armour rack", "armour racks", "armor rack",
                 "armor racks", "weapon rack", "weapon racks",
                 "guild rack", "guild racks", "drop room", "droproom",
                 "arch to the west", "archway to the west",
                 "western archway", "western arch" }),
        "You can see a number of racks through the archway to the west,"
      + " beyond a few guards who control access to the chamber.\n");
    try_item( ({ "guard", "guards", "few guards" }),
        "They look like they mean business.\n");
    try_item( ({ "chamber", "chamber to the west" }),
        "The chamber to the west appears to be an armoury.\n");
    try_item( ({ "armoury" }),
        "You can't see much from here.\n");
    try_item( ({ "south wall", "wall to the south", "southern wall" }),
        "The wall to the south separates this fairly noisy part of the"
      + " lodge with the sleeping quarters.\n");
    try_item( ({ "noisy part of the lodge", "noise",
                 "fairly noisy part of the lodge" }),
        "Yes, a bit. No need to keep your voice down, though, that is"
      + " what the wall to the south is for.\n");
    try_item( ({ "quarter", "sleeping quarter", "sleeping quarters",
                 "quarters" }),
        "They lie through the door to the south.\n");

    add_indoor_view();
    add_indoor_lodge_view();

    add_prop(ROOM_I_INSIDE, 1);

    add_exit("mess_hall", "north");
    add_exit("entrance", "east");
    add_exit("common_rack", "west", check_exit, 1, 0);

    set_no_exit_msg( ({ "northwest", "northeast", "southeast",
                        "southwest" }),
        "You poke around the corners of the hall, eventually wandering"
      + " back to where you stood.\n");

    setuid();
    seteuid(getuid());

    door = clone_object(DOORS_DIR + "neutral_n");
    door->move(this_object());
} /* create_room */


/*
 * Function name:        check_exit
 * Description  :        stop the player from going here if they
 *                       aren't an evil Mercenary
 * Returns      :        int - 1: prevent passage
 *                             0: allow passage
 */
public int
check_exit()
{
    if (!IS_MERC(this_player()))
    {
        if (this_player()->query_wiz_level())
        {
            write("The guards frown, but let you pass because you are"
              + " a wizard.\n");
            return 0;
        }

        write("The guards draw their blades as you approach, and one"
          + " says: You're no Mercenary! How did you get in"
          + " here? You should leave this lodge!\n");
        write("The guard stops you from going that way.\n");
        return 1;
    }

    if (this_player()->query_alignment() > -620 &&
        this_player()->query_alignment() < 550)
    {
        return 0;
    }

    if (this_player()->query_wiz_level())
    {
        write("The guards frown, but let you pass because you are"
          + " a wizard.\n");
        return 0;
    }

    if (this_player()->query_invis())
    {
        write("A rugged-looking guard looms before you"
          + " in the archway. Though he doesn't see you, he blocks"
          + " your passage, peering suspiciously into the"
          + " hall.\n");
        write("You are unable to proceed that direction.\n");
        return 1;
    }

    write("The guards draw their blades and step before you."
      + " One of them says: This armoury is for those of us who"
      + " aren't so biased as you. You'll find your sort of people"
      + " on the second floor. Go look for what you need up there.\n");
    write("The guard stops you from going that way.\n");
    return 1;
} /* check_exit */
