// /d/Avenir/common/vanity/barber.c    
// creator(s): Lilith, Mar 2022
// purpose:    Barber for barbershop  
// changelog: 
// todo: need a place to haul people off to in the fort like 
//       in the bazaar when people attack/kill citizens.

inherit "/d/Avenir/inherit/intro";     
inherit "/d/Avenir/inherit/sigil";       /* Does House subloc */
inherit "/d/Avenir/inherit/sybarite";    /* Emotes and specials */

#include "/d/Avenir/include/defs.h"      /* Short-hand macros */
#include "/d/Avenir/include/paths.h"     /* Avenirian path defines */
#include "/d/Avenir/include/macros.h"    /* TO and TP */
#include "/d/Avenir/include/relation.h"  /* Gods and Sybarites */

#include <macros.h>                      /* macros like VBFC and QNAME */
#include <stdproperties.h>               /* properties */
#include <wa_types.h>                    /* weapon and armour defs */
#include <ss_types.h>                    /* skill and stat defs */


#define GAOL	"/d/Avenir/common/outpost/gaol_cell"


string my_long();

void
create_sybarite()
{  

    set_name("dato");
    add_name(({"barber"}));
    set_adj(({"bald", "bearded"}));
    set_race_name("gnome");
    set_gender(G_MALE);
    set_long(my_long);
    set_stats(({100,100,100,100,100,100}));
    set_syb_house("Hayz");
    set_title("ini Hayz, the expert barber of Fort Sybarus");
    set_alignment(0);
    
    set_all_hitloc_unarmed(25);
    set_all_attack_unarmed(20, 11);

    set_skill(SS_DEFENCE,        30);
    set_skill(SS_WEP_CLUB,       50);
    set_skill(SS_AWARENESS,      70);
    set_skill(SS_UNARM_COMBAT,   50);

    add_prop(CONT_I_HEIGHT,      80); 
    add_prop(CONT_I_WEIGHT,   35000);
    add_prop(NPC_I_NO_LOOKS,      1);
    add_prop(LIVE_I_NON_REMEMBER, 1);

    set_act_time(10);
    add_act("emote snips some hair with tiny little scissors.");
    add_act("emote brushes some hair from his trousers.");
    add_act("emote clears his throat and snaps his fingers.");
    add_act("emote tugs on his square-cut blue-green beard.");
    add_act("emote twirls the ends of his thin blue pencil mustache "+
        "with ends waxed straight.");

    set_default_answer(VBFC_ME("what_me"));
    add_ask(({"help","task","job","errand","quest","assignment"}), 
        VBFC_ME("give_job"), 1);

    seteuid(getuid(TO));
}

/* This determines what I 'look' like */
string
my_long()
{
    string  str;

    str = "He is "+ LANG_ADDART(implode(query_adjs(), " ")) +" "+
           query_race_name()+".\n";

    if (TP->query_met(query_real_name()))
    {
        str = query_name() +" is "+ LANG_ADDART(implode(query_adjs()," ")) 
            + " "+ query_race_name() +", presenting himself as:\n" 
            + query_name();
        if (strlen(query_title()))
            str += " "+ query_title() +",";
        str += " "+ query_exp_title() +", male "+ query_race_name() +".\n";
    }

    str += "His skin is a pinkish white that has never seen sunlight.\n"+
         "His eyes are a keen deep-brown.\n"+
         "His head has been waxed free of hair.\n"+
         "He has a square-cut blue-green beard decorated with trinkets.\n"+
         "He has a thin blue pencil mustache with ends waxed straight.\n"+
		 "He is wearing a pair of green silk trousers, a blue webcloth "+
         "vest, and a pair of brown leather boots.\n";
    return str;
}


string
what_me()
{
    switch(random(7))
    {
        case 0:
            command("say I am not permitted to answer that question.");
            break;
        case 1:
            command("say I style beards and mustaches. That is all I know.");
            break;
        case 2:
            command("emote determinedly ignores your question.");
            break;
        case 3:
            command("say Do you want me to style your facial hair, or not?");
            break;
        case 4:
            command("emote looks pointedly at you.");
            command("say Are you trying to make trouble?");
            break;
        case 5:
            command("say Have you learned the value of asking the "+
            "right questions yet?");
            break;
        case 6:
            command("emote shrugs and goes back to work.");
            break;
    }
    return "";    
}

string
give_job()
{
    command("chuckle at " + TP->query_name());
    command("say Kind of you to ask, but...Somehow I don't think "+
        "you're an experienced beard or mustache stylist.");
    return "";
}

int
special_attack(object target)
{
    switch (random(6))
    {
        case 0: command("skick");
           return 0;
		case 1: command("punch"); 
           return 1;    // We are done with this round.
        case 2: command("heal me");
           return 0;    // Allow another attack in this round.
        default: 
    }
    return 0;
}


/*
 * Function name: attacked_by
 * Description  : This routine is called when we are attacked.
 * Arguments    : object attacker - the attacker.
 */
public void attacked_by(object attacker)
{
    (GAOL)->call_for_guards(attacker);
        attacker->add_prop(EVILDOER, IS_EVILDOER(attacker) + 1);
	command("shout Hey punishers! Someone's starting a fight with me!"); 
		
    ::attacked_by(attacker);
}


