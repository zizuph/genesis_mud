/*
 * Hobbit hole in Bree
 * By Finwe, June 2002
 */
 
#pragma strict_types

#include "/d/Shire/sys/defs.h"
#include "/d/Shire/hobbitmaker/hobbitmaker.h"
#include "defs.h"
 
inherit "/d/Shire/eastroad/smial";
 
void reset_room();
 
object hobbit;
 
void
create_room()
{
   
    areaname  = "Bree";  /*Name of village*/
    land      = "the Shire";   /*Name of land   */
    roomtype  = 1;             /*Front hall*/
    areatype  = "village";     /*Type of village*/
    smialsize = "medium size"; /*Size of the house*/
   
    extraline = "This large, circular room is the front hall of the " +
        "hobbit hole. A row of brass hooks line the wall where visitors " +
        "hang their coats and cloaks. A large door leads outside with " +
        "two circular windows on either side.";
 
    add_item(({"hooks", "few hooks", "hook", "brass hook", 
            "brass hooks"}),
        "There are some brass hooks set into the wall. Hats, " +
        "coats, and the like are hung on them by visitors.\n");
    add_item(({"hats", "coats", "coat", "hat"}),
        "You don't see any on the brass hooks.\n");
    add_item(({"ceiling", "up"}),
        "The ceiling is plain is painted white. Largem wooden beams support the ceiling.\n");
    add_item(({"down", "ground", "floor"}),
        "The floor is made of wood and swept clean.\n");
    add_item(({"wall", "walls"}),
        "The walls are painted off white and covered with paintings.\n");
    add_item("paintings",
        "The paintings are all sizes and depict portraits, landscapes, " +
        "and places where the hobbits have traveled to.\n");
    add_item(({"beams", "wooden beams"}),
        "Thew beams are large and squared. They support the " +
        "ceiling and are polished smooth.\n");
    add_item(({"door", "large door", "circular door"}),
        "The large door is circular. It is painted green and leads " +
        "outdoors.\n");
    add_item(({"doorknob"}),
        "The doorknob is set in the center of the door. It is made " +
        "of brass and polished from use.\n");
    add_item(({"round windows", "circular windows", "windows"}),
        "The windows are on either side of the door. They are round " +
        "and look outside.\n");
        
    add_exit(ROAD_DIR + "broad08",   "out");
    add_exit(HOUSES_DIR + "hobbit01a", "northeast");
    add_exit(HOUSES_DIR + "hobbit01d", "southwest");
   
    make_the_room();
    reset_room();
}
 
void
reset_room()
{
    if (!hobbit)
    {
        hobbit = clone_object(HOBBITMAKER);
        hobbit->set_type(TWEENS);
        hobbit->set_power(100);
        hobbit->move(TO);
    }
}
