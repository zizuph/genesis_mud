/*  -*- LPC -*-  */
//
// Revision history:
//
// Sir Rogon, 23rd of Mars, 1995:
//  * Added support for parse_command() and notify_fail().
                       
inherit "/d/Shire/room";
#include "/d/Shire/common/defs.h"

#include "defs.h"
#include "/sys/stdproperties.h"
#include "/sys/ss_types.h"
#include "/sys/macros.h"


create_room() {
    set_short("A small cottage");
    set_long("You stand outside a small cottage just off the Eastroad. "+
	     "It looks recently painted and you suppose that it must have "+
	     "a new occupant. Bushes and trees line your way back south, but "+
	     "in the other directions, you see nothing but green grass and "+
	     "bushes.\n");
    
    add_item(({"cottage","paint"}),
	     "The cottage is made of some sort of earthen material, all "+
	     "except for the door, which is round and wooden. The baked "+
	     "earthen material seems to have a fresh coat of whitewash, "+
	     "making it look pretty spiffy.\n");
    
    add_item(({"bushes","bush","trees","tree"}),
	     "The bushes and trees have grown so thickly together "+
	     "you have no way of telling what kind they are.\n");
    
    add_item(({"door"}), "The door is circular like a hobbit's should be, " +
	     "and even has a brass-looking doorknocker on it.\n");
    add_item(({"door knocker","doorknocker"}),
	     "The doorknocker is a plain brass maple leaf, " +
	     "attached to the door by a nail.\n");
    
    add_prop(ROOM_I_INSIDE, 0);    
    add_exit(STAND_DIR + "er4", "south",0);    
}

init()
{
    ::init();
    add_action("do_knock","knock");
}

/*
 * knock doorknocker? Too odd syntax.
 * Changed to use parse_command() by Sir Rogon. 
 * Also note that we must use notify_fail()
 * so that we do not disable a normal "knock"
 * command.
 */
int
do_knock(string str)
{
    notify_fail("Knock what?\n");

    if (!strlen(str))
	return 0; 

    if (!parse_command(str, ({}), "[on] [at] [the] [door] [with] [using] [the] 'doorknocker'")) 
    {
	if (parse_command(str, ({}), "[on] [at] [the] 'door'")) {
	    write("You knock " + str + " but nothing happens.\n");
	    return 1;
	}
	else
	    return 0;
    }
    
    write("You knock " + str + ", and walk right in.\n");
    say(QCTNAME(TP) + " walks into the cottage.\n");
    TP->move_living("M","/d/Shire/common/hobbiton/in_house",1);
    return 1;
}
