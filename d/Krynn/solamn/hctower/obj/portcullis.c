/* created by Aridor 06/25/93 */

inherit "/std/door";
#include "../local.h"

create_door()
{
    set_door_id("portcullis");
    set_pass_command(({"nw","northwest","go through","out"}));
    set_door_name(({"steel portcullis","portcullis"}));
    set_other_room(ROOM + "backex");
    set_open(0);
    set_open_command(({"open","raise"}));
    set_close_command(({"close","lower"}));
    /*set_locked(1);   --not yet*/

}
