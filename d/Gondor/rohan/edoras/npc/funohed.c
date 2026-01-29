/*
 * Gwyneth 4 November 2000 - Replaced ~elessar/lib/goodkill.h with
 *                           /d/Gondor/common/lib/logkill.c
 */
inherit "/d/Gondor/std/monster";

#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/bits.h"
#include "/d/Gondor/common/lib/logkill.c"

#define GOT_DRINK_FROM_FUNOHED   "_gondor_i_got_drink_from_funohed"
#define STALLION_FILE		"/d/Gondor/rohan/edoras/stallion"

void    jump_home();
void    go_inn();
void    inform2(string who);
void    inform3(string who);
void    quest_done(object player);
int     not_finder(object player);
void    not_ring(string obj_name, string *names, object tp);

static int     jump_alarm,
               inform_alarm;

void
create_gondor_monster() 
{
  set_living_name("funohed");
  set_name("funohed");
  add_name(({"customer","man"}));
  set_race_name("human");
  set_adj(({"aged","gray-haired"}));

  set_long(BSN("This is  an aged, gray-haired rohirrim man. "+
    "His fine clothes tell you that he is probably quite wealthy. " + 
    "In spite of his age, he seems to be quite strong and rather tough. " +
    "His red nose and the considerable girth of his belly betray his " + 
    "love for good food and excellent wine. Right now he seems to be " +
    "very depressed. Perhaps you could ask him if you can 'help' him?"));
  default_config_npc(40+random(20));
  set_base_stat(SS_STR,65);
  set_base_stat(SS_CON,75);
  set_skill(SS_WEP_SWORD, random(10)+50);
  set_skill(SS_DEFENCE, random(10)+50);
  set_skill(SS_PARRY, random(30)+30);
  set_alignment(300+random(100));
  set_act_time(5);
  set_chat_time(5);
  add_act("sigh");
  add_act("present me");
  add_act("stare gloomily");
  add_act("sigh deeply");
  add_chat("Where can I have lost it?");
  add_chat("I looked everywhere at home, I must have lost it somewhere else!");
  add_chat("The finder must return it to me! My name is stamped into it!");
  add_chat("It simply cannot be lost forever!");
  add_chat("It has been in the family since before the time of Eorl the Young!");
  add_cchat("Get out of here, you thieving scoundrel!");
  add_cchat("You won't get away with this, you know!");
  add_cchat("Guards! Help!");
  add_ask(({"do you need help?","help"}),VBFC_ME("inform"));
  add_ask("ring",VBFC_ME("tell_ring"));
  seq_new("do_things");
  seq_addfirst("do_things",({"present me",
  	"say Did you find a golden ring somewhere in Edoras?", }));
  add_prop(NPC_M_NO_ACCEPT_GIVE,0);

  set_equipment( ({
    (EDORAS_DIR + "obj/broadsword"), 
    (EDORAS_DIR + "obj/robe"), 
    (EDORAS_DIR + "obj/home_key"), }) );
}


public varargs void
arm_me()
{
    ::arm_me();
    MONEY_MAKE_CC(10 + random(50))->move(TO);
    MONEY_MAKE_SC(     random(20))->move(TO);
    MONEY_MAKE_GC( 5 + random( 5))->move(TO);
}

void
attacked_by(object ob)
{
  ::attacked_by(ob);
  command("wield sword");
  command("say You fool! Why did you attack me?");
  command("shout Help! Rohirrim, help me against this " + ob->query_race_name() + "!");
}

string
inform()
{
    string who = TP->query_real_name();

    if (inform_alarm && sizeof(get_alarm(inform_alarm)))
        return "";
  if (TP->test_bit("Gondor",GONDOR_GROUP,EDORAS_RING_BIT))
  {
    command("say I don't think that you can help me!");
    return "";
  }
  if (TP->query_prop(GOT_DRINK_FROM_FUNOHED))
  {
    command("say Well, if you can help me, I'll be very grateful!");
    return "";
  }
  command("introduce myself to "+who);
  command("sigh");
  command("say Well, if you want, you might try to help me.");
  command("say But I doubt that you will succeed, it is probably impossible!");
  command("buy whiskey");
  command("sigh deeply");
  command("say Cheers! Have a drink on me!");
  command("give whiskey to " + who);
  command("buy whiskey");
  command("drink whiskey");
  TP->add_prop(GOT_DRINK_FROM_FUNOHED,1);
  START_QUEST(TP, "EDORAS RING-QUEST");
  inform_alarm = set_alarm(20.0, 0.0, &inform2(who));
  return "";
}

void
inform2(string who)
{
    if (inform_alarm && sizeof(get_alarm(inform_alarm)))
        return;
  command("say Yesterday, I lost a ring, an ancient family heirloom.");
  command("say I have already looked everywhere, but it's hopeless!");
  command("sigh deeply");
  command("say Probably someone found it and doesn't think of returning it!");
  command("cry");
  command("say I had dinner here in the Sleeping Stallion. ");
  command("say Later I went on a walk in the gardens at the foot of the hill.");
  command("say When I retired that evening, I noticed that I had lost the ring!");
    inform_alarm = set_alarm(60.0, 0.0, &inform3(who));
  return;
}

void
inform3(string who)
{
    inform_alarm = 0;
  command("buy whiskey");
  command("drink all");
  command("say Well, I think I'll drown myself in whiskey!");
  command("say Drinking water brings bad luck!");
  command("say Look at me, yesterday I drank water from the well ... ");
  command("say ... because I was so thirsty, and the same night I lost my ring!");
  command("sigh");
  return;
}

string
tell_ring()
{
  if (TP->test_bit("Gondor",GONDOR_GROUP,EDORAS_RING_BIT))
  {
    command("say What do you care about my ring?");
    command("peer at " + TP->query_name() );
    return"";
  }
  command("sigh");
  command("say The ring?");
  command("say It's been in my family since before the times of Eorl the Young! ");
  command("say When I inherited it from my father, I had my name stamped onto it.");
  command("say So it's easy to recognize it!");
  command("say It's a golden ring, with fine leaves carved into it!");
  command("say To me it's invaluable!");
  return"";
}
  
void
enter_inv(object obj, object from)
{
  string  obj_name = OB_NAME(obj);

  ::enter_inv(obj, from);  

  if (!objectp(from) || !objectp(obj))
    return;

  command("examine " + obj_name);
  if (obj->query_prop("_ring_from_edoras_well") && from->query_prop("_found_ring_in_edoras_well"))
  {
      set_alarm(2.0, 0.0, &quest_done(from));
      return;
  }
  if (obj->query_prop("_ring_from_edoras_well") && !from->query_prop("_found_ring_in_edoras_well"))
  {
      set_alarm(2.0, 0.0, &not_finder(from));
      return;
  }
  if (!obj->query_prop("_ring_from_edoras_well"))
  {
      set_alarm(2.0, 0.0, &not_ring(obj_name, obj->query_names(), from));
      return;
  }
}

void
leave_home()
{
    command("open door");
    command("west");
    command("south");
    command("southwest");
    command("unlock door with key");
    command("open door");
    command("south");
    command("close door");
    command("lock door with key");
    jump_alarm = set_alarm(600.0, 0.0, go_inn);
}  

void
do_thank(object player)
{
  string plname;
  plname = player->query_real_name();
  set_act_time(1);
  LOG_QUEST(player, 0, "EDORAS RING - ONCE MORE");
  seq_clear("do_things");
  command("say Ah!");
  seq_addfirst("do_things",({"smile at "+plname,"say My ring!",
     "say You found it again? Very strange!", "peer at " + plname, 
     "say Well, I guess I have to be grateful, but it sure is strange!",
  	 "think","say Well, thanks, and goodbye!","@@leave_home@@"}));
  player->remove_prop("_found_ring_in_edoras_well");
}

void
do_add_exp(object player)
{
  string plname;
  seteuid(getuid(TO));
  player->set_bit(GONDOR_GROUP,EDORAS_RING_BIT);
  plname = player->query_real_name();
  player->add_exp_quest(EDORAS_RING_EXP);
  LOG_QUEST(player, EDORAS_RING_EXP, "EDORAS RING-QUEST");
  tell_object(player,"You feel more experienced.\n");
  player->remove_prop("_found_ring_in_edoras_well");
  command("smile "+plname);
  command("say My ring!");
  command("say You found my ring! This is fantastic!");
  command("hug " + plname);
  command("say I'll be forever grateful for this!");
  command("thank " + plname);
  command("say You will always be welcome in Edoras!");
  MONEY_MAKE_GC(12)->move(TO, 1);
  command("buy whiskey");
  command("give whiskey to " + plname);
  command("buy whiskey");
  command("buy stag steak");
  command("give steak to " + plname);
  command("say Let me buy you a meal, that's the least I can do!");
  command("smile");
  command("say And please accept these coins!");
  command("give 5 gold coins to " + plname);
}

void
do_reward(object player)
{
  string plname;
  plname = player->query_real_name();
  set_act_time(1);
  seq_clear("do_things");
  do_add_exp(player);
  command("wave");
  leave_home();
}

void
quest_done(object player)
{
  if(player->test_bit("Gondor",GONDOR_GROUP,EDORAS_RING_BIT))
    do_thank(player);
  else
    do_reward(player);        
}  

void
do_thank_sus(object player)
{
  string plname;
  plname = player->query_real_name();
  set_act_time(1);
  LOG_QUEST(player, 0, "EDORAS RING-QUEST cheated");
  seq_clear("do_things");
  command("say Ah!");
  seq_addfirst("do_things",({"say My ring!", "peer at " + plname, 
     "say Where did you get this ring?", "say I have been looking for it all over Edoras!",
     "say Don't tell me that you found it, I know that that is not true!",
     "glare at " + plname,"say I think you should leave Edoras now! Good day!",
     "say And remember, we don't like strangers here in Rohan!", "@@leave_home"}));
}

int
not_finder(object player)
{
  do_thank_sus(player);
  return 1;
}

void
not_ring(string obj_name, string *names, object tp)
{
    string  s1;

    if (member_array("coin", names) >= 0)
    {
        command("say Why, thank you, my dear " + tp->query_race_name() + "!");
        command("bow " + tp->query_real_name());
        command("chuckle");
        return;
    }
    command("sigh");
    command("say What shall I do with this " + names[0] + "?");
    command("say I don't need it!");
    command("drop " + obj_name);
}

void
go_inn()
{
    command("unlock door with key");
    command("open door");
    command("north");
    command("close door");
    command("lock door with key");
    command("northeast");
    command("north");
    command("open door");
    command("east");

    if (MASTER_OB(ENV(TO)) != STALLION_FILE)
        jump_alarm = set_alarm(5.0, 0.0, jump_home);
}  

void
jump_home()
{
    command("sigh");
    move_living("north", EDORAS_DIR + "rooms/funohedhome");
    if (!jump_alarm || !sizeof(get_alarm(jump_alarm)))
        jump_alarm = set_alarm(600.0 + 600.0 * rnd(), 0.0, go_inn);
}

/* solemnian prestige */
int
query_knight_prestige() {return (-7);}

void
return_introduce(object pl)
{
    if ((!objectp(pl)) || (objectp(query_attack())) || !present(pl, ENV(TO)))
        return;

    command("introduce me to "+pl->query_real_name());
    return;
}

void
add_introduced(string who)
{
    object  pl = find_player(LOW(who));

    if ((!objectp(pl)) || (objectp(query_attack())) || !present(pl, ENV(TO)))
        return;

    set_alarm(3.0, 0.0, &return_introduce(pl));
    return;
}

