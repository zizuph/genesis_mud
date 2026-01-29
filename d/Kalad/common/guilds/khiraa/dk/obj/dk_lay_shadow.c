#pragma strict_types
#pragma save_binary

inherit "/std/guild/guild_lay_sh";
#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/guilds/khiraa/khiraa_defs.h"

/*
 * /d/Kalad/common/guilds/khiraa/dk/obj/dk_lay_shadow.c
 * Purpose    : The layman shadow of the Death Knights
 * Located    : 
 * Created By : Sarr Mar.20.97
 * Modified By: 
 */

/* This will be used to define a custom surname for Death Knights */


public int
query_guild_tax_lay()
{
   return DK_LAY_TAX; /* Whatever you wish to set it to. */
}


public mixed 
query_guild_trainer_lay()
{
    return ({"/d/Kalad/common/guilds/khiraa/temple/rooms/temple_lp_train"});
}


public int
query_guild_keep_player(object ob)
{
    return 1;
}


public string 
query_guild_title_lay()
{
    return "";
}

public string
query_guild_style_lay()
{
   return DK_LAY_STYLE;
}

public string
query_guild_name_lay()
{
   return DK_LAY_NAME;
}
