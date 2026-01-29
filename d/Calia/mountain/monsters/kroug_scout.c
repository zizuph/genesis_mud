/* 
    A kroug scout, basically a regular kroug who sneaks around in Calian 
    territory trying to gather information. These are less bold than the
    krougs on the foothills, and are unarmoured. They are however very well
    trained.

    Coded by Maniac 15.9.95, modified 19.9.95, 19/2/96
*/

#pragma save_binary

inherit "/d/Calia/std/kroug";
#include "/d/Calia/sys/kroug.h"
#include <ss_types.h>
#include <money.h>
#include "monster.h"

void
arm_me()
{
   object heap;
   object weapon;

    heap = MONEY_MAKE_SC(random(15) + 10);
    heap->move(this_object());

    switch (random(4)) {
        case 0 : weapon = clone_object(MOUNTAIN_WEAPONS + "iron_flail");
                 weapon->move(this_object());
                 command("wield flail");
                 return;
                 break;
        case 1 : 
                 weapon = clone_object(MOUNTAIN_WEAPONS + "red_gladius");
                 weapon->move(this_object());
                 command("wield gladius");
                 weapon = clone_object(MOUNTAIN_WEAPONS + "red_gladius");
                 weapon->move(this_object());
                 command("wield gladius");
                 return;
                 break;
        case 2 : 
                 weapon = clone_object(MOUNTAIN_WEAPONS + "bronze_handaxe");
                 weapon->move(this_object()); 
                 command("wield handaxe");
                 weapon = clone_object(MOUNTAIN_WEAPONS + "bronze_handaxe");
                 weapon->move(this_object()); 
                 command("wield handaxe");
                 return;
                 break;
        default : 
                weapon = clone_object(MOUNTAIN_WEAPONS + "black_glaive");
                weapon->move(this_object()); 
                command("wield glaive");
                return;
                break;
    }

}


void
create_kroug()
{
    set_kroug_type(KROUG_REGULAR);
    remove_name(query_names());
    set_name("kroug");
    add_name("scout");
    set_long("A scout kroug, trained to be stealthy and quiet, which " +
             "are not traits one would normally associate with krougs. " +
             "Krougs such as these can usually handle their weapons " +
             "especially well, because of the occasional need to " +
             "carry out assassinations. " +
             "It has been sent here to gain as much information as it can " +
             "about the strength of pro-Calian forces in and around Calia.\n"); 
    set_skill(SS_WEP_CLUB, 80);
    set_skill(SS_WEP_POLEARM, 80);
    set_skill(SS_WEP_SWORD, 80);
    set_skill(SS_WEP_AXE, 80);
    set_skill(SS_WEP_KNIFE, 80);
    set_skill(SS_HIDE, random(20)+50);
    set_skill(SS_SNEAK, random(20)+50);

    set_act_time(2);
    add_act("sneak north");
    add_act("sneak northeast");
    add_act("sneak northwest");
    add_act("sneak east");
    add_act("sneak west");
    add_act("sneak south");
    add_act("sneak southest");
    add_act("sneak southwest");
}
