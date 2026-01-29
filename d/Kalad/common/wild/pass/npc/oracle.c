/*
 * /d/Kalad/common/wild/pass/npc/oracle.c
 * Purpose    : The oracle for the oracle quest
 * Located    : /d/kalad/common/wild/pass/desert/mount/p3
 * Created By : Antharanos ??.??.??
 * Polished by Ibun 2007-05-11
 */
#pragma strict_types
#include "/d/Kalad/defs.h"
inherit "/d/Kalad/std/monster";
#define CAN_DO_ORACLE_QUEST "_can_do_oracle_quest"

void
create_monster()
{
   ::create_monster();
   set_name("abdell");
   add_name("oracle");
   set_race_name("avatar");
   set_adj("wise");
   set_long("A humble and well-dressed man of indeterminate age stands "+
      "before you. He is dressed in a simple white robe, complete with a "+
      "hood, which is currently over his head. A beardless and wrinkle-free "+
      "face gazes out at you from beneath his hood. Nothing seems overly "+
      "outstanding or amazing about him, save for one feature, his eyes. "+
      "One look at those depthless eyes and you realize the magnitude of "+
      "his wisdom, boundless.\n");
   set_stats(({100,100,100,200,200,100}));
   set_alignment(1200);
   set_knight_prestige(-10);
   set_skill(SS_DEFENCE,100);
   set_skill(SS_AWARENESS,100);
   add_prop(OBJ_I_INVIS,100);
   add_prop(LIVE_I_SEE_INVIS,100);
   add_prop(LIVE_I_SEE_DARK,100);
   add_prop(NPC_I_NO_RUN_AWAY,1);
   add_prop(OBJ_M_NO_ATTACK,1);
   add_prop(OBJ_I_RES_MAGIC,100);
   set_title("the Oracle of the Desertrise mountains");
   set_default_answer("Alas, even oracles do not know everything.\n");
   add_ask(({"disappearances","disappearance"}),"@@return_question");
   add_ask(({"bedellin","nomads","nomad"}),
      "They are a group of humans that have learned to live " +
      "in this land of the ever-burning sun.\n");
   add_ask(({"kaladian sun","sun"}),
      "A might furnace of light and power that sustains all " +
      "life in the land of Kalad, as well as all the world.\n");
   add_ask(({"kalad","land"}),
      "It is the continent upon which this wasteland is located on.\n");
   add_ask(({"wasteland","great kalad waste","great waste",
       "kalad waste","waste"}),
      "A barren and varied desert of massive proportions.\n");
   add_ask("desert", "A place of little or no rain, such as " +
       "the Great Kalad Waste.\n");
   add_ask(({"desertrise mountains","desertrise"}),
      "A seried of mountains located at the heart of the " +
      "Great Kalad Waste.\n");
   add_ask(({"mountains","mountain"}),
      "Great rocky masses that jut forth from the surface of the land.\n");
   add_ask(({"kabal"}),
      "A giant city-state, filled with many decadent humans " +
      "that is located far to the southwest.\n");
   add_ask(({"caravan route","route"}),
      "The trading path that links the city-state of Kabal with the " +
      "Canthyrian Empire.\n");
   add_ask(({"canthyrian empire","empire","canthyr"}),
      "A large, oppressive society ruled by a fanatical emperor bent on "+
      "the conquest of all Kalad.\n");
   add_ask(({"magic"}),
      "It is an integral part of all our lives.\n");
   add_ask(({"death"}),
      "A state of being unlike no other.\n");
   add_ask(({"life"}),
      "A truly fragile existence.\n");
   add_ask(({"undead"}),
      "The animated remains of dead beings.\n");
   add_ask(({"ogres","ogre"}),
      "A foul race of beings noted for their dietary preference " +
      "of human flesh.\n");
   add_ask(({"power"}),
      "Something that all mortals seek, something you are " +
      "attempting to get right now.\n");
}

void
return_sacrifice()
{

    set_alarm(2.0, 0.0, "intro");
    set_alarm(4.0, 0.0, "speech1");
    set_alarm(5.0, 0.0, "speech2");
    set_alarm(6.0, 0.0, "speech3");
    set_alarm(7.0, 0.0, "wait");

}

void
intro()
{
TO->remove_prop(OBJ_I_INVIS);
command("introduce myself");
}


void
speech1()
{
   command("say Welcome to my humble abode, traveller.");
}

void
speech2()
{
   command("say By your very presence here, you have proven yourself "+
      "worthy of my wisdom.\n");
}

void
speech3()
{
   command("say Now, think greatly upon what it is you " +
       "wish to ask me, for my time is a valueable commodity " +
       "in short supply.\n");
}

void
wait()
{
   command("say However, do not wait too long...for I have but precious "+
      "few moments to answer your question.\n");
   set_alarm(60.0, 0.0, "leave");
}

void
leave()
{
   command("say Your time is up, I must depart now.\n");
   command("say Farewell mortal, and may T'har look favorably upon you.\n");
   say(QCTNAME(TO) + " vanishes from sight.\n");
   TO->add_prop(OBJ_I_INVIS,100);
}

void
return_question()
{
   command("say Ahh, yes, you wish to know who is " +
       "causing trouble for the Bedellin. Very " +
       "well, the answer is this: Ogres.\n");
   write("You now know what to tell the " +
          "Sheik of the Iriphawa!\n");
   TP->add_prop(CAN_DO_ORACLE_QUEST,1);


}
void
attacked_by(object ob)
{
   ::attacked_by(ob);
   command("sigh");
   command("say Such is your loss.");
   ob -> move_living("into a dimensional rift",
       "/d/Kalad/common/wild/pass/desert/d1");
   command("stop hunting");
}
