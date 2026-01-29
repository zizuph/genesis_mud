/*
 *  This is the outside of the door to the storage shed atop Amon Din
 *
 *  July 1995 by Gorboth
 */

inherit "/std/door";
#include "/d/Gondor/defs.h"

create_door()
{
    ::create_door();
    set_door_id("ad_storage");
    add_name("amon_din_storage_door_out");
    set_pass_command(({"n","north"}));
    set_door_name(({"door","storage door","wooden door","old door"}));
    set_door_desc(BSN(
       "This wooden door looks very old, and could use a replacement."
     + " Nevertheless, it serves its purpose, namely to keep unwanted"
     + " persons and elements out of the building."));
    set_other_room(AMON_DIR + "storage1");
    set_lock_command("lock");
    set_lock_name("lock");
    set_unlock_command("unlock");
    set_open(0);
    set_locked(1);
    set_key("amon_din_storage_key");
}
