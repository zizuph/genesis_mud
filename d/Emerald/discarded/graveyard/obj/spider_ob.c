/*
 * SPIDER_OB.c
 * this is a nasty little thing that will make even the most experienced
 * champion arachnaphobic :)
 * 
 * By Alaron July 20, 1996
 */

#include "../default.h"
#include <macros.h>
#include <stdproperties.h>

inherit "/std/object";

void do_spider_noise(object ob);
int noise_counter = 0;

void
create_object()
{
    set_name("_spider_");
    set_no_show();

    add_prop(OBJ_M_NO_DROP,"Drop what?\n");
    add_prop(OBJ_M_NO_GIVE,"Give what?\n");
    add_prop(OBJ_I_WEIGHT,0);
    add_prop(OBJ_I_VOLUME,0);
    

    if (IS_CLONE)
        set_alarm(8.0,8.0,&do_spider_noise(this_player()));

}

void
do_spider_noise(object ob)
{
    int x = random(3);

    switch (x)
    {
    case 0: {
	tell_object(ob,
		    "A horde of spiders comes streaming down out of "+
		    "your hair, scurrying to the ground through your "+
		    "clothes!!\n");
	tell_room(environment(ob),
		  "A horde of spiders comes streaming down out of "+
		  QTNAME(ob)+"'s hair, scurrying down to the ground "+
		  "through "+ob->query_possessive()+" hair.\n",ob);
            break;
    }
	case 1:
	    {
		tell_object(ob,
			    "Dozens of little black spiders scurry up your "+
			    "legs and through your clothing!!\n");
		tell_room(environment(ob),
			  "Dozens of little black spiders scurry up "+
			  QTNAME(ob)+"'s legs and through "+ob->query_possessive()+
			  " clothing!!\n", ob);
            break;
	    }
	case 2: {
	    tell_object(ob,
			"Hundreds of little black spiders stream out of "+
			"your clothing and swarm on top of you!!\n");
	    tell_room(environment(ob),
		      "Hundreds of little black spiders stream out of "+
		      QTNAME(ob)+"'s clothing and stream on top of "+
		      ob->query_objective()+"!!\n", ob);
	}
	}


    
    noise_counter++;
    if (noise_counter == 4)
    {
	remove_object();
    }

}
