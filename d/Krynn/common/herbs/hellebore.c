/*
 * Filename:        Krynn/common/herbs/hellebore.c
 * Description:     The Hellebore Stinkwort herb
 *                  It mildly poisoness
 *
 * Copyright (c) May 2003 by Daniel W. Mathiasen aka Boron
 *
 * Revision history:
 * When, Who, What:
 */
#pragma save_binary

inherit "/std/herb";

#include <herb.h>
#include <macros.h>

#include "/d/Krynn/common/defs.h"

void
create_herb()
{
    set_name("buttercup");
    add_name(({"stinkwort", "hellebore"}));
    set_adj(({"green", "stinking"}));
    set_herb_name("hellebore stinkwort");
    set_short("stinking buttercup");
    set_pshort("stinking buttercups");
    set_pname(({"buttercups", "herbs", }));
    set_ingest_verb("eat");
    set_unid_long("This buttercup is green of colour and slightly resembles "+
                "a rose with finely cut, and attractive looking, leaves. If " +
                "damaged the leaves have a foul smell to them.\n");
    set_id_long("This is the stinking hellebore or \"stinkwort\", when crushed " +
            "the leaves produce the reason for the nickname. It is of the " +
            "buttercup family and green of colour and slightly resembles "+
            "a rose with finely cut, and attractive looking, leaves. And it "+
            "would look good in a garden (unpicked of course). It is however "+
            "mildly toxic.\n");
    set_herb_value(10);
    set_id_diff(40);
    set_find_diff(3);
    set_decay_time(2000);
    set_effect(HERB_POISONING,"herb",15);
    add_effect(HERB_HEALING,"hp", -2);
    add_effect(HERB_HEALING,"fatigue",-5);
    set_amount(1);
    set_poison_file(KRPOISON + "hellebore");

}

string  query_recover() { return MASTER+":"+query_herb_recover(); }
void    init_recover(string arg) { init_herb_recover(arg); }
