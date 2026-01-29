#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/guild/dragonarmy/guild.h"
#include "/d/Ansalon/taman_busuk/sanction/local.h"
#include <macros.h>

inherit SANCOUTROOM;

object patrol;

string check_patrol_tavern();
string check_patrol_inn();

void
reset_sanction_room()
{
    if(!objectp(patrol))
    {
	patrol = clone_object(SNPC + "da_member");
	patrol->set_color("blue");
	patrol->set_dragonarmy_rank(1);
	patrol->arm_me();
	patrol->set_hunt_enemy(1);
	patrol->move_living("M", TO, 1, 1);
	tell_room(TO, QCNAME(patrol)+" arrives.\n");

	patrol->set_patrol_path( ({ "s","w","w","n","n","n","w","w","w",
				"s","s","s","e","n","e",
				5,
				check_patrol_tavern,
				"w","s","e","e","e","e","n","n","w",
				5,
				check_patrol_inn,
				"w","s" }) );
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
check_patrol_inn()
{
    setuid();
    seteuid(getuid());

    if(file_name(E(patrol)) != SCITY+"inn")
    {
	tell_room(E(patrol), QCNAME(patrol)+" leaves.\n");
	patrol->move_living("M", SCITY+"inn", 1, 1);
	tell_room(E(patrol), QCNAME(patrol)+" arrives.\n");
    }
    patrol->command("shout Cook! Bakaris wants to have lunch in his tent today!");
    return "grin";
}

void
create_sanction_room()
{
    set_short("On a street before a bridge that crosses a river of lava");
    set_extra_long("Here you stand in the eastern parts " +
      "of Sanction, to the east of houses that once were owned by " +
      "the nobles and rich merchants before the dragonarmy " +
      "occupied this city, and to the west of a river of " +
      "lava. A stone bridge crosses the river of fire to your " +
      "east into the camp of a contingent of Blue Dragonarmy " +
      "soldiers.");

    add_item(({"bridge","stone bridge"}),
      "A sturdy stone bridge crosses into the camp " +
      "of a contingent of Blue Dragonarmy soldiers " +
      "to your east.\n");
    add_item("camp",
      "An orderly camp has been set up across the bridge for " +
      "a contingent of soldiers from the Blue Dragonarmy.\n");
    add_item("houses",
      "To your west rise houses and similar structures " +
      "that were probably owned by the rich and " +
      "influential before the occupation of the city. " +
      "Now they simply stand out as being less rundown " +
      "than those buildings that stand in the expansive " +
      "slums of this city.\n");

    add_item(({"river of lava","lava","river"}),
      "To your east a river of lava flows past you " +
      "from one of the Lords of Doom to your south. " +
      "Even from this distance the heat is almost unbareable.\n");

    add_exit(SCITY + "street19","south",0);
    add_exit(SCITY + "street17","north",0);
    add_exit(SBLUE + "bridge","east",0);

    reset_room();
}

int
no_go()
{
    write("The Blue Dragonarmy encampment is off " +
      "limits by order of the Blue Lady!\n");
    return 1;
}
