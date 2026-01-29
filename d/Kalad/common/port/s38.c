#include "default.h"
inherit PORT_ROOM;

object ob1;

void
create_port_room()
{
    add_prop(ROOM_I_INSIDE,1);
    set_short("Office of the brewery's manager");
    set_long("If anything, the air here is even more soaked with the odor "+
      "of beer than anywhere else in the brewery. The walls here are "+
      "extravagantly decorated in exotic wallpaper. The room is furnished "+
      "with plush chairs for visitors and a comfortable chair behind a "+
      "large wooden desk. A small window is in the south wall.\n");
    add_item(({"walls","wall","south wall"}),"The sides of the room are "+
      "covered with unusual wallpaper, giving the room a foreign taste.\n");
    add_item(({"exotic wallpaper","unusual wallpaper","wallpaper"}),
      "It has strange patterns depicted on it, most revolving around the "+
      "central theme of beer.\n");
    add_item(({"plush chairs","plush chair","chairs"}),"Small, cushioned "+
      "seats.\n");
    add_item(({"comfortable chair"}),"A wonderfully plush chair, lined "+
      "with silken pillows.\n");
    add_item(({"silken pillows","silken pillow","pillows","pillow"}),
      "They look very soft and inviting.\n");
    add_item(({"chair"}),"Which chair?\n");
    add_item(({"large wooden desk","large desk","wooden desk","desk"}),
      "A beautifully crafted oak desk, upon the top is a small nameplate.\n");
    add_item("nameplate","@@nameplate");
    add_cmd_item("nameplate","read","@@nameplate");
    add_item(({"small window","window"}),"Outside you can see the center "+
      "of the Port District.\n");
    add_exit(PORT + "s39", "east");
    reset_room();
}

nameplate()
{
    return "Regis Rumblebelly, Manager of the Halfling Brewery.\n";
}

reset_room()
{
    if(!ob1)
    {
	ob1 = clone_object(PORT + "npc/hbmanager");
	ob1 -> move_living("xxx", TO);
	tell_room(TO,"The smell of stale beer wafts around the room.\n");
    }

}

