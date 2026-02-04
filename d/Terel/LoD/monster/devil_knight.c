/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * a knight of the legion 921103 redhawk
 * Modified by Sorgum 941002
 */

#include "/d/Terel/include/Terel.h"
inherit LOD_DIR + "monster/legion_knight";
inherit "/lib/unique";

#include <ss_types.h>
#include <money.h>

#define PEACE_DELAY     7

static object my_boss;
static object *my_foes;
void arm_me();

void help_the_boss(object boss);
void attack_someone();
public nomask void peace_attack(object who);


/*
 * Function name: query_chats
 * Description:   return list of chats for this monster.
 */
public string *
query_chats()
{
    return ({"The devil's work will be done.",
          "Now you have made a big mistake, now you are messing with " +
           "the devil's servant. HA HA HA!",
      });
}

/*
 * Function name: query_spell_level
 * Description:   spell level is used in spell_attack()
 * Returns:       this knights spell level.
 */
public int
query_spell_level()
{
    return 4;
}

/*
 * Function name: create_monster
 * Description:   Create the monster. (standard)
 */
public void
create_monster()
{
    ::create_monster();
    set_name("knight");
    add_name("devil_knight");
    set_short("devil's knight");
    set_long("A human knight that is a member of the powerful and evil " +
          "legion of darkness, the legion which is known " +
          "to take no prisoners. This knight seems to work in the " +
          "devil's leach, and he seems very confident about himself.\n");
    set_race_name("human");
    set_adj("evil");
    add_adj("devil's");
    set_gender(MALE);
    set_alignment(-600);
    SET_MAX_HP;
    SET_MAX_MANA;
    SET_MAX_FATIGUE;

    set_stats(({120, 125, 110, 125, 125, 125}));
    set_skill(SS_WEP_CLUB,     80);
    set_skill(SS_2H_COMBAT,    80);
    set_skill(SS_BLIND_COMBAT, 90);
    set_skill(SS_AWARENESS,    50);
    set_skill(SS_LANGUAGE,     60);
    set_skill(SS_DEFENCE,      90);
    set_skill(SS_UNARM_COMBAT, 90);
    set_skill(SS_SPELLCRAFT,   95);
    set_skill(SS_WEP_SWORD,    99);
    set_skill(SS_WEP_KNIFE,    99);
    set_skill(SS_PARRY,        85);

    add_prop(LIVE_I_SEE_DARK,  3);
    add_prop(LIVE_I_QUICKNESS, 100);
    add_prop("_LoD_officer",1);
    
    add_prop(OBJ_I_RES_FIRE,   25);
    add_prop(OBJ_I_RES_DEATH,  25);
    AGGRESSIVE;

    set_chat_time(15);
    add_chat("The devil's work will be done.");
    add_chat("Now you have made a big mistake, " +
        "now you are messing with the devil's servant. HA HA HA!");
    arm_me();

}

void
arm_me()
{

    FIX_EUID;
    clone_object(LOD_DIR + "armour/devils_helmet")->move(TO);
    clone_object(LOD_DIR + "armour/devils_chainmail")->move(TO);
    clone_object(LOD_DIR + "armour/leather_boots")->move(TO);
    command("wear all");
    clone_unique(LOD_DIR + "weapon/devils_sword", 10, LOD_DIR +
                 "weapon/deaths_sword")->move(TO);
    clone_unique(LOD_DIR + "weapon/devils_stiletto",5, LOD_DIR +
                 "weapon/steel_stiletto")->move(TO);
    command("wield sword");
    command("wield stiletto");
}


void
help_the_boss(object boss)
{
    if (!boss) return;
    my_boss = boss;
    my_foes = my_boss->query_my_enemies();
}

void
attack_someone()
{
    int i, found_foe = 0;
    object foe;

    if (!query_attack()) {
        help_the_boss(my_boss);
        for (i=0; i<sizeof(my_foes); i++) {
            foe = my_foes[i];
            if (foe && environment(TO) == environment(foe)) {
                command("kill " + foe->query_real_name());
                set_follow(foe->query_real_name());
          found_foe = 1;
                break;
            }
        }
     if (!found_foe && my_boss &&
         environment(my_boss) != environment(TO)) {
         tell_room(environment(TO), QCTNAME(TO) +
                " leaves to seek his master.\n", TO);
         move_living("M", environment(my_boss));
         tell_room(environment(my_boss), QCTNAME(TO) +
                " arrives.\n", TO);
            set_alarm(4.0, -1.0, attack_someone);
         return;
     }
    }
    set_alarm(20.0, -1.0, attack_someone);
}

public nomask void
stop_fight(mixed elist)
{
    if (TP->query_wiz_level()) {
        ::stop_fight(elist);
        return;
    }
    ::stop_fight(elist);
    remove_prop(LIVE_O_SPELL_ATTACK);
    set_alarm(itof(PEACE_DELAY+random(5)), -1.0, "peace_attack", TP);
}

public nomask void
peace_attack(object who)
{
    int i;
    
    if (query_hp() <= 0) return;

    set_spell_prop(TO);
    tell_room(ETO, QCTNAME(TO) + " looks a bit confused for a while.\n");

    for (i=0; i<sizeof(my_foes); i++)
        if (my_foes[i] && present(my_foes[i], ETO))
            command("kill " + my_foes[i]->query_real_name());

    if (who && present(who, ETO))
        command("kill " + who->query_real_name());
}
