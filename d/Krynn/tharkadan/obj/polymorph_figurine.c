/*
 *  A magical figurine that polymorphs you into a drake
 *  and flies you over the snow-blocked path in Tharkadan/
 *
 *  To use it you need to be standing in a Tharkadan outdoor room
 *  and need two quest bits (krynn 2 2 and krynn 2 3):
 *        * Disks of Mishakal quest
 *        * Pax Tharkas prisoner quest
 *
 *  It also needs to be winter.
 *
 *  Coded by Arman 2017.
 */

inherit "/d/Krynn/std/std_magic_obj";
inherit "/lib/keep";

#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <cmdparse.h>

#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/common/clock/clock.h"

#define DRAGON_ID     "_thark_polymorph_figurine"

int vapour = 0;

public void
create_magic_obj()
{
    set_name("figurine");
    add_name(DRAGON_ID);
    add_pname(DRAGON_ID + "s");
    add_adj("serpent");
    set_long("This is a curious figurine carved of white quartz. It is " +
         "shaped like a wingless serpent, its toothy maw open in a " +
         "silent shriek. You could probably hold it in both hands.\n");

    add_prop(OBJ_I_WEIGHT,20);
    add_prop(OBJ_I_VOLUME,20);
    add_prop(OBJ_I_VALUE, 100);
    add_prop(MAGIC_AM_MAGIC,({20,"enchantment"}));
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);

    add_prop(MAGIC_AM_ID_INFO,
      ({ "This is a figurine of transformation. This one will transform " +
         "the holder into a white dragon hatchling when the vapours of " +
         "the figurine are inhaled. This ability can only be activated " +
         "when in the Tharkadan mountain ranges during the winter " +
         "season.\n", 20 }));

    add_prop(OBJ_S_WIZINFO, "This figurine can be found in a clutch of " +
         "dragon eggs in an ancient volcano in the Tharkadan Mountain " +
         "ranges. When used, it changes the player into a white dragon " +
         "hatchling, who then flies to a spot in the Tharkadan range, " +
         "allowing players to enter this area when the pass " +
         "in blocked in winter. This object can only be used when " +
         "standing in a room in /d/Krynn/tharkadan/ and when it is " +
         "winter.\n");
        
    set_slots(W_BOTH);
    set_keep(1);

    set_holdable(1);
    
    set_magic_obj_spell("/d/Krynn/tharkadan/spells/polymorph_self.c");
    set_magic_obj_effect("_polymorph_object_");
    
    add_cmd_item(({"vapour","the vapour","vapours","the vapours"}),
                   "inhale", "@@use_figurine");
}

string
use_figurine()
{
    int in_thark = wildmatch("/d/Krynn/tharkadan/room/*",
        file_name(environment(TP)));

    if(!vapour)
    {
       notify_fail("Inhale what?\n");
       return 0;
    }

    if(!this_object()->query_held())
    {
        write("You have to be holding the figurine to use it.\n");
        return "";
    }

    foreach(string spell: query_magic_obj_spell())
    {
        if (safely_load_master_file(spell))
            spell->do_ability("drake");
    }
    
    return "";
}

void
reset_vapour(object player)
{
    tell_room(environment(player), "The frigid vapours dissipate.\n");
    vapour = 0;
}

void
effect_on(object player)
{
    int in_thark = wildmatch("/d/Krynn/tharkadan/room/*",
        file_name(environment(player)));

    if (!player->test_bit("krynn", 2, 2) || 
        !player->test_bit("krynn", 2, 3))
    {
       tell_object(player, "You think you feel the figurine pulse " +
           "briefly - as if checking something. A brief hiss escapes " +
           "from its open maw whispering something to you... two " +
           "words... 'missing narrative'?\n");
       return;

    }

    if (objectp(player) && in_thark && (GET_SEASON == WINTER) &&
        (!environment(player)->query_prop(ROOM_I_INSIDE)))  
    {
       tell_object(player, "The figurine pulses icily, releasing a " +
           "cloud of frigid vapours towards you! If you so desire, " +
           "you could inhale the vapour.\n");

       if (environment(player))
       {
           tell_room(environment(player), "The serpent figurine held by " +
               QTNAME(player)+ " releases a cloud of vapours from its " +
               "open maw!\n", player);
       }

       set_alarm(10.5,0.0,&reset_vapour(player));
       vapour = 1;
       return;
    }

    tell_object(player, "You think you feel the figurine pulse " +
           "briefly - as if checking something - and then become inert " +
           "again.\n");
}

public string
hook_magic_obj_hold()
{
    set_alarm(1.0,0.0,&effect_on(this_player()));      
}


public void
leave_env(object env, object to)
{
    ::leave_env(env, to);
    holdable_item_leave_env(env, to);
}

public void
appraise_object(int num)
{
    ::appraise_object(num);
    appraise_holdable_item();
}

public string
query_recover()
{
  return MASTER;
}

void
destroy()
{
    tell_object(E(TO), "The two serpent figurines suddenly writhe " +
           "around each other as if in vicious combat, until only " +
           "one remains!\n");
    remove_object();
}

enter_env(object dest, object old)
{
    mixed oblist;
    if (dest)
    {
	oblist = FIND_STR_IN_OBJECT("all " + DRAGON_ID + "s",dest);
	oblist -= ({ 0, TO });
	if(oblist && sizeof(oblist) > 0)
	    set_alarm(4.0,0.0,"destroy");
    }
    ::enter_env(dest,old);
}