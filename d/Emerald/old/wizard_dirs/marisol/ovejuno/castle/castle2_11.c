/* Castle rooms second floor-Servant Quarters (male)
 * Coded by Marisol (11/20/98)
 * Copyright (c) Marisol Ramos 1998
 */

#pragma strict_types
#include "defs.h"
inherit CASTLE_OV2;

void
create_castle_room()
{

    set_short("Servant Quarters");
    set_long("This is the male section of the Servant Quarters of the "+
        "castle. This room is long and full of small pallets. "+
        "One wall has two inner windows that looks outside to the "+
        "main corridor. Some curtains keep a measure of privacy for the "+
        "servants. The other wall seems to have been added recently. "+
        "Several oil lights provide light to the quarters.\n");

    add_item("quarters",
        "The quarters are definetely male. They are a little untidy "+
        "and austere, no frilly decorations here. White sheets cover "+
        "the beds and big pillows are set at the top of each beds. "+
        "The room feel quite cramped. A tall and wide closet cover all "+
        "the wall at the bottom of the room. Some servants are sitting "+
        "on the pallets, shining their shoes and chatting softly among "+
        "themselves.\n"); 

   add_item("pallets",
        "A barrack-style pallets are arranged along both walls of this "+
        "room. They are made of wood and have little padding for "+
        "comfort. In some cases, the beds are not made, so the sheets "+
        "are all wrinkled.\n");
        
   add_item(({"pillow", "pillow"}),
        "Big, confy pillows sit on top of the beds.\n");

    add_item(({"white sheets", "sheets"}),
        "White sheets, some clean and neat, other wrinkled and messy "+
        "cover the beds of this room.\n");  

    add_item(({"windows", "inner windows"}),
        "The windows are small with a wooden frame and two crossed "+
        "wooden stick that divided the windows in four smaller squares. "+
        "The windows are not covered with glass, they are interior "+
        "windows, and are covered with curtains.\n");

    add_item("curtains",
        "Dark blue curtains cover the inner windows inside this room. "+
        "They are the only bright color in this quarters.\n");

    add_item("walls",
        "Two wooden walls. One of them has inner windows that looks "+
        "outside to the main corridor. The wood is sturdy and perfectly "+
        "cut and set.  The other wall makes the border for the next room. It "+
        "is really thin and differs in quality to the other wall. The "+
        "wall was unevenly set across the room and you can hear the light "+
        "laugh of female servants coming across the other side.\n");

    add_item("west wall",
        "The west wall still has its natural beige wooden color. There "+
        "is not decorations whatsoever on this wall.\n");

    add_item("east wall",
        "A white and blue stripes wallpaper cover this "+
        "wall. Together with the curtains covering the inner windows, "+
        "that is all the decoration in this room.\n");

    add_item("closet",
        "An oakwood closet stands tall on the wall. One of its door "+
        "is open, reveling dark suits and white shirts.\n");

    add_item(({"dark suits", "suits", "white shirts", "shirts"}),
        "Very elegant black suits hang together with cotton white "+
        "shirts.\n");
     

    add_exit("castle2_13.c", "south");

    reset_room();

}                                     
