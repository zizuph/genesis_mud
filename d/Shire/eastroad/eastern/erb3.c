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
    set_area("not far from Bree on");
    set_areaname("the Great East Road");
    set_land("the Shire");
    set_areatype(AREATYPE_ROAD);
    set_areadesc("heavy forest");
    set_grass("lush long");
    set_treetype("oak");

    set_extraline("The ancient oaks of the Chetwood surround you, although "+
      "they thin out to your west where Bree Hill is still visible, and "+
      "to the and south where the rolling hills are covered with fields. "+
      "The forest thickens to the north and east however, and you wonder "+
      "what lurks within its depths. To the east the road goes on through "+
      "the Chetwood.");

    add_item(({"trees","forest","chetwood","wood","the chetwood"}),
      "Nestled against the back of Bree Hill, the Chetwood casts its "+
      "ancient shadow over the Great East Road, and off the the north "+
      "and east. The ancient oaks press down around you, as if you're "+
      "not welcome. Wildlife seems to be sparse, yet flourishing.\n");
    add_item(({"hill","bree hill"}),
      "In the distance to the west, along the road and through the "+
      "forest cover, you can see the large hill know by the locals "+
      "as Bree Hill. Close by the hill is the South gate of Bree, "+
      "and along its east flank lies Staddle.\n");
    add_item(({"hills","fields","rolling hills"}),
      "Unlike the singular and very large Bree hill, the fields south "+
      "you cling to the gently rolling hills and gullies. Much farther "+
      "to the south and east you can make out the South Downs.\n");

    add_exit(ER_DIR + "erb4",  "east", 0, 1);
    add_exit(ER_DIR + "erb2",  "west", 0, 1);
    /*  add_exit(ER_DIR + "erb3n", "north", "@@forn_msg@@", 2, 1);
	add_exit(ER_DIR + "erb3s", "south", "@@hills_msg@@", 2, 1); */

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
