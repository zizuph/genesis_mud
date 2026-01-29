#pragma save_binary
#pragma strict_types

#include "../guild.h"

inherit "/cmd/std/command_driver";
inherit DRAGONARMY_LIB + "help";
inherit DRAGONARMY_LIB + "idea";
inherit DRAGONARMY_LIB + "promotions";
inherit DRAGONARMY_LIB + "demotions";
inherit DRAGONARMY_LIB + "dlist";
inherit DRAGONARMY_LIB + "dattack";
inherit DRAGONARMY_LIB + "dragonfear";
inherit DRAGONARMY_LIB + "general";
inherit DRAGONARMY_LIB + "fund";

#include "emotes.c"

string 
get_soul_id()
{
    return GUILD_NAME;
}

int
query_cmd_soul() 
{
    return 0; /* this is not to be used as soul, should be only inherited */
}

mapping
query_cmdlist()
{
    return ([
      "didea"   : "_idea",
      "promote" : "promote_soldier",
      "demote"  : "demote_soldier",
#ifndef NO_DLIST
      "list"   : "list",
      "mlist"  : "list",
#endif
      "summon"	: "dragon_summon",

      "relinquish" : "make_general",
      "punish"	: "punish_soldier",
      "ban"	: "ban_from_dragonarmy",
      "lift"	: "remove_ban",
      "submit"	: "submit_life",
      "exterminate" : "exterminate",

      "add"	: "add_master_title",
      "remove"	: "remove_master_title",
      "charge"	: "set_master",
      "revoke"	: "remove_master",
      "check"	: "query_masters",

      "fundraising" : "fundrising",

    ]) + help_cmdlist() + emotes_cmdlist();
}

void
create()
{
    set_help_type(({ "dragonarmy" }));
    read_help_dir(DRAGONARMY_HELP);
}

