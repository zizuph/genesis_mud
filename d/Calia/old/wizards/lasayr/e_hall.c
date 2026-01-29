#pragma save_binary

inherit "/std/room";
#include <stdproperties.h>


create_room()
{

  object door;

  set_short("A long cavernous hallway");
  set_long("Adjusting your eyes to this long and narrow hallway takes " +
  "some time, as the subtle shades of shadow seem to dance. Hewn out " +
  "of the rock, the hall leads from doors to the west to an expanse of " +
  "space to the east. Being narrow as it is, the ceiling is surprisingly " +
  "invisible in the darkness above and you see nothing but a blur of " +
  "emptiness.\n");

    add_item(({"wall","walls"}),"Walking the edge of the hallway, you " +
  "take care to notice that the walls are not so natural. The rock has " +
  "been hewed away with force rather than skill, leaving uneven gaps " +
  "of shadow.\n");

    add_item("floor","A low rumble emanates from the ground you stand " +
  "on. Lacking any semblance of rhythm, it seems to numb you. The floor " +
  "distantly begins to waver in sync.\n");

    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_HIDE,90);

    add_exit("/d/Calia/palace_raid_room", "east", 0);

  door = clone_object("/d/Calia/lasayr/w_door2");
  door->move(this_object());

}
