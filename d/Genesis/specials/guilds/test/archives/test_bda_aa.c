/*
 * BDA/AA testing NPC
 *
 * Created by Petros, April 2009
 */

#pragma strict_types

#include <ss_types.h>

inherit "/d/Genesis/specials/guilds/test/npcs/test_bda";

/* 
 * Function:        create_test_npc
 * Description:     Mask this function to create your own test npc
 */
public void
create_test_npc()
{
    ::create_test_npc();
    
    // Set up a few basics
    set_name("bda_aa");
    set_short("test bda aa npc");
    set_long("This is a test bda aa npc.\n");
    
    load_guild("aa_lay");
}

public int
special_attack(object target)
{
    command("slash");
    command("dfear");
    command("dbreath");
    command("smash");
    
    refresh_npc();
           
    return 0;
}
