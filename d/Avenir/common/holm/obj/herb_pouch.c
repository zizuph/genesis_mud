//  
// creator(s):      Lilith 1/20/97
// last update:     
// purpose: 
// note:       
// bug(s):
// to-do:


inherit "/std/receptacle";
inherit "/lib/keep";
#include "../holm.h"

string *herbs = HERB_MASTER->query_herbs( ({"jungle", "boreal"}) );

public void
create_container()
{
    set_name("pouch");
    add_name("_Herb_pouch_");
    set_pname("pouches");
    set_adj( ({ "small","leather" }) );
    set_long("This is a small leather pouch, used to hold herbs and"+
             " other small items.\n");
    set_keep(1);
    add_prop(CONT_I_IN,            1);
    add_prop(CONT_I_WEIGHT,      300);         
    add_prop(CONT_I_VOLUME,      500);          
    add_prop(CONT_I_MAX_VOLUME, 5000);       
    add_prop(CONT_I_MAX_WEIGHT, 5000);      
    add_prop(CONT_I_CLOSED,        1);
    add_prop(CONT_I_RIGID,         0);
    add_prop(CONT_I_TRANSP,        0);
    add_prop(OBJ_M_NO_SELL, "@@check_sell@@");
    add_prop(OBJ_I_VALUE,   50+random(11));

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

void
fill_pouch()
{
    object herb;
    int i;

    herb = clone_object("/d/Avenir/common/herbs/carlith");
    herb->move(TO, 1);
    herb = clone_object(GET_ONE(herbs));
    herb->move(TO, 1);
    herb = clone_object(GET_ONE(herbs));
    herb->move(TO, 1);

    i = random(5);
    if (i == 4)
    {   
        herb = clone_object(GET_ONE(herbs));
        herb->move(TO, 1);
    }
}

