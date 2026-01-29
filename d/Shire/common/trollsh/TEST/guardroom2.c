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
    set_short("A guard room");
   set_long("This guardroom beneath the Trollshaws is filled with bones of "+
   "unfortunate creatures who fell victim to the residents of this area. "+
   "There is only one way out, back the way you came in.\n");
	
   add_item(({"bones","victims","creatures"}),
   "The bones look as if they were gnawed upon by large sharp teeth.\n");
	
	add_prop(ROOM_I_INSIDE, 1);
	add_prop(ROOM_I_LIGHT, 0);
	add_prop(ROOM_I_NO_CLEANUP, 1);
	
	add_exit(TROLLSH_DIR + "hall_room", "south", 0, 2);
	
    reset_room();
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
