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
    set_area("on the outskirts of the Chetwood on");
    set_areaname("the Great East Road");
    set_land("the Shire");
    set_areatype(AREATYPE_ROAD);
    set_areadesc("heavy forest");
    set_grass("lush long");
    set_treetype("oak");

    set_extraline("The dense oak forest obscures your vision on the "+
    "north side of the road, and to the south the hills break free of "+
    "the surrounding forest.  The road continues to the west and "+
    "southeast from here.");

    add_item(({"trees","forest","chetwood","wood","the chetwood"}),
      "The Chetwood casts its ancient shadow over the Great East "+
      "Road, but you notice it thinning to the south and east. "+ 
      "The ancient oaks press down around you, as if you're "+
      "not welcome. Wildlife seems to be sparse, yet flourishing.\n");
    add_item(({"hills","fields","rolling hills"}),
      "The fields south of "+
      "you cling to the gently rolling hills and gullies. Further "+
      "to the south and east you can make out the South Downs.\n");

    add_exit(ER_DIR + "erb6",  "southeast", 0, 1);
    add_exit(ER_DIR + "erb4",  "west", 0, 1);
    add_exit(ER_DIR + "erb5n1", "north",0, 1);
    add_exit(ER_DIR + "erb6n1", "northeast", 0, 1);
//    add_exit(ER_DIR + "erb5s", "south", "@@hills_msg@@", 2, 1);

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