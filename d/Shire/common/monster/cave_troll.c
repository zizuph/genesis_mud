/*
 * updated by Finwe, March 1999
 * removed 'english' phrases 
 */
inherit "/std/monster";

#include "rdefs.h"
#include <macros.h>
#include <ss_types.h>
#include <language.h>
#include <stdproperties.h>

object axe, plate;

create_monster() {
    set_name("agin");
    set_short("hideous looking cave troll");
    set_race_name("troll");
    set_long(
        "This large and powerful looking troll is very tall, " +
        "strong and hideous looking. His hide looks tough and " +
        "scaly. The troll looks like he could easily snap you " +
        "into pieces and would probably eat you if given the " +
        "chance.\n");
    add_prop(CONT_I_WEIGHT, 300*1000);
    add_prop(CONT_I_HEIGHT, 400);
    set_stats( ({ 94, 63, 87, 43, 50, 87 }) );
    set_hp(query_max_hp());

    set_skill(SS_UNARM_COMBAT, 30);
    set_skill(SS_WEP_SWORD,    60);
    set_skill(SS_WEP_AXE,      90);
    set_skill(SS_WEP_CLUB,     80);
    set_skill(SS_DEFENCE,      45);
    set_skill(SS_PARRY,        60);
    set_pick_up(43);
    set_aggressive(1);
    set_attack_chance(87);

    set_alignment(-280-random(200));
    set_act_time(6);
    add_act("growl");
    add_act("grin evil");
    add_act("emote growls something unintelligable.");
    add_act("emote snarls hungrily at you.");
    add_act("glare menacingly");
    add_act("emote shows his teeth at you.");
    add_act("emote growls something in a dark language at you.");
    add_act("emote looks at you with death in his eyes.");

    set_cact_time(7);
    add_cact("emote snaps at you with his teeth, nearly missing you.");
    add_cact("emote swings at you with his axe.");
    add_cact("emote growls savagely and attacks with renewed strength.");
    add_cact("emote works himself into a battle rage and attacks you.");
    add_cact("emote slashes you with his claws.");
    add_cact("emote yowls something unintelligable.");
    call_out("arm_me", 1);
}

arm_me()
{
    if(!axe || !present(axe, this_object()))
    {
	axe = clone_object(D_WEAPON+"trollaxe");
	axe ->move(this_object());
	command("wield waraxe");
    }
    if(!plate || !present(plate, this_object()))
    {
	plate = clone_object(D_ARMOUR+"trplate");
	plate ->move(this_object());
	command("wear plate");
    }
    command("snarls menacingly");
    command("howl evilly");
    call_out("check_door", 1);
}

reset_monster() {
    call_out("check_door", 1);
}

check_door()
{
    command("close door");
    command("lock door with key");
}
