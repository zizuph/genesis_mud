/* Modified June 7th 2006 by Navarre to stop endless guards. */


#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/sanction/local.h"
#include "/d/Ansalon/guild/dragonarmy/guild.h"
#include <macros.h>

inherit SANCOUTROOM;


int times_to_allow_more_guards = 2;
int number_of_guards_died = 0;

object *guards = allocate(6);
void summon_guards();

void
reset_sanction_room()
{
    setuid();
    seteuid(getuid());
    summon_guards();
    times_to_allow_more_guards = 2;
    number_of_guards_died = 0;    
}

void summon_guards()
{
    int i;
    for(i=0; i<sizeof(guards); i++)
    {
	if(!guards[i])
	{
	    if (random(7))
	    {
		guards[i] = clone_object(SNPC + "da_member");
		guards[i]->set_color("blue");
		guards[i]->set_dragonarmy_rank(random(4) ? 1 : 2);
		guards[i]->arm_me();
	    }
	    else
	    {
		switch(random(3))
		{
		case 0:
		    guards[i] = clone_object(DRAGONARMY_NPC+"aurak");
		    break;
		case 1:
		    guards[i] = clone_object(DRAGONARMY_NPC+"sivak");
		    break;
		default:
		    guards[i] = clone_object(DRAGONARMY_NPC+"bozak");
		}
		guards[i]->set_color("blue");
		guards[i]->arm_draconian();
	    }
	    if(i>1)
		guards[i]->set_hunt_enemy(1);
	    guards[i]->move_living("M", TO, 1, 1);
	    tell_room(TO, QCNAME(guards[i])+
	      " enters and takes the guard post.\n");
	}
	else if(!guards[i]->query_attack() && E(guards[i]) != TO)
	{
	    guards[i]->command("say I have to guard the board!");
	    tell_room(E(guards[i]), QCTNAME(guards[i])+" runs away.\n");
	    guards[i]->move_living("M", TO, 1, 1);
	    tell_room(TO, QCNAME(guards[i])+
	      " enters and takes the guard post.\n");
	}
    }
}

int
enter_board()
{
    int i;
    object guard = 0;

    for(i=0; i<sizeof(guards); i++)
    {
	if(guards[i] && E(guards[i]) == TO)
	{
	    guard = guards[i];
	    break;
	}
    }
    if(guard)
    {
	if(TP->query_dragonarmy_division() != "blue" && !TP->query_wiz_level())
	{
	    write(guard->query_The_name(TP)+" on guard stays so that not even a mouse "+
	      "could sneak past "+HIM(guard)+" into the tent.\n");
	    return 1;
	}
	write(guard->query_The_name(TP)+" lets you into the tent.\n");
	tell_room(TO, QCTNAME(guard)+" lets "+QTNAME(TP)+" into the tent.\n", TP, TP);
	return 0;
    }
    return 0;
}

void
create_sanction_room()
{
    set_short("within an encampment of the Blue Dragonarmy");
    set_long("@@long_descr");

    add_item(({"encampment","tents"}),
      "Surrounding you is an encampment of the Blue Dragonarmy. " +
      "To your south and southeast stand two tents that you " +
      "could probably enter.\n");
    add_item(({"mountains","khalkhist mountains"}),
      "Surrounding the city of Sanction is the most desolate " +
      "area of the Khalkist Mountains, the Doom Range.\n");

    add_exit(SBLUE + "r3","north",0);
    add_exit(SBLUE + "r2","northwest",0);
    add_exit(SBLUE + "board","southeast",enter_board);
    add_exit(SBLUE + "tent3","south",0);

    reset_room();
}

string
long_descr()
{
    return tod_short_descr()+ "You stand in the middle " +
    "of an encampment of the Blue Dragonarmy. " +
    "To your south and southeast rise tents that you could " +
    "probably enter. "+
    season()+ "\n";
}

void
draconian_guard_died()
{
    number_of_guards_died++;
    if(times_to_allow_more_guards>0 && number_of_guards_died >4)
    {
      tell_room(this_object(), "Someone shouts: More guards! We need more guards!\n");
      set_alarm(itof(2+random(6)), 0.0, &summon_guards());
      times_to_allow_more_guards--;
      number_of_guards_died = 0;
    }
}
