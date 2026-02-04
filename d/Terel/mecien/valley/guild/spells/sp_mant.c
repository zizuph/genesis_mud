/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/resistance";
#include <stdproperties.h>
#include <macros.h>

void
create_resistance()
{
   set_name("_mantle_");
   set_adj("spiritual");
   set_no_show();
   add_prop(OBJ_I_LIGHT, 1);
   add_prop(MAGIC_I_RES_COLD, ({ 40, 1}));
   add_prop(MAGIC_I_RES_POISON, 40);
   add_prop(MAGIC_I_RES_IDENTIFY, 40);
   add_prop(MAGIC_I_RES_FIRE, 25);
   add_prop(MAGIC_I_RES_DEATH, 40);
}

void set_duration(int dur) { call_out("remove_object", dur); }

void
enter_env(object dest, object old)
{
   ::enter_env(dest, old);
   if(living(dest)){
      dest->add_prop(MAGIC_I_RES_POISON, dest->query_prop(MAGIC_I_RES_POISON) + 1);
      dest->add_prop(MAGIC_I_RES_DEATH, dest->query_prop(MAGIC_I_RES_DEATH) + 1);
      dest->add_prop(MAGIC_I_RES_FIRE, dest->query_prop(MAGIC_I_RES_FIRE) + 1);
      dest->add_prop(MAGIC_I_RES_IDENTIFY, dest->query_prop(MAGIC_I_RES_IDENTIFY) + 1);
      dest->add_prop(MAGIC_I_RES_COLD, dest->query_prop(MAGIC_I_RES_COLD) + 1);
      dest->catch_msg("A warmth and peace seems to surround and protect you.\n");
      dest->add_prop("protected", 1);
      tell_room(environment(dest), QCTNAME(dest) + 
         " glows with a shimmering light for a brief moment.\n", dest);
   }
}

void
leave_env(object old, object dest)
{
  ::leave_env(old, dest);
  if(living(old)){
   old->catch_msg("You feel cold as a spiritual force departs from you.\n");
   old->add_prop("protected", old->query_prop("protected") -1);
   old->add_prop(MAGIC_I_RES_POISON, old->query_prop(MAGIC_I_RES_POISON) - 1);
   old->add_prop(MAGIC_I_RES_DEATH, old->query_prop(MAGIC_I_RES_DEATH) - 1);
   old->add_prop(MAGIC_I_RES_FIRE, old->query_prop(MAGIC_I_RES_FIRE) - 1);
   old->add_prop(MAGIC_I_RES_IDENTIFY, old->query_prop(MAGIC_I_RES_IDENTIFY) - 1);
   old->add_prop(MAGIC_I_RES_COLD, old->query_prop(MAGIC_I_RES_COLD) - 1);
}
}

