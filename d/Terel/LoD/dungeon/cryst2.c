/*
 * cryst2.c
 *
 * Inside the quest crystal.  Mortricia June 1996
 */

#include "/d/Terel/include/Terel.h"
inherit STDROOM;

#include <ss_types.h>

#include "/d/Terel/LoD/dungeon/quest.h"
#include "/d/Terel/include/quest_bits.h"

#define DUNG_DIR     (LOD_DIR + "dungeon/")
#define WOLF         (LOD_DIR + "monster/qwolf")
#define BACK         (DUNG_DIR + "cryst1")
#define FURTHER      (DUNG_DIR + "cryst3")

object wolf;

public void
reset_room()
{
    object *e;
    
    ::reset_room();
    
    if (!wolf)
    {
        wolf = clone_object(WOLF);
        wolf->move_living("leaves", TO);
    }
    else if (!wolf->query_attack())
    {
        e = (object *)(wolf->query_enemy(-1)) - ({ 0 });
        if (sizeof(e))
        {
            wolf->stop_fight(e);
            e->stop_fight(wolf);
        }
    }
}

public int
check_worn(string qarmour)
{
    object *ob, qarm = present(qarmour, TP);
    int i;
    
    if (!qarm || qarm->query_worn() != TP)
        return 0;
    
    ob = all_inventory(TP) - ({ qarm });
    
    for (i=0; i<sizeof(ob); i++)
        if (ob[i]->query_worn()) return 0;
        
    return 1;
}

public int
check_wolf()
{
    if (!wolf || !present(wolf))
        return 0;
    
    if (TP->query_attack() == wolf || wolf->query_attack() == TP)
        return 1;
        
    return 0;
}

public int
check_further()
{
    if (!wolf || !present(wolf))
        return 0;
       
    if (check_worn(DQ_WOLF_COAT) && !check_wolf())
    {
        wolf->command("emote sniffs suspiciously.");
        return 0;
    }
    
    TP->catch_msg(QCTNAME(wolf) + " moves in front of you and blocks " +
                  "the way.\n");
    say(QCTNAME(wolf) + " moves in front of " + QTNAME(TP) + ".\n");
    return 1;
}

public void
create_room()
{
    ::create_room();
    
    set_short("strange place");
    set_long("You are in a very strange place. Despite it is very bright " +
             "here you cannot see very far. To the northeast it looks " +
             "even brighter.\n");
    
    add_prop(ROOM_I_LIGHT, 2);
    add_prop(ROOM_M_NO_TELEPORT, 1);
    
    add_exit(FURTHER, "northeast", "@@check_further");
    add_exit(BACK, "west", 0);
    
    set_noshow_obvious(1);
        
    reset_room();
}
