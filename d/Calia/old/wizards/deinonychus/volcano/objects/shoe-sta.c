/* 	this is a object of the volcano

	coder(s):	Deinonychus

	history:	DD.MM.YY	what done		who did
			31.03.93	created			Deinonychus

	purpose:	A place where the players can put their shoes on

	quests:		none
	special:	none

	to do:		none
	bug:		none known
*/


inherit "/std/container";
#include "objects.h"
#include <stdproperties.h>
#include <macros.h>
#include <language.h>

create_container()
{
  /* descriptions */

  set_name("shoe-stand");
  set_short("shoe-stand");
  set_long(BS("This shoe-stand is in perfect condition.\n"));

  /* properties */

  add_prop(OBJ_I_VALUE, 0);
  add_prop(CONT_I_WEIGHT, 300);
  add_prop(CONT_I_MAX_WEIGHT, 5300);
  add_prop(CONT_I_VOLUME, 400);
  add_prop(CONT_I_MAX_VOLUME, 5400);
  add_prop(CONT_I_RIGID, 1);
  add_prop(OBJ_I_NO_GET, 1);
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
  add_action("put", "put");
}

/*****************************************************************************/

/*
 * Function name: put
 * Description:   put something on the wardrobe
 * Arguments:     command
 * Returns:       0/1
 */

int
put(string command)
{
  object obj1, obj2;

  NF("Put what?\n");

  if(!parse_command(command, all_inventory(environment()) + all_inventory(TP),
    "%o 'on' %o", obj1, obj2))
    return 0;
  else
  {
    write("You put " + LANG_ASHORT(obj1) + " on the shoe-stand.\n");
    say(QCNAME(TP) + " puts " + LANG_ASHORT(obj1) + " on the shoe-stand.\n");
    obj1->move(TO);
    return 1;
  }
}

/*****************************************************************************/

/*
 * Function name: none
 * Description:   none
 * Arguments:     none
 * Returns:       none
 */
