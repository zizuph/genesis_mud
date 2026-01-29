inherit "/std/monster";
#include "/sys/stdproperties.h"
#include "/d/Gondor/defs.h"
#include "/sys/ss_types.h"
#include "/sys/macros.h"
#include "/d/Gondor/elessar/lib/goodkill.h"

string code_word;

create_monster()
{
  set_name("amaron");
  add_name("man");
  add_name("ranger");
  add_name("dunadan");
  set_living_name("amaron");
  set_title("the Master Ranger of Gondor");
  set_race_name("human");
  set_gender(0);
  set_adj("master");
  set_adj("calm");
  set_short("calm master ranger");
  set_stats(({ 75, 75, 80, 73, 73, 80 }));
  set_hp(7000);
  set_skill(SS_WEP_SWORD,83);
  set_skill(SS_PARRY,70);
  set_skill(SS_DEFENCE,55);
  set_long("@@long_func");
  add_prop(CONT_I_HEIGHT,208);
  add_prop(CONT_I_WEIGHT,95000);
  add_prop(NPC_M_NO_ACCEPT_GIVE,0);
  add_chat("We do need information on the situation in Ithilien.");
  add_chat("I have tasks to do.");
  add_chat("We still haven't heard from Ithilien.");
  add_chat("Armies are mustering in the East.");
  add_chat("I fear that Saruman the White is up to no good.");
  add_ask(({"task","quest","job","tasks","quests","jobs"}),VBFC_ME("give_task"));
  add_ask(({"for ring","ring"}),VBFC_ME("new_ring"));
  add_ask("name",VBFC_ME("introduce"));
  add_ask("gondor",VBFC_ME("inform_gondor"));
  add_ask("ithilien",VBFC_ME("inform_ithilien"));
  add_ask("north",VBFC_ME("inform_north"));
  add_ask("rangers","We Rangers have but one duty: To protect the\n"+
    "Free Peoples from Evil!\n");
  add_ask("duty","The master ranger says: Our Duty is to protect the Free Peoples\n"+
    "from the Evil One!\n");
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

introduce()
{
  command("say My name is Amaron.");
  command("introduce me");
  return "";
}

new_ring()
{
  RANGER_GUILD->ask_for_ring("get ring");
  command("smile");
  return "";
}

give_task()
{
  int q;
  if (!TP->test_bit("Gondor",1,2)) enchant_seed();
  else if (!TP->test_bit("Gondor",1,3)) missing_ranger();
  else {
    command("say I'm sorry - I have no more tasks for you.");
    }
  return "";
}

missing_ranger()
{
  command("say As soon as we heard of the large army camped in Ithilien,");
  command("say we sent a ranger to scout the area further.");
  command("say He hasn't returned. I want you to find out what has");
  command("say happened to him. If he is alive - bring him back");
  command("say to me. If not - bring proof of his demise.");
}

enchant_seed()
{
  command("say An old ranger is living in a hut somewhere in this");
  command("say forest - he is our main supply of herbs. I've had");
  command("say word with him, and he said he needed help.");
  command("say Go and seek him out east from the end of the old");
  command("say forgotten road in the forest.");
}

inform_gondor()
{
  command("say Gondor is a beautiful land. Our main problem is");
  command("say the Enemy in the East. How can anyone live peacefully");
  command("say when large armies are mustering to attack us?");
  command("sigh");
  return "";
}

inform_ithilien()
{
  command("say Ithilien is even fairer than Gondor, some say.");
  command("say I haven't seen it myself, but when I do, I hope it is");
  command("say once again a free land, and not corrupted by the orcs");
  command("say from Mordor.");
  command("spit");
  return "";
}

inform_north()
{
  command("say In the North was Arnor, the sister-kingdom of Gondor.");
  command("say It was a large and beautiful kingdom. But the damned");
  command("say Witch-king of Angmar attacked, and after a long war");
  command("say destroyed the kingdom totally. What's left there now");
  command("say is an empty land, and a few small villages. Halflings");
  command("say live there, and Rangers protect them from the world.");
  command("smile");
  return "";
}

inform_orc_camp()
{
  command("frown");
  command("say The orc-camp is large. The orcs camped there are fierce");
  command("say orcs of the Red Eye army of Mordor, and they have");
  command("say been joined by an army of Haradrim soldiers.");
  command("say The dark-skinned Haradrim are even fiercer fighters");
  command("say than the Orcs of the Red Eye. Be careful there.");
}

enter_inv(object ob, object from)
{
  ::enter_inv(ob,from);
  if (!from) return;
  if (present("Ranger_Quest_Ring",TO)) test_quest_done(ob);
}

test_quest_done(object ob)
{
  if (present("Ranger_Quest_Ring",TO)==ob) quest_done(1,TP);
}

quest_done(no, pl)
{
  if (no > 1) return 0;
  if (no < 0) return 0;
  if (!pl) return 0;
  if (pl->test_bit("Gondor",1,3)) do_thank(pl);
  else {
    command("say Alas! Leydon's ring! I understand he is not with us");
    command("say anymore then.");
    command("sigh");
    command("say I'm thankful that you found out the truth for us though.");
    command("thank "+pl->query_real_name());
    pl->set_bit(1,3);
    pl->add_exp(3000,0);
    write_file(QUEST_LOG,"LOST_RANGER: Solved by "+pl->query_name()+", on "+ctime(time())+".\n");
    tell_object(pl,"You feel more experienced.\n");
    if (pl->query_prop("_gondor_met_rangers_wife")) {
      command("say Could you perhaps go to Minas Tirith and give the ring");
      command("say to Leydon's widow? She would appreciate it, I know.");
      command("give ring to "+pl->query_real_name());
      command("smile");
      }
    return 1;
    }
}

do_thank(object pl)
{
  command("say Ah, so you've helped us again! Thanks so much, but");
  command("say I can't give you any reward this time.");
  command("smile "+pl->query_real_name());
  return 1;
}

string
long_func()
{
  return break_string("He is a pale-skinned man, dark of hair, with grey eyes, and a proud face. You realize that he must be one of the Dunedain of the South, a man of the line of the Lords of Westernesse. \n",70);
}
