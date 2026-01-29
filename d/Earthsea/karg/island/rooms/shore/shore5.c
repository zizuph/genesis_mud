#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include "../../std/defs.h"

inherit ISL_DIR+"/std/room";

void
create_island_room()
{
	set_short("Near the forest");
	set_long("You are approaching a dense forest. To the "+
		 "west you see a sandy beach, but here the sand"+
		 " is covered with patches of vegetation - some"+
		 " grass and low bushes. The forest to east looks "+
		 " less dense here.\n\n");

	add_exit(SROOMS+"/shore4","north");
	add_exit(SROOMS+"/shore6","south");
	add_exit(FROOMS+"/path0","east","@@enter_forest");
	add_exit(SROOMS+"/shore2","west");
	
	add_item(({"bush","bushes","vegetation"}),
		"Low bushes with thick watery leaves."+
		"You can clearly see some salt on the leaves.\n\n");
	add_item("forest","@@exa_forest");
}


string
exa_forest()
{
	string s= "Mighty oaks spread their branches above"+
		  " thick undergrowth. ";
	if (TP->query_skill(SS_TRACKING)<20)
		return s+"You desperately look for some sign of "+
		"a trail, but alas...\n\n";
	else
		return s+"You look for some trail and after "+
		"a considerable effort find one.\n\n";

}

int
enter_forest()
{
	if (TP->query_skill(SS_TRACKING)<10)
	{
		write("You look at all these entangled branches"+
		" and your head starts to spin counterclockwise."+
		" No chance that you are going to find your way "+
		"through this mess.\n\n");
		say(QTNAME(TP)+" tries to enter the forest, but "+
		"gives up quickly\n\n");
		return 1;
	}
	if (TP->query_skill(SS_TRACKING)<20)
	{
		write("You try to find your way through the "+
		"thorny bushes, but end up at the same place "+
		"all your face and arms covered with nasty "+
		"scratches.\n\n"); 
		say(QTNAME(TP)+" enters the thicket, but after"+
		" a few moments rushes back out all covered "+
		"with scratches\n\n");
		return 1;
	}
	if (TP->query_skill(SS_TRACKING)<30)
	{
		write("You bravely step into the thicket "+
		"pushing aside thorny branches. After some "+
		"struggle you manage to break through and "+
		"are safely inside the forest with only some "+
		"scratches on you.\n\n");
		say(QTNAME(TP)+" breaks into the thicket. You "+
		"hear a loud noise fore some moments, then all "+
		"is quiet again.\n\n");
		tell_room(FROOMS+"/path0",
			  "You suddenly hear some noises out of"+
			  " the bushes. Terrified, you turn to "+
			  "run away but at the last moment "+
			  "notice "+QTNAME(TP)+"emerging from"+
			  "the thicket.\n\n");
		TP->move_living("X",FROOMS+"/path0");
		return 1;
	}
	write("You skillfully wade into the thicket avoiding "+
	"the thorns easily. After jsut a few moments you are "+
	"already on the other side, with not a scratch on you, "+
	"looking warily at the forest ahead.\n\n");
	say(QTNAME(TP)+" skillfully disappears into the forest "+
	"with only an occasional creak of a branch.\n\n");
	tell_room(FROOMS+"/path0",
		  QTNAME(TP)+" suddenly emerges from"+
		  " the thicket.\n\n");
	TP->move_living("X",FROOMS+"/path0");
	return 1;
}
