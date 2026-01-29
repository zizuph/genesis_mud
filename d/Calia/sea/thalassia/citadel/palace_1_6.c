
/*  Grand Palace in Thalassia

    coder(s):   Jaacar

    history:    15. 7.03    room coded                      Jaacar

*/

#pragma save_binary
#pragma strict_types

inherit "/d/Calia/std/water_room";
#include <stdproperties.h>
#include <macros.h>
#include <filter_funs.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

#define GUARD_NUM 4
#define PET_NUM 2
#define THALASSIAN_KING_CHALLENGED "_i_challenged_atlas"

object *guard = allocate(GUARD_NUM);
object *pet = allocate(PET_NUM);
object king;

void
make_guard(int i)
{
    guard[i] = clone_object("/d/Calia/sea/creatures/palace_triton");
    guard[i]->equip_me();
    guard[i]->move(TO);
    tell_room(TO, QCTNAME(guard[i]) + " arrives to guard the King.\n");
}

void
make_pet(int i)
{
    pet[i] = clone_object("/d/Calia/sea/creatures/dragonsaurus");
    pet[i]->move(TO);
    tell_room(TO, QCTNAME(pet[i]) + " arrives and sits next to the King.\n");
}

void
reset_room()
{
    int i,j;

    for (i=0; i < GUARD_NUM; i++)
        if (!guard[i])
            set_alarm(0.5, 0.0, &make_guard(i));
    for (j=0; j < PET_NUM; j++)
        if (!pet[j])
            set_alarm(0.5,0.0, &make_pet(j));
    if (!king)
    {
        king = clone_object("/d/Calia/sea/creatures/thalassian_king");
        king->equip_me();
        king->move(TO);
    }
}

void
create_water_room()
{
    set_short("Royal Palace Throne Room");
    set_long("You have entered the Throne Room of the Royal Palace. "+
        "This is where the King of Thalassia greets his subjects "+
        "and conducts his daily business or ruling this magnificent "+
        "underwater paradise. There is a large throne here, decorated "+
        "with golden patterns. North of here there is an entrance to "+
        "another room, to the east leads back to the Palace Guard "+
        "Room, while to the south leads to a stairway leading up "+
        "to the second floor of the palace.\n");
    add_item("stairway", "To the south you see a room with a stairway "+
        "leading up to the second floor of the palace.\n");
    add_item(({"throne", "large throne"}), "This throne is made of "+
        "solid gold and is quite large indeed. It appears as though "+
        "two people could sit easily in it side by side. There are "+
        "patterns carved into the gold on each side of the throne.\n");
    add_item(({"pattern", "patterns","gold pattern","gold patterns"}), 
        "There are many intricate patterns carved into the gold on "+
        "the sides of the throne. One looks like a pyramid, while "+
        "another looks like an upside-down pyramid.\n");

    IN;

    add_swim_exit(THALC+"palace_1_5","north",0,1);
    add_swim_exit(THALC+"palace_1_3","east",0,1);
    add_swim_exit(THALC+"palace_1_7","south",0,1);
    set_alarm(1.0, 0.0, reset_room);
}

public int
clean_up()
{
    int i,j;

    for (i=0; i < GUARD_NUM; i++)
        if (guard[i])
            return 1;
    for (j=0; j < PET_NUM; j++)
        if (pet[j])
            return 1;
    if (king)
        return 1;
    remove_object();
}

public int
challenge_atlas(string str)
{
    object target;
    
    if (!str)
    {
        notify_fail("Challenge whom?\n");
        return 0;
    }
    
    parse_command(str, environment(this_player()), "%o", target);
    if (!target)
    {
        notify_fail("There doesn't appear to be anyone here "
            + "willing to take up your challenge.\n");
        return 0;
    }
    
    if (target != king)
    {
        notify_fail(target->query_The_name(this_player()) + " doesn't "
            + "appear to be willing to take up your challenge.\n");
        return 0;       
    }
    
    this_player()->add_prop(THALASSIAN_KING_CHALLENGED, 1);
    object * team = FILTER_PRESENT(this_player()->query_team_others());
    if (sizeof(team))
    {
        target->command("emote bubbles: Ahhh! You knew you had to challenge "
            + "me with a team behind you. No matter, let us see how you "
            + "fare!");
        team->add_prop(THALASSIAN_KING_CHALLENGED, 1);
    }
    else
    {
        target->command("emote bubbles: Ahhhh!!! Finally someone willing to "
            + "challenge me. Let us see how you fare!");
    }
    target->attack_object(this_player());
    
    return 1;
}

/* 
 * Function name:       init
 * Description  :       Standard init function to add actions
 * Arguments    :       none
 * Returns      :       void/nothing
 */
public void 
init() 
{
    ::init();  
    add_action(challenge_atlas, "challenge");
}