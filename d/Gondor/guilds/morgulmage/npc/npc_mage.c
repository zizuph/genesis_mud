/*
 *  /d/Gondor/guilds/morgulmage/npc/npc_mage.c
 *
 *  Default behaviour for NPC mages.
 *
 *  Created by Eowul, Februari 2009
 *  Based on the original work by Olorin
 */

#include <stdproperties.h>
#include <ss_types.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/guilds/morgulmage/morgulmage.h"

inherit "/d/Gondor/morgul/npc/ithil_monster.c";

public int query_undead();

public void
create_mage()
{
}

nomask void
create_ithil_monster()
{
    set_alignment(MORGUL_I_ALIGN_JOIN - 200);

    add_prop(LIVE_I_UNDEAD, query_undead);
    add_prop(LIVE_I_NO_CORPSE, 1);
    
    create_mage();
    
    add_name("mage");
    if (!sizeof(query_adjs())) set_adj(({"dark-skinned", "red-eyed"}));

    if (query_base_stat(SS_OCCUP) == 0)
        set_base_stat(SS_OCCUP, query_average_stat() + random(10) -5);
    
}

public int 
query_undead()
{
    return query_stat(SS_OCCUP);
}