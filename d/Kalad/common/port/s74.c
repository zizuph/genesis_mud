#include "default.h"
inherit PORT_ROOM;

#include "/sys/ss_types.h"
#define HARD_TO_MOVE 10
#define DAMAGE 25
string long;

void
create_port_room()
{
    set_short("Small Intersection on the Street by the Bay");
    set_long("This is a small intersection by the bay.\n"+
      "This street runs aside the bay, travelling in an east-west "+
      "direction. The breaking of the surf just to the south sends up a "+
      "light shower of moisture that makes anything above a run rather "+
      "dangerous here, because of the increased chance of slipping and "+
      "falling. The cobblestones beneath you are covered with grime. Two "+
      "large buildings lie to the northwest and northeast, while an enormous "+
      "ship is docked just to the south. A large rope walkway heads south. "+
      "Northward lies the center of the Port District.\n"+
      "A large metal sign stands here.\n");
    add_item(({"street","intersection"}),"A narrow road that hugs the coastline.\n");
    add_item(({"cobblestones","cobblestone"}),"The pavement is kept "+
      "continually slick from the breaking of the surf. A layer of grime "+
      "blankets its surface.\n");
    add_item(({"layer","grime"}),"A number of rootless plants such as "+
      "moss and lichen have taken to growing on the cobblestones.\n");
    add_item(({"bay"}),"Colored a deep azure, its beauty is mirrored "+
      "only by the skies above.\n");
    add_item(({"skies","sky"}),"It is a mirror image of the bay beneath "+
      "it.\n");
    add_item(({"large buildings","large building","buildings","building"}),
      "A large structure built "+
      "from hardwood planks. It looks to be a warehouse.\n");
    add_item(({"large metal sign","large sign","metal sign","sign"}),
      "There is writing on it, perhaps you should read it.\n");
    add_item(({"enormous ship","ship"}),"An ancient looking galleon whose "+
      "massive masts tower above the docks.\n");
    add_item(({"large rope walkway","large walkway","rope walkway","walkway"}),
      "A weathered rope bridge that connects the enormous ship with the "+
      "mainland Port District.\n");
    add_exit(PORT + "s73", "west");
    add_exit(PORT + "s61", "north");
    add_exit(PORT + "s75", "east");
    add_exit(PORT + "seahawk/boat1", "south","@@move");
}

init()
{
    ::init();
    AA(read_sign,read);
}

string
sign()
{
    return "\n"+
    " {(!)}{(!)}{(!)}{(!)}{(!)}{(!)}\n"+
    " {(!)}+~~~~~~~~~~~~~~~~~~+{(!)}\n"+
    " {(!)}+   THE  SEAHAWK   +{(!)}\n"+
    " {(!)}+  ~~~~~~~~~~~~~~  +{(!)}\n"+
    " {(!)}+->Historic  Site<-+{(!)}\n"+
    " {(!)}++++++++++++++++++++{(!)}\n"+
    " {(!)}~~~~~~~~~~~~~~~~~~~~{(!)}\n"+
    " {(!)}+    First Ship    +{(!)}\n"+
    " {(!)}+     of Kabal     +{(!)}\n"+
    " {(!)}+__________________+{(!)}\n"+
    " {(!)}{(!)}{(!)}{(!)}{(!)}{(!)}\n"+
    " {(!)}{(!)}{(!)}{(!)}{(!)}{(!)}\n"+
    "           {(!)}{(!)}\n"+
    "           {(!)}{(!)}\n"+
    "           {(!)}{(!)}\n"+
    "           {(!)}{(!)}\n"+
    "           {(!)}{(!)}\n"+
    "           ~~~~~~~~~~\n";
}

move()
{
    if(TP->query_skill(SS_SWIM) < random(HARD_TO_MOVE))
    {
	write("You fearfully step onto the walkway...\n");
	write("You stumble backwards and hurt yourself for fear of falling off!\n");
	TP->heal_hp(-DAMAGE);
	say(QCTNAME(TP) + " stumbles backwards and gets hurt for fear of falling off the walkway!\n");
	if(TP->query_hp() <= 0)
	    TP->do_die(TO);
	return 1;
    }

    write("You bravely step onto the walkway.\n");
    return 0;
}

