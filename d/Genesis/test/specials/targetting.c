
/*
 * Built-in spell targeting functions
 */

#include <cmdparse.h>
#include <language.h>
#include <filter_funs.h>

/*
 * Function name: target_actor
 * Description:   Target an ability on the actor
 * Arguments:     string str - arguments to spell command
 * Returns:       An array of targets (the actor)
 */
public object *
target_actor(object actor, string str)
{
    return ({ actor });
}

/*
 * Function name: target_enemy
 */
public object *
target_one_present_enemy(object actor, string str)
{
    object enemy = actor->query_attack();

    if (!enemy || 
        /* This shouldn't happen, but we'll check just in case */
        !present(enemy, environment(actor)))
    {
        actor->catch_tell("You aren't fighting anyone!\n");
        return ({});
    }

    return ({ enemy });
}

public object *
target_present_enemies(object actor, string str)
{
    object *enemies = (object *)actor->query_enemy(-1) &
        all_inventory(environment(actor));

    if (!sizeof(enemies))
    {
        actor->catch_msg("There aren't any enemies present!\n");
        return ({});
    }

    return enemies;
}

public object *
target_present_team(object actor, string str)
{
    object *team = actor->query_team_others() & 
        all_inventory(environment(actor)) + ({ actor });

    return team;
}

public object *
target_present_team_others(object actor, string str)
{
    object *others = actor->query_team_others() &
        all_inventory(environment(actor));

    if (!sizeof(others))
    {
        actor->catch_tell("There are no other team members present.\n");
        return ({});
    }

    return others;
}

public object *
target_one_present_living(object actor, string str)
{
    object *oblist;

    if (!strlen(str))
    {
        return ({ actor });
    }

    parse_command(str, ({}), "[at] / [on] [the] %s", str);
    oblist = PARSE_THIS(str, "%l");

    if (!sizeof(oblist))
    {
	if ((str == "me") || (str == "myself") || 
            (str == actor->query_real_name()))
	{
	    return ({ actor });
	}

	actor->catch_tell("There is no " + str + " here.\n");
	return ({});
    }

    if (sizeof(oblist) > 1)
    {
        actor->catch_tell("You will have to be more specific!  You can only " +
            "select one target.\n");
        return ({});
    }
        
    return oblist;
}

public object *
target_present_livings(object actor, string str)
{
    object *oblist = PARSE_THIS(str, "[at] / [on] [the] %l");

    if (!sizeof(oblist))
    {
	actor->catch_tell("Whom do you wish to target?\n");
	return ({});
    }

    return oblist;
}
    
public object *
target_one_other_present_living(object actor, string str)
{
    object *oblist;

    if (!strlen(str))
    {
        actor->catch_tell("Whom do you wish to target?\n");
        return ({});
    }

    oblist = PARSE_THIS(str, "[at] / [on] [the] %l");

    if (!sizeof(oblist))
    {
        actor->catch_tell("Whom do you wish to target?\n");
        return ({});
    }

    if (sizeof(oblist) > 1)
    {
        actor->catch_tell("You will have to be more specific!  You can only " +
            "select one target.\n");
        return ({});
    }

    return oblist;
}

public object *
target_one_other_present_living_or_enemy(object actor, string str)
{
    object *oblist;

    object enemy = actor->query_attack();


    if (!strlen(str))
    {
        if (!enemy || 
            /* This shouldn't happen, but we'll check just in case */
            !present(enemy, environment(actor)))
        {
            actor->catch_tell("You aren't fighting anyone!\n");
            return ({});
        }
        return ({ enemy });
    }

    oblist = PARSE_THIS(str, "[at] / [on] [the] %l");

    if (!sizeof(oblist))
    {
        actor->catch_tell("Whom do you wish to target?\n");
        return ({});
    }

    if (sizeof(oblist) > 1)
    {
        actor->catch_tell("You will have to be more specific!  You can only " +
            "select one target.\n");
        return ({});
    }

    return oblist;
}

public object *
target_one_present_non_living(object actor, string str)
{
    mixed *arr;

    if (!parse_command(str, all_inventory(actor) +
        all_inventory(environment(actor)), "[at] / [on] [the] %i", arr) ||
        !sizeof(arr = NORMAL_ACCESS(arr, 0, 0)))
    {
        actor->catch_tell("What do you wish to target?\n");
        return ({});
    }

    if (sizeof(arr) > 1)
    {
        actor->catch_tell("You will have to be more specific!  You can only " +
            "select one target.\n");
        return ({});
    }

    if (living(arr[0]))
    {
        actor->catch_tell("You cannot target a living being!\n");
        return ({});;
    }

    return arr;
}

/*
 * Function name: target_present_non_livings
 * Description:   Target an ability on multiple non_living object
 * Arguments:     string str - arguments to spell command
 * Returns:       An array of targets
 */
public object *
target_present_non_livings(object actor, string str)
{
    mixed *arr;

    if (!parse_command(str, all_inventory(actor) +
	all_inventory(environment(actor)), "[at] / [on] [the] %i", arr) ||
        !sizeof(arr = NORMAL_ACCESS(arr, 0, 0)))
    {
	actor->catch_tell("What do you wish to target?\n");
	return ({});
    }

    arr = FILTER_DEAD(arr);
    if (!sizeof(arr))
    {
	actor->catch_tell("You can not target only living beings!\n");
	return ({});
    }

    return arr;
}

/*
 * Function name: target_one
 * Description:   Target an ability on one object
 * Arguments:     string str - arguments to spell command
 * Returns:       An array of targets
 */
public object *
target_one_present_object(object actor, string str)
{
    mixed *oblist;

    if (!strlen(str) || !parse_command(str, all_inventory(actor) +
        all_inventory(environment(actor)), "[at] / [on] [the] %i", oblist) ||
        !sizeof(oblist = NORMAL_ACCESS(oblist, 0, 0)))
    {
	actor->catch_tell("What do you wish to target?\n");
	return ({});
    }

    if (sizeof(oblist) > 1)
    {
	actor->catch_tell("You will have to be more specific!  You can only " +
	  "select one target.\n");
	return ({});
    }

    return oblist;
}

/*
 * Function name: target
 * Description:   Target an ability on mutiple objects
 * Arguments:     string str - arguments to spell command
 * Returns:       An array of targets
 */
public object *
target_present_objects(object actor, string str)
{
    object *arr;

    arr = FIND_STR_IN_ARR(str, (all_inventory(actor) +
	all_inventory(environment(actor))));

    if (!sizeof(arr))
    {
	actor->catch_tell("What do you wish to target?\n");
	return ({});
    }

    return arr;
}

/*
 * Function name: target_one_distant_known_living
 * Description:   Target an ability on living known to the actor
 * Arguments:     string str - arguments to spell command
 * Returns:       An array of targets
 */
public object *
target_one_distant_known_living(object actor, string str)
{
    object living;

    if (!strlen(str))
    {
        actor->catch_tell("Target whom?\n");
        return ({});
    }

    living = find_living(str);

    if (!objectp(living) || !actor->query_met(living) ||
        (living->query_wiz_level() && living->query_invis()))
    {
	actor->catch_tell("You do not sense " + LANG_POSS(str) + 
            " presence in the realms.\n");
	return ({ });
    }

    return ({ living });     
}

/*
 * Function name: target_one_distant_living
 * Description:   Target an ability on a living in the game
 * Arguments:     string str - arguments to spell command
 * Returns:       An array of targets
 */
public object *
target_one_distant_living(object actor, string str)
{
    object living;

    if (!strlen(str))
    {
        actor->catch_tell("Target whom?\n");
        return ({});
     }

    living = find_living(str);

    if (!objectp(living) || 
        (living->query_wiz_level() && living->query_invis()))
    {
	actor->catch_tell("You do not sense " + LANG_POSS(str) +
            " presence in the realms.\n");
	return ({ });
    }

    return ({ living });     
}

/* 
 * Target verification functions 
 */

public int
filter_present(mixed ob, object actor)
{
    object env;

    object target;
    
    if (pointerp(ob))
    {
        target=ob[0];
    }
    
    if (objectp(ob))
    {
        target=ob;
    }

    if (!objectp(target) || !objectp(actor))
        return 0;

    env = environment(target);
    return ((env == actor) || (env == environment(actor)));
}
    
public object *
verify_present(object actor, object *targets, string arg)
{
    return filter(targets, &filter_present(, actor));
}

