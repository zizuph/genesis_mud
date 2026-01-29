inherit "/std/room";

#include <stdproperties.h>
#include "/d/Roke/common/defs.h"

void
reset_room()
{
   object butler;
   
   butler = present("butler");
   if(butler && butler->query_name()!="ghost")
      return;
   else
      butler = clone_object(A_NPC_D + "butler");
   butler->move_living(" arrives.", this_object());
}

create_room()
{
    set_short("Garden");
    set_long(BSS("This is Pandora's garden, there are a lot of beautiful flowers here. "+
		 "There is a large door to the east.\n"));
 
    add_prop(ROOM_I_INSIDE, 0);

    add_exit(PAL_STR+"street3","west",0);
    add_exit(HOUS_D+"sittroom","east","@@no_can_do@@");

    add_item(({"door","door"}), break_string("It looks sturdy.\n",75));
    
    add_item(({"garden","garden"}),BSS(
				   "The garden looks pritty nice kept, and "+
				   "there are flowers and bushes all over\n"));

    add_item(({"flower","flowers"}),BSS(
		"There are many nice flowers here, in all of "+
		"the rainbows colours.\n"));

    add_item(({"bushes","bush"}),BSS(
		"There are lots of bushes here, both rose bushes "+
		"and others. All nicely trimmed.\n"));

    seteuid(getuid());

    reset_room();
}

no_can_do()
{
	if (present("butler"))
	{
	write("The butler stops you from going through the door.\n");
	return 1;
	}
	write("The door is locked in some strange way.\n");
	return 1;
}
