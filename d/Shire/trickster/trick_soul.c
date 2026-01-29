/*
 * trick_soul.c
 *
 * This object holds some general 'Trickster' feelings
 *
 *
 * This file was originally the shire_soul_cmd written by 
 * Tricky and several others.
 * Adapted by Dunstable for the Tricksters, a splinter
 * guild of the Hin Warriors by Tricky, 2-95
 *
 * Totally redone and reworked by Igneous June 97.
 */


#pragma save_binary
#pragma strict_types

#include "trickster.h"

inherit "/d/Shire/trickster/emotions.c";
inherit "/d/Shire/trickster/abilities.c";
inherit "/d/Shire/trickster/tlist.c";

/*
 * Return a proper name of the soul in order to get a nice printout.
 */
string
get_soul_id()
{
    return "trickster";
}

int
query_cmd_soul() 
{
    return 1;
}

/* This soul is auto_loading */
string
query_auto_load()
{
    return TRICKSTER_GUILD_SOUL;
}

mapping
query_cmdlist()
{
    return query_trickster_emotions() + 
    query_trickster_abilities() +
    query_trickster_list_verbs();
}

mixed
query_alarms()
{
    return get_all_alarms();
}
