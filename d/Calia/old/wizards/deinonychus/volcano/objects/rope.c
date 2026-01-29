/* 	this is a object of the volcano

	coder(s):	Deinonychus

	history:	DD.MM.YY	what done		who did
			28.10.93	created			Deinonychus

	purpose:	rope to tie on top of volcano

	quests:		part of the egg-quest
	special:	none

	to do:		none
	bug:		none known
*/


inherit "/std/object";
#include "objects.h"
#include <stdproperties.h>
#include <language.h>
#include <macros.h>

object tied_to;	/* object the rope is tied to */

create_object()
{
  /* descriptions */

  set_name("rope");
  set_short("rope");
  set_pshort("ropes");
  set_long(BS("It's just an ordinary rope but still good for something.\n"));

  /* properties */

  add_prop(OBJ_I_VALUE, 50);
  add_prop(OBJ_I_WEIGHT, 2000);
  add_prop(OBJ_I_VOLUME, 1500);
  add_prop(OBJ_M_NO_GET, 0);
  tied_to = 0;
} /* create_object */

/*****************************************************************************/

/*
 * Function name: init
 * Description:   add commands to the player
 * Arguments:     none
 * Returns:       none
 */
init()
{
  add_action("do_tie", "tie");
  add_action("do_untie", "untie");
  ::init();
}

/*****************************************************************************/

/*
 * Function name: do_tie
 * Description:   Try to tie the rope to something
 * Arguments:     command
 * Returns:       1/0
 */

int 
do_tie(string command)
{
  object obj1, obj2;
  object env;

  env = environment();
  
  if(living(env))	/* The environment for parse_command is env(env) */
    env = environment(env);

  if(!parse_command(command, all_inventory(env) + all_inventory(TP),
    "%o 'to' %o", obj1, obj2))
  {
    NF("Tie what to what?\n");
    return 0;
  }

  if(obj1 != TO)
  {
    NF("Tie what to what?\n");
    return 0;
  }

  if(tied_to)
  {
    NF(TO->query_prop(OBJ_M_NO_GET));
    return 0;
  }
  
  if(living(obj2) || function_exists("create_npc", obj2))
  {
    write(LANG_THESHORT(obj2) + " is no good place to tie your rope to.\n");
    return 1;
  }

  if(!(obj2->query_prop(OBJ_M_NO_GET) || obj2->query_prop(OBJ_I_NO_GET)))
  {
    write(capitalize(LANG_THESHORT(obj2)) + " is no good place to tie " +
          "your rope to.\n");
    return 1;
  }

  tied_to = obj2;
  TO->move(env);
  TO->change_prop(OBJ_M_NO_GET, "The rope is tied to " + 
                  LANG_THESHORT(obj2) + ".\n");
  write("Ok.\n");

  if(MASTER_OB(env) == ROOM("top"))
    call_other(ROOM("hole"), "rope_tied");

  return 1;
}

/*****************************************************************************/

/*
 * Function name: do_untie
 * Description:   Try to untie the rope from something
 * Arguments:     command
 * Returns:       1/0
 */

int 
do_untie(string command)
{
  object obj1;
  object env;

  env = environment();

  if(!parse_command(command, all_inventory(env),
    "%o", obj1))
  {
    NF("Untie what?\n");
    return 0;
  }

  if(obj1 != TO)
  {
    NF("Untie what?\n");
    return 0;
  }

  if(!tied_to)
  {
    NF("The rope is not tied to anything.\n");
    return 0;
  }

  TO->change_prop(OBJ_M_NO_GET, 0);
  TO->move(TP);
  write("Ok.\n");
  say(QCTNAME(TP) + " unties " + LANG_ASHORT(TO) + " from " +
      LANG_THESHORT(tied_to) + ".\n");
  tied_to = 0;

  if(MASTER_OB(env) == ROOM("top"))
    call_other(ROOM("hole"), "rope_untied");

  return 1;
}

/*****************************************************************************/

/*
 * Function name: none
 * Description:   none
 * Arguments:     none
 * Returns:       none
 */

 
