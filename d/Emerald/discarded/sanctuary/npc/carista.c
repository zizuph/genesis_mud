/* ***********************************************************************
   /d/Avenir/common/bazaar/NPCS/heboba.c
   Owner of the Bazaar Hatshop
   Grace June 1995	
 
         Functions relating to the /bazaar/extr/hatshop.c borrowed from:
 	 *
	 * /d/Gondor/minas/npc/calmacil.c
	 * Originally coded by Lord Elessar Telcontar.
	 *
  *********************************************************************** */
inherit "/d/Avenir/inherit/monster";
inherit "/lib/trade";
inherit "/std/act/action";

#include <ss_types.h>
#include <formulas.h>
#include <wa_types.h>
#include "/d/Avenir/common/bazaar/bazaar.h"

#define LOW(x)     lower_case(x)

mixed *fixing;
int    testing;

void
create_monster()
{
  set_name("heboba");
  add_name("milliner");
  add_name(({"woman", "sybarite", "sybarun"}));
  set_race_name("gnome");
  set_living_name("heboba");
  set_title("the Milliner");
  set_adj(({"slender","sloe-eyed"}));
  set_long("A lovely little gnome who seems to be very busy making hats.\n"+
    "Wisps of hair have come loose from her braid and formed damp curls "+
    "on her forehead.\nShe is wearing a fashionable black velvet hat and "+
    "a black velvet frock.\n");
  set_gender(1);
  set_alignment(100);

  add_prop(NPC_M_NO_ACCEPT_GIVE,0);
  add_prop(NPC_I_NO_LOOKS, 1);

  default_config_npc(25);

  set_tell_active(1);

  set_chat_time(7);
  add_chat("What can I help you with?");
  add_chat("If you want a hat made for you, just say you would like to order.");
  add_chat("I can make you a delightful hat to go with what you are wearing.");
  add_chat("I can make the gift to give to the person who has everything.");
  add_chat("Would you like me to make you a hat?");
  add_chat("If you have any questions about hats, just ask me.");
  add_chat("I try to price my hats reasonably, while not skimping on the quality.");
  add_chat("Turbans are all the rage, ever since I made one for the Lord High "+
      "Commissioner's wife. Would you like one?");

  add_ask(({"hat", "hats"}),
      "say I make very good hats, of various styles. If you want a hat, just "+
      "say that you would like to order.", 1);
  add_ask(({"order", "orders"}),
      "say I don't recall that you have ordered anything. If you want me to "+
      "make a hat, just say you would like to order.", 1);
  add_ask(({"snood", "about snoods", "snoods"}),
      "say The snoods I make can be worn two ways, and are "+
      "worn exclusively by women.\nHeboba says: The snood can be worn "+
      "as a head-band. When worn in this style, it indicates that a woman is "+
      "unmarried.\nHeboba says: The snood can also be worn so that it "+
      "holds the back of a woman's hair along her neck. It is a pleasant "+
      "and stylish alternative to putting one's hair into a bun.", 1);
  add_ask(({"fez", "about fez", "fezzes"}),
      "say Fezzes are generally worn by men. They are conical in shape "+
      "and are adorned with a tassel.", 1);
  add_ask(({"turban", "about turban", "turbans"}),
      "say Turbans are worn by both men and women. I make my turbans "+
      "using a long piece of cloth wrapped about a small cap.\nHeboba says: "+
      "This way you don't have to worry about ruining the turban when "+
      "remove it from your head.", 1);
  add_ask(({"fedora", "about fedora", "fedoras"}),
      "say Ah! This is a hat favoured by the adventurous types!\nHeboba "+
      "says: It is a soft hat with a curved brim and a lengthwise crease in "+
      "the crown.", 1);
  add_ask(({"cap", "about cap", "caps"}),
      "say My caps fit the head very closely. They have no brim or visor, "+
      "and are most comfortable when made from soft, supple materials.", 1);
  add_ask(({"beret", "about beret", "berets", "biretta"}),
      "say Berets are soft, visorless caps with a close-fitting headband "+
      "and an over-sized, slightly rounded top.",1);
  add_ask(({"bonnet", "bonet", "about bonnet", "bonnets"}),
      "say This type of hat is mostly worn by women.\nHeboba says: "+
      "The bonnet is a large hat which frames the face in such a way "+
      "that the hair is not seen. It is often decorated with lace and "+
      "bows.", 1);
   add_ask("list", "say There is a list on the counter.", 1);



  config_default_trade();
}


int
catch_say(string what)
{
    object  ord,
            tp = TP;
    string  who = tp->query_real_name(),
            dummy,
            vb = query_verb();

    what = LOW(what);

    if (vb[0..0] == "'")
        if (strlen(what))
            what = vb[1..] + " " + what;
        else
            what = vb[1..];

    if (sscanf(what,"%s like to order%s", dummy, dummy) == 2)
    {
        ord = environment()->query_ordering();
        if (ord)
        {
            if (ord == tp)
            {
                set_alarm(0.0, 0.0, "command",
                    "say I am sorry, but you already have an order in progress!");
                return 0;
            }
            set_alarm(0.0, 0.0, "command",
                "say I am terribly sorry "+tp->query_nonmet_name()+", You will "+
                "have to wait.");
            return 0;
        }
        set_alarm(5.0, 0.0, "make_order", tp);
        return 0;
    }
}

int
make_order(object player)
{
    environment()->place_order(player);
    return 1;
}

void
enter_inv(object obj, object from)
{
    ::enter_inv(obj,from);
    if (!from) return; /* Was probably cloned into me. */
    set_alarm(2.0, 0.0, "give_back_now",({obj,from})); // hope that works!
}


give_back_now(object *things)
{
  command("say Thank you, but I cannot accept such a gift, "+things[1]->query_nonmet_name()+".");
  command("give "+things[0]->query_name()+" to "+things[1]->query_real_name());
  if (ENV(things[0]) == TO) command("drop "+things[0]->query_name());
  return 1;
}

give_back(object *things)
{
  if (!living(things[1])) command("say How did I come by this "+things[0]->query_name()+
    "? I'll drop it here, in case its owner returns.");
  else command("say Here is your "+things[0]->query_name()+", "+things[1]->query_race_name()+"!");
  command("give "+things[0]->query_name()+" to "+things[1]->query_real_name());
  if (ENV(things[0]) == TO) command("drop "+things[0]->query_name());
  fixing = 0;
  return 1;
}


can_afford(object player, int price)
{
  return pay(price,player,0,1,0,0,0);
}

query_knight_prestige() { return -1; }

string
give_it_back()
{
    catch_tell(TP->query_name() + " says: give it back");
    return "";
}


void
init_living()
{
    ::init_living();

    add_action("catch_say", "say");
    add_action("catch_say", "'", 1);
}
