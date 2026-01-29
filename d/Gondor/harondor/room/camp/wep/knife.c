/* Name      : /w/toby/obj/knife.c
 * Purpose   : A knife to parry with and using a 
 *             shadow to mask the skillbonus from
 *             players.
 * Created by: Toby Windahl (Toby), 4:th of September 1999
 * 
 *   Modified: 20:th of June 2001, Toby Windahl (Toby)
 *                     Added the shadow.
 *             
 *             2005-11-23, Sir Toby
 *                         Modified to work with the
 *                         Genesis mudlib.
 */

#pragma strict_types

#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <formulas.h>
#include "/w/toby/path.h"

inherit "/std/weapon.c";

object  who_wields_me;
void    check_my_extra(object obj);
int     query_knife_random();

int     KNIFE_BONUS = random(2);
int     HIT=30;
int     PEN=20;

void
create_weapon()
{

   set_name("knife");
   add_name("dagger");
   add_name("_toby_defence_knife");
   set_pname("knives");
   add_pname("daggers");

   set_short("crude knife");
   set_pshort("crude knives");
   set_long("A crude steel knife, handle, darkened by dirt from " +
        "apparant long use, made of carved redwood. The blade " +
        "is roughly hammered giving the knife a crude look, the edge "+
	    "is slightly jagged and not very sharp. The knife is about " +
        "one human foot tall.\n");

   set_adj("crude");
   add_adj("metal");
   add_adj("steel");

    add_cmd_item( ({"knife","crude knife"}),({"touch","feel"}),
        "There is nothing special to it.\n");

   set_hit(HIT);
   set_pen(PEN);

   set_wt(W_KNIFE);
   set_dt(W_SLASH | W_IMPALE);
   set_wf(this_object());
   set_hands(W_LEFT);

   add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(HIT,PEN)+random(20));
   add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(PEN,W_KNIFE)/6);   
}


mixed
wield(object wep)
{
   write("You take a firm grip of the " +this_object()->query_short()+
         ", as you do, you feel better prepared for the comming " +
         "battles.\n");

   say(QCTNAME(this_player())+ " looks around alert of the surroundings "+
	      "as " +this_player()->query_pronoun()+ " wields the " +
	      this_object()->query_short()+ " in a firm grip. \n");
  
   set_alarm(2.0, 0.0, &check_my_extra(wep));
   
   return 1;
}


mixed
unwield(object obj)
{
   object who_is_wielding;

   who_is_wielding = environment(obj);

   if (living(who_is_wielding))
   {
     who_is_wielding->catch_tell("You release the firm grip of the " + 
              this_object()->query_short() + " and unwield it.\n");

     say(QCTNAME(this_player())+ " releases the grip of the "+
	             this_object()->query_short()+ " and unwields it.\n");
   }
   
   if(who_is_wielding->query_npc())
   {
      who_is_wielding->set_skill_extra(SS_PARRY, 0);
      who_is_wielding->set_skill_extra(SS_DEFENCE, 0);
   }
   else
   {
      who_is_wielding->remove_knife_effect();
   }

   set_hit(HIT);
   return 1;
}

void
check_my_extra(object obj)
{
   object who_wields_me, extra_shadow;
   
   who_wields_me = environment(obj);

   if(who_wields_me->query_npc())
   {
      who_wields_me->set_skill_extra(SS_PARRY, 20);
      who_wields_me->set_skill_extra(SS_DEFENCE, 20);
      set_hit(HIT+20);
   }
   else
   {
      setuid();
      seteuid(getuid());
   
      extra_shadow = clone_object(PATH + "obj/knife_shadow");
      extra_shadow->shadow_me(who_wields_me);
   }
}

int
query_knife_random()
{
   return KNIFE_BONUS;
}