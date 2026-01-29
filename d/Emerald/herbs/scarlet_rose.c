/* Manor's Garden red rose
 * Coded by Marisol (10/27/97)
 * This flower if smell will make you feel romantic.
 * For use in the Manor's Garden in Re Albi
 * Copyright (c) Marisol Ramos 1997 */
/* Modified in (07/09/98) to be used in the castle_garden in
 * Emerald. */


inherit "/std/herb";

#include <herb.h>
#include <macros.h>
#define SCARLET_POISON "/d/Emerald/herbs/sca_rose_poison.c"

int EFFECT, CC;

void
create_herb()
{
    set_name("rose");
    add_adj("scarlet");
    set_herb_name("russet inamorato");
    set_short("scarlet rose");
    set_pshort("scarlet roses");
    add_name("flower");
    add_pname("flowers");
    set_unid_long("A lovely-smelling scarlet rose from a rosebush.\n");
    set_id_long("A very rare rose, a Russet Inamorato. This flower "+
        "is the delight of nobles and their courtesans. This is "+
        "the right flower to show love in the most innocent way. The "+
        "fragance of this rose make you think romantic thoughts.\n");

    EFFECT = 1;
    CC = (5 * EFFECT) + (EFFECT * EFFECT)/4;

    set_ingest_verb("smell");
    set_find_diff(10);
    set_id_diff(15);
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

    tp->catch_msg("As you smell the scarlet rose, "+
    "you start feeling really romantic.\n");
    tp->command("$smile romantically");
    setuid();
    seteuid(getuid(to));
    poison = clone_object(SCARLET_POISON);
    poison->move(tp);
}
