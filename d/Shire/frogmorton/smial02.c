/*
 * Hobbit burrow in Frogmorton
 * By Finwe, September 1998
 */
 
#pragma strict_types
 
#include "/d/Shire/sys/defs.h"
#include "/d/Shire/hobbitmaker/hobbitmaker.h"
#include "defs.h"
 
inherit "/d/Shire/eastroad/smial";
 
void reset_room();
 
object hobbit1, hobbit2;
 
void
create_room()
{
   
    areaname  = "Frogmorton";  /*Name of village*/
    land      = "the Shire";   /*Name of land   */
    roomtype  = 1;            /*Type of room in the smial*/
    areatype  = "village";     /*Type of village*/
    smialsize = "small";       /*Size of the house*/
   
    extraline = "It's small by hobbit standards with only one " +
        "room off of this one. A few pieces of furniture are " +
        "here.";
 
    add_item(({"ceiling", "up"}),
        "The ceiling is plain.\n");
    add_item(({"down", "ground", "floor"}),
        "The floor is made of wood and swept clean.\n");
    add_item(({"furniture", "scraps of furniture"}),
        "A table and a some chairs are in one corner of the " +
        "room.\n");
    add_item(({"table"}),
        "The table is old and falling apart. There are some " +
        "stains on the table.\n");
    add_item(({"stains", "food stains", "stain", "food stain"}),
        "The stains are old and look set into the tabletop. " +
        "Some of the stains are a deep red, green, and other " +
        "indescribable colors\n");
    add_item(({"chairs", "old chairs",  "chair", "old chair"}),
        "They are old and falling apart. It looks like they " +
        "were made of a soft wood at one time and of good " +
        "quality. Now the chairs look pretty pathetic.\n");
 
    add_exit(FROG_DIR + "road02", "out");
    add_exit(FROG_DIR + "smial02b", "east");
   
    make_the_room();
    reset_room();
}
 
void
reset_room()
{
    if (!hobbit1)
    {
        hobbit1 = clone_object(HOBBITMAKER);
        hobbit1->set_type(CITIZEN);
        hobbit1->set_power(100);
        hobbit1->move(TO);
    }
    if (!hobbit2)
    {
        hobbit2 = clone_object(HOBBITMAKER);
        hobbit2->set_type(MAIDEN);
        hobbit2->set_power(100);
        hobbit2->move(TO);
    }
 
 
}
