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
    set_short("In the shadow caves");
    set_long("@@long_descr");
 
    add_item("walls","The walls down here are made of " +
        "limestone.  They seem capable of absorbing light.\n");
    add_item("shadows","You take a closer look at the shadowy "+
        "figures moving in the dark, but can't quite be sure "+
        "what they are.\n");
 
    add_prop(ROOM_I_LIGHT, 0);
    add_exit(SROOM + "cave19","south",0);
    add_exit(SROOM + "cave15","west",0);
    add_exit(SROOM + "cave14","northwest",0);
    
    reset_shadow_room();
}

string
long_descr()
{
    return "You are in the shadow caves below the Silvanesti " +
        "forest.  No natural light is able to penetrate this " +  
        "deep.  The tunnels open up here to a large cave where " +
        "there is plenty of room to move about.  You feel " +
        "uncomfortable in the caves as you feel the walls are " +
        "absorbing the light.  Unnatural shadows seem to move " +
        "around.  Wait... those aren't shadows!\n";
}
