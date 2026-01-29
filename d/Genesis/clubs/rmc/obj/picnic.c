inherit "/std/receptacle";

#include <macros.h>
#include <stdproperties.h>
#include <composite.h>
#include "defs.h"
#include <ss_types.h>
#include <wa_types.h>
#include <cmdparse.h>
#include <filter_funs.h>

int
fill_bag()
{
  seteuid(getuid(TO));
  
  clone_object(RICHCLUB+"/obj/winebottle")->move(TO);
  clone_object(RICHCLUB+"/obj/pie")->move(TO);
  clone_object(RICHCLUB+"/obj/cookie")->move(TO);
  clone_object(RICHCLUB+"/obj/cookie")->move(TO);
  clone_object(RICHCLUB+"/obj/cookie")->move(TO);
  clone_object(RICHCLUB+"/obj/cookie")->move(TO);
  clone_object(RICHCLUB+"/obj/cookie")->move(TO);

  return 1;
}

void
create_container()
{
  set_name("bag");
  set_adj("picnic");
  add_adj("small");

  set_short("small picnic bag");
  set_long("This is a small picnic bag for lunches outdoors. It "+
    "contains all the stuff for a perfect picnic.\n");

  add_prop(CONT_I_WEIGHT, 200);
  add_prop(CONT_I_MAX_WEIGHT, 3200);
  add_prop(CONT_I_VOLUME, 200);
  add_prop(CONT_I_MAX_VOLUME, 3200);

  fill_bag();
}
