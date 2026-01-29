/*
 * Middle Circle of the Elemental Temple of Calia
 * 
 * Created by Petros, April 2010
 */

#pragma strict_types

#include "defs.h"
#include <macros.h>

inherit TEMPLE_ROOM_BASE;

// Defines
#define IS_CONSIDERING_TAPESTRY     "_is_considering_tapestry"

// Prototypes
public void consider_stage1(object player);
public void consider_stage2(object player);
public void consider_stage3(object player);


public void
create_temple_room()
{
    set_short("Elemental Temple Middle Circle");
    set_long("This is a hallway in the middle circle of the Elemental "
        + "Temple of Calia. The walls are constructed using grey stone and "
        + "crystalline. The room is entirely sparse, except from a large "
        + "tapestry displayed prominently upon the northern wall. The "
        + "hallway continues to the east and southwest from here.\n\n");
    
    try_item( ({ "tapestry", "large tapestry", "northern wall" }),
        "This tapestry is very large, covering most of the northern wall "
      + "of this room. It is made from plush wool and has clearly been "
      + "crafted by expert Argosian seamstresses. It depicts what appears "
      + "to be a massive blur of all possible colours. Perhaps if you "
      + "were to <consider> the tapestry more carefully, some sense could "
      + "be made of the blurry depiction.\n");
    
    try_item( ({ "massive blur", "blur", "blurry depiction" }),
        "You can't make heads or tails of the massive blur. Perhaps you "
      + "can try and <consider> the tapestry more carefully.\n");
      
    add_exit(ELEMENTALIST_TEMPLE + "middle2", "east");
    add_exit(ELEMENTALIST_TEMPLE + "middle4", "southwest"); 
}

public void
init()
{
    ::init();
    
    add_action("do_consider", "consider");
}

public int
do_consider(string arg)
{
    if (!strlen(arg))
    {
        notify_fail("What would you like to consider? The tapestry?\n");
        return 0;
    }
    
    arg = lower_case(arg);
    if (!parse_command(arg, ({ }), "[large] 'tapestry'"))
    {
        notify_fail("What would you like to consider? The tapestry?\n");
        return 0;
    }
    
    if (this_player()->query_prop(IS_CONSIDERING_TAPESTRY))
    {
        notify_fail("You are already considering the tapestry!\n");
        return 0;
    }
    
    write("You take a step back and rather than trying to focus on a single "
        + "point you stare openly trying to take all of the picture in.\n\n");

    say(QCTNAME(this_player()) + " takes a step back and considers the "
        + "tapestry. For a moment " + this_player()->query_pronoun()
        + " stands transfixed with an intent gaze.\n");
    
    int next_stage_alarm = set_alarm(2.0, 0.0, &consider_stage1(this_player()));
    this_player()->add_prop(IS_CONSIDERING_TAPESTRY, next_stage_alarm);
    
    return 1;
}

public void
consider_stage1(object player)
{
    if (environment(player) != this_object())
    {
        player->remove_prop(IS_CONSIDERING_TAPESTRY);
        return;
    }
    
    player->catch_tell(
          "The colours seem to coalesce before your very eyes. Fierce red, dark "
        + "brown, deep blue and ivory white intermingled with obsidian black "
        + "and silvery streaks starts dancing in your vision. At first the "
        + "colours seem disparate and set apart from one another, but shadowy "
        + "streaks and silvery lines gradually reach and entwine from "
        + "everywhere, binding the colours together, infusing with one "
        + "another.\n\n"
        + "Movement pauses...\n\n");
    int next_stage_alarm = set_alarm(4.0, 0.0, &consider_stage2(player));
    player->add_prop(IS_CONSIDERING_TAPESTRY, next_stage_alarm);       
}

public void
consider_stage2(object player)
{
    if (environment(player) != this_object())
    {
        player->remove_prop(IS_CONSIDERING_TAPESTRY);
        return;
    }
    
    player->catch_tell("...and suddenly the colours move inward, tighter and "
        + "tighter...\n\n");

    int next_stage_alarm = set_alarm(2.0, 0.0, &consider_stage3(player));
    player->add_prop(IS_CONSIDERING_TAPESTRY, next_stage_alarm);       
}

public void
consider_stage3(object player)
{
    if (environment(player) != this_object())
    {
        player->remove_prop(IS_CONSIDERING_TAPESTRY);
        return;
    }
    
    player->catch_tell(
          "...till they literally explode in a myriad of new colours and forms. "
        + "The colours jump from the tapestry, floating around you in a brief "
        + "moment that feels like an eternity.\n\n"
        + "As you blink, the colours seem to fade and return to the tapestry "
        + "which now appears as before.\n");

    tell_room(this_object(), QCTNAME(player) + " blinks " 
        + player->query_possessive() + " eyes.\n", ({ player }));
    
    player->remove_prop(IS_CONSIDERING_TAPESTRY);
}
