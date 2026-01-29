inherit "/std/workroom";
#include <stdproperties.h>
#include <macros.h>

int
query_prevent_snoop()
{
return 1;
}
create_workroom()
{

	
set_short("By the sea");
set_long("The entire south wall of this room opens out and faces "+
"the sea. You hear the cries of seabirds and waves "+
"crashing on the beach below. "+
"You see attractive macrame hangings on the walls, which "+
"are panelled in white pine. There are flowers growing in pots "+
"along a window which faces east. It is a room filled "+
"with light. You can step right out onto the beach "+
"from here.\n");


add_prop(ROOM_I_LIGHT, 1);
add_exit("/d/Calia/mountain/road/beach3.c", "beach", 0,0);
}

void
init()
{
::init();
add_action("go_up", "loft");
}

int
go_up(string str)
{

object tp = this_player();

tp->catch_msg("You climb a hidden ladder to a room above.\n");
tell_room(environment(tp), QCTNAME(tp)+" suddenly disappears.\n", tp);
tp->catch_msg("You enter a secret room.\n");
tp->move_living("M", "/d/Calia/amelia/my_own/loft.c", 1);
return 1;
}
