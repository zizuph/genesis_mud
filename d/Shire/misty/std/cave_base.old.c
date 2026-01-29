/* this file is to be inherited by rooms in goblin caves */
#include <ss_types.h>
#include <filter_funs.h>
#include "../local.h"

inherit SHIRE_ROOM;

#ifndef ROOM_I_NO_ALLOW_STEED
#define ROOM_I_NO_ALLOW_STEED   "_room_i_no_allow_steed"
#endif


/* Global variables */
string pull_room, push_room, pull_dir, push_dir;

/* Prototypes */
void reset_shire_room();

/* This is function to be used instead of create_room() */
void create_cave(){}

void
create_shire_room()
{
    set_short("@@my_short");
    set_long("@@my_long");
    add_item(({"wall","walls"}),"When you examine the wall more closely "+
      "you have strange feeling. It reminds you of all the stories "+
      "about the secret doors. Maybe this wall is not a wall but "+
      "something else. Who knows?\n");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, -1);
    add_prop(ROOM_I_NO_ALLOW_STEED, 1);
    add_prop(OBJ_S_SEARCH_FUN, "search_wall");
    add_prop(OBJ_I_SEARCH_TIME, 15);

    create_cave();
    reset_shire_room();
}

string my_long()
{
    string str;
    int i = sizeof(TO->query_exit_cmds());
    switch(i)
    {
    case 0: str = "You are in a room without exits"; break;
    case 1: str = "You are at the end of a tunnel"; break;
    case 2: str = "You are in a tunnel"; break;
    default: str = "You are at a branch of the tunnels";
    }
    return str+" "+
    "under the Misty Mountains. It is very humid and the walls are damp "+
    "with condensed water. You seriously hope that you are not lost because "+
    "every tunnel looks much the same as the last...\n";
}

string my_short()
{
    int i = sizeof(TO->query_exit_cmds());
    switch(i)
    {
    case 0: return "The room without exits";
    case 1: return "The end of the tunnel";
    case 2: return "The tunnel";
    default: return "The branch of the tunnels";
    }
}

void
reset_shire_room()
{
    object goblin;
    int i,j;
    seteuid(getuid());
    if((!present("_misty_goblin_")) && random(2))
    {
	if(sizeof(FILTER_LIVE(all_inventory(TO))))
	{
	    set_alarm(itof(5+random(10)), 0.0, "more_goblins");
	    return;
	}

	for(i=random(2); i && (j < 4); i=random(2))
	{
	    goblin = clone_object(GOBLIN_BASE);
	    goblin->arm_me();
	    goblin->move_living("M", TO);
	    j++;
	}

	if(j > 3) set_alarm(itof(5+random(10)), 0.0, "more_goblins");
    }
}

void more_goblins()
{
    object goblin;
    goblin = clone_object(GOBLIN_BASE);
    goblin->arm_me();
    goblin->move_living("M", TO);
    tell_room(TO, QCTNAME(goblin)+" arrives attracted by the noise.\n");
    if(random(2)) set_alarm(itof(5+random(10)), 0.0, "more_goblins");
}
void

init()
{
    ::init();
    add_action("push_something", "push");
    add_action("pull_something", "pull");
}

void set_pull(string room, string dir)
{
    pull_room = room; pull_dir = dir;
}
void set_push(string room, string dir)
{
    push_room = room; push_dir = dir;
}

#ifndef TEMP_CLOSE_FOR_MOVE
int pull_something(string str)
{
    object *team;
    int i;

    if(pull_room &&
      ((str=="wall") || (str=="walls") ||
	(str==pull_dir+" wall") || (str==pull_dir+" walls")))
    {
	if(CAN_SEE_IN_ROOM(TP))
	{
	    if(TP->query_stat(SS_STR)>60)
	    {
		TP->catch_msg("You pull the wall revealing small opening.\n");
		say(QCTNAME(TP)+" pulls the wall revealing small opening.\n");
		if(sizeof(team = TP->query_team()))
		    for(i=0; i<sizeof(team); i++)
			if(present(team[i], ENV(TP)))
			{
			    team[i]->move_living("through opening", pull_room);
			    team[i]->catch_msg("You leave through opening.\n");
			}
		TP->catch_msg("You pass and close opening in wall.\n");
		TP->move_living("through opening and closes it behind",pull_room,1);
	    }
	    else
	    {
		TP->catch_msg("You pull the wall with all your strength. It " +
		  "starts to move but sudenly stops. Maybe you should eat more " +
		  "spinach.\n");
		say(QCTNAME(TP)+" pulls the wall but it doesn't give way.\n");
	    }
	}
	else
	{
	    TP->catch_msg("You try to pull some walls in the dark but " +
	      "nothing happens.\n");
	    say(QCTNAME(TP)+" tries to pull some walls.\n");
	}
	return 1;
    }
    if((str=="wall") || (str=="walls"))
    {
	TP->catch_msg("You try to pull some walls but nothing happens.\n");
	say(QCTNAME(TP)+" tries to pull some walls.\n");
	return 1;
    }
    return 0;
}

int push_something(string str)
{
    object *team;
    int i;

    if(push_room &&
      ((str=="wall") || (str=="walls") ||
	(str==push_dir+" wall") || (str==push_dir+" walls")))
    {
	if(CAN_SEE_IN_ROOM(TP))
	{
	    if(TP->query_stat(SS_STR)>47)
	    {
		TP->catch_msg("You push the wall revealing small opening.\n");
		say(QCTNAME(TP)+" pushes the wall revealing small opening.\n");
		if(sizeof(team = TP->query_team()))
		    for(i=0; i<sizeof(team); i++)
			if(present(team[i], ENV(TP)))
			{
			    team[i]->move_living("through opening", push_room);
			    team[i]->catch_msg("You leave through opening.\n");
			}
		TP->catch_msg("You pass and close opening in wall.\n");
		TP->move_living("through opening and closes it behind",push_room,1);
	    }
	    else
	    {
		TP->catch_msg("You push the wall with all your strength. It " +
		  "starts move but sudenly stops. Maybe you should eat more " +
		  "spinach.\n");
		say(QCTNAME(TP)+" pushes the wall but it doesn't give way.\n");
	    }
	}
	else
	{
	    TP->catch_msg("You try to push some walls in the dark but " +
	      "nothing happens.\n");
	    say(QCTNAME(TP)+" tries to push some walls.\n");
	}
	return 1;
    }
    if((str=="wall") || (str=="walls"))
    {
	TP->catch_msg("You try to push some walls but nothing happens.\n");
	say(QCTNAME(TP)+" tries to push some walls.\n");
	return 1;
    }
    return 0;
}
#else
int push_something(string str)
{
    if (str == "wall" || str == "walls")
    {
	TP->catch_msg("For some reason you are unable to push the walls... "+
	  "they don't seem to want to move anymore.\n");
	say(QCTNAME(TP) + " tries to push some walls but fails.\n");
	return 1;
    }

    NFN("Push what?");
    return 0;
}

int pull_something(string str)
{
    NFN("Pull what?");

    if (str == "walls" || str == "wall")
    {
	TP->catch_msg("You try to pull at the walls but they do not "+
	  "seem to wish to move anymore.\n");
	say(QCTNAME(TP) + " tries to pull some walls but fails.\n");
	return 1;
    }

    return 0;
}
#endif

string search_wall(object who, string str)
{
    string sss = "";

    if((pull_room || push_room) && ((str=="wall") || (str=="walls")) &&
      (who->query_skill(SS_AWARENESS)+who->query_stat(SS_WIS) > 100))
    {
	if(pull_dir) sss += pull_dir;
	if(push_dir)
	{
	    if(pull_dir) sss += " and "+push_dir;
	    else sss += push_dir;
	}
	return "After careful searching you decided that "+sss+
	" walls are very strange. Maybe you have found a "+
	"secret door. Now the challenge is figuring out how they open.\n";
    }
}

