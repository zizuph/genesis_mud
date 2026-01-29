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
    
    set_long("You find yourself at the centre of the east-west "
    +"path hugging the southern "
    +"edge of the camp. Some tents have been erected, and you can "
    +"even spot a crusader "
    +"or two trying to maintain a positive spirit through copious "
    +"amounts of alcohol. Aside "
    +"from some debris littered around the edges of the path there "
    +"is nothing much else to "
    +"look at. You're free to travel both east and west.\n");

    add_item("cliffs","The cliffsides are present all around the plateau, and "
    +"they all considerably drops into far below the mountainside.\n");
    
    add_item("plateau","This area is relativley flat, but littered of "
    +"boulders, rocks, pebbles and some mud.\n");
        
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
    
    add_item(({"debris", "trash"}),"There are debris and trash "
    +"everywhere. The "
    +"occupants of the plateau doesn't seem to care much "
    +"about the tidiness or "
    +"the environment of the plateau. But then, sieging is a messy and busy "
    +"business.\n");
    
    add_item(({"machine", "war machine", "heavy war machine", "machines",
    "war machines", "heavy war machines", "trebuchet", "trebuchets"}),"These "
    +"massive wooden constructs rests on large wooden wheels and "
    +"are moved about "
    +"by the crusaders. You think they are a variant of "
    +"trebuchets, judging by "
    +"their long wooden arms, baskets and counterweights.\n");
    
    add_item(({"castle", "castle gylar"}),"Partially shrouded in mist and "
    +"greyish clouds, it's hard to make out any details, but you make "
    +"out four spires, one on every corner. It is nearly adjacent to the "
    +"siege camp.\n");
    
    add_exit(MTRAIL_DIR + "siegecamp_7", "west");
    add_exit(MTRAIL_DIR + "siegecamp_5", "east");
    
    add_npc(COMMON_NPC_DIR + "holy_crusader", (2 + random(3)));
    
    reset_room();
}


void
reset_room()
{
}