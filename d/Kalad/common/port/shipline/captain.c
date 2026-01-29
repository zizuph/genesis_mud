/*********************************************************************
 * - captain.c                                                     - *
 * - shipline Gont-Kabal                                           - *
 * - Candelis                                                      - *
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
    set_name("logaan");
    add_name("_logaan_");
    add_name("captain");
    add_name("Leneer");
    set_living_name("logaan");
    set_race_name("human");
    add_adj(({"glaring","suspicious"}));
    set_title("Leneer, the Deadly Corsair");
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
    add_act("emote gazes out over the water lovingly.");
    add_act("emote smiles admiring at his ship.");
    add_act("emote sighs deeply looking out over the sea.");
    add_act("emote smiles in satisfaction.");
    add_act("say The seas, the seas, they call to me."); 
    add_ask(({"kabal"}),
      "say Kabal port district isn't as busy as it used to be.",1);
    add_ask(({"ocean"}),
      "say The ocean is like a wife, lover, sister, my best friend.",1);
    add_ask(({"route"}),
      "say Kabal Port District to Gont and back.",1);
    add_ask(({"port gont","port","gont","town"}),
      "say Gont is an interesting place to visit.",1);
    add_ask(({"candelis","boat","ship"}),
      "say Aye, she's beautiful isn't she? Like me lover she is.",1);
    add_ask("destination","@@query_destination",1);
    set_ticket(TICKET);
    set_price(PRICE);
}
 
public int buy(string str)
{
    if (this_player()->query_average_stat() < 20)
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
      == ("/d/Kalad/common/port/shipline/pier"))
    {
        return ("say We're headed to Gont.");
    }
    if((file_name(this_object()->query_prop(LIVE_O_LAST_ROOM)))
      == ("/d/Earthsea/gont/gont_city/rooms/north_pier1"))
    {
        return ("say We're headed to Kabal Port District.");
    }
    else return ("say I'm not sure matey, but I think we're headed "+
                 "to Kabal Port District or Gont.");
}
 
