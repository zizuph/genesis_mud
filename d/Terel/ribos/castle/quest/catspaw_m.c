/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * Queen Alexia's cat's paw
 *
 * modified by Sorgum 950707
 * modified by Lilith Feb 2009
 * modified by Petros Apr 2009 - fixing alarm handling and rubbing of
 *                               multiple paws. No longer allows dropping
 *                               of paw to get by the 1 minute cooldown.
 * Magical item:  rubbing paw of cat that died from old age gives health.
 * A catspaw is someone or something used as a tool. From a fable about 
 * a monkey that used a cat's paw to pull chestnuts out of a fire.
 *
 *   This catspaw has 5 healing charges to pull someone's chestnuts 
 *   out of a fire ;)
 *
 *   Similar effects to drow wand.
 */

#include <cmdparse.h>
#include "/d/Terel/include/Terel.h"
inherit STDOBJECT;
inherit "/lib/keep";
#define PAW_PROP "_live_i_rubbed_paw"
#define MAX_TIMES 5
int no_times;

/*
 * Function name: create_object
 * Description:   Default constructor.
 */
public void
create_object()
{
    ::create_object();
    set_name("paw");
    set_short("Queen Alexia's cats' paw");
    set_adj("cats");
    set_long("This is the paw of Queen Alexia's prized cat, Bootsie. " +
	     "It was given to the King for good luck after the cat died " +
	     "of old age.\n");

    add_prop(OBJ_I_VALUE,  1000);
    add_prop(OBJ_I_WEIGHT, 30);
    add_prop(OBJ_I_VOLUME, 33);

    add_prop (MAGIC_AM_MAGIC,({ 80, "life" }));
    add_prop (OBJ_S_WIZINFO, 
	      ("This catspaw is from the treasure house of the King of "+
             "Ribos. It can be rubbed for good health.  There are 5 "+
             "rubs for healing of 1/5 max hp each rub. There is a "+
             "forced delay of 1 minute between rubs.\n"));

    add_prop (MAGIC_AM_ID_INFO,
	      ({"The "+ short() +" tingles with the element Life.\n",10,
		 "If you <rub paw> good things might happen.\n",20,
             "Like a boost in your health, just a few times.\n", 30}));

}

/* Magical item:  rubbing paw of cat that died from old age gives health.
 */
public int
do_rub(string str)
{
    if (!strlen(str))
    {
        return 0;
    }

    object * items;
    object target;
    
    if (!pointerp(items = PARSE_COMMAND(str, this_player(), " [the] %i "))
        || !IN_ARRAY(this_object(), items))
    {
        return 0;
    }
    
    target = PARSE_COMMAND_ONE(str, this_player(), " [the] %i ");
    if (!objectp(target))
    {
        write("Which one did you want to rub?\n");
        return 1;
    }
        
    if (no_times > MAX_TIMES)
    {
        write("The paw's magic has been fully discharged already.\n");
        return 1;
    }

    // A person can have multiple paws. We allow rubbing once per minute. 
    // We check the property on both the paw and the person.
    if (TP->query_prop(PAW_PROP) + 60 > time()
        || query_prop(PAW_PROP) + 60 > time())
    {
        write("You rub the paw, but nothing seems to happen.\n");
        return 1;
    }
     
    TP->add_prop(PAW_PROP, time());
    add_prop(PAW_PROP, time());
    
    if (TP->query_hp() < TP->query_max_hp())
    {
        write("Your fingers caress the paw and suddenly you "
            + "are flooded with healing warmth.\n");
    }
    else
    {
        write("Your fingers caress the paw but you don't feel any "
            + "different.\n");
    }
    /* heal 1/5 of max hp */    
    TP->heal_hp(TP->query_max_hp() / 5);
    say(QCTNAME(TP) +" rubs something furry.\n");       

    /* This counter limits the number of rubs */
    ++no_times;  
    
    /* This tells user that the chestnuts will roast next time */
    if (no_times > MAX_TIMES)
    {
        write("The last of the paw's magic has been fully discharged.\n "+
            "It is no longer useful for healing.\n");
    }

    return 1;
}

void
init()
{
    ::init();
    add_action(do_rub,    "rub");
    add_action(do_rub,    "pet");
    add_action(do_rub,    "stroke");
    add_action(do_rub,    "touch");
    add_action(do_rub,    "caress");
}
