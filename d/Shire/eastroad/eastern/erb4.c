#pragma save_binary
#pragma strict_types

#include "local.h"

inherit EAST_ROAD;
inherit IS_ELF_GR_TRAVELLER;

static string  patrol_dir = "w";
public void    set_patrol_dir(string s) { patrol_dir = s; }
public string  query_patrol_dir(object ob) { return patrol_dir; }

void
create_er_room()
{
    set_area("somewhere in the Chetwood on");
    set_areaname("the Great East Road");
    set_land("the Shire");
    set_areatype(AREATYPE_ROAD);
    set_areadesc("heavy forest");
    set_grass("lush long");
    set_treetype("oak");

    set_extraline("Bree Hill has faded to your west where "+
      "the Chetwood has closed down over the Great East road. "+
      "All ways north are heavily forested, and to the south "+
      "you can make out fields through the clearing trees.");

    add_item(("bree hill"),
      "You're too far away now to see anything of Bree Hill, "+
      "you'll have to go further west.\n");
    add_item(({"trees","forest","chetwood","wood","the chetwood"}),
      "The Chetwood casts its ancient shadow over the Great East "+
      "Road, dense in all directions save to your south. "+
      "The ancient oaks press down around you, as if you're "+
      "not welcome. Wildlife seems to be sparse, yet flourishing.\n");
    add_item(("fields"),
      "Through the thinning forest to the south you can make out "+
        "the lush green fields clinging to the gently rolling land.\n");

    add_exit(ER_DIR + "erb5",  "east", 0, 1);
    add_exit(ER_DIR + "erb3",  "west", 0, 1);
    add_exit(ER_DIR + "erb4n1", "north", 0, 1);
//	add_exit(ER_DIR + "erb4s", "south", "@@south_msg@@", 2, 1);

}

public void
enter_inv(object ob, object from)
{
	string *names;
	::enter_inv(ob, from);
	names = ob->query_names();
	if(ob->id(npc_name))
	{
		if (!move_alarm || !sizeof(get_alarm(move_alarm)))
		{
			move_alarm = set_alarm(50.0 + rnd() * 20.0, 0.0, &move_patrol(ob));
		}
	return;
	}
}
