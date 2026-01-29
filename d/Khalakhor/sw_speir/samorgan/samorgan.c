/**********************************************************************
 * - samorgan.c                                                     - *
 * - Village street in Samorgan                                     - *
 * - Created by Damaris@Genesis 01/2005                             - *
 **********************************************************************/

#pragma no_clone
#pragma save_binary
#pragma strict_types
#include "defs.h"
inherit "/d/Khalakhor/std/room";
#include <filter_funs.h>
#include <macros.h>
#include <stdproperties.h>

/*********************************************************************
 * - Variables to hold our descrip lines to choose from (randomly).- *
 *********************************************************************/
private static string *shorts = ({
  "in the %s section of village of SaMorgan", });

private static string *desc1 = ({
  "\n   This is the %s section of the quiet village of SaMorgan. "+
  "The buildings here are of different shapes and sizes with each "+
  "in fair condition.",
  "\n   This is the %s section of the calm village of SaMorgan. "+
  "The buildings here are of different shapes and sizes with each "+
  "in reasonable condition.",
  "\n   This is the %s section of the tranquil village of SaMorgan. "+
  "The buildings here are of different shapes and sizes with each "+
  "in adequate condition.",
  "\n   This is the %s section of the serene village of SaMorgan. "+
  "The buildings here are of different shapes and sizes with each "+
  "in average condition.",
  "\n   This is the %s section of the fishing village of SaMorgan. "+
  "The buildings here are of different shapes and sizes with each "+
  "in fine condition.",
  "\n   This is the %s section of the peaceful village of SaMorgan. "+
  "The buildings here are of different shapes and sizes with each "+
  "in sufficient condition.",
  "\n   This is the %s section of the still village of SaMorgan. "+
  "The buildings here are of different shapes and sizes with each "+
  "in acceptable condition.", });

private static string *desc2 = ({
  "Reddish clay pots sit outside of the buildings with flowering "+
  "plants springing forth. Finely laid cobblestones make up the "+
  "streets in this quaint village.",
  "Reddish clay pots sit outside of the buildings with flowering "+
  "plants growing in them. Cobblestones complexly laid make up the "+
  "streets in this quaint village.",
  "Reddish clay pots rest outside of the buildings with flourishing "+
  "plants springing forth. Elaborately laid cobblestones make up the "+
  "streets in this quaint village.",
  "Reddish clay pots are placed outside of the buildings with "+
  "blossoming plants growing in them. Finely laid cobblestones make "+
  "up the streets in this quaint village.",
  "Reddish clay pots rest outside of the buildings with blossoming "+
  "plants springing forth. Cobblestones elaborately laid make up the "+
  "streets in this pleasing village.",
  "Reddish clay pots sit outside of the buildings with promising "+
  "plants growing in them. Finely laid cobblestones make up the "+
  "streets in this pleasant village.",
  "Reddish clay pots sit outside of the buildings with emerging "+
  "plants springing forth. Cobblestones intricately laid make up the "+
  "streets in this quaint village.",
  "Reddish clay pots sit outside of the buildings with budding "+
  "plants growing in them. Finely laid cobblestones make up the "+
  "streets in this charming village.", });

private static string *desc3 = ({
  "Smoke from burning fireplaces lingers in the air while salt "+
  "carried in from the sea dominates the surroundings.",
  "Smoldering fireplaces leave a hint of smoke in the air while "+
  "salt brought in from the sea governs the area.",
  "Smoke from burning fireplaces lingers in the air while salt "+
  "brought in from the sea governs the vicinity.",
  "Blazing fireplaces leave a hint of smoke in the air while salt "+
  "carried in from the sea dominates the environment.",
  "Smoke from burning fireplaces lingers in the air while salt "+
  "brought in from the sea presides over the area.",
  "Flaming fireplaces leave a hint of smoke in the air while salt "+
  "carried in from the sea dominates the region.",
  "Smoke from burning fireplaces lingers in the air while salt "+
  "brought in from the sea influences the area.",
  "Burning fireplaces leave a hint of smoke in the air while salt "+
  "carried in from the sea dominates the surroundings.",
  "Smoke from burning fireplaces lingers in the air while salt "+
  "carried in from the sea effects the environment.",});

private static string *extra_long, section = "middle";

/*********************************************************************
 * - This will get added to the end of the compiled long desc.     - *
 *********************************************************************/
public void
set_xlong(mixed arg)
{
	if (stringp(arg))
	arg = ({ arg });
	extra_long = arg;
}

public string *
query_xlong()
{
	return extra_long;
}

/*********************************************************************
 * - Compile the associated items to go with a room description.   - *
 *********************************************************************/
static varargs void
config_items(int x, int y, int z)
{
	set_add_item(0);
	add_item(({"samorgan", "village", "section", "still village", "fishing village", "quaint village", "calm village", "quiet village", "peaceful village", "serene village"}), query_long);
	add_item(({"building", "buildings", "old buildings", "old building"}),
	"The buildings here are of different shapes and sizes with "+
	"each in fairly good condition.\n");
	add_item(({"window", "windows"}),
	"The windows are covered with cloths hanging on this inside.\n");
	add_item(({"doors", "door", "doorway", "doorways"}),
	"The doors and doorways are made from solid oak wood. Some are "+
	"open and some closed.\n");	
	add_item(({"entrances", "entrance"}),
	"The entrances to the buildings seem to be friendly and inviting "+
	"to visitors.\n");
	add_item(({"pots", "pot", "clay pot", "clay pots", "reddish clay pot", "reddish clay pots"}),
	"Reddish clay pots are placed outside of the buildings with "+
	"blossoming plants growing in them.\n");
	add_item(({"plants", "blossoming plants", "flowering plants", "flourishing plants", "budding plants", "emerging plants"}),
	"There are many different types of flowering plants emerging "+
	"from the reddish clay pots.\n");	
	add_item(({"ground", "road", "street"}),
	"The street is made up with finely laid cobblestones and dirt.\n");
	add_item(({"cobblestone", "cobblestones", "fine cobblestones"}),
	"Many bright cobblestones are firmly laid to make up an obvious "+
	"and sturdy road.\n");
	add_item(({"air"}),
	"The air is humid from the sea but is nice and cool.\n");
	add_item(({"sky"}),
	"The sky is grey with bright white puffy clouds looming over "+
	"the village.\n");
	add_item(({"house", "houses", "home", "homes"}),
	"There are quaint homes scattered now and again between the "+
	"businesses. Some appear to be empty, while others seem to be "+
	"bristling with life.\n");
	add_item(({"dirt", "soil"}),
	"The dirt is made from a dark rich looking soil. It is mingled "+
	"with bright cobblestones that make up the street.\n");
	add_item(({"smoke", "chimney smoke"}),
	"Smoke rises and dissipates through the salted air.\n");
	
}

/*************************************************************************
 * - Compile the associated room tells to go with the room description.- *
 *************************************************************************/
static varargs void
config_tells(int x, int y, int z)
{
	clear_tells();
	set_tell_time(10 + random(5));
	add_tell("From the distance, you hear young girls laughing.");
	add_tell("A crow flying to the far north catches your eye.");
	add_tell("You hear the sound of hammering in the distance.");
	add_tell("You hear a group of sailors shouting in the distance.");
	add_tell("A group of children scurry by playing a game.");
	add_tell("Some debris blow past you along the street.");
	add_tell("A soft breeze brings the soft scent of the sea.");
}

/*********************************************************************
 * - Compile a random room description with associated items.      - *
 *********************************************************************/
static varargs void
config_room(string str, string extra = "")
{
	mixed *arr = allocate(3);
	
	if (strlen(str))
        section = str;
        
        arr[0] = random(sizeof(desc1));
        arr[1] = random(sizeof(desc2));
        arr[2] = random(sizeof(desc3));
        
        config_items(arr[0], arr[1], arr[2]);
        config_tells(arr[0], arr[1], arr[2]);
        
        arr[0] = desc1[arr[0]];
        arr[1] = desc2[arr[1]];
        arr[2] = desc3[arr[2]];
        
        set_short(sprintf(one_of_list(shorts), section));
        set_long(sprintf("%s %s %s %s %s\n",
        sprintf(arr[0], section), arr[1], arr[2],
        (pointerp(extra_long) ? one_of_list(extra_long) : one_of_list(({
		"The fishing village of SaMorgan continues on in all directions." }))), extra));

}

/*********************************************************************
 * - Basic room stuff.                                             - *
 *********************************************************************/
static void
create_khalakhor_room()
{
	set_name("samorgan");
}

