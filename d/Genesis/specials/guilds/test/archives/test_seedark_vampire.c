/*
 * Base Vampire testing NPC
 *
 * Created by Petros, February 2009
 */

#pragma strict_types

#include <ss_types.h>
#include <stdproperties.h>

inherit "/d/Genesis/specials/guilds/test/npcs/test_vampire";

/* 
 * Function:        create_test_npc
 * Description:     Mask this function to create your own test npc
 */
public void
create_test_npc()
{
    ::create_test_npc();
    add_prop(LIVE_I_SEE_DARK, 10);
    clone_object("/d/Genesis/specials/guilds/test/objects/standard_darkness")->move(this_object());
    set_name("seedark_vampire");
}
