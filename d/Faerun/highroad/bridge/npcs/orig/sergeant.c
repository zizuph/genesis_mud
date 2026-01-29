/*
 * Sergeant, guard leader, bridge near Neverwinter 
 * by Kehr, October 2006
 */

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>
#include "/d/Faerun/highroad/bridge/npcs/base_smart_npc.h"

#define NAME "koen"

inherit "/d/Faerun/highroad/bridge/npcs/base_smart_npc";

void
init_living()
{
    ::init_living();
    init_team_pickup();
    write("INIT LIVING CALLED\n");
}

void create_faerun_npc()
{
    ::create_faerun_npc();
    init_living();
    
    // customisation
    add_name(NAME);
    set_race_name("dwarf");
    set_name("__bridge_guard");
    
    set_short("muscular cold-eyed dwarf");
    set_long("You see a .\n");
    
    set_level(140, 90);
	set_alarm(2.0, 0.0, "arm_me");
}

void arm_me ()
{
	object arm, wep;

	wep = clone_unique(WEP_DIR + "m_waraxe", 5, WEP_DIR + "waraxe", 0, 99);
    wep -> move(TO);
    wep = clone_unique(WEP_DIR + "m_waraxe", 5, WEP_DIR + "waraxe", 0, 99);
    wep -> move(TO);

    //arm = clone_object("/d/Krynn/common/armours/kite-shield.c");
    //arm -> move(TO);
    
    command("wear armours");
    command("wield weapons");

    fightmode = FIGHT_SHIELD_WEP;
}
