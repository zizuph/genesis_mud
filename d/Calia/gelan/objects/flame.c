
/*      
    This is a blue magic flame that engulfs players on an attack
    spell being cast by the entrance guard in Gelan. The player
    will continue to be on fire for a random period of time until
    they expire naturally or the player gets burned to death. 

    coder(s):  Maniac 
    history:
              25.2.97    reviewed  - people who claim they 
                         didn't understand that they were on 
                         fire shouldn't have a case now.  
                                                          Maniac 
               1.2.96    bug removed                      Maniac
               2.9.94      Created                        Maniac

    purpose: DAMAGE!!

    quests:     none
    special:    none

    to do:      none
    bug:        none known
*/

inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>
#include <tasks.h>
#include <ss_types.h>
#include "object.h"

#define FLAME_SUBLOC "_flame_subloc"

int strength = 200;      /* strength of flames in damage base hp */
int burn_alarm;    /* Id of alarm that burns the player */
object burn_player;


/* Called from Gamalus if to raise the power of the flames */ 
void
increase_strength()
{
    if (strength <= 200) { 
        strength += 120;
        return;
    } 
    else if (strength <= 320) { 
        strength += 60;
        return;
    } 
    else if (strength <= 380) { 
        strength += 30;
        return;
    } 
}


/*
 * Function name: show_subloc
 * Description:   This function is called each time someone looks at us
 * Arguments:     subloc  - Our subloc
 *                me      - I
 *                for_obj - The looker
 * Returns:       The string the looker shall see
 */
string
show_subloc(string subloc, object me, object for_obj)
{
    int myself;

    if (subloc != FLAME_SUBLOC)
        return 0;

    myself = for_obj == me;
    return (myself ? "You are" : capitalize(me->query_pronoun()) + " is") +
        " burning in an inferno of magical blue flames!\n"; 
}


void
create_object()
{
    set_name("_gelan_magic_flame");
    set_short("blue flames");
    set_long(
        "Some very nasty blue flames!\n"); 
    set_no_show();   /* Don't want people to be able to see in inventory */
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_M_NO_GIVE, 1);
    add_prop(OBJ_I_VOLUME, 0);
}


/* The flames fade and die */
void
fade()
{
   if (burn_alarm) 
       remove_alarm(burn_alarm);
   if (burn_player && (environment(this_object()) == burn_player)) {
       tell_room(environment(burn_player), "The flames around " +
                 QTNAME(burn_player) + " die down and disappear.\n", 
                 burn_player);
       tell_object(burn_player, "The flames around you die down and " +
                                "disappear.\n");
       burn_player->remove_subloc(FLAME_SUBLOC);
       remove_object();
   }
   else {
       burn_player->remove_subloc(FLAME_SUBLOC);
       remove_object();
   }
}


/* The flames burn a player */
void
burn()
{
  int res, damage;

  res = burn_player->query_magic_res(MAGIC_I_RES_FIRE); 
  damage = (strength / 2) + random(strength);
  damage -= ((damage * res) / 100); 

  if (objectp(burn_player) && 
      (environment(this_object()) == burn_player)) {
      tell_room(environment(burn_player), QCTNAME(burn_player) +  
                " screams in agony as the magical blue flames continue to " +
                "burn " + burn_player->query_possessive() + " flesh!\n", 
                burn_player);
      tell_object(burn_player, "You scream in agony as the magical blue " +
                             "flames continue to burn your flesh!\n");
      burn_player->heal_hp(-damage); 
      if (burn_player->query_hp() < 1) {
          burn_player->do_die(this_object());
          remove_object();
          return;
      }
      else if (!random(5))
          set_alarm(4.0, 0.0, fade);
      else 
          burn_alarm = set_alarm(11.0, 0.0, burn);  
  }
  else {
       if (burn_alarm) 
            remove_alarm(burn_alarm);
       burn_player->remove_subloc(FLAME_SUBLOC);
       remove_object();
  }
}



void
enter_env(object dest, object old)
{
  ::enter_env(dest, old);
  if (living(dest)) {
      if (!burn_alarm)
          burn_alarm = set_alarm(2.0, 0.0, burn);  
      burn_player = dest;
      burn_player->add_subloc(FLAME_SUBLOC, this_object());
      tell_room(environment(dest), QCTNAME(burn_player) + " screams as " +
                burn_player->query_pronoun() + " is engulfed in a tower " +
                "of magical blue flames! " + 
                capitalize(burn_player->query_pronoun()) + 
                           " is on fire!\n", burn_player);   
      tell_object(burn_player, 
                    "You scream as you are engulfed in a tower " +
                    "of magical blue flames! You are on fire!\n");
   }
   else 
       remove_object();
}

