#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>

inherit BPLAINS_OUT;
#define R1 "9f"
#define R2 "10g"
#define R3 "11g"
#define R4 "9e"
#define CHANCE random(65)
object leader, ogre1, ogre2, ogre3;
object gob1, gob2, gob3, gob4, gob5, gob6;
object giant, giant2;

void
start_giant_raid()
{
	find_player("arman")->catch_msg("GIANT attack on clan.\n\n");
	log_file("clan/giant_raid",extract(ctime(time()),4,15)+ " :Giant Raid.\n", 500000);
	giant = clone_object(LIVING + "frost_giant");
	giant->arm_me();
	giant->move(TO);
	giant2 = clone_object(LIVING + "giant_leader");
	giant2->arm_me();
	giant2->move(TO);
}

void
start_ogre_raid()
{
	find_player("arman")->catch_msg("OGRE attack on clan.\n\n");
	log_file("clan/ogre_raid",extract(ctime(time()),4,15)+ " :Ogre Raid.\n", 500000);
#include "ogre_raiders.h"
}

void
reset_estwilde_room()
{
    if(CHANCE == 1)
    {
        start_giant_raid();
    }
    else if(CHANCE == 2)
    {
        start_ogre_raid();
    }
    else
	return;
}

create_estwilde_room()
{
    set_short("@@short_descr");
    set_long("@@long_descr");

    add_exit(ROOM + R1,"north",0);
    add_exit(ROOM + R2,"east",0);
    add_exit(ROOM + R3,"southeast",0);
    add_exit(ROOM + R4,"northwest",0);
    add_item_hill();

    reset_estwilde_room();
}

string
short_descr()
{
    return tod_descr1() + " before a steep hill";
}

string
long_descr()
{
    return plain_desc()+
    "To your south rises a steep hill that blocks " +
    "your view of the plains any further in that " +
    "direction.\n";
}
