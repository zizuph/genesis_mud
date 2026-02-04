
/*      
    burning oil for the gates guards of Calahtin to use.
    Taken originally from Maniac of Calia, flame.c
    Modified for use with the guards and Calathin.

    Shinto of Terel 
    080299
*/

inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>
#include <tasks.h>
#include <ss_types.h>

#define FLAME_SUBLOC "_flame_subloc"

int strength = 50;      /* strength of flames in damage base hp */
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
        " covered in burning oil!\n"; 
}


void
create_object()
{
    set_name("_terel_burning_oil");
    set_short("blue flames");
    set_long(
        "Burning oil!\n"); 
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
       tell_room(environment(burn_player), "The oil on " +
                 QTNAME(burn_player) + " has cooled enough to cease "+
                 "burning.\n", 
                 burn_player);
       tell_object(burn_player, "The oil has cooled down enough to " +
                                "cease burning you.\n");
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

  res = burn_player->query_magic_res(MAGIC_I_RES_ACID); 
  damage = (strength / 2) + random(strength);
  damage -= ((damage * res) / 100); 

  if (objectp(burn_player) && 
      (environment(this_object()) == burn_player)) {
      tell_room(environment(burn_player), QCTNAME(burn_player) +  
                " screams in agony as the oil " +
                "burns " + burn_player->query_possessive() + " flesh!\n", 
                burn_player);
      tell_object(burn_player, "You scream in agony as the  " +
                             "oil continues to burn your flesh!\n");
      burn_player->heal_hp(-damage); 

/* Removing the call to die. It is too harsh a punishment.
 *  -- Lilith Feb 2009
 */
      if (burn_player->query_hp() < 100) 
      {
          tell_object(burn_player, "You are very near death!\n");
//          burn_player->do_die(this_object());
          remove_object();
          return;
      }
      else if (!random(6))
          set_alarm(4.0, 0.0, fade);
      else 
          burn_alarm = set_alarm(6.0, 0.0, burn);  
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
                burn_player->query_pronoun() + " is showered by " +
                "burning oil! " + 
                capitalize(burn_player->query_pronoun()) + 
                           " is on fire!\n", burn_player);   
      tell_object(burn_player, 
                    "You scream as you are showered in " +
                    "burning oil!\n");
   }
   else 
       remove_object();
}

