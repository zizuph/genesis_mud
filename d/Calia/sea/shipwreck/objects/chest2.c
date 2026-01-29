/*   chest2.c
 *
 *  A small chest located in the lower level storage room.
 *
 * Baldacin@Genesis, Aug 2003
 */
 
inherit "/std/receptacle";
#include "defs.h"
#include "/sys/stdproperties.h";
#include "/d/Genesis/gems/gem.h"
#include <macros.h>
#include <money.h>
 
void create_receptacle() 
{
    object gem, gem2;
    set_name("chest");
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
    MONEY_MAKE_CC(250 + random(40))->move(TO, 1);
    MONEY_MAKE_SC(150 + random(40))->move(TO, 1);
    gem  = RANDOM_GEM_BY_RARITY(GEM_RARE);
    gem2 = RANDOM_GEM_BY_RARITY(GEM_SOMEWHAT_COMMON);
    gem->move(TO, 1);
    gem2->move(TO, 1);
}

int
open(object ob)
{
    object lacedon = present("shipwreck_lacedon", environment());   

    if (ob != TO || !objectp(lacedon))
        return 0;

    lacedon->command("emote hissess: My treasure! I'll eat you alive!");

    if (!objectp(lacedon->query_attack()))
        lacedon->command("kill " + OB_NAME(TP));
        
    return 3;
}