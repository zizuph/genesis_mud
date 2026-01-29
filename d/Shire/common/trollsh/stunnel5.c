/*  File: stunnel5.c  */
inherit "/d/Shire/common/lib/rom";
#include "/d/Shire/common/defs.h";

object troll;

create_rom()
{
    set_short("Inside a secret tunnel.");
    set_long("You are in a dark tunnel leading north and south. "
	+"The walls are black and smooth while the tunnel floor "
	+"is filled with old dried blood and guts. \n");
   	    
   add_exit(TROLLSH_DIR + "stunnel6", "north" ,0);
   add_exit(TROLLSH_DIR + "stunnel4", "south" ,0);
   	    
   add_item("wall","The wall is black and looks smooth. Blood is "
		+"trickling down from the wall...\n");

   add_item(({"guts","blood","dried blood","dried guts"}),
	 "Even though the guts may have look dried it is not. "
	+"When you feel it with your hand it is soft and gushy.\n");

   add_prop(ROOM_I_LIGHT, -2);
   add_prop(ROOM_I_INSIDE,1);

   troll = clone_object(TROLLSH_DIR + "npc/" + "trollet");
   troll->move(TO);


}

reset_rom()
{
   if (!troll) 
   {
      troll = clone_object(TROLLSH_DIR + "npc/" + "trollet");
      troll->move(TO);
   }
}

