/*
 * ratman.c
 *
 * Basic ratman.
 *
 * Copyright (C): Tianar, Jul 2003
 *
*/
#pragma strict_types

// I N C L U D E D   F I L E S
#include "ldefs.h"

inherit SFLIVDIR + "base_ratman.c";

// G L O B A L   V A R S

// P R O T O T Y P E S

// P R I V A T E   F U N C T I O N S

// P U B L I C   F U N C T I O N S

/*
 *  FUNCTION: create_npc
 *  Arguments:
 *  Returns  :
 * 
 * Create the ratman and set basic stats/descriptions.
 *
*/
public void
create_monster()
{
    int npcsize = random(100) + 10;
    
    config_ratman(npcsize);
}
