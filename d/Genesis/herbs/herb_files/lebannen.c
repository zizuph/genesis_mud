/* Rowan bark. This bark when eat it will heal all
 * kind of poison. It is really rare and expensive.
 * Found in Roke Island and in any place where Rowans
 * grown. Coded by Marisol (11/18/97)
* Copyright (c) Marisol Ramos 1997 */

inherit "/std/herb";

#include <herb.h>
#include <macros.h>

void
create_herb()
{
    set_name("bark");
    add_adj("brown");
    set_herb_name("lebannen");
    set_short("brown bark");
    set_pshort("brown barks");
    add_name("herb");
    add_pname("herbs");
    set_unid_long("A brown bark from a tree.\n");
    set_id_long("A lebannen bark! This is the most noble tree. "+
        "The Lebannen is a tree linked with legends and prophesies "+
        "of the coming of the true king to Havnor to reign over all "+
        "Earthsea. He who would be king, will heal all the poisons of "+
        "the world and bring everlasting peace. The magic properties "+
        "and better use of the bark is known to few. But it is clear "+
        "for the learned that the improper ingestion of the herb "+
        "will make you lose its marvelous benefits. The bark is brown "+
        "and tough like beef jerky so it is hard to eat\n");

    set_ingest_verb("chew");
    set_find_diff(10);
    set_id_diff(50);
    set_effect(HERB_CURING, "hp", 25);
    set_herb_value(4000);
    set_decay_time(2000);
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
