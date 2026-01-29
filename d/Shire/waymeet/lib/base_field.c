/*
 * Base room for Waymeet fields
 * -- Finwe, March 2019
 */

//#include "/d/Shire/sys/defs.h"
//#include "../defs.h"
//#include <stdproperties.h>
//#include <terrain.h>
//
//inherit AREA_ROOM;
//inherit "/d/Shire/lib/time_sky_descr";

#include "/d/Shire/sys/defs.h"
#include "defs.h"
#include <stdproperties.h>
#include <terrain.h>
inherit AREA_ROOM;
inherit "/d/Shire/std/room/room_tell";
inherit "/d/Gondor/common/lib/herbsearch";


//vegetable file names that are cloned or can be picked
#define VEG_NAMES ({"beet", "cabbage", "carrot"})

#define EXTRA_VEG ({"Bushy green carrot tops poke up among the rows of vegetables.", "Round green cabbages look plump and fat here. They look like the types of cabbages rabbits would like to eat.", "Beet greens rise above the fields. There must be beets to pick!"})

//number of times a player can pick veggies, or that are in a field
#define MAX_VEGS 4


// vegetable vars
int veg_count = 0;
string veg_extra();
public void add_wolf();



void
create_field()
{
}

void
create_area_room()
{
    setuid(); 
    seteuid(getuid());

    area = "near"; /* Distance from areaname */
    areaname = "Waymeet";
    land = "the Shire";
    areatype = 4;
    areadesc = "vegetable field";
    
    extraline = "";

    create_field();

    add_item(({"surroundings","expanse","plain","shire"}),
      "The Shire is an expanse of plains, with the occasional village "
      +"or cultivated field, where the hobbits till the rich soil of the "
      +"Shire.\n");
    add_item(({"tracks","track","animal tracks", "prints", "pawprints", "paw prints"}),
      "You see quite a few tracks across the fields here. " +
      "They're from something fairly big like a dog or a wolf.\n");
    add_item(({"field", "fields"}),
        "These fields provide food for the village of Waymeet.\n");
    add_item(({"vegetables", "cabbage", "cabbages", "carrots", "beets", "food"}),
        "Many large and healthy vegetables fill these rows. They all look " +
        "like they are nearly ripe. " + veg_extra() + "\n");
    add_item(({"village", "Waymeet", "waymeet"}),
        "To the south you can see the small village of Waymeet.\n");
    add_item(({"farm", "house", "farmhouse", "farm house", "barn"}),
        "You can see the main farm buildings not far from here.\n");
	remove_item("furrow");
	add_item( ({"furrow", "furrows"}), "The furrows are long trenches dug with a "
		+ "plow so that farmers can more easily plant crops. Here you notice those "
		+ "crops are vegetables for the village to eat.\n");
        
    add_npc(WAYM_NPC_DIR + "wolf", random(3));
        
}


// pick vegetable
int
pick_vegetable(string str)
{
    object vegetable;
    string vegetable_file = ONE_OF_LIST(VEG_NAMES);
    string vegetable_short = "";
    
    if((str == "vegetable"))
    {
        if (veg_count == MAX_VEGS)
        {
            write("It looks like the field has been picked clean.\n");
            return 1;
        }
//          setuid();
//          seteuid(getuid());
          vegetable = clone_object(WAYM_OBJ_DIR + vegetable_file);
          vegetable->move(this_player(), 1);

        write("You reach out and pick " + vegetable->short() + " from the field.\n");
        say(QCTNAME(TP) + " picks a vegetable from the field.\n");
        veg_count = veg_count + 1;
        return 1;
    }
    else
    {
        write("Pick what, a vegetable?\n");
        return 1;
    }

}

// function to add a wolf to fields.
public void add_wolf()
{
    add_npc(WAYM_NPC_DIR + "wolf", random(3));
}

//Adds some Juniper trees and the ability to search for juniper
// an herb for a task.

void
add_trees()
{
	add_item( ({"tree", "pine tree", "trees", "pine trees", "juniper trees", "juniper tree"}),
		"Large, mature pine trees grow here, in a row. It looks as if they were planted "
		+ "as a way to keep the wind at bay. You see some berries on the "
		+ "branches, but would need to look closer to see if any of them are "
		+ "ready to pick.\n");
	add_item( ({"berry", "berries"}), "These look like juniper berry herbs to you. "
		+ "But without searching it's hard to tell.\n");
	add_item("row", "The trees are planted in a row, a common strategy farmers use "
		+ "to slow the wind down and keep it from blowing away their top soil.\n");
	add_cmd_item("a closer look", "take", "You take a closer look but don't "
		+ "see much more, maybe because you were too much in a hurry. Have "
		+ "you thought about searching?\n");

	set_up_herbs( ({"/d/Shire/common/herbs/juniper"}), 
		({"tree", "trees", "pine tree", "pine trees"}), 5);
}

string
veg_extra()
{
	string veg;
	veg = ONE_OF_LIST(EXTRA_VEG);
	return veg;
}

void
add_shed()
{
	remove_item("field");
	remove_item("farm");
	remove_item("furrow");
	remove_item("vegetable");
	
	add_item( ({"field", "fields"}), "These fields have furrow after furrow of "
		+ "the Shire's most famous crop--Pipeweed!\n");

	add_item( ({"furrow", "furrows"}), "The furrows are long and straight. They've "
		+ "been expertly and lovingly plowed. You can see tobacco plants growing "
		+ "out of them.\n");
	
	add_item( ({"tobacco", "pipeweed", "Pipeweed", "plants", "tobacco plants"}),
		"The tobacco plants grow tall here. The plants look healthy and the "
		+ "leaves wide. This should be a good crop of pipweed!\n");
	
	add_item( ({"farm", "farmhouse", "shed", "house", "curing shed"}), 
		"A farmhouse and curing shed sit on the soutwest corner of the fields. "
		+ "Both of them are painted bright red. Around them the grass is neat "
		+ "and tidy, and the steps swept. The Pipeweed business must be "
		+ "profitable!\n");
	add_item( ({"step", "steps"}), "This far away, it's impossible to see "
		+ "exactly what kind of wood the steps are made from, but they look "
		+ "clean and lovingly cared for.\n");
	add_item( ({"grass", "lawn"}), "The grass looks like it's been cut short. "
		+ "It's completely green with no brown spots whatsoever. Some hobbit "
		+ "has spent a lot of time keeping it just so!\n");
}

