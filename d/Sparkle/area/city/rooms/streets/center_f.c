/*
 *  /d/Sparkle/area/city/rooms/streets/center_f.c
 *
 *  This room is EXTREMELY important. It is here that players first
 *  enter the game after leaving the church. This room provides them
 *  with a magic map.
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
public string      exa_sign(string arg);
public int         check_exit();


/*
 * Function name:        create_sparkle
 * Description  :        set up the room with area presets
 */
public void
create_sparkle()
{
    set_quadrant("center");
    set_street(STREET_CENTER);

    set_short_extra("North is a large church. A library is to the south");
    set_long_extra("Birds flutter and swoop to land on the enormous"
      + " rooftop of the First Church of Sparkle which opens its"
      + " doors to all who would seek sanctuary just to the north."
      + " All around, the sounds, smells, and sights of a busy city"
      + " greet your senses. An impressive building in its own right,"
      + " the great Library is just to the south.");

    try_item( ({ "bird", "birds" }),
        "They appear to be sparrows. They seem to like the roof of the"
      + " church for some reason, and are gathering there, strutting"
      + " around on the shingles.\n");
    try_item( ({ "sparrow", "sparrows" }),
        "What are they doing up there? They strut, they peck ... it is"
      + " a bit unnerving.\n");
    try_item( ({ "rooftop", "roof", "roof of the church",
                 "rooftop of the church", "church roof",
                 "church rooftop",
                 "rooftop of the first church of sparkle" }),
        "Of all the rooftops within view, none are nearly so expansive"
      + " as that of the church.\n");
    try_item( ({ "shingle", "shingles" }),
        "The roof of the church is angled, but not terribly steeply."
      + " The birds seem to have no trouble strutting around up"
      + " there.\n");
    try_item( ({ "door", "doors", "church door", "church doors",
                 "door of the church", "doors of the church" }),
        "The doors of the church have been constructed in such a way"
      + " that each comprises half of a full arch. When closed, they"
      + " are quite beautiful to look at.\n");
    add_cmd_item( ({ "door", "doors", "church door", "church doors",
                     "door of the church", "doors of the church" }),
                  ({ "open" }),
        "The doors of the church are already open.\n");
    add_cmd_item( ({ "door", "doors", "church door", "church doors",
                     "door of the church", "doors of the church" }),
                  ({ "close", "shut" }),
        "The doors of the church remain open at all times. Some sort"
      + " of magical enchantment prevents you from closing them.\n");
    add_cmd_item( ({ "door", "doors", "church door", "church doors",
                     "door of the church", "doors of the church" }),
                  ({ "lock", "unlock", "pick", "lockpick" }),
        "The doors of the church have no lock or key. They are open"
      + " to all - always.\n");
    add_item( ({ "church", "first church", "first church of sparkle",
                     "sparkle church", "north building",
                     "northern building", "building to the north" }),
        "The First Church of Sparkle enjoys a distinguished heritage"
      + " as one of the oldest buildings in all of Genesis. It is an"
      + " enormous building, rising high above where its steeple"
      + " pierces the skyline above the city. An elegant sign has"
      + " been hung on its outer walls.\n");
    add_item( ({ "outer wall", "outer walls", "outer wall of the church",
                 "outer walls of the church" }),
        "An elegant sign hangs there.\n");
    add_item( ({ "enormous building" }),
        "Quite so. The church is simply huge!\n");
    add_item( ({ "sound", "sounds" }),
        "The city hums with activity. The sounds of talking people"
      + " in the streets mingle with the sounds of carts bumping along"
      + " the road. Birds chirp overhead, and the occasional bark of" 
      + " a dog sounds in the distance.\n");
    add_item( ({ "people", "talking people", "person", "talking person" }),
        "People come and go in this part of town. It is one of the"
      + " busiest places outside of the docks.\n");
    add_item( ({ "cart", "carts" }),
        "Carts often pass the church on their way to or from the docks.\n");
    add_item( ({ "dog", "bark", "bark of a dog", "dog bark", "dogs" }),
        "You don't see any dogs around here, but occasionally you do"
      + " hear one.\n");
    add_item( ({ "smell", "smells" }),
        "The scents of life and activity are all around. The briny"
      + " breeze from the sea blows in from the east part of the city"
      + " where the docks offer passage to many distant ports. Many"
      + " of the passing carts bear food goods which are being"
      + " delivered to local gentry or establishments for sale.\n");
    add_item( ({ "sea", "pen sea" }),
        "The sea is not visible from here. You'd need to travel east"
      + " toward the docks.\n");
    add_item( ({ "breeze", "briny breeze", "wind" }),
        "The wind has a salty smell when it blows from the east.\n");
    add_item( ({ "food", "goods", "food goods" }),
        "Perhaps you could find some of the places in town that sell"
      + " such items, and enjoy them yourself!\n");
    add_item( ({ "sight", "sights" }),
        "The city both beautiful and practical. Much is here to be seen"
      + " for those who wish to take the time.\n");
    add_item( ({ "impressive building", "library", "library of sparkle",
                 "sparkle library", "great library",
                 "great sparkle library", "great library of sparkle",
                 "south building", "southern building",
                 "building to the south" }),
        "The Great Sparkle Library has been intentionally built just"
      + " to the south of the church so that when new adventurers to"
      + " the lands make their first steps into the city, they might"
      + " have the chance to encounter this treasure trove of useful"
      + " information. By all means, feel free to enter it by travelling"
      + " south from here. A bold sign hangs beside the path leading"
      + " to its entrance.\n");
    add_item( ({ "entrance", "library entrance",
                 "entrance to the library" }),
        "It is just to the south. You can bet there is a lot to read"
      + " by heading that direction!\n");
    add_item( ({ "path", "pathway" }),
        "A short pathway leads up to the library. A bold sign has been"
      + " hung beside it.\n");

    add_center_items();

    try_item( ({ "sign", "signs" }),
        "Examine which sign? The elegant sign and the"
      + " bold sign are both nearby.\n");
    try_item( ({ "elegant sign", "north sign", "north sign",
                 "church sign", "northern sign", "sign to the north" }),
        "@@exa_sign|sign_church@@");
    try_item( ({ "bold sign", "library sign",
                 "south sign", "southern sign", "sign to the south" }),
                 "@@exa_sign|sign_library@@");
    add_cmd_item( ({ "sign", "signs" }),
                  ({ "read" }),
        "Read which sign? The elegant sign and the"
      + " bold sign are both nearby.\n");
    add_cmd_item( ({ "elegant sign", "the elegant sign",
                     "church sign", "the church sign",
                     "north sign", "northern sign", "sign to the north",
                     "the north sign", "the northern sign",
                     "the sign to the north", }),
                  ({ "read" }),
        "@@exa_sign|sign_church@@");
    add_cmd_item( ({ "bold sign", "the bold sign",
                     "library sign", "the library sign",
                     "south sign", "the south sign",
                     "southern sign", "the southern sign",
                     "sign to the south", "the sign to the south" }),
                  ({ "read" }),
        "@@exa_sign|sign_library@@");

    add_tell("A cart laden with goods rumbles past on its way from"
      + " the docks.\n");
    add_tell("Movement catches your eye, and you notice many birds walking"
      + " to one side of the church roof.\n");
    add_tell("A few old men walk out of the building to the south and"
      + " pass out of sight to the west, conversing all the while.\n");
    add_tell("A bird circles the steeple of the church and lands on the"
      + " roof.\n");
    add_tell("A breeze blows in from the east, smelling of salt.\n");

    add_exit("center_e", "west", check_exit, 1, 0);
    add_exit("/d/Genesis/start/human/town/church", "north", check_exit, 1, 0);
    add_exit("center_g", "east", check_exit, 1, 0);
    add_exit(CITY_DIR + "library/room/entrance", "south", check_exit, 1, 0);

    add_npc(NPC_DIR + "town_crier", 1, &->arm_me());
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
    string  sign = ((arg == "sign_church")
                 ? "church" : "library");

    /* A check for the sign rating quest */
    check_rating_form(this_player(), sign);

    return "The sign reads:\n\n"
      + read_file(TEXT_DIR + arg);
} /* exa_sign */


/*
 * Function name:        check_exit
 * Description  :        check to see if we want to make the player
 *                       notice the town crier before leaving
 * Returns      :        1 - block movement, 0 - let them leave
 */
public int
check_exit()
{
    object crier = present("_sparkle_town_crier_npc", this_object());

    if (!objectp(crier))
    {
        return 0;
    }

    return crier->crier_exit_check(this_player());
} /* check_exit */