inherit "/std/object";
#include <macros.h>
#include <wa_types.h>
#include <stdproperties.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam/local.h"


void
create_object()
{
    set_name(({"handkerchief","_ansalon_kender_handkerchief_"}));
    set_adj("white");
    set_short("white handkerchief");
    set_long("This is a soft white handkerchief, used mainly to blow ones nose " +
      "with. Stitched in one corner are the initials A.K.\n");

    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VOLUME, 500);
    add_prop(OBJ_I_VALUE, 500);

    add_cmd_item("nose",({"blow","wipe"}),"@@blow_nose");
}

string
blow_nose()
{
    write("You blow your nose on the white handkerchief.\n");
    say(QCTNAME(TP) + " blows " +HIS(TP)+ " nose on the white handkerchief.\n");
    return "";
}
