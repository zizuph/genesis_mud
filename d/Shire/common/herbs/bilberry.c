/*
 * Bilberry berry. Infravision for 1 minute
 * Finwe, March 2003
 */

#include "defs.h"
#include <herb.h>
#include <macros.h>
#include <poison_types.h>
#include <ss_types.h>

inherit "/std/herb.c";

#define EFFECT "/d/Shire/common/herbs/bilberryef"

void
create_herb()
{
    set_name("bilberry");
    add_name("berry");
    set_adj(({"small","black"}));
    set_short("small black berry");
    set_pshort("small black berries");
    set_herb_name("bilberry");
    set_id_long("This is a berry from a Bilberry plant. The plant is " +
        "of medium height and grows in temperate forests. The berry " +
        "is smooth to the touch, and is rumoured to have magical " +
        "properties, but what they are, no one knows anymore.\n");
    set_unid_long("This is a black berry\n");
    set_ingest_verb("eat");
    set_id_diff(20);
    set_find_diff(6);
    set_effect(HERB_SPECIAL, "vision", 0);
    set_decay_time(500);
    set_herb_value(1500);
    set_dryable();
}

string
query_recover()
{
    return MASTER+":"+query_herb_recover();
}
 
void
init_recover(string arg)
{
    init_herb_recover(arg);
}
 
void
special_effect()
{
    setuid();
    seteuid(getuid());

    clone_object(EFFECT)->move(this_player(), 1);
}
