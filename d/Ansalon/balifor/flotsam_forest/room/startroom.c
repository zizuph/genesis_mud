#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam_forest/local.h"

inherit FOREST_IN;

create_flotsam_room()
{
    set_short("Barracks of the Knight Circle");
    set_long("@@long_descr");

    add_item(({"barracks", "cots", "cot"}), "The cots line the walls "+
      "efficiently, and they appear to be fairly comfortable, though "+
      "not luxurious.\n");
    add_item("rooms", "To the north is the armoury, and to the south "+
      "you see people writing letters.\n");
    add_item("hallway", "A hallway leads east and out of the secret "+
      "Circle of Knights in Flotsam.\n");

    add_exit(FROOM + "secret_hallway", "east");
    add_exit(FROOM + "armoury", "north");
    add_exit(FROOM + "post_office", "south");
    add_cmd_item("here", "start", "@@do_start");

}

int
do_start()
{
    NF("Start where?\n");
    if (TP->query_guild_name_occ() != "Solamnian Knights")
	return 0;
    TP->set_default_start_location("/d/Ansalon/balifor/flotsam_forest/room/startroom");
    write("You will now start here.\n");
    return 1;
}

string
long_descr()
{
    return "This makeshift barracks has cots arranged around the "+
    "walls for Knights to sleep in. A hallway leads out to the "+
    "east, and two smaller rooms are to the north and south. "+
    "Knights of Solamnia stationed at this outpost sleep here.\n";
}
