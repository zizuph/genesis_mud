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
#include <cmdparse.h>
#include <macros.h>
#include <language.h>

/* prototypes */
string long();
init();
int do_point(string command);
int do_drive_in(string command);

/* global variables */
int pointed = 0;	/* flag showing if plug is pointed */
int driven_in = 0;	/* flag showing if plug is driven in the ground */

create_object()
{
  /* descriptions */

  set_name("plug");
  set_short("wooden plug");
  set_pshort("wooden plugs");
  set_long("@@long@@");
  set_adj(({"wooden",}));

  /* properties */

  add_prop(OBJ_I_VALUE, 12);
  add_prop(OBJ_I_WEIGHT, 1500);
  add_prop(OBJ_I_VOLUME, 2000);
} /* create_object */

/******************************************************************************/

/*
 * Function name:	init
 * Description:		add some commands to the player
 * Arguments:		none
 * Returns:		none
 */
init()
{
  ::init();
  add_action("do_point", "point");
  add_action("do_drive_in", "drive");
}

/*****************************************************************************/

/*
 * Function name:	long
 * Description:		generate string depending if pointed and driven in
			ground
 * Arguments:		none
 * Returns:		longdescription
 */
string long()
{
  if(driven_in)
    return(BS("This strong wooden plug is driven firmly in the ground.\n"));
    
  if(pointed)
    return(BS("This strong wooden plug is pointed on one side so you can " +
	      "drive it easily in the ground.\n"));

  return(BS("This is a strong wooden plug. If you'd manage to point it " +
	    "you could try to drive it in the ground somewhere.\n"));
}

/*****************************************************************************/

/*
 * Function name:	do_point
 * Description:		let the player point the plug
 * Arguments:		given command
 * Returns:		0/1
 */
int
do_point(string command)
{
  NF("Point what?\n");
 
  if(!(CMDPARSE_ONE_ITEM(command, "point_it", 0)))
    return 0;
  else
    return 1;
}

/*****************************************************************************/

/*
 * Function name:	point_it
 * Description:		point a plug
 * Arguments:		object to point
 * Returns:		0/1
 */
int
point_it(object obj)
{
  if(obj != TO)
    return 0;

  if(obj->query_driven_in())
  {
    write(BS("You can't point " + LANG_THESHORT(obj) + ". It's driven " +
          "firmly in the ground.\n"));
    return 1;
  }

  if(obj->query_pointed())
  {
    write(capitalize(LANG_THESHORT(obj)) + " is already pointed.\n");
    return 1;
  }

  if(!sizeof(FIND_STR_IN_OBJECT("axe", TP)))
  {
    write(BS("You'd need an axe to point " + LANG_THESHORT(obj) + ".\n"));
    return 1;
  }

  write("You point " + LANG_THESHORT(obj) + " with the axe.\n");
  pointed = 1;
  return 1;
}

/*****************************************************************************/

/*
 * Function name:	do_drive_in
 * Description:		let the player drive the plug in the ground
 * Arguments:		given command
 * Returns:		0/1
 */
int
do_drive_in(string command)
{
  string item;
  
  NF("Drive what in what?\n");

  if(!sscanf(command, "%s in ground", item))
    return 0;
 
  if(!(CMDPARSE_ONE_ITEM(item, "drive_it_in", 0)))
    return 0;
  else
    return 1;
}

/*****************************************************************************/

/*
 * Function name:	drive_it_in
 * Description:		drive a plug in the ground
 * Arguments:		object to point
 * Returns:		0/1
 */
int
drive_it_in(object obj)
{
  object room;	/* room where the player wants to drive plug in ground */

  if(obj != TO)
    return 0;

  if(obj->query_driven_in())
  {
    write(BS(capitalize(LANG_THESHORT(obj)) + " is already firmly driven " +
          "in the ground.\n"));
    return 1;
  }

  if(!obj->query_pointed())
  {
    write(BS("You try in vain to drive " + LANG_THESHORT(obj) + " in the " +
	     "ground.\n"));
    return 1;
  }

  if(!sizeof(FIND_STR_IN_OBJECT("hammer", TP)))
  {
    write(BS("You'd need a hammer to drive " + LANG_THESHORT(obj) +
	     " in the ground.\n"));
    return 1;
  }

  room = environment(TP);
  if(room->query_prop(ROOM_I_TYPE) != ROOM_NORMAL)
  {
    write("I don't think " + LANG_THESHORT(TO) + " can be driven in here.\n");
    return 1;
  }

  write("You drive " + LANG_THESHORT(obj) + " with the hammer " +
	"in the ground.\n");
  driven_in = 1;
  TO->move(environment(TP));
  TO->add_prop(OBJ_M_NO_GET, capitalize(LANG_THESHORT(TO)) + " is driven " +
    "firmly in the ground. You're not strong enough to pull it out.\n");
  return 1;
}

/*****************************************************************************/

/*
 * Function name:	query_pointed
 * Description:		check if plug is pointed
 * Arguments:		none
 * Returns:		0/1
 */
int
query_pointed()
{
  return pointed;
}

/*****************************************************************************/

/*
 * Function name:	query_driven_in
 * Description:		check if plug is driven in ground
 * Arguments:		none
 * Returns:		0/1
 */
int
query_driven_in()
{
  return driven_in;
}

/*****************************************************************************/

/*
 * Function name:	tie_object
 * Description:		let a rope be tied to the plug
 * Arguments:		object calling tie_object, given command to tie
 * Returns:		0/1
 */
int
tie_object(object obj, string str)
{
  if(!driven_in)
  {
    NF("I don't think this will be of any use.\n");
    return 0;
  }

  if(MASTER_OB(environment(TO)) == ROOM("top"))
    call_other(ROOM("hole"), "rope_tied");

  return 1;
}    

/*****************************************************************************/

/*
 * Function name:	untie_object
 * Description:		let a rope be untied from the plug
 * Arguments:		object calling untie_object, given command to untie
 * Returns:		0/1
 */
int
untie_object(object obj, string str)
{
  if(MASTER_OB(environment(TO)) == ROOM("top"))
    call_other(ROOM("hole"), "rope_untied");

  return 1;
}    

