inherit "/std/monster";
#include "/sys/stdproperties.h"
#include "/sys/ss_types.h"
#include "/sys/macros.h"
#include "/d/Gondor/elessar/lib/goodkill.h"
#define BS(xxx) break_string(xxx,75)

string code_word;
object talked_to;

create_monster()
{
  set_name("ranger");
  add_name("man");
  add_name("strider");
  add_name("dunadan");
  set_race_name("human");
  set_gender(0);
  set_living_name("strider");
  set_short("strange-looking weather-beaten man");
  set_adj("weather-beaten");
  set_adj("strange-looking");
  set_stats(({ 75, 75, 80, 73, 73, 80 }));
  set_hp(7000);
  set_tell_active(1);
  set_skill(SS_WEP_SWORD,83);
  set_skill(SS_PARRY,70);
  set_skill(SS_DEFENCE,55);
  set_long("@@long_func");
  add_prop(CONT_I_HEIGHT,208);
  add_prop(CONT_I_WEIGHT,95000);
  seq_new("do_things");
  seq_addfirst("do_things","@@arm_me");
}

long_func()
{
  if (present("ranger_ring",this_player()))
    return BS("The strange-looking weather-beaten man is sitting in the shadows "+
      "near the wall. You quickly recognize him as one of the Rangers of the "+
      "North, as he is wearing a silver brooch shaped like a rayed star, "+
      "pinning his travel-stained, grey cloak upon his left shoulder.\n");
  return BS("The strange-looking weather-beaten man is sitting in the "+
    "shadows near the wall, listening intently to the talk in the common-room. "+
    "He has a tall tankard of ale in front of him, and is smoking a long-stemmed "+
    "pipe curiously carved. His legs are stretched out before him showing "+
    "muddy and worn leather boots. A travel-stained cloak of heavy dark-green "+
    "cloth is drawn close about him.\n");
}

arm_me()
{
  object wep,arm1,arm2;
  code_word = "perian";
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
  string who, what;
  ::catch_tell(str);
  if (str && sscanf(str,"%s whispers to you: %s\n", who, what) == 2) {
    what = lower_case(what);
    if (what == code_word) {
      command("say Ah....finally, a contact from the south.");
      talked_to = present(lower_case(who),environment());
      if (!talked_to) return 0;
      do_inform(who,"hobbit");
      return 1;
      }
    command("think");
    command("say I'm not sure I know what you mean.....");
    command("shrug");
    return 1;
    }
  else
  if (str && sscanf(str, "%s says: %s", who, what) == 2) {
    what = lower_case(what);
    who = lower_case(who);
    do_inform(who,what);
    return 1;
    }
  return 1;
}

do_inform(string who, string what)
{
  if (what == "hobbit" || what == "hobbits") {
    if (present(lower_case(who),environment()) == talked_to) {
      command("say You must go and see the hobbit Holman Cotton in Hobbiton.");
      command("say You must say 'longshanks' to him.");
      command("smile");
      command("say Then he will know I sent you, and tell you his problem.");
      command("say Go now, and act quickly! May Elbereth be with you!");
      return 1;
      }
    command("say Hobbits? They are a nice little people for sure.");
    command("say Hobbiton is the heart of the Shire, where most hobbits live.");
    command("smile");
    return 1;
  }
  if (what == "ranger" || what == "rangers") {
    command("say Rangers? I don't know anything about them.");
    command("shrug");
    return 1;
  }
  if (what == "gondor") {
    command("sigh");
    command("say Gondor is a fair country far south-east from Bree.");
    return 1;
  }
  if (what == "shire") {
    command("smile");
    command("say But everybody knows that the Shire is the home of hobbits!");
    return 1;
  }
  if (what == "sauron" || what == "evil one") {
    command("stare "+lower_case(who));
    command("say Don't ever mention that name here!");
    command("whisper "+who+" He has spies everywhere!");
    return 1;
  }
  if (what == "rivendell" || what == "imladris") {
    command("shrug");
    command("say "+capitalize(what)+"? What's that?");
    return 1;
  }
  return 1;
}
