
inherit "/d/Rhovanion/lib/room";

#include "/d/Rhovanion/farlong.h"

init()
{
    ::init();
    add_action("dive", "dive");
}

create_room()
{
    set_short("Riverbank");
    set_long("You are on the banks of the River Carnen, near "+
	"to where it empties into the Sea of Rhun.  You may "+
	"follow it southeast, or head west across the plains "+
	"of Rhun to where a dirt road sits.  The river flows "+
	"swiftly past here.\n");
	
    AE(RHUN+"hills/plains", "west");
    AE(RHUN+"hills/s1", "southeast");
    
    add_item("river", "It appears you could dive into the "+
	"water here.\n");
}

int
dive()
{
    /* Add tests on swim skill, & then send them to the 
     * area for the Rhosgobel quest.
     */
     
     write("At current, it is impossible to dive down "+
	"into the waters; perhaps you could return at "+
	"a later date?\n");
    return 1;
}
