/* Mortis 10.2005
 *   Full props to Terel for coding a fantastic stable.  Most of
 * this code was taken straight from their stable.
 *
 * Terel notes:  The underlying idea for some of the mapping code
 * comes from a stable in Neraka, coded by Ashlar, 25 Jul 97
 */

#include "../local.h"
#include CLOCKH
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <money.h>
#include <cmdparse.h>
#include <composite.h>
#include <language.h>

inherit NOBLE_BASE;

#define MAP_FILE NOBLE + "livery_map"
//#define TEMP_FILE NOBLE + "stable_temp"
#define CORRAL NOBLE + "livery_corral.c"
#define STALL NOBLE + "livery_stall.c"
#define NUM_SAVED 7
#define MAX_CORRAL 6
#define MAX_DAYS 30
#define PALDAY 86400
#define DAILYCOST 1728

string
query_to_jail()
{
  return "east";
}

//The mapping that stores horses.  The index values are player names.
//The values are arrays attributes of all the horses stabled by that player.
//If a player has n horses, there are n*NUM_SAVED entries in the array.

//The stablemaster.
object engen;

// Function Prototypes
int    restore_palan_horses();
string read_sign();
//string read_paper();
int    do_stable(string arg);
int    query_my_horses(object customer);
int    query_has_horses(object customer);
int    do_fetch(string arg);
//int    do_buy(string str);
void   dump();
void   clean();
void   init();


/***********************************************************/
/* 
   Function:   restore_palan_horses
   Purpose:    when a customer wants his horses back, this
               function finds them in the mapping and
	       turns them into horses again.  They are then
	       temporarily stored in livery_stall.c.
   Parameters: none
*/
int restore_palan_horses()
{
  mapping palanHorse = ([ ]);
  int i,j, num_customers, num_horses;
  object newhorse;
  string *customers, customer, *temp_saved_info, filename, instance,
    adj1, adj2, gender, race, *saved_info;

 mixed time_stabled, time_in_stable;

 palanHorse = restore_map(MAP_FILE);

 customer = TP->query_real_name();

 //If the customer's name isn't in the mapping, exit. 
 if (!pointerp(palanHorse[customer]))
   {
     return 0;
   }

 saved_info=palanHorse[customer];

 palanHorse[customer]="";

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

     newhorse->move_living("M", NOBLE + "livery_stall");

     sscanf(file_name(newhorse),"%s#%d", filename, instance);

     temp_saved_info=({filename, instance, gender, adj1, adj2, 
		       race, time_stabled});

     if (!pointerp(palanHorse[customer]))
       { palanHorse += ([ customer : temp_saved_info ]); }
     else
       { palanHorse[customer] += temp_saved_info;}

   }

    save_map(palanHorse, MAP_FILE);

    return 1;

}


// Returns description of room based on time.

nomask public string
get_time_desc()
{
    string desc = "";
	string road = "To the west is the Solamnian Livery manor house, an "
	+ "old two-story marble building with an oversized copper door and "
	+ "an ornate, copper roofed cupola atop its steep roof.  The "
	+ "stable longhouse runs north from it, and to the south is a corral.  "
	+ "A gravel path leads east through the equestrian field to Livery "
	+ "Street.  ";
    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
	desc += road + "The short grass to either side of the gravel path "
	+ "flutters in small waves on the the cool, misty breeze blowing "
	+ "south from the bay as the morning sun peeks above the mountains "
	+ "in the east.\n";
	break;

    case TOD_DAY:
	desc += road + "The short grass to either side of the gravel path flutters "
	+ "in small waves on the midday breeze blowing south from the bay.\n";
	break;

    case TOD_TWILIGHT:
	desc += road + "The short grass to either side of the gravel path flutters "
	+ "in small waves on the the cool, misty breeze blowing south from "
	+ "the bay as the evening sun lowers above the mountains to the west.  "
	+ "Several equestrians are here fetching their horses while visitors "
	+ "just arriving lead their horses west to be stabled.\n";
    break;

    case TOD_NIGHT:
	desc += road + "The moon and stars shed pale light across the short grass to "
	+ "either side of the gravel path as a cool, misty breeze blows south "
	+ "off the bay.\n";
    break;

    default:
	break;
    }
    return desc;
}


reset_palan_room()
{
    if(!objectp(engen))
	{
		engen = clone_object(NOBLE + "living/engen");
		engen->arm_me();
		engen->move(TO);
	}
}

void create_palan_room()
{
    SHORT("Outside the Solamnian Livery");
    LONG("@@get_time_desc@@");

	ITEM(({"livery", "solamnian livery", "house", "manor", "manor house"}),
	  "The two-story manor house is an old, translucent marble building "
	+ "whose grounds were converted ages ago to accomodate the field, "
	+ "wood-fenced corral, and stables.  Below its roof is a band of "
	+ "chiselings, and along its edge are a good many crouching gargoyles."
	+ "  Atop the steep sloped, marble tiled roof is a cupola, its copper "
	+ "roof turned green with weathering long ago.  An oversized copper "
	+ "door leads into the house, its ornate stylings still bright from "
	+ "frequent polishing.\n");

	ITEM(({"stable", "stables", "longhouse"}), "The stable longhouse runs "
	+ "north from the livery manor house.  It's as large as a barn but much "
	+ "longer.  It is the only wooden building in the noble district built "
	+ "a generation ago when this estate changed hands.  A run of fenced "
	+ "corridors extends down the length of the stables for bringing horses "
	+ "to and from it in an orderly fashion.\n");

	ITEM(({"grass", "field"}), "Short, green grass with light tints of "
	+ "brown form a small field for equestrians to gather east of here.  "
	+ "It is well trampled and dotted with the occasional pile of manure.  "
	+ "A gravel path leads east where the marble of Livery Street begins.\n");

	ITEM("manure", "Piles of horse sized droppings dot the field to your "
	+ "east.\n");

	ITEM(({"gravel", "path", "gravel path"}), "White marble gravel has "
	+ "been smoothed out to create a stately path from the manor house "
	+ "through the equestrian field to Livery Street in the east.\n");

	ITEM("corral", "The corral is a round fenced in area approximately "
	+ "thirty feet in diameter for training or viewing horses.  Its "
	+ "split log, wooden fence is seven feet high and very sturdy.\n");

	ITEM(({"horse", "horses"}), "There are horses coming and going at all "
	+ "hours at the Solamnian Livery from the corral to the field to the "
	+ "stables.\n");

	ITEM("cupola", "The cupola atop the steep roof of the manor house is "
	+ "large enough for a few people and windowed on all four sides.  It's "
	+ "difficult to make out much detail, but its roof is weathered, green "
	+ "copper and elegantly styled to curve up at the corners.\n");

	ITEM("roof", "The roof of the manor house is noticeably steep and tiled "
	+ "in weather darkened, translucent marble.\n");

	ITEM("sign","@@read_sign@@");

//  ITEM("paper","@@read_paper@@");

	CMD("sign","read","@@read_sign@@");

//  CMD("paper","read","@@read_paper@@");


	add_smell("vampire", "Misty air blowing south off the bay mingles here "
	+ "with the pungent smell of fresh cut hay, boiled leather, and well "
	+ "groomed horses.  The scent of human blood is strong here.");
    add_smell("morgul", "Misty air blowing south off the bay mingles here "
	+ "with the smell of horses and leather.");
	add_smell("human", "Misty air blowing south off the bay mingles here with "
	+ "the smell of fresh cut hay, leather, and horses.");
	add_smell("elf", "Misty air blowing south off the bay mingles here with "
	+ "the smells of fresh cut hay, tanned leather, and well cared for "
	+ "horses.");
	add_smell("goblin", "The fresh smells of horses and hay from the "
	+ "west mix here with misty air blowing south off the bay.");
	add_smell("dwarf", "Misty air blowing south off the bay mingles here "
	+ "with the smells of hay, tanned and boiled leathers, and horses.");
	add_smell("hobbit", "Misty air blowing south off the bay mingles here "
	+ "with the relaxing smell of fresh cut hay, the warm smell of leather, "
	+ "and the scent of horses.");
	add_smell("gnome", "There's moisture in the air blowing south off the "
	+ "bay.  Adding to its salty flavor are the smells of hay, horses, and "
	+ "leather from the livery.");
	add_smell("minotaur", "Misty air blowing south off the bay mingles here "
	+ "with the familiar smells of well groomed horses and leather as well "
	+ "as fresh, crunchy hay.");
	add_smell("halfhuman", "Misty air blowing south off the bay mingles here "
	+ "with the familiar smells of hay, horses, and leather.");
	add_smell("halfelf", "Misty air blowing south off the bay mingles here "
	+ "with the not unfamiliar smells of fresh cut hay, leather, and horses.");
	add_smell("orc", "Misty air blowing south off the bay mingles here with "
	+ "the mouth-watering smell of horse flesh and leather.");
	add_smell("hobgoblin", "Misty air blowing south off the bay mingles here "
	+ "with the smells of well groomed horse, good leather, and fresh hay.");
	add_smell("kender", "Misty air blowing south off the bay mingles here "
	+ "with the relaxing smell of fresh cut hay, the warm smell of leather, "
	+ "and the scent of horses.");
	add_smell("noldor", "Misty air blowing south off the bay mingles here "
	+ "with the smells of fresh cut hay, leather, and groomed horses from "
	+ "the livery.");
	add_smell("unknown", "You smell the horses and such, but "
	+ "your race is unknown to the immortals!  Please mail Krynn with your "
	+ "race.");

	add_prop(ROOM_I_ALLOW_STEED,1);

	EXIT(NOBLE + "liv_ent", "east", 0, 0);

//  add_npc(NOBLE + "living/engen", 1, &->arm_me());

	reset_palan_room();

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
   return "\nThe Solamnian Livery provides the highest level\n"
          + "of equine stabling and safety in the city of\n"
		  + "Palanthas at a cost of one platinum per day.\n"
		  + "You may stable or retrieve horse for service.\n\n";
        
 }

/*
  Function: read_paper
  Purpose: print some help text on our stable.
*/
/*
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
    "horse'.\n\nSir Engen\n";

}
*/
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

   mapping palanHorse = ([ ]);
   object *horses;
   string *saved_info, *adjs, adj1, adj2, gender, filename, race;
   string pn;
   int instance, time_stabled;

   if (!engen) 
	   {
	     notify_fail ("There is no one here to provide service.\n");
	     return 0;
	   }

	 if (!present(engen)) 
	   {
	     notify_fail ("There is no one here to provide service.\n");
	     return 0;
	   }

	 if (!CAN_SEE_IN_ROOM(engen) || !CAN_SEE(engen,TP))
	   {
	     engen->command("emote furrows his brow in concern.");
	     engen->command("say Who goes there?");
	     return 1;
	   }

	 notify_fail("Stable what? Your horse perhaps?\n");

	 if (!stringp(arg))
		 return 0;

	 horses = FIND_STR_IN_OBJECT(arg, TO);

	 if (!sizeof(horses))
		 return 0;

	 notify_fail("You may only stable one horse at a time.\n");
	 if (sizeof(horses)>1)
		 return 0;

	 notify_fail("Engen says:  Hop down from there, and we'll "
	           + "see to your animal.\n");

	 if (horses[0]->query_has_riders())
	   return 0;

	 notify_fail("You can only stable horses here.\n");
	 if (!horses[0]->id("horse"))
		 return 0;

         notify_fail("You can only stable a horse you are leading.\n");
         if (horses[0]->query_leader() != TP)
           return 0;

	 // Can't stable with a saddlebag on	 
	 if (present ("saddlebag", horses[0]))
	   {
	     engen->command("say You'll have to take your saddlebag "
			   + "with you.  We cannot be responsible for your "
			   + "belongings.");
	     return 1;
	   }

	 //Knights of Solamnia can't stable with barding on.
	 if (horses[0]->query_barding())
	   {
	     engen->command("say That's a fine set of barding, sir, "
		       + "but you'll have to take it with you.  We do "
			   + "not provide personal storage here.");
	     return 1;

	   }

	 notify_fail("You'll need more money than that.\n");
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

	 palanHorse=restore_map(MAP_FILE);

	 if (!pointerp(palanHorse[pn]))

 		 palanHorse += ([ pn : saved_info ]);
	 else
		 palanHorse[pn] += saved_info;

	 save_map(palanHorse, MAP_FILE);

	 tell_room(TO, QCTNAME(TP) + " pays the proprietor, and " +
	 "a stablehand leads the " + horses[0]->short() + " away.\n", TP);

	write("You pay the proprietor, and a stablehand leads the " +
		horses[0]->short() + " away.\n");
	
	engen->command("knod");
	
	engen->command("say Worry not about a thing.  Your "
		      + horses[0]->short()+" will be well cared for.  "
		      + "You have my word.  However, you must return "
			  + "for it within a month or I must assume that "
			  + "you have abandoned it.\n");

	horses[0]->remove_object();

	return 1;
}
/************************************************************/
/* 
   Function:   query_my_horses
   Purpose:    response to asking engen "my horses".  It looks up
               the player's horses that are stabled, without
	       actually restoring them
   Parameters: a player object
*/

int
query_my_horses(object customer)
{
  mapping palanHorse = ([ ]);
  string pn, *saved_info, *new_info;
  int num_horses, i, tl=0, *too_long;
  mixed time_stabled,days_in_stable;
  string gender,objective,adj1,adj2,race, filename,instance;

  
  palanHorse = restore_map(MAP_FILE);

  if (!CAN_SEE_IN_ROOM(engen) || !CAN_SEE(engen,customer))
    {
      engen->command("emote furrows his brow warily.");
      engen->command("say Who goes there?");
      return 1;
    }

  pn= customer->query_real_name();
  engen->command("say Let me see...");
  engen->command("hmm");

  if (!pointerp(palanHorse[pn]))
    {
      engen->command("emote confers with a stablehand.");
      engen->command("say We have no horse of yours stabled here.");

      return 1;
    }
   saved_info=palanHorse[pn];
   too_long = allocate(sizeof(saved_info));
   num_horses=sizeof(saved_info) / NUM_SAVED;
   for (i=0;i<num_horses;i++)
      {
        filename=saved_info[i*NUM_SAVED];
        instance=saved_info[i*NUM_SAVED+1];
	gender  =saved_info[i*NUM_SAVED+2];
	adj1    =saved_info[i*NUM_SAVED+3];
	adj2    =saved_info[i*NUM_SAVED+4];
	race    =saved_info[i*NUM_SAVED+5];
	time_stabled=saved_info[i*NUM_SAVED+6]; 
	
	days_in_stable=(time()-time_stabled) / PALDAY;
 
	if (gender == "male")
	  {
	    objective="him";
	  }
	else objective="her";


	switch (days_in_stable)
	  {
	  case 0 :
	      {
		engen->command("say I have your "+adj1+" "+
			       race+" stabled here.  Since it's only been "+
			       "one day, there is no additional charge to "+
			       "retrieve "+objective+".");
		break;
	      } 
	  case 1 :
	      {
		engen->command("say I have your "+adj1+" "+
			       race+" stabled here.  It has been "+
			       "one day, so it will be one "+
			       "platinum to "+
			       "retrieve "+objective+".");
		break;

	      }
	  case 2..MAX_DAYS :
	      {
		engen->command("say I have your "+adj1+" "+
			       race+" stabled here.  It's been "
			       + LANG_WNUM(days_in_stable)+
			       " days, so it will be a "+days_in_stable+
			       " platinum fee to retrieve "+objective+".");		
		break;
	      }
	  default :
	    {
		  engen->command("say You were gone so long, I assumed you "
				+ "had abandoned your "+adj1+" "+
				 " "+race+". I am sorry, but I sold "+
				 objective+" off to cover my costs.  "+
				 "You were warned about that when you "+
				 "stabled "+ objective+"!");
		  engen->command("kbow");
	    }

	  }
        // Flag the horses that have been stabled too long
        if (days_in_stable > MAX_DAYS)
        {
            too_long[i] = 1;
            tl++;
        }
      }
      // Dump out the horses that have been flagged
      if (tl)
      {
        palanHorse[pn] = "";
        for (i=0;i<num_horses;i++)
        {
          if (!(too_long[i]))
          { 
            filename=saved_info[i*NUM_SAVED];
            instance=saved_info[i*NUM_SAVED+1];
            gender  =saved_info[i*NUM_SAVED+2];
            adj1    =saved_info[i*NUM_SAVED+3];
            adj2    =saved_info[i*NUM_SAVED+4];
            race    =saved_info[i*NUM_SAVED+5];
            time_stabled=saved_info[i*NUM_SAVED+6];

            new_info=( {filename, instance, gender, adj1, adj2, race,
                       time_stabled } );
            if (!pointerp(palanHorse[pn]))

                 palanHorse += ([ pn : new_info ]);
            else
                 palanHorse[pn] += new_info;
          }
        }
        save_map(palanHorse, MAP_FILE);
      }
                
      

      engen->command("say I am certain that is all.");
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
  mapping palanHorse = ([ ]);
  palanHorse = restore_map(MAP_FILE);

  return pointerp(palanHorse[ customer->query_real_name() ]);
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
  mapping palanHorse = ([ ]);
  object horse;
  string pn, *saved_info;
  int i,j,food,drink,price, num_horses;
  mixed time_stabled, days_in_stable;
  if (!engen) 
    {
      notify_fail ("The proprietor is not here!\n");
      return 0;
    }

	notify_fail("Retrieve what? Your horse perhaps?\n");

	if (!stringp(arg))
	  return 0;
	
	if (!CAN_SEE_IN_ROOM(engen) || !CAN_SEE(engen,TP))
	  {
	    engen->command("emote furrows his brow warily.");
	    engen->command("say Who goes there?");
	    return 1;
	  }

	if ((arg!="horse") && (arg!="my horse") && 
		(arg!="horses") && (arg!="my horses"))
	{
		return 0;
	}

	pn = TP->query_real_name();

	if (!restore_palan_horses())
	  {
	    notify_fail("But you have no horse stabled here.\n");
	    return 0;
	  }

	palanHorse=restore_map(MAP_FILE);

	if (!pointerp(palanHorse[pn]))
	{
		notify_fail("But you have no horse stabled here.\n");
		return 0;
	}

 	saved_info = palanHorse[pn];

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
	    days_in_stable=(time()-time_stabled) / PALDAY;

	    //set the price.
            if (!(days_in_stable > MAX_DAYS))
	      price=price+days_in_stable*DAILYCOST;

	    if (TOTAL_MONEY(TP)<price)
	      {
		notify_fail("You don't have enough money to retrieve "+
			    "your horses.\n");
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
	    days_in_stable=(time()-time_stabled) / PALDAY;

	    switch (days_in_stable)
	      {
	      case 0  :

		{
		  engen->command("say Back already for your "+
				horse->short()
				+"?");
		break;
		}
	      case 1..4  :
		{
		  engen->command("say Greetings.  I am pleased you've "
		        + "returned.  Your "+horse->short()
				+ " is right here.  That will "+
				"be "+LANG_WNUM(days_in_stable)+
				" additional platinum for the "+
				"extra time "+horse->query_pronoun()+
				" was stabled here.");
		break;
		}
	      case 5..MAX_DAYS-1 :
		{
		  engen->command("say Ahh!  I was "+
				"curious if you were coming back for your "+
				horse->short()+". Just "+
				LANG_WNUM(MAX_DAYS-days_in_stable)+
				" more days and I would have had to sell "+ 
				horse->query_objective()+" off. That will "+
				"be "+LANG_WNUM(days_in_stable)+
				" additional platinum for the "+
				"extra time "+horse->query_pronoun()+
				" was stabled here.");
		engen->command("smile .");
		break;
		}
	      case MAX_DAYS :
		{
		  engen->command("say Ahh, what a relief!  I was "+
				"unsure if you were coming back for your "+
				horse->short()+". Just one more day and I "+
				"would have had to sell "+ 
				horse->query_objective()+" off.  That'll "+
				"be "+LANG_WNUM(days_in_stable)+
				" additional platinum for the "+
				"extra time "+horse->query_pronoun()+
				" was stabled here.");
		  break;
		}
	      default :
		{
		  engen->command("sigh");
		  engen->command("say You were gone so long that I assumed "
		         + "you weren't returning for your "+
				 horse->short()+". I'm sorry, but I sold "+
				 horse->query_objective()+" to cover "+
				 "my costs.  I warned you about that when "+
				 "you stabled "+horse->query_objective()+
				 ".");
		  engen->command("kbow");
		  horse->remove_object();
		}

	      }

	    if (horse)
	      {
		price=days_in_stable*DAILYCOST;

		if (price)
		  {
		    notify_fail("You don't have enough money.\n");
		    if (!MONEY_ADD(TP,price*-1))
		      return 0;

		    write("You pay Engen "+MONEY_TEXT_SPLIT(price)+".\n");
		    say(QCTNAME(TP)+" pays Engen some money.\n");
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
                engen->command("say My condolences on your loss.");
/*
	notify_fail("Can't find your horse. Please bug with error #103!\n");
		return 0;
*/
	      }
	 
	  }

	/*I think this should really use m_delete but I can't make it work!*/
	palanHorse[pn]="";

	save_map(palanHorse, MAP_FILE);
	return 1;
	  
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
       mapping palanHorse = ([ ]);
       string filename, adj1, adj2, race, gender,
	 *customers, *saved_info, outputline,playername;

       int i,j,days_in_stable;

       mixed time_stabled;

       palanHorse = restore_map(MAP_FILE);

       customers=m_indexes(palanHorse);

       for (i=0;i<sizeof(customers);i++)
	 {
	   playername=customers[i];
	   saved_info=palanHorse[playername];

	   if (!stringp(saved_info))
	     {
	   for (j=0;j<sizeof(saved_info)/NUM_SAVED;j++)
	     {
	       gender  =saved_info[j*NUM_SAVED+2];
	       adj1    =saved_info[j*NUM_SAVED+3];
	       adj2    =saved_info[j*NUM_SAVED+4];
	       race    =saved_info[j*NUM_SAVED+5];
	       time_stabled=saved_info[j*NUM_SAVED+6]; 
	       days_in_stable=(time()-time_stabled) / PALDAY;

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

/***********************************************************/
/*
Function: clean
Purpose:  for wizard use, cleans out the stable of horses more than
          MAX_DAYS old
Parameters: none
*/

void
clean()
     {
       mapping palanHorse = ([ ]);
       string filename, instance, adj1, adj2, race, gender,
	 *customers, *saved_info, *temp_saved_info, 
	 outputline,playername;

       int i,j,days_in_stable;

       mixed time_stabled;

       palanHorse = restore_map(MAP_FILE);

       customers=m_indexes(palanHorse);

       for (i=0;i<sizeof(customers);i++)
	 {
	   playername=customers[i];
	   saved_info=palanHorse[playername];

	   if (!stringp(saved_info))
	     {
	       temp_saved_info=({});
		   
	       for (j=0;j<sizeof(saved_info)/NUM_SAVED;j++)
		 {

		   filename=saved_info[j*NUM_SAVED];
		   instance  =saved_info[j*NUM_SAVED+1];
		   gender  =saved_info[j*NUM_SAVED+2];
		   adj1    =saved_info[j*NUM_SAVED+3];
		   adj2    =saved_info[j*NUM_SAVED+4];
		   race    =saved_info[j*NUM_SAVED+5];
		   time_stabled=saved_info[j*NUM_SAVED+6]; 
		   days_in_stable=(time()-time_stabled) / PALDAY;

		   outputline=sprintf("%-=14s:%s %s %s %s %s\n",
				  capitalize(playername),
				  ctime(time_stabled),
				  gender,
				  adj1,
				  adj2,
				  race);
		   if (days_in_stable > MAX_DAYS)
		     {
		       write (outputline);
		     }
		   else
		     {
		       temp_saved_info+=( {filename, 
				     instance, 
				     gender, 
				     adj1, 
				     adj2, 
				     race, 
				     time_stabled } );
		     }
		 }
	       if (sizeof(temp_saved_info))
		 {
		   palanHorse[playername] = temp_saved_info;
		 }
	       else
		 {
		   palanHorse[playername] = "";
		 }			 
	       
	     }
	 }
       save_map(palanHorse, MAP_FILE);
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
//  add_action(do_buy,"buy");
}


/*
> <Krynn> Navarre: my search shows filenames with stable at: /Ansalon/balifor/flotsam_forest/room/stable.c
(and stable2.c), /krynn/icewall/castl2/rooms/north_stable.c (and south_stable). then in
/krynn/solamn/palan/city/stable.c, and /krynn/solamn/vin/room/stable1.c

~Terel/calathin/stable.c
*/
