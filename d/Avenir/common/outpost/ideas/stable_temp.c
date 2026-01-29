/* 

   File:  stable.c
   Purpose: Jonas Blackmun will stable your horse, or sell you one
            He also sells bags of oats.

The underlying idea for some of the mapping code comes from a stable in Neraka,
coded by Ashlar, 25 Jul 97 

*/

#include "/d/Terel/include/Terel.h"

#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <money.h>
#include <cmdparse.h>
#include <composite.h>
#include <language.h>

#define KILL_LOGGER CALATHIN_DIR + "obj/kill_logger"
#define BUY_LOGGER "/d/Terel/log/horse_sales"
#define MAP_FILE CALATHIN_DIR+"stable_map"
#define CORRAL CALATHIN_DIR+"stable_corral.c"
#define STALL CALATHIN_DIR+"stable_stall.c"
#define NUM_SAVED 7
#define MAX_CORRAL 6
#define MAX_DAYS 7
#define DAY 86400
#define DAILYCOST 1728

inherit STDROOM;

//The mapping that stores horses.  The index values are player names.
//The values are arrays attributes of all the horses stabled by that player.
//If a player has n horses, there are n*NUM_SAVED entries in the array.



//The stablemaster.
object jonas;

// Function Prototypes
void   reset_room();
int    restore_horses();
void   create_room();
string read_sign();
string read_paper();
int    do_stable(string arg);
int    query_my_horses(object customer);
int    query_has_horses(object customer);
int    do_fetch(string arg);
int    do_buy(string str);
void   dump();
void   wherearethey();
void   init();

/***********************************************************/

/* 
   Function:   reset_room
   Purpose:    called at room reset, gets us another stablemaster
               if someone manages to kill him (not impossible, just hard) 
   Parameters: none
*/

void
reset_room()
{
  if (!jonas)
      {
	jonas=clone_object(CALATHIN_DIR+"npc/jonas.c");
	jonas->move_living("M", TO);
      }
}


/***********************************************************/
/* 
   Function:   restore_horses
   Purpose:    when a customer wants his horses back, this
               function finds them in the mapping and
	       turns them into horses again.  They are then
	       temporarily stored in stable_stall.c.
   Parameters: none
*/
int restore_horses()
{
  mapping gHorse = ([ ]);
  int i,j, num_customers, num_horses;
  object newhorse;
  string *customers, customer, *temp_saved_info, filename, instance,
    adj1, adj2, gender, race, *saved_info;

 mixed time_stabled, time_in_stable;

 gHorse = restore_map(MAP_FILE);

 customer = TP->query_real_name();

 //If the customer's name isn't in the mapping, exit. 
 if (!pointerp(gHorse[customer]))
   {
     return 0;
   }

 saved_info=gHorse[customer];

 gHorse[customer]="";

 num_horses=sizeof(saved_info) / NUM_SAVED;

 for (j=0;j<num_horses;j++)
   {
     filename=saved_info[j*NUM_SAVED];
     instance=saved_info[j*NUM_SAVED+1];
     gender  =saved_info[j*NUM_SAVED+2];
     adj1    =saved_info[j*NUM_SAVED+3];
     adj2    =saved_info[j*NUM_SAVED+4];
     race    =saved_info[j*NUM_SAVED+5];
     time_stabled=saved_info[j*NUM_SAVED+6]; 

     time_in_stable=time()-time_stabled;

     newhorse=clone_object(filename);

     if (gender == "male")
       newhorse->set_gender(0);
     else
       newhorse->set_gender(1);

     newhorse->remove_adj(newhorse->query_adj());
     
     if (!(adj2=="")) newhorse->set_adj(adj2);
     if (!(adj1=="")) newhorse->set_adj(adj1);

     newhorse->set_race_name(race);

     newhorse->set_terel_horse_stats(race); 

     newhorse->set_hp(newhorse->query_max_hp());

     newhorse->move_living("M", CALATHIN_DIR+"stable_stall");

     sscanf(file_name(newhorse),"%s#%d", filename, instance);

     temp_saved_info=({filename, instance, gender, adj1, adj2, 
		       race, time_stabled});

     if (!pointerp(gHorse[customer]))
       { gHorse += ([ customer : temp_saved_info ]); }
     else
       { gHorse[customer] += temp_saved_info;}

   }

    save_map(gHorse, MAP_FILE);

    return 1;

}


/* 

   Function: create_room
   Purpose:  called at room creation.  Also calls a function
             to load stable_corral.c so Jonas will have horses to sell.
*/

void
create_room()
{
  ::create_room();
  set_short("a stable");

  set_long("A strong, but not overpowering, smell of manure greets "+
	   "your nostrils as you enter the stable.  The floor is "+
	   "hard-packed dirt, except inside the stalls, where hay "+
	   "offers ample bedding for the horses stabled here.  "+ 
	   "An occasional neigh or whinny can be heard.  Tools hang "+
	   "in a row on the wall, along with a neatly lettered but "+
	   "somewhat faded sign.  A large wooden bin with a closed "+
	   "lid sits near the stalls.\n");

  add_item("sign","@@read_sign@@");
  add_item("paper","@@read_paper@@");
  add_item("bin", "A large wooden bin.\n");

  add_item( ({"wall","walls", "hooks","tools"}), 
	    "Clean, well-used tools hang in a neat row on hooks "+
	    "in the wall.\n");

  add_cmd_item("sign","read","@@read_sign@@");
  add_cmd_item("paper","read","@@read_paper@@");

	     
  add_prop(ROOM_I_ALLOW_STEED,1);

  add_exit(CALATHIN_DIR+"stable_yard.c","north");

  reset_room();

  //Load the corral so we have some horses for sale. 
  call_other(CORRAL, "long");
  call_other(STALL, "long");

 }



/***********************************************************/
/* 
   Function:   read_sign
   Purpose:    reads the sign showing stable services 
   Parameters: none
*/
string
 read_sign()
 {
   return "\nHorses stabled! Finest care anywhere\nfor only 12 gold a day.\n\n"+
          "Fresh hay and water:   Included\n"+
          "Oats, by the bag:      2 gold\n"+
          "Horses for sale:       Talk to Jonas\n\n"+
     "Underneath the sign a yellow piece of paper is tacked to the wall.\n";
        
 }

/*
  Function: read_paper
  Purpose: print some help text on our stable.
*/

string
read_paper()
{
  return "THE PROPER CARE AND FEEDING OF HORSES\n\n"+
    "In order to keep a horse healthy and happy, regular feeding\n"+
    "and watering is required.  I always return your horse to you\n"+
    "fully fed. Please consider buying some oats to take with\n"+
    "you.  Finding a reliable, unpoisoned water supply is more\n"+
    "difficult, but you can always water your animals at the\n"+
    "trough outside.\n\n"+
    "If you have a saddlebag, you can 'drape saddlebag on <steed>'\n"+
    "and 'remove saddlebag from <steed>'.  Terel horses are very\n"+
    "well-trained as pack animals. They will stand quietly while\n"+
    "you 'open/close saddlebag on <steed>', or even fill and empty\n"+
    "it.\n\n"+
    "For the tenderfeet among us, use 'lead <steed>' to make your\n"+
    "horse follow you, and 'leave <steed>' to stop.  Mount and\n"+
    "dismount to get on and off.  Note that two people can ride!\n\n"+
    "Finally, you must return your horse back to the stable at the\n"+
    "end of the day and 'stable <steed>.  Retrieve it with 'retrieve\n"+
    "horse'.\n\nJONAS BLACKMUN\n";

}

/***********************************************************/
/* 
   Function:   do_stable
   Purpose:    stores a horse in the stable.  The horse object
               is removed and all salient information stored
	       in a mapping file.
   Parameters: the string parameter to the player's "stable" command,
               should parse to a horse in the room
*/

 int
 do_stable(string arg)
 {

   mapping gHorse = ([ ]);
   object kill_logger = find_object (KILL_LOGGER);
   object *horses;
   string *saved_info, *adjs, adj1, adj2, gender, filename, race;
   string pn;
   int instance, time_stabled;

   if (!jonas) 
	   {
	     notify_fail ("The stable master is not here!\n");
	     return 0;
	   }

	 if (!present(jonas)) 
	   {
	     notify_fail ("The stable master is not here!\n");
	     return 0;
	   }

	 if (!CAN_SEE_IN_ROOM(jonas) || !CAN_SEE(jonas,TP))
	   {
	     jonas->command("emote looks startled.");
	     jonas->command("say Who's there?");
	     return 1;
	   }

	 if (TP->query_race_name() == "goblin")
	   {
	     jonas->command("shout A goblin!!");
	     jonas->command("panic");
	     return 1;
	   }

	 if (kill_logger->query_killer(TP->query_name()))
	   {
	     jonas->command("peer suspic");
	     jonas->command("say I may work outside the city walls, but "+
			    "I'm no hick.  You'd better move on before "+
			    "I call the guards.");
	     return 1;
	   }

	 notify_fail("Stable what? Your horse perhaps?\n");

	 if (!stringp(arg))
		 return 0;

	 horses = FIND_STR_IN_OBJECT(arg, TO);

	 if (!sizeof(horses))
		 return 0;

	 notify_fail("You can only stable one horse at a time.\n");
	 if (sizeof(horses)>1)
		 return 0;

	 notify_fail("You don't want to sleep in a stable, do you? "+
		     "Dismount first!\n");

	 if (horses[0]->query_has_riders())
	   return 0;


	 notify_fail("You can only stable horses here!\n");
	 if (!horses[0]->id("horse"))
		 return 0;

	 // Can't stable with a saddlebag on	 
	 if (present ("saddlebag", horses[0]))
	   {
	     jonas->command("say You got to take that saddlebag "+
			    "along with you.  I can't be responsible for "+
			    "that!");
	     return 1;
	   }

	 //Knights of Solamnia can't stable with barding on.
	 if (horses[0]->query_barding())
	   {
	     jonas->command("say You got to take that fancy barding "+
			    "along with you.  I can't be responsible for "+
			    "that!");
	     return 1;

	   }

	 notify_fail("You don't have enough money!\n");
	 if (!MONEY_ADD(TP,-1440))
	   return 0;


	 //get time of stabling, in seconds since 1970
	 time_stabled=time();

	 //get filename and instance number
	 sscanf(file_name(horses[0]), "%s#%d", filename, instance);

	 //get array of all adjectives, I am only saving two. 
	 adjs=horses[0]->query_adj(1);
	 if (sizeof(adjs)>=1) {adj1=adjs[0];} else {adj1="";}
	 if (sizeof(adjs)>=2) {adj2=adjs[1];} else {adj2="";}


	 if (horses[0]->query_gender()) 
	   {gender="female";}
	 else
	   {gender="male";}

	 race=horses[0]->query_race_name();

	 saved_info=( {filename, instance, gender, adj1, adj2, race, 
		       time_stabled } );

	 pn = TP->query_real_name();

	 gHorse=restore_map(MAP_FILE);

	 if (!pointerp(gHorse[pn]))

 		 gHorse += ([ pn : saved_info ]);
	 else
		 gHorse[pn] += saved_info;

	 save_map(gHorse, MAP_FILE);

	 tell_room(TO, QCTNAME(TP) + " pays the stablehand, who " +
	 "leads the " + horses[0]->short() + " away.\n", TP);

	write("You pay the stablehand, who leads the " +
		horses[0]->short() + " away.\n");
	
	jonas->command("smile");
	
	jonas->command("say A pleasure to serve you.  Your "+
		       horses[0]->short()+" will be well tended to, "+
		       "you can rest easy about that.\n");
	jonas->command("frown .");
	jonas->command("say Just to be clear - I can only keep "+
		       horses[0]->query_objective()+
		       " for a week without you settling up your bill! "+
		       "I ain't a rich man, and can't feed horses for free.");
	jonas->command("nod firmly"); 

	horses[0]->remove_object();

	return 1;
}
/************************************************************/
/* 
   Function:   query_my_horses
   Purpose:    response to asking Jonas "my horses".  It looks up
               the player's horses that are stabled, without
	       actually restoring them
   Parameters: a player object
*/

int
query_my_horses(object customer)
{
  mapping gHorse = ([ ]);
  string pn, *saved_info;
  int num_horses, i;
  mixed time_stabled,days_in_stable;
  string gender,objective,adj1,adj2,race;
  
  gHorse = restore_map(MAP_FILE);

  if (!CAN_SEE_IN_ROOM(jonas) || !CAN_SEE(jonas,customer))
    {
      jonas->command("emote looks startled.");
      jonas->command("say Who's there?");
      return 1;
    }

  pn= customer->query_real_name();
  jonas->command("say Let's see...");
  jonas->command("think");

  if (!pointerp(gHorse[pn]))
    {
      jonas->command("frown");
      jonas->command("say I'm very sorry, but I've no horse of yours "+
		     "stabled here!");
      jonas->command("say If you're in need of a mount, you've come to the "+
		     "right place, though!  Have a look in the corral "+
		     "to see the fine steeds I have for sale.");

      return 1;
    }
   saved_info=gHorse[pn];

   num_horses=sizeof(saved_info) / NUM_SAVED;
   for (i=0;i<num_horses;i++)
      {
	gender  =saved_info[i*NUM_SAVED+2];
	adj1    =saved_info[i*NUM_SAVED+3];
	adj2    =saved_info[i*NUM_SAVED+4];
	race    =saved_info[i*NUM_SAVED+5];
	time_stabled=saved_info[i*NUM_SAVED+6]; 
	
	days_in_stable=(time()-time_stabled) / DAY;
 
	if (gender == "male")
	  {
	    objective="him";
	  }
	else objective="her";


	switch (days_in_stable)
	  {
	  case 0 :
	      {
		jonas->command("say I've got your "+adj1+" "+
			       race+" stabled here.  It's just been "+
			       "today, no additional charge to "+
			       "retrieve "+objective+".");
		break;
	      } 
	  case 1 :
	      {
		jonas->command("say I've got your "+adj1+" "+
			       race+" stabled here.  It's just been "+
			       "one day, so it'll be one "+
			       "platinum additional charge to "+
			       "retrieve "+objective+".");
		break;

	      }
	  case 2..MAX_DAYS :
	      {
		jonas->command("say I've got your "+adj1+" "+
			       race+" stabled here.  It's been "+
			       ", um, "+LANG_WNUM(days_in_stable)+
			       " days, so it'll be "+days_in_stable+
			       " platinum additional charge to "+
			       "retrieve "+objective+".");		
		break;
	      }
	  default :
	    {
		  jonas->command("say Oh dear, I figgered you were never "+
				 "coming back for your "+adj1+" "+
				 " "+race+". I'm sorry, but I sold "+
				 objective+" off to cover my costs.  "+
				 "I warned you about that when you "+
				 "stabled "+ objective+"!");
		  jonas->command("sigh");
	    }

	  }
      }

      jonas->command("say I'm pretty sure that's all, "+
	"I ain't senile just yet."); 
  return 1;

}


/************************************************************/
/* 
   Function:   query_has_horses
   Purpose:    finds out if a player has any horses stabled.
   Parameters: a player object
   returns:    1 if they do, 0 if they don't.
*/

int
query_has_horses(object customer)
{
  mapping gHorse = ([ ]);
  gHorse = restore_map(MAP_FILE);

  return pointerp(gHorse[ customer->query_real_name() ]);
}



/***********************************************************/
/* 
   Function:   do_fetch
   Purpose:    returns the players horses to them, takes their money
   Parameters: parameter to player's "retrieve" command, should
               be some version of "horse" 
*/

int
do_fetch(string arg)
{
  mapping gHorse = ([ ]);
  object horse;
  string pn, *saved_info;
  int i,j,food,drink,price, num_horses;
  mixed time_stabled, days_in_stable;
  if (!jonas) 
    {
      notify_fail ("The stable master is not here!\n");
      return 0;
    }

	notify_fail("Retrieve what? Your horse perhaps?\n");

	if (!stringp(arg))
	  return 0;
	
	if (!CAN_SEE_IN_ROOM(jonas) || !CAN_SEE(jonas,TP))
	  {
	    jonas->command("emote looks startled.");
	    jonas->command("say Who's there?");
	    return 1;
	  }

	if ((arg!="horse") && (arg!="my horse") && 
		(arg!="horses") && (arg!="my horses"))
	{
		return 0;
	}

	pn = TP->query_real_name();

	if (!restore_horses())
	  {
	    notify_fail("But you have no horse stabled here.\n");
	    return 0;
	  }

	gHorse=restore_map(MAP_FILE);

	if (!pointerp(gHorse[pn]))
	{
		notify_fail("But you have no horse stabled here.\n");
		return 0;
	}

 	saved_info = gHorse[pn];

	num_horses=sizeof(saved_info) / NUM_SAVED;

  	price=0;

	//figure out the total cost for stabling all horses.
	//If the player doesn't have it, don't do anything else.
	for(i=0;i<num_horses;i++)

	  {
	    horse=0;

	    horse=find_object( sprintf("%s#%d", 
				       saved_info[i*NUM_SAVED],
				       saved_info[i*NUM_SAVED+1] ));

	    if (!horse)
	      {
	notify_fail("Can't find your horse! Please bug with error #101!");
		return 0;
	      }

	    //get the time it was stabled
	    time_stabled=saved_info[i*NUM_SAVED+6];

	    //figure out how many rl days it was in the stable
	    days_in_stable=(time()-time_stabled) / DAY;

	    //set the price.
	    price=price+days_in_stable*DAILYCOST;

	    if (TOTAL_MONEY(TP)<price)
	      {
		notify_fail("You don't have enough money to retrieve "+
			    "your horses!\n");
		return 0;
	      }
	  }

	for(i=0;i<num_horses;i++)

	  {
	    horse=0;
	    horse=find_object( sprintf("%s#%d", 
				       saved_info[i*NUM_SAVED],
				       saved_info[i*NUM_SAVED+1] ));
	    if (!horse)
	      {
	notify_fail("Can't find your horse! Please bug with error #102!");
		return 0;
	      }
 	    //get the time it was stabled
	    time_stabled=saved_info[i*NUM_SAVED+6];

	    //figure out how many rl days it was in the stable
	    days_in_stable=(time()-time_stabled) / DAY;

	    switch (days_in_stable)
	      {
	      case 0  :

		{
		  jonas->command("say Back already for your "+
				horse->short()
				+"?");
		break;
		}
	      case 1..4  :
		{
		  jonas->command("say Ah, hello!  Good to see you. Your "+
				horse->short()+" is right here.  That'll "+
				"be "+LANG_WNUM(days_in_stable)+
				" additional platinum for the "+
				"extra time "+horse->query_pronoun()+
				" was stabled here.");
		break;
		}
	      case 5..MAX_DAYS-1 :
		{
		  jonas->command("say Ah!  That's a relief!  I been "+
				"wondering if you were coming back for your "+
				horse->short()+". Just "+
				LANG_WNUM(MAX_DAYS-days_in_stable)+
				" more days and I woulda had to sell "+ 
				horse->query_objective()+" off. That'll "+
				"be "+LANG_WNUM(days_in_stable)+
				" additional platinum for the "+
				"extra time "+horse->query_pronoun()+
				" was stabled here.");
		jonas->command("wince");
		break;
		}
	      case MAX_DAYS :
		{
		  jonas->command("say Ah!  That's a relief!  I been "+
				"wondering if you were coming back for your "+
				horse->short()+". Just one more day and I "+
				"woulda had to sell "+ 
				horse->query_objective()+" off.  That'll "+
				"be "+LANG_WNUM(days_in_stable)+
				" additional platinum for the "+
				"extra time "+horse->query_pronoun()+
				" was stabled here.");
		  break;
		}
	      default :
		{
		  jonas->command("sigh");
		  jonas->command("say Oh dear, I figgered you were never "+
				 "coming back for your "+
				 horse->short()+". I'm sorry, but I sold "+
				 horse->query_objective()+" off to cover "+
				 "my costs.  I warned you about that when "+
				 "you stabled "+horse->query_objective()+
				 "!");
		  jonas->command("shrug sadly");
		  horse->remove_object();
		}

	      }

	    if (horse)
	      {
		price=days_in_stable*DAILYCOST;

		if (price)
		  {
		    notify_fail("You don't have enough money!\n");
		    if (!MONEY_ADD(TP,price*-1))
		      return 0;

		    write("You pay Jonas "+MONEY_TEXT_SPLIT(price)+".\n");
		    say(QCTNAME(TP)+" pays Jonas some money.\n");
		  }

		food=horse->eat_max() / 6;
		drink=horse->drink_max() / 20;

		//can only eat 1/6 of your max at once.
		for (j=0;j<6;j++) horse->eat_food(food);

		//top it off
		horse->eat_food (horse->eat_max() 
				 - horse->query_stuffed());

		//can only drink 1/20 of your max at once 
		for (j=0;j<20;j++)	horse->drink_soft(drink);

		horse->move_living("M",TO);

		tell_room(TO,"The stablehand retrieves " +
			  COMPOSITE_LIVE(horse) + ".\n");
	      }
	    else
	      {
	notify_fail("Can't find your horse. Please bug with error #103!\n");
		return 0;
	      }
	 
	  }

	/*I think this should really use m_delete but I can't make it work!*/
	gHorse[pn]="";

	save_map(gHorse, MAP_FILE);
	return 1;
	  
}
/* 
   Function:   do_buy
   Purpose:    buy a horse from those available in stable_corral
   Parameters: string parameter to "buy" command, should parse to
               one of the horses in the corral (or some bags of oats). 
*/

int
do_buy(string str)
{
object *horses;
object kill_logger = find_object (KILL_LOGGER);
object oats;
int i,j,food,drink, num_oats=1;

if (!str)
  {
    notify_fail ("Buy what?\n");
    return 0;
  }

if (!jonas) 
  {
    notify_fail ("The stable master is not here!\n");
    return 0;
  }

	 if (TP->query_race_name() == "goblin")
	   {
	     jonas->command("shout A goblin!!");
	     jonas->command("panic");
	     return 1;
	   }

	 if (kill_logger->query_killer(TP->query_name()))
	   {
	     jonas->command("peer suspic");
	     jonas->command("say I may work outside the city walls, but "+
			    "I'm no hick.  You'd better move on before "+
			    "I call the guards.");
	     return 1;
	   }


if (str=="horse")
  {
    notify_fail("Better be more specific, or talk to Jonas.\n");
    return 0;
  }

//buying oats: player can either type "buy oats" or "buy 20 oats"

if (
    (parse_command(str,ENV(TP),
                       "%d 'oats'",
                       num_oats)) 
    ||
    
    (str=="oats")
    )
  {

    if (num_oats>10)
      {
	jonas->command("say 10 bags at a time is about all I can handle!");
	return 1;
      }

    if (TOTAL_MONEY(TP)<(288*num_oats))
      {
	notify_fail("You don't have enough money!\n");
	return 0;
      }
    for (i=0;i<num_oats;i++)
      {
	oats=clone_object(CALATHIN_DIR+"obj/oats.c");

	if (!oats->move(TP))
	  {
	    if (!MONEY_ADD(TP,-288))
	      return 0;
      }
    else
      {
	notify_fail("You decide the little bag of oats is too much to "+
		    "carry around.");
	return 0;
      }
	
      }
    jonas->command("emote opens the wooden bin.");
    jonas->command("emote takes a metal scoop off a hook on the wall, "+
		   "and paper bags from a stack.");
    jonas->command("emote whips the paper bags through the air, opening "+
		   "and filling them with a snap.");
    jonas->command("emote delivers the oats with a smile, then "+
		   "replaces the scoop to its hook with a "+
		   "practiced flourish.");

    if (num_oats==1)
      jonas->command("say Just one bag today then?");

    return 1;
	
  }

horses=FIND_STR_IN_OBJECT(str,
			  find_object(CALATHIN_DIR+"stable_corral.c"));

if (sizeof(horses) == 0)
  {
    jonas->command("say Sorry, I don't have any such animal for sale at the moment.");
    return 1;
  }
else
  {  notify_fail("You don't have enough money!\n");
     if (!MONEY_ADD(TP,horses[0]->list_price()*-1728))
	   return 0;


    jonas->command("emote smiles brightly.");
    jonas->command("say A fine choice!  I'm sure you'll be happy with it.");
    jonas->command("emote leaves outside into the corral, and returns "+
		    "shortly leading a horse.");  
   
    write (jonas->query_The_name(TP)+" gives you the reins.\n");

    jonas->command("say Now don't forget to stable it at the end of the day!");
    
    food=horses[0]->eat_max() / 6;
    drink=horses[0]->drink_max() / 20;

    //can only eat 1/6 of your max at once.
    for (j=0;j<6;j++) horses[0]->eat_food(food);

    //top it off
    horses[0]->eat_food (horses[0]->eat_max() 
			 - horses[0]->query_stuffed());

    //can only drink 1/20 of your max at once 
    for (j=0;j<20;j++)	horses[0]->drink_soft(drink);

    horses[0]->move_living("M",CALATHIN_DIR+"stable.c");
    str="lead "+str;
    TP->command(str);

    str = TP->query_name() +
           "[" + TP->query_average_stat() + "]"
      + " (" + ctime(time()) + ") "   
      +horses[0]->query_adj()+" "
      +horses[0]->query_race_name()+"\n";

    write_file(BUY_LOGGER, str );

    return 1;
  }
}


/***********************************************************/
/*  
   Function:   dump
   Purpose:    for wizard use, prints a table of all horses currently stabled
   Parameters: none
*/

void
dump()
     {
       mapping gHorse = ([ ]);
       string filename, adj1, adj2, race, gender,
	 *customers, *saved_info, outputline,playername;

       int i,j,days_in_stable;

       mixed time_stabled;

       gHorse = restore_map(MAP_FILE);

       customers=m_indexes(gHorse);

       for (i=0;i<sizeof(customers);i++)
	 {
	   playername=customers[i];
	   saved_info=gHorse[playername];

	   if (!stringp(saved_info))
	     {
	   for (j=0;j<sizeof(saved_info)/NUM_SAVED;j++)
	     {
	       gender  =saved_info[j*NUM_SAVED+2];
	       adj1    =saved_info[j*NUM_SAVED+3];
	       adj2    =saved_info[j*NUM_SAVED+4];
	       race    =saved_info[j*NUM_SAVED+5];
	       time_stabled=saved_info[j*NUM_SAVED+6]; 
	       days_in_stable=(time()-time_stabled) / DAY;

	       outputline=sprintf("%-=14s:%s %s %s %s %s\n",
				  capitalize(playername),
				  ctime(time_stabled),
				  gender,
				  adj1,
				  adj2,
				  race);
	       
	       write (outputline);

		 }
	     }
	 }
     }

void
wherearethey()
{
  object a, *b;

  a = clone_object("/d/Terel/calathin/npc/terel_horse.c");
  b = object_clones(a) - ({a});
  a->remove_object();
  write (dump_array(b));
  /*  dump_mapping( (map(b, environment)->short()));  
      dump_mapping(b);*/

}

/***********************************************************/
/* 
   Function:   init
   Purpose:    enable the add_actions
   Parameters: none
*/

void
init()
{
  ::init();
  add_action(do_stable, "stable");
  add_action(do_fetch, "retrieve");
  add_action(do_buy,"buy");
}


