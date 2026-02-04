/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/weapon";

#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>

#define TO   this_object()
#define TP   this_player()

#define ALIGN_LIM  -25

int time;


public void
create_weapon()
{
   set_name("dagger");
   set_adj("long");
   add_adj("gilded");
    set_short("long gilded dagger");
   add_name("mystic_dagger");
   add_name("long dagger");
   add_name("blade");
   set_long(
      "A gilded blade, gold, ornate, yet very powerfully made. It is a long dagger, " +
      "its blade adorned with three stars, the hilt spiralled, the pommel in " +
      "the shape of a dragon's head, its eyes are rubies.\n");
   set_wt(W_KNIFE);
   set_dt(W_SLASH);
   set_hit(34);
   set_pen(39);
   add_cmd_item("dagger", "raise", "@@do_raise_dagger");
   add_prop("mystic_weapon", 1);
   add_prop(OBJ_I_IS_MAGIC_WEAPON, 50);
   add_prop(MAGIC_AM_MAGIC, ({ 50, "conjuration" }));
   
}

do_raise_dagger(){
   object who;
   
   who = query_wielded();
  if(!query_wielded()) return "The blade must be wielded.\n";
   if(time) return "The blade is still fiery.\n";
   who->catch_msg("You raise up the " + short() + " and feel a power pass through you.\n");
   say(QCTNAME(who) + " raises up a " +short()+ " and glows with a golden light.\n");
   time = 1;
  who->add_mana(100);
   set_alarm(1800.0, -1.0, "time_out");
   return 1;
}

time_out(){
   time = 0;
}

/*
* Function name: wield
* Description:   Try to wield a weapon.
* Arguments:     obj - the weapon to try to wield.
* Returns:       0 - wield this weapon normally.
*                1 - wield the weapon, but print no messages.
*                -1 - do not wield the weapon, use default messages.
*                string - do not wield the weapon, use this fail message.
*/

/*
* Function name: did_hit
* Description:   Tells us that we hit something. Should produce combat
*                messages to all relevant parties. If the weapon
*                chooses not to handle combat messages then a default
*                message is generated.
* Arguments:     aid:   The attack id
*                hdesc: The hitlocation description.
*                phurt: The %hurt made on the enemy
*                enemy: The enemy who got hit
*                dt:    The current damagetype
*                phit:  The %success that we made with our weapon
*                dam:   The actual damage caused by this weapon in hit points
* Returns:       True if it handled combat messages, returning a 0 will let
   *                the normal routines take over
*/

public string
query_recover()
{
   return 0;
}

