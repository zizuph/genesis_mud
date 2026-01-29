/* File         : /d/Khalakhor/se_speir/rannoch/village/room/road_18_7.c
 * Creator      : Darragh@Genesis
 * Date         : 00-10-19      
 * Purpose      : Map room file of the Loch Rannoch area.
 * Related Files: 
 * Comments     :
 * Modifications: Changed structure to coord system (Darragh 2003-07-25) 
 */

#pragma strict_types

#include "room.h"
#include <macros.h>
#include <stdproperties.h>
#include <language.h>
#include <ss_types.h>

inherit VILLAGE_BASEFILE;

int climb_tower();
int climb_cliff();

int
climb_tower()
{

    write("You are not skilled enough for a climb like this.\n");
    return 1;
}
int
climb_cliff()
{
    write("The cliff is too sheer at this place.\n");
    return 1;
}
public void
create_road()
{
    add_item(({"tower","stone tower","watch tower","sentinel"}),
               "At the end of the main road, where the village "
             + "ends at the base of the high cliffs, a stone "
             + "tower has been built long ago. Built into the "
             + "very cliff itself and rising even above the top "
             + "of the cliff, and having no windows or door, you "
             + "wonder who built it. The stones are large and "
             + "the foundation is covered in moss.\n");
    add_item(({"stone","stones","foundation","foundation stones",
               "stonework"}),
               "The stonework is ancient, but still it holds "
             + "together against weather and time. At the base of "
             + "the tower, the stones are more or less covered in "
             + "grey moss.\n");
    add_item(({"moss","grey moss"}),
               "The grey moss is dry and withered, covering the "
             + "foundation stones completely, then thinning out "
             + "as the tower rises toward the sky. Obviously "
             + "there is no one who maintains the tower these days, "
             + "for some reason.\n");
    add_item(({"cliff","cliffs","cliffside","cliffsides"}),
               "From the eastern bank of the river, the land rises "
             + "steeply into hills, eventually joining up with the "
             + "mountains. At this place the hill takes a dramatic "
             + "leap upwards in the form of a sheer cliff. It is "
             + "high, and you doubt you could climb it. Built within "
             + "the cliff itself and above is a tall tower.\n");

    add_cmd_item("tower","climb",climb_tower);
    add_cmd_item("cliff","climb",climb_cliff); 

    add_exit(ROOM + "road_17_7.c","west",0,1,0);
    add_exit(ROOM + "road_17_6.c","northwest",0,1,0);
    add_exit(ROOM + "road_17_8.c","southwest",0,1,0);

    set_short("At the base of a tower");
    set_long(query_long() + "You stand at the base of a high tower.\n");
}

