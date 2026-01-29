/* File:          /d/Khalakhor/ship/macdunn/sparkle/captain.c
 * Creator:       Teth
 * Date:          April 21, 1997
 * Modifications: Teth, September 7, 1997 - gave him equip
 *                Teth, November 11, 1997 - added destination query
 *                Khail, November 12, 1997 - added info module
 *                Khail, November 27, 1997 - Converted to Sparkle
 *                                           to Port Macdunn line.
 * Purpose:       This is the captain of the Macdunn-Sparkle, or 
 *                Khalakhor-Sparkle ship.
 * Related Files: /d/Khalakhor/ship/macdunn/
 *                /d/Khalakhor/ship/macdunn/sparkle/
 *                /d/Khalakhor/open/SHIPLINES
 * Comments:
 */

#pragma save_binary
#pragma strict_types

inherit "/d/Genesis/ship/captain";
inherit "/d/Khalakhor/lib/knowledge_base";
#include "local.h"
#include <stdproperties.h>
#include <money.h>
#include <ss_types.h>
#include <macros.h>

public void
create_monster()
{
    set_name("burwain");
    add_name("_burwain_");
    add_name("captain");
    add_name("macadoon");
    set_living_name("burwain");
    set_race_name("human");
    set_adj("lean");
    add_adj("darkly-tanned");
    set_title("Macadoon, Captain of the Sgain Dubh");
    set_long("This man appears to spend a great deal " +
      "of time at sea. His skin is darkly tanned and " +
      "deeply lined from salt spray, and his eyes have " +
      "taken on a permanent squint from the reflection " +
      "of the sun off the water.\n");

    set_stats(({ 90, 100, 90, 60, 90, 90 }));
    heal_hp(10000);
    set_skill(SS_AWARENESS, 52);
    set_skill(SS_WEP_KNIFE, 60);
    set_skill(SS_DEFENCE, 73);
    set_skill(SS_PARRY, 35);
    set_size_descs("tall","lean");

    seteuid(getuid());
    MONEY_MAKE_GC(random(5) + 5)->move(this_object());
    MONEY_MAKE_CC(random(100) + 40)->move(this_object());

    add_prop(NPC_I_NO_LOOKS, 1);

    set_act_time(10);
    add_act("say Ahh, I love the smell of sea-spray " +
      "across the deck of the Sgain Dubh!");
    add_act("say Khalakhor's a magical land, a pity " +
      "many of the lands are unreachable.");
    add_act("say Port Macdunn's me home port, though " +
      "I've not set foot ashore further than two " +
      "paces from me dark beauty in a dog's age.");
    add_act("emote squints up and briefly examines " +
      "the sails of the Sgian Dubh.");
    add_act("emote runs his hand through his hair.");
    add_act("emote admiringly inspects the craftsmanship " +
      "of the Sgian Dubh.");

    set_default_answer("I cannae help thee with that!");
    add_ask("khalakhor","say Khalakhor! If not for me love " +
      "of the sea, I'd never leave Khalakhor. A magical " +
      "land, it is.",1);
    add_ask(({"land","magical land"}),"say Aye, enchanting to the " +
      "eye!",1);
    add_ask("magic","say Indeed, some forms do exist on Khalakhor!",1);
    add_ask(({"forms","forms of magic"}),"say I'm no priest, so " +
      "I've no idea!",1);
    add_ask("priest","say I suspect you'll find some of them.",1);
    add_ask(({"ocean","sea","unforgiving sea"}),"say Cuan Siorriudh, " +
      "of course!",1);
    add_ask("route","say I sail between Port Macdunn and " +
      "Sparkle.",1);
    add_ask("sparkle","say Strange little place Sparkle is. " +
      "Never know who'll set foot aboard your ship in " +
      "that port.",1);
    add_ask(({"port macdunn","port","macdunn","town"}),
      "say Port Macdunn's a nice enough place, though " +
      "old Fahlmar Macdunn is a far cry from the lords " +
      "of old, he do keep the village peaceful.",1);
    add_ask(({"fahlmar macdunn","fahlmar"}),"say Feel free to find " +
      "and talk with him!",1);
    add_ask("sails","say Beautiful, aren't they?",1);
    add_ask(({"boat","ship","vessel","sgian dubh"}),"say The pride of " +
      "my life!",1);
    add_ask("craftsmanship","say Crafted on the shores of Khalakhor!",1);
    add_ask(({"quest","task"}),
      "say I've nothing to challenge you with, though " +
      "some of the folks in Port Macdunn may be in need " +
      "of a hand.",1);
    add_ask("destination","@@query_destination",1); 

    set_ticket(TICKET);
    set_price(PRICE);
}

public int
buy(string str)
{
    if (this_player()->query_average_stat() < 20)
    {
        command("say to " + OB_NAME(this_player()) + " Don't worry about it" +
          ", every youngster needs to spend more time at sea. " +
          "Climb aboard!");
        notify_fail("");
        return 0;
    }

    return ::buy(str);
}

public string
query_destination()
{
    if((file_name(this_object()->query_prop(LIVE_O_LAST_ROOM)))
      == (MACDUNN_PIER))
    {
        return ("say We're on our way to Sparkle.");
    }
    if((file_name(this_object()->query_prop(LIVE_O_LAST_ROOM)))
      == (SPARKLE_PIER))
    {
        return ("say We're sailing home, to Port Macdunn.");
    }
    else return ("say The Sgian Dubh's sailing from " +
          "Sparkle to Port Macdunn, as usual.");
}

public void
arm_me()
{
    object obj;

    obj = clone_object(PARENT + "common/wep/dirk");
    obj->move(this_object());
    obj = clone_object(PARENT + "common/arm/vest_leather");
    obj->move(this_object());
    obj = clone_object(PARENT + "common/arm/breeches");
    obj->move(this_object());
    obj = clone_object(PARENT + "common/arm/bracers_leather");
    obj->move(this_object());
    command("wield all");
    command("wear all");
    command("lace vest");
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
