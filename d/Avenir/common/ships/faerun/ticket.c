// name: Ticket   ~Avenir/common/ships/faerun/ticket.c
// creator(s):    Lilith  Oct 1997
// last update:   Lucius 2008: converted to Faerun line.
// purpose:       Ticket for the Luminous      
// note:
// bug(s):
// to-do:    
#pragma strict_types

inherit "/std/object";
#include "../ship.h"

public void
create_object(void)
{
    set_name("ticket");
    add_name("_SybFrun_Ticket");
    set_adj("luminous");
    add_adj("hemp");
    set_long("This is a luminous hemp ticket. It reads:\n"+
	"   Valid for one trip on the G.S. Luminous,\n"+
	"   providing transportation between the Rift\n"+
	"   of Sybarus and the Lands of Faerun.\n");

    add_prop(OBJ_I_WEIGHT, 1);
    add_prop(OBJ_I_VOLUME, 1);
    add_prop(OBJ_I_VALUE,  10);
}
