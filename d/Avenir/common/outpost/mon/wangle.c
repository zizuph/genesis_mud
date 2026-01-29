//                   evil_guard
//                   Dwarven guard for the outpost gate
// creator(s):       Kazz   Jan 1995
//                   Cirion, updated it for the quest.
// revision history: Denis, Jul'96: Removed triggers altogether.
//                   Lilith, Aug 2014: Added Maivia Quest
// purpose:          dwarven guards (initially for the outpost)
//                   This one will try to get you to poison
//                   the water of the good_guard
//
 
inherit "/d/Avenir/inherit/helper";
inherit "/d/Avenir/inherit/quest";
inherit "/d/Avenir/inherit/intro";
 
#include "/d/Avenir/common/common.h"
#include "/d/Avenir/common/outpost/outpost.h"
#include "/d/Avenir/common/outpost/water_quest.h"
#include "/d/Avenir/common/dark/maivia_quests.h"
#include <language.h>
#include <money.h>
#include </sys/ss_types.h>

int give_poison(object who);
int stop(object who);
int reset_quest();
int reward(object player);
void go_away();

 
int done_quest, busy, alarm_id, action;
 
void
create_monster()
{
    if(!IS_CLONE)
       return;
 
    set_name("wangle");
    set_title("the member of the 3rd Outpost Division");
    set_living_name("wangle");
 
    add_name("avenir_dwarf_id");
    add_name("guard");
    set_pname( "guards" );
    add_pname( "dwarves" );
    set_race_name( "dwarf" );
    set_gender(G_MALE);
    set_adj("mean-looking");
    set_long("He guards the fort and watches all strangers. He has "
            +"a bitter and nasty look about him.\n" );
 
    // stats?  50+random(10)
    set_stats(({ 80, 75+random(10), 75+random(10),
        35+random(10), 35+random(10), 75 }));
 
    set_hp(1000);
    set_alignment(-500+random(200));
    set_monster_home(OUTPOST + "cave2");
    set_title("a guard of the Sybarus outpost");
 
    set_skill( SS_DEFENSE, 50 );
    set_skill( SS_WEP_AXE, 50 );
    set_skill( SS_WEP_POLEARM, 50 );               // for hammer?
    set_skill( SS_WEP_CLUB, 50 );               // for hammer
    set_skill( SS_BLIND_COMBAT, 50 );
    set_skill( SS_AWARENESS, 50 );
 
    remove_prop(NPC_M_NO_ACCEPT_GIVE);
    add_prop("_live_m_attack_thief", 1);
 
    set_cact_time(3+random(3));
    add_cact("emote grumbles: You will die." );
    add_cact("emote says: The Source gives me strength you can't imagine.");
    add_cact("emote says: I will enjoy presenting your heart to the Elves!" );
    add_cact("emote growls at you.");
    add_cact("emote growls: You better leave while you can." );
 
 
   add_ask(({"sybarus","bazaar"}),
      "say Its just over the water to the north. Find the water and hit the pipe.",1);

   add_ask("city", "say I believe the city is still off-limits to "+
           "Outsiders like you.",1);

   add_ask(({"kilnar","bastard"}), "say That motherless bastard insulted "
            +"me and my entire family. I hope he falls into the "
            +"chasm.",1);

   add_ask(({"insult"}), "say That's not important. But let me "
            +"tell you, I intend to get my revenge",1);

   add_ask(({"revenge"}),"say Oh, believe me, it will be great indeed!",1);
 
   add_ask(({"tablet","poison"}),"say Just drop the tablet into his "
            +"drink and bring it to him.",1);

   add_ask(({"drink","water","beer","pub","alcohol"}),"say Hmm ... make "
            +"sure the drink isn't alcoholic. I think he gave that up "
            +"a while ago.",1);
	
    add_ask(({"maivia", "'dark' 'elf' 'leader'", "'leader' [of] [the] 'dark' 'elves'"}),
	"say What makes you think I know anything about him "+
	"except what everyone knows?  He's out to destroy Sybarus.", 1);
    add_ask(({"[about] [the] 'letter' / 'letters' / 'scroll' [from] [maivia]"}),
	"say I ain't got time to talk about my writin habits. "+
	"If ya got a somethin for me, give it, if not, move along.", 1);
    add_ask(({"[for] [a] 'job' / 'help' / 'task' / 'quest'"}), 
	"say If I need help, I will ask you for it.", 1);
    add_ask(({"[open] [the] 'gate'"}), "say Just knock on it. If the guards up top "+
	"like the looks of you, they'll open it for you.", 1);
			
    add_ask("[about] 'sobriety'",      "@@ask_sober@@");		
    add_ask("[about] [being] 'sober'", "@@ask_sober@@");		
    add_ask("[about] '448'",           "@@ask_sober@@");		
    add_ask("[about] 'alcohol'",       "@@ask_sober@@");	
    add_ask("[about] [why] [are] [you] [so] 'grumpy'", "@@ask_sober@@");		
    add_ask("[who] [is] 'voloda'",            "@@ask_voloda@@");
    add_ask("[about] 'voloda' / 'painter' / 'paint'",    
        "@@ask_voloda@@");
    add_ask("[about] [where] [is] [the] [gear] 'painter' / 'voloda'",
    	"@@ask_voloda@@");
    add_ask("[about] 'fix' / 'fixing' 'chip' / 'chips'",
        "@@ask_voloda@@");

			
}
 
 
void equip_me ()
{
    int which_weapon;           // 66-33 split favouring hammers
 
    which_weapon = random(3);
    if (which_weapon > 1)
        clone_object (OBJ +"dw_rhammer")->move(this_object());
    else
        clone_object (OBJ + "dw_raxe")->move(this_object());
    command ("wield all");
 
    clone_object(OBJ + "dw_rchain")->move(this_object());
    clone_object(OBJ + "dw_rhelmet")->move(this_object());
    command ("wear all");
    MONEY_MAKE_CC(22 + random(5))->move(this_object());
    MONEY_MAKE_SC(3 + random(5))->move(this_object());
}

string ask_voloda()
{
    command("say Voloda is a talented painter. She uses gemstone "+
        "dust and minerals to make durable paints for our gear "+
        "so we can keep them in perfect shape.");		
	return "";
} // ask_voloda
	
string ask_sober()
{
	command("rolleyes");
	command("say A long time ago, back in 448, some dwarves "+
        "stationed at Fort Sybarus had too much to drink and "+
		"some dark elf filth tricked them into helping him "+
        "attack the Academy of Defense.");
    command("emote looks embarassed.");
    command("say It was a huge mess, as I'm sure you can imagine, "+
        "and ever since, we're not allowed a drop of alcohol "+
        "consumption while stationed at Fort Sybarus, on penalty "+
        "of death.");
    command("say It's like having to give up mother's milk!");
    command("say But the alternative was banishment of dwarven-"+
        "kind from Sybarus--and we didn't want to die out like "+
        "the hobbits did. So... we go without for a couple of "+
        "Wei.");
   command("shrug sheepish");
	return "";
} // ask_sober



/* ***** Quest functions ***** */

// Hook on nodding, instead of triggering.
// -=Denis, Jul'96.
public void emote_hook(string emote, object actor, string adverb)
{
    if(emote == "nod" &&
       actor->query_prop(GOOD_PROP) &
       !actor->query_prop(EVIL_PROP) &&
       !actor->test_bit("Avenir", GROUP, BIT))
     {  
         remove_alarm(alarm_id);
         action = 0;
         alarm_id = set_alarm(1.0, 2.5, &give_poison(actor));
     }
}

int give_poison(object who)
{
    action++;
    switch(action)
     {
       case 1:
         command("say That bastard Kilnar insulted me and "
                +"my whole family.");
         break;
       case 2:
         command("say I swore by Zaren I would get him, and I will...");
         break;
       case 3:
         command("say I bet he's pretty thirsty about now. He's "
                +"always getting people to run and get him water.");
         break;
       case 4:
         command("say Well, I've got something that will quench "
                +"his thirst.");
         break;
       case 5:
         command("snicker");
         break;
       case 6:
         command("say Just drop this in his water before you "
                +"give it to him.");
         break;
       case 7:
         clone_object(POISON)->move(TO);
         if(!command("give tablet to "+who->query_real_name()))
            command("drop tablet");
         who->add_prop(EVIL_PROP, 1);
         break;
       case 8:
         command("say I'll reward you well, too.");
         break;

       default:
          remove_alarm(alarm_id);
          alarm_id = 0;
          action = 0;
          break;
       }
   return 1;
}

void
init_living()
{
    ::init_living();

    if (!interactive(TP))
        return;
 
   if(TP->query_prop(EVIL_PROP) ||
      !TP->query_prop(GOOD_PROP) ||
      TP->test_bit("Avenir", GROUP, BIT))
         return;

   if(alarm_id)
      return;

   action = 0;
   alarm_id = set_alarm(0.8, 2.0, &stop(TP));
   return;
}
 

int stop(object who)
{
    action++;
    switch(action)
     {
       case 1:
         command("say Hey you ... wait a minute, please.");
         break;
       case 2:
         command("say I've got a job for you. It'll pay well.");
         break;
       case 3:
         command("say If you are interested, just nod your head.");
         break;

       default:
          remove_alarm(alarm_id);
          alarm_id = 0;
          action = 0;
          break;
       }
   return 1;
}

int reset_quest()
{
  return 0;
}

void reward(object player)
{

    MONEY_MAKE_GC(20 + random(10))->move(this_object());
// Monitary reward for doing the nasty deed.

    set_alarm(0.4, 0.0, &command("laugh madly"));
    set_alarm(2.5, 0.0, &command("thank "+player->query_real_name()));
    set_alarm(4.0, 0.0, &command("give gold coins to "+player->query_real_name()));
    set_alarm(5.0, 0.0, &go_away());

    if(player->test_bit("Avenir", GROUP, BIT))
         return;
 
    player->remove_prop(GOOD_PROP);
    player->remove_prop(EVIL_PROP);

    reward_quest("Poison Kilnar", player, GROUP, BIT, EXP,
                  EVIL_ALIGN, BAD_PRESTIGE);
    WRITE_THIS_LOG( QUEST_FILE, player->query_name()
        +" poisoned Kilnar"
        +": "+EXP+" xp.\n" );
  
    return;
}

void go_away()
{
   run_away();
   remove_object();
}


void not_wanted(object what, object who)
{
    command("frown "+who->query_real_name());
    if (!command("give "+what->query_name()+" to "
				 +who->query_real_name()))
        what->remove_object();  
}

/* Maivia's scroll quest */
void
reward_maivia_quest(object player)
{

    reward_quest(QUEST_MAV1, player, M_GROUP, MBIT_WANGLE, MEXP_WANGLE);	
    WRITE_THIS_LOG( QUEST_LOG, "gave Maivia's scroll to Wangle and "+
				   "was rewarded "+MEXP_WANGLE+" exp.\n" );
	STATSERV_LOG_EVENT("dark", "Maivia quests done");
    say(QCTNAME(player) + " got a nice reward.\n");

}

public void
enter_inv(object obj, object from)
{
    ::enter_inv(obj, from);
	
    if (!living(from))
        return;

    if (obj->id(M_W_O))
    {
		if (CHECK_QUEST_6(from))
		{
			set_alarm (1.0, 0.0, &command("say This isn't for me."));
			set_alarm (3.0, 0.0, &command("say You must be mistaken."));
			set_alarm (4.0, 0.0, &not_wanted(obj, from));
			return;
		}
		if (obj->query_prop(Q_OB_OPENED))
		{
			set_alarm (1.0, 0.0, &command("say This scroll is missing its seal."));
			set_alarm (3.0, 0.0, &command("say I can't be sure it is authentic."));
			set_alarm (4.0, 0.0, &not_wanted(obj, from));
			return;
		}
		else
		{
		    set_alarm (2.0, 0.0, &command("emote nods furtively."));
		    set_alarm (3.0, 0.0, &reward_maivia_quest(from));
		    return;
		}
    }

    set_alarm(0.1, 0.0, &not_wanted(obj, from));
}


