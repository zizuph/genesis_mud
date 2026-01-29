#pragma strict_types

inherit "/std/object";

public void
create_object()
{
    set_name("egg");
    add_name("__es_hollow_egg__");
    set_adj(({"small", "hollow", "bird", "blue"}));
    set_short("small blue egg");
    set_long("Seemingly a normal blue bird egg, this " +
        "egg is in fact hollow. Two pin-sized holes at the " +
        "bottom seem to have allowed its payload to escape.\n");
    add_item(({"hole", "holes", "pin-sized hole", "pin-sized holes"}),
        "Pin-sized holes at the bottom of the egg seem to have allowed " +
        "its payload to escape.\n");
}
