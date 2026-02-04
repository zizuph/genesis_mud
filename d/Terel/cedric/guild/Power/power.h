/*
 * Power.h
 * All the includes and a few functions used by every Song of Power.
 * Cedric 4/93
 */
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include <stdproperties.h>
#include "/d/Terel/common/terel_defs.h"
#include "/d/Terel/cedric/guild/guild_defs.h"
#include <wa_types.h>

/* How long must player sing before effect kicks in? */
int
query_casting_time()	
{
    return BASE_CAST_TIME;
}

/* How high must read_music be to copy into song book? */
int 
query_read_skill()  
{
    return BASE_READ_SKILL;
}

/* Returns a written description of the song's effect. Printed 
 * out when the player 'reads' the song.  */
string
query_purpose()
{
    return PURPOSE_DESC;
}
