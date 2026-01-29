/*
 *	/d/Gondor/pelargir/npc/pelargir_soldier.c
 *
 */
inherit "/d/Gondor/pelargir/npc/pelargir_npc.c";
inherit "/d/Gondor/common/lib/logkill.c";

#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/pelargir/lib/defs.h"

#define WEP_ARRAY1 ({WEP_DIR + "grapier", WEP_DIR + "gspear", WEP_DIR + "dlongsword" })
#define WEP_ARRAY2 ({ARM_DIR + "pel_shield"})
#define ARM_ARRAY1 ({ARM_DIR + "ghelmet"})
#define ARM_ARRAY2 ({ARM_DIR + "gchainmail"})
#define ARM_ARRAY3 ({PELAR_DIR + "obj/pel_surcoat"})

int     attack_id;

string *wep1,
       *wep2,
       *arm1,
       *arm2,
       *arm3;

void
create_guard()
{
    int     rnd1 = random(21),
            rnd2 = random(21);

    set_short(implode(query_adjs(), " ")+ " guard");
    set_pshort("dark-haired guards");
    set_pname("guards");

    set_long(BSN(CAP(LANG_ADDART(implode(query_adjs()," "))) + " man from "
      + "Lebennin with a stern face and dark hair. He is wearing a blue "
      + "tunic over his armour, embroidered with the emblem of Pelargir "
      + "- three white ships surmounted by a silver crown. Obviously a "
      + "soldier in the Pelargir garrison, on patrol duty."));

    default_config_npc(65 + (rnd1+rnd2)/4);
    set_base_stat(SS_STR,      65 + rnd1);
    set_base_stat(SS_DIS,      95 + rnd2);
    set_skill(SS_WEP_SWORD,    75 + rnd1 / 3);
    set_skill(SS_WEP_POLEARM,  70 + rnd2 / 2);
    set_skill(SS_PARRY,        70 + rnd1 / 2);
    set_skill(SS_DEFENCE,      70 + rnd2 / 2);
    add_prop(CONT_I_HEIGHT,   180 + rnd1 / 2);
    add_prop(CONT_I_WEIGHT, 75000 + rnd1 * 500);
    add_prop(CONT_I_VOLUME, 70000 + rnd1 * 500);    
    add_prop(LIVE_I_SEE_DARK, 0);
    add_prop("_live_m_attack_thief", 1);

    set_chat_time(5 + rnd1);
    add_chat("The Corsairs have been quiet lately. Something is brewing, I'm quite sure!");
    add_chat("Somebody ought to do something about the thieves here in Pelargir.");
    add_chat("I heard a scout report that Haradrims are moving north.");
    add_chat("It has been some time since we saw any of those black sails now.");
    add_chat("The Black Fleet of Umbar is our main threat.");
    add_chat("Trade seems to be going well these days.");

    set_cchat_time(5 + rnd2 / 2);
    add_cchat("By Gondor! This was not the attack we expected!");
    add_cchat("Where are the archers when we need them?");
    add_cchat("Die, foe! Gondor will never fall!");
    add_cchat("In the name of the Steward - begone!");
    add_cchat("For the Admiral of Pelargir!");

    set_act_time(15 + rnd2);
    add_act("sigh");
    add_act("twiddle");
    add_act("stare");

    set_cact_time(2 + rnd1 / 2);
    add_cact("growl");
    add_cact("swear");
    add_cact("scream");
    add_cact("scowl");
    add_cact("shout Enemies are attacking! Reinforcements!");
    add_cact("shout Help! Reinforcements!");
}

string
alignlook()
{
    return ONE_OF_LIST(
        ({"noble", "stern", "strong", "lean",
          "stout", "young", "tough", "hook-nosed", 
          "swarthy", "green-eyed", }));
}

nomask void
create_pelargir_npc()
{
    int     rnd = random(11);

    // default values
    add_name("soldier");
    set_adj("dark-haired");
    add_adj(alignlook());

    default_config_npc(50);

    set_skill(SS_AWARENESS,     25+rnd);
    set_skill(SS_CLIMB,         45+rnd);
    set_skill(SS_SWIM,          45+rnd);

    set_skill(SS_DEFENCE,       25+rnd);

    set_alignment(300 + 10 * rnd);

    add_prop(LIVE_I_NEVERKNOWN,1);

    create_guard();

    // fixed values
    set_name("guard");
    add_name("_Pelargir_soldier");
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
   arm3 = ARM_ARRAY3;
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
}
    
void
adjust_lamplight()
{
    object  lamp;

    if (!objectp(lamp = present("lamp", TO)))
        return;

    if (!CAN_SEE_IN_ROOM(TO))
    {
        if (!random(5))
            command("say It's too dark here, we need more light!");
        if (lamp->light_me())
        {
            tell_room(ENV(TO),QCTNAME(TO)+" lights "
              + TO->query_possessive()+" oil-lamp.\n");
            command("say That's better!");
        }
        else
            command("say Oh no, I'm out of oil!");
    }
    else if ((ENV(TO)->query_prop(OBJ_I_LIGHT) + query_prop(LIVE_I_SEE_DARK)) > 1)
    {
        if (lamp->extinguish_me())
        {
            if (!random(4))
                command("say I don't need to spend oil on this lamp right now.");
            tell_room(ENV(TO),QCTNAME(TO)+" extinguishes his oil-lamp.\n");
            lamp->set_time_left(10000);
        }
    }
    return;
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
    if (pl->query_prop(PEL_I_DID_ATTACK))
    {
        command("shout Enemies!");
        command("say You will die, foul creature!");
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
    filter(all_inventory(room), &->id("_Pelargir_soldier"))
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
            command("shout Begone, foul "+ob->query_race_name()+"!");
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


