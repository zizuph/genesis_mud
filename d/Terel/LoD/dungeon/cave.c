/*
 * cave.c
 *
 * A cave below the Legion of Darkness quarters.
 */

#include "/d/Terel/include/Terel.h"
inherit LOD_DIR + "legion_room";

#define DUNG_DIR (LOD_DIR + "dungeon/")
#define OTHER    (DUNG_DIR + "cave2")

int closed;

public string*
query_moving_object_list()
{
    return ({LOD_DIR + "monster/bat2",
             LOD_DIR + "monster/bat2",
             LOD_DIR + "monster/hydra"});
}

public void
close_east_exit()
{
    closed = 1;
    remove_exit("east");
    add_my_desc("Several huge stones block the way to the east.\n", TO);
    
    OTHER->remove_exit("west");
    OTHER->add_my_desc("Several huge stones block the way to the east.\n", TO);
}

public void
hydra_died(object hydra, object killer)
{
    tell_room(TO, "In a final attempt of rage, the " +
                  QTNAME(hydra) +
                  " lashes out its tail toward the ceiling.\n");
    tell_room(TO, "Huge stones rain down. Luckily, you manage " +
                  "avoid them, but the exit to the east seems " +
                  "to be blocked.\n");
    close_east_exit();
}

public void
open_east_exit()
{
    closed = 0;
    add_exit(OTHER, "east", "@@check_east");
    remove_my_desc(TO);
    
    OTHER->add_exit(file_name(TO), "west", 0);
    OTHER->remove_my_desc(TO);
}

public void
reset_room()
{
    ::reset_room();
            
    if (closed && !sizeof(filter(all_inventory(TO), interactive)))
        open_east_exit();
}

public int
check_east()
{
    object hydra = present("hydra");
    
    if (hydra && hydra->try_pass(TP, "east") == 0)
        return 1;
    
    return 1;
}

public void
create_room()
{
    ::create_room();
    
    set_short("large cave");
    set_long("You are down in a large cave. There is lots of debris here, " +
             "mostly broken bones. You feel very uneasy.\n");
             
    add_item("debris", "Mostly old bones, but you notice some " +
             "half-rotten body parts as well. You begin to wonder " +
             "if there is something around here who devour " +
             "people like you.\n");
             
    add_prop(ROOM_I_LIGHT, 0);
    
    add_exit(DUNG_DIR + "tunnel2", "west", 0);
    
    open_east_exit();
    
    reset_room();
}
