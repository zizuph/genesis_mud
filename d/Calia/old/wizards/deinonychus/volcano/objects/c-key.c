/* 	this is a object of the volcano

	coder(s):	Deinonychus

	history:	DD.MM.YY	what done		who did

	purpose:	none

	quests:		none
	special:	none

	to do:		none
	bug:		none known
*/


inherit "/std/object";
#include "objects.h"
#include <stdproperties.h>

create_object()
{
  /* descriptions */

  set_name("key");
  set_short("steel key");
  set_pshort("steel keys");
  set_long(BS("It's just a sample steel key. You wonder which door it fits.\n"));
  set_adj("steel");

  /* properties */

  add_prop(OBJ_I_VALUE, 6);
  add_prop(OBJ_I_WEIGHT, 10);
  add_prop(OBJ_I_VOLUME, 10);
} /* create_object */


/*
 * Function name: none
 * Description:   none
 * Arguments:     none
 * Returns:       none
 */
