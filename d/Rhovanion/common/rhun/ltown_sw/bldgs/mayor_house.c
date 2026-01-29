#pragma save_binary

inherit "/d/Rhovanion/lib/room";
#include <macros.h>
#include "/sys/stdproperties.h"
#include "/d/Rhovanion/farlong.h"

create_room()
{
set_short("Mayor's house");
set_long(break_string("This is the home of the mayor of this"
	+" large town.  It is spacious and nicely furnished.  While"
	+" some of his citizens may be poor, the mayor is apparently"
	+" quite rich."
	+"  You may exit his domicile back to the east."
	+"\n",75));

AE(RHUN+"ltown_sw/streets/st4","east",0);

add_prop(ROOM_I_LIGHT,1);IN

SGT
clone_object(RHUN+"npc/mayor")->move(this_object(),1);

}
