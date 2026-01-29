/*
 * multi_npc
 * 
 * Stexx - June 6/95
 *
 * This object is to support large groups of npc's travelling as a single
 * object, to avoid the lag created by large teams that would otherwise
 * be required. All you do is inherit this object into a group 'npc', then
 * use add_npc to add any number of different npc's to the group.
 * The individual npc's will be cloned and moved into a staging room, where
 * they remain until the group object (which is a pseudo-npc, in that it can
 * be attacked).
 * When the group is attacked, the group object goes to the staging room,
 * and the individual npc's break away from the group to attack.
 *
 * Typical usage, a unit of 12 soldiers.
 *
 *  inherit "/d/Immortal/std/multi_npc";
 *  void  
 *  create_monster()
 *  {
 *    set_name("unit");
 *    set_pname("units");
 *    add_name("unit of soldiers");
 *    add_pname("units of soldiers");
 *    set_short("unit of soldiers");
 *    set_pshort("units of soldiers");
 *    set_multi_long("The unit is a typical unit of footsoldiers of "+
 *      "Laranate's guards. ");
 *    add_npc("/d/Immortal/std/soldier", 12);
 *
 *    create_multi();
 *  }
 */
#include "/d/Immortal/std/domain.h"
#include <composite.h>

inherit STDMONSTER;

#define STAGING_ROOM "/d/Immortal/std/staging_room"

mapping npcs;
object *npcobjs;
string multi_long;

/*
void
add_npc(string npc, int number)
{
  npcs[npc] = number;
}
 */

void
set_multi_long(string str)
{
  multi_long = str;
}

string
query_multi_long()
{
  if(!multi_long || !strlen(multi_long))
    return "This is a typical "+TO->short()+". ";
  else
    return multi_long;
}

void
create_multi()
{
object obj;
int i, j;

  for(i = 0; i < sizeof(m_indexes(npcs)); i++)
    {
    for(j = 0; j < m_values(npcs)[i]; j++)
      {
      obj = clone_object(m_indexes(npcs)[i]);
      if(!sizeof(npcobjs))
        npcobjs = (({obj}));
      else
        npcobjs += ({obj});
      obj->move(STAGING_ROOM);
      }
    }

  set_long("@@multi_long@@");
}

string
multi_long()
{
string ret;
int i, j;

  ret = query_multi_long();

  ret += "It contains ";

  ret += COMPOSITE_LIVE(npcobjs);
  ret += ".\n";

  return ret;
}
  
