/* File         : /d/Khalakhor/guilds/tuatha/obj/shadow.c
 * Creator      : Teth@Genesis
 * Copyright:   : Daniel Mosquin
 * Date         : March 14, 1999
 * Purpose      : This is the guild shadow for the Tuatha.      
 * Related Files: 
 * Comments     : TODO: lots
 * Modifications: 
 */

#pragma save_binary
#pragma strict_types

inherit "/std/guild/guild_occ_sh";

#include "../guild.h"

/*
 * Function name : query_guild_name_occ
 * Description   : Query the name of the guild.
 * Returns       : string - The name of the guild.
 */

public string 
query_guild_name_occ() 
{ 
    return GUILD_NAME; 
}


/*
 * Function name : query_guild_style_occ
 * Description   : The style of the guild.
 * Returns       : string - The guild style.
 */

public string 
query_guild_style_occ() 
{
    return GUILD_STYLE; 
}

/*
 * Function name : query_guild_tax
 * Description   : The tax for the guild.
 * Returns       : int - The guild tax.
 */
public int 
query_guild_tax_occ() 
{ 
    return GUILD_TAX;
}

