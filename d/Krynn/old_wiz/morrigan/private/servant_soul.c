inherit "/cmd/std/command_driver";

#include "/d/Krynn/common/defs.h"
#include <macros.h>
#include <formulas.h>

string get_soul_id() { return "servant soul"; }

int query_cmd_soul() { return 1; }

mapping
query_cmdlist()
{
   return ([ "e1" : "e1" , "e2" : "e2" , "e3" : "e3" , "e4" : "e4" ,
         "e5" : "e5" , "e6" : "e6" , "e7" : "e7" , "e8" : "e8",
         "e9" : "e9" , "e10" : "e10" , "e11" : "e11" , "e12" : "e12" ,
         "e13" : "e13" ]);
}

int
e1(string str)
{
   object *oblist;
   string mis = (TP->query_mistress()->query_gender() == 1 ? "Mistress" : "Master");
   string name = (TP->query_mistress()->query_real_name());
   string pos = POSSESSIVE(TP);
   
   NF("What ?\n");
   if (!str)
      return 0;
   
   oblist = parse_this(str, "%l");
   oblist -= ({ TP });
   
   if (!sizeof(oblist))
      return 0;
   
   actor("You stare deep into",oblist,"'s eyes and whisper softly: You are "+
      "so beautiful "+mis+", to simply gaze upon you is all I desire.");
   target(" stares deep into your eyes, whispering softly: You are so beautiful "+
      mis+", to simply gaze upon you is all I desire.", oblist);
   all2act(" stares deep into", oblist, "'s eyes, whispering softly: You are so "+
      "beautiful "+mis+", to simply gaze upon you is all I desire.");
   return 1;
}

int
e2(string str)
{
   object *oblist;
   string mis = (TP->query_mistress()->query_gender() == 1 ? "Mistress" : "Master");
   string name = (TP->query_mistress()->query_real_name());
   string pos = POSSESSIVE(TP);
   
   NF("What ?\n");
   if (!str)
      return 0;
   
   oblist = parse_this(str, "%l");
   oblist -= ({ TP });
   
   if (!sizeof(oblist))
      return 0;
   
   actor("You begin to massage",oblist,"'s neck and shoulders and breath: Your "+
      "skin is as soft as the lightest down, and smells far sweeter than any "+
      "rose. Oh, how I long to touch it always.");
   target(" begins to massage your neck and shoulders with "+POSSESSIVE(TP)+
      (TP->query_gender() == 0 ? " strong but gentle" : " delicate and loving")+
      " hands and says: Your skin is as soft as the lightest down, and smells far "+
      "sweeter than any rose. Oh, how I long to touch it always.", oblist);
   all2act(" begins to massage", oblist, "'s neck and shoulders with "+POSSESSIVE(TP)+
      (TP->query_gender() == 0 ? " strong but gentle" : " delicate and loving")+
      " hands and says: Your skin is as soft as the lightest down, and smells far "+
      "sweeter than any rose. Oh, how I long to touch it always.");
   return 1;
}


int
e3(string str)
{
   object *oblist;
   string mis = (TP->query_mistress()->query_gender() == 1 ? "Mistress" : "Master");
   string name = (TP->query_mistress()->query_real_name());
   string pos = POSSESSIVE(TP);
   string text = "Oh "+mis+", your hair is so majestic that I only wish to curl up "+
   "in it and sleep forever.";
   
   NF("What ?\n");
   if (!str)
      return 0;
   
   oblist = parse_this(str, "%l");
   oblist -= ({ TP });
   
   if (!sizeof(oblist))
      return 0;
   
   actor("You run your fingers through", oblist, "'s soft hair, cooing in her ear: "+
      text);
   target(" runs "+pos+" fingers through your hair, cooing in your ear: "+text, oblist);
   all2act(" runs "+pos+" fingers through",oblist, "'s hair, cooing in "+pos+" "+mis+
      "'s ear: "+text);
   return 1;
}


int
e4(string str)
{
   object *oblist;
   string mis = (TP->query_mistress()->query_gender() == 1 ? "Mistress" : "Master");
   string name = (TP->query_mistress()->query_real_name());
   string pos = POSSESSIVE(TP);
   string text = "Those lips so delicate, so lush; their pleasant taste lingers "+
   "ever on my own, reminding me that all other flavours pale in comparison to "+
   "that of my "+mis+".";
   
   NF("What ?\n");
   if (!str)
      return 0;
   
   oblist = parse_this(str, "%l");
   oblist -= ({ TP });
   
   if (!sizeof(oblist))
      return 0;
   
   actor("You brush your lips gently against",oblist,"'s whispering: "+text);
   target(" brushes "+pos+" lips gently against yours, whispering: "+text, oblist);
   all2act(" brushes "+pos+" lips gently against", oblist, "'s, whispering: "+
      text);
   return 1;
}

int
e5(string str)
{
   object *oblist;
   string mis = (TP->query_mistress()->query_gender() == 1 ? "Mistress" : "Master");
   string name = (TP->query_mistress()->query_real_name());
   string pos = POSSESSIVE(TP);
   string text = "My tongue longs to work its magic on you, "+mis+". Pray "+
   "be merciful and let it, I beg of you.";
   
   NF("What ?\n");
   if (!str)
      return 0;
   
   oblist = parse_this(str, "%l");
   oblist -= ({ TP });
   
   if (!sizeof(oblist))
      return 0;
   
   actor("You nibble and kiss along", oblist, "'s ears and neck, pleading: "+text);
   target(" nibbles and kisses along your ears and necks, pleading: "+text, oblist);
   all2act(" nibbles and kisses along", oblist,"'s ears and neck, pleading: "+text);
   return 1;
}

int
e6(string str)
{
   object *oblist;
   string mis = (TP->query_mistress()->query_gender() == 1 ? "Mistress" : "Master");
   string name = (TP->query_mistress()->query_real_name());
   string pos = POSSESSIVE(TP);
   string text = "There is no greater joy to be found, than that which I find in "+
   "your arms, my "+mis+".";
   
   NF("What ?\n");
   if (!str)
      return 0;
   
   oblist = parse_this(str, "%l");
   oblist -= ({ TP });
   
   if (!sizeof(oblist))
      return 0;
   
   actor("You wrap", oblist, " in your arms and say: "+text);
   target(" wraps you in "+pos+" arms and says: "+text, oblist);
   all2act(" wraps", oblist, " in "+pos+" arms and says: "+text);
   return 1;
}

int
e7(string str)
{
   object *oblist;
   string mis = (TP->query_mistress()->query_gender() == 1 ? "Mistress" : "Master");
   string name = (TP->query_mistress()->query_real_name());
   string pos = POSSESSIVE(TP);
   string text = "Mmmm, if only we had some privacy, "+mis+", I would promise to "+
   "take VERY good care of you...";
   
   NF("What ?\n");
   if (!str)
      return 0;
   
   oblist = parse_this(str, "%l");
   oblist -= ({ TP });
   
   if (!sizeof(oblist))
      return 0;
   
   actor("You lick", oblist, "'s neck slowly, promising: "+text);
   target(" licks your neck slowly, promising: "+text, oblist);
   all2act(" licks", oblist, "'s neck slowly, promising: "+text);
   return 1;
}

int
e8(string str)
{
   object *oblist;
   string mis = (TP->query_mistress()->query_gender() == 1 ? "Mistress" : "Master");
   string name = (TP->query_mistress()->query_real_name());
   string pos = POSSESSIVE(TP);
   string text = "I can't help touching myself as I think of you, "+mis+".";
   
   NF("What ?\n");
   if (!str)
      return 0;
   
   oblist = parse_this(str, "%l");
   oblist -= ({ TP });
   
   if (!sizeof(oblist))
      return 0;
   
   actor("You run your hands along your chest and whisper in", oblist, "'s ear: "+
      text);
   target(" runs "+pos+" fingers along "+pos+" chest and whispers to you: "+text,
      oblist);
   all2act(" runs "+pos+" fingers along "+pos+" chest and whispers something in ",
      oblist,"'s ear, who blushes slightly.");
   return 1;
}

int
e9(string str)
{
   object *oblist;
   string mis = (TP->query_mistress()->query_gender() == 1 ? "Mistress" : "Master");
   string name = (TP->query_mistress()->query_real_name());
   string pos = POSSESSIVE(TP);
   string text = "Oh, such a perfect bum, no?";
   string pos2;
   
   NF("What ?\n");
   if (!str)
      return 0;
   
   oblist = parse_this(str, "%l");
   oblist -= ({ TP });
   
   if (!sizeof(oblist))
      return 0;
   if (sizeof(oblist) > 1)
      pos2 = "their";
   else
      pos2 = oblist[0]->query_possessive();
   
   
   actor("You snuggle up to", oblist," and squeeze "+pos2+" bum delightfully, saying "+
      text);
   target(" snuggles up to you and squeezes your bum delightfully, saying: "+text,
      oblist);
   all2act(" snuggles up to", oblist, " and squeezes "+pos2+" bum delightfully, "+
      "saying: "+text);
   return 1;
}

int
e10(string str)
{
   object *oblist;
   string mis = (TP->query_mistress()->query_gender() == 1 ? "Mistress" : "Master");
   string name = (TP->query_mistress()->query_real_name());
   string pos = POSSESSIVE(TP);
   string text = "Later this evening, "+mis+", these hands will bring you "+
   "unimagineable pleasure.";
   
   NF("What ?\n");
   if (!str)
      return 0;
   
   oblist = parse_this(str, "%l");
   oblist -= ({ TP });
   
   if (!sizeof(oblist))
      return 0;
   
   actor("You begin to caress", oblist, " slowly, whispering in a sultry voice: "+
      text);
   target(" begins to caress you slowly, whispering in a sultry voice: "+text,
      oblist);
   all2act(" begins to caress", oblist, " slowly, whispering in a sultry voice: "+
      text);
   return 1;
}

int
e11(string str)
{
   object *oblist;
   string mis = (TP->query_mistress()->query_gender() == 1 ? "Mistress" : "Master");
   string name = (TP->query_mistress()->query_real_name());
   string pos = POSSESSIVE(TP);
   string text = "Oooh! Happy to see me, are you?";
   
   NF("What ?\n");
   if (!str)
      return 0;
   
   oblist = parse_this(str, "%l");
   oblist -= ({ TP });
   
   if (!sizeof(oblist))
      return 0;
   
   actor("Looking around to make sure that no one is looking, your hand slowly "+
      "slides down", oblist, "'s body, and shocked at what you find, you exclaim: "+
      text);
   target(" looks around to make sure that no one is looking, and "+pos+" hand "+
      "slowly slides down your body, and "+TP->query_pronoun()+" says in mock"+
      " surprise: "+text, oblist);
   all2act(" looks around cautiously, and you notice "+pos+" hand slowly sliding "+
      "down", oblist, "'s body, and suddenly exclaims: "+text);
   return 1;
}

int
e12(string str)
{
   object *oblist;
   string mis = (TP->query_mistress()->query_gender() == 1 ? "Mistress" : "Master");
   string name = (TP->query_mistress()->query_real_name());
   string pos = POSSESSIVE(TP);
   string text = "";
   
   NF("What ?\n");
   if (!str)
      return 0;
   
   oblist = parse_this(str, "%l");
   oblist -= ({ TP });
   
   if (!sizeof(oblist))
      return 0;
   
   actor("You press your body against", oblist, "'s letting your "+mis+" know "+
      "how much you want them.");
   target(" presses "+pos+" body against yours sensually, making "+pos+" lust "+
      "for you quite obvious.", oblist);
   all2act(" presses "+pos+" body against", oblist, "'s body sensually, making "+
      pos+" lust quite obvious.");
   return 1;
}

int
e13(string str)
{
   object *oblist;
   string mis = (TP->query_mistress()->query_gender() == 1 ? "Mistress" : "Master");
   string name = (TP->query_mistress()->query_real_name());
   string pos = POSSESSIVE(TP);
   string pos2;
   string text = "";
   
   NF("What ?\n");
   if (!str)
      return 0;
   
   oblist = parse_this(str, "%l");
   oblist -= ({ TP });
   
   if (!sizeof(oblist))
      return 0;
   
   if (sizeof(oblist) > 1)
      pos2 = "them";
   else
      pos2 = oblist[0]->query_pronoun();
   
   
   actor("You begin to kiss your way down", oblist, "'s neck, chest, stomach...");
   target(" begins to kiss "+pos+" way down your neck, chest, stomach... \n"+
      "Remembering you are in public, you deftly pull away from "+pos+" grasp.",
      oblist);
   all2act(" begins to kiss "+pos+" way down", oblist, "'s neck, chest, stomach...\n"+
      "but is suddenly forced to let go, as "+pos2+" seemingly remembers where "+
      pos2+" and pulls away from "+pos+" grasp.");
   return 1;
}
