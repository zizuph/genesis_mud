#include "../defs.h"

inherit STD("room");

public void
dark_dom(void)
{
    set_short("Entrance to Menzoberranzan.");
    set_long("This is an entrance to Menzoberranzan. "+
	"However, this seem to be quite an untravelled entrance into "+
	"the city, so be wary of what lurks behind the corners. The city looms head of you "+
	"with it's great stone columns and pillars. They are all lit up by the magical fairie "+
	"lights, so the whole city is a display of shadowy red, blue and purple lights. " +
	"Right now you cannot see any passage leading further into the city and it's famous " +
	"common quarters of merchants and pubs. Northwest of where you are standing, your " +
	"eyes gets locked on a huge stair leading up to some sort of plateau. \n");

    add_item(({"sides","side","irregular walls","walls","wall"}),
	"The stone walls are lit up by a reddish glow which seem to come from the city.\n");

    add_exit("u47", "south", check_follow);
    add_exit(P_MENZO_TIERBRECHE + "stair", "northwest");
 }