/*
 * /d/Kalad/common/wild/pass/npc/bed_loner.c
 * Purpose    : A quest npc for the mara rune quest.
 * Located    : /d/Kalad/common/wild/pass/desert/camp
 * Created By : Antharanos ??.??.??
 * Modified By:
 */
#pragma strict types
inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";
#include "/d/Kalad/defs.h"
#define KILLED_DES_MAR "_killed_des_mar"
#define QUEST_NAME "maraquest"
object bedloner;
void my_stuff();


string
random_extra()
{
   int i;
   i = random(3);
   if(i < 1)
      return "/d/Kalad/common/wild/pass/wep/bed_dag";
   else if (i < 2)
      return "/d/Kalad/common/wild/pass/wep/bed_sword";
   else
      return "/d/Kalad/common/wild/pass/wep/bed_spear";
}

/* This is the npc from which the player may find out about the
maraquest...and is also the npc from which the player is rewarded for
the maraquest. He is located in the grasslands. */
/* by Antharanos */

void
create_monster()
{
   int i;
   set_name("saddam");
   add_name("nomad");
   set_race_name("human");
   set_adj("bedellin");
   set_short("bedellin nomad");
   set_long("A dark-haired and dark-skinned man, his features wrinkled "+
      "from constant exposure to the Kaladian sun and biting winds of the "+
      "desert known as the Great Kalad Waste. His constantly-moving eyes "+
      "indicate someone learned in the ways of the desert.\n");
   for(i = 0; i < 3; i++)
   set_base_stat(i, 60 + random(30));
   set_base_stat(3, 60);
   set_base_stat(4, 60);
   set_base_stat(5, 65);
   set_alignment(600);
   set_knight_prestige(-3);
   set_title("the Nomad");
   set_random_move(10);
   set_skill(SS_WEP_KNIFE,70);
   set_skill(SS_WEP_POLEARM,80);
   set_skill(SS_WEP_SWORD,90);
   set_skill(SS_UNARM_COMBAT,30);
   set_skill(SS_DEFENCE,70);
   set_skill(SS_PARRY,70);
   set_skill(SS_AWARENESS,70);
   set_act_time(6);
   add_act("hmm");
   add_act("say A great dust storm is coming from the north.");
   add_act("emote scans the area, eyes alert to danger.");
   add_act("say It looks like T'har shall feast well tonight.");
   set_cact_time(6);
   add_cact("say Die infidel!");
   add_cact("say May T'har swallow you whole!");
   add_cact("say Esh el-kalam da?!?");
   add_cact("emote grimaces.");
   add_speak("The marauders have spread to many parts of the desert "+
      "waste...Only by using a magical artifact of great power can the "+
      "one and only desert marauder be stopped for the good of all the "+
      "desert dwellers. Might you know of someone willing to " +
      "undertake this task?\n");
   set_default_answer("I do not understand what it is "+
       "you ask of me.\n");
   add_ask(({"marauders","marauder"}),"The marauders of the waste are "+
      "terrible beings that attack all within their sight. They are a blight "+
      "upon the face of Kalad that must be cleansed that all other beings "+
      "may survive. To this end, the great desert marauder must be slain.\n");
   add_ask(({"great desert marauder","great marauder","desert marauder"}),
      "It is the one great marauder from which all others originated. " +
      "To kill it is to end the single source of new marauders. " +
      "If you succeed in your task, return to me and show me " +
      "the power of the object you used to complete this task.\n");
   add_ask(({"magical artifact","artifact","great power","power"}),
      "Rumours abound that an item located somewhere within the " +
      "reaches of the Desertrise mountains is the key to ending " +
      "the marauder threat.\n");
   my_stuff();
}

void
react_rune()
{

    if (TP->test_bit("Kalad", 0, 17))
    {
        command("chortle");
        command("say You have already defeated the marauder!");
        return;
    }

    if(TP->query_prop(KILLED_DES_MAR))
    {
        command("smile relieved");
        command("say Thank you great one! Your actions " +
            "have saved all of the desert waste, if not " +
            "all of Kalad!!");
        TP->catch_msg("You feel the power of T'har infuse your body!\n");
        TP->catch_msg("You feel much more experienced!\n");
        TP->add_exp(15000);
        TP->set_bit(0,17);
        log_file(QUEST_NAME, extract(ctime(time()),4,15)+ " "+
            capitalize(TP->query_real_name()) + " rewarded " +
                "with 15000 xp, "+
               "<"+TP->query_average_stat()+">average stats.\n");
        command("emote bids you farewell, then departs into the " +
            "tall grasses surrounding you.\n");
        object bedloner = present("saddam", environment(TP));
        if (bedloner)
            bedloner->remove_object();
        return;
    }
    return;
}

void
my_stuff()
{
   object item;
   int i;
   string extra;
   extra = random_extra();
   seteuid(getuid(TO));
   item = clone_object(extra);
   item -> move(TO);
   command("wield all");
   item = clone_object("/d/Kalad/common/wild/pass/arm/bed_robe");
   item -> move(TO);
   item = clone_object("/d/Kalad/common/wild/pass/arm/bed_keff");
   item -> move(TO);
   command("wear all");
   MONEY_MAKE_SC(random(20))->move(TO,1);
}


