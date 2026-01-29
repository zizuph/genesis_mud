#include <stdproperties.h>
#include <macros.h>
#include "defs.h"

inherit ROGON_ROOM;

create_rogon_room()
{
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, "@@query_light:"+CONTROL_FILE+"|"+MASTER+"@@");
    
    TO->create_avenue();
    
    add_item(({"avenue", "road", "lane"}),
	"The avenue is typical for the superiour design of the Dwarven City. " +
	"The road is 7 yards (21') wide, being arched and constructed " +
	"with a 'Band-pattern' of grey granite and red marble. They are as grand " +
	"as most any boulevard in Middle-Earth.\n" +
	"    The craft is beautiful, yet remains practical. Along the Avenue cart-track " +
	"grooves run the length of the grey basalt floor. You notice that the " +
	"Avenue is absolutely straight, not like the avenues in the Mines which " +
	"are gently winding through long, easy curves.\n");
    add_item(({"walls", "wall", "patterns", "pattern"}),
	"The walls are adorned in the so-called 'Band-pattern', consisting of " +
	"granite and red marble in vertical bands along the road. It is startling " +
	"to try to understand how the dwarves managed to make it, and the art " +
	"is probably lost forever, due to the loss of Khazad-dum to enemy hands.\n");
    add_item(({"ceiling", "lamps"}),
	"The ceiling is arched and domes some ten yards (30') above you. You notice "+
	"some old lamps w
