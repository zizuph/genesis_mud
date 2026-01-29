#include <files.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>

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
        /* Remove the old arrow */
        object old_arrow = bow->query_projectile();
        old_arrow->remove_object();
        /* reset the bow */
        bow->unload_projectile();
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
    arrow->move(bow->query_wielded(), 1);
    arrow->load();
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
reduce_and_miss(object target, object bow, object arrows)
{
    object arrow;
    
    if (!objectp(arrow = reduce_arrow_stack(bow, arrows)))
        return 0;
        
    bow->move_projectile_to_env(environment(target), arrow);
    arrow->unload();
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
reduce_and_hit(object target, object bow, object arrows)
{
    object arrow;
    
    if (!objectp(arrow = reduce_arrow_stack(bow, arrows)))
        return 0;
    
    bow->move_projectile_to_target(target, arrow);
    arrow->unload();
    return arrow;
} /* reduce_and_hit */