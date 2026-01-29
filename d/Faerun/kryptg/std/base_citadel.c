/*
 * Base Room for the dwarven citadel
 * -- Finwe, July 2007
 */
#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <stdproperties.h>
#include <terrain.h>

inherit "/d/Faerun/highroad/std/base_common.c";
inherit FAERUN_INDOORS_BASE;

object item_found;
int count = 0;

void
create_citadel()
{
}


void
create_indoor_room()
{
    ::create_indoor_room();
    NO_STEEDS;

    extraline = "Room description goes here.";

    set_short("In a ruined citadel");
    create_citadel();

}


/*
 * Function name : set_add_forest
 * Description   : adds descr of forests
 */
string set_add_forest()
{
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
    add_room_tell("A woodpeccker taps on a tree nearby.");
    add_room_tell("Snarls and growls can be heard from nearby.");
    add_room_tell("The forest suddenly falls silent.");
    add_room_tell("Overhead, a large dragon flies by.");

}

/*
 * Function name : set_add_citadel_out
 * Description   : adds descr of outdoors citadel
 */
void set_add_citadel_out()
{
    NO_STEEDS;

    add_item(({"stones", "stone blocks", "blocks"}),
        "They are grey and ancient looking. The blocks are squared and " +
        "stacked on top of each other. They look to be of dwarven " +
        "craftsmanship. The stones are cracked and scaborous looking " +
        "with lichens growing on them.\n");
    add_item(({"lichen", "lichens"}),
        "The lichens are grey, black, and pale white colored. They grow " +
        "on the stone blocks, making the blocks look sickly looking.\n");
    add_item(({"walls"}),
        "The walls are made of stone blocks. They are pitted with age " +
        "and cracked, and covered with lichens.\n");
    add_item(({"floor", "ground"}),
        "The ground is made of flat stone blocks. It is dirty and worn " +
        "in places from constant usage.\n");
}


/*
 * Function name : set_add_altar
 * Description   : adds descr of altar room
 */
void set_add_altar()
{
    add_item(({"altar", "stone altar"}),
        "It's a long and rectangular shaped. The altar is a group of s" +
        "tone blocks haphazardly stacked on each other. There are streaks " +
        "of dried blood down the side. Around the altar is debris.\n");
    add_item(({"blood", "dried blood"}),
        "It is sprayed around the room and on the altar. The blood is " +
        "dried and a dark color.\n");
    add_item(({"walls"}),
        "They are made from stone blocks. The walls are bare but pitted " +
        "with holes.\n");
    add_item(({"floor", "ground"}),
        "The ground is made of flat stone blocks. It is dirty and has " +
        "a stone altar set in the center. There are pools of dried " +
        "blood on the ground, and debris scattered around the room.\n");
    add_item(({"holes"}),
        "The holes are deep and look irregular, probably from racks " +
        "that were ripped out of the walls ages ago.\n");
    add_item(({"debris"}),
        "It's a pile of knawed bones, broken armours, and other garbage. " +
        "The debris is scattered around the room and looks like it " +
        "has been here for many years.\n");
    add_item(({"stones", "stone blocks", "blocks"}),
        "They are grey and ancient looking. The blocks are squared and " +
        "stacked on top of each other. They look to be of dwarven " +
        "craftsmanship. The stones are cracked and scaborous looking " +
        "with lichens growing on them.\n");
    add_item(({"lichen", "lichens"}),
        "The lichens are grey, black, and pale white colored. They " +
        "grow on the stone blocks, making the blocks look sickly looking.\n");
}

// Search function for altars in citadel


string
do_search_altar(object searcher, string str)
{
    int awareness;
    string item = ONE_OF_LIST(BONES);
    int ran_num = random(2);

    FIXEUID;

    awareness = searcher->query_skill(SS_AWARENESS);
    if(awareness < MIN_AWARENESS) 
        return "You need to learn more about your surroundings.\n";
    if(item_found || count == 2) 
        return "Your search reveals nothing.\n";  

    switch(ran_num)
    {
        case 0:
            count++;
            say(QCTNAME(searcher)+ " found nothing in the debris.\n");
            return "You found nothing in the debris.\n";
            break;
        case 1:
            seteuid(getuid(TO));
            item_found = clone_object(OBJ_DIR + item);
            item_found->move(searcher,1);
            say(QCTNAME(searcher)+ " finds something in the debris.\n");
            searcher->add_prop("_found_" + item, 1);
            return "You find a "+item_found->query_short()+" in the debris.\n";
            break;
        default:
            say(QCTNAME(searcher)+ " found nothing in the debris.\n");
            return "You found nothing in the debris.\n";
            break;

    }
}

int exit_check()
{
    if(present("insectman", TO))
    {
        write("The insect blocks your way.\n");
        return 1;
    }
    return 0;
}


/*
 * Function name : 
 * Description   : adds descr of 
 */
void set_add_under_cit()
{
    NO_LIGHT;
    add_item(({"stands", "empty torch stands", "torch stands"}),
        "They are made of several rings attached to the walls. Each " +
        "stand once held a torch, but now they are dusty, empty, and " +
        "rusted.\n");

    add_item(({"stones", "stone blocks", "blocks"}),
        "They are grey and ancient looking. The blocks are squared " +
        "and stacked on top of each other in a zig-zag pattern. They " +
        "look to be of dwarven craftsmanship and still in good condition " +
        "but are cracked and pitted with age.\n");
    add_item(({"lichen", "lichens"}),
        "The lichens are grey, black, and pale white colored. They " +
        "grow on the stone blocks, making the blocks look sickly looking.\n");
    add_item(({"walls"}),
        "The walls are made of stone blocks. They are pitted with age, " +
        "cracked, and covered with lichens. The walls are cold and drip " +
        "with water seeping through the ground, discoloring the blocks.\n");
    add_item(({"water", "dripping water"}),
        "The water is cold and brackish looking. It drips down the walls, " +
        "discoloring the stones.\n");
    add_item(({"floor", "ground"}),
        "The ground is made of flat stone blocks. It is dirty and worn " +
        "in places from constant usage.\n");
    add_item(({"ceiling"}),
        "The ceiling is lined with stone blocks. It is cracked and uneven, " +
        "and looks unstable.\n");
}
