/**********************************************************************
 * - necklace.c                                                     - *
 * - Guild item for Thanar                                          - *
 * - Created by Mirandus 
 **********************************************************************/

#pragma strict_types

#include "guild.h"
#include <language.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

inherit "/std/object";
inherit "/lib/wearable_item";
inherit "/d/Genesis/specials/examples/std_magic_lib";

#define ADJ1 ({"extravagant","shimmering","flashy","beautiful",\
                      "magnificient","opulent", "buffed"})
#define ADJ2 ({"golden","platinum","topaz","diamond-encrusted","gold",\
                      "silver"})

public string 
query_auto_load()   { return MASTER + ":"; }

public void
create_object()
{
   string adj1 = one_of_list(ADJ1);
   string adj2 = one_of_list(ADJ2);
   
   setuid();
   seteuid(getuid());
    
   set_name("necklace");
   add_name(({"medallion", OBJECT_ID}));
   set_adj(adj1);
   add_adj(adj2);
   set_short(adj1 + " " + adj2 + " necklace");
   set_long("A long, beautifully-crafted "+adj2+" chain necklace. It is a "+
   "symbol of servitude to the beliefs and purpose of the Thanarians "+
   "and the patron god of humanity, Thanar.\n"+
   "A symbol of a black snake is engraved on a small flat portion of the "
   +"necklace. On the other sized is engraved: <thhelp>. \n");
   set_wf(this_object());
   set_slots(A_NECK);
   
   add_item(({"symbol", "engraved symbol", "snake symbol"}),
   "The symbol is engraved within the necklace and the design "+
   "is of a snake wrapped around a sword.\n");
   add_prop(OBJ_S_WIZINFO, "Thanar Racial Guild Item.\n");
   add_prop(OBJ_M_NO_DROP,"Oddly enough, you can't seem to "+
     "do that.\n");
    add_prop(OBJ_M_NO_GIVE, "It's sentimental value is too high "+
      "for you to simply give it away.\n");
    add_prop(OBJ_M_NO_SELL, "The shopkeeper finds it uninteresting.\n");
    add_prop(OBJ_M_NO_STEAL, 1);
    add_prop(OBJ_I_WEIGHT, 400);
    add_prop(OBJ_I_VOLUME, 1200);
    add_prop(OBJ_I_VALUE, 100);
    
    set_magic_obj_soul(GSPELLS + "summon_soul.c");
}

public int
wear(object item)
{
    write("You wear the " + short() + " around your neck " +
      "adjusting it to sit straight.\n");
    say(QCTNAME(TP) + " wears the " + short() + " around " +
      HIS(TP) + " neck adjusting it to sit straight.\n");
    
    return 1;
}

public int
remove(object item)
{
    write("You remove the " + short() + " from around your neck.\n");
    say(QCTNAME(TP) + " removes the " + short() +
      " from around " + HIS(TP) + " neck.\n");       
    return 1;
}

void
enter_env(object env, object from)
{
    /* Required to add magic obj effects to the item */
    ::enter_env(env, from);
    
    remove_name(OBJECT_ID);
    
    if(present(OBJECT_ID,E(TO)))
    {
        tell_room(E(TO),"You throw the duplicate necklace away.\n");
        remove_object();
        return;
    }
    
    add_name(OBJECT_ID);
    
    if (IS_MEMBER(env) || env->query_wiz_level())
        add_magic_obj_effects(this_player());
}

public void
leave_env(object from, object to)
{
    ::leave_env(from, to);
    wearable_item_leave_env(from, to);
}