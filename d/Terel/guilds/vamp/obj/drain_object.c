/*
 * Vampire Drain Object
 *
 * This hidden object keeps track of the resistances and skills that the
 * vampire has drained and is currently in effect. It uses multiplicative
 * resistance stacking as opposed to the old way of inherent additive
 * stacking.
 *
 * Created by Petros, February 2009
 *
 * Modifications:
 *  3/12/2009 - Balance has allowed drain to incorporate resistances as
 *              well as haste in addition to the current skill drains.
 */

#include "../guild.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

inherit "/std/object";

#include "/d/Genesis/specials/debugger/debugger_tell.h"

// Defines
#define MANAGER     (player->query_manager())
#define SKILL_MODE  0
#define RESIST_MODE 1
#define HASTE_MODE  2

// Global variables
private mapping     resistance_mapping = ([
    MAGIC_I_RES_ACID          : OBJ_I_RES_ACID,
    MAGIC_I_RES_AIR           : OBJ_I_RES_AIR, 
    MAGIC_I_RES_COLD          : OBJ_I_RES_COLD,
    MAGIC_I_RES_DEATH         : OBJ_I_RES_DEATH,
    MAGIC_I_RES_EARTH         : OBJ_I_RES_EARTH,
    MAGIC_I_RES_ELECTRICITY   : OBJ_I_RES_ELECTRICITY,
    MAGIC_I_RES_FIRE          : OBJ_I_RES_FIRE,
    MAGIC_I_RES_LIFE          : OBJ_I_RES_LIFE, 
    MAGIC_I_RES_LIGHT         : OBJ_I_RES_LIGHT,
    MAGIC_I_RES_POISON        : OBJ_I_RES_POISON,
    MAGIC_I_RES_WATER         : OBJ_I_RES_WATER,
    ]);
public  object      player;
private mapping     skill_extras = ([ ]);
private int         drain_mode = SKILL_MODE;
private int         used_haste = 0;

// Prototypes
public void         update_all_drain_benefits();

public void 
create_object()
{
    // This object is hidden, and for all purposes should not ever be
    // known to exist by the player.
    set_name("_hidden_vamp_drain_object");
    add_name( ({"hidden_vamp_drain_object" }) );
    set_short("hidden vampire drain object");    
    set_long("A hidden drain object. The player should not see this in "
        + "their inventory.\n");
    set_no_show();
  
    remove_prop(OBJ_I_VOLUME);
    remove_prop(OBJ_I_VALUE);
    remove_prop(OBJ_I_WEIGHT);
    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_M_NO_BUY, 1);
    
    setuid();
    seteuid(getuid());
}

/*
 * Function:    query_drain_mode
 * Description: Returns which mode the drain object is operating. It
 *              determines which of the drained effects are active.
 */
public int
query_drain_mode()
{
    return drain_mode;
}

/*
 * Function:    set_drain_mode
 * Description: Allows the changing of the mode that is in effect on the
 *              drain object.
 *              
 */
public void
set_drain_mode(int mode)
{
    drain_mode = mode;
    update_all_drain_benefits();
}

public int * 
get_max_borrowed_skills()
{
    if (player->query_bloodguard())
    {
        return ({ 20, 10 });
    }
    
    return ({ 40, 20 });
}

// Vamps should get 25% combat aid from Skills
// Bloodguards should get 10% combat aid from skills
public int * 
get_max_used_skills()
{
    if (player->query_bloodguard())
    {
        return ({ 10, 6 });
    }

    return ({ 25, 10 });
}

public int 
get_max_borrowed_resistance()
{
    if (player->query_bloodguard())
    {
        return 15;
    }

    return 30;
}

public int 
get_max_used_resistance()
{
    if (player->query_bloodguard())
    {
        return 9; // 9% resistance = 10% combat aid
    }
    return 20; // 20% resistance == 25% combat aid
}

public int
get_max_borrowed_quickness()
{
    if (player->query_bloodguard())
    {
        return 0;
    }
    
    return 65;
}

public int
get_max_used_quickness()
{
    if (player->query_bloodguard())
    {
        return 0;
    }
    
    return 45; 
    
}

public int 
get_max_drain_skill(int skill, int * max_skill)
{
    mapping drain_focus;
    
    drain_focus = MANAGER->query_drain_focus(player);    
    foreach (string key : m_indexes(drain_focus))
    {
        int * focus = drain_focus[key];

        for (int i = 0; i < sizeof(max_skill); ++i)
        {
            if (sizeof(focus) > i && focus[i] == skill)
            {
                return max_skill[i];
            }
        }
    }
    return 0;
}

public void
cleanup_drained_skills()
{
    mapping skills;
    
    if (!living(player))
    {
        return;
    }
    
    skills = MANAGER->query_drained_skills(player);
    foreach (int skill_num : m_indices(skills))
    {
        skills[skill_num] = min(skills[skill_num], 
               get_max_drain_skill(skill_num, get_max_borrowed_skills()));
        if (!skills[skill_num])
        {
            m_delkey(skills, skill_num);
        }      
    }
    MANAGER->set_drained_skills(player, skills);           
}

public int *
query_drain_focus_skills()
{
    int * skills;
    mapping drain_focus;
    
    skills = ({ });
    drain_focus = MANAGER->query_drain_focus(player);    
    foreach (mixed key : m_indices(drain_focus))
    {
        skills += drain_focus[key];
    }
    
    return skills;
}

public void
update_skill_extras()
{
    mapping skills;
    int new_used;

    // First clean up the drained skills
    cleanup_drained_skills();
    
    // Next reduce all the existing skill extras
    foreach (int snum : m_indices(skill_extras))
    {
        player->set_skill_extra(snum, 
            player->query_skill_extra(snum) - skill_extras[snum]);
    }
    
    skill_extras = ([ ]);
    
    if (query_drain_mode() != SKILL_MODE)
    {
        // If not in skill mode, we don't actually adjust any skills
        return;
    }
    
    // Now, go through all the drain focus skills and set the new
    // skill extras
    skills = MANAGER->query_drained_skills(player);
    foreach (int snum : query_drain_focus_skills())
    {   
        new_used = min(get_max_drain_skill(snum, get_max_used_skills()),
                       skills[snum]);
        if ((player->query_skill(snum) + new_used) > 100)
        {
            // Skills are maxed out at 100, no matter what.
            new_used = 100 - player->query_skill(snum);
        }
        if (new_used)
        {
            player->set_skill_extra(snum, 
                player->query_skill_extra(snum) + new_used);
        }
        // Save how much skill this object is adding, so when the
        // next update occurs, we know how much to remove.
        skill_extras[snum] = new_used;
    }    
}

/*
 * Function name:  query_magic_protection
 * Description:    This function should return the
 *                 amount of protection versus an 
 *                 attack of 'prop' on 'obj'.
 * Arguments:      prop - The element property to defend.
 *                 protectee  - Magic protection for who or what? 
 */
public varargs mixed
query_magic_protection(string prop, object what)
{
    mapping resistances;
    string drain_type;
    int resistance;
    
    if (!living(player)
        || !IN_ARRAY(prop, m_indices(resistance_mapping)))
    {
        // We don't provide magic protection if it's not one of the
        // listed resistances in resistance_mapping
        return 0;
    }

    if (query_drain_mode() != RESIST_MODE)
    {
        // No resistance if not in resist mode.
        return 0;
    }
    
    // The Drain Type is the OBJ_I_RES_XXX. prop is MAGIC_I_RES_XXX
    // Vampires drain the inherent resistance and store that value.
    // We translate that value here for the purposes of calculating
    // their resistance.
    drain_type = resistance_mapping[prop];
    resistances = MANAGER->query_drained_resistances(player);
    if (IN_ARRAY(drain_type, m_indices(resistances)))
    {
        // If the Vampire has drained the particular type, we
        // return it. They max out at their "max used resistance"
        // value set in the shadow.
        resistance = max(0, min(resistances[drain_type], 
                                get_max_used_resistance()));
        return ({ resistance, 1 });
    }

    return 0;
}

public void
update_haste()
{
    mapping skills;
    int new_used;

    // First remove the existing haste benefits
    player->add_prop(LIVE_I_QUICKNESS, player->query_prop(LIVE_I_QUICKNESS)
                                       - used_haste);
    used_haste = 0;
    
    if (query_drain_mode() != HASTE_MODE)
    {
        // If not in skill mode, we don't actually adjust any skills
        return;
    }

    used_haste = min(MANAGER->query_drained_quickness(player),
                     get_max_used_quickness());
    player->add_prop(LIVE_I_QUICKNESS, player->query_prop(LIVE_I_QUICKNESS)
                                       + used_haste);
}

/*
 * Function name: update_all_drain_benefits
 * Description:   Calls both of the functions that updates the drain
 *                benefits for haste and skills
 */
public void
update_all_drain_benefits()
{
    update_skill_extras();
    update_haste();
}

/*
 * Function name: reduce_skill
 * Description:   function for reducing a value by one, min 0
 */
int reduce_skill(int i)
{
    return max(0,i-1);
}

/*
 * Function name: reduce_blood_drains
 * Description:   reduces all borrowed skills and resistance
 */
public void 
reduce_blood_drains()
{
    mapping skills;
    int quickness;
    
    skills = map(MANAGER->query_drained_skills(player), reduce_skill);

    // Reduce Skills
    foreach (int snum : m_indices(skills))
    {
        if (!skills[snum])
        {
            m_delkey(skills, snum);
        }
    }    
    MANAGER->set_drained_skills(player, skills);
    
    // Lower resistances
    mapping resistances = MANAGER->query_drained_resistances(player);
    foreach (string resistance : m_indices(resistances))
    {
        // Reduce each resistance by one.
        resistances[resistance] = max(0, resistances[resistance] - 1);
        if (resistances[resistance] == 0)
        {
            m_delkey(resistances, resistance);
        }
    }
    MANAGER->set_drained_resistances(player, resistances);
    
    // Lower haste
    quickness = MANAGER->query_drained_quickness(player);
    quickness = max(0, quickness - 1);
    MANAGER->set_drained_quickness(player, quickness);
    
    update_all_drain_benefits();
}

public int 
query_enemy_skill(object enemy, int skill)
{
    //Most NPCs never have general skills set, so we'll give them
    //a reasonable number.
    if (IN_ARRAY(skill, ALLOWED_SKILLS["general"]))
    {
        return max(enemy->query_skill(skill),
                   enemy->query_average_stat() / 2);
    }
    return enemy->query_skill(skill);
}

public void 
add_blood_drains(object enemy)
{
    mapping skills, drain_focus, resistances;
    int new_borrowed, old_used, new_used, quickness, enemy_quickness;
    
    if (!objectp(enemy))
    {
        return;
    }
       
    // Add Skills
    skills = MANAGER->query_drained_skills(player);
    foreach (int skill_num : query_drain_focus_skills())
    {   
        new_borrowed = min(skills[skill_num] + 1,
                            get_max_drain_skill(skill_num, 
                                get_max_borrowed_skills()));
        new_borrowed = min(new_borrowed, query_enemy_skill(enemy, skill_num));
        new_borrowed = max(skills[skill_num], new_borrowed);
        
        skills[skill_num] = new_borrowed;
    }    
    MANAGER->set_drained_skills(player, skills);

    // Add Resistances
    resistances = MANAGER->query_drained_resistances(player);
    foreach (string resistance : m_values(resistance_mapping))
    {
        // Increase each resistance by one if enemy has it
        int enemy_resist = min(enemy->query_prop(resistance),
                               get_max_borrowed_resistance());
        if (resistances[resistance] < enemy_resist)
        {
            // Enemy has more resistance than we have drained. We add
            // by one.
            resistances[resistance] = resistances[resistance] + 1;
        }
    }
    MANAGER->set_drained_resistances(player, resistances);    
    
    // Add Haste
    enemy_quickness = min(enemy->query_prop(LIVE_I_QUICKNESS),
                          get_max_borrowed_quickness());
    quickness = MANAGER->query_drained_quickness(player);                   
    if (quickness < enemy_quickness)
    {
        new_borrowed = min(quickness + 1, get_max_borrowed_quickness());
        MANAGER->set_drained_quickness(player, new_borrowed);
    }
    
    update_all_drain_benefits();
}

/*
 * Function     : enter_env
 * Description  : When the effect object enters the inventory, it will
 *                set the effect target of the living that it is entering.
 *                This is a convenience as this is the case for most
 *                effects.
 * Arguments    : dest - where the object is entering
 *                old  - where the object came from
 * Returns      : nothing
 */
public void
enter_env(object dest, object old)
{
    ::enter_env(dest, old);

    if (dest && living(dest))
    {
        if (!IN_ARRAY(this_object(), dest->query_magic_effects()))
        {
            send_debug_message("vamp_drain", "Entering living "
                             + "environment. Adding this object as a "
                             + "magic effect.");
            dest->add_magic_effect(this_object());
            player = dest;
            // Call the code to update the skills and haste
            update_all_drain_benefits();
        }
    }
}

/*
 * Function name: remove_object
 * Description:   Called upon object destruction. This needs to be set
 *                so that the object is properly removed from the
 *                magic effect list.
 */
public void
remove_object()
{
    if (living(player))
    {
        player->remove_magic_effect(this_object());
        
        // Remove the bonus skill effects
        foreach (int snum : m_indices(skill_extras))
        {
            player->set_skill_extra(snum, 
                player->query_skill_extra(snum) - skill_extras[snum]);
        }
        
        skill_extras = ([ ]);
        
        // Remove bonus haste effects
        player->add_prop(LIVE_I_QUICKNESS, player->query_prop(LIVE_I_QUICKNESS)
                                           - used_haste);
        used_haste = 0;        
    }
    
    ::remove_object();
}

