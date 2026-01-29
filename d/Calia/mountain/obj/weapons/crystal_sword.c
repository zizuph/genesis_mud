inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <formulas.h>
#include <macros.h>
#include <cmdparse.h>
#include <language.h>

void create_weapon()
{
    set_name("sword");
    set_pname("swords");
    set_short("crystal sword");
    set_pshort("crystal swords");
    set_long("The sword appears to be forged from crystal "+
	"hard and sharp as diamond.\n");
    likely_dull = random(35);
    likely_corr = random(35);
    likely_break = random(35);
    set_adj("crystal");
    set_hit(35);
    set_pen(35);
    set_wt(W_SWORD);
    set_dt(W_IMPALE | W_SLASH);
    set_wf(this_object());
    set_hands(W_RIGHT);
    add_prop(OBJ_I_VALUE,
	F_VALUE_WEAPON(random(20) + 25, random(20) + 25) + random(20) - 10);
    add_prop(OBJ_I_WEIGHT, 15);
}
