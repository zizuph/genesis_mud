/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * chalice2.c
 *
 * a crystal chalice
 *
 * modified by Sorgum 950707
 * modified by Lilith Feb, 2008
 *  Stuff here in the treasure rooms are boring.
 *  Lets make them more interesting -- worthy
 *  of a King's treasure house.
 */
 

#include "/d/Terel/include/Terel.h"
inherit STDOBJECT;
#include <stdproperties.h>
#define ALTER_PROP(who, what, diff) \
    (who)->add_prop((what), (who)->query_prop(what) + (diff))
#define CHALICE_PROP "_live_i_rubbed_chalice"
int alarm_id;

/*
 * Function name: create_object
 * Description:   Default constructor.
 */
public void
create_object()
{
    ::create_object();
    set_name("chalice");
    set_adj("crystal");
    set_short("small cystal chalice");
    set_long("This is just a small dark crystal chalice.  You have " +
	     "no idea why the King has chosen to store it here.\n");

    add_prop(OBJ_I_VALUE,  900); /* half plat */
    add_prop(OBJ_I_WEIGHT, 40);
    add_prop(OBJ_I_VOLUME, 200);

    add_prop (MAGIC_AM_MAGIC,({ 80, "enchantment" }));
    add_prop (OBJ_S_WIZINFO, 
	      ("This chalice is from the treasure house of the King of "+
             "Ribos. When it is rubbed, it adds 2 levels of darkness "+
             "and 3 levels of darksight. It lasts for 10 minutes per "+
             "rub.\n"));

    add_prop (MAGIC_AM_ID_INFO,
	      ({"The "+ short() +" appears to be enchanted.\n",10,
		 "Within its cup lies a pool of darkness.\n",20,
             "Which would be released when the chalice is rubbed.\n", 30}) );

}

/* rub chalice -- increase darkness and darksight */

void 
do_darken(object tp)
{
    add_prop(OBJ_I_LIGHT, -2);
    ALTER_PROP(tp, LIVE_I_SEE_DARK, 3);
    tp->update_light(1);
    tp->add_prop(CHALICE_PROP, 1);
    tp->catch_msg("You rub the chalice and suddenly, a pool of darkness "+
        "rises from it, enshrouding you.\n");
}

void
remove_dark(object tp)
{
    if (query_prop(OBJ_I_LIGHT) == -2) 
    {
        add_prop(OBJ_I_LIGHT, 0);
        ALTER_PROP(tp, LIVE_I_SEE_DARK, -3);
        tp->update_light(1);
        tp->remove_prop(CHALICE_PROP);
        write("The darkness surrounding the chalice disappears.\n");
        remove_alarm(alarm_id);
    }
}

int
do_rub(string str)
{
    if (!strlen(str))
    {
        notify_fail("What?\n");
        return 0;
    }

    if (str != "chalice")
        return 0;

    if (TP->query_prop(CHALICE_PROP))
    {
        write("You have already rubbed the chalice!");
        return 1;
    }         

    FIX_EUID; 
    
    /* 10 minutes of darkness and darksight */
    alarm_id = set_alarm(600.0, 0.0, &remove_dark(TP));
    do_darken(TP);
    return 1;
}


void
init()
{
    ::init();
    add_action(do_rub,    "rub");
    add_action(do_rub,    "polish");
}

public void
leave_env(object from, object to)
{
    
    if (from && living(from)) 
    {
        remove_dark(from);
    }

    ::leave_env(from, to);
}
