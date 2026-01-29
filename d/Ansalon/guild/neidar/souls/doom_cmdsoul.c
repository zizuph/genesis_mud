/*
 * NOTE:  See /cmd/std/soul_cmd.c for more examples of coding emotes.
 */

inherit "/d/Ansalon/guild/neidar/souls/cmdsoul";
 
#include "../guild.h"

public mapping
query_ability_map() 
{
    return ([
        "chop"          : DOOM_CHOP_ABILITY,
        "crush"         : DOOM_CHOP_ABILITY,
        "battlerage"    : DOOM_BATTLERAGE,
    ]);
}

mapping
query_cmdlist()
{
    return ([
      /* Command name : Function name */

      "battlerage"    : "do_ability",
      "chop"          : "do_ability",
      "crush"         : "do_ability",
      "clantitle"     : "set_clantitle",
      "doptions"      : "show_options",
      
    ]) +emote_cmdlist();
}
