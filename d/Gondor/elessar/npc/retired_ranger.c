inherit "/std/monster";
#include "/sys/stdproperties.h"
#include "/sys/ss_types.h"
#include "/sys/macros.h"
#include "/d/Gondor/elessar/lib/goodkill.h"
#define BS(xxx) break_string(xxx,75)

string who;

create_monster()
{
  set_name("ranger");
  add_name("man");
  add_name("dunadan");
  set_race_name("human");
  set_gender(0);
  set_short("old retired ranger");
  set_long("This old man looks like he has experienced quite a lot. His face\n"+
    "is wrinkled and weather-beaten, and his hair gray of age. He looks\n"+
    "back at you with a gleam of interest and hope in his eyes.\n");
  set_adj("weather-beaten");
  set_adj("old");
  set_adj("retired");
  set_stats(({ 53, 52, 64, 79, 83, 74 }));
  set_hp(7000);
  set_skill(SS_WEP_SWORD,82);
  set_skill(SS_PARRY,76);
  set_skill(SS_DEFENCE,75);
  add_prop(CONT_I_HEIGHT,204);
  add_prop(CONT_I_WEIGHT,92000);
  set_chat_time(4);
  add_chat("I was once a Ranger, you know. That was some time ago though.");
  add_chat("I was wounded in a fight in Ithilien.");
  add_chat("Those Southrons are Men of bad morals and without honour.");
  seq_new("do_things");
  seq_addfirst("do_things","@@arm_me");
}

arm_me()
{
  object wep,arm1,arm2;
  seteuid(getuid(this_object()));
  wep = clone_object("/d/Gondor/elessar/obj/wep/dlsword");
  wep->move(this_object());
  command("wield longsword");
  arm1 = clone_object("/d/Gondor/elessar/obj/arm/drcloak");
  arm1->move(this_object());
  command("wear cloak");
  arm2 = clone_object("/d/Gondor/elessar/obj/arm/dlboots");
  arm2->move(this_object());
  command("wear boots");
}

catch_tell(string str)
{
  string who, what, dummy;
  if (str && sscanf(str,"%s says: %s\n", who, what) == 2) {
    what = lower_case(what);
    if (sscanf(what,"%s magi%s",dummy,dummy) == 2) {
      command("say Ah - you are interested in magic, are you?");
      command("smile");
      command("say So am I. In fact, I think I can help you, if....");
      command("think");
      call_out("do_inform",6,"magic");
      return 1;
      }
    command("think");
    call_out("do_inform",6,what);
    return 1;
    }
  return 1;
}

do_inform(string what)
{
  if (what == "magic") {
    command("say The magic of the Rangers is not powerful, since there");
    command("say are other qualities about us. However, the magic is");
    command("say helpful - we can heal and rest others with it.");
    command("smile");
    command("say I have a spell-book you can have - but first you must");
    command("say prove yourself by solving this simple task:");
    command("think");
    call_out("do_inform",6,"task");
    return 1;
  }
  if (what == "task") {
    command("say Ah! I am growing herbs for the rangers in my garden.");
    command("say But there is one special herb that refuses to grow.");
    command("say I have just learned that its seeds must be enchanted");
    command("say for the herb to grow successfully. Therefore you must");
    command("say find a way to enchant this seed, so I can plant it.");
    clone_object("/d/Gondor/elessar/quest/enchantseed/normalseed")->move(this_object());
    command("drop seed");
    command("say Oops! I dropped it. Well, be off with you, and good luck!");
    return 1;
    }
  if (what == "ranger" || what == "rangers") {
    command("say Yes, I was once a Ranger of Ithilien.");
    command("say Ithilien became too dangerous for me, so I moved here.");
    command("shrug");
    return 1;
  }
  if (what == "gondor") {
    command("sigh");
    command("say Gondor is the fairest land - second to Ithilien.");
    return 1;
  }
  if (what == "shire") {
    command("smile");
    command("say The Shire, you say? That is a place far up north.");
    command("say The Halflings live there, or hobbits, they call themselves.");
    command("say The Rangers of the North are protecting them in secret.");
    return 1;
  }
  if (what == "sauron" || what == "evil one") {
    command("stare "+lower_case(who));
    command("say Don't ever mention that name!");
    command("whisper "+who+" He has spies everywhere!");
    return 1;
  }
  if (what == "rivendell" || what == "imladris") {
    command("shrug");
    command("say "+capitalize(what)+"? What's that?");
    return 1;
  }
  command("say Hmm. I don't think I quite understand.");
  return 1;
}
