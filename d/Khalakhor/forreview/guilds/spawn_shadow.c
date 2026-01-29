#pragma save_binary
#pragma strict_types

#include <language.h>
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "guild.h"

inherit "/std/guild/guild_occ_sh";
inherit (GUILD_DIR + "spawn_appearance");
inherit (GUILD_DIR + "spawn_combat");

/*
 * Function name: query_guild_trainer_occ
 * Description:   Return one or more references to the object that define
 *                sk_train_max for the player. The returned refernce can
 *                be a string reference, an object pointer or an array of
 *                those.
 * Returns:       See description.
 */
nomask public mixed
query_guild_trainer_occ()
{
    return GUILD_TRAINER;
}

/*
 * Function name: query_guild_tax_occ
 * Description  : Returns the tax for our guild.
 * Returns      : int - the tax value
 */
nomask public int
query_guild_tax_occ()
{
    return GUILD_TAX;
}

/*
 * Function name: query_guild_name_occ
 * Description  : Returns the name of the guild
 * Returns      : string - the name
 */
nomask public string
query_guild_name_occ()
{
    return GUILD_NAME;
}

/*
* Function name: query_guild_style_occ
* Description  : Returns the sytle of the guild
* Returns      : string - the style
*/
nomask public string
query_guild_style_occ()
{
    return GUILD_STYLE;
}

/*
 * Function name: query_guild_not_allow_join_occ
 * Description  : Returns whether we should allow this player to join another
 *                guild if he wants to.
 * Arguments    : player - the player that wants to join
 *                type   - the type of the guild
 *                style  - the styles of the guild
 *                name   - the name of the guild
 * Returns      : 1 - if the player is rejected
 *                0 - if the player is accepted as a member
 */
nomask public int
query_guild_not_allow_join_occ(object player, string type, string style,
  string name)
{
    /* It is a redefinition, so call the original. All tests in the
    * guild are made in the joinroom before we allow the player to
    * join.
    */
    return ::query_guild_not_allow_join_occ(player, type, style, name);
}

/*
 * Function name: query_guild_keep_player
 * Description  : Tests whether we want to keep a player if he logs in.
 * Arguments    : player - the player to check
 * Returns      : 0 - if the player will be kicked out
 *                1 - the player will remain
 */
public int
query_guild_keep_player(object player)
{
    setuid(); seteuid(getuid());
    return 1;
}

/*
 * Function name: query_guild_title_occ
 * Description  : This function will return the title for the Tricksters.
 * Returns      : string - the title.
 */
nomask public string
query_guild_title_occ()
{
    return "Spawn of Chaos";
}

public mixed
query_guild_skill_name(int num)
{
}

/*
 * Function name: init_occ_shadow
 * Description  : This function is called when a player logs in. It adds
 *                the subloc to the player and make a query to the
 *                joinroom for the family name of the player.
 * Arguments    : string foobar - an init-string if there was any.
 */
nomask public void
init_occ_shadow(string args)
{
    setuid(); seteuid(getuid());

    setup_spawn_looks(shadow_who);
    setup_spawn_combat(shadow_who);
}
