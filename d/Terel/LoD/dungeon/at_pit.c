/*
 * at_pit.c
 *
 */

#include "/d/Terel/include/Terel.h"
inherit LOD_DIR + "dungeon/dungeon_room";

#include <macros.h>
#include <stdproperties.h>
#include <language.h>
#include <ss_types.h>

#define DUNG_DIR   (LOD_DIR + "dungeon/")
#define PIT        (DUNG_DIR + "pit")

#define TPINV      all_inventory(TP)
#define ETPINV     all_inventory(ETP)

object rope = 0;

public string*
query_moving_object_list()
{
    return ({LOD_DIR + "monster/bat2",
             LOD_DIR + "monster/bat2"});
}

public void
create_room()
{
    ::create_room();
    
    set_long(query_long() + "Next to the eastern wall is a large " +
             "hole. West you barely see the bottom of some stairs.\n");
    
    add_item(({"southern wall", "south wall"}), "As you closely look " +
             "at the southern wall you find a small iron ring firmly " +
             "attached to the wall.\n");
    add_item(({"ring", "iron ring"}), "It's a bit rusty but that's all.\n");
    add_item(({"hole", "pit"}), "The pit is pitch black and " +
             "it is impossible to tell how deep it is.\n");
    
    add_exit(DUNG_DIR + "entrance", "west", 0);
    
    reset_room();
}

public int
check_climbing()
{
    if (TP->query_skill(SS_CLIMB) < 15) {
        write("Uhum... You feel that climbing down the rope " +
              "is above your capability.\n");
        say(QCTNAME(TP) + " doesn't dare to climb down the rope.\n");
        return 1;
    }
    return 0;
}

public void
open_down_exit()
{
    add_my_desc(capitalize(LANG_ADDART(rope->short())) +
                ", securely tied to an iron ring in the wall, is " +
                "going down into the pit.\n");
    add_exit(DUNG_DIR + "pit", "down", "@@check_climbing");
    PIT->add_my_desc(capitalize(LANG_ADDART(rope->short())) + 
                     " hangs down from above.\n");
    PIT->add_item("rope", rope->long());
    PIT->add_item(rope->short(), rope->long());
    PIT->add_exit(DUNG_DIR + "at_pit", "up", VBFC_ME("check_climbing"));
}

public void
close_down_exit()
{
    remove_my_desc();
    remove_exit("down");
    PIT->remove_my_desc();
    PIT->remove_item("rope");
    PIT->remove_item(rope->short());
    PIT->remove_exit("up");
}

public void
faint_sound(object ob)
{
    if (ob && ob->query_prop(OBJ_I_WEIGHT) > 100)
        tell_room(this_object(), "You hear a sound from the pit " +
                  "as if the " + ob->short() + " reached the bottom. " +
                  "Maybe the pit isn't bottomless after all?\n");
}

public int
do_throw(string str)
{
    object ob;
    
    notify_fail(capitalize(query_verb()) + " what into what?\n");
    
    if (!parse_command(str, TPINV, "%o 'into' 'pit' / 'hole'", ob))
        return 0;
    if (ob->query_prop(OBJ_M_NO_DROP) || !CAN_SEE(TP, ob))
        return 0;
    write("You throw the " + ob->short() + " down into the pit.\n");
    say(QCTNAME(TP) + " throws " + LANG_ADDART(ob->short()) +
        " down into the pit.\n");
    ob->move(PIT);
    set_alarm(4.0, -1.0, &faint_sound(ob));
    return 1;
}

public void
enter_pit(object ob)
{
    int hurt;
    
    ob->catch_msg("You enter the pit and start to fall...\n");
    ob->command("$scream");
    ob->move_living("down into the pit", PIT);
    ob->catch_msg("Ouch. That hurt!\n");
    hurt = 20*(100 - random(ob->query_skill(SS_CLIMB)));
    if (hurt > 0)
    {
        ob->reduce_hit_point(hurt);
        ob->do_die(environment(ob));
    }
}

public int
do_enter(string str)
{
    notify_fail(capitalize(query_verb()) + " into what?\n");
    if (str != "into hole" && str != "into pit")
        return 0;
    
    enter_pit(TP);
    
    return 1;
}

public int
do_push(string str)
{
    int suc;
    object *obs;
    
    notify_fail("Push who into what?\n");
    if (!parse_command(str, ETPINV, "%l 'into' 'pit' / 'hole'", obs))
        return 0;
    if (sizeof(obs) != 2)
        return 0;
    if (!CAN_SEE(TP, obs[1]) || TP == obs[1])
        return 0;
        
    if (TP->query_npc() && obs[1]->query_npc())
        suc = TP->query_stat(SS_STR) - obs[1]->query_stat(SS_DEX);
    else
        suc = random(TP->query_stat(SS_STR)) - obs[1]->query_stat(SS_DEX);
    if (obs[1]->query_race_name() == "bat") suc = 0;
    
    if (suc < 10) {
        TP->catch_msg("You fail to push " + QTNAME(obs[1]) +
                      " into the pit.\n");
        obs[1]->catch_msg(QCTNAME(TP) + " fails in " +
                          TP->query_possessive() +
                          " attempt to push you into the pit.\n");
        tell_room(TO, QCTNAME(TP) + " fails in " + TP->query_possessive() +
                  " attempt to push " + QTNAME(obs[1]) +
                  " into the pit.\n", ({TP, obs[1]}));
    } else {
        TP->catch_msg("You push " + QTNAME(obs[1]) + " into the pit.\n");
        obs[1]->catch_msg(QCTNAME(TP) + " pushes you into the pit!\n");
        tell_room(TO, QCTNAME(TP) + " pushes " + QTNAME(obs[1]) +
                  " into the pit!\n", ({TP, obs[1]}));
        enter_pit(obs[1]);
    }
    return 1;
}

public void
init()
{
    ::init();
    
    add_action(do_throw, "throw");
    add_action(do_enter, "enter");
    add_action(do_enter, "climb");
    add_action(do_enter, "jump");
    add_action(do_push,  "push");
}

public int
tie_object(object ob, string what)
{
    if (what != "ring" && what != "iron ring")
        return 0;
        
    if (rope)
        return 0;
        
    rope = ob;
    open_down_exit();
    return 1;
}

public varargs int
untie_object(object ob, string what="")
{
    if (!rope || ob != rope)
        return 0;
        
    close_down_exit();
    rope = 0;
    return 1;
}
