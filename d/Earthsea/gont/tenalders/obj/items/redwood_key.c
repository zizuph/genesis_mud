#pragma strict_types

inherit "/std/key";

public void
create_key()
{
    set_name("_redwood_tree_key_");
    add_name("key");
    set_adj("redwood");
    add_adj("wooden");
    set_short("wooden key");
    set_long("An unusual key about the size of your hand " +
        "and made from redwood.\n");
}
