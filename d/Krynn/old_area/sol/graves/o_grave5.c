#include "/d/Krynn/common/defs.h"
#include "local.h"
#include <ss_types.h>
#include <macros.h>
inherit GRAVE_STD;

#define  NO_CLIMB  200 /* can't climb fence */
#define  DAMAGE    30  /* tangleshoot usually traps, this one injures */

create_solace_room()
{
    set_short("More of the Old Graveyard.");
    set_long(BS("This is yet more of the old graveyard. The old fence runs " +
		"east to west, south of the graves. There is an especially " +
		"large old family tombstone here. " +
		"Brambles grow in abundance, blocking any movement in the " +
		"northerly direction.", 70));

    add_item(({"tombstone", "family tombstone", "old family tombstone"}), BS(
             "There is a construction fence around it. It seems that the so" +
             "meone has hired someone to clean this one up. There is are si" +
             "gns of some work already done, though not much. You wonder wh" +
             "ere the workers are.", 70));
    add_item(({"fence", "old fence", "old wrought iron fence",
		 "wrought iron fence"}), "It's in need of repairs, but " +
	"still it keeps you from going south.\n");

    add_cmd_item("fence", "climb", "@@tangleshoot");
    add_cmd_item("fence", "jump", "@@tangleshoot");
    add_cmd_item("tangleshoot", "kill",  BS(
                "You can't kill the tangleshoot. You hack it up a bit, " +
                "but there is just too much of it to kill.", 70));

    ADD_GRAVES
    ADD_GRAVEYARD
    READ_GRAVE

    add_exit(TDIR + "o_grave6", "east");
    add_exit(TDIR + "fence2", "west", "@@west_msg");
    set_alarm(10.0,0.0,"batsay");
}

tangleshoot()
{
     if (this_player()->query_skill(SS_CLIMB) < (NO_CLIMB))
     {
	say(QCTNAME(this_player()) + " was grabbed by the tangleshoot and\n" +
		"injured.\n");
	this_player()->reduce_hit_point(DAMAGE);
	return("You are grabbed by the tangleshoot. It injures you.\n");
    }
    else
	return("Greetings Guru climber. This is below your skill.\n");
}

west_msg()
{
     write("You push through the dense bushes. You find you can only follow\n"
	 + "the fence at this point.\n");
     return 0;
}

void
batsay()
{
     tell_room(TO, "A bat flapped its wings as it passed over your head.\n");
}
