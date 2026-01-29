/*
 * A mountain path in Oranea by Ckrik, July 1998
 */

inherit "/d/Earthsea/oranea/base_rooms/base_oranea_mountain.c";
 
void
create_oranea_path()
{
  add_long("You are a ways up the mountain.\n");
  add_exit("/d/Earthsea/oranea/rooms/mountain_path07", "northeast");
  add_exit("/d/Earthsea/oranea/rooms/mountain_path09", "west");
}
