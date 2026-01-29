/* created by Aridor, 08/12/94 */

#include "local.h"
#include RND_MEET

inherit SOLACE_ROOM

void
reset_solace_room()
{
    object drac;
    if (!P("baaz",TO))
    {
	drac = RANDOM_MEET(DRAC_TABLE);
	drac->set_color("red");
	drac->set_random_move(10);
	drac->move(TO);
    }
}

void
create_solace_room()
{
    set_short("Haven Road");
    set_long("You are standing on the road leading from Solace to Haven. " +
	     "Around you are a few scattered bushes and trees. Further " +
	     "to the north you can see water. There are mountains " +
	     "rising up into the sky in the northwest and also far away " +
	     "in the east. The road leads north and west, where it " +
	     "appears to run over a bridge.\n");
    add_exit(SOLACE_VILLAGE,"north", 0, 2);
    add_exit(HROAD + "bridge","west",0,2);
    add_invis_exit(HROAD + "path1","southeast","@@closed@@",2);
    
    add_item(({"bushes","trees"}),
	     "They are scattered about the landscape around you but you " +
	     "cannot see anything special about them. Maybe except for " +
             "something that could be a path leading southeast into the " +
             "greenery. The land " +
	     "is quite flat around here, except the mountains you can see " +
	     "further away to the northwest and east.\n");
    add_item(({"water"}),
	     "You guess the water there in the distance is " +
	     "Crystalmir lake. Looking further north you can see " +
	     "dark clouds gathering high in the sky.\n");
    add_item("clouds",
	     "These are ordinary clouds, but they still look quite dark " +
	     "and menacing, even from this distance.\n");
    add_item("bridge",
	     "It's most likely a bridge, but you cannot see anything " +
	     "from this far away.\n");
    add_item("mountains",
	     "The mountains in the northwest are quite high and barren, " +
	     "and they are not very far away. To the east you can see the " +
	     "mountains only in the distance and you cannot make out any " +
	     "details.\n");
    add_item("road",
	     "It's a gravel road leading northeast and west.\n");
    reset_room();
}


int
block()
{
    write("The tree village Solace is under attack by dragons and " +
	  "draconians. The wizards of Krynn, has yet again, gone into " +
	  "battle to defend their creation. The battle will go on for " +
	  "several hours, since the wizards are few and the dragons are " +
	  "many. The only thing you can do is to pray to the gods and " +
	  "give them all the support you can.\n");
    return 1;
}



int
closed()
{
    write("You step off the road into the foliage.\n");
    find_player("aridor")->catch_msg("*OLD GUILD* " + TP->query_name() + " enters.\n");
    return 0;
}
