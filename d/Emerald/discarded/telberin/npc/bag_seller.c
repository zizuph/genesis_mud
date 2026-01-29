inherit "/std/monster";
inherit "/d/Genesis/lib/craftsman";

#include <stdproperties.h>

void create_monster()
{
    set_name("antal");
    set_race_name("elf");
    set_adj(({ "thin", "pale" }));
 
    craftsman_set_sold_item_names(({ "bag", "sack", "pack" }));
    craftsman_add_attribute("style", ({ "sack", "backpack", "waist pack" }));
    craftsman_add_attribute("size", ({ "small", "medium", "large" }));
}

void
init_living()
{
    ::init_living();
    craftsman_init();
}

public object
craftsman_clone_item(object who, mapping attrs)
{
    string style = attrs["style"];

    setuid();
    seteuid(getuid());

    return clone_object("/d/Emerald/telberin/obj/" +
        implode(explode(style, " "), "_"));
}

public void
craftsman_configure_item(object who, object item, mapping attrs)
{
    string size = attrs["size"];

    item->add_prop(CONT_I_WEIGHT, ([ "small"  : 10000,
				     "medium" : 20000,
				     "large"  : 30000, ])[size]);

    item->add_prop(CONT_I_VOLUME, ([ "small"  : 10000,
				     "medium" : 20000,
				     "large"  : 30000, ])[size]);

    item->add_prop(CONT_I_MAX_WEIGHT, ([ "small"  : 10000,
				         "medium" : 20000,
				         "large"  : 30000, ])[size]);

    item->add_prop(CONT_I_MAX_VOLUME, ([ "small"  : 10000,
				         "medium" : 20000,
				         "large"  : 30000, ])[size]);
}

public int
craftsman_query_completion_time(object who, mapping attr_map)
{
    return time() + 
        ([ "sack"       : 60,
           "backpack"   : 90,
           "waist pack" : 90 ])[attr_map["style"]];
}

