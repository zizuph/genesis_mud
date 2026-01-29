/*
 * Vampire sire of Kryptgarden
 * by Finwe, Oct 2007
 * Added bite, which poison's players temporarily, turning them undead. 
 * Thanks Novo for the help!
 * Finwe, August 2008
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

#define UNDEAD_POISON "/d/Faerun/kryptg/obj/undead_convert_poison"

void arm_me();

nomask void create_monster()
{
    int i;
    string type, phys;

    seteuid(getuid());

    type = "terrible";
    phys = "pale-skinned";

    npc_name = FOR_NPC;

    set_race_name("vampire");
    set_name(npc_name);
    add_name("sire");
    add_name("_faerun_vampire_");
    add_name("vampire");
    set_adj(type);
    set_adj(phys);
    set_short(type + " " + phys + " vampire");
    set_pshort(type + " " + phys + " vampires");   
    set_long("This is a " + query_short() + ". He is a sire of vampires and looks beautiful. He looks strong with an angular shaped face. His eyes are piercing and unlike other vampires, has a aura of strength about him.\n");

    add_prop(LIVE_I_NEVERKNOWN, 1);    
    add_prop(CONT_I_WEIGHT, 100*1000);
	add_prop(CONT_I_HEIGHT, 250);
	add_prop(LIVE_I_SEE_DARK, 80);
	add_prop(LIVE_I_SEE_INVIS, 80);
    add_prop(LIVE_I_UNDEAD,1);

    set_gender(G_MALE);
    set_pick_up_team(npc_name);
    set_alignment(-900);

    set_stats(({190+random(50),
	    190+random(50),
		180+random(50),
		100+random(50),
		100+random(50),
		250}));

    set_skill(SS_DEFENCE,90);
    set_skill(SS_WEP_AXE,90);
    set_skill(SS_WEP_CLUB,90);
    set_skill(SS_WEP_SWORD,90);
    set_skill(SS_PARRY, 90);
    set_skill(SS_AWARENESS, 90);
    set_skill(SS_2H_COMBAT, 90);
    set_skill(SS_BLIND_COMBAT,90);
    set_skill(SS_BLIND_COMBAT, 90);

//    set_alarm(1.0,0.0,"arm_me");
    arm_me();

    add_leftover(OBJ_DIR + "fang", "fang", 1, 0, 1, 1);
    add_leftover(OBJ_DIR + "fang", "fang", 1, 0, 1, 1);

    set_act_time(5);
    add_act("emote smiles captivatingly.");
    add_act("emote beckons you to come to " + HIM_HER(TO) + ".");
    add_act("emote wrings " + HIS_HER(TO) + " hands dangerously and hungrily.");
    add_act("emote growls threateningly.");
    add_act("emote licks his lips mysteriously.");
    add_act("emote closes his eyes, suddenly lost in thought, smiling evilly.");
    add_act("emote smiles charmingly, revealing two white pearlescent "+
        "fangs.");
    add_act("emote looks around the area, absentmindedly scratching one "+
    "of his fangs."); 
    add_act("emote steps behind you, and you can feel his "+
           "hot breath on your neck.");
    add_cact("emote rises to his full height and power.");


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

    wep = clone_unique(WEP_DIR + "lifes", MAX_UNIQUE_ITEMS, WEP_DIR + "scimitar");
    wep -> move(TO);

    command("wear armours");
    command("wield weapons");

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

    hitresult = enemy->hit_me(500 + random(150), W_BLUDGEON, me, -1);
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
        object poison = clone_object(UNDEAD_POISON);
        poison->move(enemy, 1);
        poison->start_poison();
    }
    
    enemy -> catch_msg(QCTNAME(me) + " bites" + how + ".\n");
    tell_watcher(QCTNAME(me) + " bites " + QTNAME(enemy) + "!\n"+
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

