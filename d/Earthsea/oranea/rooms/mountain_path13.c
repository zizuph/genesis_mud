/*
 * A mountain path in Oranea by Ckrik, July 1998
 */

inherit "/d/Earthsea/oranea/base_rooms/base_oranea_mountain.c";
 
void
create_oranea_path()
{
  add_long("You are just above the foothills of the mountain. The " +
	   "path switches direction here.\n");
  add_exit("/d/Earthsea/oranea/rooms/mountain_path12", "northeast");
  add_exit("/d/Earthsea/oranea/rooms/mountain_path14", "southeast");
}
