/*
 *  /d/Emerald/common/guild/aod/rooms/norm_wep_drop.c
 * 
 *  This is the droproom for miscelaneous items for the Army of
 *  Darkness guild.
 *
 *  Created December 2006, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

inherit AOD_ROOM_DIR + "drop_room";


/* prototypes */
public void        create_drop_room();


/*
 * Function name:        create_drop_room
 * Description  :        set up the room with area defaults
 */
public void
create_drop_room()
{
    set_short("a droproom beside a pile of miscellaneous rubbish");
    set_em_long("You seem to have reached the bottom of the ravine."
      + " Huge piles of miscellaneous rubbish are heaped all"
      + " around you here - the rejects of the droproom. Perhaps"
      + " there are still a few useful things to be found. You"
      + " can climb out of here by travelling up the switchbacks.\n");

    add_item( ({ "bottom", "bottom of the ravine" }),
        "Yep, this is the bottom all right. Can't go any lower than"
      + " this.\n");
    add_item( ({ "ravine" }),
        "This is its bottom. You'll have to go up to see the rest"
      + " of it.\n");
    add_item( ({ "pile", "piles", "huge pile", "huge piles",
                 "pile of rubbish", "piles of rubbish",
                 "huge pile of rubbish", "huge piles of rubbish",
                 "pile of miscellaneous rubbish",
                 "piles of miscellaneous rubbish",
                 "huge pile of miscellaneous rubbish",
                 "huge pile of miscellaneous rubbish" }),
        "Junk! Pure junk ... well, most of it anyway. Maybe there"
      + " are a few useful odds and ends lying around. Probably not.\n");
    add_item( ({ "junk", "pure junk" }),
        "Junk junk junk!\n");
    add_item( ({ "odds", "ends", "odds and ends", "useful odds",
                 "useful ends", "useful odds and ends" }),
        "Do you see any? If so, grab 'em before someone else does!\n");

    add_droproom_items();

    add_spike("misc_drop");

    add_exit("norm_arm_drop", "up");

    reset_room();
} /* create_drop_room */


/*
 * Function name:        reset_room
 * Description  :        lets add a few boulders to this room if
 *                       there aren't already some.
 */
public void
reset_room()
{
    object  boulder;
    int     i = 1 + random(4);

    if (present("boulder", this_object()))
    {
        return;
    }

    tell_room(this_object(), "CRACK!! A few large chunks of rock"
      + " peel off from the sides of the ravine and land just beside"
      + " you!\n");

    while (i)
    {
        boulder = clone_object(AOD_OBJ_DIR + "boulder");
        boulder->move(this_object());
        i--;
    }
}
