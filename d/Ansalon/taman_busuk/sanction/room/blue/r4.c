#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/sanction/local.h"
#include "/d/Ansalon/guild/dragonarmy/guild.h"
#include <macros.h>

#define ONE_OF(x) ((x)[random(sizeof(x))])

inherit SANCOUTROOM;

int times_to_allow_more_guards = 2;
int number_of_guards_died = 0;

object *guards = allocate(6);
void summon_guards();
object mean_guard;
object mean_guard2;

void
reset_sanction_room()
{
    setuid();
    seteuid(getuid());
    summon_guards();
    times_to_allow_more_guards = 2;
    number_of_guards_died = 0;

    if(!present("_nav_bda_mean_guard", this_object()))
    {
        mean_guard = clone_object("/d/Ansalon/taman_busuk/sanction/npc/mean_guard");
        mean_guard->arm_me();
        mean_guard->move(this_object(), 1);

        mean_guard2 = clone_object("/d/Ansalon/taman_busuk/sanction/npc/mean_guard4");
        mean_guard2->arm_me();
        mean_guard2->move(this_object(), 1);
    }
}

void summon_guards()
{

   for(int i=0; i<sizeof(guards); i++)
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
		switch(random(5))
		{
		case 0:
		case 1..2:
		    guards[i] = clone_object(DRAGONARMY_NPC+"aurak");
		    break;
		case 3:
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
	    guards[i]->command("say I have to guard the armoury!");
	    tell_room(E(guards[i]), QCTNAME(guards[i])+" runs away.\n");
	    guards[i]->move_living("M", TO, 1, 1);
	    tell_room(TO, QCNAME(guards[i])+
	      " enters and takes the guard post.\n");
	}
    }
}

void
create_sanction_room()
{
    set_short("within an encampment of the Blue Dragonarmy");
    set_long("@@long_descr");

    add_item(({"encampment","tents"}),
      "Surrounding you is an encampment of the Blue Dragonarmy.\n");
    add_item(({"large tent","large canvas tent","canvas tent","command center"}),
      "To your east rises the command center for the Blue " +
      "Dragonarmy stationed here in Sanction.\n");
    add_item(({"small tent","armoury"}),
      "This heavily guarded tent is the armoury for the Blue Dragonarmy.\n");
    add_item("tent","Which tent do you want to look at? "+
      "The large canvas tent or the small tent?\n");

    add_exit(SBLUE + "armoury","north","@@enter_armoury@@");
    add_exit(DGUILD + "joinroom_blue","east","@@check_enemy@@");
    add_exit(DGUILD + "train_blue","northeast","@@check_enemy@@");
    add_exit(SBLUE + "r2","south","@@check_enemy@@");

    reset_room();
}


int check_enemy()
{
  object mean_guard = present("_nav_bda_mean_guard", this_object());
  if(!mean_guard)
  {
    return 0; // let them leave.
  }
  if(TP->query_prop("_i_attacked_bda_guild_home"))
  {
      // If they have this prop it means they were warned!
      if(!TP->query_prop("_i_received_bda_guild_attack_warning"))
      {
          mean_guard->command("shout I will let you leave this once, but don't you ever come back!");
          TP->add_prop("_i_received_bda_guild_attack_warning", 1);
      }
      else
      {
          TP->catch_tell("The "+mean_guard->short()+" prevents you from leaving!\n");
          mean_guard->command("emote says: You were warned, you should not have come back!");
          mean_guard->attack_object(TP);
          tell_room(this_object(), "The "+mean_guard->short()+" prevents "+QTNAME(TP)+
                    " from leaving!\n", TP);
          return 1;
      }
  }
  return 0;
}


int
enter_armoury()
{
    int i;
    object guard = 0;
    object mean_guard = present("_nav_bda_mean_guard", this_object());

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
	if(TP->query_dragonarmy_division() != "blue" &&
           TP->query_wiz_level() == 0)
	{
	    write(guard->query_The_name(TP)+" on guard stays so that not even a mouse "+
	      "could sneak past him into the armoury.\n");
	    return 1;
	}
	write(guard->query_The_name(TP)+" lets you into the armoury.\n");
	tell_room(TO, QCTNAME(guard)+" lets "+QTNAME(TP)+
	  " into the armoury.\n", TP, TP);
	return 0;
    }
    else if (mean_guard && TP->query_dragonarmy_division() != "blue" &&
      TP->query_wiz_level() == 0)
    {
       TP->catch_tell("The "+mean_guard->short()+" stops you from entering the armoury!\n");
       tell_room(this_object(), "The "+mean_guard->short()+" stops "+QTNAME(TP)+
                 " from entering the armoury!\n", TP);
       return 1;
    }
    else
    {
      if (TP->query_dragonarmy_division() != "blue" && TP->query_wiz_level() == 0)
      {
	write("A strange energy prevents you from going north.\n");
	return 1;
      }
    }
    return 0;
}

string
long_descr()
{
    return tod_short_descr()+ "You stand within " +
    "an encampment of the Blue Dragonarmy. " +
    "To your east rises a large canvas tent, while a " +
    "smaller, yet more heavily guarded, one stands to " +
    "your north. " +season()+ "\n";
}

void
draconian_guard_died()
{
    number_of_guards_died++;
    if(times_to_allow_more_guards>0 && number_of_guards_died >4)
    {
      tell_room(this_object(), "Someone shouts: More guards to protect the Armoury!\n");
      set_alarm(itof(2+random(6)), 0.0, &summon_guards());
      times_to_allow_more_guards--;
      number_of_guards_died = 0;
    }
}


public void
enter_inv(object ob, object from)
{

  ::enter_inv(ob, from);
  if(interactive(ob))
  {
    if(ob->query_guild_name_occ() == "Secret Society of Uncle Trapspringer")
    {
      if(present(mean_guard, this_object()))
      {
        mean_guard->command("shout Kender Alert! Kender Alert! Enemies are invading our camp!");
        mean_guard->command("kill " + OB_NAME(ob));
        mean_guard->command("kill " + OB_NAME(ob));    
        mean_guard->attacked_by(ob);
      }      
      if(present(mean_guard2, this_object()))
      {
        mean_guard2->command("shout Enemies are invading our camp! To Arms! Get the pecks!");
        mean_guard2->command("kill " + OB_NAME(ob));
        mean_guard2->command("kill " + OB_NAME(ob));
        mean_guard2->attacked_by(ob); 
      }      
    }

    if(ob->query_guild_name_occ() == "Dwarven Warriors of the Neidar Clan")
    {
      if(present(mean_guard, this_object()))
      {
        mean_guard->command("shout Enemies are invading our camp! To Arms! Get the stinking dwarves!");
        mean_guard->command("kill " + OB_NAME(ob));
        mean_guard->command("kill " + OB_NAME(ob));
        mean_guard->attacked_by(ob);
      }      
      if(present(mean_guard2, this_object()))
      {
        mean_guard2->command("shout Enemies are invading our camp! To Arms! Get the stinking dwarves!");
        mean_guard2->command("kill " + OB_NAME(ob));
        mean_guard2->command("kill " + OB_NAME(ob));
        mean_guard2->attacked_by(ob);
      }      
    }
  }
}

