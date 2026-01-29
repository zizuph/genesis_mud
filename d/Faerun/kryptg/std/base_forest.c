/*
 * Base Room Kryptogarden Forest
 * -- Finwe, July 2007
 */
#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"
#include "/d/Faerun/orcmaker/orcmaker.h"
#include <stdproperties.h>
#include <terrain.h>

inherit "/d/Faerun/highroad/std/base_common.c";
inherit FAERUN_OUTDOOR_BASE;

#define MAX_NPCS    4
#define ORCMAKER_DIR    "/d/Faerun/orcmaker/"

static object *npc = allocate(MAX_NPCS);

object strong_orc;

void
create_forest()
{
}

void create_orcs();

void
create_faerun_room()
{
    
    ::create_faerun_room();
    add_prop(ROOM_S_MAP_FILE, "krypt_forest_map.txt");

    extraline = "Room description goes here.";

    set_short("Somewhere in a dark forest");
//    set_long(short() + ". " + extra_line + "\n");
    create_forest();
}

// Forest descriptions

string forest_descr1(string str)
{
    return "The forest is full of ancient trees. Their tops soar overhead, " +
    "blocking much of the light. There are thin bushes growing beneath the " +
    "trees. Some look trampled, probably by some of the many creatures who " +
    "live here. "+ str;
}

string forest_descr2(string str)
{
    return "The trail weaves its way past ancient trees. Their tops are " +
    "hidden above you. Some light trickles down to the ground below. Thin " +
    "bushes grow in clumps beneath the trees. "+ str;
}

string forest_descr3(string str)
{
    return "Ancient trees fill the forest. The ground is littered with " +
    "branches, rotting trees, and other forest debris. Light trickles " +
    "down from the branches above. Mosses and fungi grow in the shade. "+ str;
}

string forest_descr4(string str)
{
    return "Branches and other forest debris litter the ground and hide " +
    "the trail. Trampled bushes grow at the base of the trees. On the " +
    "trees are deep scratches and gouges, probably from creatures who " +
    "inhabit the forest. "+ str;
}

string forest_descr5(string str)
{
    return "Rotting logs lay scattered across the ground. They are buried " +
    "by fallen branches and rotting leaves. Mosses and fungi grow on the " +
    "logs. They are shaded by the forest's trees. "+ str;
}

/*
 * Function name : set_add_forest
 * Description   : adds descr of forests
 */
string set_add_forest()
{
    add_std_herbs("forest");

    add_item(({"thick trees", "thick tree", "trees", "ancient trees"}),
        "They are ancient and giant in size. Their tops reach " +
        "to the sky and dwarf the trees below them.\n");
    add_item(({"plants", "woodland plants"}),
        "Besides trees, a diverse number of plants grow in the " +
        "forest. Bushes grow everywhere, many " +
        "hampering your travel and blocking your view.\n");
    add_item(({"bushes", "shrubs"}),
        "Bushes of different color and sizes grow everywhere. " +
        "Some are thick and block your view while others are " +
        "thin and spindly.\n");
    add_item(({"moss", "mosses"}),
        "Moss can be seen growing on logs, rocks, on trees, and " +
        "under the trees in patches. It is healthy and a deep " +
        "green. Some patches of moss are so large that bumps " +
        "can be seen under them.\n");
    add_item(({"lichen", "lichens"}),
        "Lichens grow on the trees and rotting logs. It is grey " +
        "and white coloured. Some are simple while others are " +
        "large and fan shaped\n");
    add_item(({"hollow logs", "hollow log"}),
        "The logs are rotting and hollowed out. Most of them " +
        "are partially buried in the ground or the forest debris. Moss " +
        "grows on them in a soft carpet of green.\n");
    add_item(({"ground", "forest debris", "debris", 
        "forest's floor", "floor", "down"}),
        "The ground is littered with dead branches, leaves, " +
        "and some fallen trees.\n");
    add_item(({"leaves", "leaf"}),
        "You see a mat of both fresh and dead leaves covering the " +
        "ground. Poking out of them are dead branches, some " +
        "plants, stones, and other signs of a living forest.\n");
    add_item(({"fallen branches", "dead branches", "dead branch", 
            "branches", "branch"}),
        "They are broken and lay scattered across the ground. " +
        "Some look like they just fell from the trees, " +
        "splintered and twisted. They lay on the ground in " +
        "various stages of decomposition.\n");
    add_item(({"twig", "twigs"}),
        "They are small branches, laying scattered across the " +
        "forest's floor.\n");
    add_item(({"fallen trees", "fallen tree", "dead trees", 
        "dead tree"}),
        "Some fallen trees lay rotting under a blanket of fallen " +
        "leaves and forest debris.\n");
    add_item(({"log", "logs", "rotting log", "rotting logs"}),
        "The rotting logs are in various forms of decomposition. " +
        "Some are hollowed out and look to be homes for " +
        "woodland animals.\n");
    add_item(({"forest"}),
        "The forest is large and stretches in all directions. " +
        "Tall, ancient trees are everywhere. Some have fallen over, " +
        "others grow tall and block the " +
        "sky above. Fallen branches, leaves, pine needles, and other " +
        "debris cover the forest's floor.\n");
    add_item(({"undergrowth", "underbrush"}),
        "Dense bushes grow under the trees, making travel " +
        "through the forest difficult and obscuring your way.\n");
    add_item(({"scratches", "deep scratches"}),
        "They are deep gouges in tree trunks. The scratches were made " +
        "by wild creatures that wander through the forest. They are " +
        "irregular shaped and look fierce.\n");

    add_room_tell("The branches move in the breeze.");
    add_room_tell("Growling sounds echo from nearby.");
    add_room_tell("A woodpecker taps on a tree nearby.");
    add_room_tell("Snarls and growls can be heard from nearby.");
    add_room_tell("The forest suddenly falls silent.");
    add_room_tell("Overhead, a large dragon flies by.");
   
}

/*
 * Function name : set_add_mts
 * Description   : adds descr of Sword Mountains
 */
void set_add_mts()
{
   add_item(({"mountains", "range of mountains", "sword mountains"}),
        "The mountains rise to the west and known as the Sword Mountains. " +
        "Their peaks touch the sky and look rugged. The mountains run " +
        "roughly northeast and southwest, and the forest grows up to the " +
        "base of the mountains.\n");
    add_item(({"mountain peaks"}),
        "They are rugged looking and tower in the distance. " + CAP(CLOCK->query_light_type()) + " glistens on the peaks, which " +
        "touch the sky and look like sharp spears.\n");  
}

/*
 * Function name : set_add_citadel
 * Description   : adds descr of dwarven citadel in the forest.
 */
void set_add_citadel()
{
    add_item(({"citadel", "ancient citadel"}),
        "The citadel is very tall. It is ancient looking and made of " +
        "stone. The citadel looks like it has been abandoned for " +
        "countless ages and has fallen into disrepair.\n");
}

/*
 * Function name : set_add_mt_caves
 * Description   : adds descr of caves in the side of Sword Mts
 */
void set_add_mt_caves()
{
    add_item(({"cave", "caves"}),
        "They are natural openings in the side of the mountains. Many " +
        "are large, and irregular shaped, and in the upper reaches of the mountain.\n");
}

/*
 * Function name : set_add_ravine
 * Description   : adds descr of ravine that leads to 
 *                 Claugiyliamatar's lair
 */
void set_add_ravine()
{
    add_item(({"ravine", "crevasse", "valley"}),
        "The ravine cuts through the forest, running northwest and " +
        "southeast. The deep valley is dangerous looking and impassable.\n");
}

void create_orcs()
{
    int index, npc_count;

    npc_count = random(MAX_NPCS);

    if(npc_count ==0)
        npc_count = 4;


        for(index = 0; index < npc_count; index++)
        {
            if (!objectp(npc[index]))
            {
                npc[index] = clone_object(ORCMAKER_DIR+"orcmaker");
                npc[index]->set_orc_type(TOUGH);
                npc[index]->set_restrain_path(FOR_DIR);
                npc[index]->set_random_move(3);
                npc[index]->move(TO);
            }
         }      
     tell_room(TO,"A group of orcs rush in.\n");
       
}