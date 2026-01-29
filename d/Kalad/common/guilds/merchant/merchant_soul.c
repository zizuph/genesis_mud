#pragma strict_types

inherit "/cmd/std/command_driver";

#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/caravan/guild/default.h"
#define HELP_FILE "BLAH"
#define MORE_OBJ "BLAH"

public int query_cmd_soul() { return 1; }
public string get_soul_id() { return "Merchant"; }

public mapping
query_cmdlist()
{
   return ([
#include "mcommands.h"
           ]);
}

public int
e_msmile(string arg)
{
   object *oblist;
   
   NF("Msmile at whom?\n");
   
   if (!strlen(arg))
      {
      allbb(" smiles slickly, as only a merchant could.");
      write("You smile slickly, as only a merchant could.\n");
      return 1;
   }
   
   oblist = parse_this(arg, "[at] / [to] / [toward] [the] %l");
   if (!sizeof(oblist))
      return 0;
   
   actor("You smile at", oblist, " like a slick merchant.");
   all2actbb(" smiles at", oblist, " like a slick merchant.");
   targetbb(" smiles at you like a slick merchant.", oblist);
   return 1;
}

public int
e_mthink(string arg)
{
   NF("Mthink what?\n");
   if (strlen(arg))
      return 0;
   
   allbb(" narrows " + TP->query_possessive() + " eyebrows and thinks "+
      "hard about the joy of accumulating wealth.");
   write("You narrow your eyebrows and think hard about the joy of accumulating wealth.\n");
   return 1;
}

public int
e_mequip(string arg)
{
   NF("Mequip what?\n");
   if (strlen(arg))
      return 0;
   
   all(" thoroughly examines every piece of " + 
      this_player()->query_possessive() + " equipment to prepare for " + 
      this_player()->query_possessive() + " long money-making mission ahead.");
   write("You go over all your equipment in preperation for the long "+
      "money-making mission ahead.\n");
   return 1;
}
public int
e_mprofit(string arg)
{
   NF("Mprofit what?\n");
   if (strlen(arg))
      return 0;
   
   all("'s eyes gain a glittering quality as you realize that " + TP->query_pronoun() + " is thinking of the profit to be made in the world.");
   write("You stare into space, thinking of the profit yet to be made out there.\n");
   return 1;
}

public int
e_mdirt(string arg)
{
   NF("Mdirt what?\n");
   if (strlen(arg))
      return 0;
   
   all(" frantically attempts to clean the dirt off " + TP->query_possessive() + " clothes, so that " + TP->query_pronoun() + " will look presentable as a clean, no-nonsense merchant.\n");
   write("You frantically attempt to clean the dirt off yourself, in an "+
      "attempt to look like a clean, no-nonsense merchant.\n");
   return 1;
}

public int
e_mgreet(string arg)
{
   object *oblist;
   
   NF("Whom did you want to greet?\n");
   if (!strlen(arg))
      return 0;
   
   oblist = parse_this(arg, "[the] %l");
   if (!sizeof(oblist))
      return 0;
   actor("You place your gold chain necklace upon", oblist, "'s brow and "+
      "greet him in the name of the Merchants and Ammercia.");
   all2actbb(" places " + TP->query_possessive() + " gold chain necklace "+
      "upon", oblist, "'s brow in the Merchant's greeting.");
   target(" places " + TP->query_possessive() + " gold chain necklace "+
      "upon your brow and greets you in the name of the Merchants and "+
      "Ammercia.", oblist);
   return 1;
}

public int
e_mdisgust(string arg)
{
   object *oblist;
   
   NF("Show your disgust at whom?\n");
   
   if (!strlen(arg))
      {
      all(" spits on the ground in disgust at the thought of poor people.");
      write("You display your disgust of poor people by spitting on the "+
         "ground.\n");
      return 1;
   }
   
   oblist = parse_this(arg, "[at] / [to] / [toward] [the] %l");
   if (!sizeof(oblist))
      return 0;
   
   actor("You spew a large gob of spit on", oblist, " because of their "+
      "poverty.");
   all2act(" spews a large gob of spit on", oblist, " because of their poverty.");
   target(" spews a large gob of spit directly onto you because you're "+
      "so poor.", oblist);
   return 1;
}

public int
e_mlook(string arg)
{
   object *oblist;
   
   NF("Look at whom?\n");
   
   if (!strlen(arg))
      {
      all(" acquires a greedy look and looks around for perspective customers.");
      write("You put on your best smile and search the area for perspective "+
         "customers.\n");
      return 1;
   }
   
   oblist = parse_this(arg, "[the] %l");
   if (!sizeof(oblist))
      return 0;
   
   actor("You flash your best smile at", oblist, " and attempt to trade something.");
   all2act(" flashes an oily smile at", oblist, " and attempts to trade something.");
   target(" flashes you an oily smile and attempts to trade you something.", oblist);
   return 1;
}

public int
e_mswear(string arg)
{
   object *oblist;
   
   NF("Swear at whom?\n");
   
   if (!strlen(arg))
      {
      all(" swears profusely and curses the day " + TP->query_pronoun() + " was born.");
      write("You swear profusely and curse the day you were born.\n");
      return 1;
   }
   
   oblist = parse_this(arg, "[at] / [to] / [toward] [the] %l");
   if (!sizeof(oblist))
      return 0;
   
   actor("You swear at", oblist, " profusely, cursing the day they were born.");
   all2act(" swears at", oblist, " profusely, cursing the day they were born.");
   target(" swears at you profusely, cursing the day you were born.", oblist);
   return 1;
}

public int
e_mledger(string arg)
{
   object *oblist;
   
   NF("Show your ledger to whom?\n");
   
   if (!strlen(arg))
      {
      all(" brings out an account ledger and starts flipping through the "+
         "pages.");
      write("You bring out your account ledger and start flipping through "+
         "the pages.\n");
      return 1;
   }
   
   oblist = parse_this(arg, "[at] / [to] / [toward] [the] %l");
   if (!sizeof(oblist))
      return 0;
   
   actor("You block", oblist, "'s view with your account ledger.");
   all2act(" waves " + TP->query_possessive() + " account ledger in front of", oblist, "'s face.");
   target(" waves " + TP->query_possessive() + " account ledger in front of "+
      "your face.", oblist);
   return 1;
}

public int
e_mpeer(string arg)
{
   object *oblist;
   
   NF("Mpeer at whom?\n");
   
   if (!strlen(arg))
      {
      all(" peers around the room suspiciously, searching for thieves.");
      write("You peer around the room suspiciously, searching for thieves.");
      return 1;
   }
   
   oblist = parse_this(arg, "[the] %l");
   if (!sizeof(oblist))
      return 0;
   
   actor("You peer at", oblist, " suspiciously, searching for any sign of "+
      "thievery.");
   all2act(" peers at", oblist, " suspiciously, searching for any sign of thievery.");
   target(" watches you suspiciously, as though you were a thief.", oblist);
   return 1;
}

public string
q_title(object ob, int wiz)
{
   if (!ob->query_guild_member("Merchants Guild of Kabal"))
      return 0;
   if (!wiz && ob->query_wiz_level())
      return 0;
   if (wiz && !ob->query_wiz_level())
      return 0;
   if (extract(ob->query_name(), -2) == "jr")
      return 0;
   return implode(explode(break_string(ob->query_presentation(), 76), "\n"),
      "\n    ");
}

public int
e_mlist(string arg)
{
   int i;
   i = (query_verb() == "mwlist" ? 1 : 0);
   write("The following Merchants are currently logged on:\n" +
      implode(map(users() - ({ 0 }), "q_title", this_object(), i) - ({ 0 }),
         "\n") + "\n");
   return 1;
}

int kolla(object ob)
{
   if(!living(ob))
      return 0;
   
   return 1;
}

int
snarl(string someone)
{
   object *a,ob;
   NF("Snarl what?\n");
   if (!someone || someone == "all")   
      if(!sizeof(a))
      write("You snarl: "+someone+"\n");
   say(QCTNAME(TP)+" snarls: "+someone+"\n");
   return 1;
}

public int
e_msay(string arg)
{
   if (!strlen(arg))
      {
      NF("Say what in the Trade tongue?\n");
      return 0;
   }
   
   if(TP->query_skill(SS_LANGUAGE) < 20)
      {
      NF("You are not skilled enough in foreign tongues to be able to "+
         "speak the Trade tongue.\n");
      return 0;
   }
   
   if (this_player()->query_get_echo())
      write("In the Trade tongue, you say: " + arg + "\n");
   else
      write("Ok.\n");
   
   filter(all_inventory(environment(this_player())) - ({ this_player() }),
      "do_say", this_object(), arg);
   return 1;
}

public int
do_say(object who, string arg)
{
   if (!living(who))
      return 0;
   if ((IS_MEMBER(who) && who->query_skill(SS_LANGUAGE) > 19) ||
         who->query_skill(SS_LANGUAGE) > 60)
   tell_object(who, this_player()->query_The_name(who) + " mutters " +
      "in the Trade tongue: " + arg + "\n");
   else
      tell_object(who, this_player()->query_The_name(who) + " says " +
      "something in a foreign tongue.\n");
}

public int
e_mbow(string arg)
{
   object *oblist;
   
   NF("Mbow what?\n");
   
   if (!strlen(arg))
      {
      all(" bows with practiced grace and ease.");
      write("You bow with practiced grace and ease.\n");
      return 1;
   }
   
   oblist = parse_this(arg, "[the] %l");
   if (!sizeof(oblist))
      return 0;
   
   actor("You bow with practiced grace and ease before", oblist);
   all2act(" bows with practiced grace and ease before", oblist);
   target(" bows with practiced grace and ease before you.", oblist);
   return 1;
}

public int
e_mrespect(string arg)
{
   object *oblist;
   
   NF("Mrespect what?\n");
   if (!strlen(arg))
      return 0;
   
   oblist = parse_this(arg, "[the] %l");
   if (!sizeof(oblist))
      return 0;
   actor("You look with great respect at", oblist, ", judging " +
      "them as a shrewd individual.");
   all2actbb(" looks with great respect at", oblist, ".");
   targetbb(" looks with great respect at you, judging you to be an "+
      "individual with shrewdness as one of your best qualities.", oblist);
   return 1;
}
