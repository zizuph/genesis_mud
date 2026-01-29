/*   Igneous' immune from non-magical attacks shadow
 *
 *  Does what it's named after ;)
 *  All attacks done by non-magical damage types will not effect the 
 *  person with this shadow, unless the weapon is a magical one.
 *
 */
inherit "/std/shadow";

#include <stdproperties.h>
#include <wa_types.h>
#define DEBUG(x) find_player("karath")->catch_msg(x)

varargs public mixed
hit_me(int wcpen,int dt,object attacker,int attack_id,int target_hitloc = -1)
{
    object weapon, co;
    int    *hitloc;

    co = attacker->query_combat_object();
    weapon = co->cb_query_weapon(attack_id);
    hitloc = co->query_hitloc_id();

    // Magical weapon so this shadow has no effect.
    if (weapon->query_prop(OBJ_I_IS_MAGIC_WEAPON))
    {
//        DEBUG("MW - weapon is " + weapon->short() + " and I allow the hit\n");
	return shadow_who->hit_me(wcpen,dt,attacker,attack_id,target_hitloc);
    }
    // A non magical weapon or an attack which does a non magical attack
    if (dt == W_IMPALE || dt == W_SLASH || dt == W_BLUDGEON)
    {
//        DEBUG("norm - weapon is " + weapon->short() + " and dt is " + dt +
//		 " and I disallow the hit\n");
	return ({-1,co->query_hitloc(hitloc[random(sizeof(hitloc))])[2],0,0});
    }
    // Default return if none of the conditions above weren't met.
//    DEBUG("default - weapon is " + weapon->short() + " and I disallow the hit\n");
    return shadow_who->hit_me(wcpen,dt,attacker,attack_id,target_hitloc);
}

void
remove_takadek_shadow()
{
    remove_shadow();
}
