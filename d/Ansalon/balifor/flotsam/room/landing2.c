#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>

inherit FLOTSAM_OUT;

object *patrol = allocate(3);

int
check_patrol_here()
{
    if (E(patrol[0]) != TO)
    {
	tell_room(E(patrol[0]), QCTNAME(patrol[0])+" leaves.\n");
	patrol[0]->move_living("M",TO,1,1);
	tell_room(TO, QCTNAME(patrol[0])+" arrives.\n");
    }
    TO->reset_flotsam_room();
    return 100 + random(500);
}

void
reset_flotsam_room()
{
    int i;

    setuid();
    seteuid(getuid());

    if (!objectp(patrol[0]))
    {
	patrol[0] = clone_object(FNPC + "da_member");
	patrol[0]->set_color("blue");
	patrol[0]->set_dragonarmy_rank(2);
	patrol[0]->arm_me();
	patrol[0]->set_patrol_path( ({ "n","n", /* inn */
				"out","e","s", /* post office */
				"n","e","e", /* tavern */
				"w","s","e","s", /* Store */
				"n","e","e","s","s","w", /* guardhouse */
				"e","e", /* guardhouse */
			reset_flotsam_room,
				"w","n","n","e","s", /* tavern */
				"n","e","n","e","s", /* adv. guild */
				"n","w","n","n","e","e","s", /* guardhouse */
				"n","n", /* guardhouse */
			reset_flotsam_room,
				"s","w","w","w","w","n","w","w","w", /* warehouse */
				"out","s","s","w","w", /* warehouse */
				"out","n", /* warehouse */
			reset_flotsam_room,
				"out","e","n","e","e","s","e","e","w","w","w", /* inn */
				"out","s","w","s","w","w","n","w","w","s", /* back at landing */
			check_patrol_here
				}) );
	patrol[0]->set_hunt_enemy(1);
	patrol[0]->move(TO, 1);
    }

    for (i=1; i<sizeof(patrol); i++)
    {
	if (!objectp(patrol[i]))
	{
	    patrol[i] = clone_object(FNPC + "da_member");
	    patrol[i]->set_color("blue");
	    patrol[i]->set_dragonarmy_rank(1);
	    patrol[i]->arm_me();
	    patrol[i]->move(TO,1);
	}
	patrol[0]->team_join(patrol[i]);
	if (E(patrol[i]) != E(patrol[0]))
	{
	    tell_room(E(patrol[i]), QCTNAME(patrol[i])+" leaves.\n");
	    patrol[i]->move_living("M",E(patrol[0]),1,1);
	    tell_room(E(patrol[i]), QCTNAME(patrol[i])+" arrives.\n");
	}
    }
}

create_flotsam_room()
{
    set_short("A cobbled square in the port town of Flotsam");
    set_long("@@long_descr");

    add_item(({"cobbled square","square"}),
      "You stand on a large cobbled square that is used by the " +
      "high officers of the Dragonarmies as a landing spot " +
      "for their dragons.\n");
    add_item(({"draconians","guards"}),
      "A contingent of draconians guard this square from intruders.\n");
    add_item("flotsam","You stand in the wretched " +
      "port town of Flotsam.\n");

    add_exit(FROOM + "street44","north",0);
    reset_flotsam_room();
}

string
long_descr()
{
    return tod_descr1() + tod_descr2()+ "You stand " +
    "on a cobbled square in the port town of Flotsam. Salt " +
    "air assaults your senses with the proximity of the " +
    "Bloodsea of Istar. As this area is being used as a landing for " +
    "officer dragons, this square is heavily guarded by draconians. " +
    season_descr()+ "\n";
}
