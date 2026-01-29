#include "/d/Shire/sys/defs.h"
#include "/d/Shire/rivendell/npc/elfmaker.h"

inherit "/d/Shire/rivendell/npc/elfmaker.c";

void
create_elf()
{
    set_type(TRAVELLER);
    set_elf_average(120);

    set_title(" of the House of Finwe");
}

