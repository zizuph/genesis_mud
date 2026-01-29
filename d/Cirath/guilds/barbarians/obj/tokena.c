#pragma save_binary

inherit "/std/object";

#include "defs.h"
#include <wa_types.h>

void
create_armour()
{	    
	set_name(({ "token", TOKEN_ID, HIGH_TOKEN_ID, COUN_TOKEN_ID}));
  	add_name("barb_brac");
  	set_short("wooden token");
  	set_long("This is the token that all true barbarians "+
           	"have. It has no decorations "+
           	"what so ever. If you want to know which commands "+
           	"and emotes you have as a high elder, just type "+
           	"'bhelp barbarian' or 'bhelp elder'.\n");
  	add_prop(OBJ_I_WEIGHT, 20);
  	add_prop(OBJ_I_VOLUME, 5);
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
    		tell_room(ENV(TO),"The tokens melt together in some mysterical way.\n");
    		remove_object();
    		return;
  	}
  		add_name("barb_brac");  	
	}    
}

void
init()
{
  	::init();
  	add_action("meditate", "meditate");
  	add_action("sneak", "sneak");
  	add_action("think", "think");
  	add_action("ponder", "ponder");
    	add_action("help", "help");
}

int
meditate()
{
  	write("What? A meditating barbarian? You maybe think you're "+
        	"some kind of monk or something?\n");
  	say(QCTNAME(TP)+" tries to meditate, but have you ever "+
        	"seen a meditating barbarian?\n");
  	return 1;
}

int
sneak(string str)
{
  	write("CLOMP! CLOMP! You really try to sneak but fail completely.\n");
  	say("CLOMP! CLOMP! "+QCTNAME(TP)+" tries to sneak but fails.\n");
  	return 1;
}

int
think(string str)
{
  	write("You try to think but fail.\n");
  	say(QCTNAME(TP)+" tries to think, but fails completely.\n");
  	return 1;
}

int
ponder(string str)
{
  	write("You try to ponder but realize that you forgot how to.\n");
 	say(QCTNAME(TP)+" tries to ponder but seems to forgotten how to.\n");
  	return 1;
}

int 
help(string str)
{
    	if (!(str=="elder")) return 0;
    	seteuid(getuid());
    	cat(BARB_HELP+"he_help");
    	return 1;
}

/* report_kill is a legacy stub, to be removed when we know
   things won't explode.                                     */
void report_kill(int which) {}