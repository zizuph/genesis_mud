// rooms can inherit this file to get standard npc support
inherit  "/d/Khalakhor/std/room";
#include <macros.h>
#include "defs.h"
#define  MAX_NPCS 5
object   *npc   = allocate(MAX_NPCS);
string   rpath  = ROOM;
string   arrmsg = "arrives";
string*  name   = ({});
 
void make_npc(int i)
{
   if (objectp(npc[i])) return;
   npc[i] = clone_object(NPC+name[i]);
   npc[i]->equip_me();
   npc[i]->command("wield all");
   npc[i]->command("wear all");
   npc[i]->set_monster_home(MASTER);
   npc[i]->set_restrain_path(rpath);
   npc[i]->move(TO);
   tell_room(TO,QCNAME(npc[i])+" "+arrmsg+".\n");
}
 
void make_npcs()
{
   int i;
   for (i=0; i<sizeof(name); i++)
      make_npc(i);
}
 
void create_khalakhor_room()
{
}

varargs void set_all_random_move(int s, int first=0)
{
   int i;
   for (i=first; i<MAX_NPCS; i++)
      if (objectp(npc[i])) (npc[i])->set_random_move(s);
}
