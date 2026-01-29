/*
 * Revenant of Kryptgarden
 * by Finwe, Oct 2007
 */

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>

inherit FAERUN_NPC_BASE;
inherit "/d/Faerun/lib/assist_friend";
inherit "/d/Faerun/lib/gems";
inherit "/lib/unique";

#define REV_TYPE ({"cold-blooded", "bloodthirsty", "evil", "savage", "ruthless", "deadly", "horrifying", "malicious"})
#define REV_PHYS ({"athletic", "ravenous", "cunning", "pale-skinned", "vain", "dark", "arrogant", "haughty"})

#define UNDEAD_SH "/d/Faerun/kryptg/obj/undead_sh"

void arm_me();

nomask void create_monster()
{
    int i;
    string type, phys;

    seteuid(getuid());

    type = ONE_OF_LIST(REV_TYPE);
    phys = ONE_OF_LIST(REV_PHYS);

    npc_name = FOR_NPC;

    set_race_name("vampire");
    set_name(npc_name);
    add_name("_faerun_vampire_");
    add_name("vampire");
    set_short(type + " " + phys + " vampire");
    set_pshort(type + " " + phys + " vampires");   
    set_long("This is a " + query_short() + ". The corpse has recently emerged from the ground and roams the forest. She has fangs and sharp claws, and is the reanimated corpse of a human.\n");

    add_prop(LIVE_I_NEVERKNOWN, 1);    
    add_prop(CONT_I_WEIGHT, 100*1000);
	add_prop(CONT_I_HEIGHT, 250);
	add_prop(LIVE_I_SEE_DARK, 80);
	add_prop(LIVE_I_SEE_INVIS, 80);
    add_prop(LIVE_I_UNDEAD,1);

    set_gender(G_FEMALE);
    set_pick_up_team(npc_name);

    set_stats(({190+random(50),
	    190+random(50),
		180+random(50),
		50+random(50),
		50+random(50),
		250}));

    set_skill(SS_DEFENCE,90);
    set_skill(SS_WEP_AXE,90);
    set_skill(SS_WEP_CLUB,90);
    set_skill(SS_WEP_SWORD,90);
    set_skill(SS_PARRY, 90);
    set_skill(SS_AWARENESS, 90);
    set_skill(SS_2H_COMBAT, 90);
    set_alignment(-900);


//    set_alarm(1.0,0.0,"arm_me");
    arm_me();

    add_leftover(OBJ_DIR + "fang", "fang", 1, 0, 1, 1);
    add_leftover(OBJ_DIR + "fang", "fang", 1, 0, 1, 1);

    set_act_time(5);
    add_act("watch");
    add_act("emote hisses dangerously at you.");
    add_act("emote wipes her mouth, leaving behind a streak of fresh blood.");
    add_act("emote wrings her hands dangerously and hungrily.");
    add_act("emote growls threateningly.");
    add_act("emote licks her lips mysteriously.");


}

void arm_me()
{
    object arm, wep, gem;

    make_gems(TO,1);

    arm = clone_object(ARM_DIR + "vamp_boots");
    arm -> move(TO);

    arm = clone_object(ARM_DIR + "vamp_armour");
    arm -> move(TO);

    arm = clone_object(ARM_DIR + "vamp_cape");
    arm -> move(TO);

//    wep = clone_unique(WEP_DIR + "lifes", MAX_UNIQUE_ITEMS, WEP_DIR + "scimitar");
    wep = clone_object(WEP_DIR + "scimitar");
    wep -> move(TO);

    command("wear armours");
    command("wield weapon");

}

int
special_attack(object enemy)
{
    object me;
    mixed* hitresult;
    string how;
    me = TO;

    if (random(3))
        return 0;

    hitresult = enemy->hit_me(400 + random(200), W_IMPALE, me, -1);
    how = " with little effect";
    if (hitresult[0] > 0)
        how = " lightly";
    if (hitresult[0] > 5)
        how = " with " + HIS_HER(TO) + " fangs, puncturing some exposed flesh";
    if (hitresult[0] > 10)
        how = " with " + HIS_HER(TO) + " fangs, leaving smudges behind";
    if (hitresult[0] > 15)
        how = " with " + HIS_HER(TO) + " fangs, leaving traces of blood behind";
    if (hitresult[0] > 20)
        how = " with " + HIS_HER(TO) + " fangs, leaving trickles of blood behind";
    if (hitresult[0] > 25)
        how = " with " + HIS_HER(TO) + " fangs so hard, that blood runs from the wounds";
    if (hitresult[0] > 30)
        how = " with " + HIS_HER(TO) + " fangs, so hard, the flesh is shredded";

    if (hitresult[0]>5 && !enemy->query_prop(LIVE_I_UNDEAD))
    {
        setuid();
        seteuid(getuid());
        object shadow=clone_object(UNDEAD_SH);
        shadow->shadow_me(enemy);
    }
    
    enemy -> catch_msg(QCTNAME(TO) + " bites you" + how + ".\n");
    tell_watcher(QCTNAME(TO) + " bites " + QTNAME(enemy) + "!\n"+
        capitalize(enemy->query_pronoun()) + " is bitten"+
        how + ".\n", enemy);
    if (enemy->query_hp() <= 0)
        enemy->do_die(me);
    return 1;
}


void
init_living()
{
    ::init_living();
    init_team_pickup();
}

