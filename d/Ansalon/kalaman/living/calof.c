/*
 * Calof, the boss
 *
 * 2004-02-19
 *   Fixed cloning of guards into the void. (cleanups) /Cotillion
 *
 */


#include <const.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include "../local.h"


inherit AM_FILE
inherit AUTO_TEAM
inherit "/lib/unique";
inherit "/d/Krynn/std/equip";

int guards_here = 0;

#define ADMIN     "/d/Krynn/solamn/vin/knight/admin/admin"

#define WEP1 KOBJ + "weapon/sceptre"
#define WEP2 KOBJ + "weapon/enforcer"
#define WEP3 KOBJ + "weapon/mace"

#define ARM1 KOBJ + "armour/gold_platemail"
#define ARM2 KOBJ + "armour/leggings"
#define ARM3 KOBJ + "armour/gauntlets"
#define ARM4 KOBJ + "armour/g_shield"
#define ARM5 KOBJ + "armour/r_robe"
#define ARM6 KOBJ + "armour/winged_helmet"
#define ARM7 KOBJ + "armour/platemail"
#define ARM8 "/d/Ansalon/common/arm/shield/shield25"


void
create_krynn_monster()
{
    set_pick_up_team(({"guard"}));
    set_max_team_size_auto_join(20);

    set_name("calof");
    set_living_name("calof");
    set_title("of Kalaman, Lord of the City");
    set_race_name("human");
    set_adj("tall");
    add_adj("thoughtful");
    set_gender(G_MALE);
    set_long("Before you stands the noble lord of Kalaman. He rules the " +
        "seaport with a firm yet fair hand. By the looks of him, " +
        "he seems no novice in either negotiations or in battle.\n");

    set_stats(({170, 200, 180, 150, 170, 130}));
    
    set_skill(SS_WEP_CLUB, 100);
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_PARRY, 100);
    set_skill(SS_BLIND_COMBAT, 90);
    set_skill(SS_AWARENESS, 80);

    set_alignment(1000);
    set_knight_prestige(-100);
    set_act_time(7);
    add_act("say I could really do with a war advisor.");
    add_act("emote strokes his chin thoughtfully.");
    add_act("say I must ensure Kalaman makes it through this war.");
    add_act("say The question is whether I should support the knights or " +
        "stay neutral until we figure out some way to defeat the dragons " +
        "that will surely destroy Kalaman if we oppose the Highlords.");

    set_cact_time(2);
    add_cact("raiseshield");
    add_cact("readyshield");
    add_cact("shout Guards! To me! Attacker in the palace!");
    add_cact("emote narrows his eyes threateningly.");
    add_cact("say You won't escape fool! My guards will cut you down!");

    add_ask(({"quest","task","help"}),"say I am sorry, I have nothing " +
        "for you to do.",1);
    add_ask(({"knights","knight","knighthood","knights of solamnia"}),
        "say My council is considering supporting the knighthood in their battle " +
        "against the dragonarmies, but we are not prepared to throw our " +
        "lot in with them if we cannot think up of a way to fight the dragons.",1);

    set_introduce(1);

    equip(({ 
        (random(2) ? clone_unique(WEP2, 4, WEP3) : 
            clone_unique(WEP1, 4, WEP3)),
            clone_unique(ARM1, 10, ARM7),
            clone_unique(ARM4, 5, ARM8),
            ARM2, ARM3, ARM5, ARM6 }));
}

void
attacked_by(object ob)
{
    object g1, g2;
    
    ::attacked_by(ob);
    
    if(ob->test_bit("Krynn", 1, 0))
    {
	(ADMIN)->perform_disgrace(ob, "Lord Gunthar",
            "of an attack on Lord Calof, " +
            "lawful ruler of the Solamnian city of Kalaman",0);
    }

    ::attacked_by(ob);

    if (guards_here == 0)
    {
        
        command("shout Guards! To me!");
        g1 = clone_object(KNPC + "elite_guard");
        g2 = clone_object(KNPC + "elite_guard");
        
        g1->arm_me();
	g1->move(environment());
	tell_room(environment(),
            "An elite guard rushes in and assists the lord of Kalaman!\n");
	g2->arm_me();
	g2->move(environment());
	tell_room(environment(),
            "An elite guard rushes in and assists the lord of Kalaman!\n");
	guards_here = 1;

        g1->command("say To Lord Calof!");
        g1->command("kill " +ob->query_real_name());
        g2->command("say Die foe!");
        g2->command("kill " +ob->query_real_name());
    }
}

int
special_attack(object enemy)
{
    int     attacktype,
        pen,
        att,
        wloc;

    mixed hitres;

    string *hitloc,
        *attack,
        how,
        weapon;


    if (!sizeof(query_weapon(-1)))
	return 0;

    attacktype = random(5);

    hitloc = ({"left arm","right arm","body","left leg","right leg"});

    attack = ({"swipe","swing"});

    weapon = query_weapon(-1)[0]->query_short();

    if (attacktype == 1)
    {
	pen = 530;
	hitres = enemy->hit_me(pen, W_BLUDGEON, TO, -1);

	wloc = random(5);
	att  = random(2);

	if (hitres[0] <= 0)
	    how = "his " + weapon + " barely missing";
	if(hitres[0] > 0)
	    how = "his " + weapon + " lightly grazing";
	if(hitres[0] > 10)
	    how = "his " + weapon + " badly bruising";
	if(hitres[0] > 20)
	    how = "his " +weapon+ " smashing";
	if (hitres[0] > 40)
	    how = "his " + weapon + " breaking the bones of";
	if (hitres[0] > 60)
	    how = "his " + weapon + " lethally injuring";

	enemy->catch_msg(QCTNAME(TO) + 
            " takes a mighty " +attack[att]
            + " at you, " + how + " your " + hitloc[wloc] + ".\n");

	tell_room(E(TO), QCTNAME(TO) + " takes a mighty " +attack[att]+ 
            " at " +QCTNAME(enemy) + ", " +how+ " " +POSSESSIVE(enemy)
            + " " + hitloc[wloc] + ".\n", ({ enemy, TO }));

	if (enemy->query_hp() <= 0)
	{
	    enemy->do_die(TO);
	}

	return 1;
    }

    return 0;
}

public void
do_die(object killer)
{
    // killer->set_alignment(killer->query_alignment() - 400);

    command("ungrip sceptre");
    command("emote tries to say something, but blood pours from " +
        "his mouth.");
    ::do_die(killer);
}

void
init_living()
{
    init_team_pickup();
    ::init_living();
}

