/*******************************************************************\
| BASH_GLOVES_SHADOW.C                                              |
+-------------------------------------------------------------------+
| The purpose of this shadow is to hook the cr_did_hit callback in  |
| the wearer of the gloves so that we can add the stun effect.      |
\*******************************************************************/

/*
 * 01/11/01 Tijgen	Created sometime around this time
 * 01/11/26 Arandir	Cleaned up and integrated with hit messages
 *			Threw out unnecessary VBFC calls in messages
 * 01/12/08 Arandir	Changed stun to use add_stun and remove_stun
 *
 */

#include "bash_gloves.h"

inherit "/std/shadow";

#include <macros.h>
#include <wa_types.h>
#include <stdproperties.h>

//-------------------------------------------------------------------

int bg_do_stun (object oEnemy, int iDamage);
void bg_do_recovery (object oEnemy);
void bg_do_message (object oEnemy, string sLocation, int iHurtPer);

//-------------------------------------------------------------------

/*******************************************************************\
| Shadow management functions.                                      |
\*******************************************************************/

/*
 * Function name : bg_attach_shadow
 * Description   : Attaches the shadow to the wearer
 *
 */

int bg_attach_shadow (mixed mWhom)
{
  int iReturn = ::shadow_me (mWhom);
  return (iReturn);
}

/*
 * Function name : bg_destroy_shadow
 * Description   : Removes the shadow hooking the wearer
 *
 */

void bg_destroy_shadow ()
{
   remove_shadow ();
}

//-------------------------------------------------------------------

/*******************************************************************\
| Shadow hook functions.                                            |
\*******************************************************************/

/*
 * Function name : cr_did_hit
 * Description   : Called every time the wearer hits something
 *   iAttack       : Identifies the attack that did the hit
 *   sLocation     : Identifies the location that got hit
 *   iHurtPer      : Percentage of maximum hurt done
 *   oEnemy        : Enemy that got hit
 *   iDamageType   : Identifies the damage type
 *   iHitPer       : Percentage of maximum hit done
 *   iDamage       : Damage that got done
 *
 */

int cr_did_hit (
  int     iAttack,
  string  sLocation,
  int     iHurtPer,
  object  oEnemy,
  int     iDamageType,
  int     iHitPer,
  int     iDamage)
{
  // The gloves only engage in combat if the hit is to a living
  // being and done by a hand not wielding a weapon.

  if ((living (oEnemy)) &&
      ((iAttack & W_LEFT) || (iAttack & W_RIGHT) || (iAttack & W_BOTH)))
  {
    object oMe = this_player ();
    if (!oMe->query_weapon (iAttack))
    {
      // If the hit is to the head and the enemy is not yet
      // stunned, we do the stun stunt :-) ...

      if ((sLocation == "head") &&
          (!present (BG_STUN_NAME, oEnemy)))
      {  
        bg_do_stun (oEnemy, iDamage);
      };

      // Now display a combat message and return without calling
      // the shadowed cr_did_hit function. This means that if the
      // wearer implements some extra functionality that relies
      // on cr_did_hit, it will not work. Too bad, eh ? :-)

      bg_do_message (oEnemy, sLocation, iHurtPer);
      return (TRUE);
    };
  };

  return (shadow_who->cr_did_hit (iAttack, sLocation, iHurtPer,
                                  oEnemy, iDamageType, iHitPer,
                                  iDamage));
}

//-------------------------------------------------------------------

/*******************************************************************\
| Gloves combat functions.                                          |
\*******************************************************************/

/*
 * Function name : bg_do_stun
 * Description   : Responsible for adding stun effect to a hit
 *
 */

int bg_do_stun (object oEnemy, int iDamage)
{
  // This function is only called after checks on the target
  // and attack are done, so we do not have to worry whether
  // it makes sense to stun in this particular situation.

  int iMana, iManaDamage;

  // For a typical living, the chance to hit with hands in a
  // combat round is about 60%. A typical humanoid target will
  // have about 15% chance to get hit in the head. Suppose the
  // enemy will have roughly the same physical and mental stats,
  // this means that if we want to stun him around the time the
  // combat ends, we have to make the mana damage 11 times the
  // physical damage.

  iMana = oEnemy->query_mana ();
  if (iDamage) iManaDamage = random (iDamage * 10) + 1;
          else iManaDamage = 0;
  oEnemy->add_mana (-iManaDamage);

  if (iManaDamage > 0)
  {
    if (oEnemy->query_mana () <= 0)
    {
      // Youpee, we just knocked out the bastard ! Paralyze him
      // by adding the paralysis object to his environment and
      // prevent him from fighting.
    
      int    iRemoveTime;
      object oParalysis;
    
      iRemoveTime = MIN (iManaDamage, 20 + random (10));
    
      seteuid (getuid ());
      oParalysis = clone_object (BG_STUN_FILE);
      oParalysis->set_name        (BG_STUN_NAME);
      oParalysis->set_no_show     (TRUE);
      oParalysis->set_remove_time (iRemoveTime);
      oParalysis->set_stop_verb   ("");
      oParalysis->set_stop_object (0);

      switch (random (3))
      {
        case 0: oParalysis->set_stop_message (
                  "You feel like you are slowly coming to, " +
                  "but your head hurts like hell.\n");
                break;
        case 1: oParalysis->set_stop_message (
                  "You regain your senses, but the headache " +
                  "makes you wish you did not.\n");
                break;
        case 2: oParalysis->set_stop_message (
                  "You open your eyes slowly, vaguely remembering " +
                  "you were fighting before something hit you.\n");
                break;
      };

      switch (random (3))
      {
        case 0: oParalysis->set_fail_message (
                  "Try as you might, you cannot get your " +
                  "brain to work.\n");
                break;
        case 1: oParalysis->set_fail_message (
                  "You're dreaming such a nice dream, you do " +
                  "not really want to disturb it.\n");
                break;
        case 2: oParalysis->set_fail_message (
                  "Your head still rings with the blow that " +
                  "sent you down. You are unable to do that.\n");
                break;
      };

      oParalysis->move (oEnemy, 1);

      // Prevent the paralyzed enemy from fighting back by setting his
      // LIVE_I_STUNNED property. I do not particularly like this approach
      // because it does not allow for more stuns to be combined, but that
      // is life I guess :-) ...

      oEnemy->add_stun ();

      // Schedule an alarm that will notify the room about the end
      // of the paralysis and remove the LIVE_I_STUNNED property.

      set_alarm (itof (iRemoveTime), 0.0,
                 &bg_do_recovery (oEnemy));

      // Ohh, and also let the enemy and room know what happened.
    
      switch (random (2))
      {
        case 0: oEnemy->catch_msg (
                  "Suddenly, a blow out of nowhere sends you to the ground.\n");
                break;
        case 1: oEnemy->catch_msg (
                  "You barely notice a silver blur coming at you before " +
                  "your vision shatters.\n");
                break;
      };

      switch (random (2))
      {
        case 0: tell_room (environment (oEnemy),
                  QCTNAME (oEnemy) + " falls unconscious to the floor.\n", oEnemy);
                break;
        case 1: tell_room (environment (oEnemy),
                  "After a particularly nasty blow to the head, " +
                  QTNAME (oEnemy) + " folds down to the floor.\n", oEnemy);
                break;
      };
    }
    else
    {
      // Oh well, we did not manage to stun the sucker, but we at
      // least sucked some of his mana, so tell everyone about it.
    
      string sHowDizzy;
      int    iManaHurt;
      object oMe = this_player ();

      iManaHurt = (100 * iManaDamage) / iMana;
      sHowDizzy = "slightly dizzy";
      if (iManaHurt > 5)  sHowDizzy = "dizzy";
      if (iManaHurt > 10) sHowDizzy = "confused";
      if (iManaHurt > 20) sHowDizzy = "disoriented";
      if (iManaHurt > 40) sHowDizzy = "dazed and confused";
     
      oMe->catch_msg (QCTNAME (oEnemy) + " seems to be " + sHowDizzy + ".\n");
      oMe->tell_watcher (QCTNAME (oEnemy) + " seems to be " + sHowDizzy + ".\n", oEnemy);
      oEnemy->catch_msg ("You are " + sHowDizzy + ".\n");
    };
  };
}

/*
 * Function name : bg_do_recovery
 * Description   : Responsible for ending stun effect of a hit
 *
 */

void bg_do_recovery (object oEnemy)
{
  // Remove the stun from the enemy so that he can fight.
  
  oEnemy->remove_stun ();

  // Tell the room that the enemy woke up. We do not tell this
  // to the enemy himself, because the paralysis object already
  // does that. We also do not tell this to anyone if the enemy
  // is a ghost, because that sort of does not make sense :-) ...
  
  if (!oEnemy->query_ghost ())
  {
    switch (random (3))
    {
      case 0: tell_room (environment (oEnemy),
                QCTNAME (oEnemy) + " appears to regain " +
                QPOS (oEnemy) + " senses again.\n", oEnemy);
      break;
      case 1: tell_room (environment (oEnemy),
                QCTNAME (oEnemy) + " looks around with a " +
                "bewildered expression on " +
                QPOS (oEnemy) + " face.\n", oEnemy);
      break;
      case 2: tell_room (environment (oEnemy),
                QCTNAME (oEnemy) + " shakes off the effects of " +
                "the blow that sent " + QOBJ (oEnemy) + " down.\n",
                oEnemy);
      break;
    };
  };
}

//-------------------------------------------------------------------

/*******************************************************************\
| Gloves message functions.                                         |
\*******************************************************************/

/*
 * Function name : bg_do_message
 * Description   : Responsible for adding fancy messages to a hit
 *
 */

void bg_do_message (object oEnemy, string sLocation, int iHurtPer)
{
  object oMe = this_player ();

  // Produce some really cool messages if the enemy died.

  if (oEnemy->query_hp () <= 0)
  {
    switch (random (2))
    {
      case 0: oMe->catch_msg ("An unreal feeling runs down your spine as you watch your gloved fist connect with " + XTPNAME (oMe, oEnemy) + " " + sLocation + ". You can hear the bones shatter by the force of the impact.\n");
              oMe->tell_watcher ("You can hear bones shatter as " + QTPNAME (oMe) + " gloved fist connects with " + QTPNAME (oEnemy) + " " + sLocation + ".\n", oEnemy);
              oEnemy->catch_msg ("You can hear bones shatter as " + XTPNAME (oEnemy, oMe) + " gloved fist connects with your " + sLocation + ". Your last impression is that of a debilitating pain ...\n");
              break;
      case 1: oMe->catch_msg ("You feel the momentum of your plated leather gloves as your open palm hits " + XTPNAME (oMe, oEnemy) + " " + sLocation + ", now snapped back in an unnatural angle.\n");
              oMe->tell_watcher ("A cold shiver runs down your spine as " + QTNAME (oMe) + " snaps " + QTPNAME (oEnemy) + " " + sLocation + " back in an unnatural angle with an open palm strike.\n", oEnemy);
              oEnemy->catch_msg ("Too late, you notice " + XTNAME (oEnemy, oMe) + " aim an open palm strike at your " + sLocation + ", now snapped back in an unnatural angle ...\n");
              break;
    };
  }
  else
  {
    // Okie, so we did not kill the bastard. But we can still
    // make him sweat a bit, seeing the other nice hits ...

    switch (iHurtPer)
    {
      case -1:
        oMe->catch_msg ("You aim for " + XTPNAME (oMe, oEnemy) + " " + sLocation + ", hitting nothing but thin air.\n");
        oMe->tell_watcher (QCTNAME (oMe) + " swings " + QPOS (oMe) + " fist at " + QTPNAME (oEnemy) + " " + sLocation + ", hitting nothing but thin air.\n", oEnemy);
        oEnemy->catch_msg (XCTNAME (oEnemy, oMe) + " swings " + XPOS (oEnemy, oMe) + " fist at your " + sLocation + ", hitting nothing but thin air.\n");
        break;
      case 0:
	oMe->catch_msg ("You scratch " + XPOS (oMe, oEnemy) + " " + sLocation + " with your plated leather gloves, starting a small trickle of blood.\n");
        oMe->tell_watcher (QCTNAME (oMe) + " scratches " + QTPNAME (oEnemy) + " " + sLocation + ", causing a small trickle of blood to flow.\n", oEnemy);
        oEnemy->catch_msg (XCTNAME (oEnemy, oMe) + " scratches your " + sLocation + ", causing a small trickle of blood to flow.\n");
        break;
      case 1..5:
	oMe->catch_msg ("You pummel " + XTNAME (oMe, oEnemy) + " in the " + sLocation + " with your plated leather gloves.\n");
        oMe->tell_watcher (QCTNAME (oMe) + " pummels " + QTPNAME (oEnemy) + " " + sLocation + " with " + QPOS (oMe) + " plated leather gloves.\n", oEnemy);
	oEnemy->catch_msg (XCTNAME (oEnemy, oMe) + " pummels your " + sLocation + " with " + XPOS (oEnemy, oMe) + " plated leather gloves.\n");
        break;
      case 6..10:
        oMe->catch_msg ("You almost unbalance " + XTNAME (oMe, oEnemy) + " as your plated leather gloves hit " + XPOS (oMe, oEnemy) + " " + sLocation + ".\n");
        oMe->tell_watcher (QCTNAME (oMe) + " almost unbalances " + QTNAME (oEnemy) + " as " + QPOS (oMe) + " plated leather gloves hit " + QTPNAME (oEnemy) + " " + sLocation + ".\n", oEnemy);
        oEnemy->catch_msg (XCTNAME (oEnemy, oMe) + " almost unbalances you as " + XPOS (oEnemy, oMe) + " plated leather gloves hit your " + sLocation + ".\n");
        break;
      case 11..20:
        oMe->catch_msg ("You execute a ferocious blow with your plated leather gloves, hitting " + XTPNAME (oMe, oEnemy) + " " + sLocation + ".\n");
        oMe->tell_watcher (QCTNAME (oMe) + " executes a ferocious blow with " + QPOS (oMe) + " plated leather gloves, hitting " + QTPNAME (oEnemy) + " " + sLocation + ".\n", oEnemy);
        oEnemy->catch_msg (XCTNAME (oEnemy, oMe) + " executes a ferocious blow with " + XPOS (oEnemy, oMe) + " plated leather gloves, hitting your " + sLocation + ".\n");
        break;
      case 21..40:
        oMe->catch_msg (XCTNAME (oMe, oEnemy) + " staggers as you savagely beat your plated leather gloves upon " + XPOS (oMe, oEnemy) + " " + sLocation + ".\n");
        oMe->tell_watcher (QCTNAME (oEnemy) + " staggers as " + QTNAME (oMe) + " savagely beats " + QPOS (oMe) + " plated leather gloves upon " + QPOS (oEnemy) + " " + sLocation + ".\n", oEnemy);
        oEnemy->catch_msg ("You stagger as " + XTNAME (oEnemy, oMe) + " savagely beats " + XPOS (oEnemy, oMe) + " plated leather gloves upon your " + sLocation + ".\n");
        break;
      case 41..60:
        oMe->catch_msg ("You lambaste " + XTPNAME (oMe, oEnemy) + " " + sLocation + " with your plated leather gloves.\n");
        oMe->tell_watcher (QCTNAME (oMe) + " lambastes " + QTPNAME (oEnemy) + " " + sLocation + " with " + QPOS (oMe) + " plated leather gloves.\n", oEnemy);
        oEnemy->catch_msg (QCTNAME (oMe) + " lambastes your " + sLocation + " with " + XPOS (oEnemy, oMe) + " plated leather gloves.\n");
        break;
      case 61..80:
        oMe->catch_msg ("You smash your plated leather gloves upon " + XTPNAME (oMe, oEnemy) + " " + sLocation + ", with a bone crushing sound.\n"); 
        oMe->tell_watcher (QCTNAME (oMe) + " smashes " + QPOS (oMe) + " plated leather gloves upon " + QTPNAME (oEnemy) + " " + sLocation + ", with a bone crushing sound.\n", oEnemy);
        oEnemy->catch_msg (QCTNAME (oMe) + " smashes " + QPOS (oMe) + " plated leather gloves upon your " + sLocation + ", with a bone crushing sound.\n");
        break;
      case 81..90:
        oMe->catch_msg ("You feel several of " + XTPNAME (oMe, oEnemy) + " internal organs burst as you smash your plated leather gloves into " + XPOS (oMe, oEnemy) + " " + sLocation + ".\n");
        oMe->tell_watcher (QCTNAME (oMe) + " breaks several of " + QTPNAME (oEnemy) + " internal organs as " + QPNOUN (oMe) + " smashes " + QPOS (oMe) + " plated leather gloves into " + QPOS (oEnemy) + " " + sLocation + ".\n", oEnemy);
        oEnemy->catch_msg (XCTNAME (oEnemy, oMe) + " breaks several of your internal organs as " + XPNOUN (oEnemy, oMe) + " smashes " + XPOS (oEnemy, oMe) + " plated leather gloves into your " + sLocation + ".\n");
        break;
      default:
        oMe->catch_msg ("Your plated leather gloves mercilessly crush " + XTNAME (oMe, oEnemy) + " to a bloody pulp with a cruel blow into " + XPOS (oMe, oEnemy) + " " + sLocation + ".\n");
        oMe->tell_watcher (QCTNAME (oMe) + " plated leather gloves mercilessly crush " + QTNAME (oEnemy) + " to a bloody pulp with a cruel blow into " + QPOS (oEnemy) + " " + sLocation + ".\n", oEnemy);
        oEnemy->catch_msg (QCTNAME (oMe) + " plated leather gloves mercilesly crush you to a bloody pulp with a cruel blow into your " + sLocation + ".\n");
        break;
    };
  };
}

//-------------------------------------------------------------------
