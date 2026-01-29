/*
 * A beach in Oranea by Ckrik, June 1998
 */

inherit "/d/Earthsea/oranea/base_rooms/base_beach_rocky.c";
 
void
create_beach()
{
  add_my_desc("A small cove lies to the east.\n");
  add_item (({"cove", "east"}),
	    "There seems to be ships coming in and out of the cove.\n");
  add_exit("/d/Earthsea/oranea/rooms/beach03", "east");
  add_exit("/d/Earthsea/oranea/rooms/beach01", "south");
}
