/*
*  Balrog's whip
*
*  Using the hit messages from the old whip.
*
*
*  Created by Znagsnuf.
*
*
*  Date:                      What is done:                            By whom:            
*  ----------------------------------------------------------------------------
*  01/05-17                   Started remaking it                      Znagsnuf
*
*
*/

inherit "/std/weapon";

#include <wa_types.h>
#include <ss_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>

#include "/d/Gondor/defs.h"

#define BWHIP_STUN   "/d/Shire/moria/wep/new/whip_stun"

void
create_weapon()
{
    set_name("whip");
    add_name( ({ "crimson", "_balrog_whip" }) );

    set_adj("red");
    add_adj("crimson");

    set_short("red crimson whip");
    set_long("This "+ short() +" is warm to hold, a bright menacing flame is "
           + "visible within. Toxic fumes shoots up into the air every few "
           + "seconds. ");

    set_default_weapon(60, 60, W_CLUB, W_SLASH | W_BLUDGEON, W_RIGHT, 0);

    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC, ({ 70, "enchantment" }));
    add_prop(MAGIC_AM_ID_INFO, ({ "The whip seems to be magical.\n", 1,
                                  "The flames will hinter your target "
                                  + "when wrapped around the legs.\n", 70 }));

    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(60,60) + random(1000));
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_WEIGHT, 4800); /* 4.8 kg */

    add_prop(OBJ_S_WIZINFO,
              "The legendary whip on the Balrog. Will hinter movement when "
            + "the whip wraps around the legs on the target.\n");

    set_wf(this_object());
}

void set_likely_dull(int i) { likely_dull = 0; }
void set_likely_break(int i) { likely_break = 0; }
void set_likely_corr(int i) { likely_corr = 0; }

varargs void
remove_broken(int silent = 0)
{
     return;
}

int
set_dull(int du)
{
    return 0;
}

/*
 * Function name: wield
 * Description:   Wield a weapon
 * Arguments:     The weapon to wield
 * Returns:       string - error message (weapon not wielded)
 *                1 - success (weapon wielded)
 */
public mixed
wield(object wep)
{
  if(TP->query_real_name() == "gash")
  {
    this_object()->set_hit(100);
    this_object()->set_pen(100);
  }

  TP->catch_msg("Flash of scorching flames bursts out from the whip, " 
              + "engulfing the " + short() + " in deadly fire.\n");

  say(QCTNAME(this_player()) + " wraps " + HIS_HER(this_player()) 
               + " hand around the hilt of the " 
               + this_object()->short() + " wielding it in " 
               + HIS_HER(this_player()) + " right hand. Flash of scorching "
               + "flames bursts out from the whip, engulfing the "
               + short() + " in deadly fire.\n", this_player());

  remove_adj( ({ "red", "crimson" }) );
  set_adj("flaming");
  set_short("flaming whip");
  set_long("The "+ short() +" is swirling with ferocious flames. The fire "
         + "flickering like the vicious tongue of a snake poised in hatred "
         + "waiting to strike.\n");  
  TP->update_weapon(wep);
  return 1;   
}

public mixed
unwield(object wep)
{
  this_object()->set_hit(60);
  this_object()->set_pen(60);

  object wielder = objectp(query_wielded()) ? query_wielded() : this_player(); 

  wielder->catch_msg("You unwrap your hand from the hilt of the " 
                     + this_object()->short() + ", releasing it "
                     + "from your right hand. A plume of fire explodes into "
                     + "the blackness, the flame rolling outwards like the "
                     + "smoke of a mushroom cloud.\n");

  say(QCTNAME(wielder) + " unwraps " + HIS_HER(wielder) + " hand "
                       + "around the hilt of "
                       + "the " + this_object()->short() + " releasing "
                       + "it from " + HIS_HER(wielder) + " right "
                       + "hand. A plume of fire explodes into "
                       + "the blackness, flames rolling outwards like the "
                       + "smoke of a mushroom cloud.\n", wielder);

  remove_adj("flaming");
  set_adj( ({ "red", "crimson" }) );
  set_short("red crimson whip");
  set_long("This " + short() + " is warm to hold, a bright menacing flame is "
           + "visible within. Toxic fumes shoots up into the air every few "
           + "seconds. ");
  wielder->update_weapon(wep);
  return 1;
}

int
lock_enemy(object enemy, string hit_loc, int dam)
{
  object stun, wielder = query_wielded();
  int stun_duration, res = enemy->query_magic_res(MAGIC_I_RES_FIRE);
  dam = dam - (res*dam/100);
  string hurt;

  // Only works if the hit loc is the legs.
  if(hit_loc == "legs")
  {
    
    setuid();
    seteuid(getuid());

    enemy->catch_tell("The flames snatch around your " 
                 + (random(2) ? "left" : "right") + " leg!\n");

    tell_room(environment(wielder), "Wild flames wraps around " + QTNAME(enemy) 
                   + ", snatching " + enemy->query_possessive() 
                   +  (random(2) ? " left" : " right") + " leg!!\n", enemy);

    stun_duration = (dam / 10);

    if(stun_duration < 5)
        stun_duration = 5;

    if(stun_duration > 15)
        stun_duration = 15;

    enemy->add_attack_delay(stun_duration);

    if(!random(2))
    {
      stun = clone_object(BWHIP_STUN);
      stun-> set_remove_time(max(5, random(10)));
      stun-> set_target(enemy);

      if (stun->move(enemy))
          stun->move(enemy, 1);  
    }
  }

  // An extra chance if the Balrog is the wielder 
  if(!random(3))
  {  
    if(wielder->query_real_name() == "gash")
    {
    
      setuid();
      seteuid(getuid());

      enemy->catch_tell("The flames whips around your body! Licking "
        + "your " + hit_loc + ".\n");

      tell_room(environment(wielder), "Wild flames wraps around " + QTNAME(enemy) 
                   + ", licking "+ HIS_HER(enemy) +" body!\n", enemy);

      stun_duration = (dam / 10);

      if(stun_duration < 5)
          stun_duration = 5;

      if(stun_duration > 15)
         stun_duration = 15;

      enemy->add_attack_delay(stun_duration);

      if(!random(2))
      {
        stun = clone_object(BWHIP_STUN);
        stun-> set_remove_time(MAX(5, random(15)));
        stun-> set_target(enemy);

        if (stun->move(enemy))
            stun->move(enemy, 1);   
      }    
    }
  }

  switch(dam)
  {
    case 1..10:
      hurt = "weak";
    break;
    case 11..40:
      hurt = "light";
    break;
    case 41..60:
      hurt = "slight";
    break;
    case 61..80:
      hurt = "powerful";
    break;
    case 81..100:
      hurt = "fierce";
    break;
    case 101..150:
      hurt = "extreme";
    break;
    case 151..200:
      hurt = "severe";
    break;
    default:
      hurt = "intense";
    break;
  }

  if (dam < 1) 
  {
    enemy->catch_msg("The swirling flames surrounding the "
                    + this_object()->short() + " do not harm you.\n");
    return 1;
  }

  enemy->heal_hp(-dam);
  enemy->catch_tell("The swirling flames wraps around you, causing "
                  + hurt +" pain!\n");

  wielder->catch_msg("The swirling flames from the " 
                    + this_object()->short() + " wraps around "
                    + QTNAME(enemy) + " causing " + hurt +" pain!\n");

  wielder->tell_watcher("The swirling flames from the "
                      + this_object()->short() + " wraps around "
                      + QTNAME(enemy) + " causing "+ hurt + " pain!"
                      +"\n", enemy);
  return 1;
}

/*
 * Function name: did_hit
 * Description  : This function merely checks if the bow is
 *                stringed and delegates to launch_weapon.
 *                If the bow is not stringed it returns 0
 *                and behaves like a normal weapon.
 */

public varargs int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt, 
        int phit, int dam)
{
    object tp;
    string whip;

    tp = this_object()->query_wielded();
    whip = this_object()->short();

    if (enemy->query_hp() <= 0)
    {
        tp->catch_msg(QCTNAME(enemy) + " screams in pain as the terrible "
                      + "flick of your " + whip + " flails " 
                      + HIS_HER(enemy) + " " + hdesc + " severely!\n");
        enemy->catch_msg("You scream in pain as " + QTPNAME(enemy) 
                       + " terrible " + whip +  " flails your " 
                       + hdesc + " severely!\n");
        tp->tell_watcher(QCTNAME(enemy) + " screams in pain as the terrible "
                     + "flick of " + QTPNAME(tp) + " " + whip + " flails " 
                     + HIM_HER(enemy) + " severely!\n", enemy);
        enemy->do_die(tp);
    }
      else
    {
        switch (phurt)
        {
        case -1:
            case -2:
        tp->catch_msg("You snap your " + whip + " towards " + QTNAME(enemy) 
                    + ", but it whistles above " + HIS_HER(enemy) 
                    + " head.\n");
        enemy->catch_msg(QCTNAME(tp)+" snaps " + HIS_HER(tp) + " " 
                   + whip + " towards you, but it whistles above your "
                   + "head.\n");
        tp->tell_watcher_miss(QCTNAME(tp)+" snaps " + HIS_HER(tp) + " " 
                   + whip + " towards " + QTNAME(enemy) + ", but it whistles "
                   + "above " + HIS_HER(tp) + " head.\n", enemy);
        break;
        case 0:
        tp->catch_msg("You whip " + QTPNAME(enemy) + " " + hdesc + ", but the " 
                      + whip + " does not harm " + HIM_HER(enemy) + ".\n");
        enemy->catch_msg(QCTNAME(tp) + " whips your " + hdesc + ", but the "
                      + whip + " does not harm you.\n");
        tp->tell_watcher(QCTNAME(tp) + " whips " + QTPNAME(enemy) + " " 
                      + hdesc + ", but the " + whip + " does not harm " 
                      + HIM_HER(enemy) + ".\n", enemy);
        break;
        case 1..10:
        tp->catch_msg("You snap your " + whip + " against " + QTNAME(enemy) 
                      + ", " + "grazing " + HIS_HER(enemy) + " " 
                      + hdesc + ".\n");
        enemy->catch_msg(QCTNAME(tp) + " snaps " + HIS_HER(tp) + " " 
                      + whip + " against you, grazing your " + hdesc + ".\n");
        tp->tell_watcher(QCTNAME(tp) + " snaps " + HIS_HER(tp) + " " 
                      + whip + " against " + QTNAME(enemy) + ", grazing " 
                      + HIS_HER(enemy) + " " + hdesc + ".\n", enemy);
        break;
        case 11..30:
        tp->catch_msg("Your " + whip + " lashes against " + QTPNAME(enemy) 
                      + " " + hdesc + ", hurting " + HIM_HER(enemy) 
                      + " with a sharp cracking sound.\n");
        enemy->catch_msg(QCTPNAME(tp) + " " + whip + " lashes against your " 
                      + hdesc + ", hurting you with a sharp cracking "
                      + "sound.\n");
        tp->tell_watcher(QCTPNAME(tp) + " " + whip + " lashes against " 
                      + QTPNAME(enemy) + " " + hdesc + ", hurting " 
                      + HIM_HER(enemy) + " with a sharp cracking "
                      + "sound.\n", enemy);
        break;
        case 31..50:
        tp->catch_msg("You flog " + QTNAME(enemy) + " as your " 
                      + whip + " delivers a " + "painful blow to " 
                      + HIS_HER(enemy) + " " + hdesc + ".\n");
        enemy->catch_msg(QCTNAME(tp) + " flogs you as " + HIS_HER(tp) 
                      + " " + whip + " delivers a painful blow to your " 
                      + hdesc + ".\n");
        tp->tell_watcher(QCTNAME(tp) + " flogs " + QTNAME(enemy) + " as " 
                      + HIS_HER(tp) + " " + whip + " delivers a painful blow "
                      + "to " + QTPNAME(enemy) + " " + hdesc + ".\n", enemy);
        break;
        default:
        case 51..100:
        tp->catch_msg("A loud crack pierces the air as your " + whip 
                    + " smacks " + QTPNAME(enemy) + " " + hdesc + ", causing "
                    + "intense pain!\n");
        enemy->catch_msg("A loud crack pierces the air as " + QTPNAME(tp) 
                    + " " + whip + " smacks your " + hdesc + ", causing "
                    + "intense pain!\n");
        tp->tell_watcher("A loud crack pierces the air as " + QTPNAME(tp) 
                    + " " + whip + " smacks " + QTPNAME(enemy) + " " 
                    + hdesc + ", causing intense pain!\n", enemy);
        break;
        }
        lock_enemy(enemy, hdesc, dam);
     }
     return 1;
}