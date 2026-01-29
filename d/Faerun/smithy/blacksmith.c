/*
 * The Blacksmith of Sparkle
 * Finwe, October 2007
 */

inherit "/std/monster";
inherit "/d/Faerun/smithy/base_blacksmith";

/* Inherit this file to allow the npc to react to introductions */
inherit "/d/Genesis/lib/intro";

#include <const.h>   // for G_MALE
#include <macros.h>  // for OB_NAME

void
create_monster()
{
    seteuid(getuid());

    set_name("derick");
    set_race_name("human");
    add_name("blacksmith");
    set_adj("muscular");
    set_adj("large");
    set_long("This is Derick, a master blacksmith. He is muscular from years of forging and repairing weapons and armours. His dark hair is peppered with gray, and his face is smudged with dirt. He looks like he has been travelling and had to stop here for a time, probably to raise money for fare. " +
    "@@help_text");
//    "Use <help smithy> for more information on how he can help you.\n");
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
