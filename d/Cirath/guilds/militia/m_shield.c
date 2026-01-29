/*
 * Coded by: Yrgol
 * date: 14/2 - 02
 * Comment: The shield specc for militia
 */

#pragma save_binary
#include "guild.h"
#include "/d/Cirath/common/defs.h"
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <filter_funs.h>
#include <options.h>
#include <macros.h>
#define MIL_SHIELD_ON "_mil_shield_on_"

int orig_value=0;  // The shields original AC value
int shield_used=0; // Used to check wheter the shield_me is in use or not
int alarm=0;       // Used to check if the alarm is on or not.

reset_shield(object shield, object militia)
{
   militia->remove_prop(MIL_SHIELD_ON);
   write("\nYou feel like you can brace your shield against "
	+ "attacks again.\n\n");
  
   	
   return 1;
}

remove_ac(object shield, object militia)
{
   militia->remove_prop(MIL_SHIELD_ON);
   militia->add_prop(MIL_SHIELD_ON, 2);
   shield->set_ac(orig_value);  // Set the original value to the shield.
   shield->add_prop(OBJ_M_NO_DROP,0); // So that the player once again can drop the shield
//   add_fatigue(-5);               // Remove some fatigue after he has done this mighty thing
   militia->update_armour(shield);
   write("Your grip starts to slip, it's now back to normal.\n");   
   set_alarm(5.0,0.0,&reset_shield(shield, militia));
}

int
shield_me(string str)
{
   object sh,shield, militia;
   int al_time, bonus;
   militia=TP;
   if (!TP->query_skill(SS_MIL_SHIELD))
   {
      write("Why, you don't even have the skill to do that.\n");
      return 1;
   }
   if(str != "me")
   {
      write("shield what?\n");
      return 1;
   }
   // Check if the player already is shielded, if so then get the hell out of here
   if(militia->query_prop_setting(MIL_SHIELD_ON) == 1)
   {
      write("You are already holding a firm grip on your shield.\n");
      return 1;
   }
   else if(militia->query_prop_setting(MIL_SHIELD_ON) == 2)
   {
      write("You have to wait a little. Let your hand rest for a while.\n");
      return 1;
   }
   al_time=TP->query_skill(SS_MIL_SHIELD)+TP->query_stat(SS_DEX)/10; // Define the time that this is active.
   // Check if a shield is used in left or right hand
   if((sh = TP->query_armour(W_LEFT)) && (sh->query_at() == A_SHIELD))
   {
      shield=sh; // I wanted to put something in these.. =)
   }
   else if((sh = TP->query_armour(W_RIGHT)) && (sh->query_at() == A_SHIELD))
   {
      shield=sh; // I wanted to put something in these.. =)
   }
   else
   {
      // If we are here, then well.. the player didn't have a shield worn.
      write("Shield you with what?\n");
      return 1;
   }
   orig_value=sh->query_ac(); // Save the original ac value.
    bonus=((TP->query_stat(SS_DEX)/4) + (TP->query_skill(SS_MIL_SHIELD))
    + (orig_value))/5;// Define bonus value...
   //say("SS_DEX/2=" + TP->query_stat(SS_DEX)/2 + " SS_MIL_SHILED=" +TP->query_skill(SS_MIL_SHIELD) + " orig_value=" + orig_value + " bonus=" + bonus + "\n");
   shield->set_ac(orig_value+bonus);  // Set the new ac
   shield->add_prop(OBJ_M_NO_DROP,1); // So that the player can't drop the shield that he gave ac bonus
   set_alarm(itof(al_time),0.0,&remove_ac(shield,militia)); // delay time until we release the bonus
   militia->add_prop(MIL_SHIELD_ON, 1);// Declares so that we see that this specc is used.
   militia->update_armour(shield);
   write("You take a firm grip of your shield and ready yourself for battle.\n");
   say(QCTNAME(TP) + " takes a firm grip of his shield.\n");
   return 1;
}



