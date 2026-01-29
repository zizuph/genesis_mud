/* created by Aridor 06/21/93 */

#include "../local.h"
#include <macros.h>

inherit OUTSIDE_BASE;


#define NPC_LIST (["Knights":0, \
		   "Free People":0, \
		   "Blue Dragon Army":"/d/Krynn/solamn/splains/living/bozak", \
		   "Red Dragon Army":"/d/Krynn/solamn/splains/living/bozak", \
		   "White Dragon Army":"/d/Krynn/solamn/splains/living/bozak", \
		   "Green Dragon Army":"/d/Krynn/solamn/splains/living/bozak", \
		   "Black Dragon Army":"/d/Krynn/solamn/splains/living/bozak"])[current_army]
	      
string current_army = "Knights";
object npc;


void
set_up_npc()
{
    string filename;

    if (npc)
      return;
    filename = NPC_LIST;
    if (filename && stringp(filename) && filename != "")
    {
	npc = clone_object(filename);
	npc->move_living("xxx",TO);
        npc->set_no_team_member(1); //bozak cannot team up
	npc->set_color(lower_case(explode(current_army," ")[0]));
	npc->command("emote takes his guardpost.\n");
    }
}

void
area_conquered(string newarmy, string oldarmy)
{
    if (npc)
    {
	npc->command("emote leaves his guardpost.");
	npc->remove_object();
    }
    current_army = newarmy;
    set_up_npc();
}

/* If the alignment of the occupant army is equal to the one who
 * wants to pass, let him/her through.
 */
int
may_pass()
{
    string army = ARMYMASTER->army_of_player(TP);
    int align = ARMYMASTER->army_alignment(army);
    int occupantalign = ARMYMASTER->army_alignment(current_army);
    
 if (objectp(npc) && E(npc)==TO && (occupantalign >= 0 && align < 0 ||
		occupantalign < 0 && align >= 0) &&
	CAN_SEE(npc, TP) &&
	query_verb() == TP->query_prop(LIVE_S_LAST_MOVE))
    {
	npc->command("say You are not allowed to pass.");
	return 1;
    }
    return 0;
}

void
reset_splains_room()
{
    set_up_npc();
}

void
create_splains_room()
{
    set_short("Bridge over West Vingaard River");
    set_long("This is a solid stone bridge spanning "
        +    "across the West Vingaard River. To the west you "
        +    "see a plain stretching out, and to the east "
        +    "the road forks.\n");

    add_exit(ROOM + "road8","west","@@may_pass@@");
    add_exit(ROOM + "xroad","east","@@may_pass@@");
    add_prop(ROOM_AS_TO_KNIGHTS,({"e","w"}));

    add_item("bridge",
	     "It looks solid enough for several of you to " +
		"cross it. Unfortunately, you cannot look under the bridge " +
		"to see what is there and the only way to get there is " +
		"along the river.\n");
    add_item(({"sidearm","river"}),"This is a little sidearm of the mighty Vingaard "
          +  "River.\n");
    add_item("fork","You can't make out any details unless you go there.\n");
 
    current_army = ARMYMASTER->army_in_area("Western Solamnian Plains");
    reset_splains_room();
}

