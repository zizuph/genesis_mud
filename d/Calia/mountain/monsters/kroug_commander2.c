/* 
   Kroug commander, the most powerful of krougs in the foothills. There 
   usually won't be more than one of these in the game. 

   Coded by Maniac. 
 
   History: 
        28/1/2001        polearm of darkness added     Maniac 
          3/11/00        set_exp_factor                Maniac
          11/8/95        Created                       Maniac
*/

#pragma save_binary

inherit "/d/Calia/std/kroug";

#include "/d/Calia/sys/kroug.h"
#include <money.h>
#include <filter_funs.h>
#include <composite.h> 
#include <macros.h>
#include "monster.h"

#define LOG_COMMANDER_DISARMS


void
arm_me()
{
    object heap;
    object weapon;
    object armour;

    seteuid(getuid()); 
    heap = MONEY_MAKE_GC(10); 
    heap->move(this_object()); 

    armour = clone_object(MOUNTAIN_ARMOURS + "steel_chainmail");
    armour->move(this_object());
    command("wear " + OB_NAME(armour));

    armour = clone_object(MOUNTAIN_ARMOURS + "long_curve_helm"); 
    armour->move(this_object()); 
    armour->set_up_desc("platinum"); 
    command("wear " + OB_NAME(armour)); 

    if (random(2)) { 
        weapon = clone_object(PALACE_WEAPONS + "sword_of_darkness"); 
        weapon->move(this_object()); 
        command("wield " + OB_NAME(weapon)); 
    } 
    else { 
        weapon = clone_object(PALACE_WEAPONS + "polearm_of_darkness"); 
        weapon->move(this_object()); 
        command("wield " + OB_NAME(weapon)); 
    } 
} 


#ifdef LOG_COMMANDER_DISARMS
void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to); 
    if (ob->id("_calia_weapon_of_darkness") && query_hp() != 0) {
        log_file("kroug_commander_disarmed", 
               ctime(time()) + ". Present were: " + 
               COMPOSITE_WORDS(map(FILTER_PLAYERS(all_inventory(environment())),
                               &->query_real_name())) +
               ", weapon of darkness moved to " + (interactive(to) ? 
                                         to->query_real_name() :
                                         to->short(this_object())) + 
               ", this_player() was " + 
               this_player()->query_real_name() + ".\n"); 
    }
}
#endif


/* Short and sweet :) */ 
void 
create_kroug() 
{ 
    set_kroug_type(KROUG_ULTRA); 
    set_hp(query_max_hp()); 
    set_exp_factor(130);  /* disarming and weapon breaking abilities,
                             protected by fellow krougs (move in front :) 
                           */ 
}
