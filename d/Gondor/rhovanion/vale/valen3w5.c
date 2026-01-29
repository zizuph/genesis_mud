/*
 * Vale of the Anduin.
 * Varian 2015
 */
#pragma strict_types

#include "../defs.h"
#include <stdproperties.h>
#include <macros.h>
 
inherit RHOVANION_DIR + "vale/base";

void 
create_vale_room()
{
    set_items_vale();
    set_items_east();
    set_herbs_2();
    
    set_short("Vale of the Anduin");
    set_long("Surrounded by a tall, yellowish grass which brushes against " +
        "you as it sways in the wind, you find yourself on the eastern " +
        "slopes of a deep valley. Rushing waters, carving their path " +
        "south towards the sea, mark the great Anduin river as it tumbles " +
        "across the bottom of the valley. On the other side of the valley, " +
        "broken foothills raise themselves higher and higher into the sky as " +
        "the jagged peaks of the Misty Mountains scrape the sky high above. " +
        "An endless line of tall, black oaks stretch across the eastern " +
        "horizon as the deep shadows of Mirkwood forest lurk, waiting for " +
        "a careless traveller.\n");

    add_exit(VALE_DIR + "valen2w5", "south",0,2,1);
    add_exit(VALE_DIR + "valen2w4", "southeast",0,2,1);
    add_exit(VALE_DIR + "valen3w4", "east",0,2,1);
    add_exit(VALE_DIR + "valen4w4", "northeast",0,2,1);
    add_exit(VALE_DIR + "valen4w5", "north",0,2,1);
    add_exit(VALE_DIR + "valen4w6", "northwest",0,2,1);
    add_exit(VALE_DIR + "valen3w6", "west",0,2,1);
    add_exit(VALE_DIR + "valen2w6", "southwest",0,2,1); 
}
