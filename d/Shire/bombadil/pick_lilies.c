/*
 * pick lilies routine for lily quest
 * inherit this file into the river file to activate the routines.
 * In the rooms that inherit this file, include these two routines:


init()
{
    add_action("pick_lily", "pick");
    ::init();
}

void reset_shire_room()
{
    //add_stuff();
    lily_counter = 0;
}

 * The first routine enables players to pick lilies, the second 
 * resets the room
 * -- Finwe, January 2002
 */

#include "local.h"
#include "/d/Shire/sys/defs.h"

#define LILY        "lily" 
#define MAX_LILY    3

int alarm_id, 
    lily, 
    lily_counter = 0;

int
pick_lily(string str)
{
//    int ran_lily;
  string what_lily;
  object picked_lily;

//    ran_lily = random(sizeof(LILY));
  what_lily = "lily";
    
  NF("Pick what, a lily?");

  if (lily_counter == MAX_LILY)
    {
      write ("You notice all the lilies have been picked.\n");
      return 1;
    }
  else
    {
      setuid();
      seteuid(getuid());
      if ((str == "lily"))
        {
          picked_lily = clone_object(OBJ_DIR + what_lily);
          picked_lily->move(this_player(), 1);
          write ("You pick a " + picked_lily->query_short() + ".\n");
          
          say (QCTNAME(this_player()) + " picks a " + picked_lily->query_short() + " from the " +
               "river.\n");
          lily_counter++;
          return 1;
        }
    }
  return 0;
}
 
