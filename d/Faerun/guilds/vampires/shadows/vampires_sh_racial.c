/* /d/Faerun/guilds/vampires/shadows/vampires_sh_racial.c
 *
 * Guildshadow for Vampires of Faerun, Nerull 2021
 *
 */

inherit "/std/guild/guild_race_sh";
inherit "/lib/commands";

#include <macros.h>
#include <const.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <composite.h>
#include "/std/combat/combat.h"
#include "../guild.h"


/*
 * Global variables
 */
public int      query_guild_not_allow_join_race(object player, 
                string type, string style, string name);
static int      query_guild_keep_player(object ob);
public void     init_race_shadow(string str);

int query_vampires_race()
{
    return 1;
}


public void
add_race_soul()
{
    setuid();
    seteuid(getuid());

    shadow_who->add_cmdsoul(VAMPIRES_GUILD_DIR 
    + "souls/vampires_guild_soul_race");

    shadow_who->update_hooks();
}


string
query_guild_title_race()
{ 
    return "";
}


public string
query_guild_name_race()
{
    return RACE_VAMPIRES_GUILD_NAME;
}


public string
query_guild_style_race()
{
    return TYPE_RACE;
}


public int
query_guild_tax_race()
{
    return TAX_RACE;
}


public mixed
query_guild_trainer_race()
{
    return ({ VAMPIRES_GUILD_DIR + "rooms/layrace_train",
           });
}


public int
query_guild_not_allow_join_race(object player, string type, 
string style, string name)
{
    if (::query_guild_not_allow_join_race(player, type, style, name))
    return 1;
}


public int
query_guild_keep_player(object ob)
{
    return 1;
}


public void
init_race_shadow(string str)
{
    object who = query_shadow_who();
    
    setuid();
    seteuid(getuid());

    ::init_race_shadow();
    
    set_alarm(0.0, 0.0, add_race_soul);
}


public void remove_shadow()
{
    shadow_who->remove_cmdsoul(VAMPIRES_GUILD_DIR 
    + "souls/vampires_guild_soul_race");

    shadow_who->update_hooks();

    ::remove_shadow();
}
