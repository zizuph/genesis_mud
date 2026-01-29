// file name: ~Avenir/common/dark/npc/lost.c
// creator(s): Denis
// revision history:
// purpose: Small tour person. Help her to get out of these tunnels.
// note: To solve the toor a player first should 
//       'rescue girl' or 'help small girl' or something like that.
//       Then he should guide her to a room which has no
//       ROOM_I_INSIDE property set and viola! Tour is solved.
//       The tour cannot be solved by evil player (alignment <- 10) -
//       girl will run away (remove_object()). Also if she is being
//       attacked she will run away too.
//       If she comes in room and sees a dark imp she might run back -
//       she is afraid of them, but in general she won't.
//
// bug(s):
// to-do:

inherit "/std/monster";
inherit "/std/act/domove";
inherit "/std/act/action";
inherit "/d/Avenir/inherit/quest";

#include "/d/Avenir/common/common.h"

object previous_room;

void
create_monster()
{
    if(!IS_CLONE)
        return;
    
    set_name("girl");
    set_race_name("girl");
    set_adj("small");
    set_short("small girl");
    set_long("A small crying girl absolutelly lost in tunnels. "+
	     "She seems to be wandering here for some time and she is "+
	     "afraid of anything.\n");
    set_gender(G_FEMALE);
    
    add_prop(LIVE_I_NEVERKNOWN,1);

    default_config_npc(5);
    
    set_act_time(15);
    add_act("@@act_hook");
}

/*-----[ Run away (self-destruct) if someone attacks us. ]-----*/
attacked_by(object ob)
{
    set_alarm(10.0,0.0,"run_away");
}

/*-----[ Emotions and look around for evil players to run away. ]-----*/
string act_hook()
{
    int i;
    object *players;
    object player;
    
    if(query_follow())
        return "";
    
    players=FILTER_PLAYERS(all_inventory(environment(TO)));
    for(i==0;i<sizeof(players);i++)
        if(players[i]->query_alignment()<-10)
        {	
            set_alarm(2.0,0.0,"run_away");
            return "emote looks around in fear.";
	}
    switch(random(4))
    {
    case 0:
        return "emote looks around crying.";
    case 1:
        return "cry";
    case 2:
	return "say Can you please help me to get out of here?";
    case 3:
	return "say Why didn't I listen to my mum? I wouldn't be here...";
    case 4:
	return "say Please guide me out of here.";
     case 5:
	return "emote tries to to hide.";
    }
}

/*-----[ Self destruct (run away) in dangerous situations. ]-----*/
run_away()
{
    command("emote runs away screaming.");
    remove_object();
}

void
init_living()
{
    ::init_living();
    add_action("rescue_func","rescue");
    add_action("rescue_func","help");
    add_action("rescue_func","save");
    add_action("rescue_func","guide");
}

/*-----[ Tracking commands ]-----*/
int rescue_func(string str)
{
    NF(capitalize(query_verb())+" whom?\n");
    if(str=="girl"||str=="lost girl"||str=="small girl"||
       str=="small lost girl"||str=="lost small girl"||
       str=="crying girl")
    {
	set_follow(this_interactive()->query_real_name());
	write("Small girl's face brightens and she stops crying.\n"+
	      "She says: Please guide me from these tunnels!\n"+
	      "She adds: And please don't go where these horrible "+
	      "monsters live, I am so afraid!\n"+
	      "Girl starts to follow you.\n");
	return 1;
    }
}

/*-----[ Examine the room we just have entere: ]-----*/
/*-----[ - is it outside (tour is over)        ]-----*/
/*-----[ - are there imps (maybe I am panicky? ]-----*/
enter_env(object dest, object old)
{
    object *monsters;
    
    ::enter_env(dest,old);
    if(query_follow()&&!dest->query_prop(ROOM_I_INSIDE))
    {
	set_alarm(5.0,0.0,"reward_func");
        return;
    }
	
    monsters=all_inventory(environment(TO));
    monsters=filter(monsters,"filter_fear",TO);
    if(sizeof(monsters)>0)
        if(!random(5))
        {
	    previous_room=old;
	    set_alarm(2.0,0.0,"return_back");
	}
}

/*--[ Return in previous room if we are too afraid imps in the new one ]--*/
return_back()
{
    tell_room(environment(TO),capitalize(short())+" runs back screaming.\n");
    move_living("M",previous_room);
    tell_room(environment(TO),capitalize(short())+" runs in screaming.\n");
}

int filter_fear(object ob)
{
    if(ob->query_name()=="Dark imp")
        return 1;
}

/*-----[ Reward experience ]-----*/
reward_func()
{
    object solver;
    
    solver=find_player(query_follow());
    command("say Thank you my savior!");
    command("kiss "+query_follow());
    command("emote runs away.");
    if(!solver->test_bit("Avenir",0,0))
    {
//        reward_quest("Rescue Girl", solver, X, X, 50, 100, 60);
// Need to redo the bits here before opening this quest! (Cirion)
    }
    remove_object();
}
