/* Infohobbit- travels the Shire dispensing his */
/* wisdom. Or he sits in the Prancing Pony. ;) */
/* Dunstable, Sept 1994 */

inherit "/std/monster";
#include "/d/Shire/common/defs.h"
#include "/sys/ss_types.h"
#include "stdproperties.h"
#include "/d/Shire/common/make_money.h"

create_monster()
{
   set_race_name("hobbit");
   add_adj(({"old kindly"}));
   set_name("bubu"); /* Like Bibi and Bobo */
    set_living_name("_bubu_");
   set_long("This hobbit looks as if he has "+
   "been out travelling the Shire for a long time. "+
   "Rather strange for a hobbit to do, but you might ask him about what he has seen.\n");

   set_act_time(5);
   add_act("emote picks some dirt from between his toes.");
   add_act("emote wonders if it is time for lunch yet.");
   add_act("smile tir");
   add_act("emote seems to drift off to sleep.");
   add_act("emote blinks his eyes carefully.");
   add_act("time");

   set_chat_time(4);
   add_chat("Have you heard the story about the Mayor?");
   add_chat("I have been many places in my time.");
   add_chat("Some hobbits think I'm a fool, or a Took. I don't know which is worse.");
   add_chat("I think I have another adventure left in me.");
   add_chat("The miles and years rest easy on me- I'm as young as a chicken!");

   set_stats(({30,67,45,21,24,55}));
   set_skill(SS_DEFENSE, 55);
   set_skill(SS_UNARM_COMBAT, 43);
   set_skill(SS_TRADING, 31);
   add_prop(LIVE_I_NEVERKNOWN, 1);
   set_whimpy(100);

   MAKE_MONEY;

   set_random_move(6);
   set_monster_home(GHAVEN_DIR + "inn");
   set_restrain_path(({"/d/Shire/michel","/d/Shire/common/greyhaven","/d/Shire/common/hobbiton"}));

   add_ask(({"what you have seen","places","things","stuff"}),VBFC_ME("ask_places"));
   add_ask(({"hobbiton","hobbits","hobbit","hobbit life"}),VBFC_ME("ask_hobbit"));
   add_ask(({"mithlond","grey havens","elves","grey haven"}),VBFC_ME("ask_mithlond"));
   add_ask(({"michel delving","mayor","white farrows"}),VBFC_ME("ask_michel"));
   add_ask(({"bree","humans","human","crossroad","brandywine"}), VBFC_ME("ask_bree"));
   add_ask(({"east road","orcs","orc","travel","travelling"}),VBFC_ME("ask_road"));
   add_ask(({"hollin","trolls","trollshaws","moria"}),VBFC_ME("ask_trolls"));
   add_ask(({"guild","hin warriors","magicians","shire"}), VBFC_ME("ask_hin"));
   add_ask(({"ranger","rangers","rangers of the north"}), VBFC_ME("ask_ranger"));
   add_ask(({"barrow","wights","old forest","downs"}),VBFC_ME("ask_downs"));

   add_ask(({"help","task","job","quest"}), VBFC_ME("ask_quest"));
   add_ask(({"booglebuttle"}),VBFC_ME("ask_cheat"));

}
string
ask_places()
{
   command("say Well, I've been many places.");
   command("count copper coins");
   command("stop counting");
   command("say I've been all over the world, it seems like.");
   command("say I was born and raised in Hobbiton.");
   command("I worked for a time at sea with the elves in Grey Havens, or Mithlond, as they call it.");
   command("say I was assistant to the Mayor of the Shire for a time, in Michel Delving.");
   command("I have downed many a beer at the Prancing Pony, in Bree.");
   command("count silver coins");
   command("stop counting");
   command("smile misc");
   command("say I have been past Bree on the East road, where the Trolls live.");
   command("say I have met some magicians in my time, who live under a mountain, of all places.");
   command("say I know some sneaking rangers who are up to no good!");
   command("say I have seen the ancient burial grounds, the downs, past Hobbiton.");
   command("say Why don't you ask me about one of those places?");
   command("nod inter");
   return "";

}

string
ask_hobbit()
{
   command("say Well, they live a good quiet life in Hobbiton, I suppose.");
   command("say Not much idea of the outside world, but ");
   command("say they're happy. Most hobbits that live in a town");
   command("say live in Hobbiton. It's in the center of the world, for all they know.");

   return "";

}

string 
ask_mithlond()
{
   command("count silver coins");
   command("stop counting");
   command("brighten");
   command("say Ah, yes, Mithlond! Home of the elven shipwright Cirdan!");
   command("say I know the place pretty well.");
   command("say Back before your time, I served the great sea captain Targon ");
   command("say at sea.  He liked me, and so did the elves. It is a rather fair town.");
   command("say The lighthouse can be seen for miles at sea.");
   command("sigh wist");
   return "";

}

string
ask_michel()
{
   command("say Michel Delving is where the Mayor lives.");
   command("say It is in the Western parts of the Shire, just east of Mithlond.");
   command("say There are a good number of hobbits who dwell there.");
   return "";


}

string
ask_bree()
{
   command("smile joy");
   command("say Bree is where the Prancing Pony, the best Inn in ");
   command("say the entire world is!");
   command("bounce exu");
   command("count silver coins");
   command("stop counting");
   command("say Bree is a unique village- the only place ");
   command("say I've never seen a village that had both Big and Little folk living there.");
   command("say It is also the crossroads for the Eastroad and the Greenway.");
   command("say The Greenway goes south into Rohan.");
   command("say But even I've not gone that far south.");
   return "";


}

string
ask_road()
{
   command("say Well, the Eastroad goes from Mithlond to Bree, ");
   command("say and some say beyond that to a place called Rivendell.");
   command("say But if I were worried about being killed by highway robbers ");
   command("grumble");
   command("say Like those miserable orcs, I'd stay between ");
   command("say Grey Havens and Bree, to be on the safe side.");
   command("say Beyond Bree, the Eastroad is wild, and there are ");
   command("say sometimes even trolls out there!");
   command("shiver");

   return "";

}

string
ask_trolls()
{
   command("spit");
   command("say Such foul creatures, I would avoid them at all costs.");
   command("say They're strong and tough, but stupid. So don't fight ");
   command("say them- trick them and get away.");
   command("say They are mostly in the East parts of the world- ");
   command("say In places like Moria, Hollin and the Trollshaws.");
   command("say But all those places are east of Bree.");
   command("say I wouldn't go east of Bree if I were looking to live.");
   command("cringe");

   return "";

}

string
ask_hin()
{
   command("say Aye, I've seen some magic practicing going on.");
   command("say But not on the West side of the Brandywine, that's for sure.");
   command("say Those people call themselves Hin Warriors, and ");
   command("say If you can believe this- live under a mountain!");
   command("laugh");
   command("say I think they're a bunch of dwarves in disguise, ");
   command("say living the way they do.");
   command("say But they're not too dangerous- at least to hobbits.");
   return "";

}

string
ask_ranger()
{
   command("say Rangers? I don't know too much about them.");
   command("say Mostly they hang around the ruins of the old ");
   command("say Kingdom in the north, and go bothering the ");
   command("say stupid Men-folk who live in Bree.");
   command("say But I hear tell that they are all over this world.");
   command("say And not just in the Northlands.");
   command("ponder silly rumors");


   return "";

}

string
ask_downs()
{
   command("say I think those downs near the Brandywine as you ");
   command("say go towards Bree are haunted.");
   command("say I've known several goodhobbits to go in there ");
   command("say and not come out.");
   command("sniff sadl");

   return "";

}

string
ask_quest()
{
   command("say You need help?");
   command("say Well, I am getting rather old, but...");
   command("think");
   command("ponder");
   command("say I think I'm up for another adventure!");
   command("emote gathers up his things.");
   command("say Where are we headed?");



   return "";

}



string
ask_cheat(object player)
{
   command("say Well now. You need to tell me your email address,");
   command("say and I'll get a little something to you.");
   command("wink");
   log_file("/d/Shire/dunstable/private/cheat",extract(ctime(time()),4,15)+ capitalize(player->query_real_name()));

   command("say Hmm.");
   command("say On second thought, I think I'll just ");
   command("say tell the Mayor what you've been up to.");
   command("say Cheater!");

   return "";

}
