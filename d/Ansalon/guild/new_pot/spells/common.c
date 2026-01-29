/*
 * Common inheritable for prayers.
 */
#pragma strict_types

#include <macros.h>
#include <wa_types.h>
#include <composite.h>
#include "../guild.h"
#include "/d/Ansalon/common/defs.h"

/* Function name: query_spell_level
 * Description:   Internally used by the standing system
 * Returns:       int - the spell level
 */
public int 
query_spell_level(void)
{
    // Default to 1
    return 1;
}

/*
 * Function name: concentrate_msg
 * Description:   Give messages indicating that spell concentration has begun
 * Arguments:     1. (object)   The caster
 *                2. (mixed *)  The targets
 *                3. (string)   The arguments passed to the "cast" command
 */
public void
concentrate_msg(object caster, mixed *targets, string arg)
{
    caster->catch_tell("You clutch your black medallion and " +
	"pray to the Queen of Darkness.\n");

    tell_room(environment(caster), QCTNAME(caster) + " clutches " +
	caster->query_possessive() + " medallion and prays to the "+
	"Queen of Darkness.\n", ({ caster }), caster);
}

/*
 * Function:    hook_casting_shield_failure
 * Description: This gets called when the player fails to cast
 * 		the spell due to interference from worn shields.
 */
public void
hook_casting_shield_failure(object caster, object *shields)
{
    caster->catch_tell("You sense that "+
	FO_COMPOSITE_DEAD(shields, caster) +
	(sizeof(shields) == 1 ? " has " : " have ") +
	"interfered with your prayer to the Queen of Darkness.\n");
}

/*
 * Prayers listing is done via the medallion.
 */
public void
list_spells(void)	{ /* intentionally empty */ } 


#if 0
/*
 * The ability mapping for spells is generated
 * dynamically, so this should not be needed.
 */
#include "../admin/admin.h"

public int
query_spell_can_be_learned(object player)
{
    if (!objectp(player))
        return 0;
    
    // NPC's can always learn the spell.
    if (player->query_npc() || player->query_wiz_level())
        return 1;

    if (player->query_guild_name_occ() != GUILD_NAME)
        return 0;
    
    if (GUILD_ADMIN->query_priest_has_punishment(player->query_real_name(),
        P_SPELLS_RESTRICTED) || !player->has_allowed_priest_alignment())
    {
        return 0;
    }

    if ((player->query_skill(PS_GUILD_LEVEL) / 10 + 1) >= query_spell_level())
       return 1;
    
    return 0;
}
#endif

