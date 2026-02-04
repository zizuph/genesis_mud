/*
 * cave2.c
 *
 * A small cave below the Legion of Darkness quarters.
 */

#include "/d/Terel/include/Terel.h"
inherit STDROOM;

#include <cmdparse.h>
#include <poison_types.h>
#include <ss_types.h>

#include "/d/Terel/LoD/dungeon/quest.h"
#include "/d/Terel/include/quest_bits.h"

#define DUNG_DIR     (LOD_DIR + "dungeon/")
#define BACK         (DUNG_DIR + "cave")
#define CRYSTAL      (LOD_DIR + "obj/crystal")
#define GUARDIAN     (LOD_DIR + "monster/guardian")
#define POISON       ("/std/poison_effect")
#define NO_OF_DRINKS "_no_of_sparkling_drinks"

int aid = 0;
object guardian, crystal;

public void
reset_room()
{
    seteuid(getuid());
    
    if (!crystal)
    {
        crystal = clone_object(CRYSTAL);
        crystal->move(TO);
    }
}

public void
bring_forth_guardian(object drinker)
{
    if (guardian || !drinker)
        return;
        
    seteuid(getuid());
    guardian = clone_object(GUARDIAN);
    guardian->set_caller(drinker);
    guardian->move_living("M", TO);
    tell_room(TO, QCTNAME(guardian) + " materializes next to the pool.\n",
              guardian);
    
    if (ENV(drinker) == TO)
    {
        guardian->command("greet " + drinker->query_real_name());
        guardian->command("introduce myself to " +
                        drinker->query_real_name());
    }
}

public void
guardian_leaves()
{
    aid = 0;
    if (!guardian)
        return;
    tell_room(TO, QCTNAME(guardian) + " vanishes.\n", guardian);
    guardian->remove_object();
}

public string
do_drink_water()
{
    int n = TP->query_prop(NO_OF_DRINKS);
    object poison;
    
    if (!CAN_SEE_IN_ROOM(TP))
        return "Drink water?\n";
    
    write("You bend down and drink some water from the pool.\n");
    say(QCTNAME(TP) + " bends down and drink some water " +
        "from the pool.\n");
    if (n == 0)
    {
        TP->heal_hp(300);
        TP->add_prop(NO_OF_DRINKS, 1);
        if (!TP->test_bit("Terel", QUEST_DUNGEON_GROUP, QUEST_DUNGEON_BIT))
            set_alarm(4.0, 0.0, &bring_forth_guardian(TP));
        return "It has a strange but refreshing taste.\n";
    }
    else if (n == 1)
    {
        TP->change_prop(NO_OF_DRINKS, 2);
        if (guardian && guardian->query_caller() == TP)
        {
            guardian->command("frown at " + TP->query_real_name());
        }
        return "Strange, the water has a somewhat bitter taste now.\n";
    }
    else
    {
        seteuid(getuid());
        poison = clone_object(POISON);
        poison->set_time(500 + random(200));
        poison->set_interval(30 + random(5));
        poison->set_strength(60 + n*random(5));
        poison->add_prop("water_poison", 1);
        poison->set_damage(({POISON_STAT, SS_CON, POISON_HP, 125 + n*20}));
        poison->move(TP);
        poison->start_poison();
        TP->change_prop(NO_OF_DRINKS, n + 1);
        if (guardian && guardian->query_caller() == TP)
        {
            guardian->command("sigh");
            aid = set_alarm(3.0, 0.0, guardian_leaves);
        }
        return "The water has a very bitter taste now.\n";
    }
}

public string
my_pool()
{
    if (!TP->query_prop(NO_OF_DRINKS))
        return "The clear pool sparkles brightly in the light. In " +
               "looks very refreshing.\n";
    else
        return "The water in the pool is still clear but does not " +
               "sparkle anylonger.\n";
}

public void
create_room()
{
    ::create_room();
    
    set_short("small cave");
    set_long("You are down in a smaller cave. This cave is very " +
             "beautiful, the walls reflect the light and create " +
             "a delicate illumination of the cave. A small pool " +
             "of clear water rests quietly in the rear part " +
             "of the cave.\n");
             
    add_item(({"pool", "water"}), "@@my_pool");
    add_cmd_item(({"pool", "water"}), "enter", "It's too small.\n");
    add_cmd_item(({"pool", "water"}), "drink", "@@do_drink_water");
             
    add_item(({"wall", "walls"}), "The walls are all covered with " +
             "tiny crystals. As the crystals reflect the light they " +
             "illuminate the cave in a very magical way.\n");
    
    add_prop(ROOM_I_LIGHT, 0);
    
    reset_room();
}

public int
do_fill(string str)
{
    object *ob, goblet;
    
    if (!str || !CAN_SEE_IN_ROOM(TP))
        return 0;
        
    notify_fail("Fill what with what?\n");
    if (!parse_command(str, all_inventory(TP), "%i 'with' 'water'", ob))
        return 0;
        
    ob = NORMAL_ACCESS(ob, 0, 0);
    if (sizeof(ob) != 1)
        return 0;
        
    if (!ob[0]->id(DQ_GOBLET))
    {
        write("That cannot be filled with the sparkling water.\n");
        return 1;
    }
    else
        goblet = ob[0];
    
    switch (goblet->fill_it_with_water(TP)) {
        case 0:     /* Not solved the quest */
            write("You try to fill the " + goblet->short() + " with " +
                  "sparkling water from the pool. Somehow, though, the " +
                  "water seem to disappear as quickly as you are " +
                  "filling it.\n");
            say(QCTNAME(TP) + " does not succeed to fill " +
                TP->query_possessive() + " " + goblet->short() +
                " with water from the pool.\n");
            break;
        case 1:     /* Solved the quest, goblet not full */
            write("You fill the " + goblet->short() +
                  " with some sparkling water from the pool.\n");
            say(QCTNAME(TP) + " fills " + TP->query_possessive() + " " +
                goblet->short() + " with some sparkling water from " +
                "the pool.\n");
            break;
        case 2:     /* Solved the quest, goblet already full */
            write("You cannot do that. Your " + goblet->short() +
                  "is already full with water from the pool.\n");
            break;
    }
    
    return 1;
}

public void
init()
{
    ::init();
    add_action(do_fill, "fill");
}

public void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);
    
    if (!ob || !living(ob) || !guardian || aid)
        return;
        
    if (guardian->query_caller() == ob)
        aid = set_alarm(10.0, 0.0, guardian_leaves);
}
