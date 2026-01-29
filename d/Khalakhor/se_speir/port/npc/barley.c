/**********************************************************************
 * - barley.c                                                       - *
 * - NPC in the Tavern in MacDunn                                   - *
 * - Created by Damaris@Genesis 02/2005                             - *
 * - Tidied up by Tapakah, 07/2021                                  - *
 **********************************************************************/

#pragma strict_types

#include <const.h>
#include <money.h>
#include <stdproperties.h>
#include "/d/Khalakhor/sys/defs.h"
#include "npc.h"

inherit BASE_NPC;

void
arm_me ()
{
  armours = ({"/d/Khalakhor/common/arm/shirt_cloth",
              "/d/Khalakhor/se_speir/port/arm/apron",
              "/d/Khalakhor/common/kilts/kilt_macdunn"});
  weapons = ({ });
  ::arm_me();    
}

void
create_khalakhor_human ()
{
  ::create_khalakhor_human();
  add_name(({"chef","waiter", "man"}));
  set_gender(G_MALE);
  add_adj(({"stout", "well-dressed"}));
  set_long("He is a great chef.\n"+
           "He has sparkling silver eyes.\n"+
           "He has smooth brown skin.\n"+
           "His hair is very short, sandy blonde and layered.\n");
  set_all_hitloc_unarmed(50);
  set_stats(({70,70,70,70,70,70}));
  add_prop(CONT_I_WEIGHT,48000);
  add_prop(CONT_I_HEIGHT,190);
  
  set_alignment(100);
  set_mm_in("arrives brushing out his chef's apron.");
  MONEY_MAKE_SC(random(40))->move(this_object());
  set_act_time(15);
  
  add_act("ponder");
  add_act("smile thought");
  add_act("whistle soft");
  add_act("emote hums a tune.");
  add_act("emote clears some dishes from a table.");
  add_act("emote straightens his apron.");
  add_ask(({"undead"}),
          "say A word of warning the undead are closer than you realize.", 1);
  add_ask(({"help"}),
          "say I could always use a bit of help, but not today.",1);
  add_ask(({"task"}),
          "say I have no tasks for you to do.", 1);
  add_ask(({"quest"}), 
          "say Ahh now there is something I wish I could do, and that "+
          "is a quest. If only I could go off and discover something "+
          "but my cooking keeps me very busy.", 1);
  add_ask(({"food", "foods"}),
          "say Oh yes please look at the menu, we have plenty of food "+
          "here.",1);
  add_ask(({"drink", "drinks"}),
          "say Oh sure we have lots to drink here, alcohol just being one.",1);
  add_ask(({"ale", "dark ale"}),
          "say The dark ale is quite good. I purchased it from a farmer "+
          "not too far from here.",1);
  add_ask(({"farmer"}),
          "say He lives up north, a pleasant fellow really.",1);
  add_ask(({"red wine", "white wine", "wine"}),
          "say We have red and white wine. The red is a nice sweet "+
          "wine if you like that and the white has a nice dry flavour.",1);
  add_ask(({"coffee", "hot coffee"}),
          "say Oh a nice cup of coffee sounds pretty good. Go ahead "+
          "and enjoy a cup.",1);
  add_ask(({"tea", "spiced tea", "hot tea"}),
          "say Nothing beats a nice cup of spiced tea to get your "+
          "appetite going.",1);
  add_ask(({"milk", "chocolate milk"}),
          "say You like milk? We have fresh milk. We can even make "+
          "chocolate milk if you prefer.",1);
  add_ask(({"spiced cocoa", "cocoa", "hot cocoa"}),
          "say Sure we have spiced cocoa. I use a special blend of "+
          "herbs to spice it up.",1);
  add_ask(({"fried clams", "clams"}),
          "say We select only the finest clams and better them up "+
          "and fry them till golden brown. Try a basket full, I'm "+
          "sure you would like it.",1);
  add_ask(({"beef", "seasoned beef"}),
          "say There is a butcher not so far from here that brings "+
          "us fresh beef and I season it to perfection. Try a plate "+
          "and see.",1);
  add_ask(({"butcher"}),
          "say The butcher? He is a nice fellow, gives me a good "+
          "price on beef too since I always give him and his family "+
          "discount",1);
  add_ask(({"discount"}),
          "say You do not look like you need a discount.",1);
  add_ask(({"corncake", "corncakes"}),
          "say Corncakes are a specialty of mine, I learned to make "+
          "them long ago while traveling and have been makingin them "+
          "ever since.",1);
  add_ask(({"travel", "traveling"}),
          "say I've not been traveling in ages. I settled here and "+
          "have been quite content.",1);
  add_ask(({"ham", "honey ham"}),
          "say If you like melt in your mouth ham, try our special "+
          "honey cured ham.",1);
  add_ask(({"sausage", "hot sausage", "sausages"}),
          "say Our spicy hot sausages go quite well with a bowl of "+
          "scrambled eggs.",1);
  add_ask(({"eggs", "egg", "scrambled eggs"}),
          "say We only use fresh eggs, give it a try.",1);
  add_ask(({"muffin", "muffins"}),
          "say The corn muffins are perfect with any meal or "+
          "just by themselves.",1);
  add_ask(({"oyster", "oysters"}),
          "say Each oyster is fresh and specially breaded and fried. "+
          "My wife loves to eat them with scrambled eggs. She is a dear woman.",1);
  add_ask(({"wife"}),
          "say Ahh yes, my wife, such a beautiful woman. I am a luckey "+
          "man to have found her.",1);
  add_ask(({"eel"}),
          "say I wasn't much of an eel eater, until I found this "+
          "special way to preapre them and I've loved eel ever since. "+
          "So please get a plate and enjoy it.",1);
  add_ask(({"dining room", "private dining", "dining"}),
          "say This dining room? Murah my cousin is a kind man, "+
          "he gave this room to me so I could cook and sell all my "+
          "creations. He is a great man to have given me such a "+
          "wonderful thing.",1);
  add_ask(({"murah", "murah drummon"}),
          "say Murah Drummon is my distant cousin. He's a great man... "+
          "I owe him much.",1);
    
    
}

void
hook_return_intro_new (string str)
{
  command("say Greetings to thee, " + capitalize(str) +
          ", I am " + query_name() + " " + query_title() + 
          ". A pleasure to make thy acquaintance.");
  command("bow " + str);
}

void
hook_return_intro_bad (string str)
{
  command("growl sof");
  command("say I remember thou very well. So be on thy way!");
}

void
hook_return_intro_good (string str)
{
  command("emote beams with pleasure.");
  command("say I remember thee very well from thy " +
          "last visit, " + capitalize(str) + ". How could I "+
          "ever forget thee.");
  command("bow " +str);
  command("say I hope thou art faring well, and enjoying our "+
          "fine city?");
}
