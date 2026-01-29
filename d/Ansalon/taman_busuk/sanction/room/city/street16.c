#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/guild/dragonarmy/guild.h"
#include "/d/Ansalon/taman_busuk/sanction/local.h"
#include <macros.h>

inherit SANCOUTROOM;

object patrol;

string check_patrol_tavern();

void
reset_sanction_room()
{
    if(!objectp(patrol))
    {
	patrol = clone_object(SNPC + "da_member");
	patrol->set_color("red");
	patrol->set_dragonarmy_rank(1);
	patrol->arm_me();
	patrol->set_hunt_enemy(1);
	patrol->move_living("M", TO, 1, 1);
	tell_room(TO, QCNAME(patrol)+" arrives.\n");

	patrol->set_patrol_path( ({ "w","w","s","s","s","w","w","w","w","w",
				"n","e","e","e","e",
				5,
				check_patrol_tavern,
				"w","w","n","n","e","e","e","e","e" }) );
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

void
create_sanction_room()
{
    set_short("On a street before a bridge that crosses a river of lava");
    set_extra_long("Here you stand before a stone bridge " +
      "that crosses a river of lava. Across the river is " +
      "an encampment of a contingent of the Red Dragonarmy.");

    add_item(({"stone bridge","bridge"}),
      "To your north is a sturdy stone bridge that " +
      "crosses a river of lava. Across the bridge is " +
      "you see an encampment of a contingent of the " +
      "Red Dragonarmy.\n");

    add_item(({"encampment","red dragonarmy","camp"}),
      "Across the river of fire is the camp of a " +
      "contingent of the Red Dragonarmy.\n");

    add_item("houses",
      "To your west rise houses and similar structures " +
      "that were probably owned by the rich and " +
      "influential before the occupation of the city. " +
      "Now they simply stand out as being less rundown " +
      "than those buildings that stand in the expansive " +
      "slums of this city.\n");

    add_item(({"river of lava","lava","river"}),
      "To your northeast two rivers of lava meet, one " +
      "coming from the east and one from the south. This " +
      "combined flow passes you to the west towards " +
      "the harbour of the city. Even from this distance " +
      "the heat is almost unbareable.\n");

    add_exit(SCITY + "street17","south",0);
    add_exit(SCITY + "street15","west",0);
    add_exit(SRED + "bridge","north",0);

    reset_room();
}
