/* Kretan Enemy Check Function
** This function checks to see if this_player() is an enemy of the Kretans,
** based on the armours/weapons worn/wielded.
** Used by Kretans to decide whether or not to attack and whether or not
** to allow them to pass a sentry point. Called in aggressive_attack in
** Kretan NPCs, and in check for blocking guarded exits.
** Player must be wearing kretan armours on his/her head and body, and
** must not be wearing/wielding any non-kretan armours/weapons elsewhere
** to "fool" the kretans (be Kretan Armoured)
*/
#include <wa_types.h>
int kretan_enemy(object Tp) {
   int    kr_body_armour =((Tp->query_armour(A_BODY))->adjectiv_id("kretan"));
   int    kr_head_armour =((Tp->query_armour(A_HEAD))->adjectiv_id("kretan"));
   object *wielded       =(Tp->query_weapon(-1)); /* ret list all wielded */
   object *worn          =(Tp->query_armour(-1)); /* ret list all worn */
   int i;
 
   if (!(kr_body_armour&&kr_head_armour)) return 1;
 
   if (wielded)
      for (i=0; i<sizeof(wielded); i++)
         if (!((wielded[i])->adjectiv_id("kretan")))
            return 1;
 
   if (worn)
      for (i=0; i<sizeof(worn); i++)
         if (!((worn[i])->adjectiv_id("kretan")))
            return 1;
   return 0;
}
