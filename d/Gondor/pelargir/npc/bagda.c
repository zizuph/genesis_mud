/* a close duplicate of the shopkeeper in MT

 * Gwyneth 4 November 2000 - Replaced ~elessar/lib/goodkill.h with
 *                           /d/Gondor/common/lib/logkill.c
 */
inherit "/d/Gondor/pelargir/npc/pelargir_npc";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/lib/logkill.c"

void
create_pelargir_npc() 
{
    int     rnd1 = random(11);

    set_living_name("bagda");
    set_name("bagda");
    add_name(({"owner", "shopkeeper", "shopowner"}));
    set_race_name("human");
    set_adj(({"scrawny","old"}));
     set_long("This is Bagda, the weapons and armour "+
      "collector of Pelargir.\n");
    default_config_npc(32 + rnd1);
    set_base_stat(SS_CON,75);

    set_skill(SS_WEP_SWORD, 80 + rnd1);
    set_skill(SS_DEFENCE,   60 + rnd1);
    set_skill(SS_PARRY,     50 + rnd1);
    set_skill(SS_AWARENESS, 50 + rnd1);

    set_alignment(50 + rnd1 * 10);

    set_chat_time(12);
    add_chat("Can I help you?");
    add_chat("Welcome to my shop!");
    add_chat("They call me Bagda.");
    add_chat("Have you got anything nice to sell?");
    add_chat("Perhaps you want to buy an excellent weapon?");
    add_cchat("Get out of here, you thieving scoundrel!");
    add_cchat("You won't get away with this, you know!");
    add_cchat("Guards! Help!");

}

void
arm_me()
{
    FIX_EUID
    clone_object(WEP_DIR+"ssword")->move(TO);
    command("wield sword");
    clone_object(ARM_DIR+"studlarm")->move(TO);
    command("wear armour");
}

void
intro_me(object who)
{
    if (!present(who) || !CAN_SEE(TO, who) || !CAN_SEE_IN_ROOM(TO))
        return;

    command("say My name is Bagda. I run the best shop in Pelargir! ");
    command("present me");
}

void
add_introduced(string name)
{
    object  who;

    if (!objectp(who = find_player(name)))
        return;
    set_alarm(2.0, 0.0, &intro_me(who));
}

