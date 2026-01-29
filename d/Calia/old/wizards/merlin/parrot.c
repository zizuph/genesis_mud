/* This is a parrot, who will be able to tell the player all changes in
   his stat (hit points, alignement and the whole rest).
   In the beginning now it's only a normal object
                                                        Merlin
*/
#define PARR_DELAY 10			/* every 10th sec a check */
#define PARR_WEIGHT 300			/* 300g */
#define PARR_VOLUME 0			/* it's sitting on your shoulder */
 
inherit "/std/object";
 
#include <stdproperties.h>
#include <merlin.h>
#include <state_desc.h>
 

void do_check();  

/* static variables */
private string physical, mental, alignment;
 
 
create_object()
{
  	set_name("parrot");
  	set_pname("parrots");
  	set_short("little parrot");
  	set_pshort("little parrots");
  	set_long(break_string("It's a wonderfully coloured little parrot. "
             + "It does not look extraordinary, so you don't see what "
             + "use it has. You wonder if this parrot can speak...\n",70));
 
 
  	add_prop(OBJ_I_WEIGHT,PARR_WEIGHT);
  	add_prop(OBJ_I_VOLUME,PARR_VOLUME);
 
    /* set global variables */
 
    physical = "";
 
   set_alarm(itof(PARR_DELAY), 0.0, do_check);
 
}
 
/*
 * Function name: do_check
 * Description:   makes a check of the players stats
 * Arguments:     none
 * Returns:       nothing
 */
 
void
do_check()
{
  	object env; 		/* object carrying the parrot */
 
  	env = environment();
 
 	 /* Tell the player his stats, this should be done with a shadow */
	if (living(env)) /* only if environment is a player ! */
	{
 
	    string *stat;          /* pointer to string array for stats */
		string tempstr;	/* temp string to compare with old */
   		int temp, max; 	
 
    	/* physical stats */
 
 
    	stat = SD_HEALTH;
    	temp = env->query_hp();
    	max = env-> query_max_hp();
 
    	tempstr = get_proc_text(temp * 100 / max, stat, 0, ({}));
										/* found in /cmd/live/state.c */
 
#if 0
    	if(tempstr != physical)
    	{
#endif
			physical = tempstr;
 
	    	tell_object(env, BS("The parrot croaks in your ear, that you seem to be physically "
			     				 + physical  + " now.\n"));
#if 0
	    }
 
    	/* mental stats */
 
	    stat = SD_MANA
    	temp = env->query_mana();
	    max = env-> query_max_mana();
 
    	tempstr = get_proc_text(temp * 100 / max, mana, 0, ({}));
 
    	if(tempstr != mental)
    	{
    		tell_object(env, BS("The parrot croaks in your ear, that you seem to be mentally "
				                 + tempstr  + " now.\n"));
			mental = tempstr;
    	}
 
    	/* alignment */
 
    	stat = SD_ALIGN
    	temp = env->query_mana();
    	max = env-> query_max_mana();
 
    	tempstr = env->get_proc_text(temp * 100 / max, mana, 0, ({}));
 
    	if(tempstr != mental)
    	{
    		tell_object(env, BS("The parrot croaks in your ear, that you seem to be mentally "
			     			     + tempstr  + " now.\n"));
			mental = tempstr;
    	}
 
#endif
 
  	}
  	else
  	{
 
    	physical = "";
	}
 
  /* Restart the function */
 
  set_alarm(itof(PARR_DELAY), 0.0, do_check);
 
}
 
