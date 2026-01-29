#pragma strict_types
#pragma save_binary
 
inherit "/std/shadow";

#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include <formulas.h>
#include <composite.h>

object *present_objects;

public void
remove_tree_shadow()
{
    object no_move;
    
    if (no_move = present("_tree_climbers_curse_of_anti_levitation", shadow_who))
        no_move->remove_object();
    
    remove_shadow();
}

public void
add_present_objects()
{
    object no_move;
    
    setuid();
    seteuid(getuid());
    
    present_objects = all_inventory(environment(this_player()));
    
    if (no_move = present("_tree_climbers_curse_of_anti_levitation", shadow_who))
        return;
    else
        no_move = clone_object("/w/carnak/projects/test/tree_binding.c");
    
    no_move->move(shadow_who);
}

public void
climb_down_tree()
{
    shadow_who->catch_msg("You climb down the tree.\n");
    tell_room(environment(shadow_who), QCTNAME(shadow_who) + " climbs " +
    "down from a tree.\n", shadow_who);
    remove_tree_shadow();
}

public int
query_tree_shadow()
{
    return 1;
}

public int
check_seen(object for_obj)
{
    int hide;
    
    hide = (shadow_who->query_skill(SS_HIDE) / 2) + 50;
    
    if (!for_obj->query_wiz_level() &&
        !IN_ARRAY(for_obj, present_objects) && 
        for_obj->query_skill(SS_AWARENESS) < hide)
    {
        return 0;
    }
    
    if (!for_obj->query_wiz_level() &&
        !IN_ARRAY(for_obj, present_objects) &&
        for_obj->query_tree_shadow() &&
        for_obj->query_skill(SS_AWARENESS) < (hide/3))
    {
        return 0;
    }
    
    return shadow_who->check_seen(for_obj);
}

/*
 * Function name: attack_object
 * Description:   This is masked to start proximity decay when attacking
 *                a target, and to show the target that s/he is attacked
 *                from a distance. 
 */
public int
attack_object(object ob)
{
    int result;
    
    shadow_who->catch_msg("You jump down from the tree.\n");
    tell_room(environment(shadow_who), QCTNAME(shadow_who) + " jumps " +
    "down from a tree.\n", shadow_who);
    
    result = shadow_who->attack_object(ob);
    remove_tree_shadow();
    
    return result;
}

/*
 * Function name: attacked_by
 * Description:   This function removes any distance in case the archer
 *                gets ambushed, and starts decay in case the attack was
 *                expected.
 */
public int
attacked_by(object attacker)
{
    int result;
    
    shadow_who->catch_msg("You jump down from the tree.\n");
    tell_room(environment(shadow_who), QCTNAME(shadow_who) + " jumps " +
    "down from a tree.\n", shadow_who);
    
    result = shadow_who->attacked_by(attacker);
    remove_tree_shadow();
    
    return result;
}

public varargs string
short(object for_obj)
{
    return shadow_who->short() + " is hiding in a nearby tree";
}

/*
 * Function name: move_living
 * Description:   Posts a move command for a living object somewhere. If you
 *                have a special exit like 'climb tree' you might want to
 *                use set_dircmd() and set it to 'tree' in the room to allow
 *                teammembers to follow their leader.
 * Arguments:     how:      The direction of travel, like "north".
 *                          "X" for teleportation, team does not follow.
 *                          "M" if you write leave and arrive messages yourself.
 *                to_dest:  Destination
 *                dont_follow: A flag to indicate group shall not follow this
 *                          move if this_object() is leader
 *                no_glance: Don't look after move.
 *
 * Returns:       Result code of move:
 *                      0: Success.
 *                      3: Can't take it out of it's container.
 *                      4: The object can't be inserted into bags etc.
 *                      5: The destination doesn't allow insertions of objects.
 *                      7: Other (Error message printed inside move() func)
 */
public varargs int
move_living(string how, mixed to_dest, int dont_follow, int no_glance)
{
    int result;
    
    if (query_tree_shadow() && how != "X")
    {
        shadow_who->catch_msg("You must climb down from the tree first.\n");
        return 7;
    }
    else
    {
        result = shadow_who->move_living(how, to_dest, dont_follow, no_glance);
        remove_tree_shadow();
        
        return result;
    }
}