/* 
 * Bakari object, simple shield, protecting the wearer from blows.
 */
inherit "/std/object";
inherit "/d/Krynn/rastlin/open/spells2/magic.object";

#include "/d/Krynn/common/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include "../../guild/local.h"

#define DEBUGTELL(x) find_player("karath")->catch_msg(x)
#define ACTENNI_SUBLOC "wohs_actenni_subloc"

object affected;
int changeAmount;

void
create_object()
{
    add_name("mag_haste_obj");
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_S_WIZINFO, "A magical object providing haste to the " +
      "affected\n");

    set_no_show();
}

public int
remove_myself()
{
    tell_object(affected, "As a surge of weariness floods over you, you "+
	"suddenly feel like your extra quickness has left you.\n");
	if(affected->query_prop(LIVE_I_QUICKNESS) != changeAmount)
	  {
	    DEBUGTELL(capitalize(affected->query_real_name()) +
		" will have a non-zero quickness after I remove "+
		"myself.!\n");
	  }
    affected->add_prop(LIVE_I_QUICKNESS,
	affected->query_prop(LIVE_I_QUICKNESS) - changeAmount);
    affected->add_fatigue( - ((3 * affected->query_max_fatigue()) / 4));
    affected->eat_food(-(affected->query_stuffed()));
    affected->remove_subloc(ACTENNI_SUBLOC);
    affected->query_combat_object()->cb_update_speed();
    return 1;
}

public void
enter_env(object dest, object old)
{
    affected = dest;

    changeAmount = affected->query_prop(LIVE_I_QUICKNESS) + 100;

    affected->change_prop(LIVE_I_QUICKNESS,
	 affected->query_prop(LIVE_I_QUICKNESS) + 100);
    affected->add_subloc(ACTENNI_SUBLOC, TO);
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
        return "You are moving so fast that others seem to be "+
		 "standing still.\n";

    return capitalize(PRONOUN(me)) + " is moving so quickly that "
	+ PRONOUN(me) + " seems to be a blur.\n";
}
