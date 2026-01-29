/*
 * A path in Oranea by Ckrik, July 1998
 */

inherit "/d/Earthsea/oranea/base_rooms/base_oranea_path.c";
 
void
create_oranea_path()
{
  add_long("You can barely see a pier to the north through the heavy " +
	   "mist.\n");
  add_exit("/d/Earthsea/oranea/rooms/oranea_path01", "north");
  add_exit("/d/Earthsea/oranea/rooms/oranea_path03", "south");
}
