/* Scarred hardened skin provides some ac benefits to the Doomseekers.
 *
 * A base armour class that when they have their maximum guild
 * stat amounts under the max allowable AC for armour purchased 
 * from an armourer (30 vs 40). 
 *
 * This provides roughly between 18.5% and 33.5% raw damage reduction 
 * across all hit locations. As guild stat resets every time a 
 * Doomseeker dies, most would not gain or retain max damage
 * reduction for long.
 *
 * Arman, May 2021
 */


#pragma strict_types

inherit "/std/armour";

#include "../guild.h"
#include "/d/Krynn/common/defs.h"
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <composite.h>
#include <language.h>
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

    set_name("doomseeker_ac_ob");    
    set_at(A_MAGIC);
    set_ac(20);
    set_no_show();
    
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


public int
query_skin_ac_bonus()
{
    // base 15 ac, max 30    
    int skin = min((15 + (wearer->query_stat(SS_OCCUP) / 10)), 30);

    return skin;
}

public string
query_skin_ac_desc()
{
    int skin = query_skin_ac_bonus();
    string skin_desc;

    switch(skin)
    {
        case 0:
            skin_desc = "unmarred";
            break;
        case 1..5:
            skin_desc = "lightly lacerated";
            break;
        case 6..10:
            skin_desc = "hardened";
            break;
        case 11..15:
            skin_desc = "lightly scarred";
            break;
        case 16..20:
            skin_desc = "scarred";
            break;
        case 21..25:
            skin_desc = "markedly scarred";
            break;
        case 26..29:
            skin_desc = "heavily scarred";
            break;
        case 30..35:
            skin_desc = "monstrously scarred";
            break;
        default:
            skin_desc = "unmarred";
            break;  
    }

    return skin_desc;
}

public status
update_doomseeker_skin()
{
    object  combat_object;
    int     skin;

    // AK_DEBUG("update_doomseeker_skin called in skin object");
    
    if (!objectp(combat_object = wearer->query_combat_object()))
        return 0;
   
    skin = query_skin_ac_bonus();

    foreach(int hid: combat_object->query_hitloc_id())
    {
        mixed  *hitloc = combat_object->query_hitloc(hid);
        int    *skin_am = allocate(3);
        
        for (int i = 0; i < sizeof(hitloc[HIT_AC]); i++)
        {
            hitloc[HIT_AC][i] -= (armour_class[hid][AC] + armour_class[hid][AM][i]);
            skin_am[i] = min(0, max(0 - hitloc[HIT_AC][i], 0 - skin));
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
        return armour_class[hid][AM];
    
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
public mixed 
wear(object obj)
{
    this_player()->add_subloc("doomseeker_ac_skin", this_object());
    return 1;
}

public mixed 
remove(object obj)
{
    this_player()->remove_subloc("doomseeker_ac_skin");
    return "";
}

void
init_doomseeker_skin(object player)
{
    if (!environment() || environment() != player)
        this_object()->move(player, 1);
    
    set_this_player(player);
    wear_me();
    
    update_doomseeker_skin();
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
    
    query_worn()->catch_msg("Your " +query_skin_ac_desc()+ 
        " skin absorbs some of " +QTPNAME(att)+ " blow.\n");
        
    tell_room(environment(query_worn()), QCTPNAME(query_worn())+ " " +
        query_skin_ac_desc()+ " skin absorbs some of " +QTPNAME(att)+ 
        " blow.\n",
        ({ query_worn() }));
      
    // return ::got_hit(hid, ph, att, dt, dam);
    return 0;
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

string
show_subloc(string subloc, object me, object for_obj)
{
    if (me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
	return "Your bare skin is " +query_skin_ac_desc()+ 
            " from your battles since taking a death oath.\n";

    if (for_obj == me)
	return "Your bare skin is " +query_skin_ac_desc()+ 
            " from your battles since taking a death oath.\n";
    else
	return C(HIS(me)) + " bare skin is " +query_skin_ac_desc()+
	" from the battles " +PRONOUN(me)+ " has fought in " +
        "since taking a death oath.\n";
}