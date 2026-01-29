/* Ashlar, 4 Oct 97 */

#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Ansalon/guild/pot/guild.h"

inherit TEMPLE_BASE;
inherit "/d/Ansalon/guild/pot/lib/train_comb";

object goblin;

void
reset_neraka_room()
{
    if (!objectp(goblin))
    {
        goblin = clone_npc(NNPC + "gruzz");
        set_trainer(goblin);
    }
}

string
long_descr()
{
    return "This is a room right outside the entrance to the temple " +
    "dungeons. The dungeons are closed off to anyone but the dungeon " +
    "guard, and those that are thrown into the dungeons.\n";
}

void
create_neraka_room()
{
    set_short("outside the entrance to the dungeons");
    set_long("@@long_descr");

    add_temple_items();
    add_item(({"entrance","dungeons","entrance to dungeons"}),
    "The entrance to the dungeons is to the east, but you cannot enter.\n");

    reset_room();

    create_skill_raise();
    set_up_skills();

    add_exit(NTEMPLE + "d9", "northwest");
    add_exit(NTEMPLE + "d4", "southwest");
}

public void
init()
{
    init_skill_raise();
    ::init();
}
