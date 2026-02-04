/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/weapon";

#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>

#define TO   this_object()
#define TP   this_player()
#define EN(x) environment(x)

//prototypes
void burning();

query_value(){ return 0; }
public void
create_weapon()
{
   set_name("fire-brand");
   set_adj("mysterious");
   set_long("It is a mysterious fire-brand, burning gloriously!\n");
   set_wt(W_SWORD);
   set_dt(MAGIC_DT);
   set_hit(30);
   set_pen(30);
   add_prop("mystic_weapon", 1);
   add_prop(MAGIC_AM_MAGIC, ({ 30, "conjuration"}));
   add_prop(OBJ_I_IS_MAGIC_WEAPON, 30);
   add_prop(OBJ_I_LIGHT, 5);
   
   set_wf(TO);
   set_alarm(3.0, 0.0, burning);
}

public mixed
wield()
{
   if (TP->query_alignment() > 500 && TP->query_prop("blessed")) {
      write("The " + short() + " does not burn you when you grasp it!\n");
      say(QCTNAME(TP) + " takes hold of the " + short() + 
         ", wielding it like some supernatural weapon!\n");
      return 1;
   }
   return "The fire-brand burns you intensely!\n";
}

void
burning(){
    
    object where = EN(TO);
    int n = random(3);

    if(!living(where)){
       if (n == 0)
           tell_room(where, "The " + short() + " crackles with a fiery glory.\n");
       else if (n == 1)
           tell_room(where, "The " + short() + " blazes up, like a frenzied spirit!\n");
       else if(n == 2)
           tell_room(where, "A white smoke arises from the " + short() + ".\n");
       return;
   }
   if(living(where)){
      if(n == 0){
          where->catch_msg("The " + short() + " crackles with a fiery glory.\n");
          tell_room(EN(where), "The " + short() + ", held by " +
                    QCTNAME(where) + " crackles with a fiery glory.\n", where);
      }
      if(n == 1){
          where->catch_msg("The " + short() + " blazes up, like a frenzied spirit!\n");
          tell_room(EN(where), "The " + short() + ", held by " +
                    QCTNAME(where) + " blazes up like a frenzied spirit!\n", where);
      }
      if(n == 2){
          where->catch_msg("A white smoke arises from the " + short() + ".\n");
          tell_room(EN(where), "A white smoke arises from the " +short() +
                    " held by " + QCTNAME(where) + ".\n", where);
      }
   }
   set_alarm(7.0, 0.0, burning);
   return;
}

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
public varargs int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt,
   int phit, int dam)
{
   if (phurt > 1 && enemy->query_prop(LIVE_I_UNDEAD)) {
      query_wielded()->catch_msg("The fire-brand burns bright!\n");
      enemy->catch_msg("You see white smoke as the " + short() + " burns you!\n");
      enemy->hit_me(10, MAGIC_DT, TP, -1);
      tell_room(environment(enemy), "The " + short() + " that " +
         QTNAME(query_wielded()) + " is holding burns brightly" +
         " with a white smoke as it touches " + QTNAME(enemy) +
         ".\n", ({query_wielded(), enemy}));
   }
   return 0;
}

public string
query_recover()
{
   return 0;
}
