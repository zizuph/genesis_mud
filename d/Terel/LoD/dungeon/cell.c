/*
 * dungeon.c
 *
 * A generic dungeon below the Legion of Darkness quarters.
 */

#include "/d/Terel/include/Terel.h"
inherit LOD_DIR + "legion_room";

#include <language.h>
#include <std.h>
#include <ss_types.h>

#define DUNG_DIR (LOD_DIR + "dungeon/")

string *stone_name = ({});

public void
reset_room()
{
    int i;
    object *all = all_inventory(TO);
    
    for (i=0; i<sizeof(all); i++)
        if (interactive(all[i]) &&
            !SECURITY->query_wiz_level(all[i]->query_real_name()))
            return;
    
    for (i=0; i<sizeof(all); i++) {
        if (function_exists("create_object", all[i]) != "/std/door") continue;
        if (all[i]->query_open()) {
            all[i]->do_close_door("");
            all[i]->query_other_door()->do_close_door("");
        }
        if (!all[i]->query_locked()) {
            all[i]->do_lock_door();
            all[i]->query_other_door()->do_lock_door("");
        }
    }
    
    ::reset_room();
}

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    
    set_short("in a dungeon");
    set_long("You are standing in a dungeon below the old mansion. " +
             "The walls are wet and the air is far from fresh.\n");

    add_item(({"floor"}), "The floor is made of stones which " +
             "have been set into place with great craftmanship.\n");

    add_item(({"wall", "walls"}), "The wet stony walls " +
             "are a masterpiece, the individual stones have been " +
             "fit together with very high precision. Those " +
             "who build the dungeons must have been very skillful " +
             "stone-cutters. You notice some inscriptions on several " +
             "stones.\n");
             
    add_item(({"stone", "stones"}),
             "The stones seems to have been cut very precisely. " +
             "Some of the stones in the walls have inscriptions.\n");
             
    add_cmd_item(({"stone"}), "push", "@@do_push");
    add_cmd_item(({"stone"}), "press", "@@do_push");
             
    add_item(({"inscription", "inscriptions"}),
             "Most of the inscriptions are not readable. The few " +
             "that you are able to understand seem to be of the " +
             "usual kind you find in prison cells.\n");
             
    add_prop(ROOM_I_LIGHT, 0);
    add_prop(OBJ_S_SEARCH_FUN, "do_search");
    add_prop(OBJ_S_WIZINFO, "Don't 'update' this room manually! It " +
                            "will screw things up! If you need to " +
                            "refresh it, use 'Call here reset_room'.\n");
}

public string
do_push()
{
    write("You push a randomly selected stone in the wall.\n");
    tell_room(TO, QCTNAME(TP) + " puts " + TP->query_possessive() +
              " hands on a stone in the wall and pushes it.\n", TP);
    
    return "Nothing seems to happen.\n";
}

public string
do_search(object searcher, string str)
{
    if (!sizeof(stone_name))
        return "";
        
    if (!searcher || ENV(searcher) != TO)
        return "";
        
    if (str != "stones" && str != "walls" && str != "stone")
        return "";
        
    if (searcher->query_skill(SS_AWARENESS) < 25)
        return "";
        
    return "You notice something odd about " +
           LANG_ADDART(stone_name[0]) + ".\n";
}

public varargs int
set_hidden_stone(mixed name, string desc, string verb, string action)
{
    if (stringp(name))
    {
        stone_name = ({ name });
    }
    else if (pointerp(name))
    {
        if (sizeof(filter(name, stringp)) != sizeof(name))
            return 0;
        stone_name = name;
    }
    else
        return 0;
    
    add_item(name, desc);
    
    if (strlen(verb))
        add_cmd_item(name, verb, action);
    
    return 1;
}
