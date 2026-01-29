/*
 * Barn
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
    iMaxEggs = 5;
    add_prop(OBJ_S_SEARCH_FUN, "do_search");
    add_prop(ROOM_S_MAP_FILE, "farm_w_map.txt");

    set_short("A large barn");
    set_long(short() + ". It is long and wide, and used as a storage " +
        "area for the farmers. The floor is made of wide slats and " +
        "covered with straw. Tools hang on a wall, and stalls line the " +
        "wall. A ladder leads up to a hayloft.\n");

    add_item(({"floor", "ground"}),
        "The floor is made of wide wood slats. They look well worn and covered with straw.\n");
    add_item(({"straw"}),
        "It is the stalks of dried hay and is used to cover the floor and as bedding in the stalls. The straw is a golden color and looks fresh.\n");
    add_item(({"slats", "wide slats"}),
        "They are wide, smooth boards. Some are used as the floor, others as walls and the ceiling. They are weathered looking but still sturdy.\n");
    add_item(({"tools"}),
        "They are various sizes and hang from the walls. They are the type of tools farmers use in tending their farm.\n");
    add_item(({"stalls"}),
        "The stalls are wide and hold different farm animals. They look well used but clean. Each stall has straw in it for the animal. A trough is set in each stall and holds hay and grain for the animal.\n");
    add_item(({"troughs", "trough"}),
        "They are rectangular shaped and deep, and there are two in each stable. The troughs are attached to the inside of each trough and hold feed and water.\n");
    add_item(({"hay", "hay bales", "bales of hay"}),
        "They are square bundles of dried grasses used to feed the animals. Some is spread around in troughs at the stalls, but the majority of it is stacked in bales against the walls and up above.\n");
    add_item(({"ladder"}),
        "The ladder is large, and really resembles a large staircase. It is in the back of the barn and leads upstairs to the hayloft. The ladder is wide and looks well used.\n");
    add_item(({"staircase", "stairs"}),
        "It is really a large ladder that resembles a staircase. The ladder is set in the back of the barn and leads upstairs to the hayloft.\n");
    add_item(({"walls"}),
        "They are made of wood. They looks like they were once smooth, but have become rough in places over the years. Tools hang on the walls.\n");
    add_item(({"ceiling"}),
        "The ceiling is made of wood and look watertight. It comes to a peak and is high overhead. A hayloft above blocks your view of the back of the barn's ceiling\n");
    add_item(({"hayloft"}),
        "The hayloft is where hay and other things are stored in the barn. It encompasses the back half of the barn and is accessible by a ladder.\n");  

    reset_room();
    set_add_chicken_noises();
    add_room_tell("A chicken swoops down from the hayloft above");

    add_exit(FARM2_DIR + "yard", "southeast");
    add_exit(FARM2_DIR + "hayloft", "up");
}


void
reset_room()
{
    ::reset_room();
    iEggFound = 0;
    
    if ((ob))
    {
        return;
    }

    ob = clone_object(FNPC_DIR + "girl");
    ob->set_monster_home(FARM2_DIR + "barn");
    ob->set_random_move(8);
    ob->set_restrain_path(FARM2_DIR);
    ob->move(this_object());
}
