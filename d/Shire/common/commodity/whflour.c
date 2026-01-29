/*
 * Wheat commodity
 * Fom Araven's commerce example
 * -- Finwe, November 2001
 */

 inherit "/std/object";
 inherit COMMODITY_LIB;

 public void
 create_object()
 {
    set_name("flour");
    add_name("white");
    set_short("sack of white flour");
    set_pshort("sacks of white flour");
    set_long("It is a sack of white flour. It is prized by many " +
        "bakers as it has been bleached to remove the brown " +
        "color, making food more appetizing.\n");

    set_commodity_name("wflour");
    set_commodity_value(750);

    add_prop(OBJ_I_WEIGHT, 3000);
    add_prop(OBJ_I_VOLUME, 6000);
}
