
#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>
#include "../nov.h";

#define TO  this_object()
#define TP  this_player()

inherit "/std/armour.c";

static  object  Shadow;

public int     query_value() { return 0; }


// a black-robed high-collared human


public void
create_armour()
{
    set_name(({"robe","cloak","Necro_Robe"}));
    set_adj(({"black","high-collared", "hooded"}));
    set_short("black high-collared robe");
    
    set_long("This robe is made of ordinary cloth, at least so it seems to the untrained " +
    "eye. It is in fact crafted with the utmost precision with the assistance of " +
    "magic. Unlike most robes, this one does not have a hood to conceal one's " +
    "image from unwanted eyes. Instead, a high-back collar, standing erect is " +
    "the most interesting feature of the robe. The lip of the collar is made of " +
    "flowing arches oriented upside down. The robe is quite large, freely falling " +
    "and flowing around the body of its owner. The material is not quite smooth, " +
    "it looks as if it is slightly crumpled in places - a conscious design for " +
    "certain. The shoulders have ample space due to the crafting of the robe, " +
    "not hindering any movements despite its weight. The material is a dark black, " +
    "it doesn't reflect a single ray of light off of its surface.\n");
    
    set_ac(1);
    set_af(TO);
    set_at(A_ROBE);
    add_prop(OBJ_I_VALUE,   57);
    add_prop(OBJ_I_WEIGHT, 300);
    add_prop(OBJ_I_VOLUME, 200);

    setuid();
    seteuid(getuid());  
}


public mixed
remove(object ob)
{
    if (ob != TO)
        return -1;
        
    if (this_player()->query_necro_robed())
        Shadow->remove_shadow();

    
    return 0;
}


public mixed
wear(object ob)
{
    object  tp = TP;

    if (ob != this_object())
        return -1;
        
    if (this_player()->query_guild_name_lay() != GUILDNAME)
    {
        write("For some reason, you fail understand how to wear it.\n");
        this_player()->command("drop robe");
        return 1;
    }

    write("You wear the "+query_short()+" around your body.\n");
    say(QCTNAME(this_player())+" wears "+LANG_ASHORT(this_object())+".\n");

    Shadow = clone_object(NOV_DIR +"shadows/necro_rob_sh");
    Shadow->shadow_me(this_player());
    this_player()->init_robe_shadow();
    return 1;
}


public void
leave_env(object from, object to)
{
    if (objectp(from) && from->query_necro_robed())
    {
        Shadow->remove_shadow();
    }

    ::leave_env(from, to);
}
