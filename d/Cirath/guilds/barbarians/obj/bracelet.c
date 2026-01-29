#pragma save_binary

inherit "/std/armour";

#include "defs.h"
#include <wa_types.h>

void
create_armour()
{	
  set_name(({ "bracelet", BRAC_ID }));
  add_name("barb_brac");
  set_short("bracelet");
  set_long("This is the bracelet that all true barbarians "+
           "have. It has no decorations "+
           "what so ever. If you want to know which commands "+
           "and emotes you have as a barbarian, just type "+
           "'bhelp barbarian'.\n");
  set_default_armour(0, A_R_ARM);
  add_prop(OBJ_I_WEIGHT, 250);
  add_prop(OBJ_I_VOLUME, 50);
  add_prop(OBJ_I_VALUE, 7);
  add_prop(OBJ_M_NO_DROP,1);
}


int
query_recover()
{
    return 0;
}

void
enter_env(object env, object from)
{
    	::enter_env(env, from);
    	if (!IS_MEMBER(env) && !IS_WIZ(env))
        	remove_object();    
    	else
    	{
  	remove_name("barb_brac");
  	if(present("barb_brac",ENV(TO)))
  	{
    		tell_room(ENV(TO),"The bracelets melt together in some mysterical way.\n");
    		remove_object();
    		return;
  	}
  	add_name("barb_brac");  	
    	set_alarm(4.5, 0.0, "auto_wear");
	}    
}

void
auto_wear()
{
    wear_me();
}

void
init()
{
  ::init();
  add_action("meditate", "meditate");
  add_action("sneak", "sneak");
  add_action("think", "think");
  add_action("ponder", "ponder");
}

int meditate()
{
  write("What? A meditating barbarian? You maybe think you're "+
        "some kind of monk or something?\n");
  say(QCTNAME(TP)+" tries to meditate, but have you ever "+
        "seen a meditating barbarian?\n");
  return 1;
}

int sneak(string str)
{
  write("CLOMP! CLOMP! You really try to sneak but fail completely.\n");
  say("CLOMP! CLOMP! "+QCTNAME(TP)+" tries to sneak but fails.\n");
  return 1;
}

int think(string str)
{
  write("You try to think but fail.\n");
  say(QCTNAME(TP)+" tries to think, but fails completely.\n");
  return 1;
}

int ponder(string str)
{
  write("You try to ponder but realize that you forgot how to.\n");
  say(QCTNAME(TP)+" tries to ponder but seems to forgotten how to.\n");
  return 1;
}

void report_kill(int which) {}