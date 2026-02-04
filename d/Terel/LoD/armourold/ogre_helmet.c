/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * ogre_helmet.c
 *
 * An ogre helmet, used in the dungeon quest.
 */

#include "/d/Terel/include/Terel.h"
inherit STDARMOUR;
inherit "/lib/keep";

#include <wa_types.h>
#include <ss_types.h>

#include "/d/Terel/LoD/dungeon/quest.h"

#define REVERT_OBJ  (LOD_DIR + "obj/ohead")
#define MIN_DUR     10
#define DEF_DUR     100
#define MAX_DUR     1000

int duration = DEF_DUR, aid = 0;

public void
create_armour()
{
    set_name("skull");
    add_name("helmet");
    add_name(DQ_OGRE_HELMET);
    set_adj("hollow");
    set_long("It is a hollow skull of an ogre! It has been carved so it " +
             "can be used as an helmet. It probably provides good " +
             "protection of your head, since the bones of an ogre are " +
             "known to withstand quite a lot.\n");

    set_default_armour(30, A_HEAD, 0, 0);
    set_am(({ -4, -4, 8}));

    add_prop(OBJ_I_WEIGHT, 1700);
    add_prop(OBJ_I_VOLUME, 800);
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(MAGIC_AM_MAGIC, ({ 30, "conjuration" }));
    add_prop(MAGIC_AM_ID_INFO,
	         ({"This is a magical helmet.\n", 10,
	           "It will help you in entering the crystal and " +
	           "endure the dangers within it.\n", 40}));
	add_prop(OBJ_S_WIZINFO, "A special helmet used in the dungeon quest.\n");
    add_prop(OBJ_I_VALUE, 200);
}

public void
revert_back()
{
    object where = query_worn();
    
    aid = 0;
    
    if (where)
    {
        set_this_player(where);
        remove_me();
    }
    else
        where = ETO;
    
    if (!where)
    {
        remove_object();
        return;
    }
    
    if (living(where))
        where->catch_msg("Something is happening to your " + short() + ".\n");
    else if (where->query_prop(ROOM_I_IS))
        tell_room(where, "Something is happening to the " + short() + ".\n");

    seteuid(getuid());
    clone_object(REVERT_OBJ)->move(where);
    
    remove_object();
}

public void
set_duration(int t)
{
    if (t < MIN_DUR)
        t = MIN_DUR;
    if (t > MAX_DUR)
        t = MAX_DUR;
        
    duration = t;
}

public string
query_recover()
{
    int time_left = DEF_DUR;
    
    if (aid)
    {
        time_left = ftoi(get_alarm(aid)[2]);
    }
    
    return MASTER + ":" + query_arm_recover() + "#dur#" + time_left + "##";
}

public void
init_recover(string arg)
{
    int dur;
    string foobar;

    init_arm_recover(arg);
    if (sscanf(arg, "%s#dur#%d##", foobar, dur) != 2)
        dur = DEF_DUR;

    aid = set_alarm(itof(dur), 0.0, revert_back);
}

public void
enter_env(object to, object from)
{
    ::enter_env(to, from);
    
    if (!to || !living(to) || aid)
        return;
        
    aid = set_alarm(itof(duration), 0.0, revert_back);
}
