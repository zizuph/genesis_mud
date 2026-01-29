inherit "/d/Emerald/lib/armourer";
inherit "/d/Emerald/std/emerald_monster";

#include <wa_types.h>
#include <ss_types.h>
#include <stdproperties.h>

nomask void
create_emerald_monster()
{
    add_armourer_material("copper",  200);
    add_armourer_material("bronze",  300);
    add_armourer_material("iron",    400);
    add_armourer_material("steel",   550);
    add_armourer_material("mithril", 850); 
    add_armourer_armour("helmet",  180, 3);
    add_armourer_armour("greaves", 140, 2);
    add_armourer_armour("bracers", 140, 2);
    add_armourer_armour("body-armour", 250, 5);
    add_armourer_armour("shield", 200, 4);

    set_armourer_armour_file("/d/Emerald/telberin/arm/armourer_armour");

    create_armourer();

    craftsman_add_attribute("enchantment", ({ "none", "lightness",
        "durability", "recoverability" }));

    set_name(({ "eril", "eril_the_smith" }));
    set_race_name("elf");
    set_adj(({ "weathered", "muscular" }));
    set_title("Master Smith of Telberin");

    set_long("Eril is the famous Master Smith of Telberin.  Having served " +
        "the royals of Telberin for centuries, he now sells some of his " +
        "works to adventurers and the common citizens of Emerald.\n");

    set_stats(({ 120, 130, 100, 120, 120, 100 }));

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
}

void
init_living()
{
    ::init_living();
    armourer_init();
}

public int
craftsman_query_completion_time(object who, mapping attr_map)
{
    return ::craftsman_query_completion_time(who, attr_map) +
        ((attr_map["enchantment"] != "none") ? 250 : 0);
}

public int
cost_mod(object who, object item, mapping attrs)
{
    if (this_player()->query_race_name() == "elf")
    {
        return 90;
    }

    return 100;
}

public int
craftsman_calc_item_cost(object who, object item, mapping attrs)
{
    int cost;

    cost = ::craftsman_calc_item_cost(who, item, attrs) *
        cost_mod(who, item, attrs) / 100;

    if (attrs["enchantment"] != "none")
    {
        cost += 3000;
    }

    return cost * cost_mod(who, item, attrs) / 100;
}

public void
craftsman_config_attributes(string *attrs, object who, mapping attr_map)
{
    /* Don't prompt for an enchantment unless we're using mithril */
    if (sizeof(attrs) && (attrs[0] == "enchantment") &&
        (attr_map["material"] != "mithril"))
    {
        craftsman_set_attribute(who, attrs, attr_map, "none");
        return;
    }
        
    ::craftsman_config_attributes(attrs, who, attr_map);
}

public void
craftsman_configure_item(object who, object item, mapping attrs)
{
    item->config_me(attrs["type"], attrs["material"], attrs["enchantment"]);
}
