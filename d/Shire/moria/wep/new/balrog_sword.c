/*
*  Balrog's sword
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

int s_power = 0;
int second_attack = 0;

void
create_weapon()
{
    set_name("sword");
    add_name( ({ "cleaver", "_balrog_sword" }) );
    set_adj( ({"giant", "black"}) );

    set_short("giant black sword");
    set_long("This "+ short() +" glows with a fiery-red aura of magic. "
           + "A massive hilt is shaped as two glowing horns, the blade "
           + "itself is unadorned, no markings can be found.\n");

    set_default_weapon(60, 60, W_SWORD, W_SLASH | W_IMPALE, W_BOTH, 0);
    set_wf(this_object());

    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC, ({"enchantment", 50}) );
    add_prop(MAGIC_AM_ID_INFO, ({"This sword glows with a fiery-red aura "
                               + "of magic.\n", 20, 
                                 "Forged in darkness and christened Calris, "
                               + "the Light Cleaver.\n", 50}));

    add_prop(OBJ_I_VOLUME, 12200);
    add_prop(OBJ_I_WEIGHT, 26600); /* 26.6 kg */
    add_prop(OBJ_I_VALUE,  3*F_VALUE_WEAPON(60, 60) + random(1000) - 500);
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_S_WIZINFO, "The legendary sword of the Balrog of Moria.\n");

}

/*
 * Function name: set_sword_power()
 * Description  : Sets the sword power.
 */
int
set_sword_power(int i)
{
    s_power = i;
}

/*
 * Function name: query_wword_power()
 * Description  : Return the sword power.
 */
int
query_sword_power(int i)
{
    return s_power;
}

init()
{
    ::init();
    add_action("do_wield", "wield");
}

int
do_wield()
{
    TO->query_hands();
    return 0;
}

int
query_hands()
{
    if (TP->query_real_name() == "gash")
        return wep_hands = W_ANYH;
    else
        return wep_hands = W_BOTH;
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

  // Better stats if wielded by the Balrog
  if(TP->query_real_name() == "gash")
  {
    this_object()->set_hit(100);
    this_object()->set_pen(100);
  }

  TP->catch_msg("You wrap your hand around the hilt of the " 
        + this_object()->short() + ". Flames emerges "
        + "from the " + this_object()->short() + ", in seconds, a yellow flame " 
        + "consumes it entirely.\n");

  say(QCTNAME(this_player()) + " wraps " + HIS_HER(this_player()) 
           + " hand around the hilt of the " + this_object()->short() 
           + " wielding it. Yellow flames emerges from the " 
           + this_object()->short() + ", consumes it entirely.\n", 
           this_player());

  remove_adj( ({"giant", "black"}) );
  set_adj( ({"flaming", "giant"}) );
  set_short("flaming giant sword");
  set_long("The "+ short() +" is swirling with wild yellow flames, tendrils of "
         + "smoke is reaching desperately into the sky. The flames consuming "
         + "the " + short() + " burns hot, short and violent. @@check_power@@\n");  
  TP->update_weapon(wep);

  return 1;   
}

public mixed
unwield(object wep)
{

  object wielder = objectp(query_wielded()) ? query_wielded() : this_player(); 

  this_object()->set_hit(60);
  this_object()->set_pen(60);

  wielder->catch_msg("You unwrap your hand from the hilt of the " 
        + this_object()->short() + ". Flames release from the blade, "
        + "spiraling down full length of the " 
        + this_object()->query_name() + ".\n");

  say(QCTNAME(wielder) + " unwraps " + HIS_HER(wielder) + " hand from "
            + "the hilt of the " + this_object()->short() + " releasing "
            + "it. Flames release from the hilt, spiraling the full "
            + "length of the " + this_object()->query_name()  
            + ".\n", wielder);

  remove_adj( ({"flaming", "giant"}) );
  set_adj( ({"giant", "black"}) );
  set_short("giant black sword");
  set_long("This "+ short() +" glows with a fiery-red aura of magic. "
           + "A massive hilt is shaped as two glowing horns, the blade "
           + "itself is unadorned, no markings can be found.\n");
  wielder->update_weapon(wep);
  return 1;
}

int
strike_enemy(object enemy, string hit_loc, int dam)
{
  if(!second_attack)
    return 0;

  object wielder = query_wielded();
  
  int res = enemy->query_magic_res(MAGIC_I_RES_FIRE);
  dam = dam - (res*dam/100);
  string hurt;

  second_attack = 0;

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
                    + this_object()->short() + " does not harm you.\n");
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
    string sword;
    int power;

    tp = this_object()->query_wielded();
    sword = this_object()->short();

    this_object()->set_sword_power(this_object()->query_sword_power() + 1);

    power = this_object()->query_sword_power();

    if (enemy->query_hp() <= 0)
    {
        tp->catch_msg(QCTNAME(enemy) + " screams in pain as the terrible "
                      + "tip of your " + sword + " cuts " 
                      + HIS_HER(enemy) + " " + hdesc + " severely!\n");
        enemy->catch_msg("You scream in pain as " + QTPNAME(enemy) 
                       + " terrible " + sword +  " cuts your " 
                       + hdesc + " severely!\n");
        tp->tell_watcher(QCTNAME(enemy) + " screams in pain as the terrible "
                     + "flick of " + QTPNAME(tp) + " " + sword + " cuts " 
                     + HIM_HER(enemy) + " severely!\n", enemy);
        enemy->do_die(tp);
    }
      else
    {
        switch (phurt)
        {
        case -1:
            case -2:
        tp->catch_msg("You arc your " + sword + " towards " + QTNAME(enemy) 
                    + ", but it miss " + HIS_HER(enemy)  + " head.\n");
        enemy->catch_msg(QCTNAME(tp)+" arcs " + HIS_HER(tp) + " " 
                   + sword + " towards you, but it misses your head.\n");
        tp->tell_watcher_miss(QCTNAME(tp)+" arcs " + HIS_HER(tp) + " " 
                   + sword + " towards " + QTNAME(enemy) + ", but it misses "
                   + HIS_HER(tp) + " head.\n", enemy);
        break;
        case 0:
        tp->catch_msg("You tickle " + QTPNAME(enemy) + " " + hdesc + ", but the " 
                      + sword + " does not harm " + HIM_HER(enemy) + ".\n");
        enemy->catch_msg(QCTNAME(tp) + " tickles your " + hdesc + ", but the "
                      + sword + " does not harm you.\n");
        tp->tell_watcher(QCTNAME(tp) + " tickles " + QTPNAME(enemy) + " " 
                      + hdesc + ", but the " + sword + " does not harm " 
                      + HIM_HER(enemy) + ".\n", enemy);
        break;
        case 1..10:
        tp->catch_msg("You slash your " + sword + " against " + QTNAME(enemy) 
                      + ", grazing " + HIS_HER(enemy) + " " 
                      + hdesc + ".\n");
        enemy->catch_msg(QCTNAME(tp) + " slashes " + HIS_HER(tp) + " " 
                      + sword + " against you, grazing your " + hdesc + ".\n");
        tp->tell_watcher(QCTNAME(tp) + " slashing " + HIS_HER(tp) + " " 
                      + sword + " against " + QTNAME(enemy) + ", grazing " 
                      + HIS_HER(enemy) + " " + hdesc + ".\n", enemy);
        break;
        case 11..30:
        tp->catch_msg("Your " + sword + " rip against " + QTPNAME(enemy) 
                      + " " + hdesc + ", hurting " + HIM_HER(enemy) 
                      + " with an accurately swing.\n");
        enemy->catch_msg(QCTPNAME(tp) + " " + sword + " rips against your " 
                      + hdesc + ", hurting you with an accurately swing.\n");
        tp->tell_watcher(QCTPNAME(tp) + " " + sword + " ripping against " 
                      + QTPNAME(enemy) + " " + hdesc + ", hurting " 
                      + HIM_HER(enemy) + " with an accurately "
                      + "swing.\n", enemy);
        break;
        case 31..50:
        tp->catch_msg("You gash " + QTNAME(enemy) + " as your " 
                      + sword + " delivers a " + "painful blow to " 
                      + HIS_HER(enemy) + " " + hdesc + ".\n");
        enemy->catch_msg(QCTNAME(tp) + " gashes you as " + HIS_HER(tp) 
                      + " " + sword + " delivers a painful blow to your " 
                      + hdesc + ".\n");
        tp->tell_watcher(QCTNAME(tp) + " gashing " + QTNAME(enemy) + " as " 
                      + HIS_HER(tp) + " " + sword + " delivers a painful blow "
                      + "to " + QTPNAME(enemy) + " " + hdesc + ".\n", enemy);
        break;
        default:
        case 51..100:
        tp->catch_msg("A chill sound penetrates your ears as your " + sword 
                    + " cleave " + QTPNAME(enemy) + " " + hdesc + ", causing "
                    + "intense pain!\n");
        enemy->catch_msg("A chill sound penetrates your ears as " 
                    + QTPNAME(tp) + " " + sword + " cleaves your " 
                    + hdesc + ", causing intense pain!\n");
        tp->tell_watcher("A hill sound penetrates your ear as " + QTPNAME(tp) 
                    + " " + sword + " cleaves " + QTPNAME(enemy) + " " 
                    + hdesc + ", causing intense pain!\n", enemy);
        break;
        }
        strike_enemy(enemy, hdesc, dam);

        if(power >= 3)
        { 
          find_living("znagsnuf")->catch_tell("DEBUG: UNLEASH FIRE!\n");
          second_attack = 1;
          strike_enemy(enemy, hdesc, dam);
          this_object()->set_sword_power(0);
        }
    }
     return 1;
}

/*
 * Function name: check_power
 * Description  : as simple as that
*/
public string
check_power()
{

    int sword_power = this_object()->query_sword_power();

    if(sword_power > 3)
        sword_power = 3;

    switch (sword_power)
    {
    case 0:
        return "Zero orbs";
        break;
    case 1:
        return "One orb";
        break;
    case 2:
        return "Two orbs";
        break;
    case 3:
        return "Three orbs";
        break;
    }
    return "";
}