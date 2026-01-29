inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include <composite.h>
#include <cmdparse.h>
#include "/d/Shire/common/defs.h"

/* Completely stolen from Olorin's stench_ob and made into */
/* A stench ob of a different sort, by Dunstable- Sept 1994 */


//    Prototypes
void remove_stench();

int alarm_id;

void
create_object()
{
  set_name("Perfume_Odor_Object");
  add_prop(OBJ_I_VOLUME,0);
  add_prop(OBJ_I_WEIGHT,0);
  add_prop(OBJ_M_NO_DROP, "Drop what?");

  set_no_show();
}

void
enter_env(object to, object from)
{
  ::enter_env(to,from);

  if (!living(to)) 
  {
    remove_object();
    return;
  }
    set_alarm(1.0, 120.0, "stench_message", to);
    alarm_id = set_alarm(600.0,0.0,&remove_stench());
}


void
remove_stench()
{
  remove_alarm(alarm_id);
  if(interactive(ENV(TO)))
    ENV(TO)->catch_msg("You feel your perfume wearing off.\n");
  TO->remove_object();
}

void
stench_message(object player)
{
    player->catch_msg("You catch a whiff of wildflowers.\n");

    tell_room(environment(environment(TO)), 
        "The air explodes with the sweet scent of wildflowers.\n");
}

