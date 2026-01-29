/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * forest11.c
 *
 */

#include "/d/Terel/include/Terel.h"
inherit ENCHANT_DIR + "forest_room";

#include <ss_types.h>
#include "enchanted.h"

object unicorn;
object check_sh_pr(string sh_desc, string prop, object ob);

/*
 * Function name: query_object_list
 * Description:   return list of objects to clone at each reset.
 */
public string*
query_object_list()
{
    return ({ENCHANT_DIR + "monster/unicorn"});

}

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    
    set_long(query_long() + "There is an old oak here.\n");
    add_item(({"oak", "old oak"}), "@@exa_oak");

    add_cmd_item(({"oak", "old oak", "hole"}), "enter", "@@enter_oak");

    add_exit(MAZE, "south", 0, HARD_TO_WALK);
    add_exit(MAZE, "west",  0, HARD_TO_WALK);
    add_exit(MAZE, "east",  0, HARD_TO_WALK);
    add_exit(MAZE, "north", 0, HARD_TO_WALK);

    reset_room();
}

public void
delay(object who)
{
    if (who)
        who->move_living("into the oak", ENCHANT_DIR + "stem1");
}

public string
enter_oak()
{
    object ring;

    ring = check_sh_pr("gold ring", "q_solver", TP);
    if (!ring) {
        if (unicorn && present("unicorn")) unicorn->attack_object(TP);
    }
    set_alarm(2.0, -1.0, &delay(TP));

    return "You start to enter the hole in the stem of the old oak.\n";
}

public object
check_sh_pr(string sh_desc, string prop, object ob)
{
    int i;
    object *ob_arr, r_ob;

    r_ob = 0;
    ob_arr = all_inventory(ob);
    for (i=0; i<sizeof(ob_arr); i++) {
        if (ob_arr[i]->query_short() == sh_desc &&
            ob_arr[i]->query_prop(prop) == ob->query_name()) {
            r_ob = ob_arr[i];
            break;
        }
    }
    return r_ob;
}

public string
exa_oak()
{
    string str = "It looks very old, and it seems to be dead. " +
                 "Only the stem is left. " +
                 "The stem has a very strange shape. It's thick at the " +
                 "bottom and so is its upper part, while its waist is " +
                 "thinner. It almost looks like an hourglass!";
    
    if (TP -> query_skill(SS_AWARENESS) > 19)
        str += " There is a hole in the stem which you can enter.";

    return str + "\n";
}
