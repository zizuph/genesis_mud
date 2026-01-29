/*
 * SHELOB
 * /d/Gondor/mordor/npc/shelob.c
 *
 * Shelob is an evil spider, huge and dangerous. When "her ladyship" bites
 * you with her poison, you will loose consciousness for some time. This
 * will in fact be the start of a quest for two players where one players
 * needs to free his mate from the orcs that take him after looses
 * concsiousness.
 *
 * Shelob is evil and she is tough!
 *
 * /Mercade, 23 September 1993
 *
 * Revision history:
 */

inherit "/std/creature";
inherit "/std/combat/unarmed";

inherit "/std/act/action";
inherit "/std/act/attack";
inherit "/std/act/chat";
inherit "/std/act/domove";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/elessar/lib/evilkill.h"

//#define DEBUG

#define SHELOB_QUEST_LOG     (LOG_DIR + "shelob")
#define SHELOB_TEXT_FILE     (OPEN_DIR + "QUESTS/shelob")
#define SHELOB_RANDOM_MOVE   90
#define TORECH_UNGOL_ID      "Torech_Ungol"
#define SHELOB_HOME          (LAIR_DIR + "lair1")
#define SHELOB_RESTRAIN_PATH LAIR_DIR
#define SHELOB_POISON_OBJECT (MORDOR_DIR + "obj/shelob_poison")
#define SHELOB_POISON_NAME   "_shelob_poison_"

/*
 * Define some attack and hitloc id's
 */
#define A_FANG  0
#define A_A_LEG 1

#define H_HEAD  0
#define H_BODY  1
#define H_BELLY 2
#define H_LEGS  3

void
create_creature()
{
 //   if (IS_CLONE)
 //   {
 //       set_alarm(1.0, 0.0, "remove_object");
 //       return;
 //   }

    set_living_name("shelob");

    set_name("shelob");
    add_name("ladyship");
    add_name("eyes");

    set_short("remorseless eyes");
    set_race_name("spider");

    add_adj("her"); /* for Her Ladyship */
    add_adj("remorseless");
    add_adj("huge");
    add_adj("evil");
    add_adj("dark");
    set_gender(G_FEMALE);

    set_long("@@long_description");

    set_base_stat(SS_STR, 90 + random(21));
    set_base_stat(SS_DEX, 90 + random(21));
    set_base_stat(SS_CON, 90 + random(21));
    set_base_stat(SS_INT, 90 + random(21));
    set_base_stat(SS_WIS, 90 + random(21));
    set_base_stat(SS_DIS, 90 + random(21));

    REFRESH; /* set hp, mana, fatigue */

    set_skill(SS_BLIND_COMBAT, 100);
    set_skill(SS_UNARM_COMBAT,  90 + random(11));
    set_skill(SS_DEFENCE,       90 + random(11));
    set_skill(SS_AWARENESS,     80 + random(21));
    set_skill(SS_CLIMB,         40 + random(21));

    set_alignment(-999); /* The steward wanted to reserve -1000 for Sauron */

    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(OBJ_S_WIZINFO, BSN("Shelob is definately evil! And she is " +
        "tough! Don't expect to be able to kill her easily. If she bites " +
        "you, she might poison you. This poison will paralize you for some " +
        "time and she will continue to attack while you are paralized. This " +
        "indeed means that she can kill you while you are paralized. If " +
        "you are with a team, you might be paralized into a quest. You can " +
        "read about this quest in " + SHELOB_TEXT_FILE + ". Gondor is a " +
        "dangerous domain and Shelob is a dangerous exponent of that " +
        "domain! *grin*"));

    /*
     * 50 Percent attack chance might do for now. I will have to add some
     * extra stuff to allow the game that was played by Frodo, Sam and Shelob
     * before there is a real attack. Checking for the phial is the least I
     * can do.
     */
    set_aggressive(1);
    set_attack_chance(50);

    set_cchat_time(60);
    add_cchat("@@poison_enemies@@");

    set_attack_unarmed(A_FANG,  random(21) + 40, random(21) + 40, W_IMPALE,
        75, "fangs");
    set_attack_unarmed(A_A_LEG, random(21) + 40, random(21) + 40, W_BLUDGEON,
        25, "one of her legs");

    set_hitloc_unarmed(H_HEAD,  ({random(21) + 70, random(31) + 70,
        random(21) + 80}), 10, "head");
    set_hitloc_unarmed(H_BODY,  ({random(21) + 80, random(31) + 70,
        random(21) + 80}), 50, "body");
    set_hitloc_unarmed(H_BELLY, ({random(21) + 20, random(31) + 70,
        random(21) + 80}), 10, "belly");
    set_hitloc_unarmed(H_LEGS,  ({random(21) + 70, random(31) + 70,
        random(21) + 80}), 30, "legs");

    set_random_move(SHELOB_RANDOM_MOVE);
    set_restrain_path(SHELOB_RESTRAIN_PATH);
    set_monster_home(SHELOB_HOME);
}

/*
 * Function name: short
 * Description  : Return the short description of Shelob. If she is in her
 *                lair, you will only see her as her eyes.
 * Returns      : string - the short :-)
 */
varargs string
short(mixed extra)
{
    if (ENV(TO)->id(TORECH_UNGOL_ID))
    {
        return ("remorseless eyes");
    }

    return "huge dark spider";
}

/*
 * Function name: long_description
 * Description  : Returns her longs description. If she is in her lair, you
 *                will get a description of her evil eyes.
 * Returns      : string - the long :-)
 */
string
long_description()
{
/*
    if (ENV(TO)->id(TORECH_UNGOL_ID))
    {
        return BSN("");
    }
*/

    return BSN("This huge spider is called Shelob, orcs use to refer to " +
        "her as 'Her Ladyship'. For ages and ages she dwelt in this lair. " +
        "She is huger than the great hunting beasts, and more terrible than " +
        "they because of the evil purpose in her remorseless eyes. Great " +
        "horns she has, behind her short stalk-like neck is her huge " +
        "swollen body, a vast bloated bag, swaying between her legs. She " +
        "serves none but herself, drinking the blood of Elves and Men, " +
        "bloated and fat with endless brooding on her feasts, weaving webs " +
        "of shadow; for all livings are her food, and her vomit darkness!");
}

/*
 * Function name: init_living
 * Description  : If you come close to Shelob, she frightens you.
 */
void
init_living()
{
    ::init_living();

    /* Add '100' panic to this_player(). May be adjusted later. */
    TP->add_panic(100);
}

/*
 * This function is called to determine whether we want to hit the opponent
 * with our fang and bite him. (read: paralize him and start the quest)
 */
int
shall_i_start_quest(object enemy)
{
#ifdef DEBUG
    enemy->catch_msg("The quest might be started now.\n");
#endif

    return (random(2));
}

/*
 * If indeed we shall bite him, this function initializes the quest!
 */
void
start_quest(object enemy)
{
#ifdef DEBUG
    enemy->catch_msg("The quest will be started now.\n");
#endif

    return;
}

/*
 * The least we can do is poison the enemy if the quest doesn't start.
 */
void
poison_enemy(object enemy)
{
    object poison;

#ifdef DEBUG
    enemy->catch_msg("Shelob tries to poison you instead.\n");
#endif

    if(!(present(SHELOB_POISON_NAME, enemy)))
    {
#ifdef DEBUG
        enemy->catch_msg("I'll clone the poison now.\n");
#endif

        FIX_EUID;

        poison = clone_object(SHELOB_POISON_OBJECT);
#ifdef DEBUG
        if (!objectp(poison))
        {
            enemy->catch_msg("Failed to clone poison\n");
        }
        enemy->catch_msg("name: " + check_call(poison->short()) + "!\n");
        enemy->catch_msg("move: " + poison->move(enemy, 1) + "!\n");
#else
        poison->move(enemy, 1);
#endif
        poison->start_poison();
    }
}

/*
 * Regularly try to poison all enemies. If the quest will be added to the
 * game, this function should be altered to prevent from any unwanted
 * poisoning.
 */

/*
 * Redefine what happens if the fang hits the opponent, the other hits will
 * still be handled by the normal combat routine. If the quest can be started,
 * the quest will be started.
 */
varargs int
cr_did_hit(int aid, string hdesc, int phurt, object enemy, int dt,
	   int phit, int dam)
{
    if ((phurt <= 0) || (aid != A_FANG))
    {
        /* normal combat message */
        return 0;
    }

    if (shall_i_start_quest(enemy))
    {
        /* Lets do it! Start the camera and do the quest */
        poison_enemy(enemy);
        return 1;
    }

    return 0;
}

/*
 * The entrance end leave messages are dependant on where Shelob is.
 */
string
query_m_in()
{
    if (ENV(TO)->id(TORECH_UNGOL_ID))
    {
        return "approaches you";
    }

    return "crawls towards you";
}

string
query_mm_in()
{
    if (ENV(TO)->id(TORECH_UNGOL_ID))
    {
        return "approaches you";
    }

    return "crawls towards you";
}

string
query_m_out()
{
    if (ENV(TO)->id(TORECH_UNGOL_ID))
    {
        return "turn";
    }

    return "crawls";
}

string
query_mm_out()
{
    if (ENV(TO)->id(TORECH_UNGOL_ID))
    {
        return "turn away from you.";
    }

    return "crawls away from you.";
}

/*
 * Solamnian prestige, we are nice to fellow domains and if we think you
 * deserve it, we are generous with prestige. (And if you manage to kill
 * Shelob, you deserve it :-) )
 */
int
query_knight_prestige()
{
    return 2000;
}
