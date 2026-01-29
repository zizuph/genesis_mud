inherit "/d/Genesis/lib/craftsman";

#define ARMOUR_ARR_TIME        0
#define ARMOUR_ARR_COST_FACTOR 1

static mapping armour_map = ([]);
static mapping material_map = ([]);
static string armour_file;

public void
add_armourer_material(string type, int cost)
{
    material_map[type] = cost;
}

public void
add_armourer_armour(string type, int t, int cost_factor)
{
    armour_map[type] = ({ t, cost_factor });
}

public void
set_armourer_armour_file(int order_id, string f)
{
    craftsman_set_item_file(order_id, f);
}

public void
create_armourer()
{
    craftsman_set_sold_item_names(({ "armour", "armor" }));
}

public void
armourer_configure_order(int order_id, string arg)
{
}

public void
craftsman_configure_order(int order_id, string arg)
{
    craftsman_add_attribute(order_id, "type", m_indices(armour_map));
    craftsman_add_attribute(order_id, "material", m_indices(material_map));
    armourer_configure_order(order_id, arg);
}

public void
armourer_init()
{
    craftsman_init();
}

public int
craftsman_query_time_to_complete(int id)
{
    mapping attrs = craftsman_query_selections(id);
    return armour_map[attrs["type"]][ARMOUR_ARR_TIME] + random(150);
}

public void
craftsman_configure_item(object item, mapping attrs, int id)
{
    item->config_me(attrs["type"], attrs["material"]);
}

public int
craftsman_calc_item_cost(object ob, int id)
{
    mapping attrs = craftsman_query_selections(id);
    return material_map[attrs["material"]] *
           armour_map[attrs["type"]][ARMOUR_ARR_COST_FACTOR];
}
