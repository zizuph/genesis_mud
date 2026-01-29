/*
 * The Dungeon Guard Room
 *
 * Quest: 
 *
 * The player will have to check through the keyhole of the door
 * so that the Guards are sleeping, if they are not sleeping then
 * they will attack anyone who enters and try to arrest the player.
 *
 * TODO: Fix a regular door instead of my special.
 *
 * Lunatari 2008-03-05
 * Changed to add_npc isntead of my own cloning.
 */
#include "local.h"
inherit DUNGEON_IN;

#define GUARDS_AWAKE 0
#define GUARDS_SLEEP 1

int gSleeping;

string query_door_desc();
int door_check_open();
int door_check_show();

create_dungeon_room()
{
  set_dungeon_type(ROOM_GUARD2);
  ::create_dungeon_room();

  add_item(({"table","tables"}), "There are three tables in " +
      "this room. A long table, small table and a round table.\n");
  add_item(({"chair","chairs"}), "Regular wooden chairs with " +
      "four legs. They are placed around the long dining table " +
      "in the middle of the room. Nothing special about them.\n");
  add_item("long table", "The long table contains a few " +
      "forks, spoons, plates and some mugs. It looks like a " +
      "regular dining table. It stands in the middle of the room.\n");
  add_item("small table", "The small table has a few steelcups, a " +
      "plate and some dices on it, nothing more.\n");
  add_item("round table", "Examining the route table you see a large leather " +
      "book, a steel cup, a small purse, a larger cup, a dirty steel " +
      "plate, a small wooden plate, a steel bucket, a fork, another fork, " +
      "a large spoon and much much more. This table seems to hold almost " +
      "everything and anything the guards wanna stow away for a while. "+
      "Under the table you also spot a small wooden chest.\n");
  add_item(({"chest", "small chest", "wooden chest", "small wodden chest"}),
      "This steel reinforced wooden chest seems to hold quite alot of " +
      "things. From small knives and some belt buckets to just about " +
      "anything a guard owns; pouches, shirts, shoes, gloves well there " +
      "is no end to the amount of items stored here.\n");
  add_item(({"plate", "plates"}), "These are regular wooden " +
      "plates that is used for hold food. A few plates are still " +
      "dirty from their last meal.\n");
  add_item(({"book", "large book", "large leather book", "leather book"}), 
      "It is a ledgar over all the prisoners that are contained in here.\n");

  add_search(({"round table", "small wooden chest", "chest" , "wooden chest" }),
     20,  "search_for_dungeon_key", 2);

  add_steel_door("steeldoor1",({ "north", "n" }), DROOM+"dc6", "north", CELL_KEY2);

  if(!KMASTER->query_status(S_DSLEEP))
  {
    add_npc(DNPC + "dungeon_guard", 6);
  }
}

void
init()
{
  ::init();

  add_action("door_open", "open");
  add_action("door_close", "close");
}

mixed
filter_key(object ob)
{
}

mixed
search_for_dungeon_key(object player, string arg)
{
  object key, *items;

  if (!TO->query_sleeping_guards()) 
  {
    return "You feel very uncomfortable about searching anything " +
      "with the guards around.\n";
  }

  if (objectp(key = clone_object(DOBJ + "dungeon_key2")))
  {
    key->move(player,1);
    return "You notice that a key seems to have been left here. " +
     "It must be one of the guards that have not been to careful " +
     "when dispatching one of his lesser valuable items.\nYou " +
     "quickly pick up the key.\n";
  }

  return "You find a nothing!\n";
}

int
query_sleeping_guards()
{
  object *guards = all_inventory(TO);
  int    i, sleeping;

  sleeping = 0;

  for ( i = 0; i < sizeof(guards); i++ )
  {
    if ( guards[i]->query_sleeping() ) sleeping++; 
  }
 
  return sleeping;
}

mixed
filter_guards(object ob)
{
  if ( ob->query_dungeon_guard() ) return 1;
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

 if ( ob->query_dungeon_guard() )
 {
   ob->set_stats(({ 220, 245, 245, 70, 70, 245 }));
 }
 else
 {
   if ( ob->query_prop(PLAYER_PEEKED) && TO->query_sleeping_guards() )
   {
     write("You silent step through the doorway, careful not to " +
      "wake the sleeping guards.\n");
   }
   else if ( TO->query_sleeping_guards() )
   {
     set_alarm(1.0, 0.0, &wake_guards(ob));
   }
 }
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

string
query_door_desc()
{
   string text = "This is a massive door, the frame is " +
     "made out of massive oak and reinforced with steel " +
     "around the whole frame to make it even sturdier. " +
     "A solid steel handle and keyhole has been effectively " +
     "inserted into the wood. ";

   switch(DMASTER->query_status(S_DDOOR1))
   {
     case 0:
       text += "The massive door closed.";
     break;
     case 1:
       text += "The massive door is wide open.";
     break;
     default:
       text += "The door is neither closed or open.";
   }

   text += "\n";

   return text;
}

int
door_check_open()
{
  if(DMASTER->query_status(S_DDOOR1))
  {
    write("You walk through the doorway.\n");
    return 0;
  }

  write ("The door is closed.\n");
  return 1;
}

int
door_check_show()
{
  if(DMASTER->query_status(S_DDOOR1)) return 0;

  return 1;
}

int
door_open(string str)
{
  notify_fail("Open what?\n");

  if (!str) return 0;

  if ( parse_command(str, ({ }), "[the] [massive] 'door'") )
  {
    if ( DMASTER->query_status(S_DDOOR1) )
    {
      write("The massive door is not closed.\n");
    }
    else
    {
      DMASTER->set_status(S_DDOOR1, 1);
      write ("You open the massive door.\n");
      tell_room(ENV(TP), QCTNAME(TP)+ " opens the massive " +
        "door.\n", TP);
      tell_room(DUNGEON + "dc6", "The door is suddenly " +
        "opened from the other side.\n", TP);
    }
    return 1;
  }
}

int
door_close(string str)
{
  notify_fail("Close what?\n");

  if (!str) return 0;

  if ( parse_command(str, ({ }), "[the] [massive] 'door'") )
  {
    if ( !DMASTER->query_status(S_DDOOR1) )
    {
      write("The massive door is not open.\n");
    }
    else
    {
      DMASTER->set_status(S_DDOOR1, 0);
      write ("You close the massive door.\n");
      tell_room(ENV(TP), QCTNAME(TP)+ " closes the massive " +
        "door.\n", TP);
      tell_room(DUNGEON + "dc6", "The door is suddenly " +
        "closed from the other side.\n", TP);
    }
    return 1;
  }
}
 
