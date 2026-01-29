/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * jail_cell.c
 *
 * A generic jail cell.
 */

#include "/d/Terel/include/Terel.h"

inherit JAIL_DIR + "prison_room";

int locked;



/*
 * Function name: init
 * Description:   Add the 'command items' of this object. 
 */
public void
init()
{
    ::init();
    add_action("do_dig", "dig");
    add_action("try_open", "open");
    add_action("try_open", "unlock");
    add_action("do_shout", "shout");    
}

public int
do_dig(string str)
{
    /*
     * check for digging utensil.
     */

    write("dig not implmented yet.\n");
    return 1;
}

public int
try_open(string str)
{
    if (member_array(str, ({"door", "gate", "lock", "padlock"})) == 1) {
	NF(query_verb() + " what?\n");
	return 0;
    }
    
    if (query_locked()) {
	write("It's locked from the outside!\n");
	return 1;
    }

    write("It's already open and unlocked.\n");
    return 1;
}

public int
query_locked()
{
    return locked;
}

public void
set_locked(int val)
{
    locked = val;
}
	   
public void
create_room()
{
    ::create_room();
    locked = 0;
    set_short("A jail cell in the Calathin city jail");
    set_long("The walls and cieling of this small cell are " +
	     "rough hewn granite, darkened in places.  The earthen floor " +
	     "is slightly damp.  In one corner sits a thin mattress " +
	     "in the other corner is a hole.  Strong bars come down from " +
	     "cieling and penetrate through the ground.  A gatelike door " +
	     "is set into the bars.\n");

    add_item(({"bar", "bars"}), "They are made of high tinsel steel.\n");
    
    add_item(({"floor", "earthen floor"}), "The ground is damp in some " +
	      "places forming a slight layer of mud.  In other places " +
	      "it is dry and cracked.\n");
    
    add_item(({"gate", "door"}), "@@gate_desc");

    add_item(({"wall", "walls", "cieling"}), "The granite of the walls " +
               "and cieling is hard, and has becomed blackedned over the " +
               "years.  It looks as if there may have been fire in here " +
               "some time ago.\n");
    
    add_item(({"mattress", "thin mattress", "bed"}), "It is lumpy in places " +
             "and the dingy covering ha worn thin in places, revealing " +
             "the stuffing.\n");

    add_item("hole", "Closer inspection reveals that it's a shit hole.  " +
	     "It smells awful.  Small bugs and flies can be seen in " +
	     "and around it.\n");

    INSIDE;
    
    add_prop(ROOM_I_NO_TELEPORT, 1);

    
}

public string
gate_desc()
{
    
    string desc = "The gate wings outward, as the hinges are on the other " +
	"side.  ";

    if (query_locked()) 
	return desc + "The door is securely locked with a large padlock.\n";

    return desc + "The door is ajar.\n";
}

	
