/* the inside of the tent
 *
 * Aridor 08/97
 */

#include "/d/Krynn/common/defs.h"

inherit R_FILE

void
create_krynn_room()
{
    set_short("Inside a nomadic chum");
    set_long("You are a nomadic chum of Abanasinian design, " +
        "although the leather and hides seem to have been modified for " +
        "much colder conditions. In the centre of the tent is a small " +
        "fire, creating a thin stream of smoke that rises out through " +
        "a small hole at the top.\n");

    add_item(({"chum","tent","leather","hides"}),"This circular tent is " +
        "made of leather and hides from alpine elk, commonly found " +
        "in the Tharkadan ranges.\n");
    add_item(({"fire","small fire","smoke","small hole","hole"}),
        "A small fire burns in the middle of the tent, keeping it warm. " +
        "Smoke rises lazily from the fire and up through a small hole " +
        "at the apex of the tent.\n");

    INSIDE;
    NO_TIME;
}


int
quit(string str)
{
    write("You can't quit the realms from inside the tent. You will " +
        "need to exit first.\n");
    return 1;
}

void
init()
{
    ADA("quit");
    ::init();
}