/*
 * A mountain path in Oranea by Ckrik, July 1998
 */

inherit "/d/Earthsea/oranea/base_rooms/base_oranea_mountain.c";
 
void
create_oranea_path()
{
  add_long("The trail forks here. The path to the east leads into " +
	   "a bamboo thicket, northwest goes down the mountain, and " +
	   "southwest goes up the mountain. " +
	   "You are quite a ways away from the top of mountain.\n");
  add_exit("/d/Earthsea/oranea/rooms/mountain_path06", "northwest");
  add_exit("/d/Earthsea/oranea/rooms/mountain_fork01", "east", "@@block@@");
  add_exit("/d/Earthsea/oranea/rooms/mountain_path08", "southwest");
}

int
block()
{
  this_player()->catch_msg("Hmm...better not go that way. The mist is " +
			   "too thick, you'd never know what " +
			   "lies that way.\n");
  return 1;
}
