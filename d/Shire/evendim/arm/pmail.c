/*
 * Platemail for prisoner quest in Orc Camp at Evendim
 * -- Finwe, May 2001
 */

inherit "/std/armour";
#include "/sys/wa_types.h"
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/common/defs.h"

create_armour()
{
    set_name("platemail");
    set_name("mail");
    set_short("bright silver platemail");
    set_pshort("bright silver platemail");
    set_long("This is an suit of platemail for what was " +
        "probably an ancient lord or someone of importance. " +
        "The armour is extremely light despite its size and " +
        "retains its original shine. The armour is made of " +
        "plates of metal that enclose and protect the upper " +
        "part of the body.\n");
    set_default_armour(28);
    set_at(A_BODY);
    add_prop(OBJ_I_WEIGHT,5000);
    add_prop(OBJ_I_VOLUME,2000);
}
