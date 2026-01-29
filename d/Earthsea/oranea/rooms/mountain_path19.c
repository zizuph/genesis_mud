/*
 * A mountain path in Oranea by Ckrik, July 1998
 */

inherit "/d/Earthsea/oranea/base_rooms/base_oranea_mountain.c";
 
void
create_oranea_path()
{
  add_long("You are right under the plateau now.\n");
  add_exit("/d/Earthsea/oranea/rooms/mountain_path18", "northwest");
  add_exit("/d/Earthsea/oranea/rooms/cliff_face", "southwest");
}
