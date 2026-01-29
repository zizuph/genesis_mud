//
// Soul - for the Order of Sean Rhian
//
// History:
// Date       Coder        Action
// -------- -------------- --------------------------------------------
// 6/27/98  Zima           Started
//
#pragma strict_types
#pragma save_binary
 
inherit "/cmd/std/command_driver";
 
#include <stdproperties.h>
#include <macros.h>
#include <adverbs.h>
#include <ss_types.h>
#include <cmdparse.h>
#include <language.h>
#include <composite.h>
#include <options.h>
#include <filter_funs.h>
#include "defs.h"
 
#define SOULDESC(x) (TP->add_prop(LIVE_S_SOULEXTRA, x))
 
//-------------------------------------------------------------------------
// short query functions
//-------------------------------------------------------------------------
string get_soul_id()    { seteuid(getuid()); return GUILD_NAME; }
int    query_cmd_soul() { seteuid(getuid()); return 1; }
 
//-------------------------------------------------------------------------
// cmd_list
//-------------------------------------------------------------------------
int cmd_list()
{
    write("Luiad bi Ardaugh!\n" +
	"  harmony - divine your harmony with Ardaugh.\n"+
    "  srchant - chant a canticle in the ancient Ghaelich language."+
    "\n");
    return 1;
}
 
//-------------------------------------------------------------------------
// Emotes
//-------------------------------------------------------------------------
int srhelp(string str)
{
	write("------------------------------------------------\n");
	write("           The Order of Sean-Rhian              \n");
	write("------------------------------------------------\n");
	write(" harmony    - divine your harmony with Ardaugh  \n");
	write(" srchant    - chant a short canticle            \n");
	write("------------------------------------------------\n");
	return 1;
}


//-------------------------------------------------------------------------
// msg_harmony
//-------------------------------------------------------------------------
void msg_harmony(object tp, string msg)
{
	tp->catch_msg(msg);
}

//-------------------------------------------------------------------------
// harmony - check harmony skill of saggart
//-------------------------------------------------------------------------
int harmony(string str)
{
    string m;
    int    h = (TP->query_skill(SS_SR_HARMONY));

    if (h<=0)
		m = "completely unknown to the Solsheyderi.";
	else
		switch (h)
		{
		case 0..19:   m="known by the Solsheyderi.";                   break;
		case 20..49:  m="share some communion with the Solsheyderi.";  break;
		case 50..89:  m="in communion with the Solsheyderi.";          break;
		case 90..139: m="in full communion with the Solsheyderi.";     break;
		case 140..199:m="share some consonance with the High Servant.";break;
		case 200..269:m="in consonance with the High Servant.";        break;
		case 270..349:m="in full consonance with the High Servant.";   break;
		case 350..439:m="in some harmony with The Most High.";         break;
		case 440..539:m="in harmony with The Most High.";              break;
		case 540..649:m="in complete harmony with The Most High.";     break;
		default:	  m="in utter harmony with The Most High.";        break;
		}
	m = "You feel you are "+m+"\n";
	TP->catch_msg("You meditate and delve deep into your soul.\n");
	tell_room(ENV(TP),QCTNAME(TP)+" breathes deeply and meditates "+
		      "momentarily.\n",TP);
	set_alarm(5.0,0.0,&msg_harmony(TP,m));
	return 1;
}

//-------------------------------------------------------------------------
// srchant emote
//-------------------------------------------------------------------------
int srchant(string str)
{
    write("You chant a short canticle in the ancient Ghaelich tounge.\n");
    tell_room(ENV(TP),QCTNAME(TP)+" chants a short canticle in the "+
                      "ancient Ghaelich tounge.\n",TP);
    return 1;
}
 
//-------------------------------------------------------------------------
// query_cmdlist()
//-------------------------------------------------------------------------
mapping query_cmdlist()
{
    return ([
    "srchant"   : "srchant",
	"srhelp"	: "srhelp",
	"harmony"	: "harmony",
    ]);
}
