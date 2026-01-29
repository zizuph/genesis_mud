/* 
 * Wrancheka Object. Random effects of confusion/20 seconds.
 */
inherit "/std/object";
inherit "/d/Krynn/rastlin/open/spells2/magic.object";

#include "/d/Krynn/common/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <tasks.h>
#include "../../guild/local.h"

#define WRANCHEKA_SUBLOC "wohs_wrancheka_subloc"

void do_confused_stuff();

object affected;
int confusion_alarm;


void
create_object()
{
    add_name("wohs_mag_confusion_obj");
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_S_WIZINFO, "A magical object creating confusion\n");

    set_no_show();
}

public int
remove_myself()
{
    tell_object(affected, "You shake off the fogginess that "+
	"was clouding your brain.\n");
    tell_room(E(affected), QCTNAME(affected) + " shakes " +
	affected->query_possessive() + " head, as if clearing "+
	"it from some fog.\n", affected);
    remove_alarm(confusion_alarm);
    affected->remove_subloc(WRANCHEKA_SUBLOC);
    return 1;
}

public void
enter_env(object dest, object old)
{
    affected = dest;
    
    affected->add_subloc(WRANCHEKA_SUBLOC, TO);
    confusion_alarm = set_alarm(itof(random(5)), 20.0, do_confused_stuff);
}

do_confused_stuff()
{
    object *potentials;
    potentials = all_inventory(E(affected)) |
      (affected->query_enemy(-1) - ({ affected->query_attack() }));

    if(affected->resolve_task(TASK_DIFFICULT, ({ TS_WIS })) > 0)
      {
	remove_myself();
	return;
      }

    switch(random(7))
      {
      case 0:
	break;
      case 1..3:
	affected->add_attack_delay(20, 1);
	affected->catch_msg("You look around, totally confused about "+
		"the battle going on.\n");
	tell_room(E(affected), QCTNAME(affected) + " looks around, "+
		"totally confused about the battle raging about.\n",
		affected);
	break;
      case 4..5:
	if(sizeof(potentials))
	affected->command("attack " +
		potentials[random(sizeof(potentials))]->query_real_name());
	affected->catch_msg("You go berserk, and start swinging into "+
		"the closest enemy!");
	tell_room(E(affected), QCTNAME(affected) + " goes berserk, "+
		"swinging wildly into the body of the closest enemy!\n",
		affected);
	break;
      case 6:
	if(affected->query_prop(LIVE_I_UNDEAD))
		break;
	affected->add_panic(25+random(25));
	affected->catch_msg("Your bowels start to quiver, and your whole "+
		"body trembles in fear.\n");
	tell_room(E(affected), QCTNAME(affected) + " starts to quiver "+
		"and tremble in fear.\n");
      }
	return;
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
        return "You are looking very confused and unsure of what to "+
		 "do.\n";

    return PRONOUN(me) + " is looking very confused and unsure of "+
	"what to do.\n";
}
