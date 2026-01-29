#include "../defs.h"

inherit STD("room");

public void
dark_dom(void)
{
    set_short("An carved arched opening near Menzoberranzan");
    set_long("You find yourself standing under an arched opening near "+
	"the city of Menzoberranzan. This seem to be quite an untravelled way into "+
	"the city, so be wary of what lurks behind the corners. "+
	"The dark stone walls are slightly lit up by reddish glow, which seems to come from " +
	"the direction of the city. \n");

    add_item(({"sides","side","irregular walls","walls","wall"}),
	"The stone walls are lit up by a reddish glow which seem to come from the city.\n");

    add_exit("u45", "west", check_follow);
    add_exit("u47", "north", check_follow);
 }