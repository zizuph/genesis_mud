/* 
 * MelbeRentis object. Slows the target by changing their quickness to -100
 */
inherit "/std/object";
inherit "/d/Krynn/rastlin/open/spells2/magic.object";

#include "/d/Krynn/common/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include "../../guild/local.h"

#define DEBUGTELL(x) find_player("karath")->catch_msg(x)
#define MELBERENTIS_SUBLOC "wohs_melberentis_subloc"

object affected;
int changeAmount;

void
create_object()
{
    add_name("wohs_mag_slow_obj");
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_S_WIZINFO, "A magical object forcing slowness to the " +
      "affected\n");

    set_no_show();
}

public int
remove_myself()
{
    tell_object(affected, "You suddenly feel your body return "+
	 "to normal, and that you can move quickly again.\n");
	if(affected->query_prop(LIVE_I_QUICKNESS) != changeAmount)
	    DEBUGTELL(capitalize(affected->query_real_name()) +
		" has a screwy quickness ... we modified it to -100 and "+
	 	"now that we want to remove it, it's at " +
		affected->query_prop(LIVE_I_QUICKNESS) + "\n");
    affected->change_prop(LIVE_I_QUICKNESS, changeAmount + 100);
    affected->remove_subloc(MELBERENTIS_SUBLOC);
    affected->query_combat_object()->cb_update_speed();
    return 1;
}

public void
enter_env(object dest, object old)
{
    affected = dest;

    changeAmount = affected->query_prop(LIVE_I_QUICKNESS) - 100;

    affected->change_prop(LIVE_I_QUICKNESS,
	 affected->query_prop(LIVE_I_QUICKNESS) - 100);
    affected->add_subloc(MELBERENTIS_SUBLOC, TO);
    affected->query_combat_object()->cb_update_speed();
}


public void
notify_dispel_magic(object ob)
{
    remove_myself();
}

public string
show_subloc(string subloc, object me, object for_obj)
{
    if (me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
        return "";

    if (for_obj == me)
        return "You are moving so slowly that others seem to be "+
		 "a whirlwind.\n";

    return PRONOUN(me) + " is moving so slowly that "
	+ PRONOUN(me) + " seems to be in a daze.\n";
}
