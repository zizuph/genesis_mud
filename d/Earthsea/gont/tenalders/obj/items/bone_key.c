#pragma strict_types

inherit "/std/key";

public void
create_key()
{
    set_name("key");
    add_name("_bone_key_");
    add_name("key");
    set_adj("bone");
    set_short("bone key");
    set_long("A key made from the bone of some animal.\n");
    set_key("_this_is_a_dead_key");
}
