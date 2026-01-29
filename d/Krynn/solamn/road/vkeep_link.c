/* Aridor, 08/98 */

#include "local.h"

inherit ROOM_BASE

int gFlooded = 1;
object ferry = 0;

void
start_ferry()
{
    if (!ferry)
      ferry = clone_object(FERRY);
    ferry->move(TO);
    /*ferry->start_ship();*/
}

void
stop_ferry()
{
    ferry->stop_at_next_possibility();
}

void
set_flooded(int i)
{
    if (i == gFlooded)
      return;

    if (i == 1)
    {    
	tell_room(TO,"Suddenly, a thunderous noise can be heard from the southwest, " +
		  "swelling more and more.\n" +
		  "A flood washes along the river, taking everything along. When the " +
		  "initial noise clears, you can see that the water level has risen " +
		  "so high that the pier here is actually useful now.\n");
	/* wash everything away in the river rooms! */
	FLOODABLE_ROOMS->flood_water();
	set_alarm(60.0,0.0,start_ferry);
    }
    else
    {
	tell_room(TO,"Without notice, the water level of the river drops rapidly, " +
		  "until you can only see a broad but shallow stream in the " +
		  "wide river bed.\n");
	FLOODABLE_ROOMS->drain_water();
	/* stop_ferry(); */
    }

    (VKEEP_LINK)->flood_message(i);
    gFlooded = i;
}

/* Returns: 1 - flooded
 *          0 - not flooded
 */
int
flooded()
{
    return gFlooded;
}

int
query_flooded()
{
    return flooded();
}

int
flood_closed()
{
    int i = flooded();
    if (i)
      write("There is no obvious exit northwest.\n");
    return i;
}

int
flood_closed_sw()
{
    int i = flooded();
    if (i)
      write("The track southwest is impassable due to the flood.\n");
    return i;
}

void
create_road_room()
{
    set_short("@@my_short@@");
    set_long("@@my_long@@");
    
    add_item(({"pier"}),"@@pier_desc@@");
    add_item(({"vingaard keep","keep","walls","fortress"}),"The massive " +
	     "walls of can be seen across the river. The Keep is a fortress " +
	     "located on the a tip of land between the large Vingaard River " +
	     "on the east and a smaller river on the west. From here you " +
	     "can see the conjunction of the rivers just beyond the Keep.\n");
    add_item(({"vingaard river","river"}),"@@river_desc@@");

    if (LOAD_ERR(ROAD_OBJECT))
    {
	write("Bug! please report immediately...\n");
	return;
    }
    add_exit("", "north","@@enter_map:" + ROAD_OBJECT + "|V@@",3,0);
    add_exit("", "east", "@@enter_map:" + ROAD_OBJECT + "|V@@",3,0);
    add_exit("", "south","@@enter_map:" + ROAD_OBJECT + "|V@@",6,1);

    add_exit("river1","northwest","@@flood_closed@@",10,1);
    add_exit("ferryman_hut","southwest",0, 2,1);

    if (flooded())
      set_alarm(0.0,0.0,start_ferry);
}

string
my_short()
{
    if (flooded())
      return "Pier at the river";
    return "Ford across the river";
}

string
my_long()
{
    if (flooded())
      return ("While the road continues north and east, a pier stretches out " +
	      "into the water from here. The river is at least 1200 feet across, " +
	      "and you can make out the impressive walls of Vingaard Keep on " +
	      "the other side.\n");
    return ("While the road continues north and east, there is a ford " +
	    "leading northwest which allows you to cross the river. The " +
	    "river is about 1000 feet across, quite a distance. Beyond " +
	    "the river, the impressive walls of Vingaard Keep can be seen. " +
	    "A seemingly useless pier is also located here, several feet " +
	    "away from and above the water. The riverbank is walkable in " +
	    "a southwestern direction.\n");
}

string
pier_desc()
{
    if (flooded())
      return ("This is an ordinary wooden pier stretching out into the water " +
	      "here.\n");
    return ("The wooden pier is high above the water level. It seems " +
	    "displaced here in this position.\n");
}

string
river_desc()
{
    if (flooded())
      return ("This is the mighty Vingaard River. It reaches all the way to " +
	      "the road here, the water level is just below the general " +
	      "elevation level of the plains. A pier is located here to " +
	      "allow transport across the river.\n");
    return ("The Vingaard River lies before you. For the most part, all you " +
	    "can see is a river bed with plenty of stones and rocks about. " +
	    "In the middle of the river bed, a shallow stream of water makes " +
	    "its way towards the northeast, to the sea. Even though the water " +
	    "is currently very low, the river bed shows the breadth the river " +
	    "can reach after a rainy season.\n");
}

