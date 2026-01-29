#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/sanction/local.h"

inherit SANCTION_OUT;

void
create_sanction_room()
{
    set_short("abandoned pier in the harbour of Sanction");
    set_extra_long("This abandoned pier must once have stretched " +
        "further north. Now a red-hot lava river slowly flows into " +
        "the dark waters of Sanction harbour. The piers south of " +
        "here seems to be considered safer, and are apparently " +
        "still in use.");

    add_harbour_items();
    add_exit(SCITY + "pier02", "south");
}
