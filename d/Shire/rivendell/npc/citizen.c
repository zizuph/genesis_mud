#include "/d/Shire/sys/defs.h"
#include "/d/Shire/rivendell/npc/elfmaker.h"

inherit "/d/Shire/rivendell/npc/elfmaker.c";

void
create_elf()
{
    set_type(CITIZEN);
    set_elf_average(110);

    set_title(" of the House of Finwe");
    command ("unwield all");
}

