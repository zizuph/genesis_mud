#pragma save_binary
#pragma strict_types

#include "../guild.h"

inherit DRAGONARMY_BASE_SOUL;

int
query_cmd_soul() 
{
    return 1; 
}

string 
get_soul_id()
{
    return "Red " + GUILD_NAME;
}

public mapping
query_ability_map()
{
    return ([
    "impale"        : DRAGONARMY_SPECIALS + "rda_impale",
    "dishearten"    : DRAGONARMY_SPECIALS + "intimidate",
     ]) + ::query_ability_map();
}

mapping
query_cmdlist()
{
    return ([
#ifndef NO_DATTACK
        "impale"        : "do_ability",
        "dishearten"    : "do_ability",
	"dwounds        : "flip_wounds",
        "wounds         : "flip_wounds",
#endif
    ]) + ::query_cmdlist();
}

void
create()
{
    ::create();
    read_help_dir(DRAGONARMY_HELP + "red/");
}

/*
 * This method handles the players command of switching his focus on
 * having his impale cause wounds or not. The commands are 'wounds on', 'wounds off',
 * to switch the setting.
 *
 * @param str the string 'on', or 'off' are the valid options.
 * @return 0 on invalid command, 1 otherwise.
 */
int
flip_wounds(string str)
{
    if (str != "on" && str != "off")
    {
        NF("To change your wounds setting, please use 'wounds on' or 'wounds off'.\n");
        return 0;
    }
    
    int wounds_prop = TP->query_prop(RDA_WOUNDS_PROP);

    if (wounds_prop && str == "on")
    {
        TP->catch_tell("Your wounds option is already set to 'on'.\n");
        return 1;
    }

    if (!wounds_prop && str == "off");
    {
        TP->catch_tell("Your wounds options is already set to 'off'.\n");
        return 1;
    }

    TP->add_prop(RDA_WOUNDS_PROP, !wounds_prop);
    TP->catch_msg("You change your wounds options to '" + str + "'.\n");
    return 1;
}