/*
 *  /d/Genesis/start/human/town/pier2
 *
 *  This is one of the many piers on the Sparkle wharf that ships
 *  visit to book passage to distant lands. Here there is some special
 *  functionality to govern whether or not a player is allowed into
 *  the pub if they have been kicked out by the bouncer.
 *
 *  Created, ??? by ???
 *
 *  Modification log:
 *    - Aug 12, 2019 (Gorboth) - General code revision,
 *                               Added pub entry checks,
 *                               General rewrite to the room text and
 *                               items.
 */
#pragma strict_types

#include <stdproperties.h>
#include <macros.h>

#include "town.h"
#include "/d/Genesis/gsl_ships/ships.h"

inherit STDPIER;

/* Global Variables */
public string    Tavern_File = 
                   "/d/Sparkle/area/city/rooms/inside/sparkle_pub";


/*
 * Function name:        create_room
 * Description  :        set up the room
 */
public void
create_room()
{
    set_short("Berth 2 - Pelargir");
    set_long("Outside the Boar's Head Tavern.\n"+
        "Much noise (some of it cheerful) greets you from the west where"
      + " this pub has established itself as the best"
      + " local watering hole for the thirsty adventurer. The piers"
      + " extend from view along the way east and south.\n"
      + "There is a sign here that reads: Berth 2 - Pelargir.\n");

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_S_MAP_FILE, "sparkle_city_genesis.txt");

    add_exit(THIS_DIR + "ship_info", "north", 0);
    add_exit(THIS_DIR + "pier3", "south",     0);
    add_exit(THIS_DIR + "pier1", "east",      0);
    add_exit(Tavern_File, "west", "@@check_bouncer@@", 1, 0);

    add_item( ({ "pier", "piers" }),
         "It is one of the piers of the harbour where "
       + "ships can land so passengers can board or disembark and cargo "
       + "can be loaded or unloaded. Wooden planks lie on thick wooden "
       + "posts that reach down into the water. Other piers are south and "
       + "east of here.\n");
    add_item( ({ "water", "posts", }),
      "The water here in the harbour is murky and smells pretty bad. The "
      + "thick posts of the pier reach down into the water.\n");
    add_item( ({ "planks", "ground", "floor", }), 
      "Wooden planks cover the ground here. They rest on thick posts "
      + "that reach down into the water of the harbour.\n");
    add_item( ({ "pub", "tavern", "boar head", "boars head",
                 "boar's head", "boar head tavern", "boars head tavern",
                 "boar's head tavern", "west" }),
        "The tavern looks lively indeed! Perhaps you should venture"
      + " inside to see for yourself.\n");
    add_item( ({ "watering hole", "hole", "local watering hole" }),
        "Every town needs one. You could make this one yours if you"
      + " wanted to become a regular.\n");
    add_item( ({ "thirsty adventurer", "adventurer", "adventurers",
                 "thirsty adventurers", "regular", "regulars" }),
        "Maybe you are one yourself?\n");
    add_item( ({ "much noise", "noise" }),
        "I suppose you'd expect that from a pub in this part of town.\n");
    add_item( ({ "cheerful noise" }),
        "Mostly cheerful. Occasionally what you hear sounds less so.\n");

    add_item( ({"sign" }), "Berth 2 - Pelargir.\n");

//  add_pier_entry(MASTER_OB(TO), "Sparkle", "Ship to Pelargir");
//  initialize_pier();

    setuid();
    seteuid(getuid());
} /* create_room */


/*
 * Function name:        check_bouncer
 * Description  :        Check to see if this player is welcome in
 *                       the tavern
 * Returns      :        int - 1: not welcome, 0: welcome
 */
public int
check_bouncer()
{
    int     banned = 
                find_object(Tavern_File)->judge_entry(this_player());

    if (!banned)
    {
        find_living("gorboth")->catch_tell("\n\t\t----*** "
            + capitalize(this_player()->query_real_name())
            + " enters the Tavern!! ***----\n\n");
    }
    
    return banned;
} /* check_bouncer */
