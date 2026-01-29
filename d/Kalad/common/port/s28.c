#include "default.h"
inherit PORT_ROOM;

#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/filter_funs.h"
int pres,i;
object *ob;
object ob1;

void
create_port_room()
{
    set_short("Narrow Street");
    set_long("You are travelling along a narrow street somewhere within "+
      "the Port District. The cobblestones beneath you are moist and covered "+
      "with green grime. The road heads in a west-east direction and stretches "+
      "away into the distance. A large wooden building lies to the south, "+
      "while another similar structure is just to the north.\n");
    add_item(({"narrow street","street","road"}),"A small road that winds "+
      "its way through the district.\n");
    add_item(({"cobblestones","cobblestone"}),"The pavement is worn and "+
      "cracked, probably due to the perpetually wet environment.\n");
    add_item(({"green grime","grime"}),"Small clumps of moss and other "+
      "rootless plants are growing on the cobblestones.\n");
    add_item(({"large wooden building","large building","wooden building","building"}),
      "A large edifice made of hardwood planks, probably some warehouse.\n");
    add_item(({"similar structure","structure"}),"It looks like a smaller "+
      "version of the large wooden building.\n");
    add_exit(PORT + "s27", "west");
    add_exit(PORT + "s12", "north", "@@query_move");
    add_exit(PORT + "s29", "east");
    reset_room();
}

reset_room()
{
    if(!ob1)
    {
	ob1 = clone_object(PORT + "npc/portguard_e");
	ob1 -> move_living("xxx", TO);
    }

}

query_move()
{
    object *ob;
    int pres,i;
    ob = FILTER_LIVE(all_inventory(this_object()));
    pres = 0;
    for(i = 0; i < sizeof(ob); i++){
	if(ob[i]->query_name() == "Aylmer"){
	    pres = 1;
	}

    }

    if (pres == 1){
	write("You are stopped by the militiaman.\n");
	say(QCTNAME(TP) + " tries to go north but is stopped by the militiaman.\n");
    }

    return pres;
}

