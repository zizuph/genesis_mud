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
    set_long("   The southeast corner of the park. It's quiet " +
        "and relaxing here since the elves consider this part " +
        "of the city a special place. The open area of the park " +
        "rises to a knoll in the northwest. The slopes are grass " +
        "covered, lush and green. Golden flowers grow randomly " +
        "across the lawn. They twinkle in the sun like golden " +
        "jewels. A stand of trees grows at the top of the knoll. " +
        "Begonia street runs through this part of the park, but " +
        "travellers are respectful and quiet as they pass by. \n\n");
 
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
                                          
    add_exit(TOWNSHIP_DIR + "pk05", "north");
    add_exit(TOWNSHIP_DIR + "pk07", "west");
    add_exit(TOWNSHIP_DIR + "fountain", "northwest");
    add_exit(TOWNSHIP_DIR + "rd24", "southeast");
}                    
 
void
reset_room()
{
}
