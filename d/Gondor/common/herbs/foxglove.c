/*
 *      /d/Gondor/common/herbs/foxglove.c
 *
 *      Poisonous, but will cure hemlock poison.
 *      Ingredient for Morgul spell ephessul.
 *      Ingredient for Ranger potion avarywalme.
 */
#pragma save_binary
#pragma strict_types

inherit "/std/herb.c";

#include <macros.h>
#include <herb.h>
#include <poison_types.h>
#include <ss_types.h>

#include "/d/Gondor/defs.h"

// POISON_FILE for some reason was no longer defined,
//  so I added this definition in - Morbeche Feb 2000
#define POISON_FILE "/std/poison_effect"
static string  Cure_Type,
Poison_Type;

void
set_medical_effect(string pt, string ct)
{
    Poison_Type = pt;
    Cure_Type   = ct;
}

void
create_herb()
{
    set_name("flowers");
    add_name( ({"ephessul_ingr1"}) );
    set_adj(({"purple", "of", "handful"}));
    set_herb_name("foxglove");
    set_short("handful of purple flowers");
    set_pshort("handful of purple flowers");
    set_ingest_verb("eat");
    set_unid_long(BSN("This is a handful of purple flowers, produced in "
	+ "a one-sided cluster. The flowers are about two inches long, and "
	+ "they are spotted within."));
    set_id_long(BSN("This is a handful of purple foxglove flowers. "
	+ "Foxglove (Digitalis) is a biennial herb of the figwort family. "
	+ "The erect plant grows from two to five feet with long rough "
	+ "leaves. The flowers, produced on a long, one-sided cluster, "
	+ "are slightly drooping, about two inches long, and spotted "
	+ "within. The plant is valued by the learned for its medical "
	+ "properties, which can be used to cure poisons paralyzing the "
	+ "circulatory system. If ingested by the healthy, however, "
	+ "foxglove can speed up the heart so much that it bursts from "
	+ "the strain."));

    set_effect(HERB_SPECIAL,"medical",50);
    set_medical_effect("digitalis","paralyze");
    set_poison_damage( ({ POISON_FATIGUE, 40, POISON_HP, 40, POISON_MANA, 50}) );

    set_id_diff(25);
    set_find_diff(3);

    set_decay_time(5400);

    set_herb_value(288);

    set_dryable();
}

void
special_effect()
{
    int     strength,
    n,
    a;
    object  poison,
    *inv;

    if (effects[1] != "medical")
    {
	write("You don't feel any effect.\n");
	return;
    }

    strength = effects[2];
    inv = all_inventory(TP);

    n = sizeof(inv);
    a = 0;
    while (n--)
    {
	if (function_exists("cure_poison", inv[n]) == POISON_FILE)
	{
	    if (inv[n]->cure_poison( ({ Cure_Type }), strength))
	    {
		write(BSN("The poison of the purple flowers happened to be "
		    + "the correct cure for the other poison in your body!"));
		a++;
		strength /= 2;
	    }
	    else
		write(BSN("The poison of the purple flowers is either too "
		    + "weak or of the wrong type to counteract the poison "
		    + "in your body."));
	}
    }
    if (a > 0)
	return;

    poison = clone_object(POISON_FILE);
    poison->set_strength(strength);
    poison->set_time(strength*10);
    poison->set_interval(60-strength);
    poison->set_poison_type(Poison_Type);
    if (poison_damage)
	poison->set_damage(poison_damage);
    poison->move(TP);
    poison->start_poison(TP);
}


