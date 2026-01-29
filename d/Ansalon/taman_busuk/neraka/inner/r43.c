/* Ashlar, 20 Jul 97 */

#include "/d/Ansalon/common/defs.h";
#include <macros.h>
#include "../local.h";

inherit INNER_OUT;

void
create_neraka_room()
{
    set_short("on the Queen's Way");
    set_extra_long("You are walking along the Queen's Way, the main street " +
        "of Neraka. The street leads northeast and west, flanked on both " +
        "sides by the tall city walls. A heavy wooden door blocks an old house "+
		"to the north.\n");

    add_item_citywalls();
    add_item_street1();
	
    add_item(({"door","house"}),"The wooden door appears unlocked, and the house "+
	   "seems abandoned. It might be possible to 'enter' the house.\n");
	   
	add_cmd_item(({"door","house","the door","the house"}),
    ({"enter","open"}),
    ({"@@enter_house","@@enter_house"}));
	  
    add_exit(NINNER + "r42", "west");
    add_exit(NINNER + "r44", "northeast");
}

string
enter_house()
{
    if (TP->move_living("M",NINNER + "house1"))
    {
        return "For some reason, you are unable to enter the house. " +
        "Please leave a bugreport of this.\n";
    }
    tell_room(TO, QCTNAME(TP) + " enters the old house.\n", TP);
    return "";
}
