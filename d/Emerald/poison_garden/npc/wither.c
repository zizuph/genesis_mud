#include "/d/Emerald/defs.h"

inherit EMERALD_MONSTER;
inherit "/d/Genesis/lib/intro";

#include "../garden.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <filter_funs.h>

#define DEBUG_WHO this_interactive()
#define DEBUG_ON
#include "/d/Emerald/sys/debug.h"

#define ENEMIES_PRESENT (query_enemy(-1) & all_inventory(environment()))

int heal(object enemy);
int powder(object enemy);

void create_emerald_monster()
{
    set_name("wither");
    add_name("_wither_");
    set_adj("willowy");
    add_adj("pallid");
    set_race_name("elf");
    set_long("Quite an odd figure...he is extremely pale and thin, even " +
	"for an elf; his hair is long and knotted...filled with twigs " +
	"and burrs, and his clothing is stained and torn.\n");
  
    set_stats(({ 30, 90, 45, 150, 150, 150 }));
    refresh_mobile();
  
    set_all_hitloc_unarmed(50);
  
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(LIVE_I_QUICKNESS, 100);
  
    // most of these skills are probably unnecessary, but who knows...?
    set_skill(SS_DEFENCE, 70);
    set_skill(SS_BLIND_COMBAT, 50);
    set_skill(SS_UNARM_COMBAT, 60);
    set_skill(SS_WEP_CLUB, 90);
    set_skill(SS_PARRY, 60);
    set_skill(SS_AWARENESS, 100);
    set_skill(SS_FORM_TRANSMUTATION, 100);
    set_skill(SS_FORM_ENCHANTMENT, 100);
    set_skill(SS_HERBALISM, 100);
    set_skill(SS_LOC_SENSE, 100);
    set_skill(SS_TRACKING, 80);
    set_skill(SS_HUNTING, 70);
    set_skill(SS_SPELLCRAFT, 90);
    set_skill(SS_SWIM, 70);
    set_skill(SS_CLIMB, 70);
  
    add_equipment(({ POISON_GARDEN_WEP + "druid_staff",
		     POISON_GARDEN_ARM + "robe" }));
  
    set_special_attack_percent(20);
    add_special_attack(heal, 80, "heal");
    add_special_attack(powder, 20, "powder");
}

int powder(object enemy)
{
    int i;
    object poison;
    object *who = FILTER_LIVE(all_inventory(environment()) -
	({ this_object() }));
  
    tell_room(environment(), QCTNAME(this_object()) + " throws some " +
	"white powder in the air!\n");
  
    for (i = sizeof(who); i--;)
    {
    	if (poison = clone_object(POISON_GARDEN_OBJ + "powder_poison"))
    	{
	    poison->move(who[i], 1);
    	}
    }
  
    return 1;
}

int heal(object enemy)
{
    tell_room(environment(), QCTNAME(this_object()) + " swallows a " +
	"small berry.\n");
   
    heal_hp(120 + random(200));
    add_fatigue(20 + random(50));
}
