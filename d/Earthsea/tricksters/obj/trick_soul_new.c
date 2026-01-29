/*
 * Creator: Ged
 * Date: 01.07.01
 * File: /w/ged/tricksters/trick_soul.c
 * Comments: This is tricksters soul file
 * Revision history:
 * 
 */

#pragma save_binary
#pragma strict_types

inherit "/cmd/std/command_driver";

#include "trick_attacks_new.h"
#include "trick_mischief.h"
#include "trick_emotions.h"
#include "trick_disguise.h"

string 
get_soul_id()
{
   return "Tricksters";
}

int query_cmd_soul() 
{ 
 return 1; 
}

mixed
query_alarms()
{
   return get_all_alarms();
}

mapping 
query_cmdlist()
{
    return query_trick_emotions() + query_trick_attacks()+
           query_trick_mischief() + query_trick_disguise();
}

