inherit "/std/room";
#include "/d/Roke/common/defs.h"
#include <macros.h>
 
reset_room()
{
 
 
}
 
create_room()
{
	set_noshow_obvious(1);
 
    set_short("Cell");
	set_long(BSS("You are in a small, dirty, poor cell in the dungeons "+
		"below the city level. There is a small bed here, which "+
		"probably is meant as yours for your 'visit' here.\n")+
		"There is a closed door leading east here.\n");

    add_prop(ROOM_I_INSIDE, 1);
 
	add_exit(TUNN_D+"rat_hole4", "enter", "@@enter_check");
 
 
    add_item(({"rathole", "hole"}), BSS("It looks just big enough for you to "+
				       "enter it\n"));

	add_item(({"bed","small bed"}),BSS("It looks dirty and uncomfortable "+
		"but the meaning is probably for you to 'lie down' on it.\n"));

    add_item(({"cell door", "door"}), BSS("It is a sturdy steeldoor, locked "+
					 "from the outside.\n"));
 
    call_out("reset_room", 1);
	call_out("crawling_rat", 20 + random(20));
 
}
enter_check(){

     string str;
     str = query_dircmd();
     if (str == "rathole" || str == "hole")
	 return 0;
     write("You can't enter that!\n");
     return 2;
 }

init()
{
    ::init();
    add_action("do_look","look");
    add_action("do_lie","lie");
    add_action("do_open","open");
}

int
do_look(string str)
{    
    if (!str)
    return 0;

    if (str != "under bed")
    {
	notify_fail("Where do you want to look ?\n");
       return 0;
    }
    
	write(BSS("You duck down, and look under the bed. You can see a small "+
		"rathole in the wall, just so big you might manage to squeeze "+
		"through.\n"));
	say(QCTNAME(this_player())+" ducks down, and looks under the bed.\n");
    return 1;

}

int
do_open(string str)
{    
    if (!str)
    return 0;

    if (str != "door")
    {
	notify_fail("Open what ?\n");
       return 0;
    }
    
	write("You try in vain to open the locked door.\n");
	say(QCTNAME(this_player())+" tries in vain to open the locked door.\n");
    return 1;

}


int
do_lie(string str)
{    
    if (!str)
    return 0;

    if (str != "down")
    {
	notify_fail("What ?\n");
       return 0;
    }
    
	write(BSS("You lie down on the uncomfortable bed, and as you lie down, "+
		"you notice a small spider crawling on the sheets, and quickly "+
		"rises again.\n"));
	say(QCTNAME(this_player())+BSS(" lies himself gently down on the bed "+
		"but after a few seconds, he pops back up with a scared "+
		"grin on his face.\n"));
    return 1;

}

void crawling_rat()	{

	tell_room(this_object(), BSS(
		"You notice a rat coming crawling out from under the bed, then "+
		"it notices you, stops, then runs back under the bed.\n"));
	call_out("crawling_rat", 50 + random(50));
}

