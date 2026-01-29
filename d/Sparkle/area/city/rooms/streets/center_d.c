/*
 *  /d/Sparkle/area/city/rooms/streets/center_d.c
 *
 *  This length of road will eventually look onto the Headquarters of
 *  the City Guard. For now, its just a connecting room.
 *
 *  Created June 2009, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

#include "../../defs.h"
inherit ROOMS_DIR + "outdoor_room";

#include <time.h>

/* Prototpyes */
public void        create_sparkle();
public void        leaf_search();
public int         check_exit();


/* Definitions */
#define            SPARKLE_I_LEAF_PROP ("_sparkle_i_leaf_prop")

/*
 * Function name:        create_sparkle
 * Description  :        set up the room with area presets
 */
public void
create_sparkle()
{
    set_quadrant("center");
    set_street(STREET_CENTER);

    set_short_extra("A large construction zone is just to the west");
    set_long_extra("The street nears the old city gates a short"
      + " distance to the north. The sides of the First Church"
      + " of Sparkle run alongside the road to the east, and a"
      + " large construction project is taking place just to the"
      + " west.");

    try_item( ({ "zone", "construction", "construction zone",
                 "large construction zone", "project",
                 "large project", "construction project",
                 "large construction project" }),
        "The frame of a very large building is being erected to the"
      + " west. One can only imagine what it will someday become.\n");
    try_item( ({ "frame", "building frame", "frame of a building",
                 "frame of a large building",
                 "frame of a very large building", "west" }),
        "Looks sturdy! Big plans are at hand in this city.\n");
    try_item( ({ "plans", "plan", "big plan", "big plans" }),
        "At hand!\n");
    try_item( ({ "hand", "at hand" }),
        "Big plans!\n");
    try_item( ({ "sides", "side", "sides of the church",
                 "side of the church",
                 "sides of the first church of sparkle",
                 "side of the first church of sparkle", "east" }),
        "The church is immense, taking up more than a city block. It"
      + " towers over the street just to the east.\n");
    try_item( ({ "city block", "block", "blocks", "city blocks" }),
        "Here in the Old City, things aren't organized quite that way,"
      + " but you can still get a fairly good sense of general scale.\n");
    try_item( ({ "scale", "sense of scale" }),
        "Some buildings are bigger than others.\n");
    try_item( ({ "leaf", "leaves" }),
        "A few leaves are scattered along the road here. Perhaps there"
      + " are some trees nearby.\n");
    try_item( ({ "tree", "trees" }),
        "There aren't any in sight, but you do see a few leaves"
      + " scattered about.\n");

    add_delay_cmd_item( ({ "leaves", "leaf" }),
                        "search",
                        "searching though some nearby leaves",
                        10,
                        "You begin searching through some of the"
                      + " nearby leaves.\n",
                        "@@leaf_search@@");

    add_center_items();

    add_tell("A horse-drawn carriage rumbles past heading south.\n");
    add_tell("A slight breeze blows a few leaves down the road.\n");
    add_tell("The barking of a dog sounds in the distance.\n");
    add_tell("A few birds land on the side of the church, peer down at"
      + " the road, and then launch back into flight and are gone.\n");

    add_exit("center_c", "north");
    add_exit("/d/Genesis/ateam/aoe/events/halloween2020/rooms/event_central",
             "west", check_exit, 1, 0);
    add_exit("center_e", "south");
} /* create_sparkle */


/*
 * Function name:        leaf_search
 * Description  :        allow players to occasionally get lucky
 *                       when searching through the leaves
 */
public void
leaf_search()
{
    object  coin;
    string  again = "";
    int     searched = this_player()->query_prop(SPARKLE_I_LEAF_PROP);

    if (random(100)) /* a 99% chance of finding nothing */
    {
        if (searched)
        {
            write("You search through the leaves one more time, but"
              + " find nothing.\n");

            again = " again";
        }
        else
        {
            write("You get your hands a bit dirty, but otherwise find"
              + " nothing interesting in the leaves.\n");
        }

        searched++;
        this_player()->add_prop(SPARKLE_I_LEAF_PROP, searched);

        write_file(LOG_DIR + "leaves",
            TIME2FORMAT(time(), "mm/dd/yyyy") + " ("
          + ctime(time())[11..18] + ") "
          + capitalize(this_player()->query_real_name()) 
          + " searched the leaves" + again + ". " + searched + "\n");

        return;
    }

    write("You find a platinum coin beneath the leaves! Someone must"
      + " have dropped it. Oh well ... their loss, your gain!\n");

    coin = clone_object("/std/coins");
    coin->set_coin_type("platinum");

    this_player()->add_prop(SPARKLE_I_LEAF_PROP, 1);

    write_file(LOG_DIR + "leaves",
        TIME2FORMAT(time(), "mm/dd/yyyy") + " ("
      + ctime(time())[11..18] + ") "
      + capitalize(this_player()->query_real_name()) 
      + " found a platinum coin in the leaves!\n");

    if (!coin->move(this_player()))
    {
        return;
    }

    /* We get here if the player is too burdened to carry it. */
    write("Oops! You dropped it!\n");
    coin->move(this_object());

    return;
} /* leaf_search */


/*
 * Function name:        check_exit
 * Description  :        Send the players a message when they enter
 *                       the Village Green.
 * Returns      :        int 1 - prevent exit
 *                           0 - allow exit
 */
public int
check_exit()
{
    int    event_end_time = 1605394800;
    int    time_remaining = event_end_time - time();

    if (time_remaining < 1)
    {
        this_player()->catch_tell(
            "You wander onto the Village Green, but it doesn't"
          + " appear as if there is anything going on there now,"
          + " so you head back to the street.\n");
        return 1;
    }

    this_player()->catch_tell("\nA spooky voice speaks into your mind,"
      + " saying: NooooOOOoooo!! The event will be ending at midnight"
      + " tooooooonight, and sooooooo I've decided toooooo stop anyone"
      + " else from creating neoooooew costuooooomes or candy!"
      + " Now is the time tooooo make sure yoooour sorting is just the"
      + " way yooooou want it soooo that yooooour true favorites are"
      + " the ones whooooo get credit at the end of the event!!\n\n"
      + "You can't seem to enter the Village Green now.\n");

    return 1;
} /* check_exit */

