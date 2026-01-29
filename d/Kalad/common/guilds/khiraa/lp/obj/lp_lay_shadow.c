#pragma strict_types
#pragma save_binary

inherit "/std/guild/guild_lay_sh";
#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/guilds/khiraa/khiraa_defs.h"

/*
 * /d/Kalad/common/guilds/khiraa/lp/obj/lp_lay_shadow.c
 * Purpose    : The layman shadow of the Lich Priesthood. Doesn't do much
 * just returns styles and tax. Main code is in the occ shadow
 * Located    : 
 * Created By : Sarr Mar.20.97
 * Modified By: 
 */


public int
query_guild_tax_lay()
{
   return LP_LAY_TAX; /* Whatever you wish to set it to. */
}


public mixed 
query_guild_trainer_lay()
{
   return ({"/d/Kalad/common/guilds/khiraa/temple/rooms/temple_lp_train",
   "/d/Kalad/common/guilds/khiraa/temple/rooms/temple_dk_train" });
}

public int
query_guild_keep_player(object ob)
{
    /* Changed to 0 to close the guild. */
    return 0;
}

public string 
query_guild_title_lay()
{
    return "";
}

public string
query_guild_style_lay()
{
   return LP_LAY_STYLE;
}

public string
query_guild_name_lay()
{
   return LP_LAY_NAME;
}
