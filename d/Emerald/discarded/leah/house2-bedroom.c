inherit "/std/room";

#include "/d/Emerald/defs.h"

int query_sickness();
int set_sickness(int a);
int do_open(string str);
int do_close(string str);
int set_window(int i);
int query_window();
string do_enter();
string small_bed_desc();
string elf_child_desc();

object outside_room;

int sickness; /* 0 = sick kid, 1 = healed */
int window; /* 1 = open, 0 = closed (default) */

void create_room()
{
    if(!LOAD_ERR(LEAH_DIR + "house2-outside"))
	 outside_room = find_object(LEAH_DIR + "house2-outside");
    set_short("A Small Bedroom");
    set_long("   You are in a bedroom, small for elf standards. "+
	"On the west side of the room is a medium sized bed, and "+
	"on the east side, a much smaller one. A brightly colored "+
	"rug covers the floor between the beds. A nightstand is "+
	"against the south wall.\n\n");

    add_item(({"nightstand", "night stand"}), "The nightstand is "+
      "bare except for a thin cloth that covers it's wood finish.\n");

    add_item(({"bed", "beds"}), "The beds are just that...beds. You "+
	"might want to look at the west bed or the east bed.\n");

    add_item(({"east bed", "eastern bed", "small sized bed",
		"small bed", "smaller bed" }),
	VBFC_ME("small_bed_desc"));

    add_item(({"child", "sick child", "sickly child", "elf child",
		"sick elf child", "sick elf", "sickly elf",
		 "sickly elf child"}), VBFC_ME("elf_child_desc"));

    add_item(({"west bed", "western bed", "medium sized bed",
		"medium bed", "larger bed" }),
	"The medium sized bed is up against the west wall. It seems "+
	"made, and doesn't look like it's been slept in for a while.\n");

    add_item(({"rug", "brightly colored rug", "colored rug"}),
	"The rug covers the floor, adding a little life to the otherwise "+
	"drabness of the room.\n");

    add_item(({"cloth", "thin cloth"}), "The cloth covers the nightstand, "+
	"protecting it's wood finish. It rustles a slight bit in the "+
	"breeze coming from the window.\n");

    add_item("window", VBFC_ME("window_desc"));

    add_cmd_item("window", "enter", VBFC_ME("do_enter"));

    add_exit(VILLAGE_DIR + "house2-main", "north");

    window = 0;
}

string small_bed_desc()
{
	if(sickness)
	  {
		return "The small bed lies unmade and empty.\n";
	  }
	return "The small bed has a sickly elf child laying asleep in it.\n";
}

string elf_child_desc()
{
	if(sickness)
	  {
		return "The child who was in the bed seems gone.\n";
	  }
	return "The elf child is laying in bed in a restless sleep. "+
		"Beads of sweat roll down his clammy cheeks.\n";
}

string window_desc()
{
	if(window)
	  {
		return "The window is openened, letting a nice warm breeze "+
			"fill the room.\n";
	  }
	return "The window is opened about a fingerswidth, letting a "+
		"hint of a warm breeze in.\n";
}

int query_sickness()
{
	return sickness;
}

int set_sickness(int a)
{
	sickness = a;
}

int do_open(string str)
{
	NF("Open what?\n");
	if(str != "window")
		return 0;
	NF("But the window is already opened!\n");
	if(window)
		return 0;
	TP->catch_msg("You slide the window open and feel the warm "+
		"breeze buffet against your face.\n");
	set_window(1);
	return 1;	
}

query_window()
{
	return window;
}

set_window(int i)
{
	window = i;
	return 1;
}

int do_close(string str)
{
	NF("Close what?\n");
	if(str != "window")
		return 0;
	NF("But the window is already closed! You can't seem to get it "+
		"the last fingerwidth closed.\n");
	if(!window)
		return 0;
	NF("The window seems stuck open!\n");
	if(!outside_room->set_window(0))
		return 0;
	tell_room(outside_room, "The windows slides shut!\n");
	TP->catch_msg("You slide the window closed and feel the warm "+
		"breeze stop.\n");
	window = 0;
	return 1;	
}

string do_enter()
{
	NF("But the window is closed! You can't fit through that small "+
		"of an opening!\n");
	if(!window)
		return 0;
	TP->catch_msg("You climb through the window.\n");
	set_dircmd("window");
	TP->move_living("through the window", LEAH_DIR + "house2-outside",
		0, 0);
	return "";	
}

init()
{
	add_action("do_open", "open");
	add_action("do_close", "close");
	::init();
}
