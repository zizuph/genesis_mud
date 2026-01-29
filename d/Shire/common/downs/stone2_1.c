inherit "/d/Shire/room";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"

create_room() {
    set_short("Dark room in the downs");
    set_long("You are inside the Barrow downs.\n"
	+ "It is wet, cold and gloomy.\n"
	+ "You notice an inscription on the wall.\n");

    add_item(({"inscription", "letter"}), ("Written in large, clumsy letters\n"
        + "you discern the message:\n"
        + "Woe to you, foolhearted wanderers,\n"
        + "for you have entered the barrow downs,\n"
 	+ "And thus your destiny is sealed.\n"));
    
add_item(({"wall","walls"}), ("The walls are of moist rock.\n"
        + "There is an inscription on one side.\n"));
    	
	add_exit(DOWNS_DIR + "pit", "south");
	add_exit(DOWNS_DIR + "stone2_2", "north");
    add_prop(ROOM_I_LIGHT,0);
    add_prop(ROOM_I_INSIDE,1);
    reset_room();	
}

init()
{
	::init();
	add_action("do_read", "read");
}

int
do_read(string str)
{
	if(str == "inscription" || str == "letter")
	{
	  write("Written in large, clumsy letters\n"
        + "you discern the message:\n"
        + "Woe to you, foolhearted wanderers,\n"
        + "for you have entered the barrow downs,\n"
 	    + "And thus your destiny is sealed.\n");
	  return 1;
	}
	else
	{
	  notify_fail("Read what? The inscription maybe?\n");
	  return 0;
	}
}

reset_room() {
	object wight;
	int i;
	if (!present ("wight")){
	for (i=1; i<=2; i++ ) {
        wight = clone_object(DOWNS_DIR + "npc/g_wight1");
        wight->move(this_object());
    tell_room(TO, "A grey barrow wight pushes up through the dirt.\n");
	      };
        };
}



