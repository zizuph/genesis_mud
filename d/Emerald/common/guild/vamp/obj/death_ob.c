inherit "/std/object";

#include "../guild.h"
#include <macros.h>
#include <stdproperties.h>

#define TELL(x) environment()->catch_tell("\n" + x + "\n")

static int i = 0;

void create_object()
{
    set_name("vamp_death_ob");
    set_no_show();
  
    remove_prop(OBJ_I_VOLUME);
    remove_prop(OBJ_I_VALUE);
    remove_prop(OBJ_I_WEIGHT);
    add_prop(OBJ_M_NO_DROP, "");
    add_prop(OBJ_M_NO_SELL, "");
    add_prop(OBJ_M_NO_BUY, "");
}

string query_auto_load()
{
    return MASTER + ":" + MAX(i - 1, 0);
}

void init_arg(string arg)
{
    i = atoi(arg);
}

static void heal_msg()
{
    string dest;

    if (!environment() || !interactive(environment()))
    {
        return;
    }
  
    switch (i++)
    {
        case 0:
            break;
    
        case 1:
            TELL("You begin to feel a faint tickle.  Feeling nothing " +
                "else, however, it may be just your imagination.");
            break;
    
        case 2:
            TELL("The tickling becomes more intense, but still " +
                "it is difficult to know if you are imagining it or " +
                "actually feeling it.");
            break;
    
        case 3:
            TELL("As you begin to feel the familiar weight of your " +
                "undead flesh, your entire body is consumed with a " +
                "raging itch.");
            break;
    
        case 4:
            TELL("You become aware of your extremities, tingling and " +
                "itching with an unimaginable intensity.  Still you " +
                "are helpless, though...unable to move or perceive " +
                "beyond the tortuous sensations raging through you.");
            break;
    
        case 5:
            TELL("Just as you feel you are about to lose your mind " +
                "to this agony, it fades--almost unnoticeable " +
                "underneath the rush of sensations as you stir at last.");
      
            environment()->remove_ghost(1);
      
            setuid();
            seteuid(getuid());
      
            if (dest = 
                LAIR_MANAGER->query_lair(environment()->query_vamp_coven()))
            {
                environment()->move_living(0, dest);
            }
            else
            {
                environment()->move_living(" appears from the shadows",
                    environment()->query_default_start_location());
            }
      
            remove_object();
            break;
    
        default:
            i = 1;
            break;
    }
}

init()
{
    int time;
  
    if (!TP->query_ghost())
    {
        remove_object();
        return;
    }
  
    ::init();
  
    TP->move_living(0, VAMP_ROOM_DIR + "death_room");
  
    time = MAX(20, 80 - TP->query_vamp_stat());
  
    set_alarm(1.0, itof(time), heal_msg);
}
