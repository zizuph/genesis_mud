/*
 *
 * Coded by Boromir June 15
 * Last edited and by whom :
 * June 12. by Boromir
 * Olorin, 13-jun-1995: updating the code
 *
 */
// I borrowed gelves.c from Shire to do this file!

inherit "/std/monster";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "../locals.h"
#include "attackers.c"

/* These are random guards descriptions */
#define RNDADJ ({"swarthy","grim","weathered","proud","long-legged","hard-working"})
#define RNDADJ2 ({"old","young","stiff","lean","dark-haired","thin"})
#define RNDLONG ({\
        "This human is shorter and more swarthy than "+\
        "other Gondorian people. "+(query_gender() ? "She":"He")+\
        " seems to be a person who somehow deals with farming.",\
})

/* These are random stats for the guards */
#define RNDSTAT ({\
		({30,20,25,25,20,15}),\
		({14,18,26,27,29,14}),\
		({25,17,38,25,16,14}),\
		({19,24,38,18,35,11}),\
		({39,21,25,25,26,24}),\
		({15,24,16,24,24,15}),\
		({18,24,26,37,18,16}),\
		({17,16,19,28,15,28})})

/* These is random equipment for guards */
#define RNDWEP ({"knife1","knife2","polearm1","polearm2","axe1"})
#define RNDARM ({"cloak1","cloak2","trousers1","trousers2"})

/* These are random combat and defence skills for guards */
#define SKILLCOM ({30,25,20,15,10})
#define SKILLDEF ({ 9, 6, 3,11, 5})

void 
create_monster()
{
    int     ran = random(6),
    ran2 = random(6),
    ran3 = random(5);

    set_name("peasant");
    add_name("villager");
    add_name("_thornlin_citizen");
    add_name("_thornlin_peasant");
    set_pname("humans");
    set_race_name("human");
    set_alignment(100);
    set_adj(RNDADJ[ran]);
    add_adj(RNDADJ2[ran2]);
    set_alignment(202 + ran);
    add_prop(CONT_I_WEIGHT, 70000 + ran*1000);
    add_prop(CONT_I_HEIGHT,   170 + ran2*2);

    set_gender(random(2)); /*Male or female*/
    set_long(BSN(RNDLONG[0]));

    set_stats(RNDSTAT[ran]);

    set_skill(SS_ANI_HANDL, 50+random(50));
    set_skill(SS_HUNTING, 30+random(20));
    set_skill(SS_AWARENESS, 20);
    set_skill(SS_WEP_KNIFE, SKILLCOM[ran3]);
    set_skill(SS_WEP_POLEARM, SKILLCOM[ran3]);
    set_skill(SS_DEFENCE, SKILLDEF[ran3]);
    set_skill(SS_PARRY, SKILLDEF[ran3]);

    set_chat_time(16);
    add_chat("How are you today?");
    add_chat("It is supposed to rain tomorrow, I think.");
    add_chat("I love pork chops.");
    add_chat("Have you been to Minas Tirith?");
    add_chat("Some say evil is here.");
    add_chat("Hmmmmm.");
    add_chat("I had a wonderful time at the inn last night.");
    add_chat("Do I know you?");

    set_act_time(9);
    add_act("smile .");
    add_act("cackle");
    add_act("sigh tiredly");
    add_act("emote looks worried at the clouds gathering in the east.");
    add_act("emote kicks some dirt off "+query_possessive()+" boots.");

    set_cact_time(5);
    add_cact("shout Militia, help!!");
    add_cact("shout Help me!");
    add_cact("shout I didn't do anything!");
    add_cact("say Why are you doing this ?");
}

void
arm_me()
{ 
    int     ran = random(5),
    ran2 = random(4);

    clone_object(OBJ_DIR + RNDWEP[ran])->move(TO,1);
    clone_object(OBJ_DIR + RNDARM[ran2])->move(TO,1);
    TO->command("wear all");
    TO->command("wield all");
}

