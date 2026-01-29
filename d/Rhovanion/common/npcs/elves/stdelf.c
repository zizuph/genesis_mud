/*
 * /d/Gondor/mordor/npc/towerorc.c
 *
 * This is the default orc in the Cirith Ungol. This orc will also patrol in
 * Torech Ungol from time to time. It is a very nice orc, for everything
 * in this orc is adjustable with only one patch. His armour and weapons are
 * dependant on his average stats and his skills will also be dependant on
 * his stats. The orc has several attack cries, which he obviously not waists
 * on wizards. With a slight chance he will get a key to the tower at
 * Cirtih Ungol and you can also give him a whip.
 *
 * I spent some time time coding this sucker and even more on debugging and
 * enhancing it. If you want to copy this orc and adjust it for your own
 * purposes, I do not mind you doing so IF you leave this header in tact.
 * You can add your own header AFTER this one.
 *
 * /Mercade 27 September 1993
 *
 * Revision history:
 */

/*
 * This is the standard elf for Thranduil's Caverns and the Mirkwood.
 * I used lots of ideas from Mercade's  towerorc.c
 *
 * Basic constants that deternine the Elf are BASE_ELF, RAN_ELF
 *
 * /Daneel November 1993
 *
 */

inherit "/std/monster";

#include <macros.h>
#include <language.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include "/d/Rhovanion/defs.h"

#ifndef BASE_ELF
#define BASE_ELF 30
#endif

#ifndef RAN_ELF
#define RAN_ELF 90
#endif

#undef ARM_DIR
#undef WEP_DIR
#define ARM_DIR "/d/Rhovanion/common/armours/elf/"
#define WEP_DIR "/d/Rhovanion/common/weapons/elf/"

#define SUP_ELF1_LEVEL      120
#define HIGH_ELF1_LEVEL      80
#define MEDIUM_ELF1_LEVEL    50

#ifndef RANDOM_WEAPONS
#define RANDOM_WEAPONS  ({ "sword", "knife" })
#endif
#ifndef RANDOM_ARMOURS
#define RANDOM_ARMOURS  ({ "helm", "shield", "boots", "gauntlets" })
#endif
#ifndef DEFAULT_ARMOURS
#define DEFAULT_ARMOURS ({ "plate" })
#endif

#define ALIGNLOOKS ({"merry","solemn","grave","thoughtful","singing"})

#ifndef COMBAT_CHAT_LIST
#define COMBAT_CHAT_LIST ({ "Just wait till Thranduil hears about this", \
                            "No longer will you be welcome here!", \
                            "Die then bastard." })
#endif

#ifndef CHAT_LIST
#define CHAT_LIST ({ "Do you know what Elrond is planning?", \
                     "Have you seen Mithrandir?", \
                     "Gollum got away!" \
                  })
#endif


/*
 * Global variables
 */
int knight_prestige;
int base = BASE_ELF + random(RAN_ELF);
string looks = ONE_OF_LIST(ALIGNLOOKS);
string type = "_low";

void
create_monster()
{
  int i;

    if (!IS_CLONE)
	return;

    if (base >= MEDIUM_ELF1_LEVEL) type = "_med";
    if (base >= HIGH_ELF1_LEVEL) type = "_high";
    if (base >= SUP_ELF1_LEVEL) type = "_sup";

    set_name("_silvan_elf");
    set_pname("elves");
    set_race_name("elf"); 
    set_adj(looks);
    set_short(looks + " elf");
    set_pshort(looks + " elves");

    set_long("This is a silvan elf, who never saw The Blessed Land.\n");

    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(CONT_I_HEIGHT, 200);
    add_prop(CONT_I_WEIGHT, 80000);
    add_prop(CONT_I_VOLUME, 80000);

    set_base_stat(SS_STR, (base * 3 / 4) + random(base / 2));
    set_base_stat(SS_DEX, (base * 3 / 4) + random(base / 2));
    set_base_stat(SS_CON, (base * 3 / 4) + random(base / 2));
    set_base_stat(SS_WIS, (base * 3 / 4) + random(base / 3));
    set_base_stat(SS_INT, (base * 3 / 4) + random(base / 3));
    set_base_stat(SS_DIS, (base * 4 / 5) + random(base / 2));

    refresh_mobile(); /* full hp, mana, fatigue */


    set_alignment(4 * base);
    knight_prestige =-( 4 * base);

    set_aggressive(random(0));

    set_skill(SS_BLIND_COMBAT, MIN(100,(base * 3 / 4) + random(base / 2)));
    set_skill(SS_WEP_SWORD,    MIN(100,(base * 3 / 4) + random(base / 2)));
    set_skill(SS_WEP_CLUB,     MIN(100,(base * 3 / 4) + random(base / 2)));
    set_skill(SS_WEP_AXE,      MIN(100,(base * 3 / 4) + random(base / 2)));
    set_skill(SS_WEP_POLEARM,  MIN(100,(base * 3 / 4) + random(base / 2)));
    set_skill(SS_WEP_KNIFE,    MIN(100,(base * 3 / 4) + random(base / 2)));
    set_skill(SS_PARRY,        MIN(100,(base * 3 / 4) + random(base / 2)));
    set_skill(SS_DEFENCE,      MIN(100,(base * 3 / 4) + random(base / 2)));
    set_skill(SS_AWARENESS,    MIN(100,(base * 3 / 4) + random(base / 2)));

    set_chat_time(10 + random(30));
    for (i = 0; i < sizeof(CHAT_LIST); i++)
       add_chat(CHAT_LIST[i]);

    set_cchat_time(random(10));
    for (i = 0; i < sizeof(COMBAT_CHAT_LIST); i++)
       add_cchat(COMBAT_CHAT_LIST[i]);

    set_act_time(10 + random(20));
    add_act("smile");
    add_act("sing");
    add_act("eat all");
    add_act("drink all");
    add_act("get all");

    set_cact_time(random(10));
    add_cact("scream");
    add_cact("grin");

    trig_new("'You' 'killed' %s", "react_kill");
}

/*
 * Give the elf armour and a weapon.
 */
void
arm_me()
{
    int i;
    object cash,
           *wep_arm;

    set_this_player(this_object());

    seteuid(getuid(TO));

    clone_object(WEP_DIR + ONE_OF_LIST(RANDOM_WEAPONS) + type)->move(TO);
    clone_object(ARM_DIR + ONE_OF_LIST(RANDOM_ARMOURS) + type)->move(TO);

    for (i = 0; i < sizeof(DEFAULT_ARMOURS); i ++)
    {
        clone_object(ARM_DIR + DEFAULT_ARMOURS[i] + type)->move(TO);
    }

    command("wield all");
    command("wear all");

    cash = clone_object("/std/coins");
    cash->set_coin_type("copper");
    cash->set_heap_size(random(base));
    cash->move(this_object());
    if(base > MEDIUM_ELF1_LEVEL)
    {
      cash = clone_object("/std/coins");
      cash->set_coin_type("silver");
      cash->set_heap_size(random(base / 2));
      cash->move(this_object());
    }
    if(base > HIGH_ELF1_LEVEL)
    {
      cash = clone_object("/std/coins");
      cash->set_coin_type("gold");
      cash->set_heap_size(random(base / 4));
      cash->move(this_object());
    }
    if(base > SUP_ELF1_LEVEL)
    {
      cash = clone_object("/std/coins");
      cash->set_coin_type("platinum");
      cash->set_heap_size(random(base / 8));
      cash->move(this_object());
    }
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

    arr = (object *)query_team_others();
    for (i = 0; i < sizeof(arr); i++)
     {
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

    if (random(10))
        call_out("help_friend", (5 + random(10)), attacker);
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
        command("grin " + ob->query_real_name());
        command("kill " + ob->query_real_name());
    }
}

void
react_kill(string who) {
   command("shout I killed "+who);
   command("get all from corpse");
   command("laugh");
}

void
shout_for_help(string who){
  call_out("command", random(10), "shout Help!!! "+who+" wants to kill me!");
}

/*
 * Solamnian knight prestige
 */
int
query_knight_prestige()
{
    return knight_prestige;
}
