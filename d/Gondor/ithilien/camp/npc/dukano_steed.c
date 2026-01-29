inherit "/d/Gondor/std/steed/steed.c";

#include "/d/Gondor/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include </d/Gondor/common/guild2/spells/spell_defs.h>

public int am_i_alone();

public void
create_steed()
{
    set_name("horse");
    set_adj(({"black", "massive"}));
    set_short("massive black horse");
    add_name(({"horse","steed","_dukano_steed_"}));
    set_long("This massive black steed looks like it is far " +
      "from being tame.  Its eyes reflect almost no light, " +
      "though they seem to study the surroundings "+
      "with evil intelligence.\n");

    add_prop(MORGUL_I_SULAMBAR_RES, 1);
    add_prop(OBJ_M_NO_STEAL, 1);
    add_prop(OBJ_M_NO_ATTACK, 1);
    set_stats(({120,120,120,60,60,85}));
    set_alignment(-300);
    set_skill(SS_UNARM_COMBAT, 75);
    set_skill(SS_DEFENCE, 75);
    set_skill(SS_BLIND_COMBAT, 75);

    allow_mounted_combat(1);


    set_alarm(5.0,400.0,am_i_alone);
}

public int
can_mount(object o)
{
    ::can_mount();
    if (o->query_real_name() != "dukano")
    {
	o->catch_tell("You do not dare to ride this steed.\n");
	return 0;
    }
    return 1;
}                                    


public int
am_i_alone()
{
if (!sizeof(Riders))
    {
	tell_room(ENV(TO),"The massive black steed gallops away.\n");
	TO->remove_object();
	return 1;
    }
    return 0;
}
