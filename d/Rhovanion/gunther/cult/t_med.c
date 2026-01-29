inherit "/d/Rhovanion/lib/room";
inherit "/lib/guild_support";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Rhovanion/defs.h"
#include "guild.h"

init()
{
	::init();
	init_guild_support();
	add_action("drink_from_stream", "drink");
}

drink_from_stream(string str)
{	
	NF("Drink from what?");
	if(str != "from stream" && str != "from channel") return 0;
	
	write("You take a refreshing drink from the clear mountain spring water.\n");
	say(QCTNAME(TP) + " drinks some water from the stream.\n");
	return 1;
}
	

create_room()
{
	set_short("Contemplation room.");
	set_long("Several thick black mats are laid out on the floor here. Dimmed light"
		+" originates from a few niches along the walls and a sombre mood prevails."
		+" A calming porling sound originates from the small stream that flows through"
		+" a channel set into one of the walls. The stream disappears into a dark hole."
		+" This place is meant for inner contemplation and maintaining self-discipline."
		+" To the northeast you see the member quarters, and to the west is the guild"
		+"master room, where the Disciples meet and decide upon important issues.\n");
	
   add_item(({"mats", "mat" }), "The thick mats are woven of a soft black material. They"
   	+" look comfortable to sit and meditate on.\n");
   add_item(({"niches", "niche"}), "The few niches in the walls house some sort of light."
   	+" They are quite deep and pentagon shaped.\n");
   add_item(({"wall", "walls", "channel"}), "The polished walls have been cut directly from the mountain."
   	+" A channel with running water is set into one of the walls.\n");   
   add_item("stream", "The water looks very refreshing.\n");
   add_item("hole", "It is dark and about fist-size, and you can't tell what is down there.\n");
		
	add_prop(ROOM_I_INSIDE, 1);
	add_prop(ROOM_I_LIGHT, 1);
	add_prop(OBJ_I_CONTAIN_WATER, 1);
	
	add_exit(CULT_DIR + "t_start", "northeast", 0);
	add_exit(CULT_DIR + "t_gmroom", "west", "@@gm_check");
	add_exit(CULT_DIR + "t_gather", "south", 0);
}

int
gm_check() /* only guildmasters are allowed in there. */
{
	if(TP->query_bit(GM_BIT) || (TP->query_wiz_level() > 10))
		return 0;
	write("Sorry, only Disciples may enter there.\n");
	return 1;
}		


/**************** MEDITATE SUPPORT *******************/

void
leave_inv(object ob, object to)
{
	::leave_inv(ob,to);
	gs_leave_inv(ob,to);
}

void
gs_hook_start_meditate()
{
	write("You sit down on one of the soft mats here and "
	+"concentrate on knowing yourself. The dark forces in this room"
	+" swirl about you, lending their power to your efforts.  "
	+"You can <estimate> your level of stats and <set> those"
	+" rates at which each gets your attention, and the benefit of your"
	+" experience.  You may <rise> when finished.\n");
}

int
gs_hook_rise()
{
	write("You arise, coming back to your full consciousness.\n");
	say(QCTNAME(this_player())+" arises, having completed meditation.\n");
}
