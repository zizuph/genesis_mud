/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
    A traveller. Mortricia 920727
 */

#include "/d/Terel/include/Terel.h"
inherit STDMONSTER;

inherit "/std/act/seqaction";
inherit "/std/act/domove";

#include <ss_types.h>
#include <money.h>

/*
 * Function name: create_monster
 * Description:   Create the monster. (standard)
 */
public void
create_monster()
{
    if (!IS_CLONE)
        return;

    ::create_monster();
    
    set_name("traveller");
    add_name("man");
    set_short("traveller");
    set_long("A bearded man. He seems to be a traveller and, " +
	     "just like you, he is a stranger in this part of the world.\n");
    set_adj("bearded");

    set_race_name("human");
    set_gender(MALE);

    set_stats(({22, 18, 15, 20, 20, 25}));
    SET_MAX_HP;
    SET_MAX_MANA;
    set_alignment(200);
    
    set_skill(SS_DEFENCE,      random(10) + 20);
    set_skill(SS_UNARM_COMBAT, random(5)  + 20);
    set_skill(SS_WEP_KNIFE,    random(5)  + 16);

    set_act_time(30);
    add_act(({"cough"}));

    set_chat_time(30);
    add_chat("It's cold today.");

    set_random_move(11);

    add_prop(LIVE_I_NEVERKNOWN, 1);
    MONEY_MAKE_CC(20)->move(TO);

    set_all_hitloc_unarmed(15);
    set_all_attack_unarmed(20, 20);

    set_alarm(1.0, -1.0, "dress_me");
}

/*
 * Function name: dress_me
 * Description:   Called by seq_addfirst, this function will equip
 *                the traveller.
 */
public void
dress_me()
{
    object cloak, knife;

    FIX_EUID;
    cloak = clone_object(PORT_DIR + "armour/cloak");
    cloak->move(TO);

    command("wear cloak");

    if (random(2) < 1)
    {
        knife = clone_object(PORT_DIR + "weapon/knife");
        knife->move(TO);
        command("wield knife");
    }
}
