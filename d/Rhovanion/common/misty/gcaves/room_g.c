/* this file is to be inherited by guarded rooms in goblin caves 
 * 
 * Changed by Ged 5/4/2002
 * Added huge goblins as well
 * Chance to encounter huge goblin is 30% (massive 70%)
 */
inherit "/d/Rhovanion/common/misty/gcaves/room";
#include "/d/Rhovanion/defs.h"
#include <stdproperties.h>
#include <macros.h>

#define CAVE_DIR MISTY_DIR + "gcaves/"

object *guards;
int    ggg;

void set_guards(int i)
{
  guards = allocate(i);
  ggg = i;
}

int add_exit(string room, string dir)
{
  return ::add_exit(room,dir,"@@block_exit:"+file_name(TO)+"|"+room+"@@");
}

int block_exit(string room)
{
  int i=0;

  if(TP->query_prop(LIVE_O_LAST_ROOM) == find_object(room)) return 0;

  while((i<ggg) && 
        (!guards[i] || !present(guards[i], TO) || !TP->check_seen(guards[i])))
    i++;
  if(i<ggg)
  {
    TP->catch_msg(QCTNAME(guards[i])+" stops you from passing.\n");
    say(QCTNAME(TP)+" was stopped by "+QTNAME(guards[i])+" from passing.\n");
    return 1;
  }
  return 0;
}


void reset_room()
{
  int i;
  seteuid(getuid());
  for(i=0; i<sizeof(guards); i++)
    if(!guards[i] || !present(guards[i]))
    {
      if(random(10)<3)
        guards[i] = clone_object(NPC_DIR+"goblins/goblin_sup");
      else
       guards[i] = clone_object(NPC_DIR+"goblins/goblin_high");   
      guards[i]->add_prop(LIVE_I_SEE_DARK, 5);
      guards[i]->arm_me();
      guards[i]->move_living("M", TO);
      tell_room(TO, QCTNAME(guards[i])+" arrives attracted by the noise.\n");
    }
}
