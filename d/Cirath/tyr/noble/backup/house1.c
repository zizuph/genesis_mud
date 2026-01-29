/* house1.c: Rich house #1. */

inherit "/std/room";
#include "defs.h"
#include "/d/Cirath/common/mobber.h"

void
reset_room()
{
    bring_room_mob("noble", TYR_NPC+"rich_hmn.c", 1, 1);
}

void
create_room()
{
    set_short("comfortable flat");
    set_long("Though clearly not at the level of opulence shared by the "+
             "mansions deeper into the quarter, this flat is still far "+
             "superior to the homes of normal Tyrians. It includes many "+
             "incredible luxuries such as a bed, a few paintings, and even "+
             "a small basin to wash one's face in.\n");

    add_item("bed", "It doesn't precisely scream luxury, but the "+
             "mattress is soft and light, and the sheets appear to have "+
             "been cleaned by actual water, rather then the traditional "+
             "standby: Sand.\n");

    add_item(({"paintings", "painting"}), "Mostly images of what long ago "+
             "faded from Athas: Forests, knights, and peaceful living. "+
             "It seems nobles enjoy staring at what they helped end.\n");

    add_item(({"basin", "small basin", "water"}), "The basin is empty for "+
             "now, though a few droplets still cling to the side.\n");

    add_cmd_item(({"hands", "face", "basin"}), "wash", "The basin has no "+
             "water in it. Perhaps the owner has used it recently?\n");

    INSIDE

    add_exit(TYR_NOBLE+"rd_hr_02.c", "west", 0, 1);
    reset_room();
}
