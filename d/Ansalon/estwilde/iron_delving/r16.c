#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <cmdparse.h>
#include <macros.h>
#include <stdproperties.h>

inherit DWARF_OUT;
object d1, d2;

#define AUDIENCE_GRANTED "_elder_granted_audience"

void
reset_dwarf_room()
{
    if(!objectp(d1))
    {
	d1 = clone_object(LIVING + "dwarf_guard02");
	d1->arm_me();
	d1->move(TO);
    }
    if(!objectp(d2))
    {
	d2 = clone_object(LIVING + "dwarf_guard");
	d2->arm_me();
	d2->move(TO);
    }
}

void
create_dwarf_room()
{
    setuid();
    seteuid(getuid());

    set_short("@@short_descr");
    set_long("@@long_descr");

    add_item(({"entrance","great stone hall","stone hall",
	"hall","hall of the thane"}),
      "The Hall of the Thane is the audience chamber used " +
      "by the leader of the Hill Dwarves. It is rather large, " +
      "and as would be expected from dwarves, extremely sturdy " +
      "and well crafted.\n");
    add_item(({"path","cobbled path"}),
      "A cobbled path leads away to your northwest.\n");
    add_item(({"dwarven community","iron delving"}),
      "You stand in the dwarven community of Iron Delving, a " +
      "place where the Clans of the Neidar dwarves gather.\n");

    add_exit(GUILD_NEIDAR_ROOM_PATH + "hall1","southeast","@@enter_hall");
    add_exit(IRON + "r11","northwest",0);

    reset_dwarf_room();

    clone_object("/d/Genesis/ateam/aoe/obj/neidar_tree")->move(this_object(), 1);
    clone_object("/d/Genesis/ateam/aoe/obj/neidar_tree_2008")->move(this_object(), 1);
}

int
enter_hall()
{
    if(objectp(d1) || objectp(d2))
    {
	if(TP->query_race() == "dwarf")
	{
	    return 0;
	}
	if(TP->query_prop(AUDIENCE_GRANTED))
	{
	    write("The dwarven guards allow you passage.\n");
	    say(QCTNAME(TP)+ " is allowed passage into the "+
	      "Hall of the Thane by the dwarven guards.\n");
	    return 0;
	}
	write("The dwarven guards stop you from entering.\n");
	say(QCTNAME(TP)+ " is stopped from entering by the guards.\n");
	return 1;
	d1->command("say A clan member must 'grant access' to " +
	  "you if you want to enter.");
	return 1;
    }
    return 0;
}

string
short_descr()
{
    return "Before the Hall of the Thane in Iron Delving";
}

string
long_descr()
{
    return "You stand before the entrance to a great " +
    "stone hall, the audience hall for the Thane of the " +
    "Neidar. A cobbled path leads away from the hall towards " +
    "the middle of the dwarven community of Iron Delving to " +
    "your northwest.\n";
}

int
audience(string str)
{
    object ob, *obj;

    if(!str)
    {
	notify_fail("Grant an audience to who?\n");
	return 0;
    }

    if(TP->test_bit("Ansalon",3,4) &&
      TP->test_bit("Ansalon",3,3))
    {
	notify_fail("Ha! A disgraced dwarf has no right to grant " +
	  "audiences!\n");
	return 0;
    }

    if(TP->test_bit("Ansalon",3,4) ||
      TP->test_bit("Ansalon",3,3))
    {
	if(strlen(str))
	{
	    if(!sizeof(obj = PARSE_THIS(str, "[audience] [to] %l")))
	    {
		notify_fail("Grant audience to who?\n");
		return 0;
	    }
	    ob = obj[0];
	}

	TP->catch_msg("You grant " +QTNAME(ob)+
	  " an audience to the Hall of the Thane.\n");
	TP->tell_watcher(QCTNAME(TP)+ " grants " +QTNAME(ob)+
	  " an audience into the Hall of the Thane.\n", ob);
	ob->catch_msg(QCTNAME(TP)+ " grants you an audience into " +
	  "the Hall of the Thane.\n");
	ob->add_prop(AUDIENCE_GRANTED, 1);

	return 1;
    }

    return 0;

}

void
init()
{
    ::init();
    add_action(audience,"grant");
}
