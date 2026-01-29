/* Solamnian cowboy
 * Aridor 08/99
 */

#include "../local.h"
#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <options.h>

inherit SOLAMNIAN

void
create_solamnian()
{
    add_name(({"villager","man","huntsman","hunter"}));
    add_pname(({"men","villagers","huntsmen","hunters"}));
    set_gender(0);
    set_extra_long("This man seems to be a huntsman, a respected member of " +
       "the community who catches wild game and protects the flocks from " +
       "predators with his handy bow.\n");
    default_config_npc(random(40) + 50);
    set_skill(SS_WEP_MISSILE, 70);
    set_skill(SS_WEP_POLEARM, 43);
    set_skill(SS_DEFENSE, 41);
    set_skill(SS_PARRY, 37);
    set_skill(SS_AWARENESS, 43);

    set_act_time(3 + random(2));
    add_act("@@check_for_arrows");

    set_give_quest(0);
}

void
arm_me()
{
    clone_object(TDIR + "obj/hunting_bow")->move(TO,1);
    clone_object(TDIR + "obj/hunting_arrow")->move(TO,1);
    clone_object(TDIR + "obj/hunting_arrow")->move(TO,1);
    clone_object(TDIR + "obj/hunting_arrow")->move(TO,1);
    clone_object(TDIR + "obj/hunting_arrow")->move(TO,1);
    clone_object(TDIR + "obj/hunting_arrow")->move(TO,1);
    clone_object(TDIR + "obj/hunting_arrow")->move(TO,1);
    clone_object(TDIR + "obj/hunting_arrow")->move(TO,1);
    clone_object(TDIR + "obj/hunting_arrow")->move(TO,1);
    clone_object(TDIR + "obj/hunting_arrow")->move(TO,1);
    clone_object(TDIR + "obj/hunting_arrow")->move(TO,1);
    clone_object(TDIR + "obj/hunting_arrow")->move(TO,1);
    clone_object(TDIR + "obj/hunting_arrow")->move(TO,1);
    clone_object(CLOAK)->move(TO,1);
    clone_object(JACKET)->move(TO,1);
    clone_object(PANTS)->move(TO,1);
    ::arm_me();
}

string
query_nonmet_name()
{
    return ::query_nonmet_name() + " huntsman";
}

void
check_for_arrows()
{
    object weapon, *wp;
    object *items;
    int    i, arrow, size;
    
    wp = query_weapon(-1);
    
    if ( sizeof(wp) )
        weapon = wp[0];
        
    if ( weapon->query_wt == W_MISSILE )
    {
        items = deep_inventory(TO);
        size = sizeof(items);
        
        for ( i = 0; i < size; i++ )
        {
            if ( (items[i])->id("arrow") )
                arrow++;
        }
        
        if ( arrow <= 10 )
        {
            command("emote puts some more arrows into his quiver.");
            clone_object("/d/Krynn/solamn/road/obj/hunting_arrow")->move(TO, 1);
            arrow += 12;
        }    
        else
        {
            command("emote inspects his quiver for arrows.");        
            command("take arrows");
            command("put arrows in quiver");
        }
    }    
}

int 
query_option(int opt)
{
    if ( opt == OPT_UNARMED_OFF )
       return 1;
}


