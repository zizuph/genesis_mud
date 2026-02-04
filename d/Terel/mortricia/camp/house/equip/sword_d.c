/* A sword. Mortricia 920729 */
inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>
#include "/d/Terel/common/terel_std_rec.h"
#define BSN(xx) break_string(xx+"\n", 70)

void
create_weapon()
{
    set_name("sword");
    set_short("long steel sword");
    set_long(BSN(
	"It is a long steel sword. It is sharp."
    ));
    set_adj("steel");
    add_adj("long");
    add_prop(OBJ_I_WEIGHT, 6000);
    add_prop(OBJ_I_VOLUME, 800);
    set_hit(30);
    set_pen(30);
    set_wt(W_SWORD);
    set_dt(W_SLASH | W_IMPALE);
    set_hands(W_ANYH);
}
