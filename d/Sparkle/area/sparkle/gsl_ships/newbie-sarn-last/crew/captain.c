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
    add_act("say Bree is a fine place to visit, although I lived most of " +
            "my life in Port Macdunn. But now I moved to Last, for the "+
            "fishing is better there!");
    add_act("scratch chin");
    add_act("emote whistles a low tune, that brings to mind an image " +
      "of highland vistas.");
    add_act("emote flexes one bicep, then the other.");
    add_act("say I love the smell of the ocean!");
    add_act("emote smiles broadly, for a passing second.");
    set_default_answer("I'm afraid I can't help you with that.");
    add_ask("route",
            "say When I am not fishing I take passengers on a circle route "+
            "through Sparkle, Sarn Ford, and the Town of Last in Terel.");
    add_ask("family","say Well, my family is not that well off, so " +
      "I have to ferry passengers as a way to make some extra " +
      "money.",1);
    add_ask(({"sparkle","hub"}),"say A huge port it is, I cannot get " +
      "used navigating through it.",1);
    add_ask(({"last","terel"}),"say We just moved there. The fishing " +
      "is much better there. But of course it's freezing, and the kobolds annoying.",1);
    add_ask("kobolds","say They live west of the docks in Terel. Someone should " +
      "really get rid of them. Small but nasty creatures.",1);
    add_ask(({"sarn","sarn ford"}),"say It's close to Bree, "+
      "where I sell some of my fish. Just have to be careful of the nearby orcs!",1);
    add_ask(({"orc","orcs"}),"say They seem to be a weak breed, but they sometimes bother "+
    "nearby travellers. Hopefully someone will take care of them one day.",1);
  	add_ask("life","say We live and we die, so whatever you do, " +
    "make sure you enjoy it!",1);
    add_ask("life","say We live and we die, so whatever you do, " +
      "make sure you enjoy it!",1);
    add_ask("fish","say Fishing is much better in Terel, on my passenger " +
      "route I usually only get few lousy sea urchins!",1);
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
