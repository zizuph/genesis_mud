/*
 * Sample craftsman NPC to make dresses
 */

inherit "/d/Genesis/lib/craftsman";
inherit "/std/monster";
public void
create_monster()
{
     // possible names for the item sold
    craftsman_set_sold_item_names(({ "piwafwi" }));
        set_name("antal");
    set_race_name("elf");
    set_adj(({ "thin", "pale" }));
    set_long("This is Antal the piwafwi maker. He makes all kinds of piwafwis " +
        "for Drow. If you would like one made for you, <purchase piwafwi>\n");

}

public void
craftsman_configure_order(int order_id, string arg)
{
    // the file for the item to clone
    craftsman_set_item_file(order_id, "/d/Faerun/guilds/drow/obj/piwafwi");

    // time in seconds to complete creation of the item
    craftsman_set_time_to_complete(order_id, 30);

    // the cost of an item (in cc)
    craftsman_set_item_cost(order_id, 800);

    // attributes for the items with possible values
    craftsman_add_attribute(order_id, "material",
        ({ "silk", "satin", "velvet" }));
    craftsman_add_attribute(order_id, "color",
        ({ "black", "stone-gray", "dark", "mottled", "ivory" }));
    craftsman_add_attribute(order_id, "quality",
        ({ "excellent", "splendid", "exceptional" }));
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
//    ob->set_adj(m_values(attrs));

    switch (attrs["material"])
    {
        case "silk":
            ob->set_ac(10);
            ob->set_adj("silk");
            break;
        case "satin":
            ob->set_ac(10);
            ob->set_adj("satin");
            break;
        case "velvet":
            ob->set_ac(10);
            ob->set_adj("velvet");
            break;
    }

    switch (attrs["quality"])
    {
        case "excellent":
            ob->set_adj("excellent");
            break;
        case "splendid":
            ob->set_adj("splendid");
            break;
        case "exceptional":
            ob->set_adj("exceptional");
            break;
    }

    switch (attrs["color"])
    {
        case "black":
            ob->set_long("This is an black piwafwi.\n");
            break;
        case "stone-grey":
            ob->set_long("This is an stone-grey piwafwi.\n");
            break;
        case "dark":
            ob->set_long("This is an dark piwafwi.\n");
            break;
        case "mottled":
            ob->set_long("This is an mottled piwafwi.\n");
            break;
        case "ivory":
            ob->set_long("This is an ivory piwafwi.\n");
            break;

    }

}