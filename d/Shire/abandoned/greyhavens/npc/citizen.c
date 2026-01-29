#include "/d/Shire/sys/defs.h"
#include "/d/Shire/greyhavens/npc/elfmaker.h"

inherit "/d/Shire/greyhavens/npc/elfmaker.c";

void
create_elf()
{
    set_type(CITIZEN);
    set_elf_average(110);
}