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
   set_wf(this_object());
   set_no_show_composite(1);
   
   set_default_armour(30, A_MAGIC);
}

void set_duration(float dur) {  set_alarm(dur,0.0,"kill_me"); }

kill_me()
{
    if (!wearer)
    {
        set_alarm(0.0,0.0,"remove_object");
        return;
    }

   object old_this_player;
   old_this_player = this_player();
   set_this_player(wearer);
   this_object()->remove_me();
   set_this_player(old_this_player);
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

   object old_this_player;
   old_this_player = this_player();
   set_this_player(wearer);
   this_object()->wear_me();;
   set_this_player(old_this_player);

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

/*
 * Function name: wear
 * Description  : This function might be called when someone tries to wear
 *                this armour. To have it called, use set_wf().
 * Arguments    : object obj - The armour we want to wear.
 * Returns      : int  0 - The armour can be worn normally.
 *                     1 - The armour can be worn, but print no messages.
 *                    -1 - The armour can't be worn, use default messages.
 *                string - The armour can't be worn, use this message.
 */
public mixed
wear(object obj)
{
    return 1;
}

/*
 * Function name: remove
 * Description  : This function might be called when someone tries to remove
 *                this armour. To have it called, use set_wf().
 * Arguments    : object obj - The armour to remove.
 * Returns      : int  0 - Remove the armour normally.
 *                     1 - Remove the armour, but print no messages.
 *                    -1 - Do not remove the armour, print default message.
 *                string - Do not remove the armour, use this message.
 */
public mixed
remove(object obj)
{
    return 1;
}
