/*
 * /d/Calia/palace/specials/calian_utility.c
 *
 * This file stores some basic utility functions that can
 * be used elsewhere in the Calian code. Simply inherit
 * this file to obtain the use of these functions.
 *
 * Created by Petros, May 2008
 */
 
#pragma strict_types

// Includes
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <language.h>
#include <std.h>
#include "defs.h"
#include CALIAN_HEADER
#include COUNCIL_HEADER
#include RECRUITER_HEADER

// Defines to be commonly used

// Global Variables

// Prototypes
public int          is_calian_wiz(object player);
public int          is_calian(object player);


/* 
 * Function name:  is_calian_wiz
 * Description  :  Determines whether the person is a Calian Wizard
 *                 A Calian Wizard is one who is either the guild master
 *                 of the Calians or a part of the Calian domain.
 * Arguments    :  player - player requesting access
 * Returns      :  0/1 - is/is not calian wizard
 */
public int 
is_calian_wiz(object player)
{
    return (SECURITY->query_wiz_dom(player->query_real_name()) == "Calia"
            || IN_ARRAY(player->query_real_name(), 
                        SECURITY->query_guild_masters("calian")));
}

/* 
 * Function name:  is_calian
 * Description  :  Checks to see whether the person is part of the Calian
 *                 guild. This includes the guildmaster.
 * Arguments    :  none
 * Returns      :  void/nothing
 */
public int 
is_calian(object player)
{
    // A Calian is either a person who's in the guild or 
    // the guild master
    return (player->query_guild_name_occ() == GUILD_NAME
            || IN_ARRAY(player->query_real_name(), 
                        SECURITY->query_guild_masters("calian")));
}
