inherit "/std/object";

#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/d/Shire/common/defs.h"

// 02/01/10 Arandir	Tiny fixes to make the most obvious bugs go away.
//			The stool still suffers from the possibility of a
//			player exitting the room via nonstandard means,
//			leaving the stool in an occupied state ...

//--------------------------------------------------------------------------

#define ST_PROP_SITTING "_live_i_sitting_on_milking_stool"

int iOccupied;

//--------------------------------------------------------------------------

void create_object ()
{
  set_name  ("stool");
  add_name  (({"wooden stool","milking stool"}));
  add_adj   (({"short","wooden"}));
  set_short ("short wooden stool");
  set_long  ("This is a rather short stool, probably made for " +
             "hobbits, you think. You can sit on it.\n");

  add_prop (OBJ_I_WEIGHT, 600);
  add_prop (OBJ_I_VOLUME, 1500);
  add_prop (OBJ_I_VALUE, 13);

  iOccupied = 0;
}

//--------------------------------------------------------------------------

void init ()
{
  ::init ();
  add_action ("do_sit", "sit");
  add_action ("do_stand", "stand");
  add_action ("do_nothing", "north");
  add_action ("do_nothing", "south");
  add_action ("do_nothing", "east");
  add_action ("do_nothing", "west");
  add_action ("do_nothing", "southeast");
  add_action ("do_nothing", "southwest");
  add_action ("do_nothing", "northeast");
  add_action ("do_nothing", "northwest");
  add_action ("do_nothing", "up");
  add_action ("do_nothing", "down");
  add_action ("do_nothing", "in");
  add_action ("do_nothing", "out");
  add_action ("do_nothing", "quit");
  add_action ("do_nothing", "kiss");

}

//--------------------------------------------------------------------------

int do_sit (string sStr)
{
  if (sStr != "on stool")
  {
    write ("Sit on what?\n");
    return (1);
  };

  if (iOccupied)
  {
    write ("The stool is already occupied!\n");
    return (1);
  };

  if (TP->query_prop (ST_PROP_SITTING))
  {
    write ("You are already sitting down!\n");
    return (1);
  };

  iOccupied = 1;

  TP->add_prop (ST_PROP_SITTING, 1);
  TP->add_prop (LIVE_S_EXTRA_SHORT, " is sitting on a wooden stool");

  // We have to prevent people from giving the stool to anyone who
  // could walk away with it, because that would leave the stool
  // and the occupant in an inconsistent state.

  add_prop (OBJ_M_NO_GET, "The stool is occupied!\n");
  add_prop (OBJ_M_NO_DROP, "The stool is occupied!\n");
  add_prop (OBJ_M_NO_GIVE, "The stool is occupied!\n");
  add_prop (OBJ_M_NO_STEAL, "The stool is occupied!\n");

  write ("You sit down on the stool, a bit uncomfortably.\n");
  say (QCTNAME(TP)+ " sits down on a wooden stool.\n");
  return (1);
}

//--------------------------------------------------------------------------

int do_stand ()
{
  if (!TP->query_prop (ST_PROP_SITTING))
  {
    write ("You are not sitting down!\n");
    return (1);
  };

  write ("You stand up from the stool.\n");
  say(QCTNAME(TP)+ " stands up from a wooden stool.\n");

  TP->remove_prop (ST_PROP_SITTING);
  TP->remove_prop (LIVE_S_EXTRA_SHORT);

  remove_prop (OBJ_M_NO_GET);
  remove_prop (OBJ_M_NO_DROP);
  remove_prop (OBJ_M_NO_GIVE);
  remove_prop (OBJ_M_NO_STEAL);

  iOccupied = 0;

  return (1);
}

//--------------------------------------------------------------------------

int do_nothing ()
{
  if (TP->query_prop(ST_PROP_SITTING)) 
  {
    write ("You must stand up from the stool before you can do that.\n");
    return (1);
  };
  return (0);
}

//--------------------------------------------------------------------------
