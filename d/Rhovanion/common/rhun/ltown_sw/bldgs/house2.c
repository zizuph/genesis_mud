#pragma save_binary

inherit "/d/Rhovanion/lib/room";
#include <macros.h>
#include "/sys/stdproperties.h"
#include "/d/Rhovanion/farlong.h"

create_room()
{
set_short("Small home");
set_long(break_string("You have stepped into a small home in this large"
	+" town.  The walls are hewn of wooden logs, and the"
	+" ceiling thatched.  A few scattered bits of furniture are here--"
	+" a bed, chair and table, for the most part.  The resident of"
	+" this tiny estate is obviously quite poor.  The only"
	+" exit is back out a small open doorway to the north."
	+"\n",75));

AE(RHUN+"ltown_sw/streets/st7","north",0);

add_prop(ROOM_I_LIGHT,1);IN

add_item(({"furniture","bed","table","chair","chairs"}),break_string("The"
	+" furniture which adorns this humble abode is all made"
	+" from wood.  It is of no interest to you.\n",75));

SGT
clone_object(RHUN+"npc/poorwoman")->move(this_object(),1);
SGT
clone_object(RHUN+"npc/poorchild")->move(this_object(),1);

}
