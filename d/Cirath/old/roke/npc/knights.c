/*
 * knights.c
 *
 * Used in nyreese/cas_a7.c nyreese/cas_b7.c nyreese/cas_b10.c
 * Used in nyreese/cas_c5.c nyreese/cas_c8.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

#pragma save_binary
#pragma strict_types

inherit "std/monster.c";

#include <ss_types.h>
#include <macros.h>
#include <language.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include "defs.h"

#define WEP_DIR   ROKEDIR + "wep/"
#define ARM_DIR   ROKEDIR + "arm/"
#define COINS     "/std/coins"

#define ONE_OF_LIST(array) (array[random(sizeof(array))])
#define NO_OF_TYPES 8
#define NO_OF_WEAPONS 6
#define NO_OF_ARMOURS 6

#define NAMES ({ "squire", "squire", "squire", "knight", "knight", "knight",\
                 "knight", "knight" })
#define PNAMES ({ "squires", "squires", "squires", "knights", "knights", \
                  "knights", "knights", "knights"})
#define SHORTS ({ \
        "insecure squire", "squire", "confident squire", \
        "young knight", "knight", "experienced knight", \
        "guardian knight", "black knight" })
#define PSHORTS ({ \
        "insecure squires", "squires", "confident squires", \
        "young knights", "knights", "experienced knights", \
        "guardian knights", "black knights" })
#define LONGS ({ \
   "The squire looks very nervous.\n", \
   "This squire has just begun his training for knighthood.\n", \
   "The squire gives you an appraising look.\n", \
   "He looks very proud.\n", \
   "The knight pointedly ignores your attention.\n", \
   "The knight stares back at you with murder in his eyes.\n", \
   "The knight is guarding the castle from intruders. Like you.\n", \
   "There seems to be something wrong with the appearance of this knight.\n"  })
#define ADJS ({ "insecure", "", "confident", "young", \
                "", "experienced", "guardian", "black" })
#define WEP_ARRAY ({ "k_mace", "k_battleaxe",\
                     "k_morningstar", "k_damask_sword" })

#define HELM_ARRAY ({ "k_helm", "k_helmet" })
#define SHIELD_ARRAY ({ "k_round_shield", "k_kite_shield", "k_kite_shield2" })

int type;
/*
 * Prototypes
 */
void make_money(int i, string type);
void help_friend(object ob);

void
create_monster()
{
    int i;
    string name, pname, short, pshort, long, adj;

    type = random(NO_OF_TYPES);

    name = NAMES[type];
    pname = PNAMES[type];
    short = SHORTS[type];
    pshort = PSHORTS[type];
    long = LONGS[type];
    adj = ADJS[type];

    set_name(name);
    set_pname(pname);
    add_name("castle_knight");
    set_race_name("human");

    set_short(short);
    set_pshort(pshort);
    set_long(long);
    if (adj != "")
        set_adj(adj);
    set_alignment(50 + random(type * 100));

    set_random_move(30);
    set_learn_pref(({0, 1, 1, 0, 0, 0}));

    add_prop(CONT_I_WEIGHT, 70000);
    add_prop(CONT_I_VOLUME, 70000);
    //    add_prop(ROKE_I_RUN_FROM_DISEASE, 1);

    set_act_time(5);
    add_act("emote tends his armour.");
    add_act("emote stares angrily at you!");
    set_chat_time(5);
    add_chat("What are you doing here?");
    add_chat("Who let this dirty creature into the Castle?");

    set_cchat_time(3);
    add_cchat("May the Master devour your soul!");
    add_cchat("I'll make you scream with pain!");
    add_cchat("You fight like a stupid child!");
    add_cchat("I hope it hurts!");
    set_cact_time(10);
    add_cact("emote kicks you savagely.");

    for (i = 0; i < 6; i++)
    {
        if (type < 3)
            set_base_stat(i, 17 + type * 7 + random((type + 1) * 4));
        else
            set_base_stat(i, 27 + type * 6 + random(type * 4));
    }
    set_skill(SS_PARRY, 20 + type * 3);
    set_skill(SS_DEFENCE, 20 + type * 9);
    set_skill(SS_AWARENESS, 20);
/*  set weapon skills   */
    for (i = 0; i < 5; i++)
        set_skill(i, 20 + type * 10);
}

void
equip_me()
{
    object arm, wep;
    seteuid(getuid(TO));

    switch (type)
    {
    case 0:
        arm = clone_object(ARM_DIR + "k_helm");
        arm->move(TO);
        wep = clone_object(WEP_DIR + "k_short_sword");
        wep->move(TO);
        break;
    case 1:
        arm = clone_object(ARM_DIR + "k_helm");
        arm->move(TO);
        arm = clone_object(ARM_DIR + "k_splintmail");
        arm->move(TO);
        wep = clone_object(WEP_DIR + "k_short_sword");
        wep->move(TO);
        break;
    case 2:
        arm = clone_object(ARM_DIR + "k_helm");
        arm->move(TO);
        arm = clone_object(ARM_DIR + "k_splintmail");
        arm->move(TO);
        wep = clone_object(WEP_DIR + "k_mace");
        wep->move(TO);
        break;
    case 3..6:
        arm = clone_object(ARM_DIR + ONE_OF_LIST(HELM_ARRAY));
        arm->move(TO);
        arm = clone_object(ARM_DIR + "k_chainmail");
        arm->move(TO);
        arm = clone_object(ARM_DIR + ONE_OF_LIST(SHIELD_ARRAY));
        arm->move(TO);
        wep = clone_object(WEP_DIR + ONE_OF_LIST(WEP_ARRAY));
        wep->move(TO);
        break;
    case 7:
        arm = clone_object(ARM_DIR + "k_helmet");
        arm->move(TO);
        arm = clone_object(ARM_DIR + "k_chainmail");
        arm->move(TO);
        arm = clone_object(ARM_DIR + "k_kite_shield2");
        arm->move(TO);
        wep = clone_object(WEP_DIR + "k_damask_sword");
        wep->move(TO);
        make_money(random(type), "gold");
        break;
    }

    command("wear all");
    command("wield all");

    make_money(random(type + 5), "copper");
    make_money(random(4 * type), "silver");
}

void
make_money(int i, string type)
{
    object money;

    money = clone_object(COINS);
    money->set_heap_size(i);
    money->set_coin_type(type);
    money->move(TO);
}

int
query_knight_prestige()
{
    int align;

    align = query_alignment();

    return 100 - align;
}

/*
 * Function name: attacked_by
 * Description:   This function is called when somebody attacks this object
 * Arguments:     ob - The attacker
 */
void
attacked_by(object ob)
{
    object *arr;
    int i;

    ::attacked_by(ob);

    arr = FILTER_LIVE(all_inventory(environment(TO)));
    for (i = 0; i < sizeof(arr); i++)
    {
        if (arr[i]->id("castle_knight"))
            arr[i]->notify_ob_attacked_me(TO, ob);
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
    set_alarm(5.0, 0.0, &help_friend(attacker));
}

/*
 * Function name: help_friend
 * Description:   Help my friends by attacking their attacker
 * Arguments:     attacker - The person who attacked my friend
 */
void
help_friend(object ob)
{
    if (ob && !query_attack() && present(ob, environment()))
    {
        command("say Bad mistake, you shouldn't have attacked him!");
        command("kill " + lower_case(ob->query_real_name()));
    }
}
