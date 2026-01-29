/* Silver bells found in Kendermore, Gwyneth, June 1999 */

inherit "/std/object";

#include <macros.h>
#include "/d/Ansalon/common/defs.h"

void
create_object()
{
    set_name("bells");
    add_name("junk");
    set_adj(({"pair","pair of"}));
    add_adj("silver");
    set_short("pair of silver bells");
    set_long("Delightful sounds come from this pair of silver bells. It " +
        "puts a smile on your face as you jingle them.\n"); 
    add_prop(OBJ_I_VALUE, 15);
    add_prop(OBJ_I_WEIGHT, 10);
    add_prop(OBJ_I_VOLUME, 20);
    add_cmd_item("bells", "jingle", "@@jingle_bells");
}

/* Function name : Jingle bells
 * Description : Added emote to go with the bells.
 * Returns : Null
*/

string
jingle_bells()
{
    write("You jingle the bells, bringing a bright smile to your face.\n");
    say(QCTNAME(TP) + " jingles a pair of silver bells with a bright smile.\n");
    return "";
}

