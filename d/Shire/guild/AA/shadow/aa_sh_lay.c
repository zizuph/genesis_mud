/*
 * The Angmar Army layman shadow 
 * by Milan
 */

/* shadow_who - which object are we shadowing */

#pragma strict_types
#pragma save_binary

#include "../guild.h"

inherit "/std/guild/guild_lay_sh";

#include "./aa_base.h";


#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>

public mixed
query_guild_trainer_lay(){ return AA_TRAINER; }

int
query_guild_tax_lay() { return GUILD_TAX_LAY; }

string
query_guild_style_lay() { return GUILD_STYLE; }

string
query_guild_name_lay() { return GUILD_NAME; }

string
query_guild_title_lay()
{
    return query_aa_guild_title();
}

int
query_guild_not_allow_join_lay(object player, string type, string style, string name)
{
    if(player->query_wiz_level())
        return ::query_guild_not_allow_join_lay(player, type, style, name);
    if (::query_guild_not_allow_join_lay(player, type, style, name))
        return 1;
    return query_aa_guild_not_allow_join(player, type, style, name);
}

void
init_lay_shadow(string arg)
{
    init_aa_shadow();
}

