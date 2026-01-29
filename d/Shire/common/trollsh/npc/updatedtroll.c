/* Trollshaw trolls
 * Updated so trolls assist other trolls in room.
 * -- Finwe February 2004
 *
 * Removed commented code, general tidying
 * -- Palmer 19 Aug 2006
 */

inherit "/d/Shire/orcmaker/team";

#include "/d/Shire/sys/defs.h"
#include "/d/Shire/common/trollsh/tunnel/local.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include "/d/Shire/common/make_money.h"


#define ARMOUR "/d/Shire/common/trollsh/arm/"

string shire_npc_name = "_trollshaw_npc_";

create_monster()
{
    seteuid(getuid());
    if(!IS_CLONE)
        return;
    create_guards(random(2));
}


create_guards(int i)
{
    object wep, arm;
    int y,z;
    string *color, *troll_type;

    // sets up arrays for different adjectives and types of trolls

    color  = (({"beastly", "blood-thirsty", "cruel", "deadly", "dreadful", 
        "evil", "ferocious", "fearless", "fearful", "foul", "hideous", 
        "horrible", "horrifying", "imposing", "powerful", "snarling", 
        "terrible", "terrifying"}));

    troll_type  = (({"young", "large", "warrior"}));



    // randomly chooses adjectives and type of troll to create

    y = random(sizeof(color));
    z = random(sizeof(troll_type));

    add_adj(color[y]);
    add_adj(troll_type[z]);
    add_prop(LIVE_I_NEVERKNOWN, 1);

    set_name("troll");
    add_name(shire_npc_name);

    add_adj(color[y]);
    add_adj(troll_type[z]);
    set_short(color[y] + " " + troll_type[z] + " troll");
    set_race_name("troll");
    set_long("This is a " + short() + ". It is one of many trolls " +
        "that inhabit the Trollshaws and a terror to travellers. " +
        "It has thick skin and a terrible look about it. The " +
        "troll towers over you and looks very powerful and evil.\n");

    set_alignment(-400 - random(100));
    set_gender(G_NEUTER);
    set_aggressive(0, 100);

    add_prop(CONT_I_WEIGHT, 500 * 1000);
    add_prop(CONT_I_HEIGHT, 450);
    add_prop(LIVE_I_SEE_DARK, 80);

    switch (troll_type[z]) // set's stats based on size
    {
        case "young": // young
        {
            set_stats(({120 + random(20),
                120 + random(20),
                125 + random(20),
                100 + random(20),
                100 + random(20),
                100}));
            break;
        }

        case "large": // large
        {
            set_stats(({130 + random(20),
                130 + random(20),
                135 + random(20),
                115+ random(20),
                115 + random(20),
                150}));
            break;
        }
        case "warrior": // warrior
        {
            set_stats(({150 + random(50),
                150 + random(50),
                155 + random(50),
                130 + random(50),
                130 + random(50),
                150 + random(5)}));
            break;
        }
    }

    set_act_time(6);
    add_act("emote snarls savagely as blood drips from his mouth!");
    add_act("scream evil");
    add_act("emote sniffs the air for trespassers.");
    add_act("emote looks you up and down dangerously.");
    add_act("emote stares at you with hate in his eyes!");
    add_act("command extinguish pitch");
    make_gold(1 + random(5));

    set_cact_time(2);
    add_cact("emote laughs pitifully at you.");
    add_cact("grin");
    add_cact("emote renews his attack on you with added hate in his eyes.");

    set_skill(SS_WEP_AXE, 90);
    set_skill(SS_WEP_POLEARM, 90);
    set_skill(SS_WEP_SWORD, 90);
    set_skill(SS_WEP_CLUB, 90);
    set_skill(SS_WEP_KNIFE, 90);
    set_skill(SS_2H_COMBAT,90);
    set_skill(SS_DEFENCE, 95);
    set_skill(SS_PARRY, 100);
    set_skill(SS_AWARENESS, 81);
    set_skill(SS_BLIND_COMBAT, 50);


    // Armours

    if(troll_type[z] == "warrior")
        arm = ({"rudeplate","leatherpl", "troll_torso", "rudeplate", "shield"})[random(5)];
    else
        arm = ({"rudeplate","leatherpl", "troll_torso", "rudeplate"})[random(4)];

    clone_object(ARM_DIR + arm)->move(TO);

    arm = ({"troll_helm", "troll_helm_steel", "troll_helm_iron"})[random(3)];
    clone_object(ARM_DIR + arm)->move(TO);
    arm = "wgaunt";
    clone_object(ARM_DIR + arm)->move(TO);

    // Weapons
    wep = ({"nastyclub","tr_scimitar","trollclub","trollaxe","trollmstar","trollhalb"}) [random(6)];
    clone_object(WEP_DIR + wep)->move(TO);

    command("wear armours");
    command("wield weapons");

    /* Cotillion XP Adjustment 2014-12-02 */
    set_exp_factor(125);
}


public void
do_die(object killer)
{
   killer->add_prop("_i_killed_trollshaw_trolls",killer->query_prop("_i_killed_trollshaw_trolls") + 1);

     ::do_die(killer);

}

int
query_knight_prestige()
{
    int i;

    i = this_object()->query_average_stat();
    i = i * i / 1;
    return i;
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

    hitresult = enemy->hit_me(350 + random(100), W_BLUDGEON, me, -1);
    how = " with little effect";
    if (hitresult[0] > 0)
        how == " lightly";
    if (hitresult[0] > 5)
        how = " with his claws, leaving traces of blood behind";
    if (hitresult[0] > 10)
        how = " with his claws, gouging the flesh";
    if (hitresult[0] > 15)
        how = " with his claws, shredding flesh as he goes";
    if (hitresult[0] > 20)
        how = " with his claws, ripping flesh from the body";
    if (hitresult[0] > 25)
        how = " with his claws so hard, that blood runs from the wounds";
    if (hitresult[0] > 30)
        how = " with his claws, ripping large chunks of flesh and spraying blood everywhere";
    enemy -> catch_msg(QCTNAME(me) + " slashes you" + how + ".\n");
    tell_watcher(QCTNAME(me) + " slashes " + QTNAME(enemy) + " hard!\n"+
        capitalize(enemy->query_pronoun()) + " is slashed"+
        how + ".\n", enemy);
    if (enemy->query_hp() <= 0)
        enemy->do_die(me);
    return 1;
}
