#pragma strict_types
#include "/d/Avenir/common/common.h"
#include <stdproperties.h>
#include <filter_funs.h>
#include <composite.h>
#include <language.h>
#include <ss_types.h>
#include <macros.h>
#include <tasks.h>
#include <terrain.h>

inherit "std/room";

int animal_path; // The path has 3 + 3 + 3 possible directions in path3, animalpath1 and animalpath2

void
create_room()
{
    set_short("On an old animal path");
    set_long("@@desc_long");
    add_exit("path2","nw");
    add_item("heather", "@@desc_heather");
	add_item("path", "@@desc_path";
    set_terrain((TERRAIN_OUTSIDE) || (TERRAIN_OPEN_SPACE) 
		|| (TERRAIN_SMALL_PLANT) || TERRAIN_ROUGH));
	int animal_path = rnd() 9;  //Creates the route for the animal path that starts in path 3
    reset_room();
}

void
reset_room()
{
	return;
}

void
init()
{
    ::init();
    add_action("walk_through", "walk");
}

int
walk_through(string str)
{
  if (strlen(str) && (str == "through") || (str == "through heather"))
  {
    write("You take a step into the thick growing heather " +
			" but it is really to thick to try.\n");
	say(QCTNAME(TP) + 
			" takes a step out into the heather " +
			"but it seems like a hard task which is immidiately " +
			"terminated.\n");
	tell_room(THIS_DIR + "path3",
		CAP(LANG_ADDART(TP->query_nonmet_name())) +
			" takes a step out into the heather " +
			"but it seems like a hard task which is immidiately " +
			"terminated.\n");
    return 1;
  }
  else
  return 0;
}

string
desc_long()
{
    string text;
    text = 	"This is an old path through a barren landscape. To the west a steep mountain side " +
			"prevents you from going west and to your right a sloap covered with thick heather " +
			"spreads up towards a mountain ridge. ";
    if (TP->query_skill(track >= 50))
        {
			text +=	"Looking closer at the thick heather you can see it is growing thick " +
					"making it hard to walk through.";
        }
	if (TP->query_skill(track =>70))
		{
			text += ""
		}
	text += "\n"
    return text;
}
	
int
desc_heather()
	write("You lean down and look close at the heather. Old and dry " +
			"and very thick preventing anything else to grow here.\n");
	say(QCTNAME(TP) + " crouches down, and looks closely at the " +
			"thick growing heather.\n");
	tell_room(THIS_DIR + "path1",
		CAP(LANG_ADDART(TP->query_nonmet_name())) +
		" crouches down, and looks closely at the " +
			"thick growing heather .\n");
    return 1;
	
int
desc_path()
	write("You take a quick look at the path. It stretches in a northwest-" +
			"southeast direction and you can not see anything remarkable " +
			"about it.\n");
	say(QCTNAME(TP) + "lifts " + TP->query_possesive() + "eyes and follow the path " +
			"along it's way through the landscape.\n");
	tell_room(THIS_DIR + "path1",
		CAP(LANG_ADDART(TP->query_nonmet_name())) +
		"lifts " + TP->query_possesive() + "eyes and follow the path " +
			"along it's way through the landscape.\n");
	return 1;

int
search_far_away_items(string str)
{
    if ((str == "landscape") || (str == "mountain") || (str == "ridge")
        || (str == "mountain side") || (str == "mountain ridge") || ("sloap"))
        write("The " +str+ " is to far away to search.\n");
        return 1;
}

int
query_animal_path()
{
	return animal_path;
}
