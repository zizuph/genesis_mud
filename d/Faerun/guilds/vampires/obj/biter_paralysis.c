inherit "/std/object";

#include "../guild.h"
#include <stdproperties.h>
#include <ss_types.h>

static object who;
static int defmod, parmod;

void create_object()
{
    set_name("_vamp_biter_paralysis");
    set_no_show();
    remove_prop(OBJ_I_WEIGHT);
    remove_prop(OBJ_I_VALUE);
    remove_prop(OBJ_I_VOLUME);
    add_prop(OBJ_M_NO_GET, "");
    add_prop(OBJ_M_NO_DROP, "");
    add_prop(OBJ_M_NO_SELL, "");
    add_prop(OBJ_M_NO_BUY, "");
}

int catch_all(string str)
{
    switch (query_verb())
    {
    	case "quit":
    	case "help":
    	case "bug":
    	case "commune":
    	case "typo":
    	case "sysbug":
    	case "reply":
    	case "stop":
    	case "systypo":
    	case "vthirst":
    	case "health":
    	case "h":
    	case "vitals":
        case "v":
    	case "drop":
    	case "vtelepath":
    	case "vvision":
    	case "voptions":
        case "stats":
        case "vdrain":
	  return 0;
    }
  
    write("You can't manage it while feeding.\n");
    return 1;
}

void init()
{
    ::init();
  
    if (environment() == this_player())
    {  
    	if (!this_player()->query_wiz_level())
    	{
	    add_action(catch_all, "", 1);
      
	    defmod = min(0, 20 - this_player()->query_skill(SS_DEFENSE));
	    parmod = min(0, 1  - this_player()->query_skill(SS_PARRY));
      
	    if (defmod)
	    {
		this_player()->set_skill_extra(SS_DEFENSE, defmod);
	    }
      
	    if (parmod)
	    {
		this_player()->set_skill_extra(SS_PARRY, parmod);
	    }
      
	    this_player()->add_stun();
    	}
    
    	who = this_player();
    }
}

void
enter_env(object env, object from)
{
    ::enter_env(env, from);

    if (!living(env))
    {
        remove_object();
    }
}

void
leave_env(object env, object to)
{
    ::leave_env(env, to);
  
    if (who)
    {
	who->remove_stun();
  
	if (defmod)
	{
	    who->set_skill_extra(SS_DEFENSE, 0);
	}
  
        if (parmod)
	{
            who->set_skill_extra(SS_PARRY, 0);
	}
    }
}
