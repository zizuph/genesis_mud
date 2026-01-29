#include "defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"


create_eastroad()
{
    set_short("Outside The Forsaken Inn");
    set_long(
	"You are standing outside an old abandoned inn. The inn "
	+"itself has long been abandoned and probably only rats "
	+"dare go into the dilapidated building nowadays. "
	+"You don't feel too comfortable hanging around.\n");


   add_item(({"inn","abandoned inn","building"}), 
	"The inn is obviously the Forsaken Inn, and after you ponder "
	+"how it got that name, you notice all the holes in the walls, "
	+"big enough for rats and larger creatures to enter and exit. "
	+"The walls are peeled completely of paint and the windows "
	+"are shattered. Glass lies sparkling in the light; "
	+"obviously the windows were broken out from the inside.\n");


   add_item(({"rat","rats","hole","holes"}), 
	"The rats must enter through those huge holes. "
	+"You don't see any now, though.\n");

    WEST("chet5");
    EAST("eroad.1");

}
init()
{
   ::init();
   add_action("do_enter","enter");
}
int
do_enter(string str)
{
   if (str != "hole")
    {
    if (str == "building" || str == "house" || str == "inn" || 
        str == "forsaken" || str == "forsaken inn")
     return notify_fail("Enter the building? How? Perhaps through a hole?\n");
   if (str == "holes")
      return notify_fail("Enter holes??\n");
     NF("Enter what?\n");
     return 0;
   }

     write("You squeeze into the biggest hole in the abandoned building.\n");
     tell_room(QCTNAME(TP)+ " enters a hole in the abandoned inn.\n");
     TP->move_living("M","/d/Shire/common/eastroad/in_forsaken",1);
     return 1;

}
