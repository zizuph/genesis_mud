/*
 *  /d/Gondor/common/npc/har_c.c
 *	A captain of the Haradrim
 *  -- Finwe, July 2005
 *
 * 11 June 2006 Palmer - Removed LIVE_I_SEE_DARK 
 * 11 Aug 2006 Palmer - Lowered alignment
 * March 16 2019 Finwe - Changed inherit file from /d/Shire/open/assist_friend
 *     to /d/Shire/open/assist_friend
 *
 */

#include "/d/Gondor/defs.h"
#include <composite.h>
#include <files.h>
#include <formulas.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <tasks.h>
#include <wa_types.h>

inherit "/std/monster";
inherit "/lib/unique.c";
inherit "/std/act/attack";
inherit "/d/Shire/open/assist_friend";

#define HARADRIM_ID "_haradrim_id"

string    /* List of adjectives for the haradrim. */
random_haradrim()
{
    string *har = ({"bloodthirsty", "brutal", "powerful", "wild",
        "ferocious", "terrible", "menacing", "barbaric", "glaring",
        "wild-eyed"});

    return ONE_OF_LIST(har);
}

//void arm_me();
//void    help_friend(object ob, object friend);
//void    test_can_see(object victim);

//static  int     Attack_Alarm;

public void arm_me();

nomask void
create_monster()
{
    int rnd = random(11);
    object wep;
    string har = random_haradrim(),
       har2 = har;
    seteuid(getuid(TO));

    set_adj(har);
    set_short(har2 + " dark-skinned male human");
    shire_npc_name = HARADRIM_ID;

    set_pshort(har2 + " dark-skinned male humans");
    set_name("haradrim");
    add_name(HARADRIM_ID);
    add_name("_harad_capt_");
    add_name("man");
    set_pname(({"men", "humans", "haradrim"}));
    set_race_name("human");
    remove_name("orc");
    set_long("This is a Captain of the Haradrim. The fierce human is " +
        "from the south and has dark skin. He has tattoos all over his " +
        "body, at least where clothing or armour does not cover it. " +
        "He is clad in bright colors and wears unusual armours from his " +
        "homeland. The Captain wears a great cloak that marks his rank " +
        "within the army.\n");

    set_base_stat(SS_STR, 200 + rnd);
    set_base_stat(SS_DEX, 200 + (rnd / 2));
    set_base_stat(SS_CON, 250 + (rnd * 2));
    set_base_stat(SS_INT, 115 + (rnd / 2));
    set_base_stat(SS_WIS,  85 + rnd);
    set_base_stat(SS_DIS, 125 + (rnd / 2));

    set_alignment(-800);
    set_skill(SS_WEP_SWORD,   75 + rnd);
    set_skill(SS_WEP_POLEARM, 75 + rnd);
    set_skill(SS_WEP_CLUB,    75 + rnd);
    set_skill(SS_WEP_AXE,     75 + rnd);
    set_skill(SS_WEP_KNIFE,   75 + rnd);
    set_skill(SS_WEP_MISSILE, 100);
    set_skill(SS_PARRY,       75 + rnd);
    set_skill(SS_DEFENCE,     75 + rnd);
    set_skill(SS_UNARM_COMBAT,40 + rnd);
    add_prop(CONT_I_HEIGHT,  220 + rnd);
    add_prop(CONT_I_WEIGHT, 200000 + rnd * 2000);
    add_prop(CONT_I_VOLUME, 200000 + rnd * 2000);
    set_aggressive(1);
    arm_me();


    set_learn_pref( ({ 1, 1, 1, 0, 0, 1, }) );

}

/* for the Solamnians */
public int query_knight_prestige() { return 500; }

do_die(object killer)
{
    object room = E(TO), haradrim;

    setuid();
    seteuid(getuid());

    if (query_hp() < 1)
    {
        command("emote screams something terrible.");
        command("emote screams: You shall not take me!");
        command("emote falls on his weapon and dies.");
    }

    return ::do_die(killer);

}

public void arm_me()
{
    int rand = random(2);
    object wep, arrows, quiver;

    FIX_EUID

    clone_object(ARM_DIR + "harc_collar")->move(TO);
    clone_object(ARM_DIR + "harc_helmet")->move(TO);
    clone_object(ARM_DIR + "harc_pmail")->move(TO);
    clone_object(OBJ_DIR + "harad_earring")->move(TO);
    command("wear armours");
    command("wear earrings");


    switch(random (99))
    {
        case 0..2: // magical items cloned, % change
        {
    
            switch(rand)
            {
                case 0:
                {
                    // Buggy sword, don't use until fixed!
                    // clone_object(WEP_DIR + "tulwar")->move(TO);
                    clone_object(WEP_DIR + "pulwar")->move(TO);
                    break;
                }
                case 1:
                {
//                    clone_object(WEP_DIR + "har_gbow")->move(TO);
                    clone_object(WEP_DIR + "har_lbow")->move(TO);
                    quiver = clone_object(OBJ_DIR + "greatquiver");
                    quiver->move(TO, 1);
                    command("wear quiver");
    
                    arrows = clone_object(WEP_DIR + "long_black_arrow");
                    arrows->move(quiver, 1);    
                    arrows->set_heap_size(50);
                    command("wield bow");
                    break;
                }
/*
                default:
                {
                    clone_object(WEP_DIR + "har_gbow")->move(TO);
                    quiver = clone_object(OBJ_DIR + "greatquiver");
                    quiver->move(TO, 1);
                    command("wear quiver");
    
                    arrows = clone_object(WEP_DIR + "long_black_arrow");
                    arrows->move(quiver, 1);    
                    arrows->set_heap_size(50);
                    command("wield bow");
                    break;
                }
*/
            }
            break;
        }
    
        default:

        {
            switch(random(3))
            {
                case 0:
                {
                    clone_object(WEP_DIR + "pulwar")->move(TO);
                    break;
                }
                case 1:
                {
                    clone_object(WEP_DIR + "har_halb")->move(TO);
                    break;
                }
                case 2:
                {
                    clone_object(WEP_DIR + "har_lbow")->move(TO);
                    quiver = clone_object(OBJ_DIR + "greatquiver");
                    quiver->move(TO, 1);
                    command("wear quiver");
    
                    arrows = clone_object(WEP_DIR + "long_black_arrow");
                    arrows->move(quiver, 1);    
                    arrows->set_heap_size(50);
                    command("wield bow");
                    break;
                }
            }
            break;
        }
    }
   command("wield weapon");
}

void
init_attack()
{
    object  victim;

    if (objectp(query_attack()))
        return;

    if ((victim = TP)->query_npc())
        return;
    if (!IS_GOOD(victim) || !CAN_SEE(TO, victim))
        return;

    set_alarm(0.0, 0.0, "do_attack", victim);
}

void
do_attack(object victim)
{
    command("kill "+victim->query_real_name());
}
