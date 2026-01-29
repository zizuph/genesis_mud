/* Undead Monk Initiate - Karath...Opening Day */
inherit "/d/Emerald/std/emerald_monster";
inherit "/d/Emerald/std/aid_npc";

#include "../defs.h"
#include <wa_types.h>
#include <const.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

public void
set_monk_level(int i)
{
    set_stats( ({i + random(20), i + random(20), i + random(20),
              i / 6 + random(20), i / 6 + random(20),
              i * 2 / 3 + random(20)}) );

    set_skill(SS_UNARM_COMBAT, i + random(10));
    set_skill(SS_DEFENCE, i + random(10));
    set_skill(SS_BLIND_COMBAT, i + random(10));
    set_skill(SS_AWARENESS, i + random(10));

    add_prop(LIVE_I_UNDEAD, i / 4);

    set_alignment(-i * 2 - random(100));
}

public void
create_monk()
{
}

nomask void
create_emerald_monster()
{
    set_race_name("monk");
    set_gender(G_NEUTER);

    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(LIVE_I_SEE_DARK, 100);
    add_prop(LIVE_I_SEE_INVIS, 99);

    set_random_move(8);
    set_restrain_path( ({ MONASTERY_DIR }) );

    set_act_time(6);
    add_act("emote mumbles something that could have resembled speech "+
        "if it had come from a body with lips and a throat.");
    add_act("emote lifts its head to the air as if trying to feel where "+
        "the warmth of life is coming from.");
    add_act("moan strange");
    set_cact_time(3);
    add_cact("moan violent");
    add_cact("emote stares at you with soulless eyes.");
                
    create_monk();
  
    add_adj("undead");
}

int
palm(object enemy)
{
    mixed* hitresult;
    string how;
    int phurt, mypow;

    mypow = query_skill(SS_UNARM_COMBAT) + query_stat(SS_STR);

    if (query_combat_object()->cb_tohit(W_RIGHT, mypow * 2 / 3, enemy))
    {
        enemy->catch_tell(query_The_name(enemy) +
            " suddenly strikes out at " +
            "you with his palm flying towards your face! You "+
            "instinctively dodge, and its fist flies right "+
            "where your chin used to be!\n");
        tell_watcher_miss(QCTNAME(this_object()) + 
            " suddenly strikes out with " +
            "its palm at "+QTNAME(enemy)+"'s face! "+ enemy->query_pronoun() +
            " instinctly dodges " + enemy->query_possessive() + 
            " head, and " + QTNAME(this_object()) + "'s palm flies " +
            "just past where " + enemy->query_possessive() + 
            " chin used to be!\n", enemy);
        return 1;
    }

    hitresult = 
        enemy->hit_me(mypow, W_BLUDGEON, this_object(), W_RIGHT, A_HEAD);

    switch(hitresult[0])
    {
        case 0:
            how = "harmless blow to the cheek";
            break;
        case 1..5:
            how = "glancing blow off the cheekbone";
            break;
        case 6..10:
            how = "solid blow to the brow";
            break;
        case 11..20:
            how = "sharp blow to chin";
            break;
        case 21..40:
            how = "crunching blow to the chin";
            break;
        case 41..80:
            how = "devastating smash on the nose";
            break;
        default:
            how = "deadly impact on the temple";
            break;
    }

    enemy->catch_tell(query_The_name(enemy) +
        " suddenly strikes out with its "+
        "palm at your head! Its sudden blow scores a "+how+".\n");
    tell_watcher(QCTNAME(this_object()) + 
        " suddenly strikes out with its palm at " + QTNAME(enemy) +
        "'s head! Its sudden blow scores a " + how + ".\n", enemy);

    if (enemy->query_hp() <= 0)
    {
        enemy->do_die(this_object());
    }

    return 1; 
}

int
sidekick(object enemy)
{
    string how;
    int delay, mypow;

    mypow = query_skill(SS_UNARM_COMBAT) + query_stat(SS_STR);

    if (query_combat_object()->cb_tohit(W_RIGHT, mypow * 2 / 3, enemy))
    {
        enemy->catch_tell(query_The_name(enemy) + 
            " unleashes a powerful snapkick "+
            "at your leg, but you step back a bit and its foot "+
            "swings harmlessly in front of you!\n");
        tell_watcher_miss(QCTNAME(this_object()) + 
            " unleashes a powerful snapkick "+
            "at "+QTNAME(enemy)+"'s leg, but "+ enemy->query_pronoun() +
            "steps back, and " + QTNAME(this_object()) + "'s foot swings " +
            "harmlessly in front of " + enemy->query_possessive() + "!\n",
            enemy);
        return 1;
    }

    mypow = random(mypow / 2) + random(mypow / 2);

    switch (mypow)
    {
        case 1..19: 
            how = "slight thump on the outside thigh";
            delay = 2;
            break;
        case 20..39:
            how = "glancing blow on the inner thigh";
            delay = 4;
            break;
        case 40..59:
            how = "solid blow on the upper thigh";
            delay = 6;
            break;
        case 60..79:
            how = "pounding blow on the front thigh";
            delay = 8;
            break;
        default: 
            how = "resounding pummel on the outside knee";
            delay = 12;
            break;
    }

    enemy->catch_tell(query_The_name(enemy) + 
        " unleashes a powerful snapkick "+
        "at your leg, landing its foot with a "+how+"."+
        " You step back, wincing and holding back attacks "+
        "for a moment while the pain subsides.\n");
    tell_watcher(QCTNAME(this_object()) + " unleashes a powerful snapkick "+
        "at " + QTNAME(enemy) + "'s leg, landing its foot with a "+
        how+". " + capitalize(enemy->query_pronoun()) + 
        " steps back, wincing and holding back attacks for a moment " +
        "while the pain subsides.\n", enemy);

    enemy->add_attack_delay(delay, 1);

    return 1;
}
