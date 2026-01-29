/* 
 * /d/Kalad/common/wild/pass/wep/wep_shadow.c
 * Purpose    : This is the shadow to make sure that any weapons that enter sunlight will rust. Used for the drow weapons
 * Located    : No where
 * Created By : Antharanos  ??.??.??
 * Modified By: 
 * First Modif: 
 */ 

inherit "/std/shadow";

public object weapon;

public void
set_weapon(object wep)
{
    weapon = wep;
}

public void
destroy_weapon()
{
    if (living(environment(weapon)))
        tell_object(environment(weapon), "Your weapon rusts!\n");
    weapon->remove_me();
    destruct();
}

public void
leave_env(object to, object from)
{
if (!from->query_prop(ROOM_I_LIGHT,0))
        destroy_weapon();
    return shadow_who->leave_env(to, from);
}
