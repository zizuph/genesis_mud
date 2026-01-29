 /*
   Wayreth.

   whitestudy.c
   ------------

   Coded ........: 95/06/02
   By ...........: Jeremiah

   Latest update : 97/07/28
   By ...........: Mhyrmarius

*/

#include "/d/Krynn/wayreth/local.h"
#include "/d/Krynn/common/clock/clock.h"
#include "/sys/macros.h"
inherit TOWERROOM;

#undef ADMIN
#define ADMIN  "/d/Krynn/wayreth/guild/admin/admin.c"
#define WHITE  ADMIN->query_conclave_head("white")

string time_desc()
{
	switch(GET_TIMEOFDAY)	
	{
		case TOD_DAWN:
		return "The rising sun sheds"; break;
		case TOD_DAY:
		return "The sun is high in the sky, shedding"; break;
		case TOD_TWILIGHT:
		return "The setting sun gives way to the three moons of the night, shedding"; break;
		case TOD_NIGHT:
		return "The two visible moons shed"; break;
	}
return "This doesn't WORK";
}

void
create_tower_room()
{
    set_short("This is the study of the Master of the White Robes");

    set_long("A magnificent multifaceted crystalline window on " +
	"the far wall spills a dazzling display of colored light "+
	"across the furnishings of this room. An intricately carved "+
	"citruswood desk dominates the opposite end of the room, and "+
	"behind it sits a simple leather armchair. What at first glance "+
	"appeared to be a pair of graceful rowan trees turns out to be a "+
	"cunningly designed book cabinet, around which there is an almost "+
	"indistinct field of shimmering energy. A plush leather couch for "+
	"visitors sits across from the desk, along with an extremely "+
	"comfortable footrest.\n");

    add_item(({"walls", "wall"}), "The walls are made of the same " +
             "black rune covered rock as the rest of the tower. " +
             "Some tapestries adorn the walls.\n");

    add_item("ceiling", "The ceiling is made of the same black " +
             "rune covered stone as the rest of the tower.\n");

    add_item("floor", "The floor is wooden and creaks slightly " +
             "as you walk across it.\n");

    add_item("window", "As you gaze out the window, you see an "+
	"incredible view of the surrounding forests, the Kharolis "+
	"mountains, and - off in the distance - the glint of light "+
	"that is the city of Haven. "+"@@time_desc@@"+" a gentle light over "+
	"the landscape.\n");

    

    add_item(({"case","bookcase","cabinet"}), "Designed to appear as a pair of rowan "+
	"trees, this contraption is instead a bookcase, undoubtedly of gnomish "+
	"origin. The knobs of the cabinet are disguised as two protruding " +
	"bumps in the trunks of the trees, and it would seem that the case "+
	"could be opened by swinging the doors in opposite directions."+
	"It is, unfortunately, securely locked, both physically and magically.\n");

    add_item(({"desk", "citruswood desk", "carved desk"}), "You have never seen "+
	"such an amazing clutter of worthless papers, useless knicknacks, and "+
	"scribbled notes.  It's amazing that the desk doesn't topple over "+
	"from the sheer weight of all the paper. None of it looks terribly "+
	"important, however, and even if it was, you doubt you could find "+
	"anything useful in the vast pile. The carvings along the front and sides "+
	"catch your eye.\n");

    add_item("carvings", "Each panel of the desk seems to represent the history of one " +
	"of the major elven tribes, the Drow, the Eldar, and the Krynnish elves. The "+
	"carvings are done in fantastic detail, to the point that the figures almost "+
	"seem alive. Some sort of magic is undoubtedly at work.\n");

    add_item(({"couch","footrest"}),"This couch and footrest ensemble seems designed to "+
	"put the visitor to the office at complete ease. Indeed, they look so "+
	"comfortable, you wonder how anyone ever has the willpower to stand up.\n");
    
    add_item(({"chair","armchair"}),"The luxurious armchair is made of " +
             "dark brown leather and looks very comfortable.\n");

    add_exit(WTOWER + "conclave", "south", 0);
} 

public int
query_start_room() { return 1; }

static int
query_prevent_snoop() { return 1; }

