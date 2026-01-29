/*
 * A soldier of the Haradrim army
 * -- Finwe, July 2005
 *
 * 11 Jun 2006 Palmer - removed LIVE_I_SEE_DARK
 * 12 Aug 2006 Palmer - Lowered alignment
 *
 * -- Toby, 10th-Sept-2007: Fixed description.
 * March 16 2019 Finwe - Changed inherit file from /d/Shire/open/assist_friend
 *     to /d/Shire/open/assist_friend
 */

inherit "/std/monster";
inherit "/std/act/attack";
inherit "/d/Gondor/common/lib/logkill.c";
inherit "/lib/unique";
inherit "/d/Shire/open/assist_friend";

#include <composite.h>
#include <files.h>
#include <formulas.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <tasks.h>
#include <wa_types.h>
#include "/d/Gondor/defs.h"

#define HARADRIM_ID "_haradrim_id"
//#define ESG_NPC   "_esgaroth_npc_"

string    /* List of adjectives for the haradrim. */
random_haradrim()
{
    string *har = ({"bloodthirsty", "brutal", "powerful", "wild",
        "ferocious", "terrible", "menacing", "barbaric"});

    return ONE_OF_LIST(har);
}

public void arm_me();

public void create_monster()
{
    int rnd = random(11);
    object wep;
    string har = random_haradrim();
    seteuid(getuid(TO));

    set_adj(har);
    set_short(har + " dark-skinned male human");
    shire_npc_name = HARADRIM_ID;

    set_pshort(har + " dark-skinned male humans");
    set_name("haradrim");
    add_name(HARADRIM_ID);
    add_name("_harad_soldier_");
    add_name("man");
    set_pname(({"men", "humans", "haradrim"}));
    set_race_name("human");
    remove_name("orc");
    set_long("This is a tall and dark-skinned haradrim soldier. Clad in " +
        "bright clothing and with golden earrings, he looks hatefully at " +
        "you, brandishing his sharp weapon fiercefully.\n");

//    shire_npc_name = HARADRIM_ID;
    set_race_name("human");
    set_alignment(-800);
    default_config_npc(140 + random(10) );
    set_base_stat(100,random(10)+62);

    set_skill(SS_2H_COMBAT,90);
    set_skill(SS_AWARENESS,85);
    set_skill(SS_DEFENCE, 85);
    set_skill(SS_PARRY, 85);
    set_skill(SS_UNARM_COMBAT,40 + rnd);
    set_skill(SS_WEP_AXE,     75 + rnd);
    set_skill(SS_WEP_CLUB,    75 + rnd);
    set_skill(SS_WEP_KNIFE,   75 + rnd);
    set_skill(SS_WEP_MISSILE, 100);
    set_skill(SS_WEP_POLEARM, 75 + rnd);
    set_skill(SS_WEP_SWORD, random(75)+10);

    set_chat_time(16);
    add_chat("The Haradrim will overrun Gondor!");
    add_chat("If only the signal for our attack would come.");
    add_chat("The Dark Lord has promised us great rewards when he rules.");
    add_chat("Why do we have to camp with the dirty orcs?");
    add_chat("We will plunder the houses of Minas Tirith soon!");
    set_cchat_time(5);
    add_cchat("Bleed to death, dirty hyena!");
    add_cchat("Your neck won't stand a chance to my skills in combat!");
    add_cchat("Die screaming, dog!");
    set_aggressive(1);

    arm_me();
}

public void arm_me()
{
    int rand = random(3);
    object wep, arrows, quiver;

    FIX_EUID


    clone_object(ARM_DIR + "harc_collar")->move(TO);
    clone_object(ARM_DIR + "harc_helmet")->move(TO);
    clone_object(ARM_DIR + "harc_pmail")->move(TO);
    clone_object(OBJ_DIR + "harad_earring")->move(TO);
    command("wear armours");
    command("wear earrings");

    switch(rand)
    {
        case 0:
        {
            clone_object(WEP_DIR + "har_halb")->move(TO);
            command("wield weapon");
            break;
        }
        case 1:
        {
            clone_object(WEP_DIR + "pulwar")->move(TO);
            command("wield weapon");
            clone_object(ARM_DIR + "haradshield")->move(TO);
            command("wear armours");
            break;
        }
        case 2:
        {
            clone_object(WEP_DIR + "h_poleaxe")->move(TO);
            command("wield weapon");

/*
            clone_object(WEP_DIR + "har_lbow")->move(TO);
            command("wield weapon");

            quiver = clone_object(OBJ_DIR + "greatquiver");
            quiver->move(TO, 1);
            command("wear quiver");
    
            arrows = clone_object(WEP_DIR + "long_black_arrow");
            arrows->move(quiver, 1);    
            arrows->set_heap_size(50);
            command("wield bow");
*/
            break;
        }

    }
  
    clone_object(ARM_DIR + "haradcloak")->move(TO);
    command("wear cloak");

    
}

/* for the Solamnians */
public int query_knight_prestige() { return 300; }

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
