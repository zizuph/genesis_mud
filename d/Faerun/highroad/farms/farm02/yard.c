/*
 * Farm yard
 * By Finwe, August 2006
 */
 
#pragma strict_types
 
#include "/d/Faerun/defs.h"
#include "defs.h"

inherit BASE_FARM;
inherit BASE_COMMON;

object ob;

void
create_farm_room()
{
    iMaxEggs = 3;
    
    set_short("A wide farm yard");
    add_prop(ROOM_S_MAP_FILE, "farm_w_map.txt");

    set_extraline("Large trees surround and shade the farm yard. Wagon " +
        "ruts cut across it in every direction. A large farm house stands " +
        "to the north next to a barn. A large stone wall surrounds the " +
        "farm yard and the house.");

    set_add_road();

    remove_item("grasses");
    remove_item("road");
    remove_item("flowers");

    add_item(({"farmhouse", "house"}),
        "The farmhouse is large and surrounded by trees. It is whitewashed " +
        "and surrounded by a stone wall. Bright flowers grow around " +
        "the house.\n");
    add_item(({"wall", "stone wall"}),
        "It is about waist high and surrounds the house. It is made of " +
        "flat stones piled on top of each other. A large gate is set " +
        "in it to keep animals out of the house.\n");
    add_item(({"stones", "flat stones"}),
        "They are stacked on top of each other and make up the stone " +
        "wall that surrounds the house. The stones are different colors " +
        "of gray, brown, red, and other earth tones.\n");
    add_item(({"barn"}),
        "The barn is set to the west of the yard. It is taller and larger " +
        "than the house, and where farm tools and animals are housed. " +
        "It looks weathered but in good condition.\n");
    add_item(({"yard", "road"}),
        "The yard is large and shaded by trees. The ground is packed " +
        "firm and bare of any weeds or other plants. Trees surround it, " +
        "providing shade and blocking the wind that blows across here. " +
        "Ruts are visible in the yard from wagons that cross it.\n");
    add_item(({"flowers", "wildflowers"}),
        "Many different types of flowers grow around the house. They " +
        "are different colors, shapes, and sizes, and provide a splash " +
        "of color around the house.\n");
    add_item(({"grass", "grasses"}),
        "They grow in clumps around the barn and chicken coop. The grass " +
        "is emerald green with some clover mixed in it. It looks like " +
        "it has been chewed on by farm animals.\n");
    
    reset_room();

    add_exit(FARM2_DIR + "great", "north");
    add_exit(FARM2_DIR + "barn", "northwest");
    add_exit(FARM2_DIR + "rd02", "south");
    
    add_prop(OBJ_S_SEARCH_FUN, "do_search");

    set_add_farm_noises();
    set_add_chicken_noises();

}

void reset_room()
{
    ::reset_room();
    iEggFound = 0;
    if ((ob))
    {
        return;
    }

    ob = clone_object(FNPC_DIR + "flower_npc");
    ob->set_monster_home(FARM2_DIR + "yard");
    ob->move(this_object());

}
