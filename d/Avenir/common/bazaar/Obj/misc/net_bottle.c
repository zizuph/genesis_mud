 // Bottle        (/d/Avenir/common/bazaar/NPC/waiter.c)
 // creator(s):    Glinda may -95
 // last update:
 // purpose:       A bottle containing a letter
 //
 // note:
 // bug(s):
 // to-do:

inherit "/std/receptacle";

#define LETTER "/d/Avenir/common/bazaar/Obj/books/book3"

#include <stdproperties.h>
#include "/d/Avenir/common/common.h"

void
create_receptacle()
{
  if (!IS_CLONE)
    return;

  set_name ("bottle");
  set_short ("green glass bottle");
  set_adj("green");
  add_adj("glass");
  set_long("The surface of this bottle bears mark of having been in water " +
           "for decades.\n");
  add_prop (CONT_I_WEIGHT, 450);
  add_prop (CONT_I_VOLUME, 500);
  add_prop (OBJ_I_VALUE, 100);
  add_prop (CONT_I_MAX_WEIGHT, 950);
  add_prop (CONT_I_MAX_VOLUME, 1000);
  add_prop (CONT_I_TRANSP, 1);
  add_prop (CONT_I_RIGID, 1);
  add_prop (CONT_I_CLOSED, 1);
   seteuid(getuid());
  set_alarm(0.1,0.0,"fill_me");
}

fill_me()
{
  object letter;

  letter=clone_object(LETTER);
  letter->move(TO, 1);
}


