/*   chest.c
 *
 *  A small chest, containing a small treasure.
 *
 * Baldacin@Genesis, Sep 2003
 */
 
inherit "/std/receptacle";
#include "../ldefs.h"
#include "/d/Genesis/gems/gem.h"
#include <stdproperties.h>
#include <macros.h>
#include <money.h>
 
void
create_receptacle() 
{
    object gem, gem2;
    set_name("chest");
    add_name("c_chest");
    set_adj("iron");
    set_long("It is an average sized iron chest, sternly "+
        "attached to the floor.\n");
 
    add_prop(CONT_I_WEIGHT,     2000);
    add_prop(CONT_I_MAX_WEIGHT, 7000);
    add_prop(CONT_I_VOLUME,     2000);
    add_prop(CONT_I_MAX_VOLUME, 7000);
    add_prop(CONT_I_RIGID,  1);
    add_prop(CONT_I_CLOSED, 1);
    add_prop(OBJ_I_NO_GET,  1);
    
    set_cf(this_object());
    
    setuid();
    seteuid(getuid());
    MONEY_MAKE_CC(1000 + random(40))->move(TO, 1);
    MONEY_MAKE_SC(150 + random(40))->move(TO, 1);
    gem  = RANDOM_GEM_BY_RARITY(GEM_RARE);
    gem2 = RANDOM_GEM_BY_RARITY(GEM_SOMEWHAT_COMMON);
    gem->move(TO, 1);
    gem2->move(TO, 1);
}
