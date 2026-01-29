/*
 * morgurth.c - the black death
 *
 * poisonous herb, ingredient for morgurth potion
 * unid desc identical to athelas
 * poison is the black breath poison
 *
 * Olorin, July 1994
 */
#pragma save_binary
#pragma strict_types

inherit "/std/herb.c";

#include <herb.h>
#include <macros.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/guild2/spells/spell_defs.h"

void
create_herb()
{
    set_name("flower");
    add_name("morthul_ingr1");
    set_short("pale white flower");
    set_pshort("pale white flowers");
    set_adj(({"pale", "white"}));
    set_herb_name("morgurth");
    set_unid_long("This is an pale white flower that gives forth a faint sickening smell.\n");
    set_id_long(BSN("This pale white flower is a morgurth, beautiful "
      + "and yet horrible of shape. It gives forth a faint sickening "
      + "charnel-smell, an odour of rottenness. It is said that the "
      + "flowers like this are cultivated in Mordor to create powerful "
      + "and insidious poisons."));

    set_effect(HERB_POISONING,"black breath", 75);
    set_poison_file(MORGUL_S_BLACK_BREATH);

    set_id_diff(35);
    set_find_diff(7);

    set_decay_time(1800);
    set_herb_value(288);
    set_dryable();
}

