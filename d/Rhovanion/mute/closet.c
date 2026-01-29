inherit "/std/room.c";
#include "/sys/stdproperties.h"
create_room()
{
object ob1;
set_short("Even for a closet, this room is sort of cool.");
set_long(" 	You have entered Mute's closet "+
" Racks of cloaks and other medieval items of clothing are arranged "+
" neatly on racks and things.  You have the odd feeling you are being "+
" watched by ninjas! \n");
add_exit("/d/Rhovanion/mute/workroom","west");
ob1 = clone_object("d/Rhovanion/mute/ninja.c");
ob1->move(this_object());
}
