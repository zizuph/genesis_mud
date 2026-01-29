

#pragma save_binary

#include <macros.h>
#include <ss_types.h>
#include <language.h>
#include <std.h>
#include "defs.h"
#include "worshipper.h"
#include "wcouncil.h"



int
is_calian_wiz(object tp)
{
    return SECURITY->query_wiz_dom(tp->query_real_name()) == "Calia";
}


int
is_worshipper(object player)
{
    return player->query_guild_name_lay() == GUILD_NAME;
}


