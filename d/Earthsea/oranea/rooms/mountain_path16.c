/*
 * A mountain path in Oranea by Ckrik, July 1998
 */

inherit "/d/Earthsea/oranea/base_rooms/base_oranea_mountain.c";
 
void
create_oranea_path()
{
  add_long("You are near the plateau now, the majestic buildings " +
	   "are becoming more visible as you get closer.\n");
  add_exit("/d/Earthsea/oranea/rooms/mountain_path15", "west");
  add_exit("/d/Earthsea/oranea/rooms/mountain_path17", "east");
}
