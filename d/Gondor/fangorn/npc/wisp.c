/*
 * /w/serif/will-o-the-wisp.c
 * A will-o-the-whisp from Gondor.
 * August 26, 2001, Serif.
 */

#pragma strict_types

inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/trigaction";
inherit "/std/act/domove";
inherit "/std/act/action";
inherit "/std/act/attack";

#include <composite.h>
#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include <wa_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

#define A_GLOW 0
#define A_GAS 1
#define A_SHAPE 2
#define A_FORM 3
#define H_CENTRE 0
#define H_PROT 1
#define H_EDGE 2
#define GLOW_OBJECT "/w/serif/harondor/obj/glow_ob.c"
#define BLIND_OBJECT "/w/serif/bhiri_blind_ob.c"
#define GAS_BLIND "_gondor_gas_blinded_me"

string  random_adj();     
string  random_adj2();  
string  random_wisp();
string  random_time();
string  random_flare();
string  random_fume();

object  cloud;
static  object  Victim;

public void  arm_me();

void
create_creature() 
{
string wisp = random_wisp(),
       wisp2 = wisp,
       adj = random_adj(),
       adja = adj,
       adj2 = random_adj2(),
       adjb = adj2;

    set_name(wisp);
    add_name("wisp");
    add_name("will-o-the-wisp");
    add_name("will-o'-the-wisp");
    add_name("swamp gas");
    add_pname("will-o-the-wisps");
    add_pname("will-o'-the-wisps");
    add_pname("shapes");
    add_pname("phosphorescences");
    add_pname("whisps");
    add_pname("swam gasses");
    set_race_name("swamp gas");
    set_adj(adj);
    set_adj(adj2);
    set_short(adja+ " " +adjb+ " " +wisp2);
    set_pshort(adja+ " " +adjb+ " " +wisp2+ "s");
    set_long("This "+adja+" " +adjb+ " " +wisp2+ " wavers in and out of "
        + "your perception, its vague form drifting and changing as you "
        + "watch. Now and then, gas swirls around it or protrudes from it "
        + "in shapes almost like limbs.\n");

    set_gender(G_NEUTER);
    set_alignment(0); 

    add_prop(CONT_I_WEIGHT,(100 + random(150)));
    add_prop(CONT_I_HEIGHT,(100 + random(100)));
    add_prop(CONT_I_VOLUME,(120000 + random(100000)));

    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(LIVE_I_SEE_DARK, 50);
    add_prop(NPC_I_NO_LOOKS, 1); 
    add_prop(LIVE_I_NON_REMEMBER,1); 
    add_prop(OBJ_I_NO_INS, 1);
    add_prop(LIVE_I_QUICKNESS, 10); 
    add_prop(LIVE_I_NO_CORPSE, 1);
    add_prop(LIVE_I_NO_BODY, 1);
    add_prop(OBJ_I_HIDE, 60);
    add_prop(OBJ_I_RES_POISON, 100);

    set_stats(({ 1, 70 + random(5), 30 + random(45), 1, 1, 20, }));

    set_skill(SS_UNARM_COMBAT, 60);
    set_skill(SS_DEFENCE, 40);
    set_skill(SS_AWARENESS, 25);
    set_skill(SS_BLIND_COMBAT, 70);
    set_skill(SS_SNEAK, 60 + random(20));
    set_skill(SS_HIDE, 55 + random(25));

    set_attack_unarmed( A_GLOW, 35, 1, W_IMPALE, 20, "ethereal glow");
    set_attack_unarmed( A_GAS, 35, 1, W_BLUDGEON, 20, "" +adjb+ " protruding "
        + "arms");
    set_attack_unarmed( A_SHAPE, 35, 3, W_BLUDGEON, 35, "gaseous edge");
    set_attack_unarmed( A_FORM, 40, 1, W_BLUDGEON, 35, "" +adja+ " gaseous "
        + "form"); 

    set_random_move(60 + random(87));

    set_hitloc_unarmed( H_CENTRE, ({ 1, 1, 1}), 60, "" +adja+ " gaseous "
        + "center");
    set_hitloc_unarmed( H_PROT, ({ 1, 1, 1}), 20, "" +adjb+ " protruding "
        + "arms");
    set_hitloc_unarmed( H_EDGE, ({ 1, 1, 1}), 20, "gaseous edge");

    add_item(({"form", "vague form"}), 
        "The "+adja+" " +adjb+ " " +wisp2+ " flickers and drifts around "
        + "as you observe it.\n");
    add_item(({"gas", "gasses"}), "Gas whisps around the "+adja+" " +adjb+ " "
        +wisp2+ ", glowing slightly.\n");
    add_item(({"arm", "arms", "protruding arm", "prodtruding arms"}), 
        "Arms of gas protrude now and then from the "+adja+" " +adjb+ " "
        +wisp2+ ".\n");
    add_item(({"edge", "gaseous edge"}), "The "+adja+" " +adjb+ " " 
        +wisp2+ "'s edge seems to waver as you examine it.\n");
    add_item(({"limb", "limbs", "protruding limb", "prodtruding limbs"}), 
        "Limbs of gas protrude now and then from the "+adja+" " +adjb+ " "
        +wisp2+ ".\n");

    set_act_time(4 + random(17)); 
    add_act("emote fades a little bit.");
    add_act("emote brightens a little bit.");
    add_act("emote seems to become more transparent.");
    add_act("emote seems to grow more solid.");
    add_act("emote slowly changes shape.");
    add_act("emote flickers suddenly.");
    add_act("emote wafts about slowly.");
    add_act("emote hisses almost silently.");
    add_act("emote drifts slowly into several smaller parts, then slowly "
        + "comes back together again.");
    add_act("emote expands slowly to almost twice its size, then slowly "
        + "retracts back into itself.");
    add_act("emote seems to grow less substantial.");
    add_act("emote flares brightly.","illuminate light");
    add_act("emote suddenly becomes almost invisible.");
    add_act("emote spreads out a little.");
    add_act("sigh quiet"); 
    add_act("illuminate light");
    add_act("illuminate light");
    add_act("illuminate light");
    add_act("illuminate light");
    add_act("illuminate light");
    add_act("illuminate light");
    add_act("illuminate light");
    add_act("illuminate light");

    set_cact_time(4 + random(2));
    add_cact("emote seems to grow less substantial.");
    add_cact("emote flares brightly.");
    add_cact("emote suddenly becomes almost invisible.");
    add_cact("emote spreads out a little.");
    add_cact("illuminate light");

    arm_me();

}

public void    /* Clones the glow_ob into the wisp. */
arm_me()  
{
    FIX_EUID
    clone_object("/w/serif/harondor/obj/glow_ob")->move(TO);
}

string    /* List of forms for the wisp. */
random_wisp()
{
    string *wisp = ({"will-o-the-wisp", "will-o-the-wisp", "will-o-the-wisp",
        "phosphorescence", "shape", "will-o-the-wisp", "form", "shape",
        "cloud", "will-o-the-wisp", "phosphorescence", "shape"});

    return ONE_OF_LIST(wisp);
}

string    /* List of adjectives for the wisp. */
random_adj() 
{
    string *adj = ({"small", "semi-transparent", "floating", "large",
        "vaguely", "strangely", "hovering", "floating", "dimly",
        "small", "semi-transparent", "floating", "large", "nebulous",
        "vaguely", "strangely", "hovering", "floating", "dimly"});

    return ONE_OF_LIST(adj);
}

string    /* List of adjectives for the wisp. */
random_adj2() 
{
    string *adj2 = ({"irridescent", "luminous", "ethereal", 
        "gaseous", "luminous", "luminous", "luminous", "vaporous",
        "luminous", "vaporous", "golden", "greenish", "gaseous",
        "vaporous", "luminous", "irridescent"});

    return ONE_OF_LIST(adj2);
}

string    /* List of duration names. */
random_time()
{
    string *time = ({"momentarily", "briefly", "partially", 
        "temporarily", "painfully"});

    return ONE_OF_LIST(time);
}

string    /* List of flare names. */
random_flare()
{
    string *flare = ({"with a dazzling light", "brightly", "brightly", 
        "with a strange flickering light", "harshly"});

    return ONE_OF_LIST(flare);
}

string    /* List of fume names. */
random_fume()
{
    string *fume = ({"Acrid", "Noxious", "Foul-smelling", "Greenish",
        "Bitter"});

    return ONE_OF_LIST(fume);
}

int query_knight_prestige() { return (10); }

mixed    /* Converts random move to a sneak. */
oke_to_move(string exit)
{
    if (this_object()->query_attack())
	return 0;

    return "sneak "+exit;
}

varargs void    /* Allows the wisp to sneak. */
sneak_away(string dir)
{
    string *dirs;

    if (strlen(dir))
    {
        command("sneak "+dir);
        return;
    }

    dirs = ENV(TO)->query_exit_cmds();

    dir = ONE_OF_LIST(dirs);

    command("sneak "+dir);
    sneak_away(dir);
}

int    /* Generates an emote during spontaneous combustion. */
do_pop()
{
    switch (random(12))
    {
    case 0..1:
    TO->command("emote hisses loudly.");
    break;
    case 2..4:
    TO->command("emote makes an abrupt popping noise.");
    break;
    case 5..6:
    TO->command("sigh airily");
    break;
    case 7..8:
    TO->command("emote sizzles and pops.");
    case 9..11:
    break;
    }
}

int
special_attack(object victim)
{
    string time = random_time(),
           flare = random_flare(),
           fl2 = flare,
           fume = random_fume(),
           fume2 = fume;

    if (random(100) > 50) 
    {
    TO->add_panic(-20); /* Wisp has low stats; this prevents panic. */
        return 0;
    }
    else
    {
    int    hp,
           burn;

    hp = (victim->query_hp());
    burn = (-hp/10);

    switch(random(10))
        {
        case 0..2: /* Attacker is blinded. */
    victim->add_attack_delay(6 + random(5));
    TO->catch_msg("You flare up with a blinding light!\n");
    write("The " +TO->query_short()+ " suddenly flares up " +flare+", " 
        +time+ " blinding you!\n");
    say("The " +TO->query_short()+ " suddenly flares up " +fl2+ "!\n", victim); 
    say(QCTNAME(victim)+ " looks a little dazed!\n", victim);
    clone_object(BLIND_OBJECT);
    BLIND_OBJECT->move(victim);
        break;
        case 3..4: /* Attacker is delayed slightly. */
    victim->add_attack_delay(2 + random(5));
    TO->catch_msg("Gas flows out from you.\n");
    write(fume+ " fumes drift from the " +TO->query_short()+ ", choking "
        + "you.\n");
    say(fume2+ " fumes from the " +TO->query_short()+ " curl around " 
        +QTNAME(victim)+ " and choke " +victim->query_objective()+
        ".\n", victim); 
    victim->command("cough");
        break;
        case 5..7: /* Attacker is delayed a little more. */
    victim->add_attack_delay(10 + random(5));
    TO->catch_msg("You avoid harm by becoming more diffuse.\n");
    write("You aim for the " +TO->query_short()+ ", but you stumble as your "
        + "blow passes harmlessly through its insubstantial form.\n");
    say(QCTNAME(victim)+ " stumbles as " +victim->query_possessive()+ " attack "
        + "passes harmlessly through the " +TO->query_short()+ ".\n"); 
        break;
        case 8..9: /* Attacker is burned 10% of current hp. */
    victim->heal_hp(burn);
    TO->command("drop all");
    do_pop();
    TO->catch_msg("You spontaneously combust!\n");
    write("The " +TO->query_short()+ " suddenly bursts into flames!\nYou get "
        + "burned slightly!\n");
    say(QCTNAME(victim)+ " gets slightly burned as the " +TO->query_short()+
        " suddenly bursts into flames!\n");
    GLOW_OBJECT->remove_object(); /* Burning removes the wisp. */
    TO->remove_object();
        break;
        }
        return 0;
    }
}

void    
do_die(object killer)
{
    setuid();
    seteuid(getuid());

    cloud = clone_object("/w/serif/cloud.c");
    cloud->move(ENV(TO)); /* Leave a cloud of gas behind. */

    GLOW_OBJECT->remove_object(); /* Remove the glow_ob. */

    TO->command("drop all"); /* In case weapons are in inventory. */

    tell_room(ENV(TO), "The " +TO->query_short()+ " dissipates, "
        + "leaving behind only a small " +cloud->query_short()+ ".\n");
    TO->remove_object(); /* No corpse, and no experience either. */

    ::do_die(killer);
}
