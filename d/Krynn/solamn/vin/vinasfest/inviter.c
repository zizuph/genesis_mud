/* Trumpeteer */

#include <std.h>
#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h";
#include "../local.h"
#include "../knight/guild.h"

inherit M_FILE
inherit VSTD + "vin_knight_base";

inherit "/std/act/action";

#include "vfest.c";
#include "vfest.h"

#define SCEPTRE "/d/Krynn/solamn/vin/vinasfest/sceptre"

string
my_answer()
{
    command("ksmooth");
    command("say to " + this_player()->query_name() + " I am supervising "+
            "sending out invitations. If you " +
            "want to <invite> someone please do so. You may also <request> " +
	    "an invitation for yourself as well.");
    command("smile slight");
    
    if (IS_CONCLAVE(this_player()))
    {
	command("whisper to " + this_player()->query_name() + " You may "+
	        "request sceptre that will allow you to control few things "+
		"during the event.\n");
    } 
    
    return "";
}

int
my_invite(string str)
{
    
    notify_fail("Request what? An invitation maybe?\n");
    if (!str)
     return 0;

    if ( (str == "sceptre") && (IS_CONCLAVE(this_player())) )
    {
        write("The knight gives you the sceptre.\n");
	command("kbow " + this_player()->query_name());
        clone_object(SCEPTRE)->move(this_player(),1);
	return 1;
    }

    if (( str == "an invitation" ) || ( str == "invitation"))
    {
	if (present("_vfest_invite_",this_player()))
	{
	   command("say to " + this_player()->query_name() +
		   " You already have an invitation.\n");
	   return 1;
	}
        command("emote pulls some cord and you hear bell ringing " +
	        "somewhere downstairs.\n");
	clone_object(INVITATION)->move(this_player(),1);
	return 1;
    }    
    return 0; // if else failed
}

string
my_long()
{
    return "This knight wears the golden ribbon across " + HIS(this_object()) +
           " chest indicating that " + HE(TO) + " is responsible for " +
	   "disposing invitations to Vinasfest. Maybe you should ask him " +
	   "about it?\n";
}

void
create_knight_npc()
{
    set_level(3);
    set_act_time(7);
    set_long("@@my_long@@");
    add_act("emote looks up something on a piece of parchment.");
    add_act("emote pulls the cord and young squire rushes in.\n" +
            QCTNAME(this_object()) + " gives the invitation to the squire and sends " +
	    "him on his way. The squire rushes out.");
    add_act("pace");
    add_act("emote looks at the list of guests and smiles contentedly"); 
    add_act("emote adds new name into the list of guests.");
    add_act("stretch");
    add_act("sneeze");
    set_default_answer("@@my_answer@@");
    add_ask("for invitation", "@@my_answer@@");
}

public void
init_living()
{
    if (interactive(TP) && TP->query_prop("_i_attacked_in_vingaard"))
	set_alarm(0.5, 0.0, "attack_func", TP);
    ::init_living();
    add_action("do_invite", "invite");
    add_action("my_invite", "request");
}

void
arm_me()
{
        command("kbow");
	command("ksmooth");
}

