/*
 *	/d/Gondor/open/examples/kid.c
 *
 */
#pragma strict_types

inherit "/d/Gondor/std/monster.c";

#include "/d/Gondor/defs.h"

public void	create_gondor_monster();

/*
 * Function name:	create_gondor_monster
 * Description	:	set up the kid
 */
public void
create_gondor_monster()
{
    set_name("kid");
    add_name("child");
    set_adj( ({ "young", "blond", }) );
    set_race_name("human");
    set_long("The small child has blond hair and freckles on his face.\n");
    
    set_equipment( ({ (WEP_DIR + "knife"), (ARM_DIR + "fjacket"), }) );
}
