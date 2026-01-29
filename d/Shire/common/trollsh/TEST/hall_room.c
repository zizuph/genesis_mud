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
    set_long("You have entered a large hall-room inside the tunnels. A well "
    	    +"hidden place this is, perhaps never visited by a living man. "
    	    +"On the western wall a cage can be seen, with thick iron bars and "
    	    +"a door which look strong and sturdy. There are several "
    	    +"doors leading out of here. The walls are covered with stained blood, "
    	    +"and heaps of bones lay on the floor, scattered around. The smell in here "
    	    +"is so foul that it can only come from one thing, Trolls!! @@is_troll@@");
	
	add_item(({"hall-room","hall", "hall room", "room"}),
	     "You are inside a large, natural cave under the shaws. The walls are hard "
	     +"and not soft as in the tunnels further back.\n");
	add_item("cage",
	     "The cage is roughly shaped, an extremely strong cage. This is not something "
	     +"that has been created by humans. The cage is filled with teared bones after "
	     +"some poor creature, that has been captured by the evil trolls here. Perhaps "
	     +"some dwarves, since trolls are fond of cooking dwarves for dinner.\n");
	
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
           " runs screaming and waving out from the guard room.\n");
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
      	    " suddenly comes running from the guards room!\n");
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
          return "There are trolls here, obviously standing on guards duty, "
                 +"watching this place from folks like you!\n";
    }
    else 
        return "The place looks empty right now, but you better leave before someone arrives!\n";
    
}
