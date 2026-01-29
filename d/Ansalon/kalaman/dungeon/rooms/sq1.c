#include "local.h"
/*
 * The Dungeon Guard Room
 *
 * Lunatari 2008-03-05
 * Changed to add_npc isntead of my own cloning.
 */
inherit DUNGEON_IN;

create_dungeon_room()
{
   set_dungeon_type(ROOM_GUARD2);
   ::create_dungeon_room();

   add_exit("dc9", "east");

   add_item(({"table","tables"}), "There are two tables in " +
     "this room. A long table and small table.\n");
   add_item(({"chair","chairs"}), "Regular wooden chairs with " +
     "four legs. Nothing special about them.\n");
   add_item("long table", "The long table contains a few " +
     "forks, spoons, plates and some mugs. It looks like a " +
     "regular dining table.\n");
   add_item("small table", "The small table has a few steelcups, a " +
     "plate and some dices on it, nothing more.\n");
   add_item(({"plate", "plates"}), "These are regular wooden " +
     "plates that is used for hold food. A few plates are still " +
     "dirty from their last meal.\n");

   add_npc(DNPC + "dungeon_guard", 6);
}

mixed
filter_guards(object ob)
{
  if ( ob->query_dungeon_guard() ) return 1;
}

int
query_sleeping_guards()
{
  object *guards = all_inventory(TO);
  int    i, sleeping;

  guards = filter(guards, filter_guards);

  sleeping = 0;

  for ( i = 0; i < sizeof(guards); i++ )
  {
    if ( guards[i]->query_sleeping() ) sleeping++; 
  }
 
  return sleeping;
}

void
wake_guards(object player)
{
  object *guards = all_inventory(TO);
  int    i, surrender, door;

  guards = filter(guards, filter_guards);

  for ( i = 0; i < sizeof(guards); i++ )
  {
    guards[i]->set_awake(); 
    if ( !surrender ) 
    {
      surrender = 1;
      guards[i]->surrender_attack(player);   
    }
    else if ( !door )
    {
      guards[i]->command("close door");
      guards[i]->command("assist");
    }
    else
    {
      guards[i]->command("assist");
    }
  }
}

void
sleep_guards()
{
  object *guards = all_inventory(TO);
  int    i;

  guards = filter(guards, filter_guards);

  for ( i = 0; i < sizeof(guards); i++ )
  {
    guards[i]->set_sleeping(); 
  }
}

/* Enter Inventory, this is to make the guards attack.
 */
void
enter_inv(object ob, object from)
{
 ::enter_inv(ob, from);

 
 if ( TP->query_prop(PLAYER_PEEKED) && TO->query_sleeping_guards() )
 {
   write("You silent step through the doorway, careful not to " +
    "wake the sleeping guards.\n");
 }
 else if ( TO->query_sleeping_guards() )
 {
   set_alarm(1.0, 0.0, &wake_guards(TP));
 }

 write("You step through the doorway and into the guardroom.\n");
}

/* Leave Inventory, here we remove the surrender object.
 */
void
leave_inv(object ob, object to)
{
 object *items;

 ::leave_inv(ob, to);

 if (ob->query_npc()) return;

 items = all_inventory(ob);

 foreach (object item: items)
 {
   if(item->query_name() == "_i_surrender_command_") 
   {
     item->remove_object();
   }
 }
}

