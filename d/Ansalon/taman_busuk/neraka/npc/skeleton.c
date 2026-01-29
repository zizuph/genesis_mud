/* Ashlar, 21 Aug 97 */

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <filter_funs.h>
#include <wa_types.h>
#include <money.h>
#include "/d/Ansalon/common/defs.h"
#include "../local.h"

inherit AM_FILE
inherit AUTO_TEAM

#define ONE_OF(x)   (x[random(sizeof(x))])

#define ADJ ({ "deadly", "dangerous", "evil", "frightening", \
    "fearful" })

void
my_set_all_hitloc_unarmed(mixed ac)
{
    set_hitloc_unarmed(A_BODY, ac, 45, "ribs");
    set_hitloc_unarmed(A_HEAD, ac, 15, "skull");
    set_hitloc_unarmed(A_LEGS, ac, 20, "shin bones");
    set_hitloc_unarmed(A_R_ARM, ac, 10, "left arm");
    set_hitloc_unarmed(A_L_ARM, ac, 10, "right arm");
}

void
create_krynn_monster()
{
    int k;
    
    set_name("skeleton");
    add_name("fighter");
    set_adj(ONE_OF(ADJ));
    set_race_name("skeleton");
    set_short(query_adj(0) + " skeleton fighter");

    set_gender(G_NEUTER);
    set_pick_up_team(({"skeleton"}));

    set_long("This is the skeleton of a man, animated and put into " +
    "service by dark priests. It has the stance of a fighter, and " +
    "a malicious light is shining in its empty eye sockets.\n");

    set_stats(({100+random(20),70+random(30),100+random(20),
        30, 30, 120+random(30)}));

    k = query_average_stat();
    k = k*k/20;

    set_alignment(-k);
    set_knight_prestige(k);

    set_skill(SS_WEP_SWORD, 70);
    set_skill(SS_PARRY, 60);
    set_skill(SS_DEFENCE, 20);
    set_skill(SS_UNARM_COMBAT, 50);

    add_prop(LIVE_I_UNDEAD, k/10);
    add_prop(LIVE_I_SEE_DARK, 2);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(LIVE_I_NO_CORPSE, 1);
    
    my_set_all_hitloc_unarmed( ({ 10, 10, 4, 10 }) );
    set_all_attack_unarmed(15,15);

    set_act_time(4);
    add_act("emote moves slightly.");
    add_act("emote stares at you with its empty eye sockets.");

    set_cact_time(2);
    add_cact("emote fights with a deadly grace.");

    set_aggressive("@@will_attack@@");
}

int
will_attack()
{
    if (TP->query_prop(LIVE_I_UNDEAD))
        return 0;
    else
        return 1;
}

public void
help_friend(object ob)
{
    if (ob && !query_attack() && present(ob, environment()))
    {
        command("kill " + lower_case(ob->query_real_name()));
    }
}


void
init_living()
{
    init_team_pickup();
    ::init_living();
}

void
arm_me()
{
    setuid();
    seteuid(geteuid(this_object()));

    clone_object(NARM + "rust_chain")->move(TO);
    clone_object(NARM + "wood_shield")->move(TO);
    clone_object(NWEP + "longsword")->move(TO);

    command("wear all");
    command("wield all");
    MONEY_MAKE_SC(random(25)+15)->move(this_object());

}

void
do_die(object killer)
{
    object ob = clone_object("/std/leftover");
    ob->leftover_init("bone","human");
    ob->move(E(TO));
    ob = clone_object("/std/leftover");
    ob->leftover_init("skull","human");
    ob->move(E(TO));
    ob = clone_object("/std/leftover");
    ob->leftover_init("bone","human");
    ob->move(E(TO));
    ob = clone_object("/std/leftover");
    ob->leftover_init("rib","human");
    ob->move(E(TO));
    ob = clone_object("/std/leftover");
    ob->leftover_init("rib","human");
    ob->move(E(TO));
    ::do_die(killer);
}


