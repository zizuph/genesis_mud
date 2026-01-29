/* Elmore, 23 Dec 15 */

#include "/d/Ansalon/common/defs.h";
#include <macros.h>
#include "../local.h";

inherit INNER_IN;

void
create_neraka_room()
{
    set_short("in an old ransacked house");
    set_long("You have entered an old house in the inner city of Neraka. Every piece of "+
	    "furniture has been destroyed and the floor is filled with broken pottery and debris. "+
		"Empty crates are stacked in one corner and a few rays of light illuminates the deserted "+
		"room. The ceiling is somewhat collapsed and the stairway leading upwards has been blocked "+
		"by trash and broken furniture. There is a door leading out to the inner city.\n");

    add_item_inside();
    add_item(({"crates","crate"}),
        "Stacks of crates line the walls. Looking further it seems as if there's a crack in the floor "+
		"leading down into the darkness.\n");
    add_item("crack","You can't see anything, it might lead to the basement.\n");
    add_item("door","The door leads south out of the house.\n");
    add_item("ceiling","It is collapsed, there is no way to reach the top floor.\n");
    add_item(({"debris","furniture", "pottery"}),"It is junk, it can't be used for anything.\n");
	
	add_prop(ROOM_I_ALLOW_STEED,0);

    add_exit(NINNER + "r43", "out");
	
	add_cmd_item(({"crack","basement","the crack","the basement"}),
    ({"enter"}),
    ({"@@enter_basement"}));
}



string
enter_basement()
{
    if (TP->move_living("M",NINNER + "basement1"))
    {
        return "For some reason, you are unable to enter the basement. " +
        "Please leave a bugreport of this.\n";
    }
    tell_room(TO, QCTNAME(TP) + " enters the basement.\n", TP);
    return "";
}
