/* 
 * Takadek object - controls subloc and shadow
 */
inherit "/std/object";
inherit "/d/Krynn/rastlin/open/spells2/magic.object";

#include "/d/Krynn/common/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include "../../guild/local.h"

#define DEBUGTELL(x) find_player("karath")->catch_msg(x)
#define TAKADEK_SUBLOC "wohs_takadek_subloc"
#define MAGOBJDIR "/d/Krynn/wayreth/magic/obj/"

object affected, sh;

void
create_object()
{
    add_name("mag_takadek_obj");
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_S_WIZINFO, "A magical object controlling the takadek " +
      "shadow of the affected. provides immunity to mundane attacks.\n");

    set_no_show();
}

public int
remove_myself()
{
    tell_object(affected, "Your skin loses it's sheen, and you feel "+
	"less protected.\n");
    sh->remove_takadek_shadow();
    affected->remove_subloc(TAKADEK_SUBLOC);
    return 1;
}

public void
enter_env(object dest, object old)
{
    affected = dest;
    if(sh = clone_object(MAGOBJDIR + "takadek_shadow"))
      {
	sh->shadow_me(affected);
    	affected->add_subloc(TAKADEK_SUBLOC, TO);
      }
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
        return "Your skin has a metallic sheen to it.\n";

    return capitalize(PRONOUN(me)) + "'s skin has a metallic "+
	"sheen to it.\n";
}
