/* Poison Ivy by Jeremiah, Rastlin and Teth, March 4,96
 * Example of cloning a 'contact' poison.
 * Poison file found in the herb directory, ivyp.c
 */

#pragma save_binary

inherit "/std/herb";

#include <herb.h>
#include <macros.h>
#include <wa_types.h>

#include "/d/Krynn/common/defs.h"

#define	IVY_IS_RECOVERED	"ivy_is_recovered"

void
create_herb()
{
    set_name("leaf");
    set_adj(({"oily", "drooping"}));
    set_herb_name("poison ivy");
    set_short("oily drooping leaf");
    set_pshort("oily drooping leaves");
    set_pname(({"leaves", "herbs", }));
    set_ingest_verb("eat");
    set_unid_long(BSN("This is an oily drooping leaf. It was " +
        "probably picked from a tri-leaved herb somewhere."));
    set_id_long(BSN("This is a leaf of poison ivy, an herb found " +
        "in temperate areas, nearly everywhere. Poison ivy (Rhus radicans) " +
        "is a nuisance herb that causes people to get itchy all over for a " + 
        "long period of time. It may be safe to handle it with protection " +
        "however. Its oily leaves cause a reaction in people's skin. " +
        "It has a three-compound leaf, and white berries. Eating it would " +
        "make you very sick."));
    set_effect(HERB_POISONING,"hp",80);
    set_herb_value(10);
    set_id_diff(5);
    set_find_diff(2);
    set_decay_time(4200);

}


int
hands_protected(object who)
{
    object *worn_armours;

    int    *prot_hit_locs,   /* protected hit locations */
    i, j;

    worn_armours = who->query_armour(-1);

    if (!sizeof(worn_armours))
        return 0;

    for (i = 0; i < sizeof(worn_armours); i++)
    {
        prot_hit_locs = worn_armours[i]->query_slots();

	for (j = 0; j < sizeof(prot_hit_locs); j++)
	  {
                if(prot_hit_locs[j] | (A_R_HAND | A_L_HAND))
		  {
			return 1;
		  }
		continue;
	  }
        continue;
    }

    return 0;
}


void
enter_env(object dest, object old)
{
    object poison;

    if (hands_protected(dest))
    {
        ::enter_env(dest, old);
        return;
    }

    if(!living(dest))
        return;

    if(dest->query_prop(LIVE_I_UNDEAD))
        return;

    if (environment() == dest && living(dest))
    {
	if (query_prop(IVY_IS_RECOVERED))
	{
	    remove_prop(IVY_IS_RECOVERED); 
	    tell_object(dest,
		"You quickly drop the oily drooping leaf " +
                "to avoid a nasty rash.\n");

	    if (move(environment(dest)))
	    {
		move(environment(dest), 1);
	    }
            return;
	}
    }

    {
        if (!present("_krynn_herb_ivy_poison", dest))
        {
            seteuid(getuid());
            poison = clone_object(KRPOISON + "ivyp");
            poison->move(dest);
            poison->start_poison();
        }
    }

    ::enter_env(dest, old);
}

void
leave_env(object old, object dest)
{
    object poison;

    if (!old)
        return ::leave_env(old, dest);

    if (hands_protected(old))
    {
        ::leave_env(old, dest);
        return;
    }

    if(!living(old))
        return;

    if(old->query_prop(LIVE_I_UNDEAD))
        return;
    {
        if (!present("_krynn_herb_ivy_poison", old))
        {
            seteuid(getuid());
            poison = clone_object(KRPOISON + "ivyp");
            poison->move(old);
            poison->start_poison();
        }
    }  
    ::leave_env(old, dest);
}

string  
query_recover() 
{ 
    return MASTER+":"+query_herb_recover(); 
}

void    
init_recover(string arg) 
{ 
    ::init_herb_recover(arg); 
    add_prop(IVY_IS_RECOVERED, 1);
}
