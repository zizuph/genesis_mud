 /*
  * catnip.c
  *
  * modified from tuo.c by Elessar
  * Olorin, July 1993
  * following a suggestion by Janus of Terel
  */
#pragma save_binary
#pragma strict_types

inherit "/std/herb.c";

#include <herb.h>
#include <macros.h>

#include "/d/Gondor/defs.h"

void
create_herb()
{
    set_name("flowers");
    add_name(({"flower", "spice"}));
    add_name("_spice");
    set_adj(({"handful", "of", "aromatic", "pale", "purplish"}));
    set_herb_name("catnip");
    set_short("handful of aromatic pale purplish flowers");
    set_pshort("handfuls of aromatic pale purplish flowers");
    set_ingest_verb("eat");
    set_unid_long("This is a handful of aromatic pale purplish flowers.\n");
    set_id_long(BSN(
	"This is a handful of catnip flowers. Catnip (Nepeta cataria) " +
	"is a perennial of the mint family. The branching herb reaches " +
	"a height of three feet. It has downy leaves and terminal racemes " +
	"of pale purplish flowers. Some say that the herb sometimes is able " +
	"to cure a strange poison that looks like a golden wine, if that " +
	"poison is not too strong. All parts of the plant have an aromatic " +
	"odour when crushed, and this odour is particularly attractive " +
	"to cats."));

    set_effect(HERB_CURING, "dollost", 50);
    set_id_diff(20);
    set_find_diff(2);
    set_decay_time(5400);
    set_herb_value(48);
    set_dryable();
}

