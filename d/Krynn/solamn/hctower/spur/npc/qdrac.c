/* **********************************************************
 *
 *    Draconian Prisoner, Knights' Spur
 *    Grace, Apr - May 1995
 *          Last Update:  4/20/96
 *
 *          modified from ~solamn/splains/living/baaz
 *            *  created by Aridor 04/19/94  * 
 *          'follow' code modified from Jeremiah's Maritta
 ********************************************************** */

#include "../local.h"
#include <ss_types.h>

#define SPUR_DRAC_QUEST  "_spur_draconian_quest"
#define QUESTION_DRAC    "_i_question_draconian"
#define S_Q_DRAC         "_succeed_question_draconian"
#define BEAT_DRAC        "_i_beat_draconian"

inherit "/d/Krynn/common/monster/baaz_base";

string color = "blue";

void
arm_draconian()
{
    /* No weapons and armour for this guy */
}


void
create_baaz()
{
    int i, j = random(6) + 2; /* j is the level of the draconian */
    string str;

    if (j < 1)
      j = 1;
    add_prop(OBJ_I_COLORABLE, 1);

#include "/d/Krynn/solamn/splains/living/level_me.h"
 
    set_short("draconian prisoner");
    set_long("This baaz draconian seems to have been injured " +
        "in battle. His left eye darts about, watching you "+
        "warily, while the other one is swollen painfully "+
        "shut. His scaly flesh is marred with unsightly "+
        "slashes and large blood-stained bandages. Manacles "+
        "encircle each wrist and ankle, binding him to the "+
        "cell wall via a length of chain.\n");
    set_name("draconian");
    set_name("_qdrac_");
    add_name(({"prisoner", "drac", "draconian prisoner"}));

    set_hp(30); // important, he's supposed to be near death

    for(i=0; i<6; i++)
        set_base_stat(i, j * 7 + random(10) + 40);
    set_skill(SS_DEFENCE,     j + random(5) + 50);
    set_skill(SS_PARRY,       j + random(5) + 50);
    set_skill(SS_WEP_SWORD,   j + random(5) + 50);
    set_skill(SS_WEP_KNIFE,   j + random(5) + 50);

   set_act_time(10);
    add_act("scream");
    add_act("emote moans: I thirst...");
    add_act("emote moans: Kitiara will come for me! She will raze "+
            "the Tower and bury you in its rubble!");
    add_act("moan pit");
    add_act("emote rubs a bruise on his arm, causing his "+
            "chains to rattle.");
    add_act("sneer");

   set_chat_time(7);
    add_chat("Go away. I will not break under questioning.");
    add_chat("Those Palanthians are real gentlemen. The "+
            "last one who came to question me beat me with "+
            "his cane. Humans have no imagination.");

    add_ask("'task' / 'help' / 'quest' / 'job' / 'errand'", 
     	    "say You're asking me? Well...sure! Get me out "+
            "of here!", 1);
    add_ask("'question'", "say I'm not answering any, so forget "+
            "it!", 1);
    add_ask("[about] 'water'",
            "say I'm dying from thirst. I need water.", 1);
    add_ask("'chains' / 'manacles' / 'ring' / 'mortar'", 
            VBFC_ME("follow"), 1);
    add_ask("'follow' / 'join' / 'team' [me]",
	    VBFC_ME("follow"), 1);
   add_prop(LIVE_I_NEVERKNOWN, 1);
   add_prop(NPC_I_NO_LOOKS, 1);
   remove_prop(NPC_M_NO_ACCEPT_GIVE);
   set_default_answer(VBFC_ME("what_me"));

}

init_living()
{
    ADA("beat");
    ADD("beat", "kill");
    ADA("question");
    ADD("question", "interrogate");
    ADD("beat", "torture");
}

void
set_color(string new_color)
{
    color = new_color;
}

string
what_me()
{
    command("emote grins stubbornly.");
    command("emote croaks: I won't tell you.");
    return "";
}

public void
enter_inv(object obj, object from)
{ 
    ::enter_inv(obj, from);

    if (!living(from))
        return;
    if (obj->query_prop(OBJ_I_CONTAIN_WATER) || obj->id("water") )
    {
        set_alarm(2.0,0.0,"check_qdq",obj,from);
    }
    else set_alarm(2.0,0.0,"not_desired",obj,from);
}

void
not_desired(object obj,object from) 
{
    command("say Resorting to bribes?");
    command("spit " + from->query_real_name());
    command("give "+ obj->query_name() + " to " + from->query_real_name());
    return;
}

/* 
 * Question Drac quest, for good-aligned players
 */
int
check_qdq(object obj, object from)
{
  /* Already done the question_drac_quest! */
  if (from->test_bit("Krynn", 3, 4))
  {
    command("drink all");
    command("say I have told you all that I will.");
    command("say Now, can you get me out of here?");
    return 1;
  }
  /* Has done the water quest -and- was sent by Gunthar */
  if (from->query_prop(SPUR_DRAC_QUEST) && 
      from->test_bit("Krynn", 3, 3 ))
  {
    command("drink water");
    from->add_prop(QUESTION_DRAC, 1);
    command("thank " + from->query_real_name()); 
    command("emote looks like he feels a little better.");                       
    return 1;
  }
  /* Nothing left to do. Water is probably old & stale. */

  command("emote takes a sip.");
  command("say This water is brackish.");                        
  command("say I cannot drink this!");
  command("give "+ (obj->query_name()) + " to " + (from->query_real_name()));
  return 0;
}

void
success_qdq(object player)
{
    set_this_player(player);
    //   Already done the question_drac_quest!
    if (player->test_bit("Krynn", 3, 4)) 
    {     
      write("The draconian prisoner tells you: I have already "+
            "told you everything I can.\n");
      return;
    }

    // Successfully questioned drac
      player->add_prop(S_Q_DRAC, 1);     
    player->remove_prop(QUESTION_DRAC);
    seteuid(getuid(TO));
    // log_file() logs relative to /d/Krynn/log/
    log_file("quests/spur_q_drac", 
	     extract(ctime(time()),4,15) + " " +
	     capitalize(player->query_real_name()) + "  questioned "+
	     "the draconian.\n");
    return;
}   
           
int
question(string str)
{
    object player = TP;
 
     if (str == "draconian" || str == "drac" || str == "prisoner" ||
         str == "draconian prisoner")
     {
        // Drac accepted water, will give info
        if (player->query_prop(QUESTION_DRAC))            
        {
           command("emote croaks: If your people had withheld water "+
                   "for much longer...");
           command("emote croaks: I would have died.");
           command("emote croaks: But you have done me a service and "+
                   "so I will tell you this one thing:");
           command("whisper "+ player->query_real_name() +" Inform Gunthar "+
                   "uth Wistan that the Red Army misleads him...");
           command("whisper "+ player->query_real_name() +" There is an "+
                   "object of great power at the old Solamnian outpost "+
                   "near Solace. He must find it before they do.");           
           command("whisper "+player->query_real_name()+" I will tell you "+
                   "nothing of my own Army though, lest Kitiara deliver "+
                   "me into the hands of Soth.");
           command("shiver");
           set_alarm(2.0, 0.0, "success_qdq", player);
        return 1;
        }
        // Player beat drac, will give info
        if (player->query_prop(BEAT_DRAC))
        {
           set_alarm(1.0, 0.0, "beat_qdq", player);
        return 1;
        }
     // Unsuccessful questioning
     command("snicker");
     command("say I won't tell you anything.");
     return 1;
     }
write("Question who?\n");
return 0;
}

int
beat(string str)
{
    object player = TP;
      if (str == "draconian" || str == "drac" || str == "prisoner" ||
         str == "draconian prisoner" || str == "baaz")
      {
        // Sent by Gunthar
        if (player->query_prop(SPUR_DRAC_QUEST))
        {
           command("cringe");
           command("say Alright, alright. I give up. ");
           command("say Just don't kill me.");
           command("sniff piti ");
           player->add_prop(BEAT_DRAC, 1);
           set_alarm(5.0, 0.0, "beat_qdq", player);
           return 1;
         }
        command("shout I am bound and cannot fight!");
        command("say Are you so cowardly a person that your opponents must "+
              "be shackled and near death before you dare attack them?");
        return 1;
     }
   return 1;
}

beat_qdq(object player)
{
     player = TP;
     //   Already done the question_drac_quest!
     if (player->test_bit("Krynn", 3, 4)) 
     return;

     // Beat the info out of the draconian
     seteuid(getuid(TO));
     log_file("quests/spur_q_drac", 
        extract(ctime(time()),4,15) + " " +
        capitalize(player->query_real_name()) + " beat the draconian.\n");
     command("say The only thing I will tell you is this: ");
     command("whisper "+ player->query_real_name() +" Inform Gunthar "+
             "uth Wistan that the Red Army misleads him...");
     command("whisper "+ player->query_real_name() +" There is an "+
             "object of great power at the old Solamnian outpost "+
             "near Solace. He must find it before they do.");           
     command("whisper "+ player->query_real_name()+" I will tell you "+
             "nothing of my own Army though, lest Kitiara deliver "+
             "me into the hands of Soth.");
     command("cringe");
return;
}

void
remove_it(object ob)
{
      ob->remove_object();
}

/*
 *  Free Draconian Quest, for evil-align players
 *  continued when drac is freed and new one is cloned
 */
follow()
{
       command("say I've been working at the mortar surrounding the ring "+
               "I am chained to. Free these chains from the wall and I "+
	       "will follow you out of here.");
       command("smile eager");
       return;
}
