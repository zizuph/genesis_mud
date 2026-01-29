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

#define REV_TYPE ({"cold-blooded", "powerful", "evil", "cruel", "dangerous"})
#define REV_PHYS ({"deadly", "horrifying", "skeletal", "hollow-eyed", "gaunt"})

string this_npc = "shade";

void arm_me();
nomask void create_monster()
{
    int i;
    string type, phys;

    seteuid(getuid());

    type = ONE_OF_LIST(REV_TYPE);
    phys = ONE_OF_LIST(REV_PHYS);

    npc_name = FOR_NPC;

    set_race_name("shade");
    add_name(npc_name);
    add_name("undead");
    add_adj(type);
    add_adj(phys);
    set_short(type + " " + phys + " shade");
    set_pshort(type + " " + phys + " shades");   
    set_long("This is a " + query_short() + ". It is a corpse that has " +
        "been reanimated. Stringy hair hangs from its head, the eyes " +
        "are sunken, and the mouth is nothing but a hole with rotting " +
        "teeth. The limbs are gaunt looking, and its fingernails are " +
        "jagged and cracked. The shade is clothed in rotting garments " +
        "that seem ready to fall off it.\n");

    add_prop(LIVE_I_NEVERKNOWN, 1);    
    add_prop(CONT_I_WEIGHT, 100*1000);
	add_prop(CONT_I_HEIGHT, 250);
	add_prop(LIVE_I_SEE_DARK, 80);
	add_prop(LIVE_I_SEE_INVIS, 80);
    add_prop(LIVE_I_UNDEAD,1);

    set_appearance_offset(40 + random(10));
    set_gender(G_NEUTER);
    set_pick_up_team(npc_name);

    set_stats(({180+random(50),
	    190+random(50),
		155+random(50),
		25+random(50),
		25+random(50),
		250}));

    set_skill(SS_DEFENCE,90);
    set_skill(SS_WEP_AXE,90);
    set_skill(SS_WEP_CLUB,90);
    set_skill(SS_WEP_SWORD,90);
    set_skill(SS_PARRY, 90);
    set_skill(SS_AWARENESS, 90);
    set_skill(SS_2H_COMBAT, 90);

    arm_me();

    set_act_time(5);
    add_act("watch");
    add_act("emote hisses at you.");
    add_act("emote claws at you.");
    add_act("emote stares off into the distance.");
    add_act("emote seems to wink in and out of your view.");
}


void
do_die(object killer)
{
	/*if (killer->query_alignment() < 0)
	{
		this_object()->set_exp_factor(10);
	
		killer->catch_tell("Since you are of an evil "
			+"alignment, you sense that the reward for "
			+"killing this creature is greatly diminished!\n");	
	}*/
		
    ::do_die(killer);
}


void arm_me()
{
    object arm, wep, gem;

    make_gems(TO,1);

    arm = clone_object(ARM_DIR + "rev_armour");
    arm ->move(this_object());
    arm = clone_object(ARM_DIR + "greaves");
    arm -> move(TO);
    arm = clone_object(ARM_DIR + "rev_robe");
    arm -> move(TO);

    wep = clone_object(WEP_DIR + "rev_axe");
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

    hitresult = enemy->hit_me(400 + random(200), W_BLUDGEON, me, -1);
    how = " with little effect";
    if (hitresult[0] > 0)
        how == " lightly";
    if (hitresult[0] > 5)
        how = " with " + HIS_HER(TO) + " claws, leaving traces of blood behind";
    if (hitresult[0] > 10)
//        how = " with " + HIS_HER(TO) + " claws, gouging your flesh";
        how = " with " + HIS_HER(TO) + " claws, gouging flesh";
    if (hitresult[0] > 15)
//        how = " with " + HIS_HER(TO) + " claws, shredding flesh as he goes";
        how = " with " + HIS_HER(TO) + " claws, shredding flesh as it goes";
    if (hitresult[0] > 20)
        how = " with " + HIS_HER(TO) + " claws, ripping flesh from the body";
    if (hitresult[0] > 25)
        how = " with " + HIS_HER(TO) + " claws so hard, that blood runs from the wounds";
    if (hitresult[0] > 30)
        how = " with " + HIS_HER(TO) + " claws, ripping large chunks of flesh and spraying blood everywhere";
    enemy -> catch_msg(QCTNAME(me) + " slashes you" + how + ".\n");
    tell_watcher(QCTNAME(me) + " slashes " + QTNAME(enemy) + " hard!\n"+
        capitalize(enemy->query_pronoun()) + " is slashed"+
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
