/* This is a magic shield, protecting the wearer from blows.
* It is nicked from examples, and changed by Korat.
*/

inherit "/d/Kalad/std/armour.c";
#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include "/d/Kalad/defs.h"

object wearer;

void
create_armour()
{
   set_name("forcefield");
   add_name("mag_shield_prot");
   set_adj("glowing");
   add_adj("magical");
   set_long("A magical forcefield covering your whole body.\n");
   add_prop(OBJ_I_NO_DROP, 1);
   add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
   add_prop(OBJ_S_WIZINFO, "A magical shield to protect the wearer. Will " +
      "out before to long\n");
   add_prop(MAGIC_AM_MAGIC, ({ 20, "abjured" }) );
   add_prop(MAGIC_AM_ID_INFO, ({
            "The forcefield will protect your entire body.\n", 0}) );
   
   set_default_armour(20, A_MAGIC);
}

void set_duration(float dur) {  set_alarm(dur,0.0,"kill_me"); }

kill_me()
{
   wearer->remove_arm(this_object());
   wearer->catch_msg("The magic forcefield is gone, you feel " +
      "unprotected.\n");
   tell_room(environment(wearer),QCTNAME(wearer)+" sighs as the "+
      "forcefield fades away.\n");
   set_alarm(0.0,0.0,"remove_object");
}

void
enter_env(object dest, object old)
{
   wearer = dest;
   wearer->catch_msg("You become surrounded by a forcefield, you feel "+
      "protected.\n");
   wearer->wear_arm(this_object());
   ::enter_env(dest,old);
}


int *
query_shield_slots()
{
   return ({ A_HEAD, A_BODY, A_L_ARM, A_R_ARM, A_LEGS});
}

int
dispel_magic(int magic)
{
   if (magic > 20)
      {
      set_alarm(0.0,0.0,"remove_object");
      return 1;
   }
   return 0;
}


