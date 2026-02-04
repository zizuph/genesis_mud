/*
 * cryst1.c
 *
 * Inside the quest crystal.
 */

#include "/d/Terel/include/Terel.h"
inherit STDROOM;

#include <ss_types.h>

#include "/d/Terel/LoD/dungeon/quest.h"
#include "/d/Terel/include/quest_bits.h"

#define DUNG_DIR     (LOD_DIR + "dungeon/")
#define TROLL        (LOD_DIR + "monster/troll")
#define CLUB         (LOD_DIR + "weapon/tclub")
#define BACK         (DUNG_DIR + "cave2")
#define FURTHER      (DUNG_DIR + "cryst2")

object troll, club;
int confused = 0;

public void
reset_room()
{
    ::reset_room();
    
    if (!troll)
    {
        troll = clone_object(TROLL);
        troll->move_living("leaves", TO);
        club = clone_object(CLUB);
        club->move(troll);
        troll->command("wield club");
    }
}

public void
unconfuse()
{
    if (troll)
        troll->command("shrug");
    confused = 0;
}

public int
check_further()
{
    object helmet = present(DQ_OGRE_HELMET, TP);
    
    if (!troll || !present(troll))
        return 0;
       
    if (confused)
    {
        TP->catch_msg(QCTNAME(troll) + " is very confused and lets you pass.\n");
        return 0;
    }
     
    TP->catch_msg(QCTNAME(troll) + " stops you from going there with a " +
                  "forceful hit on your head with his " +
                  club->short() + ".\n");
    say(QCTNAME(troll) + " stops " + QTNAME(TP) + " from going " +
        "east by hitting " + TP->query_possessive() + " head with his " +
        club->short() + ".\n");
    if (helmet && helmet->query_worn() == TP)
    {
       write("Luckily, your " + helmet->short() + " absorbs the blow.\n");
       if (!confused)
       {
           troll->command("emote looks very confused.");
           confused = 1;
           set_alarm(5.0, 0.0, unconfuse);
       }
    }
    else
    {
        write("Ouch. That hurt!\n");
        troll->command("grin evilly");
        TP->reduce_hit_point(500);
        if (TP->query_hp() <= 0)
            TP->do_die(troll);
    }
    return 1;
}

public void
create_room()
{
    ::create_room();
    
    set_short("strange place");
    set_long("You are in a very strange place. Despite it is bright " +
             "here you cannot see very far. To the west you notice " +
             "a somewhat darker spot, and to the east it looks even " +
             "brighter.\n");
                          
    add_item(({"spot", "dark spot"}), "It looks as if you can enter it.\n");
    
    add_prop(ROOM_I_LIGHT, 1);
    add_prop(ROOM_M_NO_TELEPORT, 1);
    
    add_exit(FURTHER, "east", "@@check_further");
    
    set_noshow_obvious(1);
        
    reset_room();
}

public int
do_enter(string str)
{
    notify_fail("Enter what?\n");
    
    if (!str)
        return 0;
        
    if (str != "spot" && str != "dark spot")
        return 0;
        
    write("You enter the dark spot.\n");
    say(QCTNAME(TP) + " disappears into a dark spot!\n");
    TP->move_living("M", BACK);
    tell_room(ETP, QCTNAME(TP) + " emerges from the crystal!\n", TP);
    return 1;
}

public void
init()
{
    ::init();
    add_action(do_enter, "enter");
}
