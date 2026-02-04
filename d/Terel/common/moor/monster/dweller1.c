/*
 * A tomb dweller
 * based on the LoD guard and the monsters in Mort.'s haunted house
 *
 * Updated by Lilith Jan 2022
 *   Moved from Sorgum's dir to the Moor dir
 *   Npc has stat based special attack. 
 *   See the dweller_base.c for more details. 
 */


#include "/d/Terel/include/Terel.h"
#include "../local.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <money.h>

inherit MOBDIR +"dweller_base";
#define BASE_SIZE   70

int level = 1;
int berzerked = 0;

/* call the berserk in the dweller_base file */
void
go_berzerk()
{
	 berzerked = 1;
     ::go_berzerk();
}

/* call the dress_me in the dweller_base file */
void
dress_me()
{
    seteuid(getuid(this_object()));

    set_dweller_level(1);
    MONEY_MAKE_SC(random(10)) -> move(TO);  
	
	if (random(3) == 0)
	   clone_object(OBJDIR +"dw_knife1")->move(TO);

    ::dress_me();
}
    
void	
create_monster()
{
    /* configure from the dweller_base.c file */
    ::create_monster();

    default_config_npc(random(20) + BASE_SIZE);
    set_stat_extra(SS_DIS, 100);
	
    set_short("small tomb dweller");
    add_adj("small");
    set_skill(SS_BLIND_COMBAT, 50);	
    set_skill(SS_UNARM_COMBAT, 50);
    set_skill(SS_PARRY,        50);	
    set_skill(SS_DEFENCE,      50);
    set_skill(SS_WEP_SWORD,    50);
	set_skill(SS_WEP_KNIFE,    50);
 
    set_long(query_long() +"\nIt appears to be "+ query_exp_title()+
	    " in size. \n");
		
    refresh_living();
	dress_me();
}

	
public int
special_attack(object victim)
{

    if (ENV(victim) != ENV(TO) || victim->query_ghost())
    {
     	TO->stop_fight(victim);
	    return 1;
    }

    // 33% chance of a special attack.
    if (random(3))
	return 0;

    if ((TO->query_hp() < (TO->query_max_hp() / 2)) && (!berzerked))
    {
        go_berzerk();
		return 0;
    }		
    else
    {
        command("roar");		
	    ::do_scratch(victim);
	}
    return 0;

}

