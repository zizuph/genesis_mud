/* A beer tent in Tantallon, coded by Nick */

#include "/d/Krynn/common/defs.h"
#include "local.h"

inherit TANTALLON_INSIDE;

#include QUESTH
#include <macros.h>
#include <stdproperties.h>

sleep_man()
{
    if (!present("sleepy",TO))
	clone_object(MON + "sl_human")->move_living("xxx", TO);
}

reset_tantallon_room()
{
    object beer;
    if (!present("bartender"))
    {
        beer = clone_object(MON + "bartender1");
        beer->move_living("xxx", TO);
    }
    if (!present("table"))
	clone_object(OBJ + "table1")->move(TO, 1);
    set_alarm(5.0,0.0,"sleep_man");
}

create_tantallon_room()
{
    set_short("Inside The Old Lazy Inn");
    set_long(BS(
        "You are now inside the The Old Lazy Inn. You understand that this " +
	"place has earned that name when you look around. There is dust " +
	"all over the place and a lot of people are sleeping at the " +
	"tables. Everything is calm in here, a good place for a nap it "+
	"seems. The bar stands in one corner but it looks as if it " +
	"has never been used.", SL));

    add_item("tent",
        "It's a small dusty tent.\n");
    add_item("people", BS(
        "They are all leaning agains each other or the tables sleeping. " +
	"You can hear them breathing calmly.", SL));
    add_item("bar", BS(
        "It's large and made out of wood but very dusty. There are some " +
	"marks in the dust from something that might have been bottles.", SL));
    add_item(({"bottle", "bottles", "bottles on table", "bottle on table"}),
	"Some of the bottles still have beer in them.\n");
    add_item(({"table", "tables", "wooden table", "wooden tables"}),
	     "Some nice wooden tables for putting beer on.\n");

    add_exit(TDIR + "city18", "west", 0);

    reset_room();

    INSIDE;

    add_prop(OBJ_S_WIZINFO, "Here the players must 'get beer from table' " +
	"in order to be able to solve the\nbeer quest. Four bottles " +
	"can be taken each reset 'exa table' shows if it is\npossible " +
	"to take any bottles. A player who has solved the quest already " +
	"can't\n" +
	"take any bottles, and if the player has not solved the apple quest " +
	"he has\nsame problem. Note: many thinks they have solved the apple " +
	"quest but they\nhaven't. Bit 0 12 should be set in the player if " +
	"apple quest has been solved.\n");
}

init()
{
    ::init();
    ADD("nap", "sleep");
    ADA("nap");
}

nap()
{
    write("You close your eyes and try to go to sleep.\n");
    write("Suddenly you hear someone snoring and you wake up again.\n");
    say(QCTNAME(TP) + " closed " + TP->query_possessive() + " eyes for some " +
	"reason.\n");
    return 1;
}

