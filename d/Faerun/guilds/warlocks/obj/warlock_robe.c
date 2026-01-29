/*
*  /d/Faerun/guilds/warlocks/obj/warlock_robe.c
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

static  object  Shadow;

public void
create_armour()
{
    set_name(({"robe","cloak","warlock_robe"}));
    set_adj(({"yellow", "hooded"}));
    set_short("yellow hooded robe");
    
    set_long("This hooded robe is made of ordinary cloth but is dyed "
    +"in a sickening yellow colour. The sensation of madness swirls "
    +"in your mind as you observe it.\n");
    
    set_ac(1);
    set_af(TO);
    set_at(A_ROBE);
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_WEIGHT, 300);
    add_prop(OBJ_I_VOLUME, 200);
    setuid();
    seteuid(getuid());  
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
    if (this_player()->query_guild_name_lay() != WARLOCK_NAME)
    {
        return "As you try to wear the yellow hooded robe, flashes "
        +"of terribly entities beyond time and space bursts "
        +"through your mind!\nYou decide to not wear it as "
        +"you feel uneasy about the terrible experiment "
        +"you just experienced!\n";
        return 1;
    }
    
    write("You wear the "+query_short()+" around your body.\n");
    say(QCTNAME(this_player())+" wears "+LANG_ASHORT(this_object())+".\n");
    //Shadow = clone_object(WARLOCK_GUILDDIR + "obj/warlock_robe_sh");
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