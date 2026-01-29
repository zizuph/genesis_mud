#include "defs.h";

inherit LIB_DIR + "rom";


object nasty_troll;

create_rom()
{
	set_short("secret passage");
	set_long(
		 "You have entered a secret passage in the tunnel. "
		+"It is awsome dark here, and the smell rips trough your heart! "
		+"You can see large footprints on the floor, probably made by "
		+"some huge troll. There are cobwebs hanging down from the walls, "
		+"so it must have been quite a while since anyone have been here.\n");
		
		add_item(({"tunnel"}),
			 "The tunnel is dark and moisty, and it seems like it has been carved "
			+"out of just earth.\n");
		add_item(({"footprints"}),
			 "They are really huge, maybe you should just leave this place "
			+"before any of those who made these footprints shows themselves!!\n");
			
		add_item(({"floor"}),
			 "The floor is all blood stained, filled with dried guts everywhere.\n");
			 
		add_item(({"cobwebs","cobweb"}),
			 "The cobwebs are huge, probably made by the evil spider guarding the "
		        +"tunnel.\n");
		        
		add_prop(ROOM_I_LIGHT,-1);
		add_prop(ROOM_I_INSIDE, 1);
		
		add_exit(TROLLSH_DIR + "stunnel2", "east", 0, 3);
}

			