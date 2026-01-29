/*
 * Dungeon Thief
 *
 * This is the thief that used to have his hideout in
 * the small cave within the tunnel that goes from the
 * sewers to the well in the garden of Kalaman.
 *
 * Quest NPC
 * This man/thief will ask the player for a locket that
 * he hid ages ago in his old hideout, just before being
 * captured by the elite guards of Kalaman.
 * He now wants that locket back.
 * Upon receiving the locket from the player, the player 
 * will be given the key to the cells in the western
 * part of the dungeon.
 *
 * 2008-02-19 : Lunatari
 * Added the item code for receiving the silver locket.
 * 2008-02-21 : Lunatari
 * Added food and locket checks.
 * 2011-06-02 : Lunatari
 * Modified the hunger and locket says + code.
 * 2011-09-28 : Lunatari
 * Coded changed according to Navarre's wishes in the
 * first review made.
 */
#include "local.h"

inherit AM_FILE

#define THIEF_LOCKET_XP 5000
#define SHIRT DOBJ + "rags_shirt"
#define PANTS DOBJ + "rags_pants"
#define MAP   DOBJ + "thief_map"

string get_long_desc();
string get_ask_food();
string get_ask_locket();
string get_ask_help();
string get_ask_key();
string get_ask_map();

int gFood, gLocket;

void
create_krynn_monster()
{
    set_name("dravel");
    add_name("man");
    set_title("the Collector of Items");
    set_race_name("human");
    set_adj(({"tired","old"}));
    set_short("tired old man");
    set_long(get_long_desc);

    set_stats(({45, 45, 45, 45, 45}));
    set_hp(query_max_hp());

    set_alignment(0);
    set_knight_prestige(-3);

    add_prop(CONT_I_WEIGHT, 35000);
    add_prop(CONT_I_HEIGHT, 170);

    set_act_time(2);
    add_act("moan");
    add_act("shiver");
    add_act("whispers: I miss her so much, so much.");
    add_act("sob silent");
    add_act("grin badly");
    add_act("sigh");
    add_act("cough");
    add_act("choke");
    add_act("mumble: Oh if I could just have one last look at her " +
      "before I leave this wretched world.");
    add_act("mumbles: I am so hungry!");
    add_act("winches");

    add_ask("locket", get_ask_locket, 1);
    add_ask(({"food", "hungry"}), get_ask_food, 1);
    add_ask(({"quest","task","help"}), get_ask_help, 1);
    add_ask("key", get_ask_key, 1);
    add_ask("map", get_ask_map, 1);
    add_ask("her", "say Her? Oh you heard my rambling, I wish to " +
       "see my sweet love again, my beloved wife, it has been so " +
       "long since last.", 1);
    add_ask(({"love", "wife", "beloved"}), "say Oh yes, I had a " +
       "family once, long ago, all I have left now is a locket that " +
       "keeps a small magical image of my beloved wife inside.", 1);
    add_ask("guards", "say Oh those damn guards, the elite of " +
       "Kalaman they sent for me, those cowards, fifteen of them " +
       "came and wrestled me down in my own hideout.", 1);
    add_ask("hideout", "say Yes my old hideout, It is a little " +
       "room hidden beneath Kalaman. I cannot figure out how " +
       "the guards could find the entrance though.", 1);
    add_ask("entrance", "say Well, I guess there is no point in " +
       "keeping it a secret for you, the guards already know " +
       "about it anyway. One entrance is from the surface of " +
       "Kalaman and the other is hidden in the sewers underneath " +
       "the city.", 1); 

    remove_prop(NPC_M_NO_ACCEPT_GIVE);
    add_prop(LIVE_I_NEVERKNOWN, 1);

    seteuid(getuid());
    equip(({ SHIRT, PANTS }));
}

string
get_long_desc()
{
   string text, hunger;

   if (gFood)
   {
     text = "He looks back at you with sparkling but tired eyes.";
     hunger = "but he seems not suffer from hunger. ";
   }
   else
   {
     text = "He stares back at you with tired and hungry eyes.";
     hunger = "and must not have eaten for a quite some time " +
       "since his while ribcage can be seen through his skin. ";
   }

   return "He looks extremely worn down " + hunger +
    "His arms and legs look so thin and fragile that the slightest " +
    "pressure would cause them to snap and break. He is constantly " +
    "shivering and seems to be quite sick, almost deathly sick. " + 
    text + "\n";
}

string
get_ask_food()
{
  if (!gFood)
  {
    return "say I have not eaten in days. You would not " +
      "happen to have some with you?";
  }

  return "say I have just eaten some food, thanks for asking " +
    "me though, very kind of you!";
}

string
get_ask_locket()
{
  if (!gFood) 
  {
    return "say Oh I am so hungry, I am so hungry, this hunger is killing me!";
  }

  if (gLocket)
  {
    return "say Oh I have my locket now, the picture of my love " +
      "still remains as lovely as when I first got it from her!";
  } 

 return "say Oh my precious locket, I have a magical locket that holds " +
   "and image of my love, I have hidden it in my old hideout, would you " +
   "mind finding it for me? I have a map to help you if interested.";
}

string
get_ask_help()
{
  if (!gFood)
  {
    return "say I am hungry, could you please stop talking " +
     "and just fetch me some food.";
  }

  if (TP->test_bit("ansalon", 0, 19))
  {
     return "say I am still grateful for all your help " +
       "and I am not needing anything else, my life can " +
       "end now since I have gotten my locket back!";
  }

  return "say Hmm help me, you asking for a task? Ah well " +
    "could use your help if you are up for it, I have a " +
    "hideout and in that hideout I have stashed a locket " +
    "this locket is special to me and I would want it " +
    "back before my life spirit slips away. Please bring " +
    "it to me.";
}

string
get_ask_key()
{
  if (!gFood) 
  {
    return "say I am just so hungry! Please give me some food!";
  }
  
  if ( TP->test_bit("ansalon", 0, 19) )
  {
     TO->command("say Yes, You have helped me before " +
       "so I will help you again, here is another key " +
       "I managed to slip out of the guards pocket when " +
       "they brought me food.");
     clone_object(DOBJ + "dungeon_key2")->move(TP, 1);
     return "say Once again, Thank you for all the help.";
  }

  return "say Key? You want what key? Perhaps I could help " +
    "if you help me first.";
}

string
get_ask_map()
{
  if (!gFood)
  {
    return "say Oh this hunger! So much pain!";
  }

  TP->catch_msg(QCTNAME(TO) + " gives you a furled map.\n");
  tell_room(ENV(TP), QCTNAME(TO) + " gives " + QTNAME(TP) +
    " a furled map.\n", TP);

  clone_object(MAP)->move(TP, 1);

  return "say Here you go, My map to my hideout, hope you " +
    "can decode it.";
}

void
return_intro(string who)
{
  who = L(who);

  if (P(who,E(TO)))
  {
    command("say Oh, Hello there!");
    command("introduce myself");
  }
}

void
add_introduced(string who)
{
  set_alarm(2.0, 0.0, &return_intro(who));
}

void
give_it_back(object ob, object from)
{
  string what,
  who;

  what = L(ob->query_short());
  who = from->query_real_name();

  command("emote looks at it, but isn't really " +
    "interested in it.");

  if (!gFood)
  {
    command("mumble something about hunger.");
  }
  else if (!gLocket)
  {
     command("emote whispers: The locket, find it!");
  }
  else
  {
     command("sigh");
  }

  command("drop " + what);
}

void
calculate_experience(object who)
{
  int xp_base = THIEF_LOCKET_XP;

  if (who->test_bit("ansalon", 0, 19))
  {
      who->catch_msg("You don't get a prize for doing this " +
        "quest twice!\n");
      return;
  }

  who->catch_msg("You feel more experienced!\n");
  if (who->query_wiz_level())
  {
      who->catch_msg("xp : " + xp_base + "\n");
  }

  who->add_exp_quest(xp_base, 0);
  who->set_bit(0, 19);

  A_QUEST_LOG("quest","Thief Magical Locket", who, xp_base);
  return;
}

void
return_give_locket(object from)
{
  command("emote eyes begin to water.");
  command("open locket");
  command("emote holds the locket tight against his chest " +
    "and sobs quetly.");
  command("emote sobs: Thank you, thank you, thank you!");
  command("say Here, Take this key, it leads to the cells " +
    "within the west parts of this dungeon, I heard " +
    "someone has been imprisoned wrongly there.");
  TP->catch_msg(QCTNAME(TO)+" swiftly moves his hands over the " +
    "cell wall and suddenly hands you a key.\n");
  tell_room(ENV(TO), QCTNAME(TO) + " moves his hands over  " +
    "the cell wall and suddnely he hands " + QTNAME(TP) +
    " small key.\n", TP);
  clone_object(DOBJ + "dungeon_key2")->move(TP);

  gLocket = 1;
  set_alarm(2.0, 0.0, calculate_experience(from));
}

void
return_give_food(object from)
{
  command("emote eyes sparkle.");
  command("say Oh my! Thank you so much! You cannot believe " +
    "how hungry I am!");
  command("eat food");
  command("burp");
  command("pat belly");

  gFood = 1;
}

void
enter_inv(object ob, object from)
{
  ::enter_inv(ob, from);

  if (ob->id("_kalaman_thief_locket_") && !gLocket && gFood)
  {
    set_alarm(1.0, 0.0, &return_give_locket(from));
    return;
  }

  if (ob->id("food") && !gFood)
  {
    set_alarm(1.0, 0.0, &return_give_food(from));
    return;
  } 

  /* KEEP CLOTHES */
  if (ob->id("_prison_rags_"))
  {
    return;
  }

  set_alarm(1.0, 0.0, &give_it_back(ob, from));
  return;
}
