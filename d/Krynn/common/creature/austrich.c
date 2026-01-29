/**
 * An Austrich
 *
 * Austriches are found in the warmer plains areas of Krynn
 */
#include <files.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>

inherit "/d/Krynn/std/creature";
inherit "/std/act/action";
inherit "/std/act/domove";

#define C_STAT 0
#define C_ADJ 1
#define C_HEIGHT 2
#define C_WEIGHT 3

int fleeing = random(4);
string *description = ({ 
                       "ruffled", "scrawny", "careful", "stately", 
                       "patchy" });
                /* stat, adj, height, weight */
mixed *power = ({ 
                ({ 50, "small", 160, 140 }),
                ({ 70, "average-sized", 180, 170 }),
                ({ 100, "large", 200, 200 }),
                ({ 120, "powerful", 220, 220 }),
                ({ 140, "enormous", 250, 250 })
                });

void
set_relative_stats(int average, int *weight) {
    int sum = reduce( &operator(+)(,) , weight);

    for (int i = 0; i < sizeof(weight); i++) {
        set_base_stat(i, sizeof(weight) * average * weight[i] / sum);
    }
}

public void
create_creature()
{
    mixed config = one_of_list(power);
    set_gender(G_NEUTER);

    set_race_name("austrich");
    set_adj(({ config[C_ADJ], one_of_list(description) }));

    set_long("This is a " + short() + ". Its body is covered with black feathers with " +
             "white plumes. Its long featherless neck ends in a small head with a vicious" + 
             "looking beak attached to it.\n"); 

    set_m_in("prances in");
    set_m_out("prances");

    set_relative_stats(config[C_STAT], ({ 100, 120, 120, 75, 70, 100 }));

    set_knight_prestige(0);
    set_alignment(0);

    set_random_move(50);

    set_act_time(14);
    add_act("emote suddenly stands still, fully alert!");
    add_act("emote peers suspiciously around.");
    add_act("emote scans the horizon for threats.");
    add_act("emote hides its head in the sand.");

    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(CONT_I_VOLUME, config[C_WEIGHT] * 1100);
    add_prop(CONT_I_WEIGHT, config[C_WEIGHT] * 1000);
    add_prop(CONT_I_HEIGHT, config[C_HEIGHT]); 

    set_skill(SS_DEFENSE, 65);
    set_skill(SS_UNARM_COMBAT, 65);
    set_skill(SS_AWARENESS, 65);

    set_attack_unarmed(1, 50, 40, W_IMPALE, 20, "beak");
    set_attack_unarmed(3, 50, 40, W_BLUDGEON, 40, "right foot");
    set_attack_unarmed(2, 50, 40, W_BLUDGEON, 80, "left foot");

    set_hitloc_unarmed(1, 60, 5, "head");
    set_hitloc_unarmed(2, 40, 40, "left wing");
    set_hitloc_unarmed(3, 40, 40, "right wing");
    set_hitloc_unarmed(4, 15, 15, "neck");

    add_leftover(LEFTOVER_OBJECT, "wing", random(3));
    add_leftover(LEFTOVER_OBJECT, "beak", random(2), 0, 1, 1);
    add_leftover(LEFTOVER_OBJECT, "leg", random(3));
    add_leftover(LEFTOVER_OBJECT, "feather", random(15), 0, 0, 0, 5);

    ::create_creature();
}

varargs void
flee(int count = 1) {
    object last;
    while (count-- && last != environment()) {
        last = environment();
        this_object()->run_away();
    }
}

public void
attacked_by(object ob) {
    ::attacked_by(ob);

    if (fleeing) {
        set_alarm(2.0 * rnd(), 0.0, &flee());
        fleeing = random(2);
    }
}

void
special_attack(object enemy) {

}

