#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/guild/dragonarmy/guild.h"
#include "/d/Ansalon/taman_busuk/sanction/local.h"
#include <macros.h>

inherit SANCINROOM;

object *guards = allocate(6);

void
reset_sanction_room()
{
    int i;

    setuid();
    seteuid(getuid());

    for(i=0; i<sizeof(guards); i++)
    {
	if(!guards[i])
	{
	    if (random(7))
	    {
		guards[i] = clone_object(SNPC + "da_member");
		guards[i]->set_color("red");
		guards[i]->set_dragonarmy_rank(random(4) ? 1 : 2);
		guards[i]->arm_me();
	    }
	    else
	    {
		switch(random(5))
		{
		case 0:
		case 1:
		    guards[i] = clone_object(DRAGONARMY_NPC+"aurak");
		    break;
		case 2:
		case 3:
		    guards[i] = clone_object(DRAGONARMY_NPC+"sivak");
		    break;
		default:
		    guards[i] = clone_object(DRAGONARMY_NPC+"bozak");
		}
		guards[i]->set_color("red");
		guards[i]->arm_draconian();
	    }

	    guards[i]->set_hunt_enemy(1);
	    guards[i]->move_living("M", TO, 1, 1);
	    tell_room(TO, QCNAME(guards[i])+
		" enters and takes the guard post.\n");
	}
	else if(!guards[i]->query_attack() && E(guards[i]) != TO)
	{
	    tell_room(E(guards[i]), QCTNAME(guards[i])+" runs away.\n");
	    guards[i]->move_living("M", TO, 1, 1);
	    tell_room(TO, QCNAME(guards[i])+
		" enters.\n");
	}
    }
}

void
create_sanction_room()
{
    set_short("within a stifling guardhouse of the Red Dragonarmy");
    set_long("@@long_descr");

    add_item(({"guardhouse","room"}),"@@long_descr");
    add_item(({"thick black stonework","black stonework","stonework",
	"stones"}),
      "The thick black stones that make up this guardhouse look to " +
      "be made of basalt. While common to these parts, this stone retains " +
      "heat extremely well. You certainly do not envy the guards stationed here.\n");

    add_exit(SRED + "r1","east",0);

    reset_room();
}


string
long_descr()
{
    return "You stand within a guardhouse on the edge of Sanction. " +
    "It is extremely hot in here, probably due to a combination " +
    "of the thick black stonework of the room as well as the smothering " +
    "heat of the fiery city of Sanction.\n";
}
