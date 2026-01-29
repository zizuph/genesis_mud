/* File:          /d/Sparkle/area/sparkle/gsl_ships/newbie-cadu-eg/crew/captain.c
 * Creator:       Teth
 * Date:          April 21, 1997
 * Modifications: November 11, 1997, Teth, added destination query
 *                November 14, 1997, Teth, added info module
 * Purpose:       This is the captain of the Macdunn-Gelan, or 
 *                Khalakhor-Calia ship.
 * Ship rerouted to Newbie line via Cadu/EG(Terel), Tapakah, 05/2009
 * Comments:
 */

#pragma save_binary
#pragma strict_types

#include <stdproperties.h>
#include <money.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Genesis/gsl_ships/ships.h"
#include "../ship.h"

inherit NEWBIE_CAPTAIN;
inherit "/d/Khalakhor/lib/knowledge_base";

public void
create_captain ()
{
  ::create_captain();
  set_name("cian");
  add_name("_cian_");
  add_name("captain");
  add_name("macdonough");
  set_living_name("cian");
  set_race_name("human");
  add_adj("boyish-faced");
  set_title("MacDonough, Fisherman of Cadu");
  set_long("This middle-aged human has a fresh, boyish face. No " +
           "stubble grows on his chin or cheeks, yet locks of red hair " +
           "curl around his forehead and face. His hands are rough, bearing " +
           "the marks of a life at sea. A look of perpetual worry " +
           "mars his youthful looks.\n");

  set_stats(({ 50, 60, 40, 50, 50, 50 }));
  heal_hp(10000);
  set_skill(SS_AWARENESS, 15);
  set_skill(SS_WEP_KNIFE, 20);
  set_skill(SS_DEFENCE, 10);
  set_skill(SS_PARRY, 5);
  set_size_descs("normal","normal");
  
  seteuid(getuid());
  MONEY_MAKE_CC(random(20) + 10)->move(this_object());
  
  add_prop(NPC_I_NO_LOOKS, 1);
  
  set_act_time(9);
    add_act("say I hope my family is okay.");
    add_act("say The life of a fisherman is not an easy one!");
    add_act("say Gelan is a fine place to visit, although I lived most of " +
            "my life in Port Macdunn. But now I moved to Cadu, for the "+
            "fishing is better there!");
    add_act("scratch chin");
    add_act("emote whistles a low tune, that brings to mind an image " +
      "of highland vistas.");
    add_act("emote flexes one bicep, then the other.");
    add_act("say My children are the finest in Cadu and Khalakhor!");
    add_act("say I love the smell of the ocean!");
    add_act("emote smiles broadly, for a passing second.");

    set_default_answer("I'm afraid I can't help you with that.");
    add_ask("khalakhor","say Khalakhor is my motherland, and I love " +
      "the lay of the land!",1);
    add_ask(({"lay of the land","land"}),"Rolling hills and placid " +
      "waters, such scenery is my pleasure.",1);
    add_ask(({"hills","rolling hills"}),"Just visit Khalakhor, and " +
      "you'll be sure to see them!",1);
    add_ask(({"waters","placid waters"}),"I remember them fondly " +
      "from my youth.",1);
    add_ask("children","My lads and lasses are the finest in Cadu and Port " +
      "Macdunn!",1);
    add_ask("lads","Aye, they are fine young boys!",1);
    add_ask("lasses","The prettiest young girls you've ever seen!",1);
    add_ask("ocean","say Cuan Siorriudh!",1);
    add_ask("route",
            "say I help the younger ones in a circle route "+
            "through Sparkle, Gelan, Cadu and Enchanted Garden in Terel");
    add_ask("family","say Well, my family is not that well off, so " +
      "I have to ferry passengers as a way to make some extra " +
      "money.",1);
    add_ask(({"port macdunn","port","macdunn"}),"say I was born there " +
      "and I will die there, unless I die at sea!",1);
    add_ask(({"gelan","calia"}),"say A fair place to visit, although " +
      "it tends to befuddle me with its complexities.",1);
    add_ask(({"sparkle","hub"}),"say A huge port it is, I cannot get " +
      "used navigating through it.",1);
    add_ask(({"cadu","nyreese"}),"say We just moved there. The fishing " +
      "is much better there. It looks very friendly.",1);
    add_ask(({"enchanted garden","terel"}),"say What a beautiful forest, "+
      "I should disembark and walk it one day.",1);
    add_ask("life","say We live and we die, so whatever you do, " +
      "make sure you enjoy it!",1);
    add_ask("fish","say The fish aren't catching these days, all I get " +
      "are a few lousy sea urchins!",1);
    add_ask(({"urchins","urchin","sea urchins","sea urchin"}),
      "say Take as many as you want if there are any left in the " +
      "net! I've no use for them.",1);
    add_ask(({"quest","task"}),"say My only quest is a personal one, " +
      "and that is to support my family!",1);

}

public void
arm_me()
{
    object wep, arm1, arm2;

    wep=clone_object(DIRK);
    wep->move(this_object());
    arm1=clone_object(SHIRT);
    arm1->move(this_object());
    arm2=clone_object(BREECHES);
    arm2->move(this_object());
    command("wield all");
    command("wear all");
}

public void
add_introduced(string who)
{
    kb_add_introduced(who);
}

public void
init_living()
{
    ::init_living();
    kb_init_living();
}

public void
enter_env(object to, object from)
{
    ::enter_env(to, from);
    kb_enter_env(to, from);
}
