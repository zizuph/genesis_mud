inherit "/std/paralyze";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "/d/Shire/sys/defs.h"

static int bf, def, parry;

void
create_paralyze()
{

    set_no_show();
    set_name("_Shire_chair_stun");
    remove_prop(OBJ_I_WEIGHT);
    remove_prop(OBJ_I_VOLUME);
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_NO_GIVE, 1);
    set_fail_message("You are unconscious and unable to do anything.\n");
}

void
enter_env(object ob,object from)
{
    ::enter_env(ob, from);

    if (!living(ob))
    {
	::remove_object();
	return;
    }

    set_alarm(itof(15 + random(11)), 0.0, remove_object);
    ob->add_stun();
    ADD_SKILL(ob, SS_PARRY, -(parry = (ob->query_skill(SS_PARRY) - 10)));
    ADD_SKILL(ob, SS_DEFENSE, -(def = (ob->query_skill(SS_DEFENSE) - 10)));
    ADD_SKILL(ob, SS_BLIND_COMBAT, -(bf = (ob->query_skill(SS_BLIND_COMBAT)-10)));
    ob->add_prop(LIVE_I_SEE_DARK, ob->query_prop(LIVE_I_SEE_DARK) - 200);
    ob->catch_tell("The force of the blow renders you unconscious!\n");
    tell_room(environment(ob), QCTNAME(ob) + " is knocked "+
      "unconscious and falls to the floor.\n", ({ob}));
}

void
remove_object()
{
    object ob;

    if (objectp(this_object()))
	ob = environment();
    if (objectp(ob))
    {
	ob->remove_stun();
	ADD_SKILL(ob, SS_PARRY, parry);
	ADD_SKILL(ob, SS_DEFENSE, def);
	ADD_SKILL(ob, SS_BLIND_COMBAT, bf);
	ob->add_prop(LIVE_I_SEE_DARK, ob->query_prop(LIVE_I_SEE_DARK) + 200);
	ob->catch_tell("You regain consciousness and stand on your feet.\n");
	tell_room(environment(ob), QCTNAME(ob) + " wakes up and gets "+
	  "to "+ob->query_possessive() +" feet.\n", ({ob}));
    }
    ::remove_object();
}
