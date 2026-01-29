// file name:   ~Avenir/common/herbs/osria
// creator(s):   Cirion, March 1007
// last update:
// purpose:      Hurting mushroom found in the Union's garden
// note: 
// bug(s):
// to-do:

inherit "/std/herb";
#include <herb.h>
#include "/d/Avenir/common/common.h"

create_herb()
{
    set_name("mushroom");
    add_name("herb");
    add_pname(({"herbs", "mushrooms"}));
    set_adj(({ "wide", "brimmed", "wide-brimmed" }));
    set_short("wide-brimmed mushroom");

    set_herb_name("osria");

    set_id_long("This light-grey mushroom has a short, fat stalk and "
        + "a very thick and wide brim. Along the stalk are tiny "
        + "bumps. This is the Osria mushroom, known to cause "
        + "painful effects when eaten.\n");

    set_unid_long("This light-grey mushroom has a short, fat stalk and "
        + "a very thick and wide brim. Along the stalk are tiny "
        + "bumps.\n");

    set_ingest_verb("eat");

    set_id_diff(30);
    set_find_diff(3);

    set_decay_time(100);

    set_effect(HERB_HEALING, "hp", -100); 
    set_herb_value(10);

    set_dryable();

    add_prop(OBJ_I_WEIGHT, 10);
    add_prop(OBJ_I_VOLUME, 15);

}

/*
 * Function name: consume_text
 * Description:   Here the eat message is written.
 * Arguments:     arr - Objects being consumed
 *                vb  - The verb player used to consume them
 */
void
consume_text(object *arr, string vb)
{
    string str;

    write("You " + vb + " " + (str = COMPOSITE_DEAD(arr)) + ".\n"
        + "You feel a wrenching pain in your stomach.\n");
    say(QCTNAME(this_player()) + " " + vb + "s " + str + ".\n");
}
