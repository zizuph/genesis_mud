/*
 * prisoner.c
 *
 */

#include "/d/Terel/include/Terel.h"
inherit STDMONSTER;

#include <ss_types.h>
#include <stdproperties.h>

object guard=0;

/*
 * Function name: query_object_list
 * Description:   return list of equipment
 */
public string*
query_object_list()
{
    return ({ });
}

/*
 * Function name: create_monster
 * Description:   Create the monster. (standard)
 */
public void
create_monster()
{
    ::create_monster();
   
    set_name("busty");
    add_name("pit_prisoner");
    set_long("@@my_long");
    set_adj("young");
    add_adj("brown-haired");
    set_race_name("human");
    set_gender(MALE);
    set_alignment(100);

    set_stats(({20, 25, 20, 20, 25, 25}));
    SET_MAX_HP;
    
    set_skill(SS_DEFENCE,      10 + random(11));
    set_skill(SS_UNARM_COMBAT, 10 + random(11));
    set_skill(SS_PARRY,        10 + random(11));
    set_skill(SS_WEP_SWORD,    10 + random(5));
    set_skill(SS_WEP_KNIFE,    10 + random(5));
    set_skill(SS_2H_COMBAT,    10);
    set_skill(SS_BLIND_COMBAT, 10);
    set_skill(SS_AWARENESS,    20);
    
    set_act_time(19);
    add_act("@@my_act");
}

public void
set_guard(object ob)
{
    guard = ob;
}

public string
my_long()
{
    if (guard)
        return "This poor fellow was caught by the Legion. He looks " +
               "very scared.\n";
               
    return "It's a young human. He must have lost his mind completely. " +
           "Otherwise he would not be strolling around in the " +
           "Legion's quarters.\n";
}

public string
my_act()
{
    if (guard)
        return "emote wails loudly.";
        
    return "emote looks as if he wishes to be elsewhere.";
}
