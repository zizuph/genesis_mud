/*
 * Hobbit burrow in Michel Delving
 * Updated by Finwe, September 1997
 * Updates include adding the hobbitmaker
 */
 
#pragma strict_types
#include "/d/Shire/hobbitmaker/hobbitmaker.h"
#include "local.h"
 
inherit "/d/Shire/eastroad/smial";
 
void reset_room();
 
object hobbit;
 
void
create_room()
{
   
    areaname  = "Michel Delving"; /*Name of village*/
    land      = "the Shire";      /*Name of land   */
    roomtype  = 2;                /*Type of room in the smial*/
    areatype  = "town";           /*Type of village*/
    smialsize = "large";          /*Size of the house*/
   
    extraline = "A smooth circular dining table is placed " +
        "carefully in the center of this room. This room is " +
        "rather large and the smooth circular dining table " +
        "could accomodate many hobbits at a feast. A window is " +
        "cut into the eastern wall.";
 
    add_item(({"dining table","table","smooth dining table",
                "circular table"}),
        "The smooth circular dining table is hardly  scratched " +
        "at all. On careful examination you notice candlestick " +
        "marks in the center.\n");
 
    add_item(({"marks","candlestick marks","mark"}),
        "The marks seem to be from a heavy candlestick.\n");
 
    add_item("window",
        "Looking through the window, you can see the " + areatype +
        " of " + areaname + ".\n");
 
   add_exit(MICH_DIR + "burrow/3b","east",0,1);
 
   
   make_the_room();
 
}
 
void
reset_room()
{
    if (!hobbit)
    {
        hobbit = clone_object(HOBBITMAKER);
        hobbit->set_type(MAIDEN);
        hobbit->set_power(100);
        hobbit->move(TO);
    }
        
}
