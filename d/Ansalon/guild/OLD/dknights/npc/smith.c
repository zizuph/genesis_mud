
#pragma save_binary
#pragma strict_types

#include "/d/Ansalon/common/defs.h"
#include "/sys/filter_funs.h"
#include "../local.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <filter_funs.h>
#include <money.h>
#include <formulas.h>

inherit AM_FILE

void
create_krynn_monster()
{
    set_race_name("human");
    set_name("zoreni");
    add_name("armourer");
    set_adj(({"skinny","tall"}));
    set_short("tall skinny female human");
    set_title("the High Armourer of Dargaard Keep"); 
    set_gender(G_FEMALE);
    set_long("This is a skinny female human, her job here is to supply the death knights with "+
             "their armour. You might want to use the 'list' command to see what pieces of "+
             "armour you can buy.\n");
    set_knight_prestige(10000);
    set_stats(({80,50,70,67,54,50}));
    set_introduce(1);
    set_alignment(-1000);
    add_prop(CONT_I_WEIGHT, 70000);
    add_prop(CONT_I_HEIGHT, 2000);
    add_prop(CONT_I_VOLUME, 65000); 
    add_prop(NPC_I_NO_RUN_AWAY, 1);

}


int
buy(string str)
{
    object who;
    int price;
    object armour, armour2, armour3, armour4, armour5, armour6, armour7;

    if (!str)
    {
        TP->catch_msg("Buy what armour piece?\n");
        return 1;
    }

    switch(str)
    {
        case "set":
        {
            armour = clone_object(GUILD_ARM + "dplatemail");
            armour2 = clone_object(GUILD_ARM + "dhelm");
            armour3 = clone_object(GUILD_ARM + "dgreaves");
            armour4 = clone_object(GUILD_ARM + "dbracers");
            armour5 = clone_object(GUILD_ARM + "dgauntlets");
            armour6 = clone_object(GUILD_ARM + "dboots");
            armour7 = clone_object(GUILD_ARM + "dcloak");
            who = TP;
            price = 1100 + random(250);
            price += 700 + random(100);
            price += 900 + random(100);
            price += 900 + random(100);
            price += 500 + random(200);
            price += 500 + random(200);
            price += 400 + random(200);

            if (!MONEY_ADD(who, -price))
            {
	              command("say I'm sorry, but you haven't got the money to pay for the armour set.\n");
        	      return 1;
            }
            who->catch_msg("You pay the price of " + price + " copper coins.\n");
            who->catch_msg("You recieve your armour set.\n");
            armour->move(TP,1);
            armour2->move(TP,1);
            armour3->move(TP,1);
            armour4->move(TP,1);
            armour5->move(TP,1);
            armour6->move(TP,1);
            armour7->move(TP,1);

            break;
        }
        case "platemail":
        {
            armour = clone_object(GUILD_ARM + "dplatemail");
            who = TP;
            price = 1100 + random(250);
            break;
        }
        case "helm":
        {
            armour = clone_object(GUILD_ARM + "dhelm");
            who = TP;
            price = 700 + random(100);
            break;
        }
        case "greaves":
        {
            armour = clone_object(GUILD_ARM + "dgreaves");
            who = TP;
            price = 900 + random(100);
            break;
        }
        case "bracers":
        {
            armour = clone_object(GUILD_ARM + "dbracers");
            who = TP;
            price = 900 + random(100);
            break;
        }
        case "gauntlets":
        {
            armour = clone_object(GUILD_ARM + "dgauntlets");
            who = TP;
            price = 500 + random(200);
            break;
        }
        case "boots":
        {
            armour = clone_object(GUILD_ARM + "dboots");
            who = TP;
            price = 500 + random(200);
            break;
        }
        case "cloak":
        {
            armour = clone_object(GUILD_ARM + "dcloak");
            who = TP;
            price = 400 + random(200);
            break;
        }
        default:
        {
            TP->catch_msg("Buy what armour piece?\n");
            return 1;
        }

        if (!MONEY_ADD(who, -price))
        {
            command("say I'm sorry, but you haven't got the money to pay for the armour piece.\n");
    	      return 1;
        }
        who->catch_msg("You pay the price of " + price + " copper coins.\n");
        who->catch_msg("You recieve your armour piece.\n");
        armour->move(TP,1);
    }
    return 1;
}



int
list(string str)
{
    if (!str)
    {
        TP->catch_msg("List what? The different armour types?\n");
        return 1;
    }

    if (str != "types" && str != "armour")
    {
        TP->catch_msg("List what? The different armour types?\n");
        return 1;
    }

    command("say I can bring you the following armour pieces:\n\n"+
            " - A blackened solamnic platemail.\n"+
            " - A blackened solamnic full helm.\n"+
            " - A shredded black cloak.\n"+
            " - A pair of blackened solamnic bracers.\n"+
            " - A pair of blackened solamnic greaves.\n"+
            " - A pair of blackened solamnic boots.\n"+
            " - A pair of blackened solamnic gauntlets.\n");
    command("say It's also possible to buy an entire set of armour.\n");
      command("say That's it, you can buy anyone of those, by using the 'buy' "+
            "command.\n");
    return 1;
}

void
init_living()
{
    add_action("buy", "buy");
    add_action("list", "list");
}
