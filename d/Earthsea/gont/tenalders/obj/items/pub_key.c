#pragma strict_types

inherit "/std/key";

public void
create_key()
{
    set_name("_overnight_key_");
    set_adj("blue");
    set_short("small blue key");
    set_long("A small blue key made from some undefined metal.\n");
    set_key(999);
}

public int
query_overnight()
{
    return 1;
}
