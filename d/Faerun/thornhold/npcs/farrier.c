/*
 * The Farrier of Thornhold
 * Finwe, October 2007
 * Modded by Gnim June 2016
 */

inherit "/std/monster";
inherit "/d/Faerun/smithy/base_blacksmith";

/* Inherit this file to allow the npc to react to introductions */
inherit "/d/Genesis/lib/intro";

#include <const.h>   // for G_MALE
#include <macros.h>  // forOB_NAME
#include <ss_types.h>
#include <wa_types.h>

void
create_monster()
{
    //if (!IS_CLONE) return;
    seteuid(getuid());

    set_name("bodric");
    add_name(({"farrier", "stoneshaft", "bodrick"}));
    set_living_name("bodric");
    set_title("Stoneshaft, the Farrier of Thornhold");
    set_race_name("dwarf");
    set_adj(({"stout", "callous-fingered"}));
    set_long("This is the farrier of Thornhold. He is muscular from " +
             "years of forging horseshoes and tack. His beared is coarse " +
             "and grey, and his hands are calloused from long hours of work. " +
             "You may use <help farrier> for more information on how he can help you.\n");
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

int
action_smithy_help(string str)
{
    string s;
    object tp = this_player();

    seteuid(getuid());

    switch(str)
    {
        case "farrier":
            tp->catch_msg("The farrier looks up at points at the sign.\n");
            return 1;
            break;
        default:
            return 0;
            break;
    }
    return 1;
}

void
init_living()
{
    ::init_living();
    init_smithy();

}
