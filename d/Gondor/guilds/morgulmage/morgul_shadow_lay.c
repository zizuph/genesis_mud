/*
 * /d/Gondor/guilds/morgulmage/morgul_shadow_lay.c
 *
 * The guild shadow for the Morgul Mages of Gondor. Since the guild
 * now takes up two slots, we have this additional shadow to occupy
 * the layman slot.
 *
 * Created by Eowul, September 2013
 *
 * 12-Jan-2019: Arman - Only full mages are occ+lay now.
 */

#pragma no_inherit
#pragma save_binary
#pragma strict_types

inherit "/std/guild/guild_lay_sh.c";

#include <const.h>
#include <composite.h>
#include <language.h>
#include <std.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "morgulmage.h"

public int
query_guild_tax_lay() {
    return GUILD_TAX_LAYMAN;
}


public string
query_guild_style_lay()
{
    return "magic";
}

public string
query_guild_name_lay()
{
    return GUILD_NAME;
}
