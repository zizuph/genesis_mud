#include "/d/Shire/sys/defs.h"
#include "/d/Shire/greyhavens/npc/elfmaker.h"
#include "../local.h"

inherit "/d/Shire/greyhavens/npc/elfmaker.c";

void
create_elf()
{
    object arrows, quiver;

    set_type(GUARD);
    set_elf_average(170);
    quiver = clone_object(GH_WEP_DIR + "quiver")->move(TO,1);
}
