#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/guild/dragonarmy/guild.h"
#include "/d/Ansalon/taman_busuk/sanction/local.h"
#include <macros.h>

inherit SANCOUTROOM;

object patrol;

string check_patrol_tavern();
string check_patrol_brothel();

void
reset_sanction_room()
{
    if(!objectp(patrol))
    {
	patrol = clone_object(SNPC + "da_member");
	patrol->set_color(random(2) ? "red" : "blue");
	patrol->set_dragonarmy_rank(1);
	patrol->arm_me();
	patrol->set_hunt_enemy(1);
	patrol->move_living("M", TO, 1, 1);
	tell_room(TO, QCNAME(patrol)+" arrives.\n");

	patrol->set_patrol_path( ({ "e","e","e","e","e","se","ne",
				"n","n","n","w","w","w","s","w","s","e",
				5,
				check_patrol_tavern,
				"w","w","w","w","n","e",
				5,
				check_patrol_brothel,
				"w","s","s" }) );
	patrol->set_patrol_time(10);
	patrol->start_patrol();
    }
}

string
check_patrol_tavern()
{
    object ob;

    setuid();
    seteuid(getuid());

    if(file_name(E(patrol)) != SCITY+"tavern")
    {
	tell_room(E(patrol), QCNAME(patrol)+" leaves.\n");
	patrol->move_living("M", SCITY+"tavern", 1, 1);
	tell_room(E(patrol), QCNAME(patrol)+" arrives.\n");
    }
    ob = clone_object("/std/coins");
    ob->set_coin_type("copper");
    ob->set_heap_size(14);
    ob->move(patrol, 1);

    patrol->command("buy beer");
    return "drink all";
}

string
check_patrol_brothel()
{
    setuid();
    seteuid(getuid());

    if(file_name(E(patrol)) != SCITY+"brothel")
    {
	tell_room(E(patrol), QCNAME(patrol)+" leaves.\n");
	patrol->move_living("M", SCITY+"brothel", 1, 1);
	tell_room(E(patrol), QCNAME(patrol)+" arrives.\n");
    }
    patrol->command("say Any new girls here?");
    return "say I will be back when my duty ends!";
}

void
create_sanction_room()
{
    set_short("A street in the southern parts of central Sanction");
    set_extra_long("Here you walk along a street on the southern " +
      "edge of a teeming slum consisting of filthy, closely-packed " +
      "buildings that create a maze of winding alleys. " +
      "To your west are a pair of gates that " +
      "mark the boundary between Sanction's dock and " +
      "the city of Sanction.");

    add_item(({"sanction's dock","dock"}),
      "Through a pair of gates to your west you can make out " +
      "the docks of Sanction.\n");
    add_item(({"sanction","city","city of sanction"}),
      "Open your eyes buddy, your standing in it!\n");
    add_item(({"gates","gate","pair of gates"}),
      "A pair of gates stand to your west, allowing " +
      "you to enter into Sanction's dock area.\n");
    add_item("street","You are walking upon a cobbled street " +
      "in the city of Sanction. To your north you believe you " +
      "can enter the slum district of this wretched city from here.\n");

    add_exit(SCITY + "pier05","west",0);
    add_exit(SCITY + "street2","east",0);
    add_invis_exit(SCITY + "slum1","north",0);

    slum_descriptions();
    reset_room();
}

