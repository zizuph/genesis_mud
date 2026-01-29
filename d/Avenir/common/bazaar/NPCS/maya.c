/* The widow of the Shipcaptain,
 * for the bury bones quest
 *    Cirion, 040996
 */

inherit "/d/Avenir/inherit/npc";
inherit "/d/Avenir/inherit/intro";
inherit "/d/Avenir/common/bazaar/NPCS/call_for_help";

#include "../bazaar.h"
#include "/d/Avenir/common/port/bury_bones.h"

#define ASKED      "_Avenir_burybones_asked_about_book"

string    who;

void create_monster()
{
   set_name("maya");
   set_living_name("maya");
   set_race_name("human");
   set_adj("sepulchral");
   add_adj("aging");
   add_name("human");
   set_title("the Widow");

   set_long("She was once beautiful, but now she is getting "
     +"quite old. Her long, careworn face is framed by steely "
     +"grey hair.\n");
   
   set_stats(({ 18, 26, 5, 48, 82, 29 }));
   set_gender(G_FEMALE);
   set_appearance(95);
   
   set_skill(SS_LANGUAGE,      20);
   set_skill(SS_AWARENESS,     35);
   set_skill(SS_DEFENCE,       20);
   set_skill(SS_UNARM_COMBAT,  14);
   set_skill(SS_SWIM,          10);
   set_skill(SS_CLIMB,         21);
   set_skill(SS_LOC_SENSE,     10);

   set_alignment(47);

   set_act_time(15);

  set_cact_time(3);

  remove_prop(NPC_M_NO_ACCEPT_GIVE);

  add_ask(({"husband","captain","braston","Braston","about husband",
     "about braston","about Braston"}),VBFC_ME("husband"));
  add_ask(({"ship","concubine","about ship","about concubine"}),
    VBFC_ME("ship"));
  add_ask(({"survivor","staek","Staek","about staek","about Staek"}), VBFC_ME("survivor"));
  add_ask(({"book","logbook","log","for book","for logbook",
     "for the book","give book","for log","about book"}),
     VBFC_ME("book"),1);
  set_default_answer(VBFC_ME("def_ans"));
  seteuid(getuid());
}

string def_ans()
{
  command("shrug .");
  return "";
}

string survivor()
{
  if(!TP->query_prop(SPOKENTO))
  {
    command("say How do you know about that?");
    return "";
  }

   delay_action(1.5, ({"say The only survivor of the "
    +"ship's journey was Staek, a young mate on the ship.",
     "say I think he is running a shipline of his own now, "
    +"although I haven't seen him in years."}));
   return "";
}

string ship()
{
  if(!TP->query_prop(SPOKENTO))
  {
    command("say How do you know about that?");
    return "";
  }

   delay_action(1.3, ({"say The fair ship Concubine was a proud and great "
    +"vessel, a suitable ship for my dear husband's greatness.",
     "say They never found the wreckage of it, and there "
    +"was but one survivor.",0,"say The only thing they recovered "
    +"was my husbands logbook, which they gave to me to remember "
    +"him by."}));
   return "";
}

string husband()
{
   delay_action(1.0, ({"emote weeps sadly",
     "say May his soul rest in peace.","say My husband was "
    +"a great man, the first to sail out through the great "
    +"Rift.","stare","say He never made it back, his ship "
    +"was torn to shreds when it tried to get back through "
    +"the rift."}));
   return "";
}

string book()
{
  if(!TP->query_prop(SPOKENTO))
    return "say How do you know about that?";

  if(!present(LOGBOOK_ID, TO))
  {
    if(strlen(who))
     return "say "+CAP(who)+" has borrowed the book, and hasn't "
         +"yet returned it.";
    else
     return "say Someone has stolen the book from me. It was "
         +"all I had to remember him by.";
   }

  if(TP->test_bit("Avenir", GROUP, BIT))
  {
    command("say But you have already seen it, "
          +CAP(TP->query_real_name())+".");
    return "";
  }

  TP->add_prop(ASKED, 1);

  command("say Hmmm... I still have his logbook with me.");
  command("say I keep it to remember him by.");
  command("sniff .");
  return "say I guess I could let you look at it for a minute, "
        +"if you absolutely promise to give it right back.";
}

void arm_me()
{
  object arm;

  seteuid(getuid(TO));

  arm = clone_object(OBJ+"worn/pshirt");
   arm->move(TO);
  arm = clone_object(OBJ+"books/logbook");
   arm->move(TO);

  command("wear all");
}

int query_knight_prestige()
{
   return -100;
}

void do_die(object killer)
{
  seteuid(getuid(TO));

#ifdef VERBOSE
   LOG_THIS(killer->query_name()+" killed Maya");
#endif
   ::do_die(killer);
}

void give_back(object what, object from)
{
   command("eyebrow . "+from->query_real_name());
   if(!command("give " + OB_NAME(what) + " to " + OB_NAME(from)))
     command("drop "+what->query_name());
}

void enter_inv(object what, object from)
{
  ::enter_inv(what, from);

  if(!living(from))
    return;

  if(what->id(LOGBOOK_ID))
  {
    set_alarm(1.0, 0.0, &command("thank "+from->query_real_name()));
    who = "";
    return;
  }

  if(what->id(RING_ID))
  {
    delay_action(1.5, ({"cry","say This was his ring! The one he "
     +"would seal letters with!",0,"say Where did you find it?",
      "hug "+from->query_real_name()}));
    LOG_THIS(from->query_name()+" gave the captain's ring to Maya.");
    return;
  }

  if(what->id(BONES_ID))
  {
    delay_action(1.0, ({"say What is this?",
      "emote gasps in horror!",run_away,remove_object}));
    return;
  }

  set_alarm(1.0, 0.0, &give_back(what, from));
}

void init_living()
{
  int      i;
  string  *cmds;

  ::init_living();

  cmds = ENV(TO)->query_exit_cmds();

  add_action("promise","promise");
  add_action("avoid","avoid");

  for(i=0;i<sizeof(cmds);i++)
   add_action("leave", cmds[i]);
}

void revenge(object who)
{
  object    book;

  if(ENV(TO) == ENV(who))
   return;

  if(!(book = present(LOGBOOK_ID, ({who}) + deep_inventory(who))))
   return;

  who->catch_msg("The book crumbles away to dust, "
    +"leaving nothing behind.\nYou feel you have done "
    +"an evil deed.\n");
  who->adjust_alignment(-200);
  book->remove_object();
#ifdef VERBOSE
   LOG_THIS(who->query_name()+" took the book away to "+file_name(ENV(who)));
#endif
}

int leave(string str)
{
  if(member_array(query_verb(), ENV(TO)->query_exit_cmds()) == -1)
   return 0;

  if(!present(LOGBOOK_ID, ({ TP }) + deep_inventory(TP)))
   return 0;

  set_alarm(0.9, 0.0, &command("shout No! Please don't take "
     +"it away from me, "+TP->query_name()+"!"));
  set_alarm(1.2, 0.0, &command("scream"));
  set_alarm(10.0, 0.0, &revenge(TP));
  return 0;
}

int promise(string str)
{
  if(!TP->query_prop(ASKED))
    return 0;

  NF("Promise what?\n");
   if(!strlen(str))
     return 0;

  if(!parse_command(str, ({}), 
   "[the] [widow] / [woman] / [Maya] [that] [I] "
  +"[will] / [to] 'return' [the] [a] 'book' / 'log' / 'logbook'"))
    return 0;

  TP->catch_msg("You promise "+QTNAME(TO)+" that you will "
    +"return the book.\n");
  say(QCTNAME(TP)+" promises something to "+QTNAME(TO)+".\n");

  if(!CAN_SEE(TO, TP) || !CAN_SEE_IN_ROOM(TO))
  {
    command("peer");
    return 1;
  }

  if(strlen(who) && !present(LOGBOOK_ID, TO))
  {
    command("say Sorry, but "+CAP(who)+" borrowed the "
     +"book, and hasn't given it back.");
    return 1;
  }
 
  if(!present(LOGBOOK_ID, TO))
  {
    command("say My book has been stolen by a thief!");
    command("cry");
    command("say It was all I had to remember him by!");
    return 1;
  }

  if(TP->test_bit("Avenir", GROUP, BIT))
  {
    command("say But you have already seen it, "
          +CAP(TP->query_real_name())+".");
    return 1;
  }

  if(!query_met(TP))
  {
    command("say How can I trust you? I don't even know "
     +"your name.");
    return 1;
  }
/*  Do we really want to favour alignments? 
  if (TP->query_alignment() < -15)
  {
    command("hmm");
    command("say Sorry, I don't think I can trust the likes of you "
           +"with my husband's journal.");
    return 1;
  }
*/
  command("say Ok, but please give it right back after "
    +"you have looked at it.");
  command("say It is all I have left to remember my "
    +"dear husband by.");
  if(!command("give logbook to "+OB_NAME(TP)))
    command("conf");
  else
   {
    who = TP->query_real_name();
    TP->remove_prop(ASKED);
    command("say And please stay right here while you are reading it.");
#ifdef VERBOSE
   LOG_THIS(TP->query_name()+" borrowed the logbook from Maya");
#endif
   }

  return 1;
}

int avoid(string str)
{
  if(str != "the gaze of the widow")
   return 0;

  if(TP->test_bit("Avenir", GROUP, BIT))
   return 0;

  TP->catch_msg("The gods dislike cheaters.\n");
  TP->set_bit(GROUP, BIT);

  LOG_THIS(TP->query_name()+" used 'avoid' on Maya. Bit set & killed.");
  TP->heal_hp(-TP->query_max_hp());
  TP->do_die(TO);
  return 1;
}
