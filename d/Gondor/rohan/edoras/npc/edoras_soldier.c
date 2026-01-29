/*
 *	/d/Gondor/rohan/edoras/npc/edoras_soldier.c
 *
 */
inherit "/d/Gondor/rohan/edoras/npc/edoras_npc.c";
inherit "/d/Gondor/common/lib/logkill.c";

#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/rohan/edoras/defs.h"

#define WEP_ARRAY1 ({EDORAS_DIR + "obj/guardsword", \
   EDORAS_DIR + "obj/rosword", EDORAS_DIR + "obj/broadsword", \
   EDORAS_DIR + "obj/guardsword2", WEP_DIR + "rospear" })
#define WEP_ARRAY2 ({EDORAS_DIR + "obj/roshield"})
#define ARM_ARRAY1 ({EDORAS_DIR + "obj/rohelm"})
#define ARM_ARRAY2 ({EDORAS_DIR + "obj/corslet"})
#define ARM_ARRAY3 ({EDORAS_DIR + "obj/rogreaves"})
#define SURCOAT      EDORAS_DIR + "obj/roh_surcoat"

int     attack_id;

string *wep1,
       *wep2,
       *arm1,
       *arm2,
       *arm3;

void check_attack(object pl);

void
create_guard()
{
    int     rnd1 = random(21),
            rnd2 = random(21);

    set_short(implode(query_adjs(), " ")+ " guard");
    set_pshort("blond-haired guards");
    set_pname("guards");

    set_long(BSN(CAP(LANG_ADDART(implode(query_adjs()," "))) 
      + " man from Rohan with a stern face and long, blond hair. "
      + "He is wearing a green tunic over his armour, embroidered "
      + "with the symbol of Rohan - a white horse on a green field. "
      + "Obviously a man of the King's Eored, which defends the "
      + "city of Edoras and King Theoden."));

    default_config_npc(85 + (rnd1+rnd2)/4);
    set_base_stat(SS_STR,      95 + rnd1);
    set_base_stat(SS_DIS,     105 + rnd2);
    set_skill(SS_WEP_SWORD,    75 + rnd1 / 3);
    set_skill(SS_WEP_POLEARM,  70 + rnd2 / 2);
    set_skill(SS_PARRY,        70 + rnd1 / 2);
    set_skill(SS_DEFENCE,      70 + rnd2 / 2);
    set_skill(SS_AWARENESS,    60 + rnd2 / 2);
    add_prop(CONT_I_HEIGHT,   180 + rnd1 / 2);
    add_prop(CONT_I_WEIGHT, 75000 + rnd1 * 500);
    add_prop(CONT_I_VOLUME, 70000 + rnd1 * 500);    
    add_prop(LIVE_I_SEE_DARK, 0);
    add_prop("_live_m_attack_thief", 1);

    set_chat_time(5 + rnd1);
    add_chat("There are orcs on the plains, or so I hear.");
    add_chat("Why will the King not send Riders to kill the orcs?");
    add_chat("I heard a scout report that dark fumes are rising from Isengard.");
    add_chat("We will never pay tribute to Mordor.");
    add_chat("Our loyalty is to the King of the Mark.");
    add_chat("Eomer ought to be back from his scout mission soon.");

    set_cchat_time(5 + rnd2 / 2);
    add_cchat("The Mark! Eorlingas for the Mark!");
    add_cchat("For the King! For King Theoden of the Riddermark!");
    add_cchat("Die, foe! The Mark is ours!");
    add_cchat("Death to the servants of Mordor!");
    add_cchat("For Edoras! For Meduseld!");

    set_act_time(15 + rnd2);
    add_act("sigh .");
    add_act("emote gazes at his surroundings for a while.");
    add_act("emote buffs the blade of his weapon.");
    add_act("emote hefts his weapon a little tighter.");
    add_act("emote shifts his feet restlessly.");
    add_act("emote studies the surroundings carefully.");

    set_cact_time(2 + rnd1 / 2);
    add_cact("emote slams his weapon against his shield, making noise.");
    add_cact("swear");
    add_cact("scream");
    add_cact("emote grips his weapon tighter and continues fighting.");
    add_cact("shout Enemies! Enemies in Edoras!");
    add_cact("shout Eorlingas! To arms!");
}

string
alignlook()
{
    return ONE_OF_LIST(
        ({"tall", "stern", "strong", "lean", "braided",
          "scarred", "young", "tough", "old", "noble",
          "bearded", "blue-eyed", }));
}

nomask void
create_edoras_npc()
{
    int     rnd = random(11);

    // default values
    add_name("soldier");
    set_adj("blond-haired");
    add_adj(alignlook());

    default_config_npc(50);

    set_skill(SS_AWARENESS,     25+rnd);
    set_skill(SS_CLIMB,         45+rnd);
    set_skill(SS_SWIM,          45+rnd);

    set_skill(SS_DEFENCE,       25+rnd);

    set_alignment(300 + 10 * rnd);

    add_prop(LIVE_I_NEVERKNOWN,1);
    set_name("guard");

    create_guard();

    // fixed values
    add_name("_Rohirrim_soldier");
    set_race_name("human");

    FIX_EUID
}

void
set_arm_arrays()
{
    wep1 = WEP_ARRAY1;
    wep2 = WEP_ARRAY2;
    arm1 = ARM_ARRAY1;
    arm2 = ARM_ARRAY2;
}

varargs void
arm_me(int cc = 10, int sc = 5)
{
    object  weapon;

    MONEY_MAKE_CC(cc + random(cc))->move(TO);
    MONEY_MAKE_SC(sc + random(sc))->move(TO);

    set_arm_arrays();

    if (sizeof(wep1))
        (weapon = clone_object(ONE_OF_LIST(wep1)))->move(TO);

    if ((weapon->query_hands() != W_BOTH) && sizeof(wep2))
        clone_object(ONE_OF_LIST(wep2))->move(TO);

    if (sizeof(arm1))
        clone_object(ONE_OF_LIST(arm1))->move(TO);

    if (sizeof(arm2))
        clone_object(ONE_OF_LIST(arm2))->move(TO);

    if (sizeof(arm3))
        clone_object(ONE_OF_LIST(arm3))->move(TO);

    command("wield all");
    command("wear all");
    clone_object(SURCOAT)->move(TO);
    command("wear surcoat");
}

void
init_living()
{
    ::init_living();
    if (interactive(TP) && CAN_SEE(TO, TP))
        set_alarm(3.0, 0.0, &check_attack(TP));
}

void
do_attack(object victim)
{
    remove_alarm(attack_id);
    attack_id = 0;

    if (objectp(query_attack()) || victim->query_npc())
        return;

    if (!objectp(victim) || !present(victim,ENV(TO)) || 
        !CAN_SEE(TO, victim) || !CAN_SEE_IN_ROOM(TO))
    {
        command("say Who? Where?");
        return;
    }

    command("kill "+victim->query_real_name());
}

void
check_attack(object pl)
{
    if (objectp(query_attack()) || (attack_id && sizeof(get_alarm(attack_id))))
        return;
    if (!CAN_SEE(TO, pl))
        return;
    if ((pl->query_prop(EDORAS_I_DID_ATTACK) > 3) ||
        (pl->query_prop(LIVE_I_KILLED_ROHIRRIM) > 2) ||
        (ROHAN_FRIEND_FOE->query_friend_or_foe(pl) <= -3) ||
        EDORAS_MASTER->query_enemy(pl))
    {
        command("shout Eorlingas, to me! Enemies in Edoras!");
        command("say You will die, brigand!");
        attack_id = set_alarm(3.0, 0.0, &do_attack(TP));
    }
}

void
call_for_friends(object ob)
{
    int i;
    object  room = ENV(TO),
           *arr;

    while (!room->query_prop(ROOM_I_IS))
        room = ENV(room);
    filter(all_inventory(room), &->id("_Rohirrim_soldier"))
           ->notify_ob_attacked_me(TO, ob);
}

void
attacked_by(object ob)
{
    ::attacked_by(ob);
    call_for_friends(ob);
}

/*
 * Function name: help_friend
 * Description:   Help my friends by attacking their attacker
 * Arguments:     attacker - The person who attacked my friend
 */
void
help_friend(object ob, object friend)
{
    if (objectp(ob) && !query_attack() && present(ob, ENV(TO))
        && !(attack_id && sizeof(get_alarm(attack_id)))
        && CAN_SEE(TO,ob) && CAN_SEE_IN_ROOM(TO))
    {
        if (!random(4))
            command("shout Leave the Mark, evil "+ob->query_race_name()+"!");
        if (attack_id && sizeof(get_alarm(attack_id)))
            attack_id = set_alarm(3.0, 0.0, &do_attack(ob));
    }
}

/*
 * Function name: notify_ob_attacked_me
 * Description:   This is called when someone attacks a team member of mine
 * Arguments:     friend - My team mate
 *                attacker - The attacker
 */
void
notify_ob_attacked_me(object friend, object attacker)
{
    if (query_attack())
        return;
   
    if (random(10))
        set_alarm(2.0 + 5.0 * rnd(), 0.0, &help_friend(attacker, TO));
}

public void
init_attack()
{
    if (query_attack())
        return;
   
    set_alarm(0.0, 0.0, &check_attack(TP));
}

public void
do_die(object killer)
{
    int n;
    if (interactive(killer))
    {
        n = killer->query_prop(LIVE_I_KILLED_ROHIRRIM) + 1;
        killer->add_prop(LIVE_I_KILLED_ROHIRRIM, n);
        if (n > 6)
            EDORAS_MASTER->add_enemy(killer, "Rohirrim soldier");
    }
    ::do_die(killer);
}
