#include <stdproperties.h>
#include <macros.h>
#include <language.h>
#include <ss_types.h>
#include "../nov.h"

inherit NOV_DIR +"temple/std_room";

object paralyze;

mapping token_spells = ([ ]);

 
public int 
block_studyers()
{
      
    if (!this_player()->query_prop(IAMSTUDYING))
    {
        return 0;
    }
    
    

  
    write("You are in the middle of a study! End the study first before leaving.\n");
        return 1;
}
 
void
create_nov_room()
{
                   
    set_name("In the western secion of the grand library");
    add_name( ({ "room", "hall", "corridor", "library" }) );

    set_short("In the western section of the grand library");
    set_long("This room is dimly lit and exceptionally dusty, and the dry smell of decayed " +
             "parchments gives its purpose away, for this is indeed an ancient library. There " +
             "are more shelves in here than you can count, all bursting with arcane " +
             "tomes and scrolls, enough to keep even the most ardent and dedicated " +
             "of scholars deep in study for years. A square section of the stone " +
             "floor is covered with a rug which muffles the sounds of approaching " +
             "footsteps. Smoking braziers responsible for the eerie glow stand at " +
             "each corner of the room, emitting a harsh-smelling incense.\n");
    
        
        
        add_item(({"dust"}),
        "Dust can be seen everywhere, you guess it mostly comes from the ancient " +
        "tomes the Necromancers are studying every day.\n");
        
        add_item(({"shelf", "shelves"}),
        "The wooden shelves should have been broken by the enormous weight of " +
        "the tomes placed on them. There is no other explanation that they have been " +
        "enchanted by a spell of endurance.\n");
        
        add_item(({"parchments"}),
        "You see parchments on the shelves to your west, east and south, although " +
        "the tomes look a lot more interesting.\n");
        
        add_item(({"tome", "tomes"}),
        "Tome after tome is stacked upon the shelves, they are part of Velsaroons " +
        "personal library. You may study the tomes here, perhaps you can learn something.\n");
        
        add_item(({"scrolls"}),
        "The scrolls seems to be so decayed that you are affraid of crumbling them if " +
        "you touch them. Perhaps you should concentrate on the tomes instead.\n");
        
         add_item(({"rug"}),
        "This is circular rug has the responsibility to keep the sounds of " +
        "footsteps on the cold stone floor to a minimum. The rug has a the " +
        "mark of Velsharoon on it.\n");
        
        add_item(({"floor"}),
        "The floor is made from large grey flagstone squares with dust filling " +
        "up the small wells.\n");
 

    add_exit(NOV_DIR + "temple/nmagic",   "east", block_studyers);
    
    setuid();
    seteuid(getuid());  
    


}



void
research_spell1(int level, object pl)
{

    object borb = present("_novtoken", pl);
    string *known_spells = ({ });
    string *a_spell = SPELL_LIST[level];
    string spell, *new_spells = ({ }), js, log;
    int i, j;
    setuid();
    seteuid(getuid());
    
     
    if (!objectp(borb))
    {
        pl->catch_tell("You must have your orb in order to learn new spells.\n");
        return;
    }

    token_spells = restore_map(NOV_DIR +"log/token_spells");
    if (known_spells = token_spells[pl->query_real_name()])
        a_spell -= known_spells;
    else known_spells = ({ });
    j = sizeof(a_spell) - 1;
    if (!sizeof(a_spell))
    {
        pl->catch_tell("There are no more spells for you to learn here.\n");
        
        return;
    }
    
    
    
    spell = a_spell[random(sizeof(a_spell))];

    
    new_spells = known_spells; 
    new_spells += ({ spell });
    
    switch(j)
      {
      case 0:
        js = "no more spells";
        break;
      case 1:
        js = "one more spell";
        break;
      default:
        js = LANG_WNUM(j) + " more spells";
      }

    pl->catch_tell("Finally, After a long and tedious research in arcane texts " +
    "and formulas, you learn the spell "+spell+".\n" + 
    "There are "+js+" to research in this part of the grand library.\n");

    token_spells[pl->query_real_name()] = new_spells;
    
    save_map(token_spells, NOV_DIR +"log/token_spells");
    borb->setup_my_spells(pl);
    
    

}


void
end_tome()
{
    
    
 
    
           if (!this_player()->query_prop(IAMSTUDYING))
           {
           	//write("Debugg\n");
           	this_player()->remove_prop(LIVE_S_EXTRA_SHORT);
           	return;
           }
        
    
           if (this_player()->query_skill(RESEARCH1) >= 90)
		{
			
			
			paralyze = clone_object("/std/paralyze");
                        paralyze -> set_remove_time(3);
                        paralyze -> set_fail_message("You are busy putting the tome onto the shelf!\n");
                        paralyze -> set_stop_message("");
                        paralyze -> move(this_player(), 1);
			
			
			tell_room(environment(this_player()), QCTNAME(this_player())+" learns the " +
    	                "principe of a new spell.\n", this_player());
			
			tell_room(environment(this_player()), QCTNAME(this_player())+" closes the tome " +
    	                "and puts it back to the shelf.\n", this_player());
    	                
    	                write("You finish the studying of the tome and put it back " +
                               "onto the shelf where you found it.\n");
    	   
    	                this_player()->remove_skill(RESEARCH1);
			this_player()->remove_prop(IAMSTUDYING);
			this_player()->remove_prop(LIVE_S_EXTRA_SHORT);
			this_object()->research_spell1(1, this_player());
			
			return;
	        }
	        
	      paralyze = clone_object("/std/paralyze");
              paralyze -> set_remove_time(3);
              paralyze -> set_fail_message("");
              paralyze -> set_stop_message("");
              paralyze -> move(this_player(), 1);
                           
	       write("You finish studying the tome and put it back onto " +
	       "the shelf where you found it.\n"); 
           this_player()->set_skill(RESEARCH1, this_player()->query_skill(RESEARCH1) + random(RTIME));
    	   tell_room(environment(this_player()), QCTNAME(this_player())+" closes the tome " +
    	   "and puts it back onto the shelf.\n", this_player());
    	   this_player()->remove_prop(IAMSTUDYING);
    	   this_player()->remove_prop(LIVE_S_EXTRA_SHORT);
}
    

    	

int
do_study(string str)
{

            int a, b, c, time;
            //object paralyze;

               if (str != "tomes")
               {
               	 write("Study tomes, perpaps?\n");
               	 return 1;
               	}
               	 

	        if (this_player()->query_prop(IAMSTUDYING))
	        {
	        	write("You are already studying!\n");
	        	return 1;
	        }
	        
	        


	// The actual research.
	
	        if (!this_player()->query_skill(RESEARCH1))
	        {
	        	this_player()->set_skill(RESEARCH1, 1);
	        }
	        
	     
	   a = this_player()->query_stat(3);
	   b = this_player()->query_stat(8);
	   c = this_player()->query_skill(SS_SPELLCRAFT) * 2;  
	     
	   time = 600 - a - b - c; 
	   
	   if (time < 100)
	   {
	   	time = 100;
	   }
	   
	  // Debugg timer.  time = 10;
	 
	     
	   write("You pick a dusty tome from one of the shelves and begin to study its " +
	   "contents.\n");
	   
           tell_room(environment(this_player()), QCTNAME(this_player())+" picks a tome from " +
           "one of the shelves and begins to study.\n", this_player());
            
            /*paralyze = clone_object("/std/paralyze");
            paralyze -> add_name("_studyp");
            paralyze -> set_remove_time(time);
            paralyze -> set_fail_message("You are busy studying a tome of magic!\n");
            paralyze -> set_stop_message("");
            paralyze -> move(this_player(), 1);*/
              
            this_player()->add_prop(IAMSTUDYING, 1);  
            this_player()->add_prop(LIVE_S_EXTRA_SHORT, " is studying a tome of magic");
            set_alarm(itof(time - 1),0.0,&end_tome());

            tell_room(environment(this_player()), QCTNAME(this_player())+" picks a tome from " +
           "one of the shelves and begins to study.\n", this_player());
	        
	
	
	
	return 1;
}

int
end_study(string str)
{
	if (str != "study")
	{
		write("End study first, perhaps?\n");
		return 1;
	}
	
	if (!this_player()->query_prop(IAMSTUDYING))
	{
		write("But you are not studying!\n");
		return 1;
	}
	
	this_player()->remove_prop(IAMSTUDYING);
	this_player()->remove_prop(LIVE_S_EXTRA_SHORT);
	write("You stop the study of the tome of magic and return it onto the shelf.\n");
	tell_room(environment(this_player()), QCTNAME(this_player())+" closes the tome " +
    	"and puts it back onto the shelf.\n", this_player());
    	return 1;
}


void init()
{
 add_action(do_study, "study");
 add_action(end_study, "end");

 
 ::init();
}
