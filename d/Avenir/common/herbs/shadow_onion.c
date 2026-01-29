// file name:   ~Avenir/common/herbs/shadow_onion
// creator(s):   Lilith, 2/19/2004
// last update:
// purpose:      put play on words 'shadow union' to 'shadow onion'
//               into effect
// note:         some panick and fatige healing.
//               NATIVE TO SYBARUS ONLY.
// bug(s):
// to-do:

inherit "/std/herb";
#include <herb.h>
#include "/d/Avenir/common/common.h"

create_herb()
{
    set_name("onion");
    add_name("herb");
    add_pname(({"herbs", "onions"}));
    set_adj(({"shadow", "shadowy", "sybarus", "sybarun", "sybarite"}));
    set_short("shadowy green onion");
    set_herb_name("shadow onion");
    set_id_long("This onion has tall, dark green foliage similar to "
        + "that of green onions, however the flesh of the bulb is "
        + "greyish rather than white. "
        + "It is this colour which lends the onion the name 'shadow "
        + "onion'. It is known to be native to Sybarus, where it "
        + "is eaten for its relaxing and fatigue-banishing effects. "
        + "Attempts to cultivate this onion outside Sybarus have "
        + "produced mediocre results, lending credence to the sybarite "
        + "belief that the herb owes its beneficial properties to "
        + "the blessings of Sabrus and Sachluph.\n");
    set_unid_long("This onion has tall, dark green foliage similar to "
        + "that of green onions, however the flesh of the bulb is "
        + "greyish rather than white.\n");

    set_ingest_verb("eat");

    set_id_diff(25);
    set_find_diff(2);

    set_decay_time(1000);

    set_effect(HERB_SPECIAL, "", 10);
    add_effect(HERB_HEALING, "fatigue", 15); 
    set_herb_value(70);

    set_dryable();

    add_prop(OBJ_I_WEIGHT, 10);
    add_prop(OBJ_I_VOLUME, 15);
}

/* reduce panic
 */
void
special_effect()
{
    write("How interesting...this onion tastes sweet.\n");
    write("You experience a feeling of calmness and well-being.\n");
    this_player()->add_panic(-50);           
}

