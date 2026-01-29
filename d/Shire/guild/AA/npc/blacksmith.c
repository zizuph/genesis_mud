/*
 * The Blacksmith of Angmar
 * Finwe, October 2007
 */

inherit "/std/monster";
inherit "/d/Shire/blacksmith/base_blacksmith";

/* Inherit this file to allow the npc to react to introductions */
inherit "/d/Genesis/lib/intro";

#include <const.h>   // for G_MALE
#include <macros.h>  // for OB_NAME

void
create_monster()
{
    seteuid(getuid());

    set_name("aruzagar");
    set_race_name("human");
    add_name("blacksmith");
    add_name("_aa_blacksmith");
    set_title("Aruzagar, Master Blacksmith of the Army of Angmar");
    set_adj("muscular");
    set_adj("large");
    set_long("This is Aruzagar, Master Blacksmith of the Army of Angmar. " +
        "He is muscular from years of forging and repairing weapons " +
        "and armours. His dark hair is peppered with gray, and his " +
        "face is smudged with dirt. Use <help blacksmith> for more " +
        "information on how he can help you.\n");

    set_act_time(3);
    set_chat_time(3);

    add_act("emote hammers a piece of metal on the large anvil.");
    add_act("emote wipes the sweat off his brow.");
    add_act("emote looks up at you.");
    add_act("emote plunges a piece of metal into a trough of cold water.");
    add_act("emote pumps the bellow furiously.");
    
    add_chat("The Army depends on my skills.");
    add_chat("Whatcha doing here?");
    add_chat("Do you need something?");
    add_chat("I will sharpen weapons and repair armours--for a fee.");
    add_chat("Nothing will defeat the Army.");

    set_gender(G_MALE);
    set_stats(({ 100, 100, 100, 100, 100, 100 }));

    config_default_trade();
}

void
greet(object who)
{
    command("say Nice to meet you again, " + who->query_name() + "!");
    command("smile");
}

void
introduce(object who)
{
    command("introduce myself to " + OB_NAME(who));
    command("say A pleasure to meet you, " + who->query_name() + "!\n");
}

void
init_living()
{
    ::init_living();
    init_smithy();

}
