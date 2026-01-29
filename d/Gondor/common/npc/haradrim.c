/*
 * Gwyneth 4 November 2000 - Replaced ~elessar/lib/goodkill.h with
 *                           /d/Gondor/common/lib/logkill.c
 * Serif, October 6, 2001: made earrings wearable.
 * Serif, April 20, 2002: fixed pshort, adjectives, set times to randoms.
 */

inherit "/std/monster";

#include "/d/Gondor/common/lib/logkill.c"
#include <ss_types.h>
#include <macros.h>
#include "/d/Gondor/defs.h"

#define ATTACKED_HARADRIM  "_attacked_haradrim"

string    /* List of adjectives for the haradrim. */
random_haradrim()
{
    string *har = ({"tall", "tall", "tall", "slender",
        "muscular", "tall", "fierce", "alert"});

    return ONE_OF_LIST(har);
}

void
create_monster()
{
   string har = random_haradrim(),
       har2 = har;

   set_adj(har);
   set_name("haradrim");
   set_pname(({"men", "humans", "haradrim"}));
   set_short(har2 + " dark-skinned male human");
   add_name("man");
   add_name("southron");
   add_name("_harondor_haradrim");
   set_adj("dark-skinned");
   set_adj("male");
   set_long("This is a " + har2 + " and dark-skinned haradrim warrior, "
       + "clad in bright clothing and with golden earrings. He looks "
       + "fierce.\n");
   set_race_name("human");
   set_alignment(-200-10*random(24));
   default_config_npc(random(10)+53);
   set_base_stat(SS_CON,random(10)+62);
   set_skill(SS_WEP_SWORD, random(10)+70);
   set_skill(SS_AWARENESS, 20 + random(20));
   set_skill(SS_PARRY,85);
   set_skill(SS_DEFENCE,85);
   set_chat_time(16 + random(11));
   add_chat("I'll take the scalp of every dunadan that I kill!");
   add_chat("If only the signal for our attack would come.");
   add_chat("I'm tired of waiting in this filthy camp!");
   add_chat("Why do we have to camp with the dirty orcs?");
   add_chat("We will plunder the houses of Minas Tirith soon!");
   set_cchat_time(5 + random(2));
   add_cchat("Bleed to death, dirty hyena!");
   add_cchat("Your neck won't stand a chance against my scimitar!");
   add_cchat("Die screaming, dog!");
   seq_new("do_things");
   seq_addfirst("do_things", ({"@@get_armed",
       "say Run while you can, filthy rat!"}));
 
   /* XP Adjustment 2014-12-02 Cotillion */
   set_exp_factor(160);
}

void
get_armed()
{
    FIX_EUID
    clone_object(WEP_DIR + "haradscim")->move(TO);
    command("wield scimitar");
    clone_object(ARM_DIR + "haradcloak")->move(TO);
    command("wear cloak");
    clone_object(ARM_DIR + "haradshield")->move(TO);
    command("wear shield");
    clone_object(ITH_DIR+"forest/harad_earring")->move(TO);
    command("wear earrings");
}

/* Solemnian prestige */
int query_knight_prestige() { return 100; }

/*
 * Function name: attacked_by
 * Description:   This function is called when somebody attacks this object
 * Arguments:     ob - The attacker
 */
void
attacked_by(object ob)
{
    object  room = ENV(TO),
          *arr;
    
    ::attacked_by(ob);

    while (!room->query_prop(ROOM_I_IS))
	room = ENV(room);
    arr = filter(all_inventory(room), &->id("haradrim"));
    arr->notify_ob_attacked_me(TO, ob);
    ob->add_prop(ATTACKED_HARADRIM, 1);
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
