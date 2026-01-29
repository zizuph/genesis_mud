inherit "/d/Earthsea/std/room";


#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Earthsea/atuan/defs.h"


void
create_earthsea_room()
{
    set_short("On the pier outside of the village of Gar.");
	set_long(break_string("You are standing on"+
		" a short wooden pier just outside of the village of"+
		" Gar. The sea laps gently against the wooden struts"+
		" and the scene is one of peace and tranquility."+
		" Eastwards lies the village, and you can see smoke"+
		" drifting gently into the air from the few houses"+
		" that sit here and there just off the beach."+
		" High above you seagulls turn and dive.\n",70));
		

	add_item(({"sea"}),"The sea is a deep shade of blue,"+
		" and looks very inviting.\n");
   	add_item(({"pier","struts","wooden pier"}),"The pier is well constructed, and looks very sturdy.\n");
	add_item(({"smoke"}),"The smoke is drifting gently upwards.\n");
	add_item(({"gulls","gull","seagulls","seagull"}),"The gulls are screeching overhead.\n");

    add_prop(ROOM_I_IS, 1);
    add_prop(ROOM_I_INSIDE, 0);
    add_exit(GAR + "gar_square", "east");
	add_exit(GAR + "gar_dock","west");

}
