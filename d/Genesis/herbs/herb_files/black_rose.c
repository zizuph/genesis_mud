/* Manor's Garden black rose
 * Coded by Marisol (10/27/97)
 * This flower if smell it will make you ill.
 * For use in the Manor's Garden in Re Albi
 * Copyright (c) Marisol Ramos 1997 */

inherit "/std/herb";

#include <herb.h>
#include <macros.h>
#define BLACK_POISON "/d/Earthsea/herbs/poisons/bl_rose_poison.c"

int EFFECT, CC;

void
create_herb()
{
    set_name("flower");
    add_adj("black");
    set_herb_name("midnight's angel");
    set_short("black flower");
    set_pshort("black flowers");
    add_name("herb");
    add_pname("herbs");
    set_unid_long("A peculiar-smelling black rose from a rosebush.\n");
    set_id_long("A Midnight's Angel rose. This rose is "+
      "the product of a wizard's manipulation of nature. "+
      "The result is this unique black rose with a very "+
      "peculiar aroma. It is rumoured that some evil wizards "+
      "use it for their spells.\n");
    EFFECT = 1;
    CC = (5 * EFFECT) + (EFFECT * EFFECT)/4;

    set_ingest_verb("sniff");
    set_find_diff(3);
    set_id_diff(9);
    set_effect(HERB_SPECIAL, "", EFFECT);
    set_herb_value(CC);
    set_decay_time(5000);
    set_dryable();
}

string
query_recover()
{
    return MASTER + ":" + query_herb_recover();
}
void
int_recover(string arg)

{
    init_herb_recover(arg);
}

void
special_effect()
{
    object tp = this_player();
    object to = this_object();
    object poison;

    tp->catch_msg("As you sniff the black rose, "+
      "your stomach starts to feel squeamish.\n");
    tp->command("gag");
    setuid();
    seteuid(getuid(to));
    poison = clone_object(BLACK_POISON);
    poison->move(tp);
}
