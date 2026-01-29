
#include "/d/Krynn/common/defs.h"


inherit "/d/Krynn/std/room";
inherit RECRUIT_BASE



/* Redefine this function if you want only special people to be able to recruit.
 * Returns: 0 = Not allowed to recruit
 *          1 = Allowed to recruit
 * Default is 0
 */
int
hook_allowed_to_recruit(object who)
{
    return 1;
}


/* Redefine this function if you want only special people to be able to raise funds.
 * Returns: 0 = Not allowed to raise funds
 *          1 = Allowed to funds
 * Default is 1
 */
int
hook_allowed_to_raise_funds(object who)
{
    return 1;
}

void
create_krynn_room()
{
    set_army("Blue Dragon Army");

    set_short("Recruiting room");
    set_long("This is an example room for the recruitment code. " +
	     "A sign has been hung on one wall with instructions.\n");
    add_item(({"sign","instructions"}),
	     "@@read_recruit_fund_sign@@");
    add_cmd_item(({"sign","instructions"}),"read",
		 "@@read_recruit_fund_sign@@");

}

void
init()
{
    init_recruit_fund();
    ::init();
}


