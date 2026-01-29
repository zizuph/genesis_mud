/* Altered by Navarre June 7th 2006 to avoid endless killing */
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/guild/dragonarmy/guild.h"
#include "/d/Ansalon/taman_busuk/sanction/local.h"
#include <macros.h>

inherit SANCOUTROOM;

void summon_guards();

int times_to_allow_more_guards = 2;
int number_of_guards_died = 0;

object *guards = allocate(6);
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
    if(!present("_nav_rda_mean_guard", this_object()))
    {
        mean_guard = clone_object("/d/Ansalon/taman_busuk/sanction/npc/mean_guard2");
        mean_guard->arm_me();
        mean_guard->move(this_object(), 1);

        mean_guard2 = clone_object("/d/Ansalon/taman_busuk/sanction/npc/mean_guard3");
        mean_guard2->arm_me();
        mean_guard2->move(this_object(), 1);
    }
}

void sound_alarm(object who, string str)
{
    who->command("shout "+str);
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
	else if(!guards[i]->query_attack() && E(guards[i]) != TO)
	{
	    tell_room(E(guards[i]), QCTNAME(guards[i])+" runs away.\n");
	    guards[i]->move_living("M", TO, 1, 1);
	    tell_room(TO, QCNAME(guards[i])+
	      " enters and takes the guard post.\n");
	}
    }
}

object *guards_present()
{
    int i;
    object *ob = ({});

    for(i=0; i<sizeof(guards); i++)
	if(guards[i] && E(guards[i]) == TO)
	    ob += ({ guards[i] });
    return ob;
}

int
enter_armoury()
{
    object *ob = guards_present();
    object mean_guard = present("_nav_rda_mean_guard", this_object());

    if(sizeof(ob))
    {
	if(TP->query_dragonarmy_division() != "red" && !TP->query_wiz_level())
	{
	    write(ob[0]->query_The_name(TP)+" on guard stays so that not even a mouse "+
	      "could sneak past him into the armoury.\n");
	    return 1;
	}
 	write(ob[0]->query_The_name(TP)+" lets you into the armoury.\n");
	tell_room(TO, QCTNAME(ob[0])+" lets "+QTNAME(TP)+
	  " into the armoury.\n", TP, TP);
	return 0;
    }
    else if(mean_guard && TP->query_dragonarmy_division() != "red" && !TP->query_wiz_level())
    {
       TP->catch_tell("The "+mean_guard->short()+" stops you from entering the armoury!\n");
       tell_room(this_object(), "The "+mean_guard->short()+" stops "+QTNAME(TP)+
                                " from entering the armoury!\n", TP);
       return 1;
    } 
    else
    {
      if (TP->query_dragonarmy_division() != "red" && !TP->query_wiz_level())
      {
	write("A strange energy prevents you from going southwest.\n");
	return 1;
      }
    }
    return 0;
}

int check_enemy()
{
  object mean_guard = present("_nav_rda_mean_guard", this_object());
  if(!mean_guard)
  {
    return 0; // let them leave.
  }
  if(TP->query_prop("_i_attacked_rda_guild_home"))
  {
      if(!TP->query_prop("_i_received_rda_guild_attack_warning"))
      {
          mean_guard->command("shout I will let you leave this once, but don't you ever come back!");
          TP->add_prop("_i_received_rda_guild_attack_warning", 1);
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
enter_startroom()
{
    object *ob = guards_present();
    object mean_guard = present("_nav_rda_mean_guard", this_object());
 
   int s = sizeof(ob);
   if(s)
   {
	if(TP->query_dragonarmy_division() != "red" && !TP->query_wiz_level())
	{
	  write(ob[0]->query_The_name(TP)+" on guard stays so that not even a mouse "+
		"could sneak past him into the barracks.\n");
	  return 1;
	}
	write(ob[0]->query_The_name(TP)+" lets you into the barracks.\n");
	tell_room(TO, QCTNAME(ob[0])+" lets "+QTNAME(TP)+
		  " into the barracks.\n", TP, TP);
   }
   else if(mean_guard)
   {
       if(TP->query_dragonarmy_division() != "red" && !TP->query_wiz_level())
       {
	 TP->catch_tell("The "+mean_guard->short()+" stops you from entering the sleeping hall!\n");
	 tell_room(this_object(), "The "+mean_guard->short()+" stops "+QTNAME(TP)+
		   " from entering the sleeping hall!\n", TP);
	 return 1;
       }
       else
       {
	   write(mean_guard->query_The_name(TP)+" lets you into the barracks.\n");
	   tell_room(TO, QCTNAME(mean_guard)+" lets "+QTNAME(TP)+
		     " into the barracks.\n", TP, TP);
	   return 0;
       }
   }
   else
   {
     if(TP->query_dragonarmy_division() != "red" && !TP->query_wiz_level())
     {
	 write("A strange energy prevents you from going west.\n");
	 return 1;
     }
   }
   return 0;
}

void
create_sanction_room()
{
    set_short("encampment of the Red Dragonarmy");
    set_long("@@long_descr");

    add_item(({"encampment","orderly encampment"}),
             "This is an encampment of the Red Dragonarmy, one of the most " +
             "formidable forces on Ansalon.\n");
    add_item(({"large tent","tent","barracks"}),
             "Before you stands a large tent, used to house the many " +
             "soldiers of the Red Dragonarmy stationed here.\n");
    add_item(({"small stone building","stone building","building",
                   "military depot","depot"}),
             "This small stone building is the military dump for " +
             "equipment of the Red Dragonarmy.\n");

    add_exit(DRAGONARMY_ROOM + "start_red","west",enter_startroom);
    add_exit(SRED + "r2","southeast", "@@check_enemy@@");
    add_exit(SRED + "armoury","southwest",enter_armoury);

    reset_room();
}


string
long_descr()
{
    return tod_short_descr()+ "You stand within an orderly encampment of the "+
    "red dragonarmy. To your west stands a large tent, the barracks of " +
    "the soldiers stationed in Sanction. To your southwest stands " +
    "a small stone building, a military depot, where an arsenal " +
    "of weapons and equipment are stored.\n";
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
