/* This file is /d/Gondor/morgul/npc/drunk.c           */
/*                                                     */
/* Olorin, July 1993                                   */
#pragma strict_types

inherit "/d/Gondor/morgul/npc/ithil_man.c";

#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

#define WEP_ARRAY1 ({WEP_DIR + "knife"})
#define ARM_ARRAY1 ({ARM_DIR + "ltrousers", ARM_DIR + "fjacket"})
#define ARM_ARRAY2 ({ })

public void
create_ithil_man()
{
  add_name("drunk");
  set_long(BSN("A thick swarthy man from Harad or Khand in the " +
    "south. He looks like he has had a drink or two too many. "));
    
  set_base_stat(SS_DIS, 35+random(10));
  set_base_stat(SS_DIS, 15+random(5));

  set_chat_time(10);
  add_chat("We will massacre those damned dunedain!");
  add_chat("First Ithilien, then Gondor, and finally Aman!");
  add_chat("He, he, Sauron's a fine chap!");
  add_chat("Cheers! To Lugburz!");
  add_chat("I wish I could go to fight those rangers!");
  add_chat("You know, orcs stink!");
  add_chat("We will kill everyone! And then we will rule the world!");

  set_act_time(15);
  add_act("hiccup");
  add_act("drink beer");
  add_act("buy beer");

  set_cchat_time(5+random(10));
}

static void
set_arm_arrays()
{
  ::set_arm_arrays();
  Wep1 = WEP_ARRAY1;
  Arm1 = ARM_ARRAY1;
  Arm2 = ARM_ARRAY2;
}

public string
get_money() 
{
   MONEY_MAKE_CC( 30 + random(11))->move(TO);
   MONEY_MAKE_SC(  5 + random( 6))->move(TO);
   command("emote searches his pockets for coins.");
   return "";
}

