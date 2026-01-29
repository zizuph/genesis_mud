/* 	this is a object of the volcano

	coder(s):   Deinonychus

	history:	DD.MM.YY	what done		who did
    			31.03.93	created			Deinonychus

	purpose:    wardrobe to hang your jacket on

	quests:     none
	special:    none

	to do:      none
	bug:        none known
*/


inherit "/std/container";
#include "objects.h"
#include <stdproperties.h>
#include <macros.h>
#include <language.h>

#define MAX_ITEMS 10

string *players;
object *objects;
int free;

create_container()
{
  /* descriptions */

  set_name("wardrobe");
  set_short("wardrobe");
  set_long(BS("This wardrobe looks as if it has seen many jackets.\n"));

  /* properties */

  add_prop(OBJ_I_VALUE, 0);
  add_prop(OBJ_I_NO_GET, 1);
  add_prop(CONT_I_WEIGHT, 1000);
  add_prop(CONT_I_MAX_WEIGHT, 10000);
  add_prop(CONT_I_VOLUME, 500);
  add_prop(CONT_I_MAX_VOLUME, 10000);
  add_prop(CONT_I_RIGID, 1);
  add_prop(CONT_M_NO_INS, "Put what on wardrobe?\n");
  add_prop(CONT_M_NO_REM, "Take what from wardrobe?\n");
  objects = allocate(MAX_ITEMS);
  players = allocate(MAX_ITEMS);
  free = MAX_ITEMS;
} /* create_container */

/*****************************************************************************/

/*
 * Function name: init
 * Description:   add some commands to the player
 * Arguments:     none
 * Returns:       nothing
 */

void
init()
{ 
  add_action("do_put", "put");
  add_action("do_take", "take");
  add_action("do_take", "get");
}

/*****************************************************************************/

/*
 * Function name: put
 * Description:   put something on the wardrobe
 * Arguments:     command
 * Returns:       0/1
 */

int
do_put(string command)
{
  object obj1, obj2;

  NF("Put what on what?\n");

  if(!parse_command(command, all_inventory(environment()) + all_inventory(TP),
    "%o 'on' %o", obj1, obj2))
    return 0;

  if(obj2 != TO)
    return 0;

  if(!free)
  {
    write("There's no free place on " + LANG_THESHORT(TO) + ".\n");
    return 1;
  }

  write("Ok.\n");
  say(QCNAME(TP) + " puts " + LANG_ASHORT(obj1) + " on " +
      LANG_THESHORT(TO) + ".\n");
  TO->change_prop(CONT_M_NO_INS, 0);
  obj1->move(TO);
  TO->change_prop(CONT_M_NO_INS, "What do you want to put on " +
                  LANG_THESHORT(TO) + "?\n");

  objects[MAX_ITEMS - free] = obj1;
  players[MAX_ITEMS - free] = TP->query_name();
  free--;
  return 1;
}

/*****************************************************************************/

/*
 * Function name: do_take
 * Description:   check if the wanted object belongs to the player
 * Arguments:     command
 * Returns:       0/1
 */

int
do_take(string command)
{
  object obj1, obj2;
  int index;

  NF("Take what from what?\n");

  if(!parse_command(command, all_inventory(environment()) + all_inventory(TO),
    "%o 'from' %o", obj1, obj2))
    return 0;

  if(obj2 != TO)
    return 0;

  index = member_array(obj1, objects);

  if(players[index] != TP->query_name())
  {
    write("I don't think this belongs to you.\n");
    return 1;
  }
  
  write("Ok.\n");
  say(QCNAME(TP) + " takes " + LANG_ASHORT(obj1) + " from " +
      LANG_THESHORT(TO) + ".\n");
  TO->change_prop(CONT_M_NO_REM, 0);
  obj1->move(TP);
  TO->change_prop(CONT_M_NO_REM, "Take what from " + LANG_THESHORT(TO) + ".\n");
  free++;
  objects[index] = objects[MAX_ITEMS - free];
  players[index] = players[MAX_ITEMS - free];
  objects[MAX_ITEMS - free] = 0;
  players[MAX_ITEMS - free] = 0;
  return 1;
}

/*****************************************************************************/

/*
 * Function name: none
 * Description:   none
 * Arguments:     none
 * Returns:       none
 */

