// 
// no-dachi.c
// 
// RoleMaster's Oriental Companion says:
//   The No-Dachi [noo-datch] is the Oriental cousin of the two-handed
// sword. It measures five to siz feet in length and can only be wielded
// two handed. Due to the restrictions of use it is not a popular weapon,
// but it is effective.
//   Rolemaster consideres this weapon a 2H sword +5.

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
    set_name("no-dachi");
    add_name("sword");
    add_adj(({"heavy", "two-handed", "oriental"}));
    set_short("heavy no-dachi");
    set_long("This is a No-Dachi, an Oriental slightly curved two-handed "+
	     "sword with good handling. It is 150 cm long, thus it must "+
	     "be wielded by both your hands, but you would think it was "+
	     "quite effective considering it's nice edge and heavy blow.\n");

    set_wt(W_SWORD);
    set_hit(37);  // A normal 2h sword is 32/32.
    set_pen(37);  // +5 on both for these fine oriental weapons.
    set_dt(W_SLASH | W_IMPALE);
    set_hands(W_BOTH);
}

