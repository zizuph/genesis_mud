#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/steppe/local.h"
#include <macros.h>

inherit STEPPE_OUT;

#define TORCH "/d/Krynn/solace/village/obj/torch"

int torch_present = 1;
object viridian;

void
reset_steppe_room()
{
    if(!objectp(viridian))
    {
	viridian = clone_object(SNPC + "warrior");
	viridian->arm_me();
	viridian->move(TO);
    }
}

create_steppe_room()
{
    set_short("A small campsite");
    set_long("@@long_descr");

    add_item(({"small campfire","campfire","fire"}),
      "A small campfire burns merrily before you."+
      " @@torch_present@@\n");
    add_item(({"camp","campsite"}),"@@long_descr");
    add_item(({"road","southeast"}),
      "By heading southeast, you could return to the road.\n");

    add_exit(SROOM + "road6","southeast",0);

    add_cmd_item(({"torch","torch from campfire","torch from fire"}),
      ({"get","take","pull","grab"}),"@@get_torch");

    reset_steppe_room();
}

void
reset_torch()
{
    torch_present = 1;
}

string
torch_present()
{
    if(torch_present)
    {
	return "You could probably grab a torch from it.";
    }
    return "";
}

string
get_torch()
{
    if(torch_present)
    {
	write("You reach down and grab a torch out of the campfire.\n");
	say(QCTNAME(TP)+ " reaches down and grabs a torch from the "+
	  "campfire.\n");
	clone_object(TORCH)->move(TP);
	torch_present = 0;
	set_alarm(1000.0, 0.0, &reset_torch());
	return "";
    }
    write("There are no torches to get from the campfire.\n");
    return "";
}

string
long_descr()
{
    return "You stand before a small campfire a short " +
    "distance from the road. " + tod_descr1() +
    "\n";
}
