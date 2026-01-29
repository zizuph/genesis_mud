#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam_forest/local.h"
inherit FOREST_IN;
object shaman;

void
reset_flotsam_room()
{
	if(!objectp(shaman))
	{
	    shaman = clone_object(FNPC + "shaman");
	    shaman->move(TO);
	}
}

create_flotsam_room()
{
    set_short("shamans' tent");
    set_long("@@long_descr");
    add_prop(ROOM_I_NO_CLEANUP, 1);

    add_item(({"tent","animal skins","teepee-like tent","skins"}),
      "This tent is made of the skins of quite a few different " +
      "animals. It looks quite hardy and durable.\n");
    add_item(({"totems","claws","pouches","herbs"}),
      "Totems ranging from the claws of a crow to pouches of " +
      "herbs hang all around the tent. This must be a tent " +
      "used by the tribes shaman or witchdoctor.\n");
    add_item(({"air","hazy smoke","incense","burning incense"}),
      "Swirling around the room is a thick sweet-smelling " +
      "smoke that comes from burning incense.\n");
    add_item(({"long sleeping pallet","sleeping pallet","pallet"}),
      "A long wooden bed made of furs and strong branches.\n");


    add_exit(FROOM + "g25","out",0);

    reset_flotsam_room();
}

string
long_descr()
{
    return "You stand within a small teepee-like tent made " +
    "of various animal skins. Totems hang around the place, " +
    "and a long sleeping pallet lies at the other side of the " +
    "tent. The air is thick with the hazy smoke of incense.\n";
}
