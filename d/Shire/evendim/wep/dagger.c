/*
 * Dagger cloned for chest in prisoner quest.
 * -- Finwe, May 2001
 */
 
inherit "/std/weapon";

#include <macros.h>
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"

#define IT_NO_IMPROVE 0
#define IT_WAX        1
#define IT_HARDEN     2
#define IT_SHARPEN    3

int improve_type, duration;

create_weapon()
{
    set_name("dagger");
    set_pname("daggers");
    set_short("ancient dagger");
    set_pshort("ancient daggers");
    set_adj("long");
    set_long("This is an ancient dagger. The blade is long, " +
        "narrow, and made of steel. The guard extends on both " +
        "sides with pointed tips on each end. The handgrip is " +
        "black and has a twisted pattern, with strips of silver " +
        "outlining the indentions. The end is a silver flower " +
        "bud with many different flower petals folding into " +
        "each other.\n");
    add_item(({"pommel", "end"}),
        "The pommel is a silver flower bud. It is closed by " +
        "many petals folding onto each other.\n");
    add_item(({"handgrip", "handle"}), 
        "The handle is made of ebony and carved into a twisting " +
        "pattern. Narrow strips of silver outline the " +
        "indentions of the twisting pattern, The bottom of the " +
        "handrip is capped off with a silver flower bud.\n");
    add_item(({"guard"}),
        "The guard is made of rounded steel with pointed tips " +
        "on each end.\n");
    add_item(({"blade"}),
        "The blade is made of steel and ends at a sharp point.\n");

    set_default_weapon( 
       20,              
       35,              
       W_KNIFE,         
       W_IMPALE | W_SLASH,
       W_NONE,            
       0);           

   add_prop(OBJ_I_WEIGHT,2500);
   add_prop(OBJ_I_VOLUME,1500);
 /* Formula taken from /doc/man/general/weapon:
  * cc = 50 + ((wchit * wcpen * min(wchit,wcpen)) / 4)
 */
   add_prop(OBJ_I_VALUE,30 + random(40) + ((10*11*10)/4));
}


string query_recover()
{
    return MASTER + ":" + query_wep_recover();
}


void init_recover(string arg)
{
    init_wep_recover(arg);
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
-- More -- 100 -- (<cr> t b r n a <num> q x !<cmd> h ?) -- 
 *                dt:    The current damagetype
 *                phit:  The %success that we made with our weapon
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


