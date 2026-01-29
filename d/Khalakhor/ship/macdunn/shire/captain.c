/* File:          /d/Khalakhor/ship/macdunn/shire/captain.c
 * Creator:       Teth
 * Date:          December 2, 1997
 * Modifications: 
 * Purpose:       This is the captain of the Macdunn-Grey Havens 
 *                or, the Khalakhor-Shire ship.
 * Related Files: /d/Khalakhor/ship/macdunn/
 *                /d/Khalakhor/ship/macdunn/shire/
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
#include <const.h>
#include <ss_types.h>
#include <macros.h>

public void
create_monster()
{
    set_name("isoelte");
    add_name("_isoelte_");
    add_name("captain");
    add_name("llellyn");
    set_living_name("isoelte");
    set_race_name("human");
    add_adj("lithe");
    add_adj("black-haired");
    set_gender(G_FEMALE);
    set_title("Llellyn of the Corran");
    set_long("This woman is clearly proud of her career " +
      "as a captain. Her lithe body suggests years of hard " +
      "physical work, while her weathered features are " +
      "typical of those who work outdoors. Long black hair " +
      "cascades past her shoulders.\n");

    set_stats(({ 90, 90, 100, 89, 90, 85 }));
    heal_hp(10000);
    set_skill(SS_AWARENESS, 62);
    set_skill(SS_WEP_KNIFE, 30);
    set_skill(SS_DEFENCE, 34);
    set_skill(SS_PARRY, 56);
    set_size_descs("tall","lean");

    seteuid(getuid());
    MONEY_MAKE_GC(random(5) + 3)->move(this_object());
    MONEY_MAKE_SC(random(20) + 12)->move(this_object());

    add_prop(NPC_I_NO_LOOKS, 1);

    set_act_time(9);
    add_act("say I've never had any trouble while sailing this route.");
    add_act("say My only love is the sea!");
    add_act("say The Shire is so quaint, unlike the harsh realities " +
      "of Khalakhor.");
    add_act("emote stretches like a cat.");
    add_act("emote hums a fey tune to herself.");
    add_act("emote smiles contentedly.");
    add_act("say Others seek fortune, I only seek the freedom of the sea.");

    set_default_answer("I'm not able to help you with that question.");
    add_ask("trouble","say You know, the kind where I'm forced " +
      "to bear arms.",1);
    add_ask(({"ocean","sea"}),"say Indeed, I love Cuan Siorriudh, it " +
      "has never disappointed me like some of my fellow beings.",1);
    add_ask("disappointment","say The details of my life are no " +
      "concern of yours.",1);
    add_ask("love","emote raises her eyebrow inquisitively.",1);
    add_ask(({"The Shire","the Shire","Shire","shire","the shire"}),
      "say The Shire is home to many little folk, quite a friendly " +
      "people.",1);
    add_ask(({"folk","little folk","friendly people"}),"say Hobbits, " +
      "I believe they are called.",1);
    add_ask("hobbits","say Interesting little folk.",1);
    add_ask(({"realities","harsh realities"}),"say Khalakhor isn't " +
      "a place for those who are faint of heart, especially the " +
      "northern regions.",1);
    add_ask(({"northern regions","north","regions"}),"say Be careful " +
      "if you venture there.",1);
    add_ask("khalakhor","say It's an extensive land, although much " +
      "needs to be made accessible yet.",1);
    add_ask("route","say I sail between the villages of Port Macdunn, " +
      "and Grey Havens.",1);
    add_ask(({"macdunn","port macdunn"}),"say Quite a pleasant town.",1);
    add_ask("fortune","say My fortune is that I am able to enjoy the " +
      "sea.",1);
    add_ask("freedom","say One can't be any richer if one is truly " +
      "free.",1);
    add_ask(({"quest","task"}),"say I don't require anything of " +
      "anyone!",1);
    add_ask("destination","@@query_destination",1); 

    set_ticket(TICKET);
    set_price(PRICE);
}

public int
buy(string str)
{
    if (this_player()->query_average_stat() < 20)
    {
        command("say to " + OB_NAME(this_player()) + " No need for " +
          "you to pay me. The young ride for free on my ship.\n");
        notify_fail("");
        return 0;
    }

    return ::buy(str);
}

public string
query_destination()
{
    if((file_name(this_object()->query_prop(LIVE_O_LAST_ROOM)))
      == ("/d/Khalakhor/ship/macdunn/pier12"))
    {
        return ("say We are sailing to Grey Havens!");
    }
    if((file_name(this_object()->query_prop(LIVE_O_LAST_ROOM)))
      == ("/d/Shire/common/greyhaven/pier7"))
    {
        return ("say We are sailing to Port Macdunn!");
    }
    else return ("say We are sailing the " +
          "Grey Havens and Port Macdunn route today!");
}

public void
arm_me()
{
    object wep, arm1, arm2;

    wep=clone_object(PARENT + "common/wep/dirk");
    wep->move(this_object());
    arm1=clone_object(PARENT + "common/arm/vest_hard_leather");
    arm1->move(this_object());
    arm2=clone_object(PARENT + "common/arm/bracers_hard_leather");
    arm2->move(this_object());
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
