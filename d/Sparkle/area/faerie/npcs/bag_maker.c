inherit "/d/Genesis/lib/craftsman";
inherit "/std/monster";
public void
create_monster()
{
     // possible names for the item sold
    craftsman_set_sold_item_names(({ "dress" }));
        set_name("antal");
    set_race_name("elf");
    set_adj(({ "thin", "pale" }));
    set_long("This is Antal the dress maker. He makes all kinds of dresses for elves. If you would like one made for you, <purchase dress>\n");

}

public void
craftsman_configure_order(int order_id, string arg)
{
    // the file for the item to clone
    craftsman_set_item_file(order_id, "/d/Shire/common/armour/dress");

    // time in seconds to complete creation of the item
    craftsman_set_time_to_complete(order_id, 30);

    // the cost of an item (in cc)
    craftsman_set_item_cost(order_id, 800);

    // attributes for the items with possible values
    craftsman_add_attribute(order_id, "material",
        ({ "leather", "silk", "velvet" }));
    craftsman_add_attribute(order_id, "color",
        ({ "ivory", "purple", "grey" }));
    craftsman_add_attribute(order_id, "quality",
        ({ "crude", "splendid", "shoddy" }));
}

public void
init_living()
{
    ::init_living();

    // add the craftsman's commands
    craftsman_init();
}

public void
craftsman_configure_item(object ob, mapping attrs, int order_id)
{
    ob->set_adj(m_values(attrs));
    switch (attrs["material"])
    {
        case "leather":
            ob->set_ac(10);
            break;
        case "silk":
            ob->set_ac(2);
            break;
        case "velvet":
            ob->set_ac(4);
            break;
        case "wool":
            ob->set_ac(6);
            break;
    }
}