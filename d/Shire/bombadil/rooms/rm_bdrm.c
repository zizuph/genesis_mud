/*
 * Downstairs west hall of Tom's house
 * By Finwe, January 2001
 */
 
#pragma strict_types

#include "/d/Shire/sys/defs.h" 
#include "../local.h"
 
inherit HOUSE_BASE;
int closet_open;
object closet;

void
create_house_room()
{
    set_short("A large bedroom");
    set_long("This is a large bedroom. The roof is vaulted and " +
        "supported with great beams. Some furniture is scattered " +
        "about the room, including a large bed sitting beneath " +
        "the window on the north wall. The walls are a pale " +
        "yellow and a large carpet covers the floor. Lamps " +
        "hanging from the beams fill the room with gentle light. " +
        "Candles are spread about the room on tall stands.\n");
    add_item(({"carpet"}),
        "The carpet is large and fills the room. It is dark green " +
        "colored and very plush.\n");
    add_item(({"furniture"}),
        "There is a dresser, a large bed, and tall candle stands. " +
        "The stands are scattered about the room in small clusters.\n");
    add_item(({"candle stands", "candle stand", "stands", "stand", 
            "tall stands", "tall stand", "tall candle stands", 
            "tall candle stand"}),
        "The candle stands are of varying heights. They are made " +
        "of metal and are polished. Candles in the stands flicker " +
        "and fill the room with light.\n");
     add_item("dresser",
        "The dresser is wide and carved from wood. It has four large " +
        "drawers on both sides, which are closed. The top of the " +
        "dresser is empty. \n");
    add_item("dresser legs",
        "The legs of the dresser are plain, except for the " +
        "fluting which extends up the corners of the dresser.\n");
    add_item(({"large bed", "bed"}),
		"The bed is carved of light wood. It is large enough for " +
        "two people. A large bedcover covers the large mattress " +
        "and some pillows sit at the head of the bed.\n");
    add_item("mattress",
        "The mattress is thick and comfortable looking. It is full of " +
        "feathers and covered with a white cotton linen cloth.\n");
    add_item(({"bedcover", "large bedcover"}),
        "The bedcover is dark purple and covered with a leaf motif. " +
        "It is thick and luxurious and stuffed with down feathers. " +
        "The bedcover is spread across the bed.\n");
    add_item(({"pillows", "pillow"}),
        "There are several soft and fluffy pillows on the bed. " +
        "They are white and sit at the head of the bed.\n");
    
    reset_shire_room();
    add_item(({"north window", "northern window"}), 
        "@@north_up@@\n");

    set_extra_window("@@window_position@@ set into the " +
        "north wall.");
    add_cmd_item(({"curtains", "drapes"}), "close",
        "@@close_curtains@@");
    add_cmd_item(({"curtains", "drapes"}), "open",
        "@@open_curtains@@");
    num_of_windows=1;


    add_exit(ROOMS_DIR + "rm_closet", "south");
    add_exit(ROOMS_DIR + "rm_hall03", "east");
    add_exit(ROOMS_DIR + "rm_study",  "west");
}
void
init()
{
    ::init();

}


void
reset_shire_room()
{
}


