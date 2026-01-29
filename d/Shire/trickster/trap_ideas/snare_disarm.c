inherit "/std/object";

#include <macros.h>
#include "/d/Shire/common/defs.h"
#include <ss_types.h>
#include <tasks.h>

object shadow, shadow_who;

void
create_object()
{
    set_name("disarm_object");
    set_short("You should never see this!");
    set_long("A part of the trickster snare trap, since I was unable "+
      "to add_actions via a shadow and add_cmd_item didn't work for "+
      "heaps I decided to make this object!\n");
    set_no_show();
    add_prop(OBJ_M_NO_GET,1);
}

void
set_disarm_object(object sh, object s_object)
{
    shadow = sh;
    shadow_who = s_object;
}

void
init()
{
    ::init();
    add_action("disarm","disarm");
    add_action("disarm","disable");
    add_action("disarm","remove");
}

int
disarm(string str)
{
    string rope;

    if (!shadow || !shadow_who)
	return 0;
    if (member_array(str,shadow_who->query_names()) == -1 && str != "trap") 
	return 0;

    if (TP->query_real_name() == shadow->query_trap_setter())
    {
	TP->catch_msg("You decide that you know a better place to set this "+
	  "trap up so you quickly remove it.\n");
	if (rope = shadow->query_rope_file())
	{
	    setuid(); seteuid(getuid());
	    clone_object(rope)->move(ENV(shadow_who));
	}
	tell_room(ENV(shadow_who), QCTNAME(TP) +" quickly removes the trap "+
	  "from the "+ shadow_who->short() +", apparently not satisified "+
	  "with it's present location.\n",TP);
	shadow->remove_snare_shadow();
	return 1;
    }

    if (TP->query_mana() < 20)
    {
	notify_fail("You are too mentally exhausted to do disarm "+
	  "the "+shadow_who->short()+"!\n");
	return 0;
    }
    //  Causes us some mental strain to do this
    TP->add_mana(-10);
    if (TP->resolve_task(shadow->query_trap_quality(), ({SS_FR_TRAP,
	  TS_DEX})) > 0)
    {
	TP->catch_msg("You managed to disarm the "+shadow_who->short()+"!\n");
	if (rope = shadow->query_rope_file())
	{
	    setuid; seteuid(getuid());
	    clone_object(rope)->move(ENV(shadow_who));
	}
	tell_room(ENV(shadow_who), QCTNAME(TP) + " managed to disarm the "+
	  shadow_who->short() + ".\n",TP);
	shadow->remove_snare_shadow();
	return 1;
    }
    notify_fail("You were unable to disarm the "+shadow_who->short()+".\n");
    return 0;
}
