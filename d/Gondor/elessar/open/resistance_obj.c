/*
 * A standard invisible resistance object.
 * Elessar, Genesis - July 1992.
 */
 
inherit "/std/object";
#include "/sys/ss_types.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"

mixed res_type;
int time, strength;

set_res_type(string str) { res_type = str; }
set_strength(int i) { strength = i; }
query_strength() { return strength; }
set_time(int i) { time = i; }
query_time() { return time; }

create_object()
{
  set_name("Resistance_Object");
  add_prop(OBJ_I_INVIS,1);
  add_prop(OBJ_M_NO_DROP,1);
  add_prop(OBJ_I_WEIGHT,0);
  add_prop(OBJ_I_VOLUME,0);
  add_prop(OBJ_I_VALUE,0);
}

init()
{
  call_out("stop_res",time);
  add_prop(res_type,({strength,1}));
}

enter_env(to, from)
{
  if (living(to))
    to->add_prop(res_type,(to->query_prop(res_type)+1));
}

leave_env(from, to)
{
  if (living(from))
    from->add_prop(res_type,(from->query_prop(res_type)-1));
}

stop_res()
{
  write("You feel less resistant.\n");
  remove_object();
}
