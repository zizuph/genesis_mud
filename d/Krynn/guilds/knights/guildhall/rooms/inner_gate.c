/* Vingaard Keep coded by Percy. */
/* Guarding of the gate by Aridor */
/* Modified by Morrigan, 11/11/96 for the New Vingaard Keep */

#include <ss_types.h>
#include <macros.h>
#include <cmdparse.h>
#include "../../local.h"

inherit IN_BASE;

#define COURTY      VROOM + "inner_court"

object guard1, guard2, guard3, guard4;

/* load the gate guards */
void
reset_vin_room()
{
    if (!guard1)
    {
	guard1 = clone_object(VNPC + "inner_gate_guard");
	guard1->move(TO);
	guard1->set_block_dir("south");
    }
    if (!guard2)
    {
	guard2 = clone_object(VNPC + "inner_gate_guard");
	guard2->move(TO);
	guard2->set_block_dir("south");
    }

    if (!guard3)
    {
	guard3 = clone_object(VNPC + "inner_gate_guard");
	guard3->move(TO);
	guard3->set_block_dir("south");
    }

    if (!guard4)
    {
	guard4 = clone_object(VNPC + "inner_gate_guard");
	guard4->move(TO);
	guard4->set_block_dir("south");
    }
}

void
create_vin_room()
{
    set_short("Inner Gate of Vingaard");
    set_long("This is the inner gate of Vingaard Keep. This gate "+
      "protects the inner sanctum of Vingaard Keep, where the "+
      "Knights of Solamnia guild hall is located. It is typically "+
      "well defended, and it is doubtful anyone could break down such "+
      "a massive wall of steel and stone. To the north lies the inner "+
      "courtyard, while an archway exists to the south.\n");

    AE(COURTY, "north", "@@go_north");
    AE(VROOM+"archway", "south", 0);

    AI(({"inner courtyard","courtyard"}),"This is the inner courtyard " +
      "of Vingaard Keep, an open area.\n");
    AI(({"ceiling","floor"}),"It is made of a dark stone.\n");
    AI(({"dark stone","stone"}),"It is difficult to tell what it is, " +
      "only that it is volcanic in origin.\n");
    AI("archway","The archway to the south leads to the outer courtyard, "+
      "and two guard posts.\n");   
    AI(({"wall", "walls"}), "The walls are made of a dark stone.\n");
    AI(({"gate", "gates","portcullis","inner gate"}), "@@gate");
    add_prop(ROOM_I_LIGHT, 2);
    add_prop("_room_i_allow_steed", 1);
    reset_room();
}

void
init()
{
    ::init();
    ADD("knock_on_gate","knock");
}


/* add_item descriptions */
gate()
{
    if ((COURTY)->query_portcullis_closed())
	write("The gate is made of iron. It looks extremely solid. At the " +
	  "moment, the gates are closed! A most disturbing sign!\n");
    else
	write("The gate is made of iron. It looks extremely solid. At the " +
	  "moment however the gate lies open, a sign of the " +
	  "knighthood's confidence in their power to defeat the evil " +
	  "in the world.\n");
    return "";

}

/* return 0 to allow travel under gate */
int
go_north()
{
    object gu;

    if ((COURTY)->query_portcullis_closed())
    {
	write("The portcullis is closed, denying you access.\n");
	return 1;
    }

    gu = present("knight", TO);
    if (!CAN_SEE(gu, TP))
	return 0;
    if (gu && TP->query_prop("_i_attacked_in_vingaard"))
    {
	gu->command("say Fool! Do you expect to be able to just waltz "+
	  "into Vingaard, after attacking its inhabitants?");
	write("You are roughly shoved back as you try to pass the Inner "+
	  "Gate of Vingaard.\n");
	return 1;
    }
    write("You pass under the Inner Gate, into a large courtyard inside "+
      "Vingaard Keep.\n");
    return 0;
}

/* return 0 to allow travel south */
int
go_south()
{
    return 0;
}

int
knock_on_gate(string str)
{
    NF("What?\n");
    NF("Knock where?\n");
    if (!str)
	return 0;
    if (str != "gate" && str != "on gate" && str != "gates" &&
      str != "on gates" && str != "portcullis" && str != "at portcullis" &&
      str != "at gate" && str != "at gates")
	return 0;

    if (!(COURTY)->query_portcullis_closed())
    {
	write("The gate is open already.\n");
	return 1;
    }
    write("You knock on the gate.\n");
    say(QCTNAME(TP) + " knocks on the gate.\n");
    if (TP->query_guild_name_occ() != "Solamnian Knights")
    {
	write("Nothing happens.\n");
	return 1;
    }

    (COURTY)->do_open_portcullis();
    return 1;
}
