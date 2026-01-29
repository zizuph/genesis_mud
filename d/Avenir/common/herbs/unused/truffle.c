// file name:   ~Avenir/common/herbs/truffle
// creator(s):   Cirion, March 97
// last update:
// purpose:      A truffle - no effect, but they taste good.
// note: 
// bug(s):
// to-do:

inherit "/std/herb";
#include <herb.h>
#include "/d/Avenir/common/common.h"

create_herb()
{
    set_name("ball");
    add_name("herb");
    add_name("fungus");
    set_adj(({ "round", "black" }));
    set_short("round black fungus");

    set_herb_name("truffle");

    set_id_long("This round sporific fungus is a rich shade of deep black, "
        + "its sides glistening with moisture. The truffle is widely "
        + "thought to be a delicacy, and are valued greatly.\n");

    set_unid_long("This round sporific fungus is a rich shade of deep black, "
        + "its sides glistening with moisture.\n");

    set_ingest_verb("eat");

    set_id_diff(8);
    set_find_diff(50);

    set_decay_time(1000);

    set_herb_value(430);

    set_amount(35);

    add_prop(OBJ_I_WEIGHT, 80);
    add_prop(OBJ_I_VOLUME, 85);
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

    write("You greedily " + vb + " " + (str = COMPOSITE_DEAD(arr)) + ".\n"
        + "It tastes wonderful!\n");
    say(QCTNAME(this_player()) + " greedily " + vb + "s " + str + ".\n");
}
