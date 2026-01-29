#pragma strict_types

inherit "/std/armour";

#include "lizards.h"
#include <math.h>
#include <wa_types.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/std/combat/combat.h"

#define AM  1
#define AC  0

static mapping armour_class = ([
    A_HEAD : ({ 0, ({ 0, 0, 0 }) }),
    A_BODY : ({ 0, ({ 0, 0, 0 }) }),
    A_L_ARM : ({ 0, ({ 0, 0, 0 }) }),
    A_R_ARM : ({ 0, ({ 0, 0, 0 }) }),
    A_LEGS : ({ 0, ({ 0, 0, 0 }) })
]);
/*
 * Function name:   create_object
 * Description:     
 * Arguments:       
 * Returns:         
 */
public void
create_armour()
{
    setuid();
    seteuid(getuid());
    
    set_at(A_MAGIC);
    set_ac(20);
    set_no_show();
    set_short("saurian skin");
    
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(OBJ_M_NO_DROP, 1); 
    add_prop(OBJ_M_NO_GIVE, 1); 
    add_prop(OBJ_I_INVIS,1);
    
    remove_prop(OBJ_I_VALUE);
    remove_prop(OBJ_I_VOLUME);
    remove_prop(OBJ_I_WEIGHT);
    
    set_af(this_object());
} /* create_object */

/*
 * Function name:   query_shield_slots
 * Description:     Give a bodypart protected by a shield or magic armour
 * Arguments:
 * Returns:
 */
public int *
query_shield_slots()
{
    return (({ A_HEAD, A_BODY, A_L_ARM, A_R_ARM, A_LEGS }));
} /* query_shield_slots */


public status
update_saurian_skin()
{
    object  combat_object;
    int     skin;
    
    if (!objectp(combat_object = wearer->query_combat_object()))
        return 0;
    
    skin = min((wearer->query_stat(SS_LAYMAN) / 3), 35);
    foreach(int hid: combat_object->query_hitloc_id())
    {
        mixed  *hitloc = combat_object->query_hitloc(hid);
        int    *skin_am = allocate(3);
        
        for (int i = 0; i < sizeof(hitloc[HIT_AC]); i++)
        {
            // We have 1 ac by default, so subtract it (so we
            // still get it)
            int other_ac = -1 - skin/2 + (hitloc[HIT_AC][i] -
                (armour_class[hid][AC] + armour_class[hid][AM][i]));
            skin_am[i] = min(0, max(0 - other_ac, 0 - skin));
        }
        
        armour_class[hid][AC] = skin;
        armour_class[hid][AM] = skin_am;
    }
    
    wearer->update_armour(this_object());
    return 1;
}

/*
 * Function name:   query_am
 * Description:     Give the ac modifier for a specific hitlocation
 * Arguments:       hid: Hitlocation id
 * Returns:
 */
int *
query_am(int hid)
{
    if (hid && (member_array(hid, m_indexes(armour_class)) > -1))
        return armour_class[hid][AM] + ({});
    
    return ({ 0, 0, 0 });
} /* query_am */

/*
 * Function name:   query_ac
 * Description: Give the ac for a specific hitlocation that is protected
 * Arguments:   hid: Hitlocation id
 * Returns:
 */
varargs int
query_ac(int hid)
{
    if (hid && (member_array(hid, m_indexes(armour_class)) > -1))
        return armour_class[hid][AC];
        
    return 0;
} /* query_ac */

/*
 * called from the set_at - we want to be able to wear
 * the armour without printing messages
 */
public mixed wear(object obj)
{
  return 1;
}

public mixed remove(object obj)
{
  return "";
}

void
init_saurian_skin(object player)
{
    if (!environment() || environment() != player)
        this_object()->move(player, 1);
    
    set_this_player(player);
    wear_me();
    
    update_saurian_skin();
    this_object()->remove_item_expiration();
}

/*
 * Function name: got_hit
 * Description:   Notes that the defender has been hit. It can be used
 *                to reduce the ac for this hitlocation for each hit.
 * Arguments:     hid:   The hitloc id, ie the bodypart hit.
 *                ph:    The %hurt
 *                att:   Attacker
 *                aid:   The attack id
 *                dt:    The damagetype
 *                dam:   The damage done to us in hit points
 */
 varargs int
 got_hit(int hid, int ph, object att, int dt, int dam)
 {
    if(dam <= 0)
    return 0;
    
    int idx = QUICK_FIND_EXP(dt) - 1;
    
    if (idx >=0 && idx <= sizeof(armour_class[hid])-1 && random(100) < 
        armour_class[hid][AC] + armour_class[hid][AM][idx])
    {
    query_worn()->catch_msg("Your skin seems to absorb some of the blow\n");
        
    tell_room(environment(query_worn()), QNAME(query_worn())+ "'s skin seems "+
    "to deflect the blow.\n",({ query_worn() }));
    }
    
    // We do not need to count hits or change condition, so don't need to call
    // ::got_hit().
    return 0;
    //return ::got_hit(hid, ph, att, dt, dam);
 }

public string
query_recover()
{
    return "";
}

int set_dull(int du) 
{ 
    return 0; 

}
int set_condition(int cond) 
{ 
    return 0; 
}

varargs void remove_broken(int silent = 0) 
{ 
    return; 
}