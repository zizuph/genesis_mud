/*
 *  /d/Sparkle/area/city/rooms/streets/center_e.c
 *
 *  These are the city streets of Sparkle. Refer to outdoor_room.c for
 *  functionality.
 *
 *  Created June 2009, by Cooper Sherry (Gorboth)
 *    - Much credit and thanks to Styles for his inspirational city
 *      design concepts.
 */
#pragma strict_types

#include "../../defs.h"
inherit ROOMS_DIR + "outdoor_room";


/* Prototpyes */
public void        create_sparkle();


/*
 * Function name:        create_sparkle
 * Description  :        set up the room with area presets
 */
public void
create_sparkle()
{
    set_quadrant("center");
    set_street(STREET_CENTER);

    set_short_extra("A towering building is to the West. South is"
      + " an Adventurer's Guild");
    set_long_extra("Rounding a bend here, the street is bordered by"
      + " two important looking establishments. West, a towering building"
      + " frowns down onto the area. An ornamented platinum sign has"
      + " been placed before a pathway that leads toward its grand"
      + " entrance. The building to the south, though somewhat less regal,"
      + " is still quite imposing. A painted wooden sign swings from"
      + " a signpost before its doors.");

    try_item( ({ "bend", "bend in the road", "bend in the street" }),
        "The road turns north toward the city gates and east toward"
      + " the distant docks here.\n");
    try_item( ({ "distant dock", "distant docks" }),
        "They are a ways off to the east, yet.\n");
    try_item( ({ "establishments", "establishment",
                 "important establishment", "important establishments",
                 "important looking establishment",
                 "important looking establishments" }),
        "What makes something seem important, I wonder? Well, the"
      + " building to the west is just so elaborate and grand, it looks"
      + " as if some sort of royalty could exist there. The building"
      + " to the south, however, looks both friendly and ... well, it"
      + " just seems to call to you.\n");
    try_item( ({ "west", "western building", "west building",
                 "western building", "building to the west",
                 "towering building", "museum", "mvsevm",
                 "museum of genesis", "mvsevm of genesis",
                 "sparkle museum", "sparkle mvsevm",
                 "museum of events", "mvsevm of events" }),
        "This building is simply huge! Embellished beyond almost"
      + " anything you have ever laid eyes upon, it is clear that"
      + " someone feels this building deserves every spare ounce of"
      + " money that can be thrown at it. Surely within such a structure"
      + " are things of great worth.\n");
    try_item( ({ "south", "southern building", "building to the south",
                 "south building", "imposing building",
                 "wood-framed building", "wood building",
                 "framed building", "guild", "adventurer guild",
                 "adventurers guild", "adventurer guild of sparkle",
                 "adventurers guild of sparkle",
                 "sparkle adventurer guild", "sparkle adventurers guild",
                 "large building", "rugged building",
                 "extremely large building", "large and rugged building",
                 "timber-framed building",
                 "large and rugged timber-framed building",
                 "extremely large and rugged timber-framed building" }),
        "An extremely large and rugged timber-framed building is"
      + " just to the south of the road. This is the Adventurer Guild"
      + " of Sparkle. Anyone starting out in the world would be well-"
      + " advised to spend a great deal of time in such places learning"
      + " the skills they will need to find and make their fortunes in"
      + " the wide world.\n");
    try_item( ({ "post", "signpost", "sign post" }),
        "A painted wooden sign swings from it. Perhaps you should"
      + " give it a read?\n");
    try_item( ({ "door", "doors", "doors of the guild",
                 "doors of the building",
                 "doors of the adventurer guild",
                 "doors of the adventurers guild" }),
        "The doors are built from the same timbers which frame the rest"
      + " of the building. They look quite sturdy, yet inviting.\n");
    add_cmd_item( ({ "door", "doors", "the door", "the doors" }),
                  ({ "open" }),
        "The doors already stand open.\n");
    add_cmd_item( ({ "door", "doors", "the door", "the doors" }),
                  ({ "close", "shut" }),
        "You close the doors, but someone from inside opens them"
      + " again.\n");
    add_cmd_item( ({ "door", "doors", "the door", "the doors", "lock" }),
                  ({ "lock", "unlock", "pick", "lockpick" }),
        "You don't see any lock on the doors.\n");
    try_item( ({ "entrance", "entry", "entrance to the museum",
                 "entrance to the mvsevm", "museum entrance",
                 "mvsevm entrance", "grand entrance" }),
        "It looks as if more money was spent on the entrance to this"
      + " building alone than would be spent on a standard house in its"
      + " entirety!\n");
    try_item( ({ "sign", "signs" }),
        "Examine which sign? The ornamented platinum sign and the"
      + " painted wooden sign are both nearby.\n");
    try_item( ({ "ornamented platinum sign", "ornamented sign",
                 "platinum sign", "west sign", "western sign",
                 "sign to the west" }), "@@exa_sign|sign_museum@@");
    try_item( ({ "painted wooden sign", "painted sign",
                 "wooden sign", "wood sign", "painted wood sign",
                 "south sign", "southern sign", "sign to the south" }),
                 "@@exa_sign|sign_adventurers_guild@@");
    add_cmd_item( ({ "sign", "signs", "the sign", "the signs" }),
                  ({ "read" }),
        "Read which sign? The ornamented platinum sign and the"
      + " painted wooden sign are both nearby.\n");
    add_cmd_item( ({ "ornamented platinum sign", "ornamented sign",
                     "platinum sign", "the ornamented platinum sign",
                     "the ornamented sign", "the platinum sign",
                     "west sign", "western sign", "sign to the west",
                     "the west sign", "the western sign",
                     "the sign to the west", "museum sign",
                     "the museum sign" }),
                  ({ "read" }),
        "@@exa_sign|sign_museum@@");
    add_cmd_item( ({ "painted wooden sign", "the painted wooden sign",
                     "wooden sign", "the wooden sign",
                     "painted sign", "the painted sign",
                     "wooden sign", "the wooden sign",
                     "wood sign", "the wood sign",
                     "painted wood sign", "the painted wood sign",
                     "south sign", "the south sign",
                     "southern sign", "the southern sign",
                     "sign to the south", "the sign to the south",
                     "signpost", "post", "the signpost", "the post",
                     "guild sign", "the guild sign",
                     "adventurer guild sign", "the adventurer guild sign",
                     "adventurers guild sign", "the adventurers guild sign",
                     "adventurer's guild sign",
                     "the adventurer's guild sign" }),
                  ({ "read" }),
        "@@exa_sign|sign_adventurers_guild@@");

    add_center_items();

    add_tell("Sunlight gleams off of the building to the west.\n");
    add_tell("A cart loaded with goods rounds the corner and proceeds"
      + " east toward the docks.\n");
    add_tell("A bird passes overhead, disappearing behind the steeple"
      + " of the church.\n");
    add_tell("A few clouds drift by overhead.\n");

    add_exit("center_d", "north");
    add_exit("center_f", "east");
    add_exit("/d/Genesis/ateam/aoe/museum/room/entrance", "west");
    add_exit("/d/Genesis/start/human/town/adv_guild", "south");
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
    string  sign = ((arg == "sign_museum")
                 ? "museum" : "adventurer guild");

    /* A check for the sign rating quest */
    check_rating_form(this_player(), sign);

    return "The sign reads:\n\n"
      + read_file(TEXT_DIR + arg);
} /* exa_sign */