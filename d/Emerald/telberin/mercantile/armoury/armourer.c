/*
 *  /d/Emerald/telberin/mercantile/armoury/armourer.c
 *
 *  This is Eril the Armourer, who offers his wares in the city
 *  of Telberin in Emerald.
 *
 *  Copyright (c) ??? by Shiva
 */
inherit "/d/Emerald/lib/armourer";
inherit "/d/Emerald/telberin/npc/telberin_elf";
inherit "/d/Genesis/lib/intro";

#include <wa_types.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

public mixed do_act();

/*
 * Function name:        create_telberin_elf
 * Description  :        set up the npc
 */
public void
create_telberin_elf()
{
    add_armourer_material("copper",  200);
    add_armourer_material("bronze",  300);
    add_armourer_material("iron",    400);
    add_armourer_material("steel",   550);
    add_armourer_material("mithril", 850); 
    add_armourer_armour("helmet",  90, 3);
    add_armourer_armour("greaves", 70, 2);
    add_armourer_armour("bracers", 70, 2);
    add_armourer_armour("body-armour", 150, 5);
    add_armourer_armour("shield", 100, 4);

    create_armourer();

    set_living_name("eril");
    set_name("eril");
    add_name( ({ "eril vordant", "smith", "smithy",
                 "armourer", "eril_the_smith" }) );
    add_adj( ({ "weathered", "muscular" }) );

    set_title("Vordant, Armourer of the Telberin Merchants"
      + " Guild");

    set_short("weathered, muscular elf");
    set_long("This is the Master Smith of Telberin. Having served"
      + " the royals of Telberin for centuries, he now sells some"
      + " of his works to adventurers and the common citizens"
      + " of Emerald.\n");

    config_elf(130);  /* He's no wimp */


    set_skill(SS_WEP_SWORD, 50);
    set_skill(SS_WEP_AXE, 50);
    set_skill(SS_WEP_KNIFE, 50);
    set_skill(SS_WEP_CLUB, 50);
    set_skill(SS_WEP_POLEARM, 50);
    set_skill(SS_UNARM_COMBAT, 30);
    set_skill(SS_AWARENESS, 60);
    
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(LIVE_I_NON_REMEMBER, 1);

    set_chat_time(20);
    add_chat("If you would like me to make you a piece of armour, " +
        "simply \"order armour\".");

    set_speak(({ "If you would like me to make you a piece of armour, " +
        "simply \"order armour\"." }));

    add_ask(({ "armour", "armours" }),
        &command("say I can make helmets, body-armour, shields, bracers, " +
        "or greaves from a variety of materials."), 1);

    add_ask(({ "material", "materials" }),
        &command("say Copper and bronze are the cheapest, but also offer " +
        "the least protection.  Iron and steel are somewhat more expensive, " +
        "but are better quality materials for making armour.  Then of " +
        "course there is mithril, which is quite a bit more expensive; " +
        "though, I can offer several enchanted types of mithril."), 1);

    add_ask(({ "enchantment", "enchantments" }),
        &command("say The only enchanted material I have is mithril.  " +
        "For an extra fee, you can get extra light mithril, extra durable " +
        "mithril, or mithril that is more likely to last through those " +
        "nasty armageddons."), 1);

    add_ask(({ "cost", "how much", "prices", "price", }),
        &command("say Well, that depends on what you want.  Try ordering, " +
        "and if you don't have the money, you can simply cancel it after " +
        "I've added up all the costs."), 1);
    add_prop(NPC_M_NO_ACCEPT_GIVE, 1);

    set_act_time(5);
    add_act(do_act, 0);
}

public mixed
do_act()
{
    int *order_ids = craftsman_query_orders_configured();
    if (sizeof(order_ids) > 0)
    {
        return ({ "emote pounds a metal sheet into shape.",
                  "emote crimps a piece of metal with pliers.",
                  "emote rivets together two metal sections.", })[random(3)];
    }

    return 0;
}

public void
armourer_configure_order(int order_id, string arg)
{
    set_armourer_armour_file(order_id, "/d/Emerald/telberin/mercantile/armoury/armourer_armour");
    craftsman_add_attribute(order_id, "enchantment", ({ "none", "lightness",
        "durability", "recoverability" }));
}

void
init_living()
{
    ::init_living();
    armourer_init();
}

public int
craftsman_query_time_to_complete(int id)
{
    mapping attrs = craftsman_query_selections(id);
    return ::craftsman_query_time_to_complete(id) +
        ((attrs["enchantment"] != "none") ? 100 : 0);
}

public int
cost_mod(object ob, int id)
{
    object owner = find_player(craftsman_query_owner(id));
    
    if (owner && (owner->query_race_name() == "elf"))
    {
        return 90;
    }

    return 100;
}

public int
craftsman_calc_item_cost(object ob, int id)
{
    int cost;
    mapping attrs = craftsman_query_selections(id);

    cost = ::craftsman_calc_item_cost(ob, id);

    if (attrs["enchantment"] != "none")
    {
        cost += 3000;
    }

    return cost * cost_mod(ob, id) / 100;
}

public void
craftsman_config_attributes(int id, int attr_number)
{
    if ((craftsman_query_attribute_name(id, attr_number) == "enchantment") &&
        (craftsman_query_selections(id)["material"] != "mithril"))
    {
        craftsman_set_attribute("none", id, attr_number);
        return;
    }
        
    ::craftsman_config_attributes(id, attr_number);
}

public void
craftsman_configure_item(object item, mapping attrs, int id)
{
    item->config_me(attrs["type"], attrs["material"], attrs["enchantment"]);
}
