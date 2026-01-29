#include <files.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>

#include "../guild.h"

#define GAIN_DELAY  6

static mapping  last_gain = ([]);

/*
 * Function name:   filter_bow
 * Description:     It checks if given object is a missile weapon.
 * Arguments:       (object) ob
 * Returns:         (status) 1/0 Missile weapon/Not a missile weapon
 */
public status
filter_bow(object ob)
{
    return ( IS_WEAPON_OBJECT(ob) && (ob->query_wt() == W_MISSILE) );        
} /* filter_bow */

/*
 * Function name:   query_wielded_bow
 * Description:     Finds any bows wielded by the archer.
 * Arguments:       (object) archer
 * Returns:         (object) The arrow object or 0 if no arrow was found.
 */
public mixed
query_wielded_bow(object archer)
{
    mixed bow;
    
    if (pointerp(bow = filter(archer->query_weapon(-1),
        &filter_bow())) && sizeof(bow))
        bow = bow[0];
        
    if (!objectp(bow))
        return 0;
    
    return bow;
} /* query_wielded_bow */

/*
 * Function name:   find_arrows
 * Description:     Finds an arrow in the archers inventory or quiver.
 * Arguments:       (object) archer
 *                  (object) bow
 * Returns:         (object) The arrow or 0 if no arrow was found.
 */
public varargs object
find_arrows(object archer, object bow, mixed exclude)
{
    object *arrows, *quivers;
    int    i;
    
    arrows = bow->query_valid_projectiles(archer);
    
    if (objectp(exclude))
        exclude = ({ exclude });
    
    if (pointerp(exclude))
        arrows -= exclude;
    
    if (!sizeof(arrows))
    {
        quivers = filter(all_inventory(archer),
                         &->query_prop(CONT_I_IS_QUIVER));
                    
        if (!sizeof(quivers))
            return 0;
        
        for (i = 0; i < sizeof(quivers); i++)
        {
            arrows = bow->query_valid_projectiles(quivers[i]);
            
            if (sizeof(arrows))
                break;
        }
        
        if (!sizeof(arrows))
            return 0;
    }
    
    return arrows[0];
} /* find_arrows */

/* 
 * Function name:   reduce_arrow_stack
 * Description:     This function takes care of reducing missile stack.
 * Arguments:       (object) bow
 *                  (object) stack
 * Returns:         (object)
 */
public varargs object
reduce_arrow_stack(object bow, object stack)
{
    object quiver, arrow;
    
    /* Handle potential destruction of nocked arrow */
    if (objectp(bow->query_projectile()))
    {
        setuid();
        seteuid(getuid());
        
        arrow = clone_object(MASTER_OB(bow->query_projectile()));
        arrow->set_heap_size(1);
        bow->query_projectile()->remove_object();
        bow->unload_projectile();
        
        return arrow;
    }
    
    if (!objectp(stack) && !(stack = bow->query_projectile_stack()))
    {
        bow->find_projectiles();
        stack = bow->query_projectile_stack();
    }
    
    if (!objectp(stack))
        return 0;
    
    quiver = environment(stack);
    stack->split_heap(1);
    arrow = stack;
    stack = stack->make_leftover_heap();
    arrow->move(bow, 1);
    stack->move(quiver, 1);
    bow->set_projectile_stack(stack);
    
    return arrow;
}

/* 
 * Function name:   reduce_and_miss
 * Description:     This function takes care of moving the arrow to the
 *                  environment of our target when we miss.
 * Arguments:       (object) target
 *                  (object) bow
 * Returns:         (object) arrow
 */
public varargs object
reduce_and_miss(object target, object bow, object arrow)
{
    if (!objectp(arrow = reduce_arrow_stack(bow, arrow)))
        return 0;
        
    /* Let's hide arrows in the bushes, grass etc. */
    if (random(3))
        arrow->add_prop(OBJ_I_HIDE, 33 * random(3));
    
    if (arrow->move(environment(target), 1))
        return 0;
    
    return arrow;
} /* reduce_and_miss */

/* 
 * Function name:   reduce_and_hit
 * Description:     This function takes care of moving the arrow to the target.
 * Arguments:       (object) target
 *                  (object) bow
 * Returns:         (object) arrow
 */
public varargs object
reduce_and_hit(object target, object bow, object arrow)
{
    if (!objectp(arrow = reduce_arrow_stack(bow, arrow)))
        return 0;
    
    /* Let's move an arrow to the target. */
    if (arrow->move(target, 1))
        return 0;
    
    return arrow;
} /* reduce_and_hit */

/* 
 * Function name:   query_skill_gain
 * Description:     This function takes care of moving the arrow to the target.
 * Arguments:       1. (mixed) archer - The object or name of the archer using
 *                                      the ability
 *                  2. (int) skill - The skill being used
 * Returns:         (int) The valued amount
 */
public int
query_skill_gain(mixed archer, int skill)
{
    if (objectp(archer))
        archer = archer->query_real_name();
    
    if (!stringp(archer))
        return 0;
    
    return min(OPTIONS_MANAGER->query_option("#" + skill, archer), 100);
} /* query_skill_gain */

/* 
 * Function name:   add_skill_gain
 * Description:     This function increases the skill of the used ability.
 * Arguments:       1. (object) archer - The archer using the ability
 *                  2. (int) skill - The skill being used
 * Returns:         (status) 1/0 Success/Failure
 */
public status
add_skill_gain(object archer, int skill)
{
    string  name  = archer->query_real_name();
    int     value, basic;

    if (last_gain[name] && (time() - last_gain[name]) < GAIN_DELAY)
        return 0;
    
    value = query_skill_gain(archer, skill);
    basic = archer->query_base_skill(skill);
    
    find_player("carnak")->catch_msg("Add skill gain tried on skill: " + skill + "\n");
    /*
     * The %chance is ranged between 10% and 1% chance to gain a new skill level
     * to slow down progression.
     */
    if (value > 99 || random(value))
        return 0;
    
    last_gain[name] = time();
    
    OPTIONS_MANAGER->set_option("#" + skill, name, value + 1);
    
    /* Make sure to limit the raising of skills to the caps of the guild */
    if (!sizeof(filter(archer->query_guild_trainer_occ(),
        &operator(<)(basic,) @ &->sk_query_max(skill, 1))))
    {
        if (skill != SS_WEP_MISSILE)
            return 0;
        
        if (!archer->test_bit("krynn", GROUP, Q_BIT))
        {
            OPTIONS_MANAGER->set_option("#" + skill, name, value - 1);
            archer->catch_msg("You have reached the limit of your "
            + "understanding in archery, seek out the Loremaster for "
            + "further guidance.\n");
        }
    
        return 0;
    }
    
    return 1;
} /* add_skill_gain */