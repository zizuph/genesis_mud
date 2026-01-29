/* File:          /d/Khalakhor/ship/macdunn/ashlagh/captain.c
 * Creator:       Zima (copied from Teth)
 * Date:          June 16, 1998
 * Purpose:       This is the captain of the Macdunn-Baile Ashlagh ship
 * Related Files: /d/Khalakhor/ship/macdunn/
 *                /d/Khalakhor/ship/macdunn/ashlagh/
 *                /d/Khalakhor/open/SHIPLINES
 * Comments:
 * Ported by Tapakah to the new ship system 04/2009
 */

#pragma save_binary
#pragma strict_types

#include <stdproperties.h>
#include <money.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Genesis/gsl_ships/ships.h"
#include "../ship.h"

inherit STDCAPTAIN;
inherit "/d/Khalakhor/lib/knowledge_base";

public void
create_captain ()
{
  ::create_captain();
  set_name("leabag"); // flounder
  add_name("_leabag_");
  add_name("captain");
  add_name("ashlish");
  set_living_name("leabag");
  set_race_name("elf");
  add_adj(({"calm","blonde-bearded"}));
  set_title("Ashlish, Captain of the Aigne Deas");
  set_long("This blonde-bearded ship captain is one of the calmest "+
           "you have ever met, the normal dangers of ocean-going not "+
           "affecting his serene and peaceful face. He seems to be a quiet "+
           "but very adept fellow who loves his work, sailing this modest "+
           "but impressive ship, the Aigne Deas.\n");
  
  set_stats(({ 90, 85, 90, 80, 86, 90 }));
  heal_hp(10000);
  set_skill(SS_AWARENESS, 62);
  set_skill(SS_WEP_SWORD, 55);
  set_skill(SS_DEFENCE, 73);
  set_skill(SS_PARRY, 40);
  set_size_descs("tall","thin");
  
  seteuid(getuid());
  MONEY_MAKE_GC(random(5) + 3)->move(this_object());
  MONEY_MAKE_CC(random(100) + 100)->move(this_object());
  
  add_prop(NPC_I_NO_LOOKS, 1);
  
  set_act_time(15);
  add_act("emote gazes out over the waters as if beholding a lover.");
  add_act("emote lovingly admires his ship as if it were his daughter.");
  add_act("say The seas, the seas, they call to me.");
  add_act("emote rubs his blonde-bearded chin gazing at the skies.");
  add_act("emote breathes in the salt air deeply.");
  add_act("emote smiles in satisfaction.");
  add_act("emote hums an old celtic tune.");
  add_act("say The south seas are magical.");
  
  set_default_answer("I'm not sure about that.");
  add_ask("khalakhor","say Ah, me beloved Khalakhor. The mainland is " +
          "fairly safe, but some of the islands I wouldn't dock at.",1);
  add_ask(({"mainland","continent","main continent"}),"say Stay out of " +
          "the northlands and you'll be fine.",1);
  add_ask(({"islands","surrounding islands"}),"say Powerful beings "+
          "there. Not sure they're mortal.",1);
  add_ask("beings","say Don't worry, we'll not be landing on the "+
          "islands if the winds are with us.",1);
  add_ask("ocean","say The ocean is like a wife to me, my best friend.",1);
  add_ask(({"north","northlands"}),
          "say Evil abounds in the north. Pray ye never wreck there.",1);
  add_ask("route","say Port Macdunn to Baile Aslagh and back, around "+
          "the southeastern speir of Khalakhor.",1);
  add_ask(({"Baile Ashlagh","baile ashlagh"}),
          "say Its a small village but it sees alot of traffic, being "+
          "the port to Ardmaugh and all.",1);
  add_ask(({"ardmaugh","Ardmaugh","holy city"}),
          "say It be to the west of Baile Ashlagh, deep inland. "+
          "Few have ever been there.",1);
  add_ask(({"port macdunn","port","macdunn","town"}),
          "say The big city on the west coast of the speir.",1);
  add_ask(({"aigne deas","boat","ship"}),"say Aye, she's beautiful "+
          "isn't she? Like me daughter she is.",1);
  add_ask("destination","@@query_destination",1);
  add_ask(({"Kheldour","kheldour"}),
          "say Kheldour is an elven city at the tip of the southeastern "+
          "speir of the continent of Khalakhor. Its ports are closed.",1);
  add_ask(({"Rhemouth","rhemouth"}),
          "say Rhemouth is a dwarven city on the east coast of the meidh. "+
          "Its a very old and dangerous place, where chaos and order "+
          "battle constantly.",1);
  add_ask(({"meidh","speir"}),
          "say The continent is formed of three speirs, like pinwheel, "+
          "which radiate from the central highlands of the meidh.",1);
  add_ask("isles","say You never know what you'll find on the isles.",1);
  
}

public void arm_me()
{
    object wep, arm1, arm2, arm3;

    wep=clone_object(DOMAIN_OBJS_DIR + "common/wep/claymore");
    wep->move(this_object());
    arm1=clone_object(DOMAIN_OBJS_DIR + "common/arm/vest_hard_leather");
    arm1->move(this_object());
    arm2=clone_object(DOMAIN_OBJS_DIR + "common/arm/breeches");
    arm2->move(this_object());
    arm3=clone_object(DOMAIN_OBJS_DIR + "common/arm/belt");
    arm3->move(this_object());
    command("wield all");
    command("wear all");
    command("lace vest");
}

public void add_introduced(string who)
{
    kb_add_introduced(who);
}

public void init_living()
{
    ::init_living();
    kb_init_living();
}

public void enter_env(object to, object from)
{
    ::enter_env(to, from);
    kb_enter_env(to, from);
}
