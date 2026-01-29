/* created by Aridor 06/21/93 (for H. C. Tower)
* modified by Grace 05/31/94 (for Knight Spur)
   *   Knight Spur stairs    */

#include "../local.h"
inherit SPURRM;

create_spur_room()
{
    SHORT("Stairwell in the lower level of Knights' Spur");
    LONG("You are standing in the middle of the stairs which " +
      "connect the first and second levels of the Knights' " +
      "Spur.  The stairwell is dim and poorly illuminated.\n");

    INSIDE;
    LIGHT;

    AE(ROOM + "landing1","up",0);
    AE(ROOM + "hall4", "down",0);    

    add_prop("_room_i_no_allow_steed", 1);
}
