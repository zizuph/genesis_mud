/*
 * Surrender.c (object to give the player surrender)
 *
 * This is cloned from the guards in the guardroom into 
 * any player that entered the room without checking
 * the room through peeking the lock.
 *
 * If this object leaves the room it shall self destruct.
 *
 * 2008-05-11 Lunatari
 */
inherit "/std/object";

#include "../local.h"
#include <macros.h>
#include <filter_funs.h>
#include <language.h>
#include <composite.h>
#include <stdproperties.h>

#define GUARD_ROOM "/d/Ansalon/kalaman/dungeon/gr1"
#define CELL_ROOM  "/d/Ansalon/kalaman/dungeon/cell1"

int do_surrender(string arg);

void
create_object()
{
   set_name("_i_surrender_command_");

   add_prop(OBJ_M_NO_SELL, 1);
   add_prop(OBJ_I_NO_STEAL, 1);
   add_prop(OBJ_I_NO_DROP, 1);

   set_no_show_composite(1);
}

void
init()
{
 ::init();

 add_action(do_surrender, "surrender");
}

int
do_surrender(string arg)
{
  int count;
  mixed objects = all_inventory(environment(this_player()));

  /* Failsafe, if this is used outside the room, destruct it */
  if (file_name(ENV(ENV(TO))) != GUARD_ROOM) 
  {
    if(ENV(TO)->query_real_name() == "lunatari")
      write("Master: " + file_name(ENV(ENV(TO))) + " Guard: " + GUARD_ROOM + "\n");

    write("You lost the ability to surrender.\n");
    TO->remove();
    return 1;
  }

  /* lopp through the list */
  while (count < sizeof(objects)) 
  {
    /* Lets stop NPC's fighting you */
    if (objects[count]->query_npc())
    {
       /* Lets stop fighting */
       this_player()->stop_fight(objects[count]);
       objects[count]->stop_fight(this_player());
    }

    count++;
  }

  write("You surrender to the guards!\nYou are put in chains.\n");
  write("The guards rushes you to the cell corridor..\n");
  write("A guard opens the cell door using his key.\n");
  write("One of the guards remove your chains and kick you inside " +
    "the cell.\nYou land flat on the ground, face first, Ouch!\n");
  write("You hear a loud 'click' as the cell door is locked from " +
    "the outside.\n");
  TP->move_living("X", find_object(DUNGEON + "cell1"), 1);
  TO->remove();

  /* We should clone the stun object here */

  return 1;
}
