#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/common/guild/lib/councilroom.c";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"

#define COMPANY_NUMBER 1
#define MASTER_COUNCIL_BOARD (BOARD_DIR + "council_master")

void
reset_councilroom()
{
    seteuid(getuid(this_object()));

    /*
     * This may seem like a strange construct, but I want the master object
     * to be in this room and this construct works, so let it be.
     */
    call_other(MASTER_COUNCIL_BOARD, "teleledmingsanka");
    find_object(MASTER_COUNCIL_BOARD)->move(this_object(), 1);
}

void
create_councilroom()
{
    set_long(BSN("This large, spacious room in the second floor of the " +
        "guildhouse of the Gondorian Rangers is the Council-room of the Council " +
        "of the Rangers. The Council consists of three Captains of the Ranger " +
        "companies and their deputies, and their task is to form the future of " +
        "the Guild of the Rangers of the Westlands. There is a private bulletin "+ 
        "board here for the Council and the Chieftain of the Rangers to use, "+
	"and a long settle. "+
        "A poster on the wall explains the commands that are available "+
        "to council members here."));

    clone_object(RANGER_DIR + "obj/cdoor2")->move(TO);
    add_exit(RANGER_GON_DIR+"office", "east", check_sitting, 0, 1);
    set_company_number(COMPANY_NUMBER);
    set_alarm(0.0, 0.0, reset_councilroom);

    add_prop(ROOM_I_NO_CLEANUP, 1);
}

void 
init()
{
    ::init();
    init_council_room();
}
