/* Office of the High templar of Jail /*
/* Zayn March 97 */

inherit "/std/room";
#include "defs.h"
#include "/d/Cirath/common/teamer.h"

void
reset_room()
{
    bring_room_team(TYR_NPC+"jailtemp.c", 1);
}


void
create_room()
{
	set_short("office");
	set_long("This square chamber is about the size of a common room in "
		+"an inn, the walls presenting hunting scenes carved in "
		+"stone of the purest white. There are tapestries between "
		+"the carvings with different images. In the center of the "
		+"room stands a heavy wooden table with high-backed chairs "
		+"standing around it. The room is brightly lit by tall "
		+"candles on the table and wall racks and by the huge "
		+"fireplace built into the centre of the wall on the left. "
		+"The ancient floor is polished to a bright shine.\n");

	add_item(({"tapestries", "tapestry", "images"}), "The tapestries "
		+"is gentle images of bright flowers and brilliantly "
		+"plumaged hummingbirds, except for the two at the far end "
		+"of the room, where the High Templar of the jail stands "
		+"erect and tall among a group of soldier. The tapestries "
		+"must originate from sometime before the plague, except "
		+"the two representing the High Templar which looks rather "
		+"new.\n");

	add_item(({"walls", "wall"}), "The walls are decorated with hunting "
		+"scenes carved in stone. Between the carvings there are "
		+"tapestries with different motives. The room is lit by "
		+"candle racks that is fixed against the wall.\n");

	add_item(({"fireplace", "huge fireplace"}), "The firewood crackle "
		+"in the fireplace, giving both warmth and light. The "
		+"fireplace gives you a cosy feeling. But you quickly "
		+"disregard the feeling when you remind yourself that "
		+"you are in a jailhouse.\n");

	add_item(({"scenes", "hunting scenes"}), "The present different "
		+"hunting scenes performed years ago, before the dreaded "
		+"plague. The are carved in the whitest stones.\n");

	add_item("stone", "The stone is of the purest white colour you could "
		+"ever imagine. This room must for sure been built long "
		+"before the plague. It is probably because of the beautiful "
		+"scenes and tapestries that the High Templar of the jail "
		+"has taken this room in possession.\n");

	add_item("table", "It is made of very heavy wood, standing very "
		+"steady. It would take at least six men to lift it and "
		+"probably more to move it out of the room. On the table "
		+"there are tall candles lighting up the room. Besides that "
		+"the table looks quite empty.\n");

	add_item(({"chairs", "high-backed chairs"}), "Standing around the "
		+"heavy wooden table is high-backed chairs. They are made "
		+"of wood and look quite heavy. They are dressed in some "
		+"sort of textile. The textile feels smooth and the chair "
		+"feels comfortable to sit on.\n");

	add_item(({"candles", "candle", "racks", "wall racks"}), "They are "
		+"here so that the room can have some light.\n");

	add_item(({"ancient floor", "floor"}), "The floor is polished to a "
		+"bright shine, probably polished by a group of slaves "
		+"every day to keep up the shine, otherwise it would get "
		+"dull by all dust and sand that are elsewhere.\n");

	add_cmd_item("table", ({"lift", "move", "push"}), "You can't even "
		+"dislodge the table. You would probably have to be alot "
		+"stronger than that to move it.\n");

	add_cmd_item(({"candle", "candles"}), "pull", "Nothing happens, "
		+"except that you get burnt by the candle-grease.\n");

	add_cmd_item(({"tapestry", "tapestries"}), ({"take", "pull", "get",
		 "pick"}), "You start to pull down a tapestry, when a "
		+"thought flashes through you head. You can see yourself "
		+"locked up in a cell, only getting water and breed to feed "
		+"on. You realise that you should let those tapestries hang "
		+"where they do. It isn't worth ending up in a cell for.\n");

	INSIDE

	add_exit(TYR_JAIL + "jail1_5.c", "east", 0,1);
	reset_room();
}
