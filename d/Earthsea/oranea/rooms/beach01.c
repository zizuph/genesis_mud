/*
 * A beach in Oranea by Ckrik, June 1998
 */

inherit "/d/Earthsea/oranea/base_rooms/base_beach_rocky.c";
 
void
create_beach()
{
    add_my_desc("A large cliff blocks the path to the south.\n");
    add_item (({"beach", "rocky beach"}),
        "The beach is rocky with broken boulders from the " +
        "cliff and from rocks that have come in with " +
	"the tide.\n");
    add_item("cliff",
        "The cliff towers over the beach. It " +
	"is impossible to climb over.\n");
 
    add_exit("/d/Earthsea/oranea/rooms/beach02", "north");
}
