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
    set_name("bertwick");
    add_name("captain");
    set_living_name("bertwick");
    set_race_name("human");
    set_adj("dignified");
    add_adj("majestic");
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
 
    set_act_time(15);    add_act("say My ship is the finest to sail the seas.");
    add_act("emote looks lovingly at his ship.");
    add_act("say Isn't sea travel magnificent?");
    add_act("say I love the sea like I would a lover.\n");
    add_act("emote bursts into a song about the sea.\n");
    add_act("smile");
    set_title("the Captain of the Clipper Ship 'Sealover'");
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
        return ("say We're headed to the Grey Havens.");
    }
    if((file_name(this_object()->query_prop(LIVE_O_LAST_ROOM)))
      == ("/d/Earthsea/gont/gont_city/rooms/north_pier1"))
    {
        return ("say We're headed to Kabal Port District.");
    }
    else return ("say I'm not sure matey, but I think we're headed "+
                 "to Kabal Port District or Grey Havens.");
}
 
