/* Coded by Ckrik June 1999
 * Shadow of bl_platemail.c
 *
 * Ckrik 2/1/2004 Added check to make sure the shadow is shadowing the
 * person wearing the armour.
 *
 * 4/8/2008 - Fixed shadow issue with removal of wrong shadow. Petros
 *
 */

inherit "/std/shadow";

#include <wa_types.h>

public object bl_platemail;
private int doing_hit = 0;

public void
remove_bl_platemail_shadow()
{
    remove_shadow();
}

public void
set_platemail_shadow_owner(object owner)
{
    bl_platemail = owner;
}

varargs public mixed 
hit_me(int wcpen, int dt, object attacker, 
       int attack_id, int target_hitloc = -1)
{
    mixed dam_lvl;
    if (!objectp(bl_platemail) || !objectp(bl_platemail->query_worn()) ||
	bl_platemail->query_worn() != shadow_who)
    {
        remove_shadow();
	return;
    }
    dam_lvl = shadow_who->hit_me(wcpen, dt, attacker, attack_id,
        target_hitloc);
    target_hitloc = dam_lvl[4];
    if(target_hitloc == TS_TORSO && doing_hit != 1)
    {
        doing_hit = 1;
        bl_platemail->armour_hit_me(wcpen, dt, attacker, attack_id,
            target_hitloc);
	doing_hit = 0;
    }

    return dam_lvl;
}

public mixed
query_nonmet_name()
{
    string func = calling_function();

    if(func == "do_die" || func == "set_name")
    {
        return shadow_who->query_nonmet_name();
    }

    return "spiked " + shadow_who->query_nonmet_name();
}
