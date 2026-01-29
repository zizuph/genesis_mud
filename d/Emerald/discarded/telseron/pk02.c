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
    set_long("   The northern edge of the park. This open area " +
        "is grass covered and slopes gently upwards to a knoll " +
        "south of here. The ground is a sea of grass with golden " +
        "flowers sprinkled across the landscape. At the top of the " +
        "knoll, a stand of trees grows. Elves often gather in the " +
        "park for the sense of peace here. Amaryllis street travels " +
        "south here, but the traffic is subdued.\n\n");
 
 
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
        "star shaped and glimmer on the grass like carved " +
        "glass crystals.\n");
                                          
    add_exit(TOWNSHIP_DIR + "board", "north");
    add_exit(TOWNSHIP_DIR + "fountain", "south");
    add_exit(TOWNSHIP_DIR + "pk03", "east");
    add_exit(TOWNSHIP_DIR + "pk01", "west");
}                    
 
void
reset_room()
{
}
