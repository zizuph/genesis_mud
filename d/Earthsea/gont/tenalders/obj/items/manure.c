#pragma strict_types

inherit "/std/object";

public void
create_object()
{
    set_name("manure");
    add_name("pile");
    add_name("__es_farm_manure__");
    set_adj(({"pile", "pile of"}));
    set_short("pile of manure");
    set_long("A pile of manure. Whatever animal made it, it must " +
        "have been big. And with a healthy diet...\n");
}
