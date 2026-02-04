#include "ss_types.h"
#include "include/cave_defs.h"
#include "stdproperties.h"
#include "tasks.h"

inherit KOB_LAIR_PATH + "default_kob_lair";

int trap_set;
int trap_found;

public int remove_trap(string text);

public void 
create_room()
{
    ::create_room();

    set_long("@@long_desc");
    
    add_exit(KOB_LAIR_PATH + "kob_lair_a09", "north", 0);
    add_exit(KOB_LAIR_PATH + "kob_lair_a12", "west", 0);

    clone_object(DOORS + "storeroom_in")->move(this_object());
    
    add_prop(ROOM_I_LIGHT, 0);
    add_prop(OBJ_S_SEARCH_FUN, "do_search");
    
    reset_room();
}

public string 
long_desc()
{
    string result = "The natural cave continues to the north and west " +
      "with signs the stone has been tool cut down to a heavy wooden door " +
      "fitted in the middle of the east wall.\n";
    if (!trap_set)
    {
        result += "There are two large spiked logs handing in the cave " + 
          "to the west.\n";
    }
    return result;
}

void
reset_room()
{
    trap_set = 1;
    trap_found = 0;
}

public void
init()
{
    add_action(remove_trap,"remove");
    add_action(remove_trap,"disarm");

    ::init();
}

public int trigger_trap()
{
    object player = this_player();
    if (trap_set)
    {
        player->catch_tell("You hear a sharp click from underfoot.\n");
        if (present(player))
        {
            if (player->resolve_task(TASK_DIFFICULT, SS_ACROBAT) <= 0)
            {
                int damage = player->query_max_hp() / 4;
                player->heal_hp(-damage);
                tell_room(environment(player), player->query_name() + " is crushed " +
                "between two swinging spiked logs.\n", player);
                player->catch_tell("You are crushed between two spiked logs.\n");
            }
            else
            {
                tell_room(environment(player), player->query_name() + 
                  " performs an acrobatic roll to avoid a swinging log, and " +
                  "dives over another log. The logs crush together and " + 
                  "embed their spikes in each other causing the logs to " + 
                  "spike together.\n", player);
                player->catch_tell("You perform an acrobatic roll to avoid " +
                  "one swinging log and dive over the other. The logs crush " + 
                  "together and embed their spikes in each other causing " + 
                  "the logs to stick together.\n");
            }
        }
        trap_set = 0;
        return 1;
    }
}

public string do_search(object searcher, string str)
{
    if (str == "here for traps")
    {
        if (searcher->resolve_task(TASK_EASY, SS_FR_TRAP) > 0)
        {
            if (trap_set)
            {
                trap_found = 1;
                return "two spiked logs are suspended from the ceiling. " +
                  "A pressure plate on the floor will trigger the logs to " + 
                  "crash down crushing the person travelling west.\n";
            }
            else
            {
                return "There are two large spiked logs handing in front of the west entrance.\n";
            }
        }
    }
    return 0;
}

public int remove_trap(string text)
{
    if (parse_command(text, this_player(), " [spiked] [log] 'trap'"))
    {
        if (trap_found)
        {
            if (this_player()->resolve_task(TASK_ROUTINE, SS_FR_TRAP) > 0)
            {
                if (trap_set)
                {
                    trap_set = 0;
                    this_player()->catch_tell("You touch the trap and cause " + 
                      "logs to swing down. The logs crush together and embed "+ 
                      "thier spikes in each other causing the logs to spike " + 
                      "together.\n");
                    tell_room(environment(this_player()), 
                      this_player()->query_name() + "touches the trap and cause " + 
                      "logs to swing down. The logs crush together and embed "+ 
                      "thier spikes in each other causing the logs to spike " + 
                      "together.\n");
                }
                else
                {
                    this_player()->catch_tell("The trap has already been sprung.\n");
                }
                return 1;
            }
            else
            {
                set_alarm(2.0, 0.0, trigger_trap);
                this_player()->catch_tell("You accidentally trigger the trap.\n");
                return 1;
            }
        }
    }
}

