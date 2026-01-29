/*
 *  This is the inside of the door to the tower shed atop Amon Din
 *
 *  July 1995 by Gorboth
 */

inherit "/std/door";
#include "/d/Gondor/defs.h"

create_door()
{
    ::create_door();
    set_door_id("ad_storage");
    add_name("amon_din_storage_door_in");
    set_pass_command(({"s","south"}));
    set_door_name(({"door","storage door","wooden door","old door"}));
    set_door_desc(BSN(
       "This old wooden door has seen happier times. Years of use have"
     + " taken their toll on its surface. Though it is not much to look"
     + " at, it does keep this building secure."));
    set_other_room(AMON_DIR + "summit5");
    set_lock_command("lock");
    set_lock_name("lock");
    set_unlock_command("unlock");
    set_open(0);
    set_locked(0);
    set_key("amon_din_storage_key");
}
