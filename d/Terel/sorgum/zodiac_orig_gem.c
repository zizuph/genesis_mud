inherit "/std/object";
#include <stdproperties.h>
#include <ss_types.h>
#include <tasks.h>
#include <macros.h>

object to_summon;

string
query_auto_load()
{
    return (MASTER_OB(this_object()) + ":");
}

int
wiz_check()
{
    if (this_player()->query_wiz_level()) {
	set_alarm(1.0, -1.0, "check_carry");
	return 0;
    } else return 1;
}

void
check_carry() {
    if (!living(environment()) || environment()->query_npc())
	remove_object();
}

create_object()
{
    set_name("gem");
    set_adj("glowing");
    set_long(break_string("This is a strange gem glowing in all rainbow " +
	"colors. Actually, it could give you some light in the dark. You " +
	"have the feeling there is something else you could do with " +
	"it...\n",70));
    add_prop(OBJ_I_WEIGHT,100);
    add_prop(OBJ_I_VOLUME,100);
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_LIGHT,10);
    add_prop(OBJ_I_NO_STEAL,1);
    add_prop(OBJ_M_NO_DROP, "@@wiz_check");
    to_summon = 0;
/*
    add_prop(OBJ_M_NO_GIVE, "@@wiz_check");
*/
}

init() {
    ::init();
    add_action("do_rub","rub");
}

int
do_rub(string str) {
    int manas,success;

    notify_fail("Rub what?\n");
    if (str != "gem") return(0);
    if (!present(this_object(),this_player())) return(0);
    notify_fail("But you're already rubbing the gem like a mad....\n");
    if (to_summon) return 0;
    manas = this_player()->query_mana();
    if (manas < 100)
    {
	write("A shiver goes thru your body - but it seems you're too weak.\n");
	return 1;
    }
    manas = manas/3;
    if (manas < 30) manas = 30;
    this_player()->add_mana(-manas);
    success = this_player()->resolve_task(TASK_ROUTINE,
	({SKILL_WEIGHT, 80, SS_SPELLCRAFT,
	  SKILL_WEIGHT, 20, SS_FORM_CONJURATION }));
    if (success > 0)
    {
	write(break_string("You concentrate yourself and get together " +
		"all your power... You can feel something is going " +
		"on...\n",70));
	to_summon = this_player();
	set_alarm(10.0, -1.0, "do_summon");
    }
    else write(break_string("You concentrate yourself and get together " +
	"all your power... But nothing seems to happen.\n",70));
    return 1;
}


void
do_summon()
{
    tell_object(to_summon,"Suddenly, you feel magically summoned...\n");
    to_summon->move_living("X",
	to_summon->query_default_start_location());
    to_summon = 0;
}

