inherit "/d/Rhovanion/lib/room";
#include <macros.h>
#include "/sys/stdproperties.h"
#include "/d/Rhovanion/defs.h"

init()
{
	::init();
	add_action("do_start","start");
}

create_room()
{
	set_short("Rune chamber");
	set_long("This small chamber is a resting place for"
		+" the Spellweavers.  It is completely featureless, carved,"
		+" as the rest of the guild, from a strange, dark stone.  You"
		+" may <start here> if you are a member of this guild."
		+"\n");
	
	add_exit(SWG+"strune_","west",0);
	
	add_prop(ROOM_I_LIGHT,1);
	add_prop(ROOM_I_INSIDE);
	
	add_item(({"wall","walls","stone"}),"The walls of this"
		+" chamber are made of dark stone, and are polished"
		+" smooth.  You are unable to recognize the variety of"
		+" stone from which they were made, centuries ago."
		+"\n");
	add_item(({"corner","corners"}),"Peering into the corners of"
		+" this shadowy chamber, you can see nothing; yet you are unable to"
		+" shake the feeling that some dark force watches over you, and over"
		+" this place.\n");
	
}

int
do_start(string str) {
    if (str == "here")
    {
        this_player()->set_default_start_location(SWG+"startroom");
        write("You shall begin your journeys here in"
		+" the home of the Spellweavers from this time"
		+" forth.\n");
        return 1;
    }
    return 0;

}

