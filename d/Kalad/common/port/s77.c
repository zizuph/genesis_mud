#include "default.h"
inherit PORT_ROOM;

#include "/sys/ss_types.h"
#define HARD_TO_MOVE 10
#define DAMAGE 5
string long;

void
create_port_room()
{
    set_short("Street by the Bay");
    set_long("This street runs aside the bay, travelling in an east-west "+
      "direction. The breaking of the surf just to the south sends up a "+
      "light shower of moisture that makes anything above a run rather "+
      "dangerous here, because of the increased chance of slipping and "+
      "falling. The cobblestones beneath you are covered with grime. A "+
      "long pier lies directly south, jutting into the bay while a large "+
      "building is to the north. An enormous ship is docked to your southwest.\n");
    add_item(({"street"}),"A narrow road that hugs the coastline.\n");
    add_item(({"cobblestones","cobblestone"}),"The pavement is kept "+
      "continually slick from the breaking of the surf. A layer of grime "+
      "blankets its surface.\n");
    add_item(({"layer","grime"}),"A number of rootless plants such as "+
      "moss and lichen have taken to growing on the cobblestones.\n");
    add_item(({"long pier","pier"}),"A large pier where a great many ships "+
      "might land.\n");
    add_item(({"bay"}),"Colored a deep azure, its beauty is marred only "+
      "by the pier in the southeast.\n");
    add_item(({"large building","building"}),"A large structure built "+
      "from hardwood planks. It looks like a warehouse.\n");
    add_item(({"enormous ship","ship"}),"An ancient looking galleon whose "+
      "massive masts tower above the docks.\n");
    add_exit(PORT + "s76", "west");
    add_exit(PORT + "s83", "south","@@move");
    add_exit(PORT + "s78", "east");
}

move()
{
    if(TP->query_skill(SS_SWIM) < random(HARD_TO_MOVE))
    {
	write("You fearfully step onto the pier...\n");
	write("You stumble backwards and hurt yourself for fear of falling off!\n");
	TP->heal_hp(-DAMAGE);
	say(QCTNAME(TP) + " stumbles backwards and gets hurt for fear of falling off the pier!\n");
	if(TP->query_hp() <= 0)
	    TP->do_die(TO);
	return 1;
    }

    write("You bravely step onto the pier.\n");
    return 0;
}

