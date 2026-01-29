/*
 * A mountain path in Oranea by Ckrik, July 1998
 */

inherit "/d/Earthsea/oranea/base_rooms/base_oranea_mountain.c";
 
void
create_oranea_path()
{
  add_long("You are quite a ways away from the top of mountain.\n");
  add_exit("/d/Earthsea/oranea/rooms/mountain_path01", "northeast");
  add_exit("/d/Earthsea/oranea/rooms/mountain_path03", "southeast");
}
