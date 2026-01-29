/*
 * /d/Ansalon/goodlund/nethosak/docks/obj/weapon/battle_axe.c
 *
 * glain
 *
 * These are the standard axes for the minotaurs in general.
 * According to everything I have read, minotaurs favour large,
 * two-handed battle axes, and large two-handed swords, usually
 * a broad sword.  This file will prolly be moved to a more
 * std dir higher up in the nethosak dir.
 *
 */
#pragma strict_types

inherit "/std/weapon";

#include <stdproperties.h>
#include <tasks.h>
#include <wa_types.h>
#include "/d/Ansalon/common/defs.h"

void create_weapon()
{
   set_name("axe");
   set_adj("huge");
   add_adj("battle");
   set_long("This huge axe looks like it has seen quite a bit of " +
            "use, but it has been well kept for.  Only a few deep " +
            "marks scar the axe showing off the battles it has " +
            "taken part in.  These axes are common among the " +
            "minotaurs and are by far their weapons of choice.\n");
   set_short("huge battle axe");
   set_default_weapon(21,40, W_AXE, W_SLASH, W_BOTH);

   add_prop(OBJ_I_VOLUME, 6000);
   add_prop(OBJ_I_WEIGHT, 12000);

   set_wf(this_object());
}

/* 
 * Function name: wield
 * Description  : Checks to see if the character is strong enough to 
 *                wield the axe properly.
 * Arguments    : what - some object???
 * Returns      : int 0 - successfull wield
 *                string - a fail message
 */
mixed wield(object what)
{
   if (TP->resolve_task(1800, ({SKILL_WEIGHT, 900, TS_STR})) > 0)
   {
      return 0;
   }  

   return "Your muscles strain in effort as you try to properly " +
      "wield the battle axe, but the weight is too much for you.\n";
}