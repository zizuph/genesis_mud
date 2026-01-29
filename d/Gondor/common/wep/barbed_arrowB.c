/*
 *Special stun arrow for haradrim greatbow
 *Altrus, July 2005
*/

inherit "/std/arrow";
#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <formulas.h>
#include "/d/Gondor/defs.h"

public void
create_arrow()
{
    set_adj("barbed grey-feathered");
    add_name("_arrow_for_stunning");
    set_projectile_id("gondor_grey_feathered_arrow");
    set_hit(45 + random(10));
    set_pen(50 + random(10));
}

string
get_projectile_long(string str, object for_obj, int num)
{
    return ((num == 1) ? "This arrow is" : "These arrows are") + " somewhat heavier than normal. Tipped with " + ((num == 1) ? "a nasty looking, barbed steel head" : "nasty looking, barbed steel heads") + " the " + ((num == 1) ? "arrow looks" : "arrows look") + " like " + ((num == 1) ? "it" : "they") + "might severely hurt if shot properly. " + ((num==1) ? "It" : "They") + " might even knock someone to the ground, if shot hard enough.\n";
}
