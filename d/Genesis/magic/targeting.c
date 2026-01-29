
/*
 * Built-in spell targeting functions
 */

#include <cmdparse.h>
#include <language.h>
#include <filter_funs.h>

/*
 * Function name: spell_target_caster
 * Description:   Target a spell on the caster
 * Arguments:     string str - arguments to spell command
 * Returns:       An array of targets (the caster)
 */
public object *
spell_target_caster(object caster, string str)
{
    return ({ caster });
}

/*
 * Function name: spell_target_enemy
 */
public object *
spell_target_one_present_enemy(object caster, string str)
{
    object enemy = caster->query_attack();

    if (!enemy || 
        /* This shouldn't happen, but we'll check just in case */
        !present(enemy, environment(caster)))
    {
        caster->catch_tell("You aren't fighting anyone!\n");
        return ({});
    }

    return ({ enemy });
}

public object *
spell_target_present_enemies(object caster, string str)
{
    object *enemies = (object *)caster->query_enemy(-1) &
        all_inventory(environment(caster));

    if (!sizeof(enemies))
    {
        caster->catch_msg("There aren't any enemies present!\n");
        return ({});
    }

    return enemies;
}

public object *
spell_target_present_team(object caster, string str)
{
    object *team = caster->query_team_others() & 
        all_inventory(environment(caster)) + ({ caster });

    return team;
}

public object *
spell_target_present_team_others(object caster, string str)
{
    object *others = caster->query_team_others() &
        all_inventory(environment(caster));

    if (!sizeof(others))
    {
        caster->catch_tell("There are no other team members present.\n");
        return ({});
    }

    return others;
}

public object *
spell_target_one_present_living(object caster, string str)
{
    object *oblist;

    if (!strlen(str))
    {
        return ({ caster });
    }

    oblist = PARSE_THIS(str, "[at] / [on] [the] %l");

    if (!sizeof(oblist))
    {
	if ((str == "me") || (str == "myself") || 
            (str == caster->query_real_name()))
	{
	    return ({ caster });
	}

	caster->catch_tell("There is no " + str + " here.\n");
	return ({});
    }

    if (sizeof(oblist) > 1)
    {
        caster->catch_tell("You will have to be more specific!  You can only " +
            "select one target.\n");
        return ({});
    }
        
    return oblist;
}

public object *
spell_target_present_livings(object caster, string str)
{
    object *oblist = PARSE_THIS(str, "[at] / [on] [the] %l");

    if (!sizeof(oblist))
    {
	caster->catch_tell("Whom do you wish to target?\n");
	return ({});
    }

    return oblist;
}
    
public object *
spell_target_one_other_present_living(object caster, string str)
{
    object *oblist;

    if (!strlen(str))
    {
        caster->catch_tell("Whom do you wish to target?\n");
        return ({});
    }

    oblist = PARSE_THIS(str, "[at] / [on] [the] %l");

    if (!sizeof(oblist))
    {
        caster->catch_tell("Whom do you wish to target?\n");
        return ({});
    }

    if (sizeof(oblist) > 1)
    {
        caster->catch_tell("You will have to be more specific!  You can only " +
            "select one target.\n");
        return ({});
    }

    return oblist;
}

public object *
spell_target_one_present_non_living(object caster, string str)
{
    mixed *arr;

    if (!parse_command(str, all_inventory(caster) +
        all_inventory(environment(caster)), "[at] / [on] [the] %i", arr) ||
        !sizeof(arr = NORMAL_ACCESS(arr, 0, 0)))
    {
        caster->catch_tell("What do you wish to target?\n");
        return ({});
    }

    if (sizeof(arr) > 1)
    {
        caster->catch_tell("You will have to be more specific!  You can only " +
            "select one target.\n");
        return ({});
    }

    if (living(arr[0]))
    {
        caster->catch_tell("You cannot target a living being!\n");
        return ({});;
    }

    return arr;
}

/*
 * Function name: spell_target_present_non_livings
 * Description:   Target a spell on multiple non_living object
 * Arguments:     string str - arguments to spell command
 * Returns:       An array of targets
 */
public object *
spell_target_present_non_livings(object caster, string str)
{
    mixed *arr;

    if (!parse_command(str, all_inventory(caster) +
	all_inventory(environment(caster)), "[at] / [on] [the] %i", arr) ||
        !sizeof(arr = NORMAL_ACCESS(arr, 0, 0)))
    {
	caster->catch_tell("What do you wish to target?\n");
	return ({});
    }

    arr = FILTER_DEAD(arr);
    if (!sizeof(arr))
    {
	caster->catch_tell("You can not target only living beings!\n");
	return ({});
    }

    return arr;
}

/*
 * Function name: spell_target_one
 * Description:   Target a spell on one object
 * Arguments:     string str - arguments to spell command
 * Returns:       An array of targets
 */
public object *
spell_target_one_present_object(object caster, string str)
{
    mixed *oblist;

    if (!parse_command(str, all_inventory(caster) + 
        all_inventory(environment(caster)), "[at] / [on] [the] %i", oblist) ||
        !sizeof(oblist = NORMAL_ACCESS(oblist, 0, 0)))
    {
	caster->catch_tell("What do you wish to target?\n");
	return ({});
    }

    if (sizeof(oblist) > 1)
    {
	caster->catch_tell("You will have to be more specific!  You can only " +
	  "select one target.\n");
	return ({});
    }

    return oblist;
}

/*
 * Function name: spell_target
 * Description:   Target a spell on mutiple objects
 * Arguments:     string str - arguments to spell command
 * Returns:       An array of targets
 */
public object *
spell_target_present_objects(object caster, string str)
{
    object *arr;

    arr = FIND_STR_IN_ARR(str, (all_inventory(caster) +
	all_inventory(environment(caster))));

    if (!sizeof(arr))
    {
	caster->catch_tell("What do you wish to target?\n");
	return ({});
    }

    return arr;
}

/*
 * Function name: spell_target_one_distant_known_living
 * Description:   Target a spell on living known to the caster
 * Arguments:     string str - arguments to spell command
 * Returns:       An array of targets
 */
public object *
spell_target_one_distant_known_living(object caster, string str)
{
    object living;

    if (!strlen(str))
    {
        caster->catch_tell("Target whom?\n");
        return ({});
    }

    living = find_living(str);

    if (!objectp(living) || !caster->query_met(living) ||
        (living->query_wiz_level() && living->query_invis()))
    {
	caster->catch_tell("You do not sense " + LANG_POSS(str) + 
            " presence in the realms.\n");
	return ({ });
    }

    return ({ living });     
}

/*
 * Function name: spell_target_one_distant_living
 * Description:   Target a spell on a living in the game
 * Arguments:     string str - arguments to spell command
 * Returns:       An array of targets
 */
public object *
spell_target_one_distant_living(object caster, string str)
{
    object living;

    if (!strlen(str))
    {
        caster->catch_tell("Target whom?\n");
        return ({});
     }

    living = find_living(str);

    if (!objectp(living) || 
        (living->query_wiz_level() && living->query_invis()))
    {
	caster->catch_tell("You do not sense " + LANG_POSS(str) +
            " presence in the realms.\n");
	return ({ });
    }

    return ({ living });     
}

/* 
 * Target verification functions 
 */

public int
filter_present(object ob, object caster)
{
    object env = environment(ob);
    return ((env == caster) || (env == environment(caster)));
}
    
public object *
spell_verify_present(object caster, object *targets, string arg)
{
    return filter(targets, &filter_present(, caster));
}

