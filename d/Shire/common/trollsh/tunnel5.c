inherit "/d/Shire/common/trollsh/tunnrom";
#include "../defs.h"
#include <stdproperties.h>

create_tunnrom()
{
    set_short("Dark tunnel");
    set_long("You are walking in the tunnels underneath the trollshaws. "
    	    +"The place is covered with utter darkness, and has a foul smell "
    	    +"in the air. Bones lay scatered on the ground, teared appart "
    	    +"by some nasty creature. The walls, covered with dirt, are moist "
    	    +"and make you feel all closed up.\n");
    	    
    add_exit(TROLLSH_DIR + "tunnel4", "east", 0, 2);
    add_exit(TROLLSH_DIR + "hall_room", "west", 0, 2);
    add_exit(TROLLSH_DIR + "tunnel6","south",0,2);
    
    add_prop(ROOM_I_LIGHT, -2);
    add_prop(ROOM_I_INSIDE, 1);
}
