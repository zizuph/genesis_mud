
/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * Hillary's broom
 *
 * modified by Sorgum 950707
 * modified by Lilith Feb, 2008
 *  Stuff here in the treasure rooms are boring.
 *  Lets make them more interesting -- worthy
 *  of a King's treasure house.
 */

#include "/d/Terel/include/Terel.h"
inherit STDOBJECT;
inherit "/lib/keep";
#define BROOM_PROP "_live_i_am_riding_broom"
object broom_effect;
int alarm_id;

/*
 * Function name: create_object
 * Description:   Default constructor.
 */
public void
create_object()
{
    ::create_object();
    set_name("broom");
    set_short("Hillary's broom");
    set_long("This is the broom that the Calathin Mayors wife, " +
	     "Hillary Rodham Archibus, once used to fly around on.  " +
	     "She stopped using it when she was crushed by a house.\n");

    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_VALUE,  1000);

    add_prop (MAGIC_AM_MAGIC,({ 80, "air" }));
    add_prop (OBJ_S_WIZINFO, 
	      ("This broom is from the treasure house of the King of "+
             "Ribos. When riding it, a player feels lighter on his "+
             "feet and thus is less fatigued. This clones the "+
             "broom_effect object which is a reverse poison. "+
             "It slips you off after 10 minutes.\n"));

    add_prop (MAGIC_AM_ID_INFO,
	      ({"The "+ short() +" tingles with the element Air.\n",10,
		 "You might feel lighter on your feet when riding it.\n",20,
             "Which would certainly make you less fatigued.\n", 30}) );


}

/* MAGICAL ride broom -- you feel light on your feet when riding this broom -- fatigue regen for 10 minutes. */

void
remove_the_prop()
{
    
    if (environment(TO)->query_prop(BROOM_PROP))
    {
        TP->remove_prop(BROOM_PROP);
        remove_alarm(alarm_id);
        if (living(environment(TO)))
        {
            TP->catch_msg("You slip off the broom.\n");
        }
    }
}


int
do_ride(string str)
{
    if (!strlen(str))
    {
        notify_fail("What?\n");
        return 0;
    }

    if (str != "broom")
        return 0;

    if (TP->query_prop(BROOM_PROP))
    {
        write("You are already riding the broom!");
        return 1;
    }         

    FIX_EUID; 
    TP->add_prop(BROOM_PROP, 1);
    broom_effect = clone_object("/d/Terel/ribos/castle/quest/broom_effect"); 
    broom_effect->move(TP);
    broom_effect->start_poison(TP);      
    alarm_id = set_alarm(600.0, 0.0, remove_the_prop);
    write("You hop on the broom. It has enough magic left to support your "+
        "weight just enough for you to feel lighter on your feet.\n");
    return 1;
}


void
init()
{
    ::init();
    add_action(do_ride,    "ride");
    add_action(do_ride,    "straddle");
    add_action(do_ride,    "fly");
    add_action(do_ride,    "sit");
}

void
leave_env(object from, object to)
{
    remove_the_prop();
    broom_effect->remove_object();

    ::leave_env(from, to);
}
