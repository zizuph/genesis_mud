inherit "/std/herb";
#include "/d/Kalad/defs.h"
#include <poison_types.h>
#include <herb.h>

/* A very poisonous herb , Sarr */

void
create_herb()
{
    set_name("mushroom");
    add_adj("black");
    add_adj("green-spotted");
    set_short("black green-spotted mushroom");
    set_id_long("This is a small looking mushroom. It has a short, "+
    "stubby stem, but a large and pointed head. It is black, except "+
    "for its head which has many green spots. You recognize this as "+
    "one of the most lethal herbs known. It is nightshade, poisonous "+
    "in the extreem.\n");

    set_unid_long("This is a small looking mushroom. It has a short, "+
    "stubby stem, but a large and pointed head. The whole mushroom "+
    "is black, except for the head where it has many strange green "+
    "spots on it.\n");

    set_herb_name("nightshade");
    set_amount(2);
    set_decay_time(600);
    set_id_diff(50);
    set_find_diff(8);
    set_herb_value(80);
    set_ingest_verb("eat");
    set_effect(HERB_SPECIAL,"",0);
}

void
special_effect()
{
    object poison;
    seteuid(getuid());
    poison = clone_object("/std/poison_effect");
    poison->set_interval(1);
    poison->set_time(500);
    poison->set_damage( ({ POISON_HP, 100 }) );
    poison->set_strength(50);
    poison->set_poison_type("herb");
    poison->move(TP);
    poison->start_poison();
}
