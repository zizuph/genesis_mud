/*
 * Base room for Waymeet fields
 * -- Finwe, March 2019
 * 
 * Adjusted very slightly for base file for the tobacco fields of Waymeet.
 * --Raymundo, March 2020
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
    add_item(({"village", "Waymeet", "waymeet"}),
        "To the south you can see the small village of Waymeet.\n");
       remove_item("furrow");
    add_item( ({"field", "fields"}), "These fields have furrow after furrow of "
        + "the Shire's most famous crop--Pipeweed!\n");
    add_item( ({"furrow", "furrows"}), "The furrows are long and straight. They've "
        + "been expertly and lovingly plowed. You can see tobacco plants growing "
        + "out of them.\n");
    add_item( ({"tobacco", "pipeweed", "Pipeweed", "plants", "tobacco plants"}),
        "The tobacco plants grow tall here. The plants look healthy and the "
        + "leaves wide. This should be a good crop of pipweed!\n");

    add_item( ({"grass", "lawn"}), "The grass looks like it's been cut short. "
        + "It's completely green with no brown spots whatsoever. Some hobbit "
        + "has spent a lot of time keeping it just so!\n");

}

void
add_house()
{
    add_item( ({"farm", "farmhouse", "shed", "house", "curing shed"}), 
        "A farmhouse and curing shed sit on the soutwest corner of the fields. "
        + "Both of them are painted bright red. Around them the grass is neat "
        + "and tidy, and the steps swept. The Pipeweed business must be "
        + "profitable!\n");
    add_item( ({"step", "steps"}), "This far away, it's impossible to see "
        + "exactly what kind of wood the steps are made from, but they look "
        + "clean and lovingly cared for.\n");
    
}
// function to add a wolf to fields.
public void add_wolf()
{
    setuid();
    seteuid(getuid());

    object wolf;
    if(!objectp(wolf))
    {
        wolf = clone_object("/d/Gondor/common/npc/wolf");
//        wolf->set_restrain_path("/d/Shire/waymeet/rooms/fields");
        wolf->set_restrain_path(WAYM_FIELD_DIR);
        wolf->set_random_move(2);
        wolf->set_short("mangy grey wolf"); //set this to make this wolf unique from the gondor wolves.
        wolf->add_adj("mangy");
        wolf->add_leftover(WAYM_ARM_DIR + "wolf_pelt", "pelt", 1, 0, 1, 100);
        wolf->move(TO);
    }
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
    add_item( ({"berry", "berries"}), "These look like juniper berries to you. "
        + "But without taking a closer look it's to tell.\n");
    add_item("row", "The trees are planted in a row, a common strategy farmers use "
        + "to slow the wind down and keep it from blowing away their top soil.\n");
    add_cmd_item("a closer look", "take", "You take a closer look but don't "
        + "see much more, maybe because you were too much in a hurry. Have "
        + "you thought about searching?\n");

    set_up_herbs( ({"/d/Shire/common/herbs/juniper"}), 
        ({"tree", "trees", "pine tree", "pine trees"}), 5);
}

string
my_extra()
{
    int ext = random(4);
    switch(ext)
    {
        case 0:
        return("Tall tobacco plants grow in these fields, reaching nearly to "
        + "a hobbit's shoulder. Their leaves are green and healthy, and will "
        + "eventually become the famous Pipeweed of the Shire. Across the "
        + "fields you see a farmhouse and curing shed.");
        break;
        
        case 1:
        return("Tobbaco plants reach from the furrows to the sky. They sway "
        + "back and forth in the breeze, growing and waiting for harvest "
        + "when they will be placed in the curing shed to become Pipeweed.");
        break;
        
        case 2:
        return("The field is lined with furrows. Out of each furrow grows a row"
        + " of tobacco plants. The tobacco will be cured in the shed next to "
        + "the farmhouse and eventually exported as Pipeweed.");
        break;
        
        case 3:
        add_wolf();
        return("Tobacco plants grow in straight furrows here. "
            + "Between the plants, you notice paw prints--big ones. "
            + "Wolves seem to be near. Nevertheless,"
            + "the tobacco is tall and the farmhouse looks peaceful.");
        break;
        
        default:
        return("Tall tobacco plants grow in these fields, reaching nearly to "
        + "a hobbit's shoulder. Their leaves are green and healthy, and will "
        + "eventually become the famous Pipeweed of the Shire. Across the "
        + "fields you see a farmhouse and curing shed.");
        break;
    }
}
        

