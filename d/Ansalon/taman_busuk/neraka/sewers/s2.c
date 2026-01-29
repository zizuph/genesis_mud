/* Ashlar, 21 Aug 97 */

#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <stdproperties.h>

inherit SEWER_BASE;

void
reset_neraka_room()
{
}

string
long_descr()
{
    return "This is a tunnel in the sewers beneath Neraka. " +
    "The tunnel is wide enough for four men to walk abreast, and it " +
    "is just as high. " + water_desc() + "The tunnel leads east and " +
    "northwest. There is an iron ladder here, leading up.\n";
}

void
create_neraka_room()
{
    set_short("in the sewers");
    set_long("@@long_descr");

    add_lsewer_items();
    add_item(({"ladder","iron ladder"}),"The iron ladder is slippery, " +
    "the rungs covered with slime. It still looks climbable though, if " +
    "you are careful.\n");
    add_item(({"rungs"}),"The rungs are covered with slime and are " +
    "slippery.\n");
    add_cmd_item(({"ladder","iron ladder"}),"climb","@@climb_ladder");

    add_lsewer_herbs();
    remove_prop(ROOM_I_LIGHT);

    reset_room();

    add_exit(NSEWER + "s1", "northwest");
    add_exit(NSEWER + "s3", "east");
    add_exit(NOUTER + "blue/ware1", "up", "@@go_up", 0);
}

int
go_up()
{
    write("You climb up the ladder and through the trapdoor.\n");
    return 0;
}

string
climb_ladder()
{
    TP->command("$up");
    return "";
}
