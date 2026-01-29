/*
*   by Amelia, for use in the Light Forest, frog pond
*	this is the famous frog for the frog tour
*	revised 20/6/95
*       bug fixed, Maniac, 25/11/95
*/
inherit "std/object";
#include "../pond.h"
#include <stdproperties.h>
#include <macros.h>

int id;

create_object()
{
	set_name("frog");
	add_name("bullfrog");
	add_name("jeremiah");
	set_short("large green bullfrog");
	set_pshort("large green bullfrogs");
	set_long("A large green bullfrog. He looks like he might be "+
        "hard to catch.\nHe reminds you of a story you heard once...\n"+
        "He looks ugly.\n"+
        "He is feeling very well.\n");
	add_prop(OBJ_I_VALUE, 0);
	add_prop(OBJ_I_WEIGHT, 50);
	add_cmd_item(({"frog","bullfrog"}), "kiss", "@@kiss_me");
	add_cmd_item(({"frog","bullfrog"}),"kill", "@@kill_me");
	add_cmd_item(({"frog","bullfrog"}),"catch", "@@catch_frog");
	add_cmd_item(({"all"}), "get", "@@no_get");
	add_prop(OBJ_I_VOLUME, 50);
	add_cmd_item(({"frog", "bullfrog"}), "get", "@@no_get");

}

void
enter_env(object ob, object from)
{

	::enter_env(ob,from);
	if (interactive(ob))
	id = set_alarm(10.0, 0.0, "croak", ob);
}

void
leave_env(object ob, object to)
{

	::leave_env(ob,to);
	if(interactive(ob))
	{
	remove_alarm(id);
	id = set_alarm(5.0,0.0, "hop_away");
	}
}

int
croak(object ob)
{
	tell_room(environment(ob),"Ribbit! Ribbit!\n",({}));
	id = set_alarm(45.0, 0.0, "croak", ob);
}

int
hop_away(object ob)
{

	seteuid(getuid(TO));
	TO->remove_object();
	tell_room(environment(TP), "The frog leaps quickly away.\n", ({}));
	
}


int
kiss_me()
{
    object shadow, cr, fr, dummy, nt;

    object tp = TP;
	
    if (present(this_object(), tp)) {
        seteuid(getuid(TO));
        write("You gently kiss the frog.\n");
        tell_room(environment(tp), QCTNAME(tp)+ " gently "+
                  "kisses the frog.\n", ({tp}));
        if (!tp->test_bit(FQ_DOMAIN, FQ_GROUP, FQ_BIT)) 
        { 
        tell_room(environment(tp), "POUF!!\n", ({}));
	shadow = clone_object(FROG_SHADOW);
	shadow->shadow_me(tp);
	shadow->destruct_frog_shadow();
	if (tp->query_prop(PLAYER_I_FOUND_NET) &&
		tp->query_prop(PLAYER_I_FOUND_FROG) &&
		tp->query_prop(PLAYER_I_CAUGHT_FROG))
	{
		tp->add_exp(FQ_XP);
		tp->set_bit(FQ_GROUP, FQ_BIT);
		tp->command("save");
		log_file("frog_quest", tp->query_name()+
			" "+ ctime(time())+".\n");
		write("You feel more experienced!\n");
		write("You feel an overwhelming urge to "+
		"exercise your player rights!\n");
		tp->remove_prop(PLAYER_I_FOUND_NET);
		tp->remove_prop(PLAYER_I_FOUND_FROG);
		tp->remove_prop(PLAYER_I_CAUGHT_FROG);
        }
	}
	TO->hop_away(dummy);
	return 1;
	}
    else
        return 0;
}


int
kill_me()
{
    object dummy;

    tell_room(environment(TP),"The frog makes a giant "+
              "leap and escapes!\n", ({}));
    TO->hop_away(dummy);
    return 1;
}


int
no_get()
{
	tell_room(environment(TP), QCTNAME(TP)+ " tries to "+
		"get the frog, but fails.\n", ({TP}));
	write("You try to get the frog, but he's too slippery "+
		"to catch with your bare hands.\n");
	return 1;
}


int
catch_frog()
{
        object tp = TP;
	object n = present("net", tp);

	if (objectp(n)) {
            if (tp==n->query_wielded()) {
		write("You catch the frog with the net!\n");
		TO->move(tp);
		tell_room(environment(tp), QCTNAME(tp)+
		    " catches the frog deftly with "+
		    tp->query_possessive()+" net.\n", ({tp}));
		    tp->add_prop(PLAYER_I_CAUGHT_FROG, 1);
		n->remove_object();
                write("You lose your grip on the net. It drops, "+
                       "and you lose sight of where it went.\n");
                tell_room(environment(tp), QCTNAME(tp)+
                        " drops the net, and you lose sight of "+
                        "where it went.\n", tp);
		return 1;
           }
	   else {
               notify_fail("But you're not wielding the net!\n");
               return 0;
           }
       }
    else {
        notify_fail("The frog is too slippery. You " +
                    "can't catch him with your bare hands.\n");
        return 0;
   }
}

