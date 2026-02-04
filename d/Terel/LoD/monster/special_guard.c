/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * special_guard.c
 *
 * A dark guard for the legion of darkness
 * Sorgum 941029
 * Modified here for a special guard in the dungeons
 * Mortricia June 1996
 */

#include "/d/Terel/include/Terel.h"
inherit LOD_DIR + "monster/legion_soldier";

#include <ss_types.h>

#define TORCH  "/std/torch"

object prisoner = 0;

/*
 * Function name: query_object_list
 * Description:   return list of equipment
 */
public string*
query_object_list()
{
    return ({LOD_DIR + "armour/dark_helmet",
             LOD_DIR + "armour/dark_chainmail",
             LOD_DIR + "armour/dark_shield",
             LOD_DIR + "weapon/dark_sword",
             TORCH});
}

/*
 * Function name: create_monster
 * Description:   Create the monster. (standard)
 */
public void
create_monster()
{
    ::create_monster();
    
    set_name("guard");
    add_name("special_guard");
    set_short("young legion guard");
    set_long(
         "A human guard that guards the entrance to these evil quarters " +
	     "of the legion of darkness. He seems younger than most of " +
	     "the other guards.\n");
    set_adj("evil");
    add_adj("young");
    set_race_name("human");
    set_gender(MALE);
    set_alignment(-100);
   
    set_stats(({60, 60, 60, 50, 40, 40}));
    SET_MAX_HP;
    
    set_skill(SS_DEFENCE,      55 + random(11));
    set_skill(SS_UNARM_COMBAT, 30 + random(11));
    set_skill(SS_PARRY,        55 + random(11));
    set_skill(SS_WEP_SWORD,    85 + random(5));
    
    add_chat("Hmm. I wonder what's in those cells... no one has " +
             "has found the keys...");
}

public string
guard_response()
{
    object guard = present("dark_guard", ETO);
    
    if (!guard)
        return "shrug";
    
    if (!prisoner || !present(prisoner, ETO)) {
        command("say Have you found the keys yet?");
        guard->command("say No.");
        return "nod at dark_guard";
    }
    
    command("say What shall I do with this prisoner?");
    command("point pit_prisoner");
    guard->command("say Ha! We don't take prisoners. Remember? " +
                   "Throw him into the pit!");
    return "smile";
}

public string
beg_for_life()
{
    if (!prisoner)
        return "emote ponders what's down that pit.";
    
    prisoner->command("emote begs for his life.");
    prisoner->set_hp(10);
    return "say You heard what they said. We don't take any prisoners. " +
           "Now, please be a nice guy and accept that.";
}

public void
start_push_seq(object ob)
{
    prisoner = ob;
    
    team_join(prisoner);
    
    seq_clear("walk");
    seq_new("walk");
    seq_addfirst("walk", ({"down", "east", "greet dark_guard",
                           "@@guard_response", 
                           "light torch", "east",
                           "point pit",
                           "say Ok, here we go...",
                           "@@beg_for_life",
                           "push pit_prisoner into pit", "cackle",
                           "west", "extinguish torch",
                           "say Hah! What a pathetic fellow...",
                           "wave dark_guard", "west", "up"
                           }));
}
