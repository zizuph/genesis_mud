/*
 * This orc is used in /d/Gondor/arnor/
 * This file structure was taken from Nick's random draconian
 * and from Elessar's random ranger. The file is of course
 * modified to suit me.
 * The loot_item function was made by Olorin. I liked
 * it so much so I had to include it too.
 *
 * Arren, January 1994
 *
 * Modification log:
 *
 */

inherit "std/monster.c";

#include <ss_types.h>
#include <macros.h>
#include <language.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <money.h>

#include "/d/Gondor/defs.h"

#undef ARM_DIR
#undef WEP_DIR
#define ARM_DIR   "/d/Gondor/common/arm/orc_arm/"
#define WEP_DIR   "/d/Gondor/common/wep/orc_wep/"
#define LOOT_DIR  "/d/Gondor/common/obj/orc_loot/"
#define BAG_DIR   "/d/Gondor/rohan/edoras/obj/bag"
#define COINS     "/std/coins"

#define NO_OF_TYPES 8
#define NO_OF_WEAPONS 6
#define NO_OF_ARMOURS 6

#define ONAME ({ "orc", "orc", "orc", "orc", "orc", "orc", "uruk", "uruk" })
#define OPNAME ({ "orcs", "orcs", "orcs", "orcs", "orcs", "orcs", \
               "uruk-hai", "uruk-hai" })
#define OSHORT ({ \
        "stooped orc", "long-armed orc", "slant-eyed orc", \
        "crook-legged orc", "swarthy orc", "yellow-fanged orc", \
        "tall uruk", "stout uruk" })
#define OPSHORT ({ \
        "stooped orcs", "long-armed orcs", "slant-eyed orcs", \
        "crook-legged orcs", "swarthy orcs", "yellow-fanged orcs", \
        "tall uruk-hai", "stout uruk-hai" })
#define OLONG ({ \
   "A short orc, aged and stooped, that looks to be somewhat infirm. "+ \
   "The long arms hang almost to the ground, they end in clawlike "+ \
   "hands. ", \
   "A short and exceptionally long-armed orc that glances nervously "+ \
   "around. The arms end in clawlike hands.", \
   "An orc that seems not to be properly trained yet. The orc is short "+ \
   "and broad, and his arms hang almost to the ground. He has a hideous "+ \
   "face, with conspicous eyes.", \
   "An ordinary orc fit for raiding duty. Crook-legged and with broad "+ \
   "shoulders.", \
   "A capable orc with a confident and rough look, as if he went on "+ \
   "lone scouting missions. His swarthy skin makes him hard to spot "+ \
   "on dark nights.", \
   "This orc looks larger and bolder than most orcs. He is an elite "+ \
   "warrior, the backbone of every orc army. Short and very broad, "+ \
   "with arms that hang almost to the ground. The arms end in clawlike "+ \
   "hands.", \
   "This is a heavily armed and fierce-looking uruk, standing tall "+ \
   "and erect. His tough and thick legs look like they could run "+ \
   "for days. ", \
   "A large and black uruk. By the look of his eyes, kindness doesn't "+ \
   "seem to be one of his faults. He has long and strong arms, giving "+ \
   "an impression of savage strength"  })
#define OADJ ({ "stooped", "long-armed", "slant-eyed", "crook-legged", \
                "swarthy", "yellow-fanged", "tall", "stout" })

#define WEP_ARRAY ({ "saw_knife", "dull_scimitar", "stabbing_sword", \
                     "battleaxe", "morningstar", "broad_scimitar" })
       
#define ARMOUR_KIT1 ({ "gorget", "shoes", "cloak" })
#define ARMOUR_KIT2 ({ "round_shield", "breeches", "cap" })
#define ARMOUR_KIT3 ({ "kite_shield", "orc_helmet", "g_leggings" })
#define LOOT_LIST ({ "cheese", "liquor", "pin", "torch", "bread", \
                     "cup", "meat", "plate", "bracelet", "liquor" })

/*
 * Prototypes
 */
void arm_me(int j);
int brave_in_team();
int try_attack();
void attacked_by(object ob);
void notify_ob_attacked_me(object friend, object attacker);
void help_friend(object ob);


void
create_monster()
{
    int i, j;
    string oname, opname, oshort, opshort, olong, oadj;

    if (!IS_CLONE)
	return;

    j = random(NO_OF_TYPES);

    oname = ONAME[j];
    opname = OPNAME[j];
    oshort = OSHORT[j];
    opshort = OPSHORT[j];
    olong = OLONG[j];
    oadj = OADJ[j];
 
    set_name(oname);
    set_pname(opname);
    add_name(({ "_random_orc", "_serf_of_sauron" }));
    set_race_name("orc");

    set_short(oshort);
    set_pshort(opshort); 
    set_long(BSN(olong));
    set_adj(oadj);
    set_alignment(-(50 + random(j * 40)));

    set_aggressive(try_attack());
    set_learn_pref(({ 2, 2, 2, 1, 1, 1 }));

    add_prop(LIVE_I_SEE_DARK, 2);
    if(j < NO_OF_TYPES-2)
    {
        add_prop(CONT_I_HEIGHT, 150);
        add_prop(CONT_I_WEIGHT, 55000);
        add_prop(CONT_I_VOLUME, 55000);
    }
    else
    {
        add_prop(CONT_I_HEIGHT, 180);
        add_prop(CONT_I_WEIGHT, 70000);
        add_prop(CONT_I_VOLUME, 70000);
    }

    set_act_time(30);
    add_act("emote licks his lips.");
    add_act("emote grumbles angrily.");
    set_chat_time(10);
    add_chat("I don't trust you, you little swine.");
    add_chat("You are nothing but a muckraker.");
    add_chat("You won't have me for dinner!");

    set_cchat_time(3);
    add_cchat("@@loot_item");
    add_cchat("You're cooked!");
    add_cchat("I'll make you squeak, you miserable rat!");
    add_cchat("I'll put red maggot holes in your belly!");
    add_cchat("Ape! I'm going to suck your bones.");
    add_cchat("You rat-bitten, motherless dog.");
    set_cact_time(25);
    add_cact("emote kicks you savagely.");
    add_cact("@@shout_loot_item");

    set_base_stat(SS_STR, 20 + j * 4 + random(j * 4));
    set_base_stat(SS_DEX, 20 + j * 4 + random(j * 4));
    set_base_stat(SS_CON, 20 + j * 4 + random(j * 4));
    set_base_stat(SS_INT, 20 + j * 3 + random(j * 4));
    set_base_stat(SS_WIS, 20 + j * 3 + random(j * 4));
    set_base_stat(SS_DIS, 20 + j * 3 + random(j * 4));

    set_skill(SS_PARRY, 20 + j * 3);
    set_skill(SS_DEFENCE, 20 + j * 5);
    set_skill(SS_AWARENESS, 20 + j * 2);
    set_skill(SS_SWIM, 10);
    set_skill(SS_CLIMB, 10);
/*  set weapon skills   */
    for (i = 0; i < 5; i++)
        set_skill(i, 20 + j * 7);

    add_notify_meet_interactive("brave_in_team");

    arm_me(j);
}


int
query_show_list(object x)
{
    return !((x->query_no_show()) || (x->query_prop(OBJ_I_INVIS)));
}

string
loot_item()
{
    object *loot_list,
	    tp = TP;

    if (!interactive(tp) ||
	!present(tp, ENV(TO)))
    {
        return "";
    }
    loot_list = filter(all_inventory(tp), query_show_list);
    if (!sizeof(loot_list))
        return "I want to kill " + OBJECTIVE(tp) + "!";

    return "I want to have " + POSSESSIVE(tp) + " "
      + (ONE_OF_LIST(loot_list))->short() + "!";
}

string
shout_loot_item()
{
    return "shout "+loot_item();
}

void
arm_me(int j)
{
    object arm, wep, money;
    object me = TO;
    int tmp;

    FIX_EUID

    tmp = (j + random(NO_OF_TYPES - 3)) / 2;
    if (tmp < 0)
        tmp = 0;
    if (tmp >= NO_OF_WEAPONS)
    	tmp = NO_OF_WEAPONS - 1;

    wep = clone_object(WEP_DIR + WEP_ARRAY[tmp]);
    wep->move(me);
    wep->wield_me();

    tmp = (j + random(NO_OF_TYPES - 3)) / 2;
    if (tmp < 0)
    	tmp = 0;
    if (tmp >= NO_OF_ARMOURS)
    	tmp = NO_OF_ARMOURS - 1;
    switch(tmp)
    {
        case 0 :
             arm = clone_object(ARM_DIR + ONE_OF_LIST(ARMOUR_KIT1));
             arm->move(me);
	     arm->wear_me();
             break;
        case 1 :
             arm = clone_object(ARM_DIR + "gambeson");
             arm->move(me);
	     arm->wear_me();
             arm = clone_object(ARM_DIR + ONE_OF_LIST(ARMOUR_KIT1));
             arm->move(me);
	     arm->wear_me();
             break;
        case 2 :
             arm = clone_object(ARM_DIR + "gambeson");
             arm->move(me);
	     arm->wear_me();
             arm = clone_object(ARM_DIR + ONE_OF_LIST(ARMOUR_KIT2));
             arm->move(me);
	     arm->wear_me();
             break;
        case 3 :
             arm = clone_object(ARM_DIR + "ring_mail");
             arm->move(me);
	     arm->wear_me();
             arm = clone_object(ARM_DIR + ONE_OF_LIST(ARMOUR_KIT2));
             arm->move(me);
	     arm->wear_me();
             break;
        case 4 :
             arm = clone_object(ARM_DIR + "ring_mail");
             arm->move(me);
	     arm->wear_me();
             arm = clone_object(ARM_DIR + ONE_OF_LIST(ARMOUR_KIT3));
             arm->move(me);
	     arm->wear_me();
             break;
        case 5 :
             arm = clone_object(ARM_DIR + "red_chainmail");
             arm->move(me);
	     arm->wear_me();
             arm = clone_object(ARM_DIR + ONE_OF_LIST(ARMOUR_KIT3));
             arm->move(me);
	     arm->wear_me();
             break;
    }

    money = MONEY_MAKE(random(8+j), "copper");
    money->move(me, 1);
    money = MONEY_MAKE(random(2*j), "silver");
    money->move(me, 1);

    if (!random(8))
        clone_object(BAG_DIR)->move(me);
    if (!random(3))
        clone_object(LOOT_DIR + ONE_OF_LIST(LOOT_LIST))->move(me);
}  

query_knight_prestige()
{
    int stat;

    stat = TO->query_average_stat();   

    return stat*stat/10;
}

int
brave_in_team()
{
    object me = TO;
    int i;

    i = sizeof(me->query_team_others());
    if (i == 0)
        return 0;
    else
        me->set_stat_extra(SS_DIS, i * 5);
    return 1;
}

int
try_attack()
{
    if(IS_MORGUL_MAGE(TP))
        return 0;
    else
        return 1;
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

    arr = FILTER_LIVE(all_inventory(ENV(TO)));
    for (i = 0; i < sizeof(arr); i++)
    {
        if (arr[i]->id("_random_orc"))
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
    set_alarm(5.0, 0.0, "help_friend", attacker);
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
        command("say Traitorous brigand!");
        command("kill " + lower_case(ob->query_real_name()));
    }
}
