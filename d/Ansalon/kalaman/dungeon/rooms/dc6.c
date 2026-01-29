/*
 * The Room just North of the Guard Room.
 * 
 * Here is the door and keyhole you have to
 * examine and figure out how to get unseen
 * into the guardroom, if you enter when they
 * are awake, you will be attacked and thrown
 * into the cells.
 *
 * TODO: Fix a regular door and just keep the 
 * peeking code.
 *
 * You will be able to wake them up.
 */
#include "local.h"

inherit DUNGEON_IN;

#define GROOM1 DROOM+"gr1"

create_dungeon_room()
{
   set_dungeon_type(ROOM_MAIN);
   ::create_dungeon_room();

   add_exit("dc7", "west");
   add_exit("dc5", "east");

   add_item("keyhole", "The keyhole is actually quite big and " +
     "perhaps one could peek through it to get a view of the " +
     "other side of the door.\n");
   add_steel_door("steeldoor1",({ "south", "s" }), DROOM+"gr1", "south", CELL_KEY2);
}

void
init()
{
  ::init();

  add_action("door_peek", "peek");
//  add_action("door_open", "open");
//  add_action("door_close", "close");
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
       text += "The door is closed.";
     break;
     case 1:
       text += "The door is open.";
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
    return 0;
  }
 
  write ("The door leading south is closed.\n");
  return 1;
}

int
door_check_show()
{
  if(DMASTER->query_status(S_DDOOR1)) return 0;
 
  return 1;
}

mixed
filter_guards(object ob)
{
  if ( ob->query_dungeon_guard() ) return 1;
}

int
door_peek(string str)
{
  notify_fail("Peek where? Through keyhole?\n");

  if (!str) return 0;

  int *time, i;
  time = CLOCK->query_time();

  if (LOAD_ERR(GROOM1))
  {
    return 0;
  }

  if (parse_command(str, ({ }), "'through' [the] 'keyhole'") )
  {
    object *oblist = all_inventory(find_object(GROOM1));
    oblist = filter(oblist, filter_guards);
    string view = "You peek through the keyhole.\n";
    view   += find_object(DUNGEON + "gr1")->long();

    write("Time is: " + time[3] + ":" + time[4] + "\n");
    for (i = 0; i < sizeof(oblist); i++)
    {
      if ( time[3] > 6 && time[3] < 22 )
      {
         oblist[i]->set_awake();
         TP->remove_prop(PLAYER_PEEKED);
      }
      else
      {
         oblist[i]->set_sleeping();
         TP->add_prop(PLAYER_PEEKED, 1);
      }
    }

    if ( sizeof(oblist) )
    {
      view += capitalize(COMPOSITE_LIVE(oblist)) + ".";
    }

    write( view + "\n");
    return 1;
  }

   return 0;
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
      tell_room(DUNGEON + "gr1", "The door is suddenly " +
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
