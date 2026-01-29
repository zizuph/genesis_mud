/*
* Nice Cigar sold in the Rich Men's Bar
* Coded by Conan Jan -95
*
* Modifications:
* Petros, November 20, 2015
* - added parsing using PARSE_COMMAND_ONE
* - use a single alarm so that people can't keep spawning alarms.
*
*/

inherit "/std/object";

#include "defs.h"
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <composite.h>
#include <cmdparse.h>
#include <filter_funs.h>

private int MAX_PUFFS = 5;
private int inhale_alarm = 0;
private int puffs = 0;

// Prototypes
public int inhale();

void
create_object()
{
    set_name("cigar");
    set_adj("fat");
    
    set_short("fat cigar");
    set_pshort("fat cigars");
    set_long("This fat cigar is a symbol of your wealth. " +
             "You can <light cigar> to enjoy its flavour.\n");
    
    add_prop(OBJ_I_WEIGHT, 50);
    add_prop(OBJ_I_VOLUME,100);
    add_prop(OBJ_I_VALUE,  15);
    
    seteuid(getuid(TO));
}

void
init()
{
    ::init();
    
    add_action("smoking","light");
}

int
smoking(string str)
{
    NF("Light what?\n");

    object target = PARSE_COMMAND_ONE(str, this_player(), "[the] %i");
    if (target == this_object())
    {
        if (inhale_alarm != 0 && get_alarm(inhale_alarm) != 0)
        {
            write("You are already smoking your cigar!\n");
            return 1;
        }
        write("You light your cigar and start to inhale the lovely smoke.\n");
        inhale_alarm = set_alarm(20.0, 0.0, "inhale");
        
        return 1;
    }
  
    return 0;
}

int
inhale()
{
    if (!objectp(this_player()))
    {
        return 1;
    }
    write("You inhale the smoke from your cigar, you feel relaxed and "+
          "eased at mind.\n");
    say(QCTNAME(TP)+" smokes on "+HIS_HER(TP)+" cigar and creates almost perfect "+
        "rings of smoke.\n");
    
    // Increment the number of puffs. We only allow 5 puffs.
    puffs++;
    if (puffs >= MAX_PUFFS)
    {
        inhale_alarm = set_alarm(20.0, 0.0, "nomore");
    }
    else
    {
        inhale_alarm = set_alarm(20.0, 0.0, "inhale");
    }

    return 1;
}

int
nomore()
{
    if (!objectp(this_player()))
    {
        return 1;
    }
    write("You take the last smoke on the cigar and then you drop it on "+
          "the ground, stomping on it to make sure it isn't lit.\n");
    say(QCTNAME(TP)+" takes "+HIS_HER(TP)+" last smoke on the cigar, "+
        "then drops it and stomps on it to make sure it isn't lit.\n");
    TO->remove_object();
    
    return 1;
}
