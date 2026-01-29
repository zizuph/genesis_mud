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
//#include "/d/Faerun/highroad/bridge/npcs/base_smart_npc.h"

#define NAME "koen"

//inherit FAERUN_NPC_BASE;
inherit "/d/Faerun/highroad/bridge/npcs/base_npc";
inherit "/d/Faerun/highroad/bridge/npcs/smart_npc";
inherit "/lib/unique";

object wep1;
object wep2;
object shield;

void
init_living()
{
    ::init_living();
}

void create_faerun_npc()
{
    ::create_faerun_npc();
    init_living();
    
    // customisation
    set_name(NAME);
    set_living_name(NAME);

    set_race_name("dwarf");

    set_short("muscular cold-eyed dwarf");
    set_long("You see a " + short() + ". He is in charge of the small " +
    	"contingent of guards protecting the barricade here and preventing " +
    	"people from approaching Neverwinter.\n"); 

    
    set_level(140, 90);
    set_alarm(2.0, 0.0, "arm_me");
    set_aggressive(0);
    set_aggressive(1);
    set_aggressive(1,100);
	
    // resist necro fear
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    
    add_ask(({"city", "neverwinter", "barricade"}), "say By order of Lord Nasher Alagondar noone is allowed to enter the City now!", 1);
    add_ask("plague", "say A horrible plague is killing people in Neverwinter. " +
    	"Everyone is looking for a cure but for now for help but no cure is known for now.\n"); 
    add_ask(({"lord", "nasher", "nasher alagondar", "alagondar"}), "say Lord Nasher is a ruler of Neverwinter. We would all be slaves of Luskan without him.");
}

void arm_me ()
{
    object arm, wep;

    wep1 = clone_unique(WEP_DIR + "m_waraxe", 5, WEP_DIR + "waraxe", 0, 99);
    wep1 -> move(TO);
    
    wep2 = clone_object(WEP_DIR + "waraxe");
    wep2 -> move(TO);

    shield = clone_object(ARM_DIR + "w_heater");
    shield -> move(TO);

    arm = clone_object(ARM_DIR + "fullplate");
    arm -> move(TO);
    arm = clone_object(ARM_DIR + "coif");
    arm -> move(TO);

    wep1->wield_me();
    command("wear armours");
}
