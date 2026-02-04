/* File         : /d/Terel/silver/forest/road02.c
 * Creator      : Pasqua
 * Date         : March 2006         
 * Purpose      : road file for Silver Forest.
 * Related Files: /d/Terel/silver/include/road_base.c
 * Comments     : Basic Silver forest road room.
 * Modifications: Caravan start moved to road1.c
 *                Lilith, Oct 2021: fixed typo on trap door.
 */


#pragma strict_types

#include "/d/Terel/include/Terel.h"
#include "../include/defs.h"

inherit INCLUDE + "road_base";

object caravan;
int next_caravan = 1;

public void reset_room()
{
	::reset_room();
  if(!objectp(caravan))
  {
    caravan = clone_object(CARAVAN + "caravan");
    caravan->create_caravan(next_caravan);
    next_caravan = -next_caravan;
	write_file("/d/Terel/silver/log/caravan_clones", ctime(time()) 
    	+" caravan cloned.\n");
  }
}

/* Called by quest givers. Returns 1 if there is no caravan
  in the forest and the new one can be created.
*/
public int create_caravan(object ppl, int align = 1)
{
	FIX_EUID;	
	if(!caravan)
	{
		caravan = clone_object(CARAVAN + "caravan");
		caravan->create_caravan(1);
		next_caravan = -1;
		write_file(CAR_LOG, "caravan created for " + ppl->query_real_name() +
        " | " + ctime(time()) + "\n");
	}
	for(int i = 0; i <sizeof(ROUTE); ++i)
		ROUTE[i]->caravan_block();
	if(align)
		return caravan->set_defender(ppl);
	else
		return caravan->set_attacker(ppl);
}

/*
 * Function name: create_room
 * Description:   Default constructor
 */

public void
create_room()
{
    ::create_room();

    set_short("a road in the southern silver forest");
    add_exit(CALATHIN_DIR + "north_gate", "south", 0);
    add_exit(ROAD + "road03", "north", 0);
    add_exit(FOREST_AG + "forest_a13", "west",0,random(4),"@@exits");
	add_exit(FOREST_AG + "forest_a15", "east",0,random(4),"@@exits");
    add_item(({"drift", "snowdrift", "snowdrifts", "drifts of snow"}),
        "The snow covers everything, piling up along the road and the "+
        "treeline. The snowdrifts are fairly hard-packed and conceal "+
        "the underlying ground so well you can only guess at the terrain.\n");        
    add_item(({"treeline", "tree basin"}), 
        "The snow has drifted to the treeline, and reaches nearly to the "+
        "branches in places\n");
    add_item(({"roadside", "side of road"}),
        "Steep snowdrifts line the side of the road.\n");
    add_item("trapdoor", "@@check_see");
    add_cmd_item(({"door","trapdoor","trap door"}),
                  ({"lift","open"}),"@@trapdoor");
    add_prop(OBJ_I_SEARCH_TIME,4);
    add_prop(OBJ_S_SEARCH_FUN, "search_ground");

    reset_room();
	enable_reset(200); // every 45 mins to keep caravans running.
}



public string
check_see()
{
    string str;

    if (!TP->query_prop("_terel_i_found_it"))
        str ="You find no trapdoor.";
    else
        str = "It is a very cleverly made trapdoor, hidden under the "+
              "snowdrift.";

    return str +"\n";

}
string
search_ground(object player, string str)
{

    switch (str)
    {
        case "snow":
        case "drift":
        case "snowfall":
        case "snowdrift": 
        case "snowdrifts":
        case "drifts of snow":
        case "treeline":
        case "roadside":
        case "side of road":
        {
            player->add_prop("_terel_i_found_it", 1);
            /* I get some general experience for succeeeding */
            player->add_exp_general(100 + random(50));
            say(({METNAME + " begins methodically searching the drifts of snow under the treeline.\n",
            TART_NONMETNAME + " begins methodically searching the drifts of snow under the treeline.\n"}), TP);
            return "Your methodical search through the drifts of snow under the treeline " +
                "pays off when your hand brushes what appears to be a cleverly concealed "+
                "trapdoor.\n";
        }
        default:
            return "";
    }
}

/* Hidden entrance in and out of Calathin because the gates can kill people */
public mixed
trapdoor()
{
    if (!TP->query_prop("_terel_i_found_it"))
    {
        write("Where is it, exactly, in this mess of snow?\n");
        return 0;
    }
    write("You lift open the trapdoor and climb down.\n");
    say(QCTNAME(TP) + " wades into a snowdrift and disappears.\n");
    tell_room(CALATHIN_DIR + "tunnel/tunnel_11b", QCTNAME(TP) + 
       " arrives in a shower of snow.\n");
    TP->move_living("M",CALATHIN_DIR + "tunnel/tunnel_n01",1,0);
    return 1;
}
