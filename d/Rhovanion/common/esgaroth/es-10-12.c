inherit "/d/Rhovanion/common/esgaroth/house.c";

create_exits()
{
    add_exit("/d/Rhovanion/common/esgaroth/es-9-12", "west");
    set_extras("This is the kitchen, there is a cutting block here with " +
        "bread crumbs scattered across it.\n");
    add_item(({ "cutting block", "block" }),
        "This cutting block is covered in breadcrumbs and scratched from " +
        "numerous knife strokes.\n");
    add_item(({ "crumbs", "breadcrumbs" }),
        "These are just the crumbs from homemade bread, they are hard and " +
        "inedible.\n"); 
}
