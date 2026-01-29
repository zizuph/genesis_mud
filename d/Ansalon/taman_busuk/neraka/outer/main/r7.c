/* Ashlar, 19 Jul 97 */

#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/neraka/local.h"

inherit OUTER_OUT;

void
create_neraka_room()
{
	set_short("a dirt road outside Neraka");
    set_extra_long("You are walking along a dirt road a short distance " +
        "north of Neraka. You see the city walls to the south, while a " +
        "smaller road branches off to the west. The main road continues " +
        "north towards the distant mountains.");
    add_item_dirtroad();
    add_item(({"walls","city walls","inner city walls","inner walls"}),
        "They are giant walls that surround the inner part of Neraka, " +
        "where only the elite officers of the Dragonarmies are allowed " +
        "to enter. You cannot make out much detail from this distance.\n");
        
    add_exit(NOUTER+"main/r8","north");
    add_exit(NOUTER+"main/r2","south");
    add_exit(NOUTER+"main/r6","west");
}
