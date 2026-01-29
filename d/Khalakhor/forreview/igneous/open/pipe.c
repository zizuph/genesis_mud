inherit "/std/object";
#include "/d/Shire/common/defs.h"

#define SOULDESC(x)   (TP->add_prop(LIVE_S_SOULEXTRA, x))
#define SMOKING       "_pipe_is_smoking_"

static int    smoke_time;
static int    alarm_id;

void
create_object()
{
   set_name("pipe");
   set_pname("pipes");
   set_short("small wooden pipe");
   set_adj(({"small", "wooden"}));
   set_long("A beautifully hand-carved pipe.  Much skill and " +
      "effort has gone into the making of this smoking pipe, you " +
      "marvel at the craftsmanship.\n" +
      "You notice some directions on the bottom of the pipe.\n");
   
   add_cmd_item("pipe", "tap", "@@do_tap");
   add_cmd_item("pipe", "clean", "@@do_clean");
   add_cmd_item("rings", "make", "@@do_rings");
   add_cmd_item("pipe", "inhale", "@@do_inhale");
   add_cmd_item("pipe", "keep", "@@do_keep");
   add_cmd_item("directions", "read",
      "You can do many things with this pipe.\n" +
      "===========================================================\n" +
      " tap pipe:    For when you're out of pipe-weed.\n" +
      " clean pipe:  For when your pipe gets dirty.\n" +
      " smoke pipe:  To smoke from your pipe.\n" +
      " make rings:  Blow some smoke rings :)\n" +
      " inhale pipe: For when you want to inhale deeply.\n" +
      " keep pipe:   So you can sell or keep your pipe.\n" +
      "===========================================================\n\n");
   add_item("directions", "Why don't you try and read them?\n");
   
   add_prop(OBJ_I_WEIGHT, 25);
   add_prop(OBJ_I_VOLUME, 7);
   add_prop(OBJ_I_VALUE, 100);
   add_prop(OBJ_M_NO_SELL, 1);
}

string
do_tap()
{
   if (TO->query_prop(SMOKING))
      {
      return("You can't tap your pipe like that while it is lit.\n");
   }
   say(QCTNAME(TP) +
      " taps " + HIS_HER(TP) + " pipe against " + HIS_HER(TP) + " leg. " +
      "You can tell by the expression on " + HIS_HER(TP) + " face that " +
      "" + QCTNAME(TP) + " wishes " + HE_SHE(TP) + " had some " +
      "tobacco to smoke.\n");
   SOULDESC("tapping " + HIS_HER(TP) + " pipe against " + HIS_HER(TP) + " leg");
   return("You tap your pipe against your leg, desperately wishing that " +
      "you had some tobacco to fill it with.\n");
}

string
do_clean()
{  
   if (TO->query_prop(SMOKING))
      {
      return("What?  Trying to clean a lit pipe?\n");
   }
   say(QCTNAME(TP) +
      " cleans out " + HIS_HER(TP) + " pipe with great precision " +
      "and care by tapping it lightly upon the ground.\n");  
   return("You clean out your pipe by tapping it gently on the " +
      "ground. You take great care not to damage your precious pipe.\n");  
}

string
do_rings()
{
   if (TO->query_prop(SMOKING))
      {
      say(QCTNAME(TP) +
         " blows some smoke rings from " + HIS_HER(TP) + " pipe. You " +
         "gaze at the perfect rings as they slowly rise in the air.\n");
      SOULDESC("gazing at " + HIS_HER(TP) + " perfect smoke rings");
      return("You blow some smoke rings from your pipe. You watch in " +
         "delight as they rise up in the air.\n");  
   }
   return("You can't make smoke rings with an unlit pipe!\n");
}

string
do_inhale()
{
   int constat;
   
   constat = TP->query_stat(SS_CON);
   
   if (TO->query_prop(SMOKING))
      {
      if (constat <= 25)
         {
         say(QCTNAME(TP) + " inhales deeply from " + HIS_HER(TP) + " pipe, " +
            "cuasing " + HIS_HER(TP) + " face to turn green.\n");
         TP->command("puke");
         return("What a mess!!  Perhaps you shouldn't inhale so deeply " +
            " until your weak lungs can handle it.\n");
       }
      if (constat <= 50)
         {
         say(QCTNAME(TP) + " inhales deeply from " + HIS_HER(TP) + " pipe, " +
            "causing " + HIS_HER(TP) + " face to turn a little pale.\n");
         TP->command("cough");
         return("Perhaps you shouldn't inhale so deeply?  All that " +
            "coughing is making you look like a fool.  Maybe on day " +
            "you'll be able to inhale deeply and not have a cough spasm.\n");
       }
      say(QCTNAME(TP) +
         " inhales deeply, savouring the wonderful tobacco.\n");
      SOULDESC("inhaling deeply from " + HIS_HER(TP) + " pipe");
      return("You inhale deeply enjoying the wonderful pipe smoke.\n");  
   }
   return("Try to inhale from an unlit pipe?\n");
}

string
do_keep()
{
   if (TO->query_prop(OBJ_M_NO_SELL))
      {
      TO->remove_prop(OBJ_M_NO_SELL);
      return("You will now be able to sell your pipe now.\n");
   }
   TO->add_prop(OBJ_M_NO_SELL, 1);
   return("You will not sell your pipe now.\n");
}

void
init()
{
   ::init();
   add_action("do_smoke", "smoke");
}

int
do_smoke(string str)
{
   if (TO->query_prop(SMOKING))
      {
      write("But your still smoking the last batch!!\n");
      return 1;
   }
   smoke_time = set_alarm(itof(150 + random(60)),0.0,"timeout");
   alarm_id = set_alarm(2.0,itof(10 + random (5)),"puff");
   TO->add_prop(OBJ_M_NO_DROP, 1);
   TO->add_prop(OBJ_M_NO_GIVE, 1);
   TO->add_prop(SMOKING, 1);
   say(QCTNAME(TP) +
      " stuffs some tobacco into " + HIS_HER(TP) + " pipe and then " +
      "proceeds to light it. " + CAP(HE_SHE(TP)) + " inhales deeply and " +
      "smiles happily as " + HE_SHE(TP) + " exhales the wonderful smoke.\n");
   SOULDESC("smoking " + HIS_HER(TP) + " pipe");
   write("You quickly fill your pipe with some available tobacco " +
      "and imediately light it. As you start to inhale the wonderful " +
      "smoke, you smile happily, thoroughly enjoying it.\n");
   return 1;
}

void
timeout()
{
   remove_alarm(smoke_time);
   remove_alarm(alarm_id);
   smoke_time = 0;
   alarm_id = 0;
   TO->remove_prop(OBJ_M_NO_DROP);
   TO->remove_prop(OBJ_M_NO_GIVE);
   TO->remove_prop(SMOKING);
   write("Your pipe has run out of tobacco!\n");
   say(QCTNAME(TP) + " ceases to smoke " + HIS_HER(TP) + " pipe.\n");
   return;
}

void
puff()
{
   write("You take a puff from your pipe.\n");
   say(QCTNAME(TP) + " takes a puff from " + HIS_HER(TP) + " pipe.\n");
   return;
}
