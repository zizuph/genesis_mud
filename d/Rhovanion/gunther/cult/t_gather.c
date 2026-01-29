inherit "/d/Rhovanion/lib/room";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Rhovanion/defs.h"
#include "guild.h"

object board;

init()
{
	::init();
	add_action("drink_from_stream", "drink");
}

drink_from_stream(string str)
{	
	NF("Drink from what?");
	if(str != "from stream" && str != "from channel") return 0;
	
	write("You take a refreshing drink from the clear mountain spring water.\n");
	say(QCTNAME(TP) + " drinks some water from the stream.\n");
	return 1;
}

create_room()
{
	set_short("Gathering hall.\n");
	set_long("This is the gathering hall of the home. Here worshippers"
		+" idle around discussing cult business, techniques and whatever"
		+" they like. The lounge is tastefully decorated with a few images"
		+" of Melkor and the walls are draped with black cloth. A small"
		+" stream flows out of the mouth of some creature carved upon the"
		+" wall and continues in a small channel north. You also notice a"
		+" strange exit marked common.\n");
	
	add_item(({ "wall", "walls", "cloth" }), "The walls are entirely covered"
		+" with heavy black cloth, fuzzing out the distinctness of the room"
		+" and making you unsure of its extent. Some space has been left on one"
		+" wall however where you can see a channel with running water in it.\n");
	
	add_item(({ "images", "image" }), "The images are carried out in great"
		+" detail and depict Melkor in several key stages of His past.\n");
		
	add_item("creature", "It looks like an evil water-sprite of sorts, you"
		+" cannot quite tell.");
		
	add_item(({"stream", "channel"}), "The water seems to come from an under"
		+"ground stream and looks crystal clear. It flows through an ornamentally"
		+" carved channel set into the wall continuing north.\n");
	
	add_exit(CULT_DIR + "t_cor1",		"south",		0);
	add_exit(CULT_DIR + "t_muntr",	"west",		0);
	add_exit(CULT_DIR + "t_spltr",	"southwest",0);
	add_exit(CULT_DIR + "t_med",		"north",		0);
	add_exit(CULT_DIR + "t_post",		"northeast",0);
	add_exit(CULT_DIR + "t_shop",		"east",		0);
	add_exit(CULT_DIR + "t_common",	"common",	0);
	
	add_prop(ROOM_I_INSIDE, 1);
	add_prop(ROOM_I_LIGHT, 1);
	add_prop(OBJ_I_CONTAIN_WATER, 1);

	if(!present("board",TO))
	{
		board=clone_object("/std/board");
		board->set_board_name(CULT_DIR + "boards/private");
		board->set_num_notes(30);
		board->set_no_report(1);
		board->set_silent(0);
		board->move(TO);
	}	
}
