inherit "/std/room";
#include "/d/Roke/common/defs.h"
#include <macros.h>
 
reset_room()
{
 
 
}
 
create_room()
{
	set_noshow_obvious(1);
 
    set_short("Cellhall");
	set_long(BSS("You are walking down a small corridor in "+
		"the cellars below the Templar Pandora's house. "+
		"The corridor is dim, and you would easily understand it "+
		"if this place was crowded with insects and such, "+
		"but strangely enough, there is no insect in sight. "+
      "The corridor leads east and west from here.\n"));

    add_prop(ROOM_I_INSIDE, 1);
 
	add_exit(CELL_D+"cellhall2","west",0);
	add_exit(CELL_D+"hallway4","east",0);
 
 
	add_item(({"door","cell door"}), BSS(
		"The door looks sturdy and it has a lock that seems "+
		"a bit rusted.\n"));

	add_item(({"doors","cell doors"}), BSS(
		"The doors looks sturdy and they each have a lock that "+
		"seems a bit rusty.\n"));

	add_item("lock", BSS(
		"The lock is of the common bolt type, with no key. Although "+
		"the bolts have rusted stuck, you might manage to bend it "+
		"loose.\n"));

	add_item("locks", BSS(
		"The locks are the common bolt lock type, no key usage, just "+
		"a bolt which you pull aside. Though the bolt seems rusted "+
		"stuck, you might manage to bend one of them loose.\n"));

 
    call_out("reset_room", 1);
 
}
init()
{
    ::init();
    add_action("do_bend","bend");
    add_action("do_pull","pull");
    add_action("do_open","open");
}

int
do_bend(string str)
{    
    if (!str)
    return 0;

	if (str != "bolt" || str != "lock")
    {
	notify_fail("Bend what?\n");
       return 0;
    }
    
	write(BSS("You try in vain to bend the bolt loose, but the rust "+
		"has made it so stuck you cannot manage to bend it loose.\n"));
	say(QCTNAME(this_player())+" tries in vain to bend open one of the locks.\n");
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
do_pull(string str)
{    
    if (!str)
    return 0;

	if (str != "bolt" || str != "bolt aside")
    {
	notify_fail("Pull what?\n");
       return 0;
    }
    
	write(BSS("You try to pull aside one of the bolts, but they are "+
		"totally stuck, you might need to bend them loose.\n"));
	say(QCTNAME(TP)+BSS(" tries to pull one of the bolts aside, but fails "+
		"miserably.\n"));
    return 1;

}
