/* A priest. Made by Korat nov. 1996. 
   He gives out a quest. */

inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";
#include "/d/Kalad/defs.h"
#define QUEST_NAME "scrollquest"

int scroll;
string long;
object priest;
int telling;
int meinvis;

void
/* by Korat */
create_monster()
{
   set_name("xarox");
   add_name("priest");
   set_race_name("dwarf");
   set_adj("ancient");
   add_adj("priest");
   set_long("This old and wise-looking dwarf is clothed in a grey-coloured "+
      "cloak with some faint emblems attached to the chest-piece, "+
      "resembling an anvil and a hammer surrounded with flame-like "+
      "decorations. An aura seems to envelope him, giving him "+
      "not just a holy and wise feel but also one of godly "+
      "protection. To shorten the small time this dwarf has left "+
      "after his beard has had time to grow for probably four "+
      "centuries, may be a futile attempt and a unwise one.\n");
   set_stats(({75,50,100,60,60,75}));
   set_alignment(1000);
   set_skill(SS_UNARM_COMBAT,50);
   set_skill(SS_DEFENCE,60);
   set_skill(SS_AWARENESS,70);
   set_skill(SS_CLIMB,60);
   set_title("the last Priest of Rahxvan");
   set_act_time(3);
   add_act("emote scratches his long, gray beard thoughtfully.");
   add_act("sigh");
   add_act("emote looks rather sad.");
   set_cact_time(3);
   add_cact("say Damn you! Can't you leave an old dwarf to his thoughts?!?");
   add_cact("say Rahxvan, save me and save the last vein of faith on Earth!");
   add_speak("I have lived to see mountains be holowed, citadels "+
      "built and cities die. I know history as well as I know the value "+
      "of gold. But now ... now times are bad. Only Rahxvan can "+
      "save us! My beloved God that has granted me such a long life "+
      "and powers.\n");
   
   set_knight_prestige(-10);
   add_prop(NPC_M_NO_ACCEPT_GIVE,0);
   add_ask("curse","The ancient dwarf says: The curse, yes. The curse ... and all because of "+
      "that stupid dwarf that defied my God.\n");
   add_ask("drow","The ancient dwarf says: Ahh, what foul creatures of darkness. "+
      "Elves turned to evilness they are, and magic are their "+
      "lust. Not like the duergars that just went mad and evil in their search for gold.\n");
   add_ask("underhome","The ancient dwarf says: "+
      "Ahh, Underhome. Well, that is "+
      "this once so proud city gone into ruins.\n");
   add_ask("undreath","The ancient dwarf says: "+
      "Undreath! My own hometown as a child ... "+
      "that the drows have taken and demolished to their own needs.\n");
   add_ask("scouts","The ancient dwarf says: "+
      "The scouts ... they come at night and test our defences. "+
      "One day they will come through and be our doom, unless ...\n");
   add_ask("defences","The ancient dwarf says: "+
      "Our defences, yes. They are strong and manned by "+
      "our best guards. We have even gone so far as to use dewars for our "+
      "protecton! We are desperate ...\n");
   add_ask("magic","The ancient dwarfs says: "+
      "Ahh, magic. We had magic once. My own deity is strong in it "+
      "and if we only could ... ohwell.\n");
   add_ask("affairs","The ancient dwarf says: "+
      "The affairs??? They are in a bad shape here.\n");
   add_ask("wrath","The ancient dwarf says: "+
      "My Gods wrath?! Beware of it, for it will crush "+
      "any opposition as fit is.\n");
   add_ask(({"dares","dares to enter","enter","in"}),
      "The ancient dwarf whispers: "+
      "You are curious aren't you my child. Courage you will need, "+
      "be sure of it! Unless ...\n");
   add_ask("unless","The ancient dwarf says: "+
      "Ohh, unless you would please my God so much that he "+
      "will remove his curse. But how to do that ... my prayers has not "+
      "helped at all.\n");
   add_ask(({"gurden","climber","climber dwarf"}),
      "Ohh, him! My fellow brothers thinks of him "+
      "as a hero ... a man that angered my God, Raxhvan.\n");
   add_ask("help","Help? I am afraid I can't help you much ... all I know is history "+
      "and one fun spell.\n");
   add_ask(({"spell","power","powers"}),"My spell? I can with the help of my God, "+
      "make people dissapear! If you want me to do that to you, "+
      "then just ask me to do it.\n");

   trig_new("%w 'attacks' %s","react_attack");
   trig_new("%w 'arrives.' %s","react_arrive");

   meinvis = 0;
}

int
react_attack(string who, string dummy){
   string *str_check;
   if(who){
      who = lower_case(who);
      str_check = explode(dummy, " ");
      if (sscanf(str_check[0],"you%s",dummy))
         {
         TO->command("emote shrieks: Rahxvan! Save me now and save "+
            "the last vein of belief of you on this earth!");
         set_alarm(2.0,0.0,"help_priest");
         return 1;
      }
      TO->command("say Please stop this violent behaviour. Save it to the drows!");
      return 1;
   }
}

void
react_arrive(string who, string dummy)
{
   set_alarm(2.0,0.0,"do_react_arrive");
}

void
do_react_arrive()
{
   TO->command("emote bows deeply.");
   TO->command("say welcome stranger.");

/* let the priest show off his spell sometimes
    to trigger the curiosity of the players */

   if(random(5)==0 && !TO->query_prop(OBJ_I_INVIS))
      set_alarm(6.0,0.0,"do_invis_spell",TO);
}

void
help_priest()
{
   TO->set_stats(({60,60,160,50,50,60}));
   TO->heal_hp(TO->query_max_hp());
   tell_room(E(TO),"The priest seems to grow in front of your eyes!\n");
   tell_room(E(TO),"You notice that the room grows hotter and hotter.\n");

   /* The room has a special-attack coded in it that aids this npc */
   E(TO)->ask_attack();
}

/* when triggered on players asking something, this function starts */
int
give_history(string who,string what)
{
   object person;
   if(who)
      {
      who = lower_case(who);
      person=present(who,E(TO));
      if(!person)
         {
         TO->command("emote peers around wondering.");
         return 1;
      }

      /* no info to evil players */
      if(person->query_alignment() < -100)
         {
         TO->command("emote fumes: Leave me be you foul being! "+
            "Go and mine for coal or something.");
         TO->command("emote spits on the floor in disgust.");
         return 1;
      }

      /* this npc only tells one story at a time */
      if(telling)
         {
         TO->command("say Patience, "+person->query_name()+
            ", it takes time to chisel out the gold-vein of history.");
         return 1;
      }

      telling = 1;
      what = lower_case(what);
      if (wildmatch("about *", what)) what = what[6..]; 
      switch (what)
      {
         case "history": set_alarm(1.0,0.0,"first",person); break;
         case "story": set_alarm(1.0,0.0,"first",person); break;
         case "temple": set_alarm(2.0,0.0,"temple1",person); break;
         case "temple ruins": set_alarm(2.0,0.0,"temple1",person); break;
         case "salvation": set_alarm(2.0,0.0,"salv1",person); break;
         case "rahxvan": set_alarm(2.0,0.0,"god1",person); break;
         case "god": set_alarm(2.0,0.0,"god1",person); break;
         case "deity": set_alarm(2.0,0.0,"god1",person); break;
         case "him": set_alarm(2.0,0.0,"god1",person); break;
         case "shrine": set_alarm(2.0,0.0,"shrine1",person); break;
         case "scrolls": set_alarm(2.0,0.0,"shrine1",person); break;
         case "scroll": set_alarm(2.0,0.0,"shrine1",person); break;
         case "scrolls of wisdom": set_alarm(2.0,0.0,"shrine1",person); break;
         case "scroll of wisdom": set_alarm(2.0,0.0,"shrine1",person); break;
         case "make me dissapear": set_alarm(2.0,0.0,"do_invis_spell",person); break;
         case "dissapear": set_alarm(2.0,0.0,"do_invis_spell",person); break;
         default:
         set_alarm(0.0,0.0,"diff_return");
         telling = 0;
         break;
      }
   }
   return 1;
}

/*
 * Routine catch_question() introduced by Mercade to remove the trig_new on
 * asking.
 */
void
catch_question(string str)
{
    give_history(this_player()->query_real_name(), str);
}

/* if it didn't understand the question, a random reply is created */
void
diff_return()
   {
   switch (random(5))
   {
      case 0: TO->command("say I didn't quite catch that ... can you repeat it?"); break;
      case 1: TO->command("say Pardon me?"); break;
      case 2: TO->command("emote peers at you."); break;
      case 3: TO->command("say Uhh, my hearing is bad ..."); break;
      case 4: TO->command("say Well ... what?"); break;
      default: break;
   }
}


/* This part is the different stories the dwarf can tell */   
void
temple1(object person)
{
   if(!present(person,E(TO))) { set_alarm(0.0,0.0,"finnish",person); return; }
   TO->command("emote peers at you.");
   set_alarm(2.0,0.0,"temple2",person);
}
void
temple2(object person)
{
   if(!present(person,E(TO))) { set_alarm(0.0,0.0,"finnish",person); return; }
   TO->command("say Yes? Ohh you don't know about the curse ... "+
      "none can get into it now that my friends down here has turned "+
      "their backs to my deity, Rahxvan. But salvation lies within it! "+
      "But do you think they listen to me? Ohno, I am just an old grumpy "+
      "dwarf that rambles about long forgotten Gods. They believe "+
      "in steel and rock! Not words and magic.");
   set_alarm(6.0,0.0,"temple3",person);
}
void
temple3(object person)
{
   if(!present(person,E(TO))) { set_alarm(0.0,0.0,"finnish",person); return; }
   TO->command("emote grumbles and complains about the state of affairs.");
   telling = 0;
}
void
salv1(object person)
{
   if(!present(person,E(TO))) { set_alarm(0.0,0.0,"finnish",person); return; }
   TO->command("emote goes Hmmm.");
   set_alarm(3.0,0.0,"salv2",person);
}
void
salv2(object person)
{
   if(!present(person,E(TO))) { set_alarm(0.0,0.0,"finnish",person); return; }
   TO->command("say Well, if you want to listen to me ... inside it there "+
      "is a shrine that contains the scrolls of wisdom. With them I will "+
      "be able to turn the heads back to the right vein in their stubborn "+
      "way of digging through this problem we are facing.");
   set_alarm(7.0,0.0,"salv3",person);
}
void
salv3(object person)
{
   if(!present(person,E(TO))) { set_alarm(0.0,0.0,"finnish",person); return; }
   TO->command("say Get it to me and we can save my people!");
   set_alarm(3.0,0.0,"salv4",person);
}
void
salv4(object person)
{
   if(!present(person,E(TO))) { set_alarm(0.0,0.0,"finnish",person); return; }
   TO->command("emote goes Hmm.");
   set_alarm(3.0,0.0,"salv5",person);
}
void
salv5(object person)
{
   if(!present(person,E(TO))) { set_alarm(0.0,0.0,"finnish",person); return; }
   TO->command("say And maybe Rahxvan will reward you too? He used to "+
      "be nice to brave men. And cruel to stupid fools ... so be warned. "+
      "You may have to face the wrath of my God!");
   set_alarm(4.0,0.0,"salv6",person);
}
void
salv6(object person)
{
   if(!present(person,E(TO))) { set_alarm(0.0,0.0,"finnish",person); return; }
   TO->command("emote the dwarf ponders on something.");
   set_alarm(2.0,0.0,"salv7",person);
}
void
salv7(object person)
{
   if(!present(person,E(TO))) { set_alarm(0.0,0.0,"finnish",person); return; }
   TO->command("say Ohh, almost forgot: Nobody dares to enter the ruins "+
      "of my old temple or did I mention that ... ?");
   set_alarm(3.0,0.0,"salv8",person);
}
void
salv8(object person)
{
   if(!present(person,E(TO))) { set_alarm(0.0,0.0,"finnish",person); return; }
   TO->command("emote tugs his long gray beard in though.");
   set_alarm(4.0,0.0,"salv9",person);
}
void
salv9(object person)
{
   if(!present(person,E(TO))) { set_alarm(0.0,0.0,"finnish",person); return; }
   TO->command("say And I don't know how to get in ...");
   TO->command("emote seems to get a troubled look on his face as "+
      "he is lost in his own thoughts.");
   telling = 0;
}

void
god1(object person)
{
   if(!present(person,E(TO))) { set_alarm(0.0,0.0,"finnish",person); return; }
   TO->command("say That is my God of worship. He is a hard deity that "+
      "demands much from his followers. Once a Master-mason made a "+
      "monument for Him, but managed to chip off a small peice of "+
      "the smooth surface of the monuments eye.");
   set_alarm(6.0,0.0,"god2",person);
}
void
god2(object person)
{
   if(!present(person,E(TO))) { set_alarm(0.0,0.0,"finnish",person); return; }
   TO->command("emote shakes his head in disbelief of such "+
      "open defiance of his God.");
   set_alarm(4.0,0.0,"god3",person);
}
void
god3(object person)
{
   if(!present(person,E(TO))) { set_alarm(0.0,0.0,"finnish",person); return; }
   TO->command("say Rahxvan was angry, very angry, and cast "+
      "him out of Underhome for ever. He was doomed to watch "+
      "the great sky for ever in players and solitude. None "+
      "has heard of him since. The funny part is that this dwarf "+
      "is now a hero here among my brothers.");
   set_alarm(3.0,0.0,"god4",person);
}
void
god4(object person)
{
   if(!present(person,E(TO))) { set_alarm(0.0,0.0,"finnish",person); return; }
   TO->command("emote the dwarf chuckles.");
   set_alarm(3.0,0.0,"god5",person);
}
void
god5(object person)
{
   if(!present(person,E(TO))) { set_alarm(0.0,0.0,"finnish",person); return; }
   TO->command("say It shows the stupidity they have fallen into. "+
      "Mining for coal they are!");
   TO->command("emote spits on the floor to emphasize the insult and "+
      "grows silent.");
   telling = 0;
}

void
shrine1(object person)
{
   if(!present(person,E(TO))) { set_alarm(0.0,0.0,"finnish",person); return; }
   TO->command("emote nods gravely.");
   set_alarm(3.0,0.0,"shrine2",person);
}
void
shrine2(object person)
{
   if(!present(person,E(TO))) { set_alarm(0.0,0.0,"finnish",person); return; }
   TO->command("say That is what I need.");
   set_alarm(2.0,0.0,"shrine3",person);
}
void
shrine3(object person)
{
   if(!present(person,E(TO))) { set_alarm(0.0,0.0,"finnish",person); return; }
   TO->command("emote whispers: The scrolls ...");
   set_alarm(2.0,0.0,"shrine4",person);
}
void
shrine4(object person)
{
   if(!present(person,E(TO))) { set_alarm(0.0,0.0,"finnish",person); return; }
   TO->command("say Get them for me, will you?");
   TO->command("emote smiles hopefully at you.");
   telling = 0;
}

void
first(object person)
{
   if(!present(person,E(TO))) { set_alarm(0.0,0.0,"finnish",person); return; }
   TO->command("say This region ...");
   set_alarm(2.0,0.0,"second",person);
}
void
second(object person)
{
   if(!present(person,E(TO))) { set_alarm(0.0,0.0,"finnish",person); return; }
   TO->command("emote points around.");
   set_alarm(3.0,0.0,"third",person);
}
void
third(object person)
{
   if(!present(person,E(TO))) { set_alarm(0.0,0.0,"finnish",person); return; }
   TO->command("say ... of the underdark, known as Underhome is "+
      "one of the last refugees for us the ancient deep dwarves.");
   set_alarm(5.0,0.0,"fourth",person);
}
void
fourth(object person)
{
   if(!present(person,E(TO))) { set_alarm(0.0,0.0,"finnish",person); return; }
   TO->command("emote sighs.");
   set_alarm(3.0,0.0,"fifth",person);
}
void
fifth(object person)
   {
   if(!present(person,E(TO))) { set_alarm(0.0,0.0,"finnish",person); return; }
   TO->command("say Long ago, when humans were a rare sight in Kalad, "+
      "my skillfull people flourished. Our mighty citadels and "+
      "expansive underground cities were true technological marvels!");
   set_alarm(2.0,0.0,"sixth",person);
}
void
sixth(object person)
{
   if(!present(person,E(TO))) { set_alarm(0.0,0.0,"finnish",person); return; }
   TO->command("emote smiles proudly.");
   set_alarm(4.0,0.0,"seventh",person);
}
void
seventh(object person)
{
   if(!present(person,E(TO))) { set_alarm(0.0,0.0,"finnish",person); return; }
   TO->command("say Yes, even by today's standards our work in that "+
      "time was of excellensy.");
   set_alarm(3.0,0.0,"eight",person);
}
void
eight(object person)
{
   if(!present(person,E(TO))) { set_alarm(0.0,0.0,"finnish",person); return; }
   TO->command("emote suddenly gets a troubled look as he thinks back in time.");
   set_alarm(4.0,0.0,"ninth",person);
}
void
ninth(object person)
{
   if(!present(person,E(TO))) { set_alarm(0.0,0.0,"finnish",person); return; }
   TO->command("say Yet the great and terrible war between the "+
      "dwarves and the drow took a terrible toll on us dwarves "+
      "that are blessed with a long life. Although we manged to "+
      "defeat the drow, forcing them away from Underhome, we lost "+
      "over three-fourths of  our forces. Friends and family.");
   set_alarm(8.0,0.0,"ten",person);
}
void
ten(object person)
{
   if(!present(person,E(TO))) { set_alarm(0.0,0.0,"finnish",person); return; }
   TO->command("emote sighs deeply.");
   set_alarm(3.0,0.0,"eleven",person);
}
void
eleven(object person)
{
   if(!present(person,E(TO))) { set_alarm(0.0,0.0,"finnish",person); return; }
   TO->command("say ... a loss we never really recovered from. And so "+
      "our surface citadels fell into ruin, a skeletal "+
      "reminder of the glory days when everyone marvelled at "+
      "our work. Even Underhome, one of, if not the most "+
      "magnificent of our cities, is but a poor shadow of itself now.");
   set_alarm(8.0,0.0,"twelv",person);
}
void
twelv(object person)
{
   if(!present(person,E(TO))) { set_alarm(0.0,0.0,"finnish",person); return; }
   TO->command("emote touches the walls of his cave.");
   set_alarm(5.0,0.0,"thirteen",person);
}
void
thirteen(object person)
{
   if(!present(person,E(TO))) { set_alarm(0.0,0.0,"finnish",person); return; }
   TO->command("say And now ... they are back! They have "+
      "taken one of our old cities and called "+
      "it Undraeth, just a few leagues from Underhome, "+
      "and has already begun to send scouts to probe our defences!");
   TO->command("emote grumbles.");
   set_alarm(9.0,0.0,"fourteen",person);
}
void
fourteen(object person)
{
   if(!present(person,E(TO))) { set_alarm(0.0,0.0,"finnish",person); return; }
   TO->command("say If I only could get back to my temple.");
   TO->command("emote seems to fade away into his own thoughts.");
   telling = 0;
}

/* if the player gets "bored" (no way!!) the npc reacts */
void
finnish(object person)
{
   TO->command("shout "+person->query_name()+", "+
      "Why are you leaving?");
   TO->command("say Didn't "+person->query_name()+" like my story?");
   TO->command("emote folds his arms and goes: 'Hmpff'.");
   telling = 0;
}

/* checks if a quest-item was given to him */
public void
enter_inv(object ob, object from)
{
   if(MASTER_OB(ob) != "/d/Kalad/common/wild/pass/dwarf/obj/quest_scroll")
      {
      ::enter_inv(ob, from);
      set_alarm(3.0,0.0,"drop_the_object",ob);
      return;
   }
   ::enter_inv(ob, from);
   if(!interactive(from))
      return;
   else
      set_this_player(from);

   /* no reward to evil players. */
   if(TP->query_alignment()<0)
   {
      TO->command("hmm");
      TO->command("say I don't trust you, you foul being!\n");
      TO->command("emote tears up the scrolls.");
      ob->remove_object();
      return;
   }
   if(from->test_bit("Kalad",2,1))
      {
      write(query_The_name(from) + " smiles happily and says: You've "+
         "brought it to me again! How nice of you!\n");
      TP->catch_msg("You do not feel more experienced.\n");
   }
   else
      {
      TO->command("say You got it ... it is a miracle!");
      TO->command("thank "+from->query_real_name());
      TO->command("say Now I can turn those stubborn heads back to "+
         "the path of Rhoxvan again.");
      TO->command("emote lifts his face towards the cave-roof and "+
         "prays loudly.");
      TO->command("emote prays: Reward this foreigner that has "+
         "helped salvage our faith towards you. He do deserve it.");
      TP->catch_msg("A warm heat, as from a furnace, envelopes you. "+
         "The heat seems to shape your being into the core, and you "+
         "feel more experienced.\n");
      TP->add_exp(10000);
      TP->set_bit(2,1);
      seteuid(getuid(TO));
      log_file(QUEST_NAME, extract(ctime(time()),4,15)+ " " +
         capitalize(TP->query_real_name()) + " rewarded with 10000 xp, "+
         "<"+TP->query_average_stat()+"> average stats.\n");
   }
   set_alarm(3.0,0.0,"remove_the_object",ob);
}
void
drop_the_object(object ob)
{
   command("drop all");
}
void
remove_the_object(object ob)
{
   write("The dwarf runs out of the cave while shouting "+
      "for his fellow men to hear the good news.\n");
   say("The lonely dwarf wanders down the mountain.\n");
   if(priest = present("xarox",E(TP)))
      {
      priest ->remove_object();
   }
}

void
tell_watcher(string str, object enemy)
{
   object me,*ob;
   int i;
   
   me = this_object();
   ob = FILTER_LIVE(all_inventory(environment(me))) - ({ me });
   ob -= ({ enemy });
   for (i = 0; i < sizeof(ob); i++)
   if (ob[i]->query_option(OPT_BLOOD))
      ob[i]->catch_msg(str);
}

int
special_attack(object enemy)
{
   int attacktype, i, penet;
   mixed* hitresult;
   string how;
   object me, *ob;
   me = this_object();
   
/* this npc uses his invisibility-spell to aid himself */
   attacktype=random(30);
   if(attacktype == 1 && !meinvis)
      {
      TO->add_prop(OBJ_I_INVIS,1);
      tell_room(E(TO),"The priest chants slowly, and suddenly "+
         "dissapears in front of your eyes.\n");
      set_alarm(60.0,0.0,"remove_invis");
      meinvis=1;
   }
   
   return 1;
}

/* called when invis-spell is over */
void
remove_invis()
{
   TO->add_prop(OBJ_I_INVIS,0);
   tell_room(E(TO),"An image of a deep dwarf flickers in front of you, "+
      "but soon the image turns into a solid object. You watch amazed.\n");
   meinvis = 0;
}

/* the actual invis-spell code (for this npc and for players) */
void
do_invis_spell(object ob)
{
   if(ob==TO)
   {
      write("You become invisible!");
   TO->command("say I'll show you something fun I know.");
      TO->command("chuckle merrily");
      set_alarm(4.0,0.0,"make_spell",ob);
      return;
   }
   TO->command("say I will try to do it for you. Any help I can give by the "+
      "grace of Rahxvan, is yours to have.");
   TO->command("emote seems to concentrate deeply.");
   set_alarm(4.0,0.0,"make_spell",ob);
  return;
}

void
make_spell(object ob)
{
   object invis;
   object who;
   if(who=present(ob,E(TO)))
   {
   /* no help to evil dudes */
      if(ob->query_alignment()<0)
      {
         TO->command("say do you really think I would waste my "+
         "powers on somebody like you?");
         TO->command("giggle innanely");
         return;
      }
      TO->command("emote starts to chant in the old dwarven "+
        "language, lifting his hands above himself.");
      tell_room(E(TO),"The air almost sparkles from some unknown power!\n");
      if(TO==ob)
         TO->command("emote places his hands on his own fronthead.");
   else
      TO->command("emote places his hands on "+ob->query_real_name()+"'s head.");
      if(TO->query_mana()<300)
      {
         TO->command("emote sighs deeply, looking very tired.");
         TO->command("say sorry, but I lack suficient mental power to do it.");
         return;
      }
     /* the actual spell-object! */
      invis=clone_object(CPASS(dwarf/obj/invis_object));
      invis->move(ob);
      TO->set_mana(TO->query_mana()-300);
      TO->command("chuckle");
      return;
   }
   TO->command("say where did that person leave so sudden?");
   return;
}