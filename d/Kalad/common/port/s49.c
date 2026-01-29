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
    set_short("Corner of two streets");
    set_long("You are at the corner where two narrow streets intersect. "+
      "An extremely large building lies to your west and south, taking up "+
      "most of your field of view. The cobblestones of the road are moist "+
      "and covered with grime. One street heads north towards a small square while "+
      "the other travels east into the heart of the district.\n");
    add_item(({"corner","two narrow streets","two streets","streets","narrow streets","narrow street","street"}),
      "The intersection of two narrow roads.\n");
    add_item(({"extremely large building","large building","building"}),
      "A large wooden structure built from hardwood planks. From its "+
      "gigantic size you assume it must be a warehouse. The section "+
      "immediately to your west has a sign hanging in front of it.\n");
    add_item(({"sign"}),"A large brightly painted sign. There is some "+
      "writing on it.\n");
    add_item(({"cobblestones","cobblestone","road"}),"The pavement is "+
      "weatherbeaten and cracked in several places, also a thin film of "+
      "moisture covers it, allowing several plants to grow on the cobblestones.\n");
    add_item(({"grime","plants","plant"}),"Moss, lichen and a number of "+
      "other rootless plants are growing on the road.\n");
    add_exit(PORT + "s36", "north");
    add_exit(PORT + "s48", "west", "@@block");
    add_exit(PORT + "s59", "south", "@@query_move");
    add_exit(PORT + "s50", "east");
    reset_room();
}

reset_room()
{
    if(!ob1)
    {
	ob1 = clone_object(PORT + "npc/portguard_n");
	ob1 -> move_living("xxx", TO);
    }

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
    "                ((((((((((((((((((((((((((((()\n"+
    "                (|~~~~~~~~~~~~~~~~~~~~~~~~~~()\n"+
    "                (|         AYRIA'S          ()\n"+
    "                (|        HOUSE  OF         ()\n"+
    "                (|          GAMES           ()\n"+
    "                (|@@@@@@@@@@@@@@@@@@@@@@@@@@()\n"+
    "                ((((((((((((((((((((((((((((()\n"+
    "                ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
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
	say(QCTNAME(TP) + " tries to go south but is stopped by the militiaman.\n");
    }

    return pres;
}

block()
{
    write("This building has been closed for failure to pay city taxes. "+
      "If you come back later, perhaps the owner will have payed the "+
      "proper fees and this establishment will be open.\n");
    return 1;
}

