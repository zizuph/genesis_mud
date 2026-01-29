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
    set_long("   You stand in the northwest corner of the park. " +
        "It gradually rises to the southeast where a fountain " +
        "sits. The slopes are a blanket of velvet green grass. " +
        "Dotted across the grass are little flowers. Their golden " +
        "faces wave in the breeze. A stand of trees grows at the " +
        "top of the slope, in the southeast part of the park. " +
        "A calm feeling descends upon you as you contemplate the " +
        "beauty of the park. Even though Begonia street runs here, " +
        "the travellers are quiet and respectful of the park.\n\n");
 
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
        "shaped like stars and glimmer on the grass like the " +
        "morning dew.\n");
                                          
    add_exit(TOWNSHIP_DIR + "pz01", "north");
    add_exit(TOWNSHIP_DIR + "pk04", "south");
    add_exit(TOWNSHIP_DIR + "pk02", "east");
    add_exit(TOWNSHIP_DIR + "rd09", "northwest");
    add_exit(TOWNSHIP_DIR + "fountain", "southeast");
}                    
 
void
reset_room()
{
}
