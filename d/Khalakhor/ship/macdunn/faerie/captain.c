/* File:          /d/Khalakhor/ship/macdunn/faerie/captain.c
 * Creator:       Teth
 * Date:          November 16, 1997
 * Purpose:       This is the captain of the Macdunn-Faerie, or 
 *                Khalakhor-Faerie ship.
 * Related Files: /d/Khalakhor/ship/macdunn/
 *                /d/Khalakhor/ship/macdunn/faerie/
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
    set_name("gwynyd");
    add_name("_gwynyd_");
    add_name("captain");
    add_name("mcllwain");
    set_living_name("gwynyd");
    set_race_name("human");
    add_adj(({"tall","unkempt"}));
    set_title("Mcllwain, Captain of the Fiu Alladh");
    set_long("This tall ship captain apparently has his mind " +
      "elsewhere. His brown hair is uncombed, and it appears " +
      "that he has not shaved properly for days. This is in " +
      "stark contrast to the near-magical cleanliness of the " +
      "boat he captains, the Fiu Alladh.\n");

    set_stats(({ 90, 85, 90, 80, 86, 90 }));
    heal_hp(10000);
    set_skill(SS_AWARENESS, 62);
    set_skill(SS_WEP_SWORD, 55);
    set_skill(SS_DEFENCE, 73);
    set_skill(SS_PARRY, 40);
    set_size_descs("tall","normal");

    seteuid(getuid());
    MONEY_MAKE_GC(random(5) + 3)->move(this_object());
    MONEY_MAKE_CC(random(100) + 100)->move(this_object());

    add_prop(NPC_I_NO_LOOKS, 1);

    set_act_time(9);
    add_act("emote shudders at a personal thought.");
    add_act("shout The things I've seen would turn any man mad!");
    add_act("say They still call to me...");
    add_act("emote rubs his forehead, as if he had a headache.");
    add_act("emote stares into the distance with a vacant gaze.");
    add_act("say I don't understand why...");
    add_act("say The ocean gives me time to think...");
    add_act("emote sighs deeply.");

    set_default_answer("I... don't know.");
    add_ask("khalakhor","say Khalakhor... the main continent is " +
      "safe enough... but the surrounding islands...",1);
    add_ask(({"continent","main continent"}),"say If you avoid " +
      "the north, you should be safe...",1);
    add_ask(({"islands","surrounding islands"}),"say That's where... " +
      "That's where I saw them...",1);
    add_ask("ocean","say The ocean is safe... They can't cross " +
      "the water...",1);
    add_ask("north","say Evil has laid waste there...",1);
    add_ask("route","say Port Macdunn and Faerie...",1);
    add_ask("faerie","say I never stay too long there, it reminds me...",1);
    add_ask(({"port macdunn","port","macdunn","town"}),"say A safe " +
      "haven from they that haunt me...",1);
    add_ask(({"fiu alladh","boat","ship"}),"say My boat... my boat...",1);
    add_ask("them","emote stares vacantly into the distance, and " +
      "refuses to answer.",1);
    add_ask("memories","shout Make them go away!",1);
    add_ask("destination","@@query_destination",1); 

    set_ticket(TICKET);
    set_price(PRICE);
}

public int
buy(string str)
{
    if (this_player()->query_average_stat() < 20)
    {
        command("say to " + OB_NAME(this_player()) + " No... " +
          "The innocent need not pay...\n");
    notify_fail("");
    return 0;
}

return ::buy(str);
}

public string
query_destination()
{
    if((file_name(this_object()->query_prop(LIVE_O_LAST_ROOM)))
      == ("/d/Khalakhor/ship/macdunn/pier10"))
    {
        return ("say Faerie! Faerie! Faerie! Faerie...");
    }
    if((file_name(this_object()->query_prop(LIVE_O_LAST_ROOM)))
      == ("/d/Genesis/start/elf/room/cove_5"))
    {
        return ("say I think we're headed to Port Macdunn...");
    }
    else return ("say Hmm? Where am I going? I don't know... " +
          "I often sail between Port Macdunn and Faerie, though...");
}

public void
arm_me()
{
    object wep, arm1, arm2, arm3;

    wep=clone_object(PARENT + "common/wep/claymore");
    wep->move(this_object());
    arm1=clone_object(PARENT + "common/arm/vest_hard_leather");
    arm1->move(this_object());
    arm2=clone_object(PARENT + "common/arm/breeches");
    arm2->move(this_object());
    arm3=clone_object(PARENT + "common/arm/belt");
    arm3->move(this_object());
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
