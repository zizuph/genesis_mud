/*
 *  /d/Sparkle/area/city/rooms/streets/center_g.c
 *
 *  This is just west of the Church. The Bank is north and the Tower
 *  of Realms is to the south.
 *
 *  Created June 2009, by Cooper Sherry (Gorboth)
 *    - Much credit and thanks to Styles for his inspirational city
 *      design concepts.
 *
 *  FEB 2009: Added north exit to bank: Aeg 
 *  December 2015, Added yule tree, Cherek
 *  December 2016, Added autoloading of the Yule tree if the Wheel-Of-Fun 
 *  lottery is currently running.
 *  October 2018, Removed the code related to the Wheel-Of-Fun lottery 
 *  since it has been moved to the event folder instead.
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

    set_short_extra("The Bank of Sparkle is to the north. South is the"
      + " Tower of Realms");
    set_long_extra("Buildings unlike any you have ever seen border"
      + " the street here. A tower that seems impossibly tall rises"
      + " almost out of sight just to the south. This is the fabled"
      + " Tower of Realms, a destination point for many would-be"
      + " quest-solvers. North, all sorts of construction is taking"
      + " place on a large domed building that can, at best, be"
      + " described as utterly bizarre. A strange sign hangs on a"
      + " very unusual signpost in front of the building.");

    try_item( ({ "building", "buildings" }),
        "The buildings to the north and south are unmistakable. They"
      + " look nothing like other structures in the city.\n");
    try_item( ({ "building to the north", "bank", "bank of sparkle",
                 "sparkle bank", "gog", "g.o.g.", "gnomes of genesis",
                 "main branch", "gnomes of genesis main branch",
                 "gog main branch", "g.o.g. main branch",
                 "large building", "large domed building",
                 "domed building", "bizarre building",
                 "utterly bizarre building", "north", "north building",
                 "northern building", "building to the north" }),
        "Just to the north is the Bank of Genesis, though its fanatical"
      + " proprietors refer to it as the Gnomes of Genesis (G.O.G.) Main"
      + " Branch. While other races would probably look upon such a"
      + " structure with deep misgivings, this sort of construction is"
      + " standard practice for a Gnome. Cogs, gears, pistons, bells,"
      + " and (yes) numerous whistles are attached to the exterior of"
      + " the building in places where such things couldn't possibly have"
      + " any (good) purpose. Were it not for the monopoly these people"
      + " hold on the monetary system, such a place would almost certainly"
      + " be ordered torn down by the Sparkle Historical Society.\n");
    try_item( ({ "exterior", "exterior of the building",
                 "bank exterior", "exterior of the bank" }),
        "The exterior of the bank is crowded with all sorts of ..."
      + " shall we say ... extras.\n");
    try_item( ({ "extra", "extras", "cog", "cogs", "gear", "gears",
                 "piston", "pistons", "bell", "bells", "whistle",
                 "whistles" }),
        "It's best not to think about it too much. This is gnomish stuff."
      + " If you are a gnome, there is no need to explain it to you. If"
      + " you are not, there is no WAY to explain it to you.\n");
    try_item( ({ "bells and whistles" }),
        "The calling card of any gnomish ... anything.\n");
    try_item( ({ "construction" }),
        "Who could dream up such things? Well, a gnome could.\n");
    try_item( ({ "dome", "cupola" }),
        "The cupola of the bank is covered with bright blue tiles. Atop"
      + " its peak a red and orange flag flaps in the breeze.\n");
    try_item( ({ "tile", "tiles", "blue tile", "blue tiles",
                 "bright blue tile", "bright blue tiles" }),
        "The tiles upon the cupola are quite striking. Were it not for"
      + " all the ... extras ... piled all over the building, it might"
      + " actually be quite beautiful.\n");
    try_item( ({ "flag", "red flag", "orange flag",
                 "red and orange flag" }),
        "Emblazoned on the flag in purple letters are is the g.O.g."
      + " logo of the Gnomes Of Genesis.\n");
    try_item( ({ "purple letter", "purple letters" }),
        "Purple letters on a red and orange background? Dreadful!\n");
    try_item( ({ "red background", "orange background",
                 "red and orange background", "background" }),
        "Such color combinations should probably be illegal. In fact, they"
      + " might be.\n");
    try_item( ({ "construction" }),
        "The bank appears to be undergoing quite a bit of"
      + " restructuring.\n");
    try_item( ({ "post", "signpost", "unusual post",
                 "unusual signpost" }),
        "Bells and whistles have been placed all over the signpost,"
      + " evidently to ring (??) when someone reads ... the sign? Oh,"
      + " forget it. There is no hope of comprehending the reason for"
      + " any of it (unless you are a gnome, in which case, enjoy.)\n");
    try_item( ({ "south", "southern building", "south building",
                 "building to the south" }),
        "The Tower of Realms rises just to the south.\n");

    add_item( ({ "signs" }), "There is one sign to the north.\n");

    add_item( ({ "sign", "strange sign", "north sign",
                 "northern sign", "sign to the north",
                 "bank sign" }), "@@exa_sign@@");

    add_cmd_item( ({ "sign", "the sign", "strange sign",
                     "the strange sign", "north sign", "northern sign",
                     "the north sign", "the northern sign",
                     "sign to the north", "the sign to the north",
                     "bank sign", "the bank sign" }),
                  ({ "read" }), "@@exa_sign@@");

    add_center_items();

    add_tell("A huge steam-powered armoured carriage rattles noisily"
      + " into view, and disappears behind the bank.\n");
    add_tell("A bird swoops around the tower and flies out of sight"
      + " over the nearby church steeple.\n");
    add_tell("A few gnomes (arguing loudly) arrive from the east and"
      + " disappear into the building to the north.\n");
    add_tell("A muffled explosion is heard from inside the building"
      + " to the north, followed by frantic loud pounding.\n");
    add_tell("A few of the gears atop the building to the north begin"
      + " turning for a moment and then stop.\n");

    add_exit("center_f", "west");
    add_exit("/d/Genesis/start/human/town/bank", "north");
//  add_exit("/d/Sparkle/area/city/bank/room/line2", "north");
    add_exit("market_square", "east");
    add_exit("/d/Genesis/start/human/town/tower", "south");

    
} /* create_sparkle */


/*
 * Function name:        exa_sign
 * Description  :        provide a description of the sign that is
 *                       hanging here
 * Returns      :        string - the text to display
 */
public string
exa_sign()
{
    /* A check for the sign rating quest */
    check_rating_form(this_player(), "bank");

    return "The sign reads:\n\n"
      + read_file(TEXT_DIR + "sign_bank");
} /* exa_sign */
