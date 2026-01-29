/*
 * A path in Oranea by Ckrik, July 1998
 */

inherit "/d/Earthsea/oranea/base_rooms/base_oranea_path.c";
 
void
create_oranea_path()
{
  add_long("A trail into what seems to be a small " +
	   "fishing village is to the east. The main path continues " +
	   "running north and south.\n");
  add_exit("/d/Earthsea/oranea/rooms/oranea_path02", "north");
  add_exit("/d/Earthsea/oranea/rooms/village/village01.c", "east", 
	   "@@block@@");
  add_exit("/d/Earthsea/oranea/rooms/oranea_path04", "south");
}

int
block()
{
  this_player()->catch_msg("The village is repairing the mess " +
			   "left by the tsunami wave that struck " +
			   "Oranea recently.\n");
  return 1;
}
