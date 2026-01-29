/* this file is to be inherited by guarded rooms in goblin caves */
#include "../local.h"

inherit CAVE_BASE;

object *guards;
int    ggg;

void set_guards(int i)
{
    guards = allocate(i);
    ggg = i;
}

int add_exit(string room, string dir)
{
    return ::add_exit(room,dir,"@@block_exit:"+file_name(TO)+"|"+room+"@@");
}

int block_exit(string room)
{
    int i=0;

    if(TP->query_prop(LIVE_O_LAST_ROOM) == find_object(room)) return 0;

    while((i<ggg) && 
      (!guards[i] || !present(guards[i], TO) || !TP->check_seen(guards[i])))
	i++;
    if(i<ggg)
    {
	TP->catch_msg(QCTNAME(guards[i])+" stops you from passing.\n");
	say(QCTNAME(TP)+" was stopped by "+QTNAME(guards[i])+" from passing.\n");
	return 1;
    }
    return 0;
}


void
reset_shire_room()
{
    int i;
    seteuid(getuid());
    for(i=0; i<sizeof(guards); i++)
	if(!guards[i] || !present(guards[i]))
	{
	    if (!random(6))  // 25% of golins are huge
		guards[i] = clone_object(GOBLIN_NPC_DIR + "goblin_sup");
	    else
		guards[i] = clone_object(GOBLIN_NPC_DIR + "goblin_high");
	    guards[i]->add_prop(LIVE_I_SEE_DARK, 4);
	    guards[i]->arm_me();
	    guards[i]->move_living("M", TO);
	    tell_room(TO, QCTNAME(guards[i])+" arrives attracted by the noise.\n");
	}
}
