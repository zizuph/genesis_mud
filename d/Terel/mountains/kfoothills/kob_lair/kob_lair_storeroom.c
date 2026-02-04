/*
 * kob_lair_storeroom.c
 *
 * A large quantity of meat from the strange animal is kept in the 
 * locked storeroom. A spear trap is set to be triggered by anyone
 * attempting to get the meat
 *
 * Britanica 160322
 */
#pragma strict_types

#include "ss_types.h"
#include "include/cave_defs.h"
#include "stdproperties.h"
#include "tasks.h"

inherit KOB_LAIR_PATH + "default_kob_lair";

int trap_set;
int trap_found;

public int remove_trap(string text);
public int get_meat(string text);

/*
 * Function name: create_room
 * Description  : constructor.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void 
create_room()
{
    ::create_room();

    set_long("@@long_desc");
    
    clone_object(DOORS + "storeroom_out")->move(this_object());
    
    add_prop(ROOM_I_LIGHT, 0);
    add_prop(OBJ_S_SEARCH_FUN, "do_search");
    
    add_item(({"holes", "holes in ceiling"}), "@@holes_in_ceiling");
    add_item(({"spears", "spear"}), "@@spears_in_gound");
    
    add_npc(NPC + "salamander", 1, 0);

    set_alarm(0.1, 0.0, reset_room);
}

/*
 * Function name: reset_room
 * Description  : Resets the rooms trap and add meat if not present
 * Arguments    : n/a
 * Returns      : n/a
 */
void
reset_room()
{
    trap_set = 1;
    trap_found = 0;
    if (!present("strange_meat"))
    {
        int count = random(6);
        object meat = clone_object(KOB_LAIR_PATH + "obj/strange_meat");
        meat->set_heap_size(7 + count);
        meat->move(this_object());
        
        string* herbs = ({"aravelis", "argil", "lukilvor", "moosho",
                          "ramira", "sebre", "tilhiyin", "whitehorn",
                          "wilcol", "ylpi", "ylpoe"});
        
        for (int i = 0; i < 1 + random(2); i++)
        {
            string herb = herbs[random(sizeof(herbs))];
            object herbs = clone_object(TEREL_COMMON + "herbs/" + herb);
            herbs->set_heap_size(1 + random(2));
            herbs->move(this_object());
        }
    }
    
    object salamander = present("salamander");
    if (salamander)
    {
        salamander->secure_room();
    }
    else
    {
        write("Salamander not present.\n");
    }
}

/*
 * Function name: holes_in_ceiling
 * Description  : Returns the description of the holes based on trap
 *                found and set status.
 * Arguments    : n/a
 * Returns      : string - description if trap can be seen.
 */
public string holes_in_ceiling()
{
    if (trap_set)
    {
        if (trap_found)
        {
            return "They appear to have spear tips protruding from "
              + "the holes.\n";
        }
    }
    else
    {
        return "They appear to be directly above the spears.\n";
    }
}

/*
 * Function name: holes_in_ceiling
 * Description  : Returns the description of the spears based on trap
 *                set status.
 * Arguments    : n/a
 * Returns      : string - description if spears can be seen.
 */
public string 
spears_in_gound()
{
    if (!trap_set)
    {
        return "There are several spear embedded in the ground which " + 
          "appear to have come from holes in the ceiling.\n";
    }
}

/*
 * Function name: init
 * Description  : add room actions for player
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
init()
{
    add_action(remove_trap,"remove");
    add_action(remove_trap,"disarm");
    add_action(get_meat,"get");

    ::init();
}

/*
 * Function name: long_desc
 * Description  : VBFC description of room.  Adds trap description if 
 *                not set
 * Arguments    : n/a
 * Returns      : n/a
 */
public string 
long_desc()
{
    string result = "The tool cut walls around the door in the west wall "
     + "give way to a large natural section of cave. All round this room "
     + "are supplies and goods raided by the kobolds. Several sections " 
     + "of the ground are raised and provide a natural area to place "
     + "goods.\n";
    if (!trap_set)
    {
        result += "There are several spear embedded in the ground which "
          + "appear to have come from holes in the ceiling.\n";
    }
    return result;
}

/*
 * Function name: trigger_trap
 * Description  : Handle player triggering the trap
 * Arguments    : n/a
 * Returns      : 1 for success, 0 for no action
 */
public int trigger_trap()
{
    object player = this_player();
    if (trap_set)
    {
        if (present(player))
        {
            if (player->resolve_task(TASK_DIFFICULT, SS_DEFENCE) <= 0)
            {
                int damage = player->query_max_hp() / 10;
                player->heal_hp(-damage);
                tell_room(environment(player), player->query_name() 
                  + " is stabbed by spears descending from the " 
                  + "ceiling.\n", player);
                player->catch_tell("You are stabbed by spears " 
                  + "descending from the ceiling.\n");
            }
            else
            {
                tell_room(environment(player), player->query_name() 
                  + " deflects several spears as they descend from " 
                  + "the ceiling.\n", player);
                player->catch_tell("You deflect several spears that "
                  + "suddenly descend from the ceiling.\n");
            }
        }
        trap_set = 0;
        return 1;
    }
}

/*
 * Function name: do_search
 * Description  : Handle custom searching
 * Arguments    : object searcher - Player searching
 *                string str - Search Target
 * Returns      : string - description of trap if found
 */
public string do_search(object searcher, string str)
{
    if (str == "here for traps")
    {
        if (searcher->resolve_task(TASK_EASY, SS_FR_TRAP) > 0)
        {
            if (trap_set)
            {
                trap_found = 1;
                return "Several holes in the ceiling are aiming spears " 
                  + "to the location just in front of the meat. When the "
                  + "meat is moved, the spears will rapidly descend from "
                  + "the ceiling, impaling the unfortunate soul who is "
                  + "standing in front of the meat.\n";
            }
            else
            {
                return "There several spears embedded in the ground.\n";
            }
        }
    }
    return 0;
}

public int remove_trap(string text)
{
    if (parse_command(text, this_player(), " [spear] 'trap'"))
    {
        if (trap_found)
        {
            if (this_player()->resolve_task(TASK_ROUTINE, SS_FR_TRAP) > 0)
            {
                if (trap_set)
                {
                    trap_set = 0;
                    this_player()->catch_tell("You touch the meat and " 
                      + "quickly retreat to a safe distance. The " 
                      + "movement causes spears to descend from their "
                      + "holes in the ceiling.\n");
                    tell_room(environment(this_player()), 
                      this_player()->query_name() + "touches the meat "
                      + "and quickly steps away. The movement causes " 
                      + "spears to shoot down from holes in the "
                      + "ceiling.\n");
                }
                else
                {
                    this_player()->catch_tell("The trap has already been "
                    + "sprung.\n");
                }
                return 1;
            }
            else
            {
                set_alarm(2.0, 0.0, trigger_trap);
                this_player()->catch_tell("You accidentally trigger the "
                    + "trap.\n");
                return 1;
            }
        }
    }
}

public int
get_meat(string text)
{
    if (parse_command(text, this_player(), 
        " [strange] [animal] 'meats'"))
    {
        if (trap_set)
        {
            this_player()->catch_tell("As you start to lift the meat you hear " +
                "a click.\n");
            tell_room(environment(this_player()), 
                      this_player()->query_name() + " starts to lift the meat " + 
                      "and you hear a click.\n");
            set_alarm(1.0, 0.0, trigger_trap);
            return 1;
        }
    }
}