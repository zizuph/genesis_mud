inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>

#define TP   this_player()

public void
create_object()
{
  set_name("recorder");
  set_adj(({"heavy", "brass"}));
  add_prop(OBJ_I_VALUE,    300);
  add_prop(OBJ_I_WEIGHT,  5000);
  add_prop(OBJ_I_VOLUME, 10000);
  set_long("A heavy recorder made of brass.\n");
}

public int
do_play(string str)
{
  if (!id(str)) return 0;
  
  write("You play a merry tune on the " + short() + ".\n");
  say(QCTNAME(TP) + " plays a merry tune on " + TP->query_possessive() +
      " " + short() + ".\n");
  return 1;
}

public void
init()
{
    ::init();
    add_action(do_play, "play");
}

