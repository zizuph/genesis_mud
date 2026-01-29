// 
// katana.c
// 
// RoleMaster's Oriental Companion says:
//    One of the most widely used blades in the Orient due to the
// presence of the Samurai. The Katana is one of the two swords
// to carry along with the Wakisashi. The Katana is a one-handed
// blade designed to be both slashing or impaling weapon. It measures
// between three to four feet in length and is built with an unusually
// long hilt, as if a two-handed weapon.
//
// Also, it says to use the Broadsword table with an additional
// 5 % add to armour classes up to and including chain-mails.


#include "defs.h"
#include <stdproperties.h>
#include <filter_funs.h>
#include <cmdparse.h>
#include <ss_types.h>
#include <formulas.h>
#include <wa_types.h>
#include <macros.h>

inherit THIS_DIR + "wakizashi";

CONSTRUCT_WEAPON
{
    set_name("katana");
    add_name("sword");
    add_adj(({"long","deep-cleaving", "cleaving", "oriental"}));
    set_short("deep-cleaving katana");
    set_long("Ah! This is a Katana, an Oriental slightly curved sword "+
	     "with an unusual long hilt to provide better handling. The "+
	     "edge seems quite sharp, and you would guess that it is "+
	     "quite useful against not so heavily armed opponents.\n");

    set_wt(W_SWORD);
    set_hit(29);  // Easier to hit with than the Broadsword.
    set_pen(26);  // Though it is lighter.
    set_dt(W_SLASH | W_IMPALE);
    set_hands(W_RIGHT);
}

