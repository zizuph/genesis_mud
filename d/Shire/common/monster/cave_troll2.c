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
        "This large and powerful looking troll is about 12 feet tall (4 meters)\n"+
        "He is awesome in power with a tough, scaly hide. His arms are like steel\n"+
        "cables and his scaly hide is pallid as are most cave-dwelling things.\n");
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
    add_act("burp");
    add_act("grin");
    add_act("emote stamps his feet loudly on the ground!");
    add_act("fart");
    add_act("growl");
    add_act(({"scream", "laugh"}));
    add_act("say Argh! Wanna see some blood!??");
    add_act("emote looks at you with death in his eyes.");

    set_cact_time(7);
    add_cact("shout HAHAHA! You got no chance, loser!");
    add_cact("say I am gonna rip your tongue out and eat it raw!");
    add_cact("say Say, you look like a fine meal to me...");
    add_cact("emote kicks you in the groin. Ouch!");
    add_cact("shout Hey folks! There is a PECK here, trying to kill me! Gee, how I am scared!");
    add_cact("laugh");
    add_cact("say Can't you fight no better than that, then try golf!");
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
    command("shout Yeah! Ready for battle .... Pecks!!");
    command("laugh");
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
