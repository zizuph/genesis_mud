/*
 * The park in Telseron
 * By Finwe, September 1996        
 */
 
inherit "/std/room";
 
#include "/d/Emerald/defs.h"
 
void reset_room();
 
void
create_room()
{
    reset_room();
    set_short("The park"); 
    set_long("   The northeast side of the park. It's quiet and " +
        "relaxing here since. The elves consider this part of " +
        "the city a special place. The open area of the park " +
        "rises to a knoll that is in the southwest part of the " +
        "park. The slopes are grass covered and are lush and green. " +
        "Golden flowers scattered across the lawn twinkle in the " +
        "sun like golden jewels. A stand of trees grows at the top " +
        "of the knoll. Gardenia street runs through here, but the " +
        "travellers are respectful of the park.\n\n");
 
    add_item(({"trees", "stand"}),
        "The stand of trees grow around the knoll like a crown. The " +
        "tall birch trees are magnificent and reach towards the " +
        "sky.\n");
    add_item("ground",
        "The ground is a velvet carpet of lush green grass.\n");
    add_item("sky",
        "The sky is clear and blue. \n");
    add_item("flowers",
        "The flowers are small and golden colored. They are " +
        "star shaped and glimmer on the grass.\n");
                                          
    add_exit(TOWNSHIP_DIR + "pz02", "north");
    add_exit(TOWNSHIP_DIR + "pk05", "south");
    add_exit(TOWNSHIP_DIR + "pk02", "west");
    add_exit(TOWNSHIP_DIR + "rd11", "northeast");
    add_exit(TOWNSHIP_DIR + "fountain", "southwest");
}                    
 
void
reset_room()
{
}
