/* file name:        /d/Avenir/rangorn/temp/c6.c
 *  creator(s):      (Rangorn , Feb 97)
 *  revisions:
 *  purpose:
 *  note:
 *  bug(s):
 *  to-do: Find the function that actually kills the player 
 */

/* Inherit the room that is the base for the area. */
inherit "/d/Avenir/common/holm/t_camp/camp_base";

/* Include the local area defines, etc */
#include "camp.h"
#include <ss_types.h>
#include <cmdparse.h>
#include <tasks.h> /* This is for the resolve task in jump */

/* Now create the room.  */
void 
create_camp_room()
{
    set_short("A jagged crack in the ground. A tent on the other side");
    set_long("You are surounded by towering and jagged stones, with "+
             "a wide crack opening the ground in the east. Heavy " +
             "and thick steam is rising from the chasm and every " +
             "now and then a burst of boiling water erupts from " +
             "within it, spraying you with burning pellets of "+
             "crystal-clear water. " +
             "Beyond the crack to the east you can make out a " +
             "tent.\n");

    add_exit("c7", "north", 0);
    add_exit("c8", "south", 0);
    add_exit("c4", "west", 0);    

    add_ground(); 

    add_item(({"crack", "chasm", "rent", "crevice"}),
              "It looks just as if someone has shattered the bedrock " + 
              "and opened a wide crack in the ground. " + 
              "Clouds of white-hot steam arises from the depths of the " +
              "crack. It is very wide -- a gaping, hungry mouth waiting "+
              "to swallow the unwary. You should not try to jump the "+
              "chasm unless you are very certain that you will be "+
              "successful.\n"); 
    add_item(({"mud", "boiling mud", "steam", "clouds", "water", "bottom"}),
        "The bottom of the chasm is shrouded in clouds of steam, but "+
        "you can see that there is a mass of boiling mud and water "+
        "here and there.\n");
    add_item(({"towering stones", "stones"}), "They are part of the "+
        "cliff wall, standing sentinel over the camp.\n");
}

int 
do_jump(string str)
{
    int jump_task;
    object tp = this_player(); 
    object to = this_object();    

    notify_fail("");
    if (!str || !strlen(str))    
        return 0;

    notify_fail("Jump what? The chasm?"); 
    if (!parse_command(str, ({ }), "[over] / [the] 'chasm' / 'crack'"))     
        return 0;

    jump_task = tp->resolve_task(TASK_SIMPLE, ({ TS_DEX, TS_DIS, SS_ACROBAT }));   
    if (jump_task < 0) 
        jump_task = 0;
  
    switch(jump_task)
    {
        case 0..20:
        if (tp->query_prop(JUMP_WARNED))
        {
            write("You take a few steps back and start running toward "+
                "the crack in the ground. You leap as strongly as you "+
                "can, but you miss the other side by a couple of feet "+
                "and fall into the crack!\nYou fall helplessly into "+
                "the dark depths of the chasm, landing in hot boiling "+
                "water. Your vision fades from your eyes and you are "+
                "paralyzed by excruciating pain...\n");
            say(QCTNAME(tp) + " tries to jump across the crack but "+
                "fails to reach the other side. " + 
                capitalize(tp->query_pronoun()) + " screams long and "+
                "horribly, followed by a deadly ominous silence.\n");
            tp->heal_hp(-(tp->query_max_hp()));
            if ((tp->query_hp() <= 0) && (!tp->query_ghost()))
                tp->do_die(to); 
            break;
        }
        else
        {
            tp->add_prop(JUMP_WARNED, 1);
            write("You take a few steps back and start running toward "+
                "the crack in the ground.\nAs you approach the edge "+
                "your courage fails you! The boiling mud and water "+
                "at the bottom of the crack does not look inviting.\n"+          
                "Your blood hammers in your head and you find yourself "+ 
                "wondering if trying to make the jump is worth your life.\n");
            say(QCTNAME(tp) + " takes a few steps back and starts "+
                "running toward the crack in the ground.\n"+  
                capitalize(tp->query_pronoun()) + " suddenly stops "+
                "short at the edge and stares down into the crack, "+
                "a frightened look on " + tp->query_possesive() + 
                " face.\n");    
            break;
        }
        case 21..40:
            tp->add_prop(JUMP_WARNED, 1);
            write("You take a few steps back and start running toward "+
                "the crack in the ground. As you approach the edge "+
                "you trip on a stone and land flat on your nose, "+
                "landing a few centimeters from the edge!\nYour blood "+
                "hammers in your head and you find yourself wondering "+
                "if trying to make the jump is worth your life.\n");
            say(QCTNAME(tp) + " takes a few steps back and starts "+
                "running toward the crack in the ground.\n"+  
                capitalize(tp->query_pronoun()) + " trips on a loose "+
                "stone and lands flat on " + tp->query_possesive() + 
                " nose, just a few centimeters from the edge.\n");    
            break;
        default:
            write("Confidently, you take a few steps back and run for "+ 
                "the crack in the ground, your eyes focused determin" +
                "edly on the opposite side.\nAt the last moment, at "+
                "the very edge of the chasm, you gather your strength "+
                "and leap across it, landing safely on the other side.\n");
            say(QCTNAME(tp) + " smiles confidently and takes a few "+
                "steps backward, then starts running for the chasm.\n "+ 
                "As " + tp->query_pronoun() +" reaches the crack "+ 
                QTNAME(tp)+ "'s muscles gather for a tremendous leap "+
                "that launches "+ tp->query_objective() +" safely "+
                "across.\n");
            if (tp->query_prop(JUMP_WARNED))
                tp->remove_prop(JUMP_WARNED);
            tp->move_living("jumping over the chasm", T_CAMP + "w1", 1, 0);   
            break;    
    }
    return 1;  
}

void
do_troloby_jump()
{
    object trol;

    if (trol = (present("troloby", this_object())))
    {
        trol->move_living("jumping over the chasm",  T_CAMP + "w1", 1, 0);   
        trol->command("assist nemur");
        return;
    }
    else
        call_other("/d/Avenir/common/holm/t_camp/c7", "do_troloby_jump");
    return;
}                                                                              

void
init()
{
    add_action(do_jump, "jump");
    add_action(do_jump, "leap");
    ::init();
}

	
