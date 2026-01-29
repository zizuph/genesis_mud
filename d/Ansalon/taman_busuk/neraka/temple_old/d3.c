/* Ashlar, 30 Sep 97 */

#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <stdproperties.h>
#include "../guild/guild.h"

inherit TEMPLE_BASE;

void
reset_neraka_room()
{
}

string
long_descr()
{
    return "This is the east end of a corridor in the lower level of " +
    "the temple. To the east is a large door set in a curving wall, " +
    "around which smaller corridors lead northeast and southeast.\n";
}

void
create_neraka_room()
{
    set_short("at an intersection of corridors in the temple");
    set_long("@@long_descr");

    add_temple_items();
    add_item(({"door","large door"}),
    "The large door is made of oak inlaid with metal. It is set in the " +
    "curving wall to the east.\n");

    add_item(({"curving wall"}),
    "The curving wall indicates that it houses a near-circular chamber " +
    "within.\n");

    reset_room();

    add_exit(NTEMPLE + "d2", "west","@@go_west");
    add_exit(NTEMPLE + "d5", "northeast");
    add_exit(NTEMPLE + "abbey", "east");
    add_exit(NTEMPLE + "d6", "southeast");
}

int
go_west()
{
    if (TP->query_wiz_level() || (TP->query_guild_member(GUILD_NAME)))
    {
        write("You feel a chill passing through you as you go west, and " +
        "you realise that part of the corridor was warded.\n");
        return 0;
    }
    else
    {
    	write("You attempt to go west, but you find that you cannot " +
    	"move in that direction. That part of the corridor must be " +
    	"warded.\n");
    	return 1;
    }
}

void
dispel_magic(int strength)
{
    tell_room(TO,"To the west, the corridor lights up from wall to wall " +
    "with a shimmering light as the powerful warding absorbs the dispel " +
    "attempt. The light dies down after a short while.\n");
}
