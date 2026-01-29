#include "defs.h";
inherit "/d/Shire/common/trollsh/tunnrom";

create_tunnrom()
{
    set_short("dark tunnel");
    set_long(
    "You are walking still further into the tunnels. Darkness " +
    "lays as a creepy carpet over you, giving an unsafe feeling.\n");


	add_prop(ROOM_I_LIGHT,0);
	add_exit(TROLLSH_DIR + "tunnel5", "west", 0, 2);
	add_exit(TROLLSH_DIR + "tunnel7", "south", 0, 2);    
	add_exit(TROLLSH_DIR + "tunnel6", "southwest", 0, 2);  
}

