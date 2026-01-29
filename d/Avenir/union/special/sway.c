/*
 * This is a pseudo-ability, it doesn't actually use
 * any of the standardized ability code.
 */
#pragma strict_types
#include "special.h"
/*
 * Need permissions to clone.
 */
public void
create(void)
{
    setuid();
    seteuid(getuid());
}
/*
 * Add the nuke button.
 */
public void
remove_object(void)	{ destruct(); }


public int has_sway_override()
{
    if (U_IS_PUNISHED(TP, U_PUNISHED_NOSTART))
    {
        return 0;
    }
    if (wildmatch("/d/Avenir/union/room/*", file_name(environment(TP))))
    {
        return 1;
    }
    return 0;
}

/*
 * Special Ability: SWAY
 */
public int
do_ability(string str)
{
    string sway_type;

    if (strlen(str))
    {
        if(str != "unerringly" && str != "aggressively" && str != "defensively")
	    return NF("You can sway, sway unerringly, sway " +
                "aggressively or sway defensively.\n");
    }

    /* Can't have your mind occupied with spells, etc */
    if (TP->query_prop(LIVE_I_CONCENTRATE))
	return NF("Your mind is too occupied right now.\n");

    if (present(SWAY_ID, TP))
	return NF("You are already deep in the Sway.\n");

    if (present(SWAY_ID_UNERR, TP))
	return NF("You are already deep in the Unerring Sway.\n");

    if (present(SWAY_ID_AGG, TP))
	return NF("You are already deep in the Aggressive Sway.\n");

    if (present(SWAY_ID_DEF, TP))
	return NF("You are already deep in the Defensive Sway.\n");

    if (!TP->query_skill(SS_SWAY) && !has_sway_override())
	return NF("You would first need to learn how to do it!\n");

    if (random(TP->query_skill(SS_SWAY)) < random(8)
         && !has_sway_override())
    {
	TP->adjust_union_virtue(US_GRACE, -10);
	return NF("You fail to enter the Sway.\n");
    }

    /* Players can't be fighting when they enter it, but npcs can ;)  */
    /* Altered so players can enter sway when in battle. Arman, Jul 2020 */
/*
    if (TP->query_attack() && !TP->query_npc())
	return NF("You cannot enter into the Sway while in battle.\n");
*/

    /* Must be less than a % of max intox  */
    if (DRUNK(TP) >= DRUNK_LIMIT)
	return NF("You are far too drunk to gather your thoughts.\n");

    /* Takes some mana... */
    if (TP->query_mana() < SWAY_MANA)
	return NF("You lack the mental strength needed.\n");

    /* And fatigue  */
    if (TP->query_fatigue() < SWAY_FATIGUE)
	return NF("You are far too tired.\n");

    if ((time() - TP->query_prop(UNION_I_MOVE)) < 20)
    {
	return NF("Running back and forth from combat has you "+
	    "too confused to enter the Sway.\n");
    }

    /* Cannot enter it if the fire in the guildroom is out  */
    if (STATE <= SWAY_FLAME_COST)
    {
	return NF("The Flame is not strong enough for you to "+
	    "enter the Sway.\n");
    }

    TP->add_mana(-SWAY_MANA);
    TP->add_fatigue(-SWAY_FATIGUE);

    /* Only for real players. */
    if (query_interactive(TP))
	LIST->change_state(-SWAY_FLAME_COST, 1);

    if(str == "unerringly")
    {
        clone_object(SWAY_OBJ_INERR)->move(TP, 1);
        return 1;
    }

    if(str == "aggressively")
    {
        clone_object(SWAY_OBJ_AGG)->move(TP, 1);
        return 1;
    }

    if(str == "defensively")
    {
        clone_object(SWAY_OBJ_DEF)->move(TP, 1);
        return 1;
    }

    clone_object(SWAY_OBJ)->move(TP, 1);
    return 1;
}
