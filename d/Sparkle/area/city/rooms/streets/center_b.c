/*
 *  /d/Sparkle/area/city/rooms/streets/center_b.c
 *
 *  Here Old Sparkle Road travels past the public notary.
 *
 *  Created June 2009, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

#include "../../defs.h"
inherit ROOMS_DIR + "outdoor_room";

#include <macros.h>


/* Prototpyes */
public void        create_sparkle();
public string      exa_sign(string arg);
public int         check_exit();


/* Global Variables */
public string     *allowed_persons = ({ "gorbyjr",
                                        "gorbjr",
                                        "kitriana",
                                        "kellonjr", });



/*
 * Function name:        create_sparkle
 * Description  :        set up the room with area presets
 */
public void
create_sparkle()
{
    set_quadrant("center");
    set_street(STREET_CENTER);

    set_short_extra("The Archives of Genesis are just to the west, and"
      + " a shop is north of here");

    set_long_extra("The street rounds a corner here, passing by"
      + " a very official looking building to the west, and a small"
      + " shop to the north. A bit to the southwest, some construction"
      + " project is visible. A well-framed sign"
      + " has been placed before the building to the west, and there"
      + " is a polished green sign hanging just before you above the"
      + " entrance on the shop to the north.");

    try_item( ({ "corner", "bend", "bend in the road" }),
        "The street travels east and south here, rounding the bend"
      + " as it passes by a shop, an official-looking building,"
      + " and some construction.\n");
    try_item( ({ "project", "projects", "various projects",
                 "construction project", "construction projects",
                 "various construction projects",
                 "zone", "construction zone", "work area" }),
        "There is a work area just to the southwest. It appears that many"
      + " new features are being gradually added to the city.\n");
    try_item( ({ "feature", "features", "new feature",
                 "new features" }),
        "No telling what they will be yet. Give it time.\n");
    try_item( ({ "building", "official building",
                 "very official building", "official looking building",
                 "very official looking building", "archives",
                 "archives of genesis", "notary", "public notary",
                 "notary public" }),
        "A well-framed sign has been placed before the building"
      + " indicating that the Archives of Genesis can be found"
      + " within. It is not unusual to find a notary public in such"
      + " a place as well.\n");
    try_item( ({ "shop", "small shop", "enchanter", "enchanters shop",
                 "enchanter's", "enchanter's shop", "workshop",
                 "enchanters workshop", "enchanter's workshop",
                 "north", "shop to the north" }),
        "The polished green sign hung above the entrance to this rather"
      + " small and simple looking structure indicates that this is an"
      + " Enchanter's Worskshop.\n");
    try_item( ({ "structure", "small structure", "simple structure",
                 "simple looking structure",
                 "small and simple looking structure" }),
        "There is nothing about the shop to the north that suggests"
      + " anything but a simple and honest business.\n");
    try_item( ({ "entrance", "shop entrance", "workshop entrance",
                 "entrance to the north", "north entrance",
                 "entrance on the shop",
                 "entrance on the shop to the north" }),
        "It looks most inviting.\n");
    try_item( ({ "fountain" }),
        "The fountain is a ways to the east. You can't see much from"
      + " here.\n");

    add_center_items();

    add_tell("A young page walks out of the building to the west and"
      + " continues out of sight down the road.\n");
    add_tell("A few birds land on a nearby rooftop, and then abruptly"
      + " launch into flight and are gone.\n");
    add_tell("Sunlight glints off a fountain down the street to the"
      + " east.\n");
    add_tell("Clouds drift lazily overhead.\n");
    add_tell("A few official looking persons pass you and enter the"
      + " building to the west.\n");
    try_item( ({ "sign", "signs" }),
        "Examine which sign? The polished green sign and the"
      + " well-framed sign are both nearby.\n");

    add_item( ({ "polished sign", "green sign", "polished green sign",
                 "north sign", "enchanter sign", "enchanters sign",
                 "enchanter's sign", "enchanters shop sign",
                 "enchanter's shop sign" }),
                 "@@exa_sign|sign_enchanter@@");

    add_cmd_item( ({ "sign", "signs", "the sign", "the signs" }),
                  ({ "read" }),
        "Read which sign? The polished green sign and the"
      + " well-framed sign are both nearby.\n");

    add_cmd_item( ({ "polished sign", "the polished sign",
                     "green sign", "the green sign",
                     "north sign", "the north sign",
                     "enchanter sign", "the enchanter sign",
                     "enchanters sign", "the enchanters sign",
                     "enchanter's sign", "the enchanter's sign",
                     "enchanters shop sign", "the enchanters shop sign",
                     "enchanter's shop sign", "the enchanter's shop sign",
                     "polished green sign", "the polished green sign" }),
                  ({ "read" }),
                     "@@exa_sign|sign_enchanter@@");

    add_item( ({ "well-framed sign", "west sign", "notary sign",
                 "archive sign", "archives sign",
                 "framed sign" }), "@@exa_sign|sign_notary@@");

    add_cmd_item( ({ "framed sign",
                     "the framed sign", "well-framed sign",
                     "west sign", "the west sign",
                     "archive sign", "the archive sign",
                     "notary sign", "the notary sign",
                     "archives sign", "the archives sign",
                     "the well-framed sign" }),
                  ({ "read" }), "@@exa_sign|sign_notary@@");

    add_exit(INSIDE_DIR + "enchanter", "north", check_exit, 1, 0);
    add_exit("center_a", "east");
    add_exit("center_c", "south");
    add_exit("/d/Genesis/start/human/town/notary_room", "west");
} /* create_sparkle */


/*
 * Function name:        exa_sign
 * Description  :        provide a description of the sign that is
 *                       hanging here
 * Arguments    :        string arg - which sign do we want?
 * Returns      :        string - the text to display
 */
public string
exa_sign(string arg)
{
    string  sign = ((arg == "sign_enchanter")
                 ? "enchanter's shop" : "archives");

    /* A check for the sign rating quest */
    check_rating_form(this_player(), sign);

    return "The sign reads:\n\n"
      + read_file(TEXT_DIR + arg);
} /* exa_sign */


/*
 * Function name:        check_exit
 * Description  :        see if players can use this exit
 * Returns      :        0 - let the player move this way
 *                       
 * This is a way to tell Gorboth that someone is in the shop.
 */
public int
check_exit()
{
    return 0;

} /* check_exit */
