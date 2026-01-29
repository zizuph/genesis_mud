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
    set_long("   The western side of the park. Gradually rising " +
        "to the east, the slopes of the park are covered with a " +
        "blanket of rich green grass. Dotted across the grass are " +
        "little flowers. The flowers are golden and wave in the " +
        "breeze. A stand of trees grows at the top of the slope, in " +
        "the eastern part of the park. Scattered around the park " +
        "are groups of elves. They talk quietly among themselves. " +
        "Camellia street quietly runs east and west here. The " +
        "travellers are quiet and respectful of the park.\n\n");
 
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
                                          
    add_exit(TOWNSHIP_DIR + "pk01", "north");
    add_exit(TOWNSHIP_DIR + "pk06", "south");
    add_exit(TOWNSHIP_DIR + "fountain", "east");
    add_exit(TOWNSHIP_DIR + "rd16", "west");
}                    
 
void
reset_room()
{
}
