#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam/local.h"

inherit FLOTSAM_OUT;
object home1;

void
reset_flotsam_room()
{
    if(!objectp(home1))
    {
	home1 = clone_object(FNPC + "homeless");
	home1->move(TO);
    }
}

create_flotsam_room()
{
    set_short("Warehouse");
    set_long("@@long_descr");

    add_item("crates","These crates are used by the homeless " +
      "of Flotsam to sleep in. They don't look very comfortable.\n");
    add_item(({"walls","wooden walls"}),"The great wooden walls rise up into " +
      "the darkness of the ceiling. \n");
    add_item(({"roof","wooden roof","ceiling"}),"Far above " +
      "you, shrouded with darkness is the wooden roof of this warehouse.\n");

    add_exit(FROOM + "street40","out","@@ware_out",0);

    reset_flotsam_room();
}

string
long_descr()
{
    return "You stand within the great wooden walls of one " +
    "of Flotsam's warehouses. This high-vaulted stone " +
    "structure faces the full fury of winter sea storms " +
    "that come in from the docks, so it leans slightly towards the " +
    "inner parts of town. " +
    "This warehouse has long been abandoned by its owners, and " +
    "is now the residence of some of Flotsam's homeless. A few " +
    "empty crates sit at the back of the warehouse. Above you " +
    "hear the sound of rain drumming on the wooden roof. \n";
}

int
ware_out()
{
    write("You leave the warehouse... \n");
    return 0;
}
