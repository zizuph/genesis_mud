/*
*  /d/Faerun/guilds/warlocks/obj/warlock_robe3.c
*
*  2018, Nerull
*
*/

#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>
#include "../guild.h";
#define TO  this_object()
#define TP  this_player()

inherit "/std/armour.c";
inherit "/lib/wearable_item";

static  object  Shadow;

public void
create_armour()
{
    setuid();
    seteuid(getuid());  
    
    set_name(({"robe","cloak","warlock_robe"}));
    add_name(GUILD_ITEM_NAME);
    add_name("patr3_guild_object");
    set_adj(({"violet", "hooded"}));
    set_short("violet hooded robe");
    
    set_long("This hooded robe is made of ordinary cloth but is dyed "
    +"in a gross violet color. You sense the presence of "
    +"tormented infant souls in the fabric.\nWarlocks may <wahelp> for more information.\n");
    
    set_ac(1);
    set_af(TO);
    set_at(A_ROBE);
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_WEIGHT, 300);
    add_prop(OBJ_I_VOLUME, 200);
        
    set_looseness(20);
    set_layers(1);
}


/*public mixed
remove(object ob)
{
    if (this_player()->query_war_robed())
        Shadow->remove_warrobe_shadow();
    
    return 0;
}*/


public mixed
wear(object ob)
{
    if (this_player()->query_guild_name_lay() != WARLOCK_NAME 
    && !WARLOCK_MASTER->is_patr3_warlock(this_player()->query_name()))
    {
        return "As you try to wear the violet hooded robe, flashes "
        +"of mutilated infants spills into your mind! You let it be.\n";
        return 1;
    }
    
    write("You wear the "+query_short()+" around your body.\n");
    say(QCTNAME(this_player())+" wears "+LANG_ASHORT(this_object())+".\n");
    //Shadow = clone_object(WARLOCK_GUILDDIR + "obj/warlock_robe3_sh");
    //Shadow->shadow_me(this_player());
    //this_player()->init_warrobe_shadow();
    
    return 1;
}


public void
leave_env(object from, object to)
{
    if (objectp(from) && from->query_war_robed())
    {
        Shadow->remove_shadow();
    }
    ::leave_env(from, to);
}


void
enter_env(object to, object from)
{
    ::enter_env(to, from);
   
    if (sizeof(filter(all_inventory(to),&->id(GUILD_ITEM_NAME)) - ({this_object() })))
    {
        // One is enough.
        set_alarm(0.0, 0.0, remove_object);
        return;
    }
}