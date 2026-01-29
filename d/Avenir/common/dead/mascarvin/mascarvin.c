// Mascarvin    /d/Avenir/common/dead/mascarvin/mascarvin.c
// creator(s): Lilith  Sept 2014
// last update: Lilith June 2021 Updated descs and got emote_hooks set up.
//              Lilith Sep 2021 added statserv logging.
//                
// purpose:   Mascarvin, Goddess of Death, Collector of Souls.
// note:      Players who meet her get their just reward.
//            She doesn't tolerate rudeness. In Sybarus,
//            rude behaviour is a crime worthy of death.
//            Code for the Meet Mascarvin quest is in 
//            /d/Avenir/common/dead/mascarvin/resting.c and/or
//            /d/Avenir/common/dead/mascarvin/raging.c 
//            depending on what the player does.
// bug(s):
// to-do:    
	

inherit "/d/Avenir/inherit/monster";
inherit "/d/Avenir/inherit/quest";
#include "/d/Avenir/smis/sys/statserv.h"
#include "defs.h"
#include <language.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>

string my_long();

void
create_monster()
{
    ::create_monster();

    set_name("mascarvin");
	set_living_name("mascarvin");
    set_adj(({"hauntingly-beautiful"}));
    set_title("the Goddess of Death and Rebirth");
    set_race_name("goddess");
	add_name("god");
    set_gender(G_FEMALE);

    set_long(my_long);

    /* Her stats don't matter, she can't be attacked */
    set_stats(({400,400,400,500,500,500}));

    add_prop(CONT_I_HEIGHT, 500);
    add_prop(CONT_I_WEIGHT, 56000);
    add_prop(OBJ_M_NO_MAGIC_ATTACK, 1);
	add_prop(OBJ_M_NO_ATTACK, 1);
    add_prop(NPC_I_NO_RUN_AWAY,1);
    set_appearance_offset(-50);
    set_alignment(0);
	
	seteuid(getuid(TO));
}

string
race_sound()
{
   return "speaks";
}

/* This determines what I 'look' like */
string
my_long()
{
    string  str;

    str = "She is "+ LANG_ADDART(implode(query_adjs(), " ")) +" "+
           query_race_name()+".\n";

    if (TP->query_met(query_real_name()))
    {
        str = query_name() +" is "+ LANG_ADDART(implode(query_adjs()," ")) 
            + " "+ query_race_name() +", presenting herself as:\n" 
            + query_name() +" "+ query_title() +", "+ query_exp_title() 
			+" enfleshed, female God of Sybarus.\n";
    }

    str+="It doesn't take much mental effort to recognize that you "
		+"are in the presence of a goddess. "
	    +"You are looking at She who collects the souls of dying "
		+"Sybarites and nurtures them back to the point where they "
		+"are ready to be reborn and serve the Gods once more.\n"
		+"Shadows play about this towering, womanly figure dressed "
	    +"in a long, voluminous cloak the color of blood.\n"
        +"She is wearing a simple black webcloth tunic with a "
        +"central slit through which the valley beween her four " 
        +"breasts can be glimpsed.\n"
		+"She is wearing a pair of "
        +"glittering sandals, a chain of fire agates about "
        +"her hips, a black diamond and platinum ring, "
        +"a fire agate studded armband, a platinum and "
        +"cobalt ear cuff, and a black diamond and "
        +"sapphire diadem on her forehead.\n"	
        +"She wears her black hair in very short, tight curls that "
        +"lay close to her skull.\n"
		+"Her skin is pale blue with a pearly sheen.\n"
        +"Her dark eyes are simultaneously compassionate "
        +"and impersonal.\n"
		+"You feel nourished and revived just being in her "
		+"presence.\n"
        +"You get the feeling that you should be on your best "
        +"behaviour around her.\n";		
    return str;
	
}

void 
rudeness_means_death(object tp)
{
    if (present(RIPO_ID, tp))
        return;		

	object poison;
    seteuid(getuid(TO));
	tp->set_fatigue(0);
	poison=clone_object(RIPOISON)->move(tp, 1);
    poison->start_me_up(tp);
    tp->move_living("X", CRYPT+"pit_falling");
	
}
	
void 
give_token(object tp)
{
	object token;
    seteuid(getuid(TO));
	token=clone_object("/d/Avenir/common/obj/syb_coin");
	token->set_heap_size(3 +random(10));
    token->move(tp, 1);			
}

public void
emote_hook(string emote, object actor, string adverb, object *oblist,
    int cmd_attr, int target)
{
	object para; 
	
    if(!interactive(actor))
        return;
	
	// She is not the target.
	if (target != 1)
		return;
	
	// The actor is already in trouble.
    if (actor->query_prop(BAAAD_MORTAL))
    	return; 
	
    string *offensive = ({ "kiss", "tickle", "pat", "fondle",
              "squeeze", "lick", "french", "ffinger", "bite",
			  "hug", "nibble", "pinch", "pet", "spank",
              "slap", "spit", "kick", "curse", "leer", "steal",
	          "caress", "flirt", "grope", "hold", "peek"});
			  
    string *respectful = ({ "bow", "curtsey", "respect", "worship", 	
        	  "grovel", "admire", "kneel", "thank" }); 

    if(member_array(emote, offensive) != -1) 
    {	
        /* Boy did they mess up their quest reward! */
        if (!CHECK_QUEST_MASQ(actor))
		{	
            reward_quest("Meet Mascarvin", actor, MASQ_GROUP, MASQ_BIT, MASQ_EXP_ALT);
	        SCROLLING_LOG(MASQ_LOG, capitalize(actor->query_real_name()) +
		         " met Mascarvin, was rude, got "+MASQ_EXP_ALT+" reward.");			
			STATSERV_LOG_EVENT("crypt", "Meet Mascarvin: alt v rude");
		}
		// Stop the room from continuing the script.
		ENV(TO)->stop_acting();
		// remove quest stage tracker.
        actor->set_skill(SS_MASQ_STAGE, 0);
		// Paralyze them until Mascarvin is done with them.
        //       para=clone_object(PARA)->move(actor, 1);
        actor->MAKE_INFIDEL;
	    FLUX("\n\nThe Source flares momentarily with a disturbing red-"
	       +"brown color.\nAs the light washes over you, a feeling of "
	       +"dread fills you. Someone has disrespected "
	       +"the goddess Mascarvin, and you know that their punishment"
	       +"--death--will be slow and painful.\n\n");
	    set_alarm(1.0, 0.0, &command("laugh slow"));
	    set_alarm(2.0, 0.0, &command("say You must have a death-wish "
	       +"because no one is foolish enough to disrespect a god "
		   +"and not expect consequences."));
        set_alarm(4.0, 0.0, &command("say Your wish is granted. Goodbye."));
	    set_alarm(5.0, 0.0, &rudeness_means_death(actor));
		return;
    }
	
    if(member_array(emote, respectful) != -1)  
    {
        if (actor->query_prop("_Mascarvin_Approves"))
		{
    		set_alarm(1.0, 0.0, &command("say Once was enough, child."));
	    	set_alarm(4.0, 0.0, &command("say Too often seems insincere "
			   +"or opportunistic."));
			return;
		}
		actor->add_prop("_Mascarvin_Approves", 1);
		set_alarm(1.0, 0.0, &command("smile approv"));
		set_alarm(4.0, 0.0, &command("say You have excellent manners."));
		set_alarm(6.0, 0.0, &command("say How refreshing."));
		set_alarm(7.0, 0.0, &give_token(actor));
		set_alarm(8.0, 0.0, &command("emote gives you some sybarun coins "
		    +"as a token of Her approval."));
		
		FLUX("\nThe Source reaches a new level of brightness and as its " 
		    +"light touches you, you have a feeling that someone " 
		    +" has pleased the goddess Mascarvin.\n\n");
		return;		
	}
}


