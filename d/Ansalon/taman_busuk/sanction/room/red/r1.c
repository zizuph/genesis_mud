/* Modified by Navarre to avoid endless npcs */


#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/guild/dragonarmy/guild.h"
#include "/d/Ansalon/taman_busuk/sanction/local.h"
#include <macros.h>

inherit SANCOUTROOM;

int times_to_allow_more_guards = 2;
int number_of_guards_died = 0;

object *guards = allocate(4);
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
    int i,enforce = 0;

    setuid();
    seteuid(getuid());

    for(i=0; i<sizeof(guards); i++)
    {
	if(!guards[i])
	{
	    enforce = 1;
	    if (random(7))
	    {
		guards[i] = clone_object(SNPC + "da_member");
		guards[i]->set_color("red");
		guards[i]->set_dragonarmy_rank(random(4) ? 1 : 2);
		guards[i]->arm_me();
	    }
	    else
	    {
		switch(random(5))
		{
		case 0:
		case 1:
		    guards[i] = clone_object(DRAGONARMY_NPC+"aurak");
		    break;
		case 2:
		case 3:
		    guards[i] = clone_object(DRAGONARMY_NPC+"sivak");
		    break;
		default:
		    guards[i] = clone_object(DRAGONARMY_NPC+"bozak");
		}
		guards[i]->set_color("red");
		guards[i]->arm_draconian();
	    }

	    if(i>1)
		guards[i]->set_hunt_enemy(1);
	    guards[i]->move_living("M", TO, 1, 1);
	    tell_room(TO, QCNAME(guards[i])+
		" enters and takes the guard post.\n");
	}
	else if(guards[i]->query_attack())
	{
	    enforce = 1;
	}
	else if(E(guards[i]) != TO)
	{
	    enforce = 1;
	    tell_room(E(guards[i]), QCTNAME(guards[i])+" runs away.\n");
	    guards[i]->move_living("M", TO, 1, 1);
	    tell_room(TO, QCNAME(guards[i])+
		" enters and takes the guard post.\n");
	}
    }
    if(!enforce)
    {
	for(i=0; 2<sizeof(guards); i++)
	{
	    guards[2]->remove_object();
	    guards -= ({ guards[2] });
	}
	if(i)
	{
	    tell_room(TO, C(LANG_WNUM(i))+" guard"+(i>1 ? "s" : "")+
		" returned to the guardhouse.\n");
	}
    }
}

int
enter_camp() 
{
    int i;
    object guard = 0;
    object *team;

    for(i=0; i<sizeof(guards); i++)
	if(guards[i] && E(guards[i]) == TO && TP->check_seen(guards[i]))
	{
	    guard = guards[i];
	    break;
	}
    if(guard)
    {
         if (IS_MEMBER(TP) || IS_MEMBER(TP->query_leader()) ||
            TP->query_guild_name_occ() == "Priests of Takhisis"
        || (!TP->query_guild_name_occ() && TP->query_alignment() < -200))
        {
            write(guard->query_The_name(TP)+" lets you into the camp.\n");
            return 0;
        }

        team = TP->query_team_others();
        for(i=0; i<sizeof(team); i++)
        {
            if (IS_MEMBER(team[i]) ||
                team[i]->query_guild_name_occ() == "Priests of Takhisis"
                || (!TP->query_guild_name_occ() && TP->query_alignment() < -200))
            {
                write(guard->query_The_name(TP)+" lets you into the camp.\n");
                return 0;
            }
        }

        write(guard->query_The_name(TP)+" stops you.\n");
        guard->command("say Only potential recruits or those in the company of "+
            "dragonarmy soldiers may enter!");
        return 1;
    }

    return 0;
}

void
create_sanction_room()
{
    set_short("On a path before an encampment of the Red Dragonarmy");
    set_long("@@long_descr");

    add_item(({"river of lava","lava","river"}),
      "To your south flows a great river of lava. Its presence makes " +
      "this area seem frightfully hellish.\n");
    add_item(({"bridge","stone bridge"}),
      "To your south is a stone bridge that crosses the river of lava " +
      "before you.\n");
    add_item(({"sanction","city"}),
      "To your south across the bridge is the nightmarish city " +
      "of Sanction.\n");
    add_item("encampment","To your north stands the orderly encampment " +
      "of the Red Dragonarmy.\n");
    add_item(({"guardhouse","door"}),
      "To your west stands a small guardhouse made of " +
      "black stone. The door has been left open it seems to " +
      "let the heat out.\n");
    add_item(({"black stone","stone"}),
      "The guardhouse to your west seems to be made of black stone, " +
      "most likely basalt.\n");
    add_item("path","A path leads up the side of one of the " +
      "volcanoes here to a large temple that stands near the " +
      "top.\n");
    add_item(({"temple","large temple"}),
      "Near the top of the volcano stands a large temple. It looks " +
      "like it has been created to look like the ghastly head " +
      "of a dragon.\n");
    add_item(({"volcano","volcanoes"}),
      "To your northest rises one of the Lords of Doom.\n");

    add_exit(SRED + "bridge","south",0);
    add_exit(SRED + "r2","north",enter_camp);
    add_exit(SRED + "r4","northeast",0);
    add_exit(SRED + "guardhouse","west",0);

    reset_room();
}

string
long_descr()
{
    return tod_short_descr()+ "You stand to the north of a " +
    "great river of lava that flows past you from " +
    "the east to the west. A bridge crosses it to your south into " +
    "the heart of Sanction while to your north you can enter " +
    "the encampment of the red dragonarmy. A guardhouse made " +
    "of black stone stands to your west, while a path heads up " +
    "the side of one of the volcanoes to your northeast.\n";
}

void
draconian_guard_died()
{
    number_of_guards_died++;
    if(times_to_allow_more_guards>0 && number_of_guards_died >2)
    {
      tell_room(this_object(), "Someone shouts: More guards! We need more guards!\n");
      set_alarm(itof(2+random(6)), 0.0, &summon_guards());
      times_to_allow_more_guards--;
      number_of_guards_died = 0;
    }
}
