/*
 * Manor's Garden black rose
 * Coded by Marisol (10/27/97)
 * This flower if smell will make you ill.
 * For use in the Manor's Garden in Re Albi
 * Copyright (c) Marisol Ramos 1997
*/

#pragma strict_types
#pragma save_binary

inherit "/std/herb";

#include <herb.h>

#define RED_POISON "/d/Earthsea/herbs/poisons/red_rose_poison"

public void
create_herb()
{
    set_name("flower");
    add_adj("red");
    set_herb_name("crimson's tippler");
    set_short("red flower");
    set_pshort("red flowers");
    add_name("herb");
    add_pname("herbs");
    set_unid_long("A intoxicating-smelling red rose from a rosebush.\n");
    set_id_long("A Crimson's Tippler rose. This rose is " +
        "the product of a wizard's manipulation of nature. " +
        "The result is this unique red rose with a very " +
        "peculiar aroma. It is rumored that a small sniff to this rose " +
        "can make you really happy.\n");
    set_ingest_verb("sniff");
    set_find_diff(3);
    set_id_diff(9);
    set_effect(HERB_SPECIAL, "", 1);
    set_herb_value((5 * 1) + (1 * 1)/4);
    set_decay_time(5000);
    set_dryable();
}

public void
special_effect()
{
    object tp = this_player(), to = this_object(), poison;
    write("As you sniff the red rose, you start feeling really gay.\n");
    tp->command("$smile drunkenly");
    setuid();
    seteuid(getuid(to));
    poison = clone_object(RED_POISON);
    poison->move(tp, 1);
}
