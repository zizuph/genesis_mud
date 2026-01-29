// file:    /d/Avenir/common/dead/mon/banshee.c
// Banshee that holds the key to the crypts
// creator(s): Cirion, October 1996
// purpose: Former Chatelaine of her house, now she is 
//          chatelaine of the catacombs.
// bug(s):
// to-do:    make unfreindly to holy & anti-undead types
// mofications: 
//           Lilith, Dec 2007: Added functionality for the golden watch 
//           Lilith, Jun 2021: Added asks for 5 of 6 quests on the Dead Isle
//                              Added functionality for the Banshee Mask quest.
//           Lilith, Oct 2021: Lowered live_i_quickness req to >24
//                             fixed line 630 runtime error  (I think)
//                             fixed name error in quest log.
//           Lilith, Nov 2021: reduced the length of time on the paralyze.
//                      
// to do:

inherit "/d/Avenir/inherit/monster";
inherit "/d/Avenir/inherit/defeat";
inherit "/d/Avenir/inherit/quest";
inherit "/std/act/asking";

#include "../dead.h"
#include <formulas.h>
#include <cmdparse.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <language.h>
#include <poison_types.h>
#include "/d/Genesis/gems/gem.h"
#include "/d/Avenir/smis/sys/statserv.h"
#include "/d/Avenir/include/guilds.h"
#include "/d/Avenir/include/relation.h"

#define PEOPLE     (FILTER_LIVE(all_inventory(ENV(TO)) - ({ TO })))

string answer_default();
string answer_cat_ask();
string answer_chat_ask();
string answer_i_am();
string answer_mask_ask();
string answer_masq_ask();
string answer_quest_ask();

int
dead_filter_fun(object ob)
{
    string    nihil;
    object    where;

    if(!(where = ENV(ob)))
      return 0;

    if(!wildmatch("*Avenir/common/dead*", file_name(where)))
      return 0;

    if(wildmatch("*Avenir/common/dead/cata*", file_name(where)))
      return 0;
  
    return 1;
}

void 
tell_dead(string str)
{
    (filter(users(), dead_filter_fun) - PEOPLE)->catch_msg(str);
}

object *
dead_people()
{
    return filter(users(), dead_filter_fun) - all_inventory(ENV(TO));
}

string
my_short()
{
	if (TP->query_prop(WIND_PROP))
        return "slender luminous figure"; 
    if (TP->query_prop(LIVE_I_QUICKNESS) > 24)
        return "slender luminous figure";		
    else 
        return "luminous blur";
}

string
my_long()
{
    if (TP->query_prop(WIND_PROP) ||
	    TP->query_prop(LIVE_I_QUICKNESS) > 24)
        return "You are moving at a faster tempo than normal "+
               "so now you can see the figure, making it "+
			   "possible to distinguish "+
               "clearly a beautiful female form with wildly "+
               "floating hair. Her eyes are ageless and "+
               "dark as death, and they seem to ask questions "+
               "and expect answers. She resembles the banshees "+
			   "of lore.\n";        
    else 
        return "It is little more than a streak of light "+
               "that seems to be moving too quickly for "+
               "you to focus on.\n";
}


void 
create_monster()
{
    ::create_monster();
    set_name("banshee");
    add_name(({ "blur", "streak", "figure", "form", "bean sidhe" }));
    add_adj(({"slender", "luminous"}));
    set_short("@@my_short");
    set_long("@@my_long");
    set_gender(G_FEMALE);
    set_stats(({150,300,150,300,300,300}));
 
    set_skill(SS_UNARM_COMBAT, 95);
    set_skill(SS_DEFENCE, 93);
    set_skill(SS_AWARENESS, 99);
    set_skill(SS_BLIND_COMBAT, 100 );
    set_skill(SS_ACROBAT, 90);
	
	/* Natural body armour of 60 */
    set_all_hitloc_unarmed(60);
	
	/* Powerful unarmed attack */
    set_all_attack_unarmed(65, 65);

    /* She is moving very, very fast */
    add_prop(LIVE_I_QUICKNESS, 250);
    add_prop(LIVE_I_NO_CORPSE, 1);
    add_prop(LIVE_I_SEE_DARK, 10);
    add_prop(LIVE_I_UNDEAD, 95);
    add_prop(LIVE_I_NEVERKNOWN, 1);
	remove_prop(NPC_M_NO_ACCEPT_GIVE);
    add_prop(NPC_I_NO_FEAR, 1);
    add_prop(NPC_I_NO_LOOKS, 1);
	set_alignment(0);
	
    set_hp(query_max_hp());
	
	set_act_time(50);
	add_act("emote emits a chilling, high-pitched wail.\n"+
	    "You have a feeling that someone just died.");
    add_act("emote wails with grief.");
	add_act("emote keens in such a way that you feel "+
	    "swamped with sadness.");
	add_act("emote sings a sad and beautiful song.");

   set_cact_time(3);
    add_cact("emote lets out a wail of anger and pain.");
    add_cact("emote screams in rage.");
    add_cact("glare menac enemy");

    // Grr. We must set a default answer 
    set_default_answer(VBFC_ME("answer_default"));
    
    add_ask(({"[how] [to] [open] / [enter] [the] "+
	    "'catacomb' / 'catacombs' / 'gate'"}),
		answer_cat_ask );
    add_ask(({"[for] / [about] [the] 'catacomb' / 'catacombs' 'gate' [quest]"}),
		answer_cat_ask );
	add_ask(({"[about] [the] 'house' [of] [the] 'dead'"}),
		answer_cat_ask );
    add_ask(({"[what] [does] [the] / [a] 'chatelaine' 'want' / 'wants'"}),
        "say What does any Gatekeeper in Sybarus want?", 1);	
    add_ask(({"[about] [the] / [a] 'chatelaine' [of] [the] [catacombs]"}),
        answer_chat_ask );	
 	add_ask(({"[for] / [about] [a] / [the] [bejewelled] "
	        +"[platinum] 'death' 'mask' [quest]"}),
	    answer_mask_ask );
	add_ask(({"[for] / [about] [a] / [the] 'death' 'mask' [quest]"}),
	    answer_mask_ask );
    add_ask(({"[about] [the] 'gallery'/ 'galleries' [of] [bones]"}),
        "emote speaks very slowly: In the catacombs the walls are lined with galleries of bones", 1);	
	add_ask(({"[about] [the] [meet] 'mascarvin' [quest]"}),
	    answer_masq_ask );
	add_ask(({"[for] / [about] [a] 'help' / 'quest' / 'task'"}),
	    answer_quest_ask );
	add_ask(({"[who] / [what] [are] 'you'"}), 
        answer_i_am );
    add_ask(({"[what] [is] [your] 'name'"}), 
        answer_i_am );
    add_ask(({"'introduce' / 'intro' [yourself]"}), 
        answer_i_am);
    add_ask(({"[how] [are] [you] [the] 'key'"}), 
        answer_i_am );		
 	add_ask(({"[about] [where] [to] [bury] [the] 'captains' 'bones'"}),
	    "emote speaks very slowly: "+
        "Ah... do you know that little hill at the farthest north "+
		"point of the island? I heard from the captain's ghost that "+
		"he wanted his bones buried there, under the oak tree. You'll "+
		"need a shovel, of course.", 1);
 	add_ask(({"[about] [how] [to] [fix] [the] [golden] 'watch' [quest]"}),
        "emote speaks with excruciating slowness: "+
		"Rare that watch is. Something very useful here, in this spot, "+
		"especially if you manage to get it working. Seek the Source if "+
		"you want to know how.", 1); 
	add_ask(({"[about] [the] [massive] 'guardians' / 'sentinels' / 'objects'"}),
	    "emote says with exaggerated slowness: Those are the guardians "+
		"of the hours, of course. You aren't from around here, are you?", 1);
    add_ask(({"[about] [the] 'guardians' 'of' 'the' 'hours'"}),
	    "emote seems to curtsey in the direction of one of the massive objects",1);
}

string
answer_default()
{
    if (!CAN_SEE(TO, TP))
    {
        command("emote looks angrily about.");        
        return "";
    }
    switch(random(4))
    {
        case 0:
            command("emote gestures in a way you find threatening.");
            break;
        case 1:
            command("emote appears to be sharpening her nails.");
            break;
        case 2:
            command("emote floats close to you and laughs in your face.");
            break;
        case 3:
            command("emote speaks slowly: You. Are. Wasting. My. Time.");
            break;
    }
	// 1 in 25 chance of pissing her off.
	if (random(25) < 1)
	{
		command("say You annoy me with your questions! "+
		    "You should have learned to ask better ones.");
        command("$kill "+ NAMEQ(TP));
	}
    return "";    
}

// answers to asks about gate, catacombs, key.
string
answer_cat_ask()
{
    if (IS_INFIDEL(TP))
    {
        command("emote screams something that sounds like: INFIDEL!");
        command("$kill "+ NAMEQ(TP));
        return "";
    }
    if (!CAN_SEE(TO, TP))
    {
        command("emote shrieks something so fast she is unintelligible.");
        return "";
    }		
    if (TP->query_prop(WIND_PROP))
    {
        set_alarm(2.0, 0.0, &command("emote narrows her eyes thoughtfully.")); 
	    command("whisper to "+ NAMEQ(TP) +" "+
		    "Make haste child, the Hour is near.");
        command("whisper to "+ NAMEQ(TP) +" "+
            "Through your watch you may know the Hour."); 
	    command("whisper to "+ NAMEQ(TP) +" "+
	        "Pray to the Guardian of the time to find your way "+
			"into the catacombs, the House of the Dead...");
        command("whisper to "+ NAMEQ(TP) +" "+
		    " To leave there you will need to find the Gate... and "+
			"the Chatelaine who operates it. She will require the "+
			"same token that opens most gates in Sybarus. ");
        return "";
    }
	if (TP->query_prop(LIVE_I_QUICKNESS) > 24)
    {
	    command("whisper to "+ NAMEQ(TP) +" "+
		    "Make haste child, the Hour is near.");
	    command("whisper to "+ NAMEQ(TP) +" "+
	        "Pray to the Guardian of the time to find your way to "+
			"the catacombs...");
    	command("whisper to "+ NAMEQ(TP) +" "+
		    " and to Mascarvin.");
		return "";
	}

    command("emote shrieks something so fast that she is unintelligible.");
    return "";    
}

// answers asks about the Chatelaine
string
answer_chat_ask()
{
    if (IS_INFIDEL(TP))
    {
        command("emote screams something that sounds like: INFIDEL!");
        command("$kill "+ NAMEQ(TP));
        return "";
    }
    if (!CAN_SEE(TO, TP))
    {
        command("emote shrieks something unintelligible.");
        return "";
    }
	// Notice the mask to get players to ask her about it.
	// Then continue on to the rest of the answer.
	if (TP->query_prop(DMASK_PROP))
		command("whisper to "+ NAMEQ(TP) +" I like your "+
	        "death mask. Very nice. ");
    if (TP->query_prop(WIND_PROP))
    {
        command("say to "+ NAMEQ(TP) +" "+
            "Every House in Sybarus has a Chatelaine, a "+
            "keeper of the keys. Even the House of "+
			"the Dead has one. She minds the gate  "+
			"and decides who may pass and who may not. "+
			"Like all gatekeepers here, she requires "+
			"a token of the God's approval.");
        return "";
    }
	if (TP->query_prop(LIVE_I_QUICKNESS) > 24)
	{
        command("whisper to "+ NAMEQ(TP) +" "+
            "The House of the Dead has a Chatelaine. "+
			"She decides who may pass through the gate "+
			"and who may not. She might let you pass "+
			"if you have what she wants.");
		return "";
 	}		
	
    command("emote screeches something fast and unintelligible to you.");
    return "";


}

string
answer_i_am()
{
    if (IS_INFIDEL(TP))
    {
        command("emote screams something that sounds like: INFIDEL!");
        command("$kill "+ NAMEQ(TP));
        return "";
    }
    if (!CAN_SEE(TO, TP))
    {
        command("emote screams something high-pitched and unintelligible to you.");
        return "";
    }
	if (TP->query_prop(DMASK_PROP))
	{ 
        command("whisper to "+ NAMEQ(TP) +" "+
		    "I do love your death mask! I want one, too, but not just "+
			"any old one...");
        command("whisper to "+ NAMEQ(TP) +" "+
	        "And oh, yes -- I am the key to the catacombs. It is through "+
			"me that you will find your way.");
		return "";
    }
	if (TP->query_prop(LIVE_I_QUICKNESS) > 24)
	{
		command("sigh quickly");
        command("whisper to "+ NAMEQ(TP) +" "+
            "I am the key to the catacombs. Through me you will "+
            "find the way...");
		return "";
 	}		
    if (TP->query_prop(WIND_PROP))
    {
        command("whisper to "+ NAMEQ(TP) +" "+
            "I am the key to the catacombs. Through me you will "+
            "find the way...");
        return "";
    }
	
    command("emote shrieks something unintelligible.");
    return "";

}

string
answer_mask_ask()
{
    if (IS_INFIDEL(TP))
    {
        command("emote screams something that sounds like: INFIDEL!");
        command("$kill "+ NAMEQ(TP));
        return "";
    }
    if (!CAN_SEE(TO, TP))
    {
        command("emote shrieks something unintelligible.");
        return "";
    }
	if (TP->query_prop(DMASK_PROP))
	{
		command("whisper to "+ NAMEQ(TP) +" That is a beautiful "+
		    "death mask you are wearing."); 
        command("whisper to "+ NAMEQ(TP) +" There is a death "+
            "mask that I want. It is the mask of my beloved. ");
        command("whisper to "+ NAMEQ(TP) +" If you come across "+
            "a bejewelled platinum mask whilst combing the "+
			"catacombs, bring it to me and I shall reward you "+
            "handsomely.");
		return "";
    }			
	if (TP->query_prop(LIVE_I_QUICKNESS) > 24)
    {
        command("whisper to "+ NAMEQ(TP) +" There is a death "+
            "mask that I want. It is the mask of my beloved. ");
        command("whisper to "+ NAMEQ(TP) +" If you come across "+
            "a bejewelled platinum mask whilst combing the "+
			"catacombs, bring it to me and I shall reward you "+
            "handsomely.");
        return "";
    }
    command("emote screeches something but you can only make "+
	    "out a few syllables. ...want... bej... ...tinum ...dea... "+
	    "mask.");
    return "";

}

string
answer_masq_ask()
{
    if (IS_INFIDEL(TP))
    {
        command("emote screams something that sounds like: INFIDEL!");
        command("$kill "+ NAMEQ(TP));
        return "";
    }
    if (!CAN_SEE(TO, TP))
    {
        command("emote shrieks something unintelligible.");
        return "";
    }
	if (TP->query_prop(WIND_PROP) || TP->query_prop(LIVE_I_QUICKNESS) > 24)
	{
        command("whisper to "+ NAMEQ(TP) +" "+
            "So you want to meet Mascarvin? I don't recommend "+
            "attempting it, but since you asked so nicely...");
		command("whisper to "+ NAMEQ(TP) +" "+
		    "You need to find your way through the catacombs. "+
			"Where a gallery ends you will find the entrance "+
            "to the place where she rests. Beware though, she "+
			"may not welcome guests."+
			""); 	
        return "";			
	}		
	if (TP->query_prop(DMASK_PROP))
	{
        command("whisper to "+ NAMEQ(TP) +" "+
            "So you want to meet Mascarvin? I don't recommend "+
            "attempting it, but since you have such a pretty mask...");
		command("whisper to "+ NAMEQ(TP) +" "+
		    "You need to find your way through the catacombs. "+
		    "Look in the places where the death masks are "+
			"found... and the bones of the faithful abound.");
        return "";			
	}
    command("emote is talking so fast that you "+
        "cannot understand her.");
    return "";

}

string
answer_quest_ask()
{
    if (IS_INFIDEL(TP))
    {
        command("emote screams something that sounds like: INFIDEL!");
        command("$kill "+ NAMEQ(TP));
        return "";
    }
    if (!CAN_SEE(TO, TP))
    {
        command("emote shrieks something unintelligible.");
        return "";
    }
	
	if (!TP->query_prop(LIVE_I_QUICKNESS) > 24)
	{
        command("emote screeches and wails.\nShe is moving and talking "+
		    "too fast for you to understand her.\nIf only you could be "+
            "as quick as she, then perhaps you could understand each "+
			"other.\n");			
		return "";
 	}	
	if (!CHECK_QUEST_GATE(TP))	
	{
		command("say If you are looking for something to do, perhaps "+
		     "you should begin with the catacombs gate.");
        return "";
	}
	if (!CHECK_QUEST_MASK(TP))	
	{
		command("say Now that you have appeased the Chatelaine, there is "+
		    "something you could do for me...");
		command("say There is a mask I want, a bejewelled platinum death "+
		    "mask. If you find one in the catacombs and bring it to me "+
			"I will reward you handsomely.");
        return "";
	}
	if (!CHECK_QUEST_MASQ(TP))	
	{
		command("say You have yet to meet with Mascarvin in her place "+
		     "of rest. Seek the entrance in the places where death "+
			 "masks are found and bones abound.");
        return "";
	}

}

// Player has managed to find the correct death mask (out of 16 possible)
// In only 7 guarded rooms of the 100+ rooms in the catacombs.
// It sounds much easier than it is -- they would probably
// have to go through multiple area resets to find one.
void
reward_mask_quest(object player)
{
	object reward;
    string str;

	seteuid(getuid(TO));
	
    reward_quest(MASK_QUEST, player, SHEE_GROUP, SHEE_BIT, SHEE_EXP);	
    SCROLLING_LOG(SHEE_LOG, player->query_cap_name()+" gave mask to Banshee and "+
				  "got "+ SHEE_EXP +" exp.\n" );
	STATSERV_LOG_EVENT("necronisi", "Gave Banshee her beloved's death mask");
    	
    reward = clone_object("/d/Genesis/gems/obj/sea_agate");
	reward->set_heap_size(12); // One for each hour guardian
	reward->move(TO);
    command("give gems to "+ NAMEQ(player));
}

void 
not_wanted(object what, object who)
{
    command("frown "+ NAMEQ(who));
    command("drop "+ what->query_name());
  
} 


void
enter_inv(object obj, object from)
{
    ::enter_inv(obj, from);
	
    if (!interactive(from))
        return;

    if (obj->short() == "bejewelled platinum death mask")
    {
		if (CHECK_QUEST_MASK(from))
		{
			set_alarm (3.0, 0.0, &command("say You've given me one just like it already."));
			set_alarm (4.0, 0.0, &not_wanted(obj, from));
			return;
		}
		else
		{
		    set_alarm (4.0, 0.0, &command("emote glows with joy."));
			set_alarm (6.0, 0.0, &command("say This must be the death mask of my beloved."));
			set_alarm (7.0, 0.0, &command("thank "+ NAMEQ(from)));
		    set_alarm (7.0, 0.0, &reward_mask_quest(from));
			obj->remove_object();
		    return;
		}
    }
    set_alarm(0.1, 0.0, &not_wanted(obj, from));
}



void
scream(string str)
{
    object *places;
    int     i;

    places = map(ENV(TO)->query_exit_rooms(), find_object);

    if(!sizeof(places))
     return;

    for(i=0;i<sizeof(places);i++)
       if(objectp(places[i]) && (places[i] != ENV(TO)))
         tell_room(places[i], str);
}

varargs int
res(object who = query_attack(), string type = MAGIC_I_RES_MAGIC, int val = 25 + random(20))
{
    if(who->query_magic_res(type) > val)
        return 1;

    return 0;
}


int 
special_attack(object enemy)
{
  object   *people,
           *here,
            attacker,
            ob;
  int       i,
            para_time;

  if(random(3))
   return 0;

  if(sizeof(query_enemy(-1)))
     attacker = ONEOF(query_enemy(-1));
  else
     return 0;

  here = PEOPLE;
  people = dead_people();

  switch(random(7))
  {
    /* Fear */
    case 0:
       command("emote throws back her head and lets out a wail of "
               +"anger and rage.");
       for(i=0;i<sizeof(here);i++)
        if(here[i]->query_stat(SS_DIS) < 70 + random(100))
        {
          if(res(here[i]))
          {
             here[i]->catch_msg("You feel resistant to some terrible "
               + "fear.\n");
             continue;
          }

          here[i]->catch_msg("A terrible fear invades your soul!\n");
          here[i]->add_panic(10 + random(50));

          if(here[i]->query_panic() > here[i]->query_stat(SS_DIS))
          {
            here[i]->catch_msg("You feel you must flee!\n");
            say(QCTNAME(here[i])+" looks terrified.\n", here[i]);
            here[i]->run_away();
          }
        }

      people->catch_msg("A terrifying wail echos across the moors.\n"
           +"You feel slightly panicky.\n");
      people->add_panic(10 + random(20));
      return 0;
      break;
   
    /* Drain strength/life */
    case 1:
      say(QCTNAME(TO) + " tears her nails along the face of "
          + QTNAME(attacker) + ".\n", attacker);
      attacker->catch_msg(QCTNAME(TO) + " lashes at your face "
          + "and tears her nails into your flesh.\n");
      if(res(attacker))
      {
         attacker->catch_tell("A terrible weakness starts to "
             + "come over you, but you manage to resist it somehow.\n");
         return 0;
      }

      attacker->catch_tell("You feel dizzy, "
          + "and your strength drains away.\n");
      attacker->add_fatigue(10 + random(20)); /* Make him tired */
      attacker->add_tmp_stat(SS_CON, -10, 10); /* Drain his con  */
      attacker->add_tmp_stat(SS_STR, -20, 10); /* Drain his str  */
      return 1;
      break;

    /* Sickness */
    case 2:
      say(QCTNAME(TO) + " stares deep into the eyes of "
           + QTNAME(attacker) + ".\n", attacker);
      attacker->catch_msg(QCTNAME(TO) + " stares deep into your "
           + "eyes.\n");

      if(res(attacker))
      {
         attacker->catch_tell("You feel you have resisted some "
            + "terrible sickness.\n");
         return 0;
      }

      attacker->catch_tell("You feel a gnawing sensation in your mind, "
           + "as if some parasite were eating away at your soul.\n");
      ob = clone_object("/std/poison_effect");
       ob->set_strength(20);
       ob->set_time(100);
       ob->set_damage(({ POISON_FATIGUE, 20, POISON_HP, 20, }));
       ob->set_poison_type("disease");
       ob->move(attacker, 1);
       ob->start_poison();
      return 0;
      break;

    /* Paralysis */
    case 3:
      say(QCTNAME(TO) + " runs her fingers along the face of "
           + QTNAME(attacker) + ".\n", attacker);
      attacker->catch_msg(QCTNAME(TO) + " runs her fingers along "
           + "your face.\n");
      if(res(attacker))
      {
         attacker->catch_tell("A weight seems to fall upon you, "
           + "but you somehow manage to resist it.\n");
         return 0;
      }

      attacker->catch_tell("A paralyzing horror invades "
         + "your soul, you feel incapacated.\n");
		 
      // Cirion made the original time as 10+random(50) but with
	  // white hits being so vicious now and her being hasted its
	  // a death sentance. Changed so its just a few rounds, max.
	  // --Lilith Nov 2021.
      para_time = 2 + random(10);
      if(present("banshee_terror", attacker))
      {
         return 0;
      }

      ob = clone_object("/std/paralyze");
       ob->set_name("banshee_terror");
       ob->set_fail_message("You are paralyzed with fear.\n");
       ob->set_stop_message("You feel your terror draining away, "
         + "your limbs are no longer paralyzed.\n");
       ob->set_strength(20);
       ob->set_remove_time(para_time);
       ob->move(attacker, 1);

      /* Make the attacked delay attacks as long as he is
       * paralyzed. */
      attacker->add_attack_delay(para_time);
      return 0;
      break;

    /* Slow attacks */
    case 4:
      say(QCTNAME(TO) + " cries out with rage and fury.\nYour "
         + "limbs feel numb, every movement is pain.\n");
      query_enemy(-1)->add_attack_delay(5 + random(10));
      return 0;
      break;

   default:
    return 0;
    break;
   }
}


void
victory()
{
    object corpse = present("corpse", ENV(TO));

    scream("A terrible cry of bloodthirsty rage echos from "
         + "nearby.\n");
    command("emote cries out in a terrible howl of "
         + "victory.\n");

    if(!corpse)
       return;

    tell_room(ENV(corpse), "The " + QSHORT(corpse)
         + " explodes in a terrible black flame.\n");
    corpse->remove_object();
}

void
notify_you_killed_me(object who)
{
    set_alarm(1.0, 0.0, victory);
    STATSERV_LOG_EVENT("necronisi", "Banshee killed someone");
}

void
check_meet(object tp)
{
    string  occ;
	
    if (!present(tp, environment(TO)))
        return;

    if (!CAN_SEE(TO, TP))
		return;

    if (IS_INFIDEL(tp))
    {
        command("emote screams something that sounds like: INFIDEL!");
        command("$kill "+ NAMEQ(tp));
        return;
    }

    occ = tp->query_guild_name_occ();
    if (occ == OUNION)
    {
        command("say to "+ NAMEQ(tp) +" I see you "+
                "Shadow Warrior. Serve the Gods well.");
        return 0;
    }
    
    command("emote glides to the center of the hill.");
    return;
}


void
init_living()
{
    ::init_living();

    if (interactive(TP))
        set_alarm(0.2, 0.0, &check_meet(TP));


}

