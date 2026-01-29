/*
 *  Improved weapon
 *  This weapon is set to look like another weapon that the player gave,
 *  but redefines the did_hit function. To the player all should look alike.
 *
 *  The weapon degenerates when 90%+ hits are made. With set_duration(hits)
 *  the number of those hits can be set. When the duration is consumed, the
 *  weapon acts normal again.
 *							Tricky
 */
 
inherit "/std/weapon";

#include <macros.h>
#include <wa_types.h>
#include <stdproperties.h>

#define IT_NO_IMPROVE 0
#define IT_WAX        1
#define IT_HARDEN     2
#define IT_SHARPEN    3

int improve_type, duration;

void
create_weapon()
{
   set_name("_improved_weapon_");
   improve_type = IT_NO_IMPROVE;
}

public void
set_improve_type(int type)
{
   if (type == IT_WAX || type == IT_HARDEN || type == IT_SHARPEN)
      improve_type = type;
   else
      improve_type = IT_NO_IMPROVE;
}

public void
set_duration(int hits)
{
   duration = hits;
}

/*
 * Function name:   make_copy
 * Description:     Makes this weapon a copy of the given original.
 * Arguments:       orig: The original weapon to copy
 */
public void
make_copy(object orig)
{
   int i;
   string *prop_arr;

   if (!orig) return;

   /*
    * Unfortunately the VBFC features of the original are neglected.
    * We'll just have to learn to live with that...
    */
   set_name(orig->query_names());
   set_pname(orig->query_pnames());
   set_adj(orig->query_adjs());
   set_short(orig->short());
   set_pshort(orig->plural_short());
   set_long(orig->long());

   /* Let's set the properties right */
   prop_arr = orig->query_props();
   for (i=0; i < sizeof(prop_arr); i++)
      add_prop(prop_arr[i], orig->query_prop(prop_arr[i]));
}

query_hit()
{
   int hit;
   hit = ::query_hit();
   if (improve_type == IT_WAX)
      hit = (105 * hit)/100;			/* 5% more */
   else if (improve_type == IT_HARDEN)
      hit = (110 * hit)/100;			/* 10% more */
   else if (improve_type == IT_SHARPEN)
      hit = (115 * hit)/100;			/* 15% more */

   return hit;
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
 *		  dt:	 The current damagetype
 *		  phit:  The %success that we made with our weapon
 * Returns:       True if it handled combat messages.
 */
public varargs int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit)
{
   string how, what, where, with;
   object me, co;

   if (improve_type != IT_WAX && improve_type != IT_HARDEN
       && improve_type != IT_SHARPEN)
      return ::did_hit(aid, hdesc, phurt, enemy, dt, phit);

   if ((!enemy) || (!(me = query_wielded())))
      return ::did_hit(aid, hdesc, phurt, enemy, dt, phit);

   if (!(co = me->query_combat_object()))
      return ::did_hit(aid, hdesc, phurt, enemy, dt, phit);

   where = "the " + hdesc + " of " + QTNAME(enemy);

   with = co->cb_attack_desc(aid);

   if (phurt == -1 || phurt == -2)
   {
       me->catch_msg("You aim for " + where
                   + "with your " + with + " but miss.\n");
       enemy->catch_msg(QCTNAME(me) + " aim for your " + hdesc
                      + " with " + me->query_possessive() + " " + with
                      + ", but miss.\n");
   }

   /*
    * The actual combat messages.
    */
   how = ", without effect.";
   what = "hit";

   if (phurt > 0)
   {
      how = ".";
      what = "tickled";
   }
   if (phurt > 5)
   {
      how = ".";
      what = "grazed";
   }
   if (phurt > 10)
   {
      how = ".";
      what = "hurt";
   }
   if (phurt > 17)
   {
      how = ", rather bad.";
      what = "hurt";
   }
   if (phurt > 30)
   {
      how = ", very bad.";
      what = "hurt";
   }
   if (phurt > 45)
   {
      how = ", very hard.";
      what = "smash";
   }
   if (phurt > 60)
   {
      how = ", with a bone crushing sound.";
      what = "smash";
      where = QTNAME(enemy);
   }
   if (phurt > 75)
   {
      how = ".";
      what = "massacre";
      where = QTNAME(enemy);
   }
   if (phurt > 90)
   {
      if (improve_type == IT_WAX)
      {
         what = "slice";
         how = " to little pieces.";
      }
      else if (improve_type == IT_HARDEN)
      {
         what = "chop";
         how = " into tiny bits.";
      }
      else /* improve_type == IT_SHARPEN */
      {
         what = "slice";
         how = " to little pieces.";
      }
      where = QTNAME(enemy);

      duration--;
      if (duration <= 0)
         improve_type = IT_NO_IMPROVE;
   }    
   me->catch_msg("You " + what + " " + where + " with your " + with +
                 how + "\n");
   enemy->catch_msg(QCTNAME(me) + " " + what + " your " + hdesc + " with " +
                    me->query_possessive() + " " + with + how + "\n");

}


string query_recover()
{
    return MASTER + ":" + query_wep_recover();
}


void init_recover(string arg)
{
    init_wep_recover(arg);
}
