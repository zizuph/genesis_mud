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
    set_short("On the wall");    
    set_long("@@long_descr");

    add_item("drop","You are about halfway between levels.\n");
    add_item("wall","You hold onto the wall and easily spot "+    
        "your next foothold.\n");
        
    add_prop(ROOM_I_LIGHT, 0);
    add_exit(SROOM + "entrance","up",0);
    add_exit(SROOM + "tunnel02","down",0);

    reset_shadow_room();
}
 
string
long_descr()
{
    return "You are climbing the wall between the entrance "+ 
        "and the lower levels of the caves.  No natural light "+
        "at all is able to penetrate this deep.  The wall is "+
        "a very easy climb as it slants somewhat away from "+
        "the entrance, letting gravity keep you in place.  "+
        "The cavern walls have changed now from granite to "+
        "limestone, you begin to think the granite above was "+
        "somehow moved to its present location.  Perhaps it "+
        "is a remnant of the Cataclysm.\n";
}
