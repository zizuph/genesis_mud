inherit "/std/shadow";
 
#include "/d/Emerald/defs.h"
 
#include <filter_funs.h>
 
#define DRAKE_BONE_WHIRL "_drake_bone_whirl"
 
void
shadow_me( object whom )
{
    ::shadow_me( whom );
}
 
void
dest_bone_shadow()
{
    ::remove_shadow();
}
 
int
bone_shadow_exists()
{
    return 10;
}
 
void
tell_watcher( string str, object me, object enemy )
{
    object *ob;
    int i;
 
    ob = FILTER_LIVE(all_inventory(environment(me))) - ({ me });
    ob -= ({ enemy });
    for (i = 0; i < sizeof(ob); i++)
        if (ob[i]->query_see_blood())
            ob[i]->catch_msg(str);
}
 
 
int
query_not_attack_me( object attacker,int att_id )
{
    mixed *attack;
    object combat_object;
    string attack_desc;
 
    if( shadow_who->query_prop( DRAKE_BONE_WHIRL ) != 1 || random( 2 ) )
        return shadow_who->query_not_attack_me( attacker,att_id );
 
    combat_object = attacker->query_combat_object();
    attack = combat_object->query_attack( att_id );
    if( !attack )
        return shadow_who->query_not_attack_me( attacker,att_id );
    attack_desc = combat_object->cb_attack_desc( att_id );
    shadow_who->catch_msg( "You parry " + QTNAME( attacker ) + "'s " +
                   attack_desc + " with your bone spear.\n" );
    attacker->catch_msg( QCTNAME( shadow_who ) + " parries your " + attack_desc +
                   " with " + POS( shadow_who ) + " bone spear.\n" );
    tell_watcher( QCTNAME( shadow_who ) + " parries " + QTNAME( attacker ) +
                  "'s " + attack_desc + " with bone spear.\n",shadow_who,attacker );
    return 1;
 
}
 
 
