#pragma save_binary

#include <macros.h>

inherit "std/object.c";

object  gDruid;
int     phase, phase_alarm;

void process_input(string str);

#define PRAY_CHISLEV        ("0x02")

#define PHASE_ONE   0
#define PHASE_TWO   1
#define END_PHASE   2
#define FINISHED    3

void
set_druid(object druid)
{
    gDruid = druid;
}

public void 
create_object()
{
    setuid();
    seteuid(getuid());
    
    set_name("_druid_guru_ritual_");
    set_short("guru object");
    set_long("an object used in the archer guru.\n");
    
    set_no_show();
}

varargs int
get_phase(int inc = 0)
{
    if (phase < FINISHED)
        input_to(process_input, 1);
    
    phase += inc;
    
    if (inc)
    {
        switch(phase)
        {
            case PHASE_ONE:
            this_player()->catch_msg("You assist the druid in decorating the "
            + "grove with herbs and crystals. The ornaments form a circle in "
            + "the surrounding garden, flowers and leaves are tied into "
            + "festoons which hang above you, between the trees and the "
            + "ruin.\n");
                break;
            case PHASE_TWO:
            this_player()->catch_msg("You wipe yourself off with wet leaves "
            + "to cleanse yourself and rub crushed flowers along your arms, "
            + "staining them in numerous colours. The druid draws an intricate "
            + "pattern on your face in blue dye and summon fireflies which "
            + "slowly wash the clearing in an eerie glow.\n");
                break;
            case END_PHASE:
            this_player()->catch_msg("You kneel down in the center of the "
            + "circle while the druid begins to tie you up with vines, your "
            + "hands forming a cup infront of you.\n\nThe druid chants in an "
            + "unknown language, every word reverberating as if confined in "
            + "a spacious cave.\n");
                break;
            case FINISHED:
            this_player()->catch_msg("As the ritual ends, the druid tidies "
            + "up around you before freeing you from the vines.\n");
            gDruid->command("emote speaks in a calm demeanor: She has "
            + "graciously agreed to grant you what it is you desire. You must "
            + "enter the temple sanctuary to be bestowed with the wisdom of "
            + "Zivilyn.");
            
            this_player()->set_guru_stage(PRAY_CHISLEV);
            set_alarm(0.0, 0.0, &remove_object());
            return 1;
        }
    }
    
    return phase;
}

status
process_input(string str)
{
    if (IN_ARRAY(str, ({ "q", "quit", "stop", "exit", "end" })) && 
        phase != END_PHASE)
    {
        this_player()->catch_msg("You have aborted the ritual.\n");
        remove_alarm(phase_alarm);
        return 1;
    }
    
    switch(get_phase())
    {
        case PHASE_ONE:
        this_player()->catch_msg("You are preparing the grove for a "
        + "ritualistic prayer to Chislev. You may 'stop' if you so desire.\n");
            break;
        case PHASE_TWO:
        this_player()->catch_msg("You are in the process of cleansing yourself "
        + "for your prayer. You may 'stop' if you do not wish to proceed with "
        + "the ritual.\n");
            break;
        case END_PHASE:
        this_player()->catch_msg("The ritual has begun, it would be too late "
        + "to end it now.\n");
            break;
        default:
        return 0;
    }
    
    return 1;
}

public status
start(string str)
{
    notify_fail("Begin what? the ritual?\n");
    if (!strlen(str) || (str != "the ritual" && str != "ritual"))
        return 0;
    
    phase_alarm = set_alarm(5.0, 10.0, &get_phase(1));
    input_to(process_input, 1);
    write("You begin to perform the ritual.\n");
    tell_room(environment(this_player()), QCTNAME(this_player()) + " performs "
    + "an intricate ritual.\n", ({ this_player() }));
    return 1;
}

void
init()
{
    ::init();
  
    add_action(start, "begin");
}