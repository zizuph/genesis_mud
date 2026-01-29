/* Mountain trail room, credit to Sarr and Nerull */
#pragma strict_types
#include "defs.h"
inherit MTRAIL_ROOM;


void
create_room()
{
    ::create_room();
    
    setuid();
    seteuid(getuid());
    
    set_short("At the siege camp near Castle Gylar");
    
    set_long("You stand at what appears to be the northwesternmost part "
    +"of the camp. Eerie clouds hug the mountains, reminding you of "
    +"how high up you are. The camp comes to an abrupt end as a sheer "
    +"cliff wall onto which some broken war-machines have been stashed, "
    +"probably in wait for repair. The castle to the east is barely visible "
    +"through all the fog, but there's a path going south "
    +"leading deeper into the camp.\n");

    add_item("plateau","This area is relativley flat, but littered of "
    +"boulders, rocks, pebbles and some mud.\n");
    
    add_item(({"cliff", "cliffs", "sheer cliff", "cliff wall",
    "wall"}),"The cliffsides are present all around the plateau, and "
    +"they all considerably drops into far below the mountainside. The "
    +"cliff wall here rises further up on the mountainside.\n");
        
    add_item(({"ground", "groves", "large groves"}),"The ground here looks "
    +"rather well travelled judging by the groves and marks in the "
    +"mud all around "
    +"the area. Horses, carriages, and machines of war and boots probably.\n");
    
    add_item(({"rock", "rocks", "boulder", "boulders"}),"Littered "
    +"everywhere in this area, in different sizes and shapes, befitting the "
    +"natural environment.\n");
       
    add_item(({"mountain", "mountains"}),"The mountain landscape is both "
    +"pretty and scary at the same time. The tops are sporadically clad in "
    +"snow and ice, sprinkled with boulders and deep crevisses, comforted "
    +"by large steep drops into various abysses of sharp rocks.\n");
       
    add_item(({"mud"}),"While it's higher up in the mountains, melted "
    +"water mixed "
    +"with dust and other particules have created a thin slurry covering much "
    +"of the ground.\n");
        
    add_item(({"tent", "tents", "rows", "rows of tents"}),"Primitive fabric "
    +"canopies erected on improvised "
    +"sticks and other tools to prevent some level of shelter "
    +"from the potential "
    +"snow or rain. Little care or neglect is evident judging by their level "
    +"of disarray.\n");
    
    add_item(({"debris", "trash", "empty bottles", "bottles", "rags", 
    "dirty rags", "food scraps", "scraps"}),"There are debris and trash "
    +"everywhere. The "
    +"occupants of the plateau doesn't seem to care much "
    +"about the tidiness or "
    +"the environment of the plateau. But then, sieging is a messy and busy "
    +"business.\n");
    
    add_item(({"broken war machines", "war machines", "war-machines"}),"These "
    +"massive wooden constructs rests on large wooden wheels "
    +"and are moved about "
    +"by the crusaders. You think they are a variant of "
    +"trebuchets, judging by "
    +"their long wooden arms, baskets and counterweights. The machines "
    +"in this area seems to be broken and discarded.\n");
    
    add_item(({"castle", "castle gylar"}),"Partially shrouded in mist and "
    +"greyish clouds, it's hard to make out any details, but you make "
    +"out four spires, one on every corner. It is nearly adjacent to the "
    +"siege camp.\n");
    
    add_item(({"camp", "siege camp"}),"Littered around this rocky plateau, "
    +"holy crusaders have set up a position of siege versus the "
    +"castle to the east.\n");
    
    add_item(({"camp", "siege camp"}),"Littered around this rocky plateau, "
    +"holy crusaders have set up a position of siege versus the "
    +"castle to the east.\n");
   
    add_exit(MTRAIL_DIR + "siegecamp_23", "east");
    add_exit(MTRAIL_DIR + "siegecamp_21", "south");
    
    
    add_npc(COMMON_NPC_DIR + "holy_crusader", (2 + random(3)));
    
    reset_room();
}


void
reset_room()
{
}