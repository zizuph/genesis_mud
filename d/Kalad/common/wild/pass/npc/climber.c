/* 
 * /d/Kalad/common/wild/pass/npc/climber.c
 * Purpose    : The dwarf at the top of the mountains. He rewards the scale quest as well as giving info on magic items
 * Located    : /d/Kalad/common/wild/pass/top.c
 * Created By : Antharanos ??.??.??
 * Modified By: 
 */ 

inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";
#include "/d/Kalad/defs.h"
#define QUEST_NAME "scalequest"
int scale;
string long;
object climber;
void
/* by Antharanos */
create_monster()
{
   set_name("gurden");
   set_race_name("dwarf");
   set_adj("aged");
   add_adj("weathered");
   set_long("This old dwarf stands here atop the mountain, barely "+
      "moving, as if he were in deep thought. There is a certain sadness in "+
      "his eyes, perhaps that is one reason he has so isolated himself by "+
      "coming here.\n");
   set_stats(({75,50,100,60,60,75}));
   set_alignment(1000);
   set_skill(SS_UNARM_COMBAT,50);
   set_skill(SS_DEFENCE,60);
   set_skill(SS_AWARENESS,70);
   set_skill(SS_CLIMB,60);
   set_title("the lonely");
   set_act_time(3);
   add_act("emote gazes wistfully towards the west.");
   add_act("sigh");
   add_act("emote looks rather sad.");
   set_cact_time(3);
   add_cact("say Damn you! Can't you leave an old dwarf to his thoughts?!?");
   add_cact("say I'll throw yer stinkin corpse offa this mountain!");
   add_speak("Please leave me be...I don't feel like speaking with anyone.\n");
   set_knight_prestige(-10);
   set_default_answer("The old dwarf says: Pardon me?\n");
   add_ask(({"help"}),"The old dwarf says: The only way you can help me "+
      "lad, is to find Underhome.\n");
   add_ask(({"underhome"}),"The old dwarf says: My homeland of course.\n");
   add_ask(({"quest"}),"The old dwarf says: I cannot help you with that.\n");
   add_ask(({"task","job"}),"The old dwarf says: I have no need of your "+
      "services.\n");
   add_ask(({"magic"}),"The old dwarf says: There are many things of "+
      "magic in this world, you'll have to be more specific in your "+
      "questioning if you want an answer to your liking.\n");
   add_ask(({"two-handed thanar sword"}),"The old dwarf says: Ahh...yes "+
      "I know of that weapon...however I shan't tell you a thing about it.\n");
   add_ask(({"massive two-handed warhammer"}),"The old dwarf says: Hmm... "+
      "yes I am familiar with that weapon...however I will not reveal its "+
      "powers to you.\n");
   add_ask(({"bloody steel axe"}),"The old dwarf says: Yes, a powerful "+
      "weapon that is...I shan't reveal its powers to you lest you bring "+
      "me the scale of old Shadowgloom itself!\n");
   add_ask(({"old shadowgloom","shadowgloom","deep dragon","dragon"}),"The old dwarf says: The "+
      "most terrible creature to dwell beneath the light of the Kaladian "+
      "sun, and I do mean beneath...\n");
   add_ask(({"scale"}),"The old dwarf says: Yes, you must slay the "+
      "ferocious creature, and thus prove to me that you are worthy enough "+
      "to know the power of the axe.\n");
   add_ask(({"sword","club","axe","warhammer","weapon"}),"The old dwarf "+
      "says: What about it?\n");
   add_ask(({"foul stygion-black sword","sword of thanar"}),"The old "+
      "dwarf says: Hmm, I can't seem to remember much about that particular "+
      "weapon, you'd better seek the advice of Aleanna, she's a priestess "+
      "of Solara.\n");
   add_ask(({"aleanna","priestess of solara","priestess"}),"The old "+
      "dwarf says: She's a fiesty young priestess of the Church of Solara, "+
      "I believe she's somewhere in Kabal...can't remember where though...\n");
   add_ask(({"church of solara"}),"The old dwarf says: Its "+
      "devoted to the Sun Goddess and her worship. Most people consider it "+
      "to be the state religion in the city-state of Kabal.\n");
   add_ask(({"solara"}),"The old dwarf says: She is the Goddess of the "+
      "sun, watcher of all beneath its warm, life-giving rays. Some say "+
      "that she was once consort to the god, Thanar...but that's nothing "+
      "but rumour...trust me.\n");
   add_ask(({"thanar"}),"The old dwarf says: He is the most wretched of "+
      "all the gods of Kalad, for no other god is more treacherous or "+
      "conniving.\n");
   add_ask(({"pure snow-white sword"}),"The old dwarf says: Ahh, that "+
      "is the fabled sword of Solara...\n");
   add_ask(({"delicate adamantine sword"}),
      "The old dwarf says: Ahh, a powerful drow weapon that be, great magic indeed. If I recall "+
      "correctly, it has a command word. If I were you, I'd listen carefully "+
      "to what the wielder of this sword says.\n");
   add_ask(({"large adamantine morning star"}),
      "The old dwarf says: Hmm...yes I am familiar with that weapon, "+
      "however, old age has made me forgetful. Perhaps if you were to bring "+
      "me some fungus beer from Undraeth I would remember better?\n");
   add_prop(NPC_M_NO_ACCEPT_GIVE,0);
}

scale_return()
{
   scale = 1;
}

public void
enter_inv(object ob, object from)
{
   if(!interactive(from))
      return;
   else
      set_this_player(from);


   if(MASTER_OB(ob) == "/d/Kalad/common/wild/pass/drow/obj/drow_beer")
   {
      ::enter_inv(ob, from);
      command("drink all");
      command("emote goes ahh...");
      command("say Such a tasty beer that be!");
      command("thank " + (TP->query_real_name()));
      command("whisper " + TP->query_real_name() + " The word you are "+
         "seeking is ardinalon.");
      return;
   }

   if(MASTER_OB(ob) == "/d/Kalad/common/caravan/wep/sword_of_thanar")
   {
      ::enter_inv(ob, from);
      command("smile .");
      command("say So...you have the sword...");
      command("say Very well, I'll tell you what you need to know.");
      command("whisper " + TP->query_real_name() + " To recover the sword of Solara, "+
         "you must do the following...From the Lord of the Trading Company "+
         "you must retrieve his priceless jewel. Then, you must journey to the "+
         "the lair of the foul dragon, Shadowgloom. Once in his chamber, you "+
         "must show the old dragon the jewel. Once shown, the dragon will believe "+
         "you to be the Lord of the Trading Company. From there, you must "+
         "drop the foul stygion-black sword before him, such a treasure it "+
         "will surely be interested in...This you must do to recover the "+
         "sword of Solara!\n");
      set_alarm(4.0,0.0,"drop_the_object");
      return;
   }

   if(MASTER_OB(ob) == "/d/Kalad/common/wild/pass/arm/dragon_scale")
   {
      if(from->test_bit("Kalad",0,12))
         {
         write(query_The_name(from) + " smiles happily and says: You've "+
            "brought it to me again! How nice of you!\n");
         TP->catch_msg("You do not feel more experienced.\n");
      }
      else
         {
         write("The lonely dwarf smiles happily at you and whispers the "+
             "command word into your ear...alrandulgur.\n");
         TP->catch_msg("You feel more experienced!\n");
         TP->add_exp(10000);
         TP->set_bit(0,12);
         seteuid(getuid(TO));
         log_file(QUEST_NAME, extract(ctime(time()),4,15)+ " " +
            capitalize(TP->query_real_name()) + " rewarded with 10000 xp, "+
            "<"+TP->query_average_stat()+"> average stats.\n");
      }
      ::enter_inv(ob, from);
      set_alarm(3.0,0.0,"remove_the_object",ob);
      return;
   }

   /* the object does not interest the climber-dwarf */
   ::enter_inv(ob, from);
   TO->command("chuckle");
   set_alarm(4.0,0.0,"drop_the_object");
   return;
}

void
drop_the_object()
{
   command("drop all");
}

void
remove_the_object(object ob)
{
   write("The lonely dwarf wanders down the mountain.\n");
   say("The lonely dwarf wanders down the mountain.\n");
   if(climber = present("gurden",environment(TP)));
   {
      climber -> remove_object();
   }
}