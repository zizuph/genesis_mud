inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Ansalon/common/defs.h"

void
create_object()
{
    set_name(({"shell","conch shell","pink conch shell",
	"_flotsam_c_shell_"}));
    set_adj("conch");
    add_adj("pink");
    set_short("pink conch shell");
    set_long("This is a large pink conch shell. The outer whorl " +
      "of the shell is broadly triangular in outline and has a wide " +
      "lip. What causes the pink colour is unknown, and is furiously " +
      "debated by scholars. \n");
    add_prop(OBJ_I_VOLUME, 300);
    add_prop(OBJ_I_WEIGHT, 500);

    add_cmd_item(({"shell","conch shell"}),"blow","@@blow_shell");
}

string
blow_shell()
{
    write("You blow on the conch shell, making a deep and " +
      "loud bellowing noise that echoes around you.\n");
    say(QCTNAME(TP) + " blows into the pink conch shell, " +
      "producing a loud and deep bellowing noise that echoes " +
      "around you.\n");
    return "";
}
