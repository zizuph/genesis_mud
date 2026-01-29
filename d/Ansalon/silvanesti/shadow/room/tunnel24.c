#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/silvanesti/shadow/local.h"
#include <ss_types.h>
#include <macros.h>
inherit SHADOW_IN;

void
reset_shadow_room()
{
    return;
}

create_shadow_room()
{
    set_short("Inside the tunnel system");
    set_long("@@long_descr");
    
    add_item(({"tunnel","tunnels","tunnel system"}), "The " +   
        "tunnels seem to twist and turn on their own whim. " +
        "Every tunnel looks as good as the next.\n");
    add_item("walls","The walls down here are made of " +
        "limestone.\n");
    
    
    add_prop(ROOM_I_LIGHT, 0);
    add_exit(SROOM + "tunnel26","east",0);     
    add_exit(SROOM + "tunnel25","northwest",0);
    add_exit(SROOM + "tunnel23","southeast",0);
    
    reset_shadow_room();
}

string
long_descr()
{
    return "You are in the tunnel system on the lower level " +
        "of the caverns.  No natural light is able to penetrate " +
        "this deep.  The tunnels seem to twist in a variety of " + 
        "directions, and you cannot see well enough to judge " +   
        "one over another.  You feel uncomfortable in the caves "+
        "as you feel the walls are absorbing the light.  It is "+ 
        "very difficult to see and you feel you should tread "+
        "carefully.\n";
}
