/* Feather from Kendermore, by Gwyneth on May 12, 1999 */

inherit "/std/object";

#include <macros.h>
#include "/d/Ansalon/common/defs.h"

void
create_object()
{
    set_name("feather");
    add_name("junk");
    set_adj("blue-green");
    set_short("blue-green feather");
    set_long("The brilliant colours of this feather give off a faint " +
      "metallic sheen.  It is long and plumed, perhaps coming " +
      "from a fancy hat.\n");
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_WEIGHT, 50);
    add_prop(OBJ_I_VALUE, 200);
    add_cmd_item(({"feather", "blue-green feather"}), "twirl", 
      "@@twirl_feather");
}

/* Function name: twirl
 * Description  : This allows people to twirl the feather.
 */ 
string
twirl_feather()
{
    write("You twirl the feather through the air, admiring its elegance.\n");
    say(QCTNAME(TP) + " twirls a brilliant blue-green feather through " +
      "the air, drawing your gaze.\n");
    return "";
}
