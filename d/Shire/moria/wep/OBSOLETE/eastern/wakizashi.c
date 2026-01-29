//
// wakizashi.c
//
// According to RoleMaster, a Wakisashi is the Oriental equivalent of
// a western shortsword. It measures two feet long, an has a curved
// blade like the Katana. This is the most common weapon in the Orient,
// even more so than the Katana. Even the lowest ranked members of
// society are permitted to carry these weapons, however, only the
// Samurai and Kuge are permitted to carry them in conjunction with
// the Katana.
//
// Another thing about this weapon, is that it is *more* effective
// against non-plate armours, than the shortsword. Thus I will give
// it a 5% better weapon class against such attacks.


#include "defs.h"
#include <stdproperties.h>
#include <filter_funs.h>
#include <cmdparse.h>
#include <ss_types.h>
#include <formulas.h>
#include <wa_types.h>
#include <macros.h>

inherit BASE_WEAPON;

CONSTRUCT_WEAPON
{
    set_name("wakizashi");
    add_name("sword");
    add_adj(({"short","oriental"}));
    set_short("beautifully ornamented wakizashi");
    set_long("You are examining an oriental short sword, a Wakizashi, "+
	     "a 60 cm (2') long curved sword with a dangerously sharp " +
	     "edge. You would recon that it is poor against heavy "+
	     "platemails, however. Against more unarmoured spots, it "+
	     "would yield better performance, if only you know how to "+
	     "handle this sword.\n");
    
    set_wt(W_SWORD);
    set_hit(23);        // Easy handling.
    set_pen(20);        // Slashes easily, but is not that powerful. 
    set_dt(W_SLASH);
    set_hands(W_ANYH);
}

//
// If ac on a spot is > 20 then the effect is normal, or else
// an extra damage of 5% is added.
//
int
query_extra_dam(int aid, string hdesc, int phurt, object enemy, int dt)
{
    object *arms = get_armours_protecting(hdesc, enemy);
    mixed *hdata = get_hitloc_data(hdesc, enemy);
    int i, sum=0;

#ifdef _DEBUG
#  define TELLME find_player("rogon")->catch_msg("Good slash!\n")
#else
#  define TELLME 0
#endif

#define totac hdata[0][1]
#define hid   hdata[4]
 
    if (!sizeof(arms))
	if (totac > 20)
	    return 0;
        else
	    return TELLME, 5;

    for (i=0; i<sizeof(arms); i++, sum += arms[i]->query_ac(hid))
	if (arms[i]->query_ac(hid) > 20)
	    return 0;
    
    if (totac > sum + 20) // Skin ac == totac - sum > 20.
	return 0;
    else
	return TELLME, 5;

#undef TELLME
#undef totac
#undef hid
}





