#include "/d/Shire/sys/defs.h"
#include "/d/Shire/rivendell/npc/elfmaker.h"

inherit "/d/Shire/rivendell/npc/elfmaker.c";

void
create_elf()
{
    set_type(GUARD);
    set_elf_average(130);

    set_title(" of the House of Finwe");
}

/*
 * Function name:	move_living
 * Description	:	mask parent so we can check new env for spying eyes
 * Arguments	:	string how -- direction of travel, etc
 *			mixed to_dest -- destination
 *			int dont_follow -- flag re group movement
 *			int no_glance -- flag re looking in new room
 * Returns	:	int -- 0 on success, non-0 on failure
 */
public varargs int
move_living(string how, mixed to_dest, int dont_follow, int no_glance)
{
    int rval;
    rval = ::move_living(how, to_dest, dont_follow, no_glance);
    return rval;
} /* move_living */

