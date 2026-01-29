inherit "/std/shadow";

#include <stdproperties.h>
#include <wa_types.h>

#define REMOVE_TIME  300  

// Prototypes
void remove_warp_shadow();

int last_hit = time();

varargs public mixed
hit_me(int wcpen,int dt,object attacker,int attack_id,int target_hitloc = -1)
{
    object weapon;
    mixed result;
    int res;

    weapon = attacker->query_combat_object()->cb_query_weapon(attack_id);

    if (weapon->query_is_warped())
    {
	last_hit = time();
	res = shadow_who->query_magic_res(MAGIC_I_RES_MAGIC);
	if (res)
	    wcpen = wcpen - ((wcpen * res) / 100);
	result = shadow_who->hit_me(wcpen,MAGIC_DT,attacker,attack_id,target_hitloc);
    }

    else
	result = shadow_who->hit_me(wcpen,dt,attacker,attack_id,target_hitloc);

    if (time() - last_hit > REMOVE_TIME)
	set_alarm(0.0,0.0,remove_warp_shadow);
    return result;
}

int
query_is_warp_shadowed()
{
    return 1;
}

void
remove_warp_shadow()
{
    remove_shadow();
}
