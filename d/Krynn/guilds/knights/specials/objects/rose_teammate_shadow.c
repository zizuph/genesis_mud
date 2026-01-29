/*
 * Rose Knight Teammate Shadow
 *
 * When a Rose Knight leads a team, we want to grant to the entire
 * team not only discipline, but also the ability to withstand
 * dragonfear. This is a very special ability reserved for the most
 * dedicated of Knights.
 *
 * Created by Petros, December 2013
 *
 * 2018-11-13: The rose knight discipline boost kept on interfering with other
 *             discipline items, fixed it and moved it here. - Carnak
 */
 
#include <stdproperties.h>
#include <std.h>
#include <macros.h>

#include "/d/Krynn/common/defs.h"
#include "../../guild.h"

inherit "/std/shadow";

#include "/d/Genesis/specials/debugger/debugger_tell.h"

int extra_dis = 0;

/*
 * Function name:   add_rose_knight_discipline
 * Description:     Adds discipline to any member of a rose knights team.
 * Arguments:       (object) leader - The rose knight leader
 * Returns:         (status) 1 - Successful, 0 - Failed.
 */
public status
add_rose_knight_discipline(object leader)
{
    string  name;
    int     stat;
    
    if (!objectp(leader) || extra_dis)
        return 0;
    
    stat =  leader->query_base_stat(SS_DIS) / 20 +
            leader->query_knight_sublevel();
    name =  leader->query_name();
    
    switch(stat)
    {
        case 0..9:
        shadow_who->catch_msg("The confident leadership of " + name + " gives "
        + "you courage.\n");
             break;
             
        case 10..13:
        shadow_who->catch_msg("The bold leadership of " + name + " steadies "
        + "your resolve.\nYou grow more determined.\n");
        tell_room(environment(shadow_who), QCTNAME(shadow_who) + " seems more "
        + "determined to face evil.\n", ({ shadow_who }), shadow_who);
             break;
             
        case 14..17:
        shadow_who->catch_msg("The inspired leadership of " + name + " kindles "
        + "fire in your heart.\nYou grit your teeth, ready to withstand any "
        + "evil on the face of Krynn.\n");
        tell_room(environment(shadow_who), QCTNAME(shadow_who) + " grits "
        + shadow_who->query_possessive() + " teeth, a daring look in "
        + shadow_who->query_possessive() + " eyes.\n", ({ shadow_who }),
        shadow_who);
             break;

        default:
        shadow_who->catch_msg("The epic leadership of " + name + " heartens "
        + "your spirit.\nYou smile proudly, confident and relaxed.\n");
        tell_room(environment(shadow_who), QCTNAME(shadow_who) + " smiles "
        + "proudly and looks confident and relaxed.\n", ({ shadow_who }),
        shadow_who);
             break;
    }
    
    extra_dis = stat;
    shadow_who->set_stat_extra(SS_DIS,
        shadow_who->query_stat_extra(SS_DIS) + extra_dis);
    
    return 1;
} /* add_rose_knight_discipline */

/*
 * Function name:   remove_rose_knight_discipline
 * Description:     Removes any discipline gained from teaming with a knight.
 * Arguments:       None
 * Returns:         Nothing
 */
public void
remove_rose_knight_discipline()
{
    shadow_who->set_stat_extra(SS_DIS,
        shadow_who->query_stat_extra(SS_DIS) - extra_dis);
    extra_dis = 0;
} /* remove_rose_knight_discipline */

public int
has_rose_teammate_shadow()
{
    return 1;
}

public void
remove_rose_teammate_shadow()
{
    if (extra_dis)
        remove_rose_knight_discipline();
    
    remove_shadow();
}

/*
 * Function:    query_can_control_dragonfear
 * Description: This function gets called by the dragon_fear
 *              object to determine whether this person can
 *              control dragonfear. If true, then a message
 *              shows their control via the hook function.
 */
public int
query_can_control_dragonfear()
{
    object player = shadow_who;
    object leader = player->query_leader();
    if (!objectp(leader))
    {
        return 0;
    }

    if (leader->query_knight_level() == L_ROSE
        && (environment(leader) == environment(player)))
    {
        // If the leader is a Rose Knight and the Knight is in the same
        // room as this teammate, then the teammate can control dragonfear
        // also.
        return 1;
    }

    return 0;
}

/*
 * Function:    hook_controlled_dragonfear
 * Description: This function shows the messages that indicate the
 *              player was able to control the dragonfear.
 */
public void
hook_controlled_dragonfear()
{
    object player = shadow_who;
    object leader = player->query_leader();
    
    if (!objectp(leader))
        return;

	player->catch_msg("Terror sweeps over you, threatening to overcome you "
    + "fully. Looking towards your fearless Solamnian leader, " + QTNAME(leader)
    + ", you feel the divine courage of Paladine wash over you, allowing you "
    + "to fight the fear back and keep control of yourself.\n");
	tell_room(E(player), QCTNAME(player) + " looks toward " + QTNAME(leader)
    + " as the dragonfear sweeps over " + HIM(player) + ", and a divine "
    + "courage washes over " + HIM(player) + " and allows " + HIM(player) + " "
    + "to keep control of " + HIM(player) + "self.\n", player);
}

/*
 * Function name:   enter_env
 * Description:     When we enter an interactive environment, add a subloc to
 *                  indicate that the person is writing something.
 * Arguments:       (object) to - the object we are entering.
 *                  (object) from - the object we come from.
 * Returns:         Nothing
 */
void
enter_env(object to, object from)
{
    shadow_who->enter_env(to, from);
    
    object leader = shadow_who->query_leader();
    
    // If the leader is not present, remove discipline boost.
    if (extra_dis && (!objectp(leader) ||
        !present(leader, environment(shadow_who))))
        remove_rose_knight_discipline();
} /* enter_env */

/*
 * Function name:   init_living
 * Description:     This is called when we meet another living object.
 * Arguments:       None
 * Returns:         Nothing
 */
void
init_living()
{
    shadow_who->init_living();
    
    if (!extra_dis && interactive(this_player()))
    {
        object leader = shadow_who->query_leader();
        
        // If we do not have the discipline boost, add it.
        if (this_player() == leader)
            add_rose_knight_discipline(leader);
    }
} /* init_living */