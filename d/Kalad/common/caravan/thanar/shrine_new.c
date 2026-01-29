
/* This is the startlocation of the Thanar guild.
 * It is beeing kept here for backward compability
 * The rest of the guild-files have been moved to
 *  common/guilds/thanar
 * Ull 19.02.96
 */

inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#include <thanardefs.h>

create_room()
{ 
    ::create_room();
    INSIDE;
    set_short("A shrine dedicated to the glory of Thanar");
    set_long("A shrine dedicated to the glory of Thanar, patron god of "+
      "all humanity. Here you may bask in the glorious power that is "+
      "Thanar's to wield, simply type 'start here' and you shall forever "+
      "after begin your journeys from this place of quiet solitude.\n");
    add_prop(ROOM_M_NO_ATTACK,"You would not dare to incur the wrath of "+
      "Thanar by such a foolish act!\n");
    add_exit(THANAR(joinroom),"south",0,-1);
}
init()
{
    ::init();

    add_action("start","start");
}
int start(string s)
{
    if(s =="here" && (IS_MEMBER(TP)))
    {
	TP->set_default_start_location("/d/Kalad/common/caravan/thanar/shrine");
	write("From now on you shall start here, within the shrine to Thanar.\n");
	return 1;
    }

    write("Either you can't type or you are not a member. Please try again.\n");
    return 1;
}
