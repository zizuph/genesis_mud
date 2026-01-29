/*
 *  This is the inside of the door to the tower atop Amon Din
 *
 *  July 1995 by Gorboth
 */

inherit "/std/door";
#include "/d/Gondor/defs.h"

create_door()
{
    ::create_door();
    set_door_id("ad_tower");
    set_pass_command(({"w","west"}));
    set_door_name(({"door","arch","wooden door","arched door","doorway"}));
    set_door_desc(BSN(
        "The wood which this door is constructed of is quite striking."
      + " Obviously quite old, it shows very few signs of use or decay,"
      + " and is clearly sturdy enough to keep out those who are without"
      + " the proper means of entry. An ornate keyhole lies in the direct"
      + " center of this door, shaped much in the manner of the arched"
      + " passageway it maintains."));
    set_other_room(AMON_DIR + "summit3");
    set_lock_command("lock");
    set_lock_name("lock");
    set_unlock_command("unlock");
    set_open(0);
    set_locked(1);
    set_key("amon_din_tower_key");
}
