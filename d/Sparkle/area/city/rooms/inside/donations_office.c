/*
 *  /d/Sparkle/area/city/rooms/inside/donation_office.c
 *
 *  This is the new (2021) donations office, containing the club
 *  for players who donate real money through Patreon.com.
 *  The old donations office, now called the "special campaigns
 *  room" is found downstairs from this room. South leads back 
 *  out to the market square.
 *
 *  Created May 2021, by Cherek
 */
#pragma strict_types

inherit "/std/room";

#include <macros.h>
#include <stdproperties.h>
#include "../../defs.h"

/* Prototypes */
public void        create_room();

/*
 * Function name:        create_room
 * Description  :        the room constructor
 */
public void
create_room()
{
    set_short("In the Donations Office");
    set_long("The office of the treasurer of Genesis is comfortable, " +
      "yet not luxurious. Skilled craftsmen created a functional " +
      "environment without rich decorations. Smooth wooden panels cover " +
      "the brick walls and a red carpet covers the stone slabbed floor. " +
      "An iron strongbox, bolted to the floor, is placed behind the old " +
      "oak desk. The oak desk is prominently situated against the side " +
      "wall.\n\n");

    add_item( ({ "place", "here", "area", "store",
                 "place of business", "room", "shop",
                 "enchanters shop", "enchanter's shop" }),
        "This is the Enchanter's Shop. You'll have to look around a bit"
      + " to get a sense of the place.\n");
    add_item( ({ "business" }),
        "Perhaps you'd like to engage in some yourself?\n");
    add_item( ({ "energy", "palpable energy", "strange energy",
                 "feeling", "strange palpable energy",
                 "strange, palpable energy" }),
        "It is hard to pinpoint exactly what this feeling is all about."
      + " There is a sense of the arcane here, as if the mere presence"
      + " of certain practices and knowledge have changed the aura of"
      + " the surroundings.\n");
    add_item( ({ "arcane", "sense", "sense of the arcane", "aura",
                 "surroundings", "aura of the surroundings" }),
        "It feels ... tingly.\n");
    add_item( ({ "tingle", "tingly feeling" }),
        "Tingle, tingle, tingle!\n");
    add_item( ({ "air" }),
        "The air in here is heavy with strange energy.\n");
    add_item( ({ "arcane item", "arcane items" }),
        "Much in here seems foreign to your experience and knowledge."
      + " A poster on the wall attacts your attention, however.\n");
    add_item( ({ "acrane image", "image", "images", "arcane images" }),
        "The images on the walls are most beguiling.\n");
    add_item( ({ "table", "stone table", "large table",
                 "large stone table" }),
        "The table is perfectly clean and there is nothing upon it.\n");
    add_item( ({ "stone" }),
        "The stone of the table appears to be white marble.\n");
    add_item( ({ "marble", "white marble" }),
        "The marble that makes up the stone table is polished and"
      + " spotlessly clean.\n");
    add_item( ({ "wall", "walls" }),
        "You notice a poster which hangs prominently on the wall.\n");
    add_item( ({ "shelf", "shelves", "many shelves" }),
        "The shelves are stuffed with very old looking scrolls, books,"
      + " and papers.\n");
    add_item( ({ "scroll", "scrolls", "book", "books", "paper",
                 "papers" }),
        "The contents of the shelves are beyond your reach behind the"
      + " counter.\n");
    add_item( ({ "counter" }),
        "The counter separates the front of the shop from the work area"
      + " toward the back, where the enchanter usually stands.\n");
    add_item( ({ "work area" }),
        "It is off limits.\n");
    add_item( ({ "stair", "staircase", "stairs", "spiral stair",
                 "steps", "spiral staircase", "northeast",
                 "northeast corner", "corner" }),
        "Spiral stairs in the northeast corner lead down through a hole"
      + " in the floor.\n");
    add_item( ({ "hole", "hole in the floor" }),
        "The hole in the floor allows access via the spiral staircase to"
      + " some lower level of the shop.\n");
    add_item( ({ "lower level", "lower level of the shop" }),
        "You'd probably need to climb down the stairs to know more.\n");
    add_item( ({ "door", "doorway", "south",
                 "doorway to the south" }),
        "The door opens back up onto the street.\n");
    add_item( ({ "street" }),
        "You could head south out of the shop to see it again if you"
      + " wished.\n");
    add_item( ({ "floor", "down", "ground" }),
        "The floor is neatly swept.\n");
    add_item( ({ "ceiling", "up", "roof" }),
        "The ceiling slopes upward high above your head.\n");
    add_item( ({ "sky" }),
        "The sky is not visible here, indoors.\n");

    add_item( ({ "poster", "prominent poster",
                 "prominently placed poster" }),
        &read_file("/d/Sparkle/area/orc_temple/text/enchanter_poster.txt"));

    add_cmd_item( ({ "poster", "the poster" }),
                  ({ "read", }), 
        &read_file("/d/Sparkle/area/orc_temple/text/enchanter_poster.txt"));

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_S_MAP_FILE, "sparkle_city_current.txt");
    add_prop(ROOM_M_NO_STEAL,
        "Just as you are reaching out to make your attempt at thievery,"
      + " you feel as though your hand is slapped by some invisible force."
      + " There must be some powerful enchantments in this room to prevent"
      + " such an action.\n");

      add_exit(STREET_DIR + "market_square", "south");
      add_exit("/d/Genesis/obj/donation/office", "down");

} /* create_room */
