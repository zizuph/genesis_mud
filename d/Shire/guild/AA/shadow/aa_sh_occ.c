/*
 * The Angmar Army occupational shadow 
 * by Milan
 */

/* shadow_who - which object are we shadowing */

#pragma strict_types
#pragma save_binary

#include "../guild.h"

inherit "/std/guild/guild_occ_sh";

#include "./aa_base.h";

#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>
#include <stdproperties.h>

// Global Variables
static int      last_retreat;       // Timestamp for the retreat ability.
static object   retreat_target;     // Stored target for retreat ability.

public mixed
query_guild_trainer_occ(){ return AA_TRAINER; }

int
query_guild_tax_occ() { return GUILD_TAX_OCC; }

string
query_guild_style_occ() { return GUILD_STYLE; }

string
query_guild_name_occ() { return GUILD_NAME; }

string
query_guild_title_occ()
{
    return query_aa_guild_title();
}

int
query_guild_not_allow_join_occ(object player, string type, string style, string name)
{
    if(player->query_wiz_level())
        return ::query_guild_not_allow_join_occ(player, type, style, name);
    if (::query_guild_not_allow_join_occ(player, type, style, name))
        return 1;
    FIXEUID;
    return query_aa_guild_not_allow_join(player, type, style, name);
}

void
init_occ_shadow(string arg)
{
    init_aa_shadow();

}

/*
 * Function name:   set_last_retreat
 * Description:     Sets the last retreat integer, to handle OBJ_M_NO_ATTACK
 * Arguments:       (int) retreat - the retreat time() integer value
 * Returns:         Nothing
 */
public void
set_last_retreat(int retreat)
{
    last_retreat = retreat;
} /* set_last_retreat */

/*
 * Function name:   set_retreat_target
 * Description:     Sets the last retreat target, to handle OBJ_M_NO_ATTACK
 * Arguments:       (object) retreat - the retreat target
 * Returns:         Nothing
 */
public void
set_retreat_target(object target)
{
    retreat_target = target;
} /* set_retreat_target */

/*
 * Function name: query_prop
 * Description  : Find the value of a property. This function is usually
 *                implemented as CFUN, i.e. as real C implementation in the
 *                gamedriver as it is used so often. You should NOT mask this
 *                function in code. Use VBFC on the property value, if you
 *                must.
 * Arguments    : mixed prop - the name of the property (usually a string).
 * Returns      : mixed - the value of the property, or 0 if the property did
 *                    not exist..
 */
public mixed
query_prop(string prop)
{
    int retreat_skill;

    if (prop == OBJ_M_NO_ATTACK)
    {
        retreat_skill = shadow_who->query_skill(SS_RETREAT);
        
        if ((time() - (retreat_skill / 25)) <= last_retreat &&
            objectp(retreat_target) &&
            environment(retreat_target) == environment(shadow_who))
            return shadow_who->query_The_name(this_player()) + " has recently "
            + "retreated and is outside of your reach.\n";
    }
    
    // All other properties, just return the base.
    return shadow_who->query_prop(prop);
} /* query_prop */