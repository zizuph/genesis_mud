/*
* /std/mbase.c
* This is the base file for missile combat
* (bow, sling, crossbow, etc.)
*/
inherit "/std/weapon.c";

#include <wa_types.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <tasks.h>
#include <language.h>
#include <formulas.h>
#include <macros.h>
#include <filter_funs.h>
#include "missile.h"

#define IS_MEMBER(el,ar) (member_array((el),(ar)) >= 0)
#define TASK_HARD 650

static int bow_pen, bow_acc;

string load_verb;
string shoot_verb;
int *aim_penalties;
object target;
int aim_total = -1;

varargs public void disrupt_aim(int silent = 0);
int firing_distant();
int firer_visible();
int can_see_distant(object one, object two);
string * distant_descs(object from, object to);
object * possible_targets(object for_ob);

/*
* Function:      set_bow_pen()
* Description:   Sets the damage this projectile weapon does
* Arguments:     int pen
* Returns:       void
*/
public void
set_bow_pen(int pen)
{ bow_pen = pen; }

/*
* Function:      query_bow_pen
* Description:   The damage this projectile weapon does
*/
public int
query_bow_pen()
{ return bow_pen; }

/*
* Function:      set_bow_acc()
* Description:   Sets how accurate this weapon is
* Arguments:     int acc
* Returns:       void
*/
public void
set_bow_acc(int acc)
{ bow_acc = acc; }

/*
* Function:      query_bow_acc
* Description:   How accurate this weapon is
*/
public int
query_bow_acc()
{ return bow_acc; }

/*
* Function:     check_under_attack
* Description:  Is this player being attacked by someone?
* Arguments:    object player
* Returns:      0 If not, 1 If yes
*/
public int
check_under_attack(object player)
{
   object *enemies;
   int x;
   
   enemies = player->query_enemy(-1);
   for(x = 0; x < sizeof(enemies); x++)
   {
      if(!enemies[x]->query_prop(LIVE_I_STUNNED) &&
            !enemies[x]->query_prop(LIVE_I_ATTACK_DELAY))
      {
         if(enemies[x]->query_attack() == player)
            return 1;
       }
   }
   return 0;
}

/*
* Function:      can_attack
* Description:   Can the bow-wielder attack this target?
* Arguments:     object attacker
*                object target
* Returns:       0 If can't, 1 If can
*/
public int
can_attack(object attacker, object target)
{
   mixed temp;
   
   if(!attacker || !target)
      return 0;
   
   /* You can always attack someone you're fighting. */
   if(member_array(attacker,target->query_enemy(-1)) >= 0)
      return 1;
   
   if(temp = (target->query_prop(OBJ_M_NO_ATTACK)))
      {
      notify_fail(
            ( stringp(temp) ? temp : "You can't attack " +
            target->query_objective() +".\n" )
      );
      return 0;
   }
   
   notify_fail("Umm... no, You do not have enough self-"+
         "discipline to dare!\n");
   if(!F_DARE_ATTACK(attacker,target))
      return 0;
   
   notify_fail("You cannot attack an immortal.\n");
   if(!attacker->query_wiz_level() &&
         target->query_wiz_level())
   return 0;
   
   return 1;
}

/*
* Function:     set_shoot_verb
* Description:  sets the verb used to shoot this weapon
* Arguments:    string verb
* Returns:      void
*/
void
set_shoot_verb(string verb)
{ shoot_verb = ( strlen(verb) ? verb : "loose" ); }

/*
* Function:     query_shoot_verb
* Description:  the verb used to shoot this weapon
*/
public string
query_shoot_verb()
{ return shoot_verb; }

/*
* Function:     set_aim_penalties
* Description:  sets the penalties associated with various aim times
* Arguments:    int *aim_penalties
*               ({ no aiming, aim typed, 5 sec., 10 sec., 15 sec. })
* Returns:      (int) 1 If valid argument, 0 otherwise
*/
public int
set_aim_penalties(int *arr)
{
   if(sizeof(arr) != 5)
      return 0;
   
   aim_penalties = arr;
}

/*
* Function:     query_aim_penalties
* Description:  the penalties associated with various aim times
*/
public int *
query_aim_penalties()
{ return aim_penalties; }

/*
* Function:     disrupt_aim
* Description:  Causes the wielder to lose her aim on her target
* Arguments:    int silent
* Returns:      void
*/
varargs public void
disrupt_aim(int silent = 0)
{
   mixed aim_alarms;
   int x;
   
   if(!silent && (aim_total >= 0))
      query_wielded()->catch_msg("You lose your aim.\n");
   target = 0;
   aim_total = -1;
   
   /* Find and kill any aim-related alarms */
   aim_alarms = get_all_alarms();
   for(x = 0; x < sizeof(aim_alarms); x++)
   {
      if(aim_alarms[x][1] == "aim_improve" ||
            aim_alarms[x][1] == "aim_check_LOS")
      remove_alarm(aim_alarms[x][0]);
   }
}

void
get_me_a_target(string str)
{
   mixed livings;
   object *obj_list;
   
   target = 0;
   
   notify_fail("Aim at whom?\n");
   /* check for out of room targets added -- Falke 10/25/95 */
   obj_list = possible_targets(query_wielded());
   if(!parse_command(str,obj_list, "[at] [for] [the] [a] [an] %l",livings))
      return;
   
   notify_fail("It's hard to aim at more than one thing at once.\n");
   if(livings[0] == 0)
      return;
   if(livings [0] > 1)
      return;
   
   notify_fail("There aren't that many to choose from.\n");
   livings[0] = ABS(livings[0]);
   if(livings[0] > (sizeof(livings) - 1))
      return;
   
   target = livings[livings[0]];
   
   notify_fail("But that's you!\n");
   if(target == this_player())
      target = 0;
   
}

/*
* Function:     aim
* Description:  called from init - aim at a target
* Arguments:    string str
* Returns:      0/1 (standard action)
*/
public int
aim(string str)
{
   notify_fail("You're not wielding a missile weapon.\n");
   if(query_wielded() != this_player())
      return 0;
   
   notify_fail("But you're under attack!\n");
   if(check_under_attack(this_player()))
      return 0;
   
   if(!this_object()->aim_consider())
      return 0;
   
   get_me_a_target(str);
   if(!target)
      {
      return 0;
   }
   
   if(!can_attack(this_player(),target))
      return 0;
   
   write("You aim " +
      (firing_distant() ?
         distant_descs(this_player(),target)[0]  + " " :
         "") +
      "at " + target->query_name() + ".\n");
   if(!firing_distant())
      {
      tell_room(environment(this_player()),
         QCTNAME(this_player()) + " aims " +
         LANG_ADDART(short()) + " at " + QTNAME(target) + ".\n",
         ({ target, this_player() }) );
      target->catch_msg(QCTNAME(this_player()) + " aims " +
         LANG_ADDART(short()) + " at you.\n");
   }
   else
      {
      object * cansee;
      
      // FIRER'S ROOM
      
      cansee = FILTER_LIVE(all_inventory(environment(this_player())));
      cansee -= ({ this_player() });
      cansee->catch_msg(QCTNAME(this_player()) + " aims " +
         LANG_ADDART(short()) + " " +
         distant_descs(this_player(),target)[0]);
      filter(cansee, &can_see_distant(,target))->
      catch_msg(" at " + QTNAME(target));
      cansee->catch_msg(".\n");
      
      // TARGET'S ROOM
      
      cansee = FILTER_LIVE(all_inventory(environment(target)));
      cansee = filter(cansee, &can_see_distant(,this_player()));
      
      cansee->catch_msg(QCTNAME(this_player()) + " aims " +
         LANG_ADDART(short()) + " at ");
      if (IS_MEMBER(target, cansee))
         target->catch_msg("you");
      
      (cansee - ({ target }))->catch_msg(QTNAME(target));
      
      cansee->catch_msg(" " + distant_descs(this_player(),
            target)[1] + ".\n");
   }
   
   set_alarm(1.0,0.0,"aim_check_LOS");
   aim_total = 0;
   set_alarm(4.0,0.0,"aim_improve");
   return 1;
}

/*
* Function:      aim_check_LOS
* Description:   checks that the target is still valid
* Arguments:     none
* Returns:       nothing
*                (alarms itself to check the target again)
*/
void
aim_check_LOS()
{
   if(!target)
      disrupt_aim();
   
   if(!query_wielded())
      disrupt_aim();
   
   if(check_under_attack(this_player()))
      disrupt_aim();
   
   if(!IS_MEMBER(target, possible_targets(query_wielded())))
      {
      query_wielded()->catch_msg(QCTNAME(target) + " moves out of " +
         "your line of sight.\n");
      disrupt_aim(1);
   }
   
   if(!target)
      return;
   
   set_alarm(1.0,0.0,"aim_check_LOS");
}

/*
* Function:    aim_improve
* Description: moves the aim quality up to the next level
* Arguments:   none
* Returns:     none (alarms itself)
*/
varargs public void
aim_improve()
{
   if(aim_total < 4)
      aim_total++;
   /*
   query_wielded()->catch_msg("Your aim reaches level " +
      aim_total+".\n");
   */
   set_alarm(4.0,0.0,"aim_improve");
}

/*
* Function:     break_aim
* Description:  Causes the player's aim to be broken
*               by any action other than the shoot verb
* Arguments:    none
* Returns:      0 (so the other action may take place)
*/
int
break_aim()
{
   if(!target)
      return 0;
   
   if(query_verb() == "lower")
      {
      write("You lower your "+short()+".\n");
      say(QCTNAME(this_player())+" lowers "+this_player()->query_possessive() +
         " "+short()+".\n");
      disrupt_aim(1);
      return 1;
   }
   if(query_verb() != shoot_verb && query_verb() != "shoot")
      disrupt_aim();
   return 0;
}

/*
* Function:    hit_target
* Description: Determines If the fired shot hit the target
* Returns:     1 If hit, 0 otherwise
*/
public int
hit_target()
{
   int difficulty;
   int success;
   int aim_mod, f_enc, t_enc;
   object firer = query_wielded();
   int target_room_mods = environment(target)->query_room_target_mods(
      environment(firer), target);
   int firer_room_mods = environment(firer)->query_room_firer_mods(
      environment(target), firer);
   
   aim_mod = ( aim_total < 0 ? aim_penalties[0] :
      aim_penalties[aim_total] );
   
   f_enc = (this_player()->query_encumberance_volume() +
      this_player()->query_encumberance_weight()) / 2;
   
   t_enc = (target->query_encumberance_volume() +
      target->query_encumberance_weight()) / 2;
   
   difficulty = TASK_HARD - aim_mod - bow_acc -
      this_object()->fire_difficulty_consider() + f_enc;
   difficulty += target_room_mods + firer_room_mods;
   
   success = this_player()->resolve_task(difficulty,
         ({ TS_DEX, SS_WEP_MISSILE }),
      target,
      ({ SKILL_WEIGHT, 100 - t_enc, SS_DEFENSE,
            SKILL_WEIGHT, 100 - t_enc, SS_ACROBAT }) );
   
   return (success >= 0);
}

/*
* Function:       query_damage
* Description:    how much damage this weapon does
* Arguments:      none
* Returns:        the damage
*/
public int
query_damage()
{
   return bow_pen;
}

/*
* Function:      hurt_target
* Description:   Having hit the target, hurt it
*/
public void
hurt_target()
{
   int damage, mskill, ammo_dt;
   mixed result;
   string hit_msg = "";
   
   damage = this_object()->query_damage();
   mskill = this_player()->query_skill(SS_WEP_MISSILE);
   damage = F_PENMOD(damage, mskill);
   ammo_dt = this_object()->query_ammo_dt();
   
   result = target->hit_me(damage,ammo_dt,this_player(),-1);
   
   this_object()->hurt_message(result);
}

/*
* Function:      shoot_consider
* Description:   Any extra considerations for allowing shooting
* Returns:       1 If allowed, 0 otherwise
*/
public int
shoot_consider()
{
   return 1;
}

/*
* Function:      shoot
* Description:   Player shoots another living.
* Arguments:     string str
* Returns:       0/1 (standard action)
*/
public int
shoot(string str)
{
   int delay_target;
   
   notify_fail("You're not wielding a missile weapon.\n");
   if(!query_wielded())
      return 0;
   
   notify_fail("But you're under attack!\n");
   if(check_under_attack(this_player()))
      return 0;
   
   if(!this_object()->shoot_consider())
      return 0;
   
   if(str)
      {
      object previous_target = target;
      get_me_a_target(str);
      if(target != previous_target)
         {
         disrupt_aim();
         get_me_a_target(str);
      }
   }
   
   if(!can_attack(this_player(),target))
      return 0;
   
   notify_fail(capitalize(query_verb())+" at whom?\n");
   if(!target)
      return 0;
   
   notify_fail("Your target has left your sight.\n");
   if(!IS_MEMBER(target,possible_targets(this_player())))
      {
      disrupt_aim();
      return 0;
   }
   
   /* Now get on with the business of shooting */
   
   this_object()->shoot_message();
   
   if(!sizeof(target->query_enemy(-1)))
      {
      delay_target = 1;
   }
   
   if(hit_target())
      hurt_target();
   else
      this_object()->miss_message();
   
   this_object()->shoot_post_message();
   
   this_player()->attack_object(target);
   
   query_wielded()->add_attack_delay(DELAY_WIELDER,1);
   
   if(delay_target)
      {
      target->add_attack_delay(DELAY_TARGET,0);
   }
   
   /*
   write("Your delay is currently " +
      query_wielded()->query_prop(LIVE_I_ATTACK_DELAY) + 
      " seconds;  your target's is " +
      target->query_prop(LIVE_I_ATTACK_DELAY) + " seconds.\n");
   */
   
   if(target->query_hp() < 1)
      target->do_die(this_player());
   
   disrupt_aim(1);
   return 1;
}

// Distance code

/*
* Function:     firing_distant
* Description:  Determines If the firer is firing through a link
*/
int
firing_distant()
{
   return environment(this_player()) != environment(target);
}

int _fv_locked = 0;  // Locks the firer_visible value to prevent
// prevent unnecessary recalulation
int _fv_prev = 0;  // Stores the last value of firer_visible

void
lock_fv()
{
   firer_visible();
   _fv_locked = 1;
}
void unlock_fv() { _fv_locked = 0; }

/*
* Function:       firer_visible
* Description:    Determines If the firer is visible in the distance
*/
int
firer_visible()
{
   mixed arr;
   int x;
   
   // If the value is locked, return the saved value
   if(_fv_locked)
      return _fv_prev;
   
   if(!firing_distant())
      return _fv_prev = 1;
   
   arr = environment(this_player())->query_other_missile_rooms();
   for(x = 0; x < sizeof(arr); x++)
   {
      mixed mroom = arr[x][0];
      if(stringp(mroom))
         mroom = find_object(mroom);
      
      if(mroom == environment(target))
         return _fv_prev = arr[x][3];
   }
   
   return _fv_prev = 0;
}

int
can_see_distant(object one, object two)
{
   if(!firing_distant())
      return 1;
   if(environment(one) == environment(two))
      return 1;
   return IS_MEMBER(two,
      environment(one)->query_valid_targets(one));
}

string *
distant_descs(object from, object to)
{
   mixed arr = environment(from)->query_other_missile_rooms();
   int x;
   
   for(x = 0; x < sizeof(arr); x++)
   {
      mixed mroom = arr[x][0];
      if(stringp(mroom))
         mroom = find_object(mroom);
      
      if(mroom == environment(to))
         return arr[x][1..2];
   }
   return ({ "from /dev/null", "into /dev/null" });
}

object *
possible_targets(object for_ob)
{
   mixed *v_targets;
   if(!for_ob)
      return ({ });
   
   v_targets = environment(for_ob)->query_valid_targets(for_ob);
   if (!pointerp(v_targets))
      v_targets = ({ });
   return all_inventory(environment(for_ob)) +
     v_targets;
}
