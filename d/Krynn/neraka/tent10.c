/* Tantallon coded by Nick */

#include "/d/Krynn/common/defs.h"
#include "local.h"
inherit TANTALLON_INSIDE;
#include <macros.h>

object priest;

create_tantallon_room()
{
    object door;

    set_short("In evil tent");
    set_long(BS(
	"You are in a tent. There are no windows in the walls but light " +
	"shines from a strange orb floating in the air. You see a small " +
	"altar in one corner. It seems to be the source of the evil. " +
	"", SL));

    add_item("orb", "It's floating in the air, nothing holding it up.\n");
    add_item("altar",
      "It's small but some powerful force seems to protect it.\n");
    add_cmd_item("orb", ({"get", "touch"}), ({
	"When you try to reach it it moves away from you.\n",
	"You reach for the orb but it moves away as if by magic.\n"}));

    add_exit(TDIR + "under10", "down", 0);

    reset_tantallon_room();
}

reset_tantallon_room()
{
    if(!objectp(priest))
    {
	priest = clone_object(MON + "ev_priest");
	priest ->move(TO);
    }
}

init()
{
    ::init();
    ADA("pray");
    ADA("kneel");
}

kneel()
{
    write(BS("You kneel in front of the altar. You somehow feel someone is " +
	"pleased with you.", SL));
    say(QCTNAME(TP) + " kneels at the altar.\n");
    return 1;
}

pray()
{
    write("You mumble a short prayer at the altar.\n");
    say(QCTNAME(TP) + " mumbles a short prayer at the altar.\n");
    return 1;
}
