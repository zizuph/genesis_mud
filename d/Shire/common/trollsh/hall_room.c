/*
 * Cleaned up and updated by Finwe, August 2001
 */

inherit "/d/Shire/room";
#include "../defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <language.h>

#define MAX_TROLLS 2
int num_trolls, alarm_id;
object leader, *trolls = ({});

void
make_trolls();

void
reset_room()
{
  make_trolls();
}

create_room()
{
    set_short("A large hall");
    set_long("This is a large natural cave beneath the " +
        "Trollshaws. On the western wall is a cage. The walls " +
        "are covered with stained blood and gouged. Scattered " +
        "about the cage and the floor are heaps of bones. The " +
        "smell in here is so foul that it can only come from " +
        "trolls. @@is_troll@@\n");
	
	add_item(({"hall-room","hall", "hall room", "room"}),
        "This is a a large natural cave beneath the Trollshaws. " +
        "The walls are hard yet dank and show signs of marks, as " +
        "if it the hall enlarged by troll slaves.\n");
	add_item("cage",
	     "The cage is roughly box shaped and strong looking. It " +
         "is made from thick iron bars and a strong, sturdy door. " +
         "The floor is littered with gnawed and broken bones. " +
         "They are probably the remains of prisoners trolls " +
         "caught and later ate. \n");
    add_item(({"shattered bones", "bones", "gnawed bones"}),
        "The bones are the remains of prisoners the trolls caught " +
        "and later ate. Some of the bones have teeth marks where " +
        "trolls gnawed on them while others are shattered from " +
        "when they were broken. Blood, sinews, and flesh can " +
        "still be seen on some bones.\n");
    add_item(({"blood", "stained blood"}),
        "Some of blood is fresh and spread about the room and on " +
        "some bones. It has gathered in small red pools, some " +
        "dried and others fresh.\n");
    add_item("flesh",
        "Chunks of flesh still lie attached to some of the bones. " +
        "It leaves a rancid stench in the room.\n");
    add_item(({"marks", "gouges"}),
        "The marks and gouges are in the walls, probably from " +
        "tools that enlarged the hall.\n");
//    add_item("sinews",
        
	
	add_prop(ROOM_I_INSIDE, 1);
	add_prop(ROOM_I_LIGHT, 0);
	add_prop(ROOM_I_NO_CLEANUP, 1);
	
	add_exit(TROLLSH_DIR + "guardroom2", "north", 0, 2);
	add_exit(TROLLSH_DIR + "guardroom1", "south", 0, 1);
	add_exit(TROLLSH_DIR + "tunnel5", "east", 0, 1);
   add_exit(TROLLSH_DIR + "w_hall","west",0,1);
	
    reset_room();
}

init()
{
    ::init();
    add_action("do_enter","enter");
}

do_enter(string arg)
{
    if (arg == "cage")
    {	
    	write("You enter the cage.\n");
    	say(QCTNAME(TP) + " enters the cage.\n");
    	TP->move_living("M", TROLLSH_DIR + "cage", 1);
    	return 1;
    }
    else
    notify_fail("Enter what?\n");
    return 0;
}

void
make_trolls()
{
    int i;
    
    if(!leader)
    {
        leader = clone_object(TROLLSH_DIR + "npc/guard_troll");
        leader->move(TO);
        tell_room(TO,CAP(LANG_ADDART(leader->query_nonmet_name())) +
           " runs screaming and charging out from the guard room.\n");
    }
    
    if(!sizeof(trolls))
        trolls = allocate(MAX_TROLLS);
    for(i = 0; i < MAX_TROLLS; i++)
    if(!trolls[i])
    {
      	trolls[i] = clone_object(TROLLSH_DIR + "npc/guard_troll");
      	leader->team_join(trolls[i]);
      	trolls[i]->move(TO);
      	tell_room(TO,CAP(LANG_ADDART(trolls[i]->query_nonmet_name()))+
      	    " suddenly comes running in from the guard room!\n");
    }
    else
        if(trolls[i]->query_leader() !=leader)
        leader->team_join(trolls[i]);
}

string
is_troll()
{
    if (present("troll",TO))
    {
          return "There are trolls here, guarding the Hall from " +
          "looters and trespassers.\n";
    }
    else 
        return "The place is empty now, but that probably won't " +
        "last for long.\n";
    
}
