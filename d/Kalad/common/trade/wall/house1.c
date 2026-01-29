inherit "/d/Kalad/room_std";
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Kalad/defs.h"

void
create_room()
{
set_short("Old House");
set_long("This is an old shadowy house.\n");
add_cmd_item(({"north","shadows"}),"enter","@@enter");
add_cmd_item("shadows","enter","@@emter");
add_item(({"shadows","shadow"}),"The shadows seem to take up the "
                               +"entire north wall.\n");
add_exit(TRADE(wall/wall5),"west");
add_prop(ROOM_I_INSIDE,1);
add_prop(ROOM_NO_TIME_DESC,1);
}
enter()
{
write("You slip into the shadows.");
set_dircmd("shadows");
TP->move_living("into a poorly lit room.","/d/Kalad/common/trade/wall/sewent");
return 1;
}
