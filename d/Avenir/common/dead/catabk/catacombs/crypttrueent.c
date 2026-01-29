// file name: crypt93
// creator: Ilyian (September 1, 1995)
// last update:
// purpose: Room in the underground crypts
// note: Most of the code for these rooms is in
//         dead.c - see that file for info on these rooms.
// bug(s):
// to_do:

inherit "/d/Avenir/common/dead/dead";
#include "../dead.h"

int skull1 = 0;
int skull2 = 1;
int skull3 = 2;

int deathroll = random(3);


public int
block_people()
{

   if (!present("greater_death_", TO))
   {
    write("You climb down the stairway.\n");
        return 0;
   }
   
   write("The shadowlike figure rasps: Only those who dares to face my test of true bravery may pass, for none " +
   "who fears me, Death, shall ever pass. I will put a silver coin inside one of these skulls, and " +
   "those selecting the skull with the coin, will die, so ye be warned. A warning for those with " +
   "low health and, or low natural constitution, I will deal a severe strike legardless " +
   "of success of failure of my test, so those who doubt in their stamina may try " +
   "at their own peril. Those who " +
   "dares, may 'select <orc/elf/human> skull' now at any time.\nThe shadowlike " +
   "figure points with a skeletal finger at the humanoid skulls at the stone altar.\n");
   return 1;     
}

int
query_deathroll()
{
	return deathroll;
}

void
kill_me()
{
	 write("Suddenly, a ghostly transparent scythe arrives from nowhere and " +
	 "cuts through you, for then to disappear again!\nApparently, you selected the " +
	 "skull with the silver coin.\n");
	 TP->set_hp(0);
	 TP->do_die(this_object());
	 return;
}

void
success_me()
{
	 write("Suddenly, a ghostly transparent scythe arrives from nowhere and " +
	 "cuts through you, for then to disappear again!\n");
	 
	 TP->heal_hp(-2300);    // Minimum survival size is 121+ con, which is 2300 hps.
	 
	 if (TP->query_hp() <= 0)
         {
            TP->do_die(this_object());
            return;
         }
         
         write("You feel little more experienced as you survived the scythe of " +
         "death.\nYou selected a skull without the silver coin and pass Death's " +
         "test.\nYou may enter the " +
         "crypt at will without further tests of Death.\nCongratulations!\n");
	 
	 return;
}


	

int
select_skull(string str)
{

     if (str == "elf skull")
     {
     	
     	write("You place your hand on the elf skull for a short moment.\n");
     	
     	if (deathroll == skull1)
     	{
     		set_alarm(10.0,0.0, &kill_me());
     		deathroll = random(3);
     		return 1;
     	}
     	
     	set_alarm(10.0,0.0, &success_me());
     	deathroll = random(3);

     	return 1;
     }
     
     if (str == "human skull")
     {
     	write("You place your hand on the human skull for a short moment.\n");
     	
     	if (deathroll == skull2)
     	{
     		set_alarm(10.0,0.0, &kill_me());
     		deathroll = random(3);
     		return 1;
     	}
     	
     	set_alarm(10.0,0.0, &success_me());
     	deathroll = random(3);
     	
     	return 1;
     }
     
     if (str == "orc skull")
     {
     	write("You place your hand on the orc skull for a short moment.\n");
     	
     	if (deathroll == skull3)
     	{
     		set_alarm(10.0,0.0, &kill_me());
     		deathroll = random(3);
     		return 1;
     	}
     	
     	set_alarm(10.0,0.0, &success_me());
     	deathroll = random(3);
     	
     	return 1;
     }
     
     
     
     if (!str)
     {
     	write("You have to select either the elf, human or the orc skull.\n");
     	return 1;
     }
     
     return 0;
}


void
create_room()
{
  acat("_entr","north");


  //acat("93","down", block_people);
  add_exit("/d/Avenir/common/dead/catacombs/crypt93", "down", block_people);

 
  crypt_long("There is some light coming in from the north.");

  set_long("The walls seem to be made from "
          +"glistening limestone, and the floor is covered "
          +"with a thick white mist, similiar to the fog "
          +"that lies on the moors, but whiter. A small limestone altar erects from " +
          "the east wall here, and on top of it you can see a few skulls. You can " +
          "barely see a rusty stairway leading down at the " +
          "end of the cave.\n");
         
         
   
  add_item(({"altar", "skull", "skulls", "orc skull", "elf skull", "human skull"}), "This " +
  "is a small altar made of limestone, erecting out from the east wall. On top of the altar you " +
  "see an orc skull, human skull and an elf skull resting on its cold surface.\n");
  
 


/* Room light values from -11 to 0 */
//   add_prop(ROOM_I_LIGHT, random(12)-12);

  reset_room();
}

void
reset_room()
{
 	
  if (!present("greater_death_", TO))
 	{
 		clone_object(MON+"greater_death")->move(TO);
 	}
  crypt_reset();
}


void
init()
{
    ::init();
    add_action(select_skull, "select");
    
}