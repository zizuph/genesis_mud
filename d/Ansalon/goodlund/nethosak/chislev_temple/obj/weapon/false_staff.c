/*
 *  false_staff.c
 *
 *  As the name would suggest, this is the false staff
 *  cloned when the 'chislev_staff' is uniquely limited.
 *
 *  Created by Carnak, January 2016
 */
#pragma save_binary

inherit "/std/weapon";
inherit "/lib/keep";

#include <wa_types.h>
#include <stdproperties.h>

void
create_weapon()
{
    setuid();
    seteuid(getuid());
	
    set_name("staff");
    add_name("weapon");
    set_pname("staves");
    add_pname("weapons");
    
    set_adj("gnarled");
    add_adj("wooden");

    set_short("gnarled wooden staff");
    set_pshort("gnarled wooden staves");
    
    set_long("This is a thick gnarled wooden pole, the shaft is "+
    "riddled with budding branches growing small wild blossoms.\n");
    
    set_default_weapon(35 + random(2),
                       35 + random(2),
                       W_POLEARM,
                       W_BLUDGEON,
                       W_BOTH);
    
    set_keep(1);
    set_likely_corr(0);
    set_likely_dull(0);
	
    add_prop(OBJ_I_VOLUME, 5000+random(500));
    add_prop(OBJ_I_WEIGHT, 7000+random(500));
    
    set_wf(this_object());
}

mixed
wield(object what)
{
    if (wielder->query_skill(W_CLUB) >
        wielder->query_skill(W_POLEARM))
    {
        set_wt(W_CLUB);		
    }
    else
    {
        set_wt(W_POLEARM);
    }
}