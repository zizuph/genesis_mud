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
    set_name("wheat");
    set_short("sheaf of wheat");
    set_pshort("sheaves of wheat");
    set_long("It is a sheaf of wheat, newly cut and golden-brown. 
        "Brewery owners need this in order to make beer.\n");

    set_commodity_name("wheat");
    set_commodity_value(500);

    add_prop(OBJ_I_WEIGHT, 300);
    add_prop(OBJ_I_VOLUME, 600);
}
