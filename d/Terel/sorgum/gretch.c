#include "/d/Terel/include/Terel.h"

inherit "/std/room";

object virus;

public int
infect (string str)
{
    object victim;
    
    if (!strlen (str)) {
	NF("Infect whom?`n");
	return 0;
    }

    victim = find_player (str);
    if (!victim) {
	NF (str + " not found.\n");
	return 0;
    }
    virus->add_player(victim);
    TP->catch_msg ("Ok.\n");
    return 1;
}
    
init ()
{
    add_action("infect", "infect");
}

void
create_room()
{
    
    set_short("cell");
    set_long("You are in an empty cell with no exits!\n");

    add_prop(ROOM_I_INSIDE, 0);
    virus = clone_object ("/d/Terel/sorgum/disease");
}

