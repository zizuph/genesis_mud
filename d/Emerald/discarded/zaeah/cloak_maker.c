inherit "/d/Genesis/lib/craftsman";
inherit "/d/Emerald/std/emerald_monster";

#include <ss_types.h>
#include <stdproperties.h>

void create_emerald_monster()
{
    set_name(({ "craftsman", "npc" }));

    set_race_name("elf");

    add_adj("well-dressed");
    add_adj("young");

    add_prop(NPC_I_NO_RUN_AWAY, 1);
    remove_prop(NPC_M_NO_ACCEPT_GIVE);

    set_long("An elegantly dressed, young elf, he specializes in creating " +
        "custom-made cloaks for the wealthy and fashionable of Telberin; " +
        "though, he sometimes fills orders from other customers for an " +
        "extra fee.\n");

    set_stats(({ 40, 60, 30, 90, 50, 50 }));

    set_skill(SS_UNARM_COMBAT, 30);
    set_skill(SS_DEFENSE, 30);
    set_skill(SS_AWARENESS, 70);

    set_exp_factor(50); // offset the relatively high mental stats and poor combat

    add_ask(({ "cloak", "cloaks", "about cloak", "about cloaks", "about ordering",
        "ordering", "about ordering cloak", "about ordering cloaks", "about buying",
        "about buying cloak", "about buying cloaks", "about fabric", "about cloth",
        "ordering cloak", "ordering cloaks", "buying cloak", "buying cloaks",
        "buying", "fabric", "fabrics", "cloth", "cloths" }),
        "say Unfortunately my fabric orders have not come in yet, " +
        "so I cannot take any orders unless you can provide the fabric " +
        "yourself.", 1);
         
    // possible names for the item sold
    craftsman_set_sold_item_names(({ "cloak" }));

    // the file for the item to clone
    craftsman_set_item_file("/d/Emerald/common/guild/vamp/obj/cloak");

    // time in seconds to complete creation of the item
    craftsman_set_time_to_complete(10);

    // set the amount we charge for an item (in cc)
    craftsman_set_item_cost(10);

    craftsman_add_attribute("material", ({ "leather", "silk", "velvet" }));
    craftsman_add_attribute("color", ({ "ivory", "purple", "grey" }));
    craftsman_add_attribute("quality", ({ "crude", "splendid", "shoddy" }));
}

void init_living()
{
    ::init_living();

    /* add the craftsman's commands */
    craftsman_init();
}

void craftsman_configure_item(object who, object ob, mapping attrs)
{
    ob->config_cloak(({ attrs["color"] }));
}

void craftsman_purchase_hook(object who, string str)
{
    command("say to " + who->query_real_name() + " Unfortunately my " +
        "fabric orders have not come in yet, " +
        "so I cannot take any orders unless you can provide the fabric " +
        "yourself.");
}

int craftsman_config_completed_hook(object who, mapping attr_map, int time)
{
    craftsman_notify_completion_time_hook(who, time);
    craftsman_notify_cost_hook(who, attr_map);
    craftsman_notify_cancel_hook(who);
    craftsman_notify_hold_time_hook(who);
}

void exa_fabric(object who, object ob)
{
    string color;

    command("emote examines the fabric.");
    command("smile");

    if (ob->id("_vamp_fabric_red"))
    {
        color = "blood-red";
    }
    else
    {
        color = "jet-black";
    }

    ob->remove_object();
    craftsman_completed_config(who, ([ "color" : color ]));
}

int prevent_enter(object ob)
{
    if (this_player() && present(this_player(), environment(this_object())))
    {
	if (!(ob->id("fabric") || ob->id("cloth")))
	{
	    command("say Sorry, I cannot accept that.");
	    return 1;
	}
    
	if (ob->id("_vamp_fabric"))
	{
	    set_alarm(0.5, 0.0, &exa_fabric(this_player(), ob));
	    return 0;
	}
    
	command("say Sorry, I cannot work with this fabric.");
	return 1;
    }

    return 0;
}
