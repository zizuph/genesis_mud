#pragma strict_types

inherit "/std/object";

public void
create_object()
{
    set_name("dust");
    add_name("guano");
    add_name("dung");
    add_name("__es_dung_dust__");
    set_adj(({"dung", "guano", "pile of", "pile"}));
    set_short("pile of guano dust");
    set_long("This is a pile of decayed guano.\n");
}
