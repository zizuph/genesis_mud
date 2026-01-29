/*
 * /d/Ansalon/goodlund/nethosak/obj/weapon/red_sword.c
 *
 * glain
 *
 * This sword can be found wielded by the first mate of Stormseeker.
 * The first mate is a very well traveled and old minotaur.  In fact
 * he is a swordmaster and has the kestral mark branded on him.  This
 * sword was a gift from one of the many friends he made during his
 * journeys.  Hmmm, maybe I should talk to Arman about this one, maybe
 * even it was a gift from Viridion?  Anyway the sword is not magical
 * even though the description might make you think that it is.  
 * Instead the steel that the blade was created from had a 
 * non-magical natural reddish mineral mixed in with it to give the
 * blade its really cool look.  All that you are seeing in the
 * description is the veins of the reddish mineral in the blade.
 *
 */
#pragma strict_types

inherit "/std/weapon";
inherit "/lib/keep";

#include <macros.h>
#include <stdproperties.h>
#include <tasks.h>
#include <wa_types.h>
#include "/d/Ansalon/common/defs.h"

void create_weapon()
{
   set_name(({"sword","broadsword"}));
   set_adj("heavy");
   add_adj("red-bladed");
   set_long("The broad blade of this sword is perfectly balanced and " +
            "shows the work of a master weaponsmith.  The blade has " +
            "a faint red color to it that swirls across it, making " +
            "you dizzy.  Crafted to be used in the large hands of a " +
            "minotaur, you are not too sure if you can wield it " +
            "even with both hands.\n");
   set_short("heavy red-bladed broadsword");   
   set_default_weapon(34,39, W_SWORD, W_SLASH, W_BOTH);
   
   add_prop(OBJ_I_VOLUME, 5000);
   add_prop(OBJ_I_WEIGHT, 12000);
   
   add_cmd_item("sword", "show", "@@show_sword");

   set_wf(this_object());

   seteuid(getuid());
}


/* 
 * Function name: wield
 * Description  : Checks to see if the character is strong enough to 
 *                wield the blade properly.
 * Arguments    : what - some object???
 * Returns      : int 0 - successfull wield
 *                string - a fail message
 */
mixed 
wield(object what)
{
   object wielder = TP;

   if (wielder->resolve_task(1800, ({SKILL_WEIGHT, 900, TS_STR})) > 0)
   {
      return 0;
   }  

   return "Your muscles strain in effort as you try to properly " +
      "wield the broadsword, but the weight is too much for you.\n";
}

/* 
 * Function name: show_sword
 * Description  : Replaces the standard show emote for this item.
 *                Basically just shows off the odd blade.
 * Returns      : string - a empty string
 */
string
show_sword()
{
   write("You show your " + short() + " around.  The streaks " +
      "of red along the blade swirl and glitter making you dizzy.\n");
   
   say(QCTNAME(TP) + " shows " + HIS(TP) + " " +
      short() + " around.  The streaks of red along the blade swirl " +
      "and glitter making you dizzy.\n");
   
   return "";
}