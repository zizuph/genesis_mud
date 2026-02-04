inherit "/std/room.c";

/*  THis is a servants quarters, Coded by Vader on 10/27/92
 * 
 */

#include <macros.h>
#include <stdproperties.h>

#include "/d/Terel/common/terel_defs.h"

create_room()
{
   object ward;
   set_short("servants quarters");
   set_long(break_string(
    "You are in a servants quarters.  This room is quite spartan, with " +
    "only the bare necessities.  There is a bed, a night stand, a chest, " +
    "and a small desk with which to write.  There is also a wardrobe here." +
    "\n", 70));

   add_item(({"bed"}), "This bed is quite regular, and well made.\n");

   add_item(({"night stand"}), "This night stand is quite regular, and well " +
    "dusted.\n");

   add_item(({"chest"}), "This chest is quite regular, and well dusted.\n");

   add_item(({"desk", "small desk"}), "This desk is quite regular, and does " +
    "not see much use.\n");

   ward=clone_object(MANSION + "obj/ward");
   ward->move(this_object());

   add_prop(ROOM_I_INSIDE, 1);

   add_exit(MANSION + "wing_s5", "northwest", 0);

}
