/*
 * cell_4.c
 *
 * A dungeon below the Legion of Darkness quarters.
 */

#include "/d/Terel/include/Terel.h"
inherit LOD_DIR + "/dungeon/cell";

#include <stdproperties.h>
#include <macros.h>

#include <ss_types.h>

#define DUNG_DIR (LOD_DIR + "dungeon/")
#define BEHIND   (DUNG_DIR + "behind")

int pushed = 0;

public void
create_room()
{
    ::create_room();
    
    set_hidden_stone(({"cleaner stone", "different stone", "hidden stone"}),
                     "This stone, half-way up the rear wall, " +
                     "seems slightly " +
                     "different from the others. It locks " +
                     "somewhat cleaner than the rest.\n",
                     "push", "@@do_push_hidden_stone");
    
    reset_room();
}

public void
open_secret_exit()
{
    object stone;
    
    if (pushed)
        return;
    
    pushed = 1;
    add_exit(BEHIND, "east", 0);
    if (member_array("west", BEHIND->query_exit_cmds()) == -1)
        BEHIND->add_exit(file_name(TO), "west", 0);
    add_my_desc("Someone has removed a stone in the eastern wall.\n", TO);
    BEHIND->add_my_desc("Someone has removed a stone in the " +
                        "western wall.\n", TO);
    
    seteuid(getuid());
    
    if (stone = present("wall_stone", find_object(BEHIND)))
        stone->remove_object();
    
    clone_object(LOD_DIR + "obj/stone")->move(BEHIND, 1);
}

public void
close_secret_exit()
{
    if (!pushed)
        return;
    
    pushed = 0;
    remove_exit("east");
    BEHIND->remove_exit("west");
    remove_my_desc(TO);
    BEHIND->remove_my_desc(TO);
}

public void
push_action(object who)
{
    if (!who || ENV(who) != TO)
        return;
        
    if (who->query_stat(SS_STR) > 80 + random(11)) {
        who->catch_msg("The stone moves into the wall.\n");
        tell_room(TO, "The stone " + QTNAME(who) + " is pushing " +
                  "moves into the wall!\n", who);
        open_secret_exit();
    } else if (who->query_stat(SS_STR) > 53 + random(11)) {
        who->catch_msg("For a short while you thought that the " +
                       "stoned moved.\n");
    }
}

public string
do_push_hidden_stone()
{
    if (pushed)
        return "Push what?\n";
        
    say(QCTNAME(TP) + " pushes a stone on the rear wall.\n");
    
    set_alarm(1.0, 0.0, &push_action(TP));
    
    return "You push the cleaner stone on the rear wall.\n";
}

public void
reset_room()
{
    ::reset_room();
    
    if (!pushed || sizeof(filter(all_inventory(TO), interactive)))
        return;
        
    close_secret_exit();
}
