#pragma strict_types

inherit "/cmd/std/command_driver";

#include "/d/Kalad/defs.h"
#include <thanardefs.h>
#include <tasks.h> /* needed for task-difficulties */
#include <ss_types.h> /* needed for skills */

#define HELP_FILE "BLAH"
#define MORE_OBJ "BLAH"
#define THANAR_TALK "_thanar_talk"

public int query_cmd_soul() { return 1; }
public string get_soul_id() { return "Thanarian"; }

public mapping
query_cmdlist()
{
   return ([
#include "tcommands.h"
           ]);
}

/* Spell: Summon a messenger snake */
public int
e_snake()
{
   object snake;
   int task_result;

   NF("You are too weak to summon a snake.\n");
   if(TP->query_mana() < 30)
      return 0;
   write("You kneel on the ground and mumble a prayer to Thanar.\n");
   say(QCTNAME(TP)+" kneels on the ground and mumbles a prayer to "+
      "Thanar.\n");
   
   /* Task: Cast a summoning spell. Summons a messenger snake.
   Difficulty: easy
      Skills: Race-stat and spellcraft-skill.
   Max spellcraft learned in the guild is 30.
   */
   
   task_result = TP->resolve_task(TASK_SIMPLE,({TS_RACE,SS_SPELLCRAFT}));
   if (task_result > 0)
   {
      /* The task was successfully done */
      TP->add_mana(-30);
      setuid();
      seteuid(getuid());
      snake = clone_object(THANAR(snake));
      set_alarm(3.0,0.0,"snake1",snake);
      return 1;
   }
   /* the task was a failure */
   set_alarm(2.0,0.0,"snake_fail");
   return 1;
}
void
snake_fail()
{
   write("It seems Thanar is refusing to listen to your prayers.\n");
   TP->add_mana(-5); /* punish even failed casting of this spell */
   say(QCTNAME(TP)+" stands up again.\n");
}

void
snake1(object snake)
{
   tell_room(E(TP),"A coil of smoke begins to rise out of the "+
      "ground...\n");
   set_alarm(2.0,0.0,"snake2",snake);
}
void
snake2(object snake)
{
   tell_room(E(TP),"The coil of smoke then transforms into a snake!\n");
   write("The snake slithers up to you and coils around your arm.\n");
   say("The snake slithers up to "+QTNAME(TP)+" and coils around "+
      "his arm.\n");
   snake->move(TP);
}

/* Spell: Summon an apparition of Thanar. */
public int
e_tsummon(string str)
{
   object thanar;
   int task_result;

   NF("Summon what?\n");
   if(str != "thanar")
      return 0;
   NF("You are mentally too weak to do that.\n");
   if(TP->query_mana() < 30)
      return 0;
   NF("You have already summed the apparition of Thanar!\n");
   if(TP->query_prop(THANAR_TALK))
      return 0;
   write("You mumble a prayer to Thanar.\n");
   say(QCTNAME(TP)+" mumbles a prayer to Thanar.\n");
   /* Task: Spell to summon an apparition of thanar
   Difficulty: Routine, but demands high guild-stat.
      Skills: TS_RACE and SS_SPELLCRAFT
   
   */
   
   task_result = TP->resolve_task((TASK_ROUTINE+150),({TS_RACE, SS_SPELLCRAFT}));
   log_file("thanar_task",TP->query_real_name()+" got the result: "+
      task_result+" with racestat at "+TP->query_stat(SS_RACE)+
      " and spellcraft at "+TP->query_skill(SS_SPELLCRAFT)+".\n");
   if (task_result > 0)
   {
      /* casting a success */
      write("Your mind is drained!\n");
      TP->add_mana(-30);
      setuid();
      seteuid(getuid());
      thanar = clone_object(THANAR(ap_thanar));
      thanar->move(E(TP));
      thanar->set_owner(TP);
      tell_room(E(TP),"A ghostly image of Thanar fades into view!\n");
      TP->add_prop(THANAR_TALK,thanar);
      set_alarm(60.0,0.0,"remove_thanar",thanar,TP);
      return 1;
   }
   /* casting a failure */
   write("You fail in calling upon Thanar's apparitions!\n");
   say(QCTNAME(TP)+" seems to have finnished praying.\n");
   TP->add_mana(-5); /* failure is also punished */
   return 1;
}

void
remove_thanar(object thanar, object player)
{
   player->remove_prop(THANAR_TALK);
   tell_room(E(thanar),"The ghostly image of Thanar fades away.\n");
   if(!present(thanar,E(player)))
      player->catch_msg("You feel the image of Thanar has left.\n");
   thanar->remove_con();
   thanar->remove_object();
}

public int
e_anger(string arg)
{
   object *oblist;
   
   NF("Express your anger at whom?\n");
   
   if (!strlen(arg))
      {
      allbb(" expresses " + TP->query_possessive() + " anger with horrible insults directed at demihumans.");
      write("You express your anger with horrible insults directed at demihumans.\n");
      SOULDESC("cursing violently and spewing forth horrible insults");
      return 1;
   }
   
   oblist = parse_this(arg, "[at] / [to] / [toward] [the] %l");
   if (!sizeof(oblist))
      return 0;
   
   SOULDESC("cursing violently and spewing forth horrible insults");
   actor("You hurl the most horrible and vile insults known at", oblist, " because they deserve it.");
   all2actbb(" hurls the most horrible and vile insults known at", oblist, " because they deserve it.");
   targetbb(" hurls the most horrible and vile insults known at you because you deserve it.", oblist);
   return 1;
}

public int
e_cruelty(string arg)
{
   object *oblist;
   NF("Show cruelty to whom?\n");
   if(!strlen(arg))
      {
      allbb(" develops a malicious and devious look on " + TP->query_possessive() + " face in anticipation of commiting acts of cruelty.");
      write("You develop a malicous and devious look on your face in "+
         "anticipation of commiting acts of cruelty.\n");
      SOULDESC("anticipating commiting acts of obscene cruelty");
      return 1;
   }
   oblist = parse_this(arg, "[at] / [to] / [toward] [the] %l");
   if(!sizeof(oblist))
      return 0;
   SOULDESC("anticipating commiting acts of obscene cruelty");
   actor("You relate your most demonic and base thoughts to", oblist, " in all their horrid detailedness.");
   all2actbb(" relates " + TP->query_possessive() + " most demonic and base thoughts to", oblist, " in all their horrid detailedness.");
   targetbb(" relates " + TP->query_possessive() + " most demonic and base thoughts to you in all their horrid detailedness.", oblist);
   return 1;
}

public int
e_hatred(string arg)
{
   NF("Did you want to show your hatred?\n");
   if (strlen(arg))
      return 0;
   
   allbb(" narrows " + TP->query_possessive() + " eyes to mere slits, "+
      "twists " + TP->query_possessive() + " mouth into a grotesque caricature of "+
      "itself and looks around with an expression of utter hatred.");
   write("You narrow your eyes to mere slits, twist your mouth into a "+
      "grotesque caricature of itself and look around with an expression of "+
      "utter hatred.\n");
   SOULDESC("looking around with unconcealed hatred");
   return 1;
}

public int
e_pride(string arg)
{
   NF("Did you want to show your pride?\n");
   if(strlen(arg))
      return 0;
   
   allbb(" stands tall and erect, pride evident in " + TP->query_possessive() + " face at being human.");
   write("You stand tall and erect, pride evident in your face at being human.\n");
   SOULDESC("standing proudly");
   return 1;
}
public int
e_joy(string arg)
{
   NF("Did you want to express your joy?\n");
   if (strlen(arg))
      return 0;
   
   all(" smiles joyfully, for " + TP->query_pronoun() + " knows that nothing can defeat the will of Thanar.");
   write("You smile joyfully, for you know that nothing can defeat the will of Thanar.\n");
   SOULDESC("smiling joyfully at the thought of Thanar's omnipotence");
   return 1;
}
public int
e_horror(string arg)
{
   NF("Did you want to express your horror?\n");
   if (strlen(arg))
      return 0;
   
   all("'s face contorts into a mask of horror and loathing at the thought "+
      "of a world populated by demihumans.");
   write("Your face contorts into a mask of horror and loathing at the "+
      "thought of a world populated by demihumans.\n");
   SOULDESC("gazing about in horror and loathing");
   return 1;
}

public int
e_tgreet(string arg)
{
   object *oblist;
   
   NF("Whom did you want to greet in the name of Thanar?\n");
   if (!strlen(arg))
      return 0;
   
   oblist = parse_this(arg, "[the] %l");
   if (!sizeof(oblist))
      return 0;
   actor("You place your platinum chain necklace upon", oblist, "'s brow in "+
      "the Thanarian greeting.");
   all2actbb(" places " + TP->query_possessive() + " platinum chain necklace "+
      "upon", oblist, "'s brow in the Thanarian greeting.");
   target(" places " + TP->query_possessive() + " platinum chain necklace "+
      "upon your brow and greets you in the name of Thanar.", oblist);
   return 1;
}

public int
e_tstrangle(string arg)
{
   object *oblist;
   NF("Whom did you want to strangle with your necklace?\n");
   if(!strlen(arg))
      return 0;
   oblist = parse_this(arg, "[the] %l");
   if(!sizeof(oblist))
      return 0;
   actor("You quickly wrap your platinum chain necklace around", oblist, "'s throat "+
      "and forcefully begin twisting it, slowly constricting it so as to "+
      "crush the wind-pipe.\n"+
      "Slowly, you relax your grip.");
   all2actbb(" quickly places " + TP->query_possessive() + " platinum chain necklace around", oblist, "'s neck and "+
      "forcefully begins to twist it so as to crush the wind-pipe.\n"+
      "Slowly " + TP->query_pronoun() + " relaxes " + TP->query_possessive() + " grip.");
   target(" quickly wraps " + TP->query_possessive() + " platinum chain necklace "+
      "around your neck and forcefully begins twisting it, slowly constricting "+
      "it so as to crush your wind-pipe.\n"+
      "Just when you think you've breathed your last, " + TP->query_pronoun() + " releases " + TP->query_possessive() + " stranglehold.", oblist);
   return 1;
}

public int
e_tcurse(string arg)
{
   object *oblist;
   
   NF("Whom did you want to tcurse?\n");
   
   if (!strlen(arg))
      {
      all(" spits on the ground in disgust and curses loudly in the name of Thanar.");
      write("You spit on the ground in disgust and curse loudly in the name of Thanar.\n");
      return 1;
   }
   
   oblist = parse_this(arg, "[at] / [to] / [toward] [the] %l");
   if (!sizeof(oblist))
      return 0;
   
   actor("You spit on", oblist, " while calling down the wrath of Thanar.");
   all2act(" spits on", oblist, " while calling down the wrath of Thanar.");
   target(" spits directly on you while calling down the wrath of Thanar to "+
      "curse you.", oblist);
   return 1;
}

public int
e_tlook(string arg)
{
   object *oblist;
   
   NF("Whom did you want to look at?\n");
   
   if (!strlen(arg))
      {
      all(" gazes around with a barely concealed look of overwhelming arrogance.");
      write("You gaze around with a barely concealed look of overwhelming arrogance.\n");
      SOULDESC("gazing around with a look of barely concealed arrogance");
      return 1;
   }
   
   oblist = parse_this(arg, "[the] %l");
   if (!sizeof(oblist))
      return 0;
   
   SOULDESC("gazing around with a look of overwhelming arrogance");
   actor("You look at", oblist, " with a barely concealed look of overwhelming arrogance.");
   all2act(" looks at",  oblist, " with a barely concealed look of overwhelming arrogance.");
   target(" looks at you with a barely concealed look of overwhelming arrogance.", oblist);
   return 1;
}

public int
e_tswear(string arg)
{
   object *oblist;
   
   NF("Whom did you want to tswear?\n");
   
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
e_tpreach(string arg)
{
   object *oblist;
   
   NF("Preach the ways of Thanar to whom?\n");
   
   if (!strlen(arg))
      {
      all(" begins to sing the praises of Thanar's world vision, a vision where "+
         "only the chosen race, humanity, shall live while all other races "+
         "are pushed into extinction.");
      write("You begin to sing the praises of Thanar's world vision, a "+
         "vision where only the chosen race, humanity, shall live while all "+
         "other races are pushed into extinction.\n");
      SOULDESC("preaching the glories of Thanar's world vision");
      return 1;
   }
   
   oblist = parse_this(arg, "[at] / [to] / [toward] [the] %l");
   if (!sizeof(oblist))
      return 0;
   
   SOULDESC("preaching the glories of Thanar's world vision");
   actor("You begin to preach to", oblist, " about Thanar's world vision of human supremacy.");
   all2act(" begins to preach to", oblist, " about Thanar's world vision of human supremacy.");
   target(" begins to preach to you about Thanar's world vision of human supremacy.", oblist);
   return 1;
}

public int
e_suspicion(string arg)
{
   object *oblist;
   
   NF("Stare with suspicion at whom?\n");
   
   if (!strlen(arg))
      {
      all(" peers around the room suspiciously, searching for thieves.");
      write("You peer around the room suspiciously, searching for thieves.\n");
      SOULDESC("peering around suspiciously, searching for thieves");
      return 1;
   }
   
   oblist = parse_this(arg, "[the] %l");
   if (!sizeof(oblist))
      return 0;
   
   SOULDESC("peering around suspiciously, searching for thieves");
   actor("You peer at", oblist, " suspiciously, searching for any sign of "+
      "thievery.");
   all2act(" peers at", oblist, " suspiciously, searching for any sign of thievery.");
   target(" watches you suspiciously, as though you were a thief.", oblist);
   return 1;
}

public string
q_title(object ob, int wiz)
{
   if (!ob->query_guild_member("Thanarian human race guild"))
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
e_tlist(string arg)
{
   int i;
   i = (query_verb() == "mwlist" ? 1 : 0);
   write("Whispering a prayer to Thanar, you discover that the "+
      "following Thanarians are currently out on missions:\n"+
      implode(map(users() - ({ 0 }), "q_title", this_object(), i) - ({ 0 }),
         "\n") + "\n");
   say(QCTNAME(TP) + " whispers a prayer to Thanar.\n");
   return 1;
}

int kolla(object ob)
{
   if(!living(ob))
      return 0;
   
   return 1;
}

public int
e_tspeak(string arg)
{
   if (!strlen(arg))
      {
      NF("Say what in the language of Thanar?\n");
      return 0;
   }
   
   if(TP->query_skill(SS_LANGUAGE) < 30)
      {
      NF("You are not skilled enough in foreign tongues to be able to "+
         "speak the Thanar tongue.\n");
      return 0;
   }
   
   if (this_player()->query_get_echo())
      write("In the Thanar tongue, you say: " + arg + "\n");
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
   if ((IS_MEMBER(who) && who->query_skill(SS_LANGUAGE) > 29) ||
         who->query_skill(SS_LANGUAGE) > 60)
   tell_object(who, this_player()->query_The_name(who) + " mutters " +
      "in the Thanar tongue: " + arg + "\n");
   else
      tell_object(who, this_player()->query_The_name(who) + " says " +
      "something in a strange tongue.\n");
}

public int
e_ttorture(string arg)
{
   object *oblist;
   
   NF("Torture whom?\n");
   
   if (!strlen(arg))
      {
      all(" looks around, searching for someone to torture.");
      write("You look around, searching for someone to torture.\n");
      SOULDESC("looking around, searching for someone to torture");
      return 1;
   }
   
   oblist = parse_this(arg, "[the] %l");
   if (!sizeof(oblist))
      return 0;
   
   SOULDESC("looking around, searching for someone to torture");
   actor("You torture", oblist, " cruelly and without mercy.");
   all2act(" tortures", oblist, " cruelly and without mercy.");
   target(" tortures you cruelly and without mercy, ripping your "+
      "fingernails off one by one and hamstringing you.", oblist);
   return 1;
}

public int
e_respect(string arg)
{
   object *oblist;
   
   NF("Show respect to whom?\n");
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

public int
e_tshout(string arg)
{
   object *oblist;
   NF("Shout in ecstacy at whom?\n");
   if(!strlen(arg))
      {
      all(" screams outloud in pure ecstacy at all the glory that shall belong "+
         "to Thanar.");
      write("You scream outloud in pure ecstacy at all the glory that shall "+
         "belong to Thanar.\n");
      SOULDESC("screaming outloud in pure ecstacy");
      return 1;
   }
   oblist = parse_this(arg, "[at] / [to] / [toward] [the] %l");
   if(!sizeof(oblist))
      return 0;
   SOULDESC("screaming out loud in pure ecstacy");
   actor("You scream at", oblist, " in pure ecstacy, for all glory is "+
      "Thanar's.");
   all2act(" screams at", oblist, " in pure ecstacy, for all glory is Thanar's.");
   target(" screams at you in pure ecstacy, for all glory is Thanar's.", oblist);
   return 1;
}

public int
e_disregard(string arg)
{
   object *oblist;
   NF("Disregard whom as a threat?\n");
   if(!strlen(arg))
      {
      all(" disregards anything in the immediate area as a threat.");
      write("You disregard anything in the immediate area as a threat.\n");
      SOULDESC("disregarding anything in the immediate area as a threat");
      return 1;
   }
   oblist = parse_this(arg, "[the] %l");
   if(!sizeof(oblist))
      return 0;
   SOULDESC("disregarding anything in the immediate area as a threat");
   actor("You disregard", oblist, " as a threat to the power of Thanar.");
   all2act(" disregards", oblist, " as a threat to the power of Thanar.");
   target(" disregards you as a threat to the power of Thanar.", oblist);
   return 1;
}

public int
e_tsneer(string arg)
{
   object *oblist;
   NF("Sneer in derision and contempt at whom?\n");
   if(!strlen(arg))
      {
      all(" sneers in obvious derision and complete contempt of everything in "+
         "sight.");
      write("You sneer in obvious derision and complete contempt of everything "+
         "in sight.\n");
      SOULDESC("sneering in obvious derision and complete contempt of everything in sight");
      return 1;
   }
   oblist = parse_this(arg, "[at] / [to] / [toward] [the] %l");
   if(!sizeof(oblist))
      return 0;
   SOULDESC("sneering in obvious derision and complete contempt of everything in sight");
   actor("You sneer at", oblist, " in obvious derision and complete contempt.");
   all2act(" sneers at", oblist, " in obvious derision and complete contempt.");
   target(" sneers at you in obvious derision and complete contempt.", oblist);
   return 1;
}

public int
e_tjoke(string arg)
{
   object *oblist;
   NF("Joke at whom's expense?\n");
   if(!strlen(arg))
      {
      all(" makes a very crude joke involving a hobbit, a horse and a wooden "+
         "stick.");
      write("You make a very crude joke involving a hobbit, a horse and a wooden "+
         "stick.\n");
      return 1;
   }
   oblist = parse_this(arg, "[at] / [to] / [toward] [the] %l");
   if(!sizeof(oblist))
      return 0;
   actor("You make a very crude joke involving", oblist, ", a horse and a "+
      "wooden stick.");
   all2act(" makes a very crude joke involving", oblist, ", a horse and a "+
      "wooden stick.");
   target(" makes a very crude joke involving you, a horse and a wooden "+
      "stick.", oblist);
   return 1;
}

public int
e_sacrifice(string arg)
   {
   object *oblist;
   NF("Sacrifice whom?\n");
   if(!strlen(arg))
      {
      all(" looks around the area for a suitable sacrifice to Thanar.");
      write("You look around the area for a suitable sacrifice to Thanar.\n");
      SOULDESC("looking around the area for a suitable sacrifice to Thanar");
      return 1;
   }
   oblist = parse_this(arg, "[the] %l");
   if(!sizeof(oblist))
      return 0;
   SOULDESC("looking around the area for a suitable sacrifice to Thanar");
   actor("You gaze very intently at", oblist, ", your next sacrifice to Thanar.");
   all2act(" gazes very intently at", oblist, ", the next sacrifice to Thanar.");
   target(" gazes very intently at you, for you are the next sacrifice to Thanar.", oblist);
   return 1;
}

public int
e_amused(string arg)
{
   object *oblist;
   NF("Look at whom with an amused expression?\n");
   if(!strlen(arg))
      {
      all(" looks around with a totally amused expression.");
      write("You look around with a totally amused expression.\n");
      SOULDESC("looking around with a totally amused expression");
      return 1;
   }
   oblist = parse_this(arg, "[at] / [to] / [toward] [the] %l");
   if(!sizeof(oblist))
      return 0;
   SOULDESC("looking around with a totally amused expression");
   actor("You look at", oblist, " with a totally amused expression.");
   all2act(" looks at", oblist, " with a totally amused expression.");
   target(" looks at you with a totally amused expression, for you are "+
      "nothing but an insolent worm with delusions of grandeur.", oblist);
   return 1;
}

