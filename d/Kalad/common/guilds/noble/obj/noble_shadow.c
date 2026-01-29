inherit "/std/guild/guild_race_sh";
#include "/d/Kalad/defs.h"
#pragma strict_types
#pragma save_binary
#define TAX 1

int
query_guild_tax_race()
{
   return TAX; /* Whatever you wish to set it to. */
}

public mixed 
query_guild_trainer_race()
{
   return ({});
}

void
noble_init(object ob)
{
    ob->update_hooks();
    setuid();
    seteuid(getuid());
}
    
void
noble_dispell(object ob)
{
    remove_guild_race();
}

int
query_guild_family_name()
{
    return 1;
}

int
query_guild_keep_player(object ob)
{
    if(ob->query_race_name() != "human")
        set_alarm(2.0,0.0,&noble_dispell(ob));
    else
        set_alarm(2.0,0.0,&noble_init(ob));
    return 1;
}

string 
query_guild_title_race()
{
    return "Alexander";
}


/*
* Function name: query_guild_style_race
* Description:   Get the style of this guild
* Returns:       String describing guild style
*/

string
query_guild_style_race()
{
   return "race";
}

string
query_guild_name_race()
{
   return "Nobles of Kabal";
}

string
query_presentation()
{
    return "Baron "+shadow_who->query_presentation();
}

