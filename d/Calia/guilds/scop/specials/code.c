
#pragma save_binary

#include <macros.h>
#include <std.h>
#include "defs.h"
#include SPIRIT_HEADER
#include COUNCIL_HEADER

int
is_calian_wiz(object tp)
{
    return SECURITY->query_wiz_dom(tp->query_real_name()) == "Calia";
}

int
is_spirit(object player)
{
    return player->query_skill(SS_SPIRIT_CHOSEN);
}
