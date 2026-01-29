
//  /bazaar/Obj/misc/pouch.c
// creator(s): Ilyian
// last update: Boriska , Sep 1995. Made the second gem random
//              Two gems are too much. 
// purpose: Small pouch the npcs keep things in
//          This one contains 1 or 2 random gems
//          Meant for the possession of the punishers
// note:
// bug(s):
// to-do:


inherit "/std/receptacle";

#include "/d/Genesis/gems/gem.h"
#include "/d/Avenir/common/common.h"
#include <stdproperties.h>
#include <cmdparse.h>
#include <macros.h>

public void
create_container()
{
    set_name("pouch");
    add_name("_money_and_gem_pouch_");
    set_pname("pouches");
    set_adj( ({ "small","leather" }) );
    set_long("This is a small leather pouch, used to hold money or"+
             " other small items.\n");

    add_prop(CONT_I_HOLDS_COMPONENTS, 1);
    add_prop(CONT_I_IN,1);
    add_prop(CONT_I_WEIGHT,     1200);          /* 1.2 kg        */
    add_prop(CONT_I_VOLUME,     500);           /* Empty volume. */
    add_prop(CONT_I_MAX_VOLUME, 3*1000);       /* 3.0 l          */
    add_prop(CONT_I_MAX_WEIGHT, 5*1000);      /* 5.0 kg        */
    add_prop(CONT_I_CLOSED,     0);
    add_prop(CONT_I_RIGID,      0);
    add_prop(CONT_I_TRANSP,     0);
    add_prop(OBJ_M_NO_SELL,     "@@check_sell@@");
    add_prop(OBJ_I_VALUE,       50+random(11));

    seteuid(getuid());
}

mixed
check_sell()
{
    if (sizeof(all_inventory(TO)))
        return "There are things in the "+short()+". Empty it first.\n";
    else
        return 0;
}

string
short(object for_obj)
{
    if (query_prop(CONT_I_CLOSED))
        return "closed " + ::real_short(for_obj);
    else
        return "open " + ::real_short(for_obj);
}

public void
fill_pouch()
{
    object gem;
  
        gem = RANDOM_GEM(-1);
        gem->move(this_object());    
  
    if (random(5)) 
    {
        gem = RANDOM_GEM(GEM_EXTREMELY_RARE);
        gem->move(this_object());    
    }
    add_prop(CONT_I_CLOSED, 1);
}

