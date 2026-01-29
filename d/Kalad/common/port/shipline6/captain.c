/*********************************************************************
 * - captain.c                                                     - *
 * - shipline Raumdor-Kabal                                        - *
 * - Recoded by Damaris 5/2003                                     - *
 *********************************************************************/
#pragma save_binary
#pragma strict_types
inherit "/d/Kalad/lib/intro";
#include "../default.h"
#include "defs.h"
#include <stdproperties.h>
#include <money.h>
#include <ss_types.h>
#include <macros.h> 
inherit "/d/Genesis/ship/captain";



public void
create_monster()
{
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
      "now I run this boat from Kabal to the docks of Raumdor, never "+
      "to set foot on that accursed land again...\n");
    set_act_time(3);
    add_act("emote whispers to you: The undead are growing in numbers"+
      " in Raumdor...");
    add_act("say I dare never travel onto Raumdor anymore...");
    add_act("say Beware of the night if you go to Raumdor...");
    add_act("emote thinks of retiring soon in Kabal.");
    add_act("say I shall never return to Raumdor again...");
    set_title("the Captain of the Dreadnaught");
    add_ask("destination","@@query_destination",1);
    set_ticket(TICKET);
    set_price(PRICE);
}
 
public int buy(string str)
{
    if (this_player()->query_average_stat() < 24)
       {
       command("say to " + OB_NAME(this_player()) + " No need to pay. "+
               "Little ones ride for free.");
       notify_fail("");
       return 0;
       }
    return ::buy(str);
}
 
public string query_destination()
{
    if((file_name(this_object()->query_prop(LIVE_O_LAST_ROOM)))
      == ("/d/Kalad/common/port/s104"))
    {
        return ("say We're headed to Kabal Port District.");
    }
    if((file_name(this_object()->query_prop(LIVE_O_LAST_ROOM)))
      == ("/d/Kalad/common/raum/wforest/dock3"))
    {
        return ("say We're headed to Raumdor.");
    }
    else return ("say I'm not sure matey, but I think we're headed "+
                 "to Kabal Port District or Raumdor.");
}
 
