/*
 * The old graveyard
 */

#include "/d/Krynn/common/defs.h"
#include <macros.h>
#include <ss_types.h>
#include "local.h"
inherit GRAVE_STD;

#define  NO_CLIMB  200 /* can't climb fence */
#define  DAMAGE    30  /* tangleshoot usually traps, this one injures */

object ob;

create_solace_room()
{
    set_short("Old Graveyard");
    set_long(BS("This is part of the old graveyard. " +
		"It is in desperate need of upkeep. The o" +
		"ld gravestones are covered with moss, are chipped, cracked," +
		" broken, and some are even tipped over. The old peeling fe" +
		"nce forms its southeast corner here, running north and west" +
		", just to the east and south of the graves. An ancient che" +
		"stnut tree towers over head. " +
		"", 70));

    add_item(({"tree", "chestnut tree", "chestnut"}), BS(
							 "This is a beautiful ancient chestnut tree. Its beauty is eerie, gn" +
							 "arles twisting into shadowy figures and faces, animated by its sway" +
							 " in the breeze ... wait a minute ... there is NO breeze ...",70));
    add_item(({"fence", "old fence", "old wrought iron fence",
		 "wrought iron fence", "south fence", "east fence"}),
	     "The fence seems to cover the entire elder graveyard.\n");
    add_item("hole", BS(
			"This is a tiny little rodent hole and it is protected by the 'Anima" +
			"l Rights Activists' magic.", 70));

    ADD_GRAVES;
    ADD_GRAVEYARD;
    READ_GRAVE;

    add_cmd_item("fence", "climb", "@@tangleshoot");
    add_cmd_item("fence", "jump", "@@tangleshoot");
    add_cmd_item("tangleshoot", "kill",  BS(
					    "You can't kill the tangleshoot. You hack it up a bit, " +
					    "but there is just too much of it to kill.", 70));

    add_exit(TDIR + "o_grave4", "north", "@@north_msg");
    add_exit(TDIR + "o_grave5", "west");
    set_alarm(1.0,0.0,"batsay");

    reset_room();
}

reset_solace_room()
{
    if (!ob)
      (ob = clone_object(MONSTER + "skeletal_rat"))->move_living("xx", TO);
}

tangleshoot()
{
    if (this_player()->query_skill(SS_CLIMB) < (NO_CLIMB))
    {
	say(QCTNAME(this_player()) + "was grabbed by the tangleshoot and\n" +
	    "injured.\n");
	this_player()->reduce_hit_point(DAMAGE);
	return("You are grabbed by the tangleshoot. It injures you.\n");
    }
    else
      return("Greetings Guru climber. This is below your skill.\n");
}

north_msg()
{
    write("The chestnut tree seems to laugh at you as you go.\n");
    return 0;
}

void
batsay()
{
    tell_room(TO,
	      "A chestnut bonks you on the head, then rolls into a hole.\n");
}
