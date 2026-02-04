




/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * thief_glove.c
 *
 * A thief glove, used in the dungeon quest.
 *
 * Updated to reflect use of new standard armour in Terel.
 * Torm, Sept 98
 */

#include <wa_types.h>
#include <ss_types.h>
#include "/d/Terel/include/Terel.h"
#include "/d/Terel/LoD/dungeon/quest.h"

inherit STDARMOUR;
inherit "/lib/keep";

#define REVERT_OBJ  (LOD_DIR + "obj/thand")
#define MIN_DUR     10
#define DEF_DUR     100
#define MAX_DUR     1000

int duration = DEF_DUR, aid = 0;

public void
create_terel_armour()
{
    set_name("glove");
    add_name(DQ_THIEF_GLOVE);
    set_adj("skin");
    set_long("It is a skin glove. It's made of some kind of " +
             "yellowish skin that looks strangely familiar.\n");

    set_default_armour(10, A_R_HAND, 0, 0);
    set_am(({ 2, 2, -4}));

    add_prop(OBJ_I_WEIGHT, 300);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(MAGIC_AM_MAGIC, ({ 30, "conjuration" }));
    add_prop(MAGIC_AM_ID_INFO,
	         ({"This is a magical glove.\n", 10,
	           "It will help you in entering the dungeon crystal and " +
	           "endure the dangers within it.\n", 40}));
	add_prop(OBJ_S_WIZINFO, "A special glove used in the dungeon quest.\n");
    add_prop(OBJ_I_VALUE, 83);
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
