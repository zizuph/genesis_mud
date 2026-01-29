#pragma save_binary
#pragma strict_types

#include "local.h"

inherit EAST_ROAD;
inherit IS_ELF_GR_TRAVELLER;

static string  patrol_dir = "sw";
public void    set_patrol_dir(string s) { patrol_dir = s; }
public string  query_patrol_dir(object ob) { return patrol_dir; }


void
create_er_room()
{
    set_area("close by");
    set_areaname("the South Gate of Bree");
    set_land("the Shire");
    set_areatype(AREATYPE_ROAD);
    set_areadesc("rolling hillside");
    set_grass("lush long");
    set_treetype("oak");

    set_extraline("The rolling hills around you meet in a valley here "+
      "below what the locals call Bree Hill. The South gate of Bree "+
      "is barely visible to the southwest, the great trees of the Chetwood "+
      "already encroaching on your vision. A thick hedge grows along the " +
      "hills, enclosing Bree. To the east the long road cuts its way though " +
      "the ancient forest.");

    add_item(({"hill","bree hill","hills","valley"}),
      "Right before you is Bree hill, its long arms stretching out "+
      "right to your feet. The Great East road follows the hill "+
      "to the South gate of Bree to the southwest, and from here "+
      "sets off east away from the hill.\n");
    add_item(({"trees","forest","chetwood","wood","the chetwood"}),
      "Nestled against the back of Bree Hill, the Chetwood casts its "+
      "ancient shadow over the Great East Road, and off the the north "+
      "and east. The ancient oaks press down around you, as if you're "+
      "not welcome. Wildlife seems to be sparse, yet flourishing.\n");
    add_item(({"gate","south gate"}),
      "In the distance to the southwest you can just make out the "+
      "break in the hedge wall where the South Gate controls access "+
      "into Bree.\n");
    add_item(({"hedge"}),
        "The hedge grows around the outside of the town. It is very " +
        "thick and resembles a wall. It offers a measure of protection, " +
        "increased by a deep dike that has been dug to the right of " +
        "the hedge. @@ranger_descr@@\n");
    add_item(({"dike", "deep dike"}),
        "The dike is a very wide, deep trench that looks like it was " +
        "dug ages ago. Nonetheless, it is kept in good repair and " +
        "surrounds the town. It is outside the hedge and offers another " +
        "defense in protecting Bree.\n");
    add_item(({"bushes"}),
        "They grow thick together, making up the hedge that surrounds " +
        "the town.\n");
    add_item(({"opening"}),
        "@@opening_descr@@\n");
   

    add_exit(ER_DIR + "erb3",  "east", 0, 1);
//    add_exit(OLD_BREE_DIR + "egate",  "southwest", 0, 1);
    add_exit("/d/Shire/bree/rooms/road/sgate","southwest");
    
//    add_exit(ER_DIR + "stad1", "north", 0, 1);
//   add_exit(ER_DIR + "erb3n", "northeast", "@@north_msg@@", 2, 1);
//   add_exit(ER_DIR + "erb2s", "southeast", "#south_msg#", 2, 1); */

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



string ranger_descr()
{
    if (R_ALLOWED)

        return "There is a slight opening in the hedges where the bushes are thinner.";
    else
        return "";

}

string opening_descr()
{
    if (R_ALLOWED)

        return "The opening is a thin place in the hedge.";
    else
        return "";

}

public void
init()
{
    ::init();
//    add_action("enter_hedge", "enter");
}

int enter_hedge(string str)
{

    if (R_ALLOWED)
    {    
        if(!str)
        {
            write("Enter what?\n");
            return 1;
        }

        if(str =="hedge" || str == "opening" || str == "gap" || str == "bushes")
        {
            write("You disappear into the hedge.\n");
            TP->move_living("M",ER_DIR + "br1_01", 1);
            tell_room(ENV(TP), QCTNAME(TP) + " arrives from the South Gate of Bree.\n",TP);
            return 1;
        }
        else 
        {
            write("Enter what?\n");
            return 1;
        }
    }
    
}
