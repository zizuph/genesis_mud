/*
 * waterdeep/std/guard_base.c
 * Functions for generating NPCs of the city guard of Waterdeep
 *
 * Created by Brine, Feb 2021
 * -----------------------------------------------
 * Feb 2022 Brine   Added special atk, assist friends, attack enemies
 */

#pragma strict_types

#include "../defs.h"

inherit WATERDEEP_NPC_BASE;
inherit "/d/Genesis/specials/npc/stat_based_specials";

#include <wa_types.h>

// Rank and title descriptions
#define RANKS               ({ "private", "sergeant", "lieutenant", "captain", \
                                "commander", "warden" })
#define TITLES              ({ "private", "armar", "civilar", \
                                "senior civilar", "commander", "warden" })

// Stats, skills and alignment
#define BASE_STATS          ({ 110, 110, 110, 85, 85, 100 })
#define STAT_MODS           ({ 1.0, 1.2, 1.4, 1.6, 2.2, 2.5 })
#define STAT_VARIANCE       5
#define SKILL_LEVELS        ({ 70, 80, 90, 100, 100, 100 })
#define BASE_ALIGNMENT      150

// Probabilities.
#define FEMALE_CHANCE       33

string *soldier_armours = ({
    WD_ARM_DIR + "g_boots", WD_ARM_DIR + "g_cuirass", WD_ARM_DIR + "g_helm",
    WD_ARM_DIR + "g_leggings"
});

mixed *soldier_weapons = ({
    ({ WD_ARM_DIR + "g_shield", WD_WEP_DIR + "g_armingsword" }),
    ({ WD_ARM_DIR + "g_shield", WD_WEP_DIR + "g_mace" }),
    ({ WD_WEP_DIR + "g_pike" })
});

string *soldier_descs = ({
    "alert", "vigilant", "watchful", "wary", "perceptive", "stalwart",
    "resolute", "steadfast", "serious-looking", "tough", "sturdy", "determined",
    "unwavering"
});

string *officer_descs = ({
    "stern", "austere", "eagle-eyed", "imposing", "august", "distinguished",
    "solemn", "proud", "lofty", "stony", "steely", "formidable"
});

string *battlecries = ({
    "Die, evildoer!",
    "Die, criminal!",
    "Enemy of Waterdeep, you shall pay for your foul deeds!",
    "The judgement of the Lords upon you, scoundrel!",
    "You shouldn't have messed with the City Guard!",
    "Then pay with your blood!"
});

// Prototypes
int select_gender();
void set_rank(int rank);
void arm_me();
void setup_guard(string rand_adj);
void add_acts_cacts();

// Internal variables
private int my_rank = -1;
private int my_alarm_id;

void
create_waterdeep_npc()
{
    set_name(({ "guard", "city guard" }));
    set_adj("waterdavian");

    set_alignment((BASE_ALIGNMENT + random(351)));

    add_prop(NPC_I_NO_UNARMED, 1);
}

int
select_gender()
{
    return (random(100) + 1) > FEMALE_CHANCE ? G_MALE : G_FEMALE;
}

int*
apply_stat_mods(int rank)
{
    int scalar = STAT_MODS[rank];
    // Convert int to float, multiply by scalar, convert back to int
    function multiply_by = ftoi @ &operator(*)(scalar) @ itof;

    return map(BASE_STATS, multiply_by);
}

void
set_skills(int rank)
{
    int primary_skill = SKILL_LEVELS[rank];
    int secondary_skill = primary_skill * 80 / 100;
    int tertiary_skill = primary_skill * 70 / 100;

    set_skill(SS_WEP_SWORD, primary_skill);
    set_skill(SS_WEP_POLEARM, primary_skill);
    set_skill(SS_WEP_AXE, primary_skill);
    set_skill(SS_WEP_CLUB, primary_skill);
    set_skill(SS_WEP_KNIFE, secondary_skill);
    set_skill(SS_2H_COMBAT, secondary_skill);
    set_skill(SS_UNARM_COMBAT, secondary_skill);

    set_skill(SS_DEFENCE, primary_skill);
    set_skill(SS_PARRY, primary_skill);
    set_skill(SS_BLIND_COMBAT, secondary_skill);

    set_skill(SS_AWARENESS, tertiary_skill);
    set_skill(SS_ACROBAT, tertiary_skill);
}

int
set_rank(int rank)
{
    my_rank = rank;

    switch (rank)
    {
        case 0:
        case 1:
            add_name("soldier");
            set_occupation("soldier");
            setup_guard(ONE_OF(soldier_descs));
            break;
        case 2:
        case 3:
            add_name("officer");
            set_occupation("officer");
            setup_guard(ONE_OF(officer_descs));
            break;
        default:
            // TODO: Commander, Warden
            return 0;
    }

    return 1;
}

int
query_rank()
{
    return my_rank;
}

void
setup_guard(string rand_adj)
{
    add_name(({ TITLES[my_rank], RANKS[my_rank] }));
    add_adj(rand_adj);

    select_race();
    set_gender(select_gender());

    set_short(rand_adj + " " + TITLES[my_rank] + " of the city guard");
    set_long(
        "This " + rand_adj + " " + query_subrace_name() + " is serving in the "
        + "City Guard of Waterdeep, " + HIS(TO) + " markings and demeanour "
        + "identifying " + HIM(TO) + " as " + LANG_ADDART(CAP(RANKS[my_rank]))
        + ".\n"
    );

    set_random_size_descs();

    set_skills(my_rank);
    set_stats(apply_stat_mods(my_rank), STAT_VARIANCE);

    add_prop(LIVE_I_NEVERKNOWN, 1);

    add_acts_cacts();

    replenish_me();
    arm_me();
}

void
add_acts_cacts()
{
    set_act_time(6);
    set_cact_time(6);

    add_act("stretch");
    add_act("hiccup");
    add_act("emote clears " + HIS(TO) + " throat.");
    add_act("cough");
    add_act("scratch chin");
    add_act("scratch back");
    add_act("scratch nose");
    add_act("emote inspects " + HIS(TO) + " armour.");
    add_act("emote systematically scans the area.");
    add_act("emote furls " + HIS(TO) + " brow.");

    add_cact("scowl");
    add_cact("snarl");
    add_cact("fume");
    add_cact("shout For Waterdeep!");
    add_cact("shout By the Nine Hells!");
    add_cact("shout To arms! Invaders are upon us!");
    add_cact("say I'll make short work of you, fiend!");
    add_cact("say You will pay dearly for this!");
}

void
arm_me()
{
    if (my_rank < CIVILAR)
    {
        // Explicit wielding before wearing to prevent all shield-bearers
        // from being left-handed
        equip(soldier_armours + ONE_OF(soldier_weapons), 1);
        command("wield all");
        command("wear all");
        return;
    }
}

void
try_attack(object enemy)
{
    my_alarm_id = 0;
    // defined in WATERDEEP_NPC_BASE
    try_kill_enemy(enemy, ONE_OF(battlecries));
}

void
init_living()
{
    // Attack the first enemy that enters our vicinity
    if (TP->query_prop(ENEMY_OF_WATERDEEP) && !my_alarm_id)
        my_alarm_id = set_alarm(itof(random(2) + 1), 0.0, &try_attack(TP));
}

int
special_attack(object enemy)
{
    object *wielded = query_weapon(-1);
    // Do a special attack every 8 rounds on average, or every 6 rounds if we
    // are high ranking
    int spec_freq = my_rank > 1 ? 6 : 8;
    // and only if we are wielding a weapon
    if (!sizeof(wielded) || random(spec_freq))
        return 0;

    string wep = wielded[0]->short();

    mixed *result = do_stat_based_attack(TO, enemy, W_BLUDGEON);

    if (!result || result[3] <= 0)
    {
        enemy->catch_tell(
            query_The_name(enemy) + " brings " + HIS(TO) + " " + wep +
            " around with fierce determination, but you avoid the attack.\n"
        );
        tell_watcher_miss(
            QCTNAME(TO) + " brings " + HIS(TO) + " " + wep + " around with " +
            "fierce determination, but " + QCTNAME(enemy) + " avoids the " +
            "attack.\n",
            enemy
        );
        return 1;
    }

    string how_damage;

    switch (result[0])
    {
        case 0..2:
            how_damage = "barely hurt.";
            break;
        case 3..9:
            how_damage = "hurt.";
            break;
        case 10..19:
            how_damage = "seriously hurt.";
            break;
        case 20..50:
            how_damage = "grievously wounded!";
            break;
        default:
            how_damage = "mortally wounded!";

    }

    enemy->catch_tell(
        query_The_name(enemy) + " brings " + HIS(TO) + " " + wep + " around " +
        "with fierce determination, hitting your " + result[1] + ".\nYou are "
        + how_damage + "\n"
    );
    tell_watcher(
        QCTNAME(TO) + " brings " + HIS(TO) + " " + wep + " around with " +
        "fierce determination, hitting " + QCTNAME(enemy) + "'s " + result[1] +
        ".\n" + QCTNAME(enemy) + " appears to be " + how_damage + "\n",
        enemy
    );

    if (enemy->query_hp() <= 0)
    {
        enemy->do_die(TO);
    }

    return 1;
}
