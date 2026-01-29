
inherit "/d/Rhovanion/lib/room";
#include <macros.h>
#include "/sys/stdproperties.h"
#include "/d/Rhovanion/farlong.h"

create_room()
{
set_short("Abandoned home");
set_long(break_string("You have stepped inside an empty shack in this"
	+" small town.  It is made of wood, apparently built with great"
	+" care at some time in the past.  Now, this place is deserted."
	+ "  No sign of the inhabitants remains.  The place looks as"
	+" it were invaded at some not-so-distant time in the past."
	+"  Furniture is overturned, and a few signs of a struggle"
	+" remain evident."
	+"\n",75));

AE(RHUN+"stown5/crossroads","north",0);

add_prop(ROOM_I_LIGHT,1);IN

}

