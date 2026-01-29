/*********************************************************************
 * - captain.c                                                     - *
 * - shipline Raumdor-Kabal                                        - *
 * - Recoded by Damaris 5/2003                                     - *
 * - Ported to the new ship system by Tapakah, 05/2009             - *
 *********************************************************************/
#pragma save_binary
#pragma strict_types

#include <stdproperties.h>
#include <money.h>
#include <ss_types.h>
#include <macros.h> 
#include "../ship.h"
#include "/d/Genesis/gsl_ships/ships.h"

inherit STDCAPTAIN;
inherit "/d/Raumdor/lib/intro";

public void
create_captain()
{
  ::create_captain();
  set_name("doogala");
    add_name("captain");
    set_race_name("human");
    set_adj("pale");
    add_adj("slim");
    set_long("This is a very pale looking individual, he looks like he "+
      "has seen terrors only found in nightmares. His beady black eyes "+
      "dart back and forth, and he cracks his knuckles quite often.\n");
    set_alignment(500);
    set_stats(({150,175,150,125,125,150}));
    set_skill(SS_SWIM,100);
    set_skill(SS_DEFENCE,100);
    set_skill(SS_BLIND_COMBAT,100);
    set_skill(SS_UNARM_COMBAT,100);
    set_skill(SS_AWARENESS,100);
    heal_hp(15000);
    
    seteuid(getuid());
    MONEY_MAKE_GC(random(5) + 3)->move(this_object());
    MONEY_MAKE_CC(random(100) + 100)->move(this_object());

    add_prop(OBJ_M_NO_ATTACK,
      "Your futile attempts are thwarted by a mysterious enchantment "+
      "about the captain.\n");
    add_prop(OBJ_M_NO_MAGIC_ATTACK,
      "Your futile attempts are thwarted by a mysterious enchantment "+
      "about the captain.\n");
 
    add_prop(NPC_I_NO_LOOKS, 1);
 
    set_act_time(15);
    add_act("say I once lived in Drakmere, a city on the east side "+
      "of the mountains of Raumdor. The madness drove me insane, and "+
      "now I run this boat from Sparkle to the docks of Raumdor, never "+
      "to set foot on that accursed land again.\n");
    set_act_time(3);
    add_act("emote whispers: The undead are growing in numbers"+
      " in Raumdor.");
    add_act("say I dare never travel onto Raumdor anymore.");
    add_act("say Beware of the night if you go to Raumdor.");
    add_act("emote thinks of retiring soon in Kabal.");
    add_act("say I shall never attempt the journey to Drakmere again.");
    set_title("the Captain of the Dreadnaught");
    add_ask("destination","@@query_destination",1);
}
 
