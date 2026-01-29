/*
 * Standard flower for flowers
 * A simple heap object.
 */

inherit "/std/heap";

#include "/d/Faerun/defs.h"
#include "flowers.h"
#include <stdproperties.h>
#include <macros.h>

int is_fragrant; 
int yes = 1, no = 0;

void set_fragrance(int i);

void create_flower() {}
string
flower_long()
{
    return "The " + short() +  
        IS_ARE + "dark and ugly. " + CIT_THEY + 
        "bugged if you are getting this description.\n";
}

void
create_heap()
{

    set_heap_size(1);
    add_name("weed");
    add_name("flower");
    add_pname("flowers");

    set_adj(({"dark","ugly"}));

    set_long(flower_long);
    set_fragrance(1);

    add_prop(OBJ_M_NO_SELL, 1);

    add_prop(HEAP_S_UNIQUE_ID, "faerun_flower_weed");

    add_prop(HEAP_I_UNIT_WEIGHT, 5);
    add_prop(HEAP_I_UNIT_VOLUME, 3);
    add_prop(HEAP_I_UNIT_VALUE, 20);

    create_flower();
}    

/* 
 * This is called when an autoloading object is reloaded.  We use
 * it to restore the heap to it's correct size.
 */
void
init_arg(string arg)
{
    set_heap_size(atoi(arg));
}

/*
 * This is called when the player is logging out.  We use it to
 * store the size of the heap so that we can restore it to the right
 * amount when the player logs back in.
 */
string
query_auto_load()
{
    return MASTER + ":" + num_heap();
}

/*
 * Function name: smell_flower
 * Description:   Lets player smell the flower
 * Returns:       none
 */
 int smell_flower(string str)
{
    NF ("Smell which flower?\n");
    if (is_fragrant == 1)
    { 
        write ("You close your eyes and smell the heady " +
            "fragrance of " + short() + ". You smile " +
            "as you enjoy the lingering perfume.\n");
        say (QCTNAME(this_player()) + " smells a flower.\n");
        return 1;
    }
    else
    {
        write ("You close your eyes to smell " + short() + 
            ". It seems it isn't fragrant after all. " +
            "Nonetheless, it's still a pretty flower.\n");
        (QCTNAME(this_player()) + " tries to smell a flower.\n");
        return 1;
    }
}



/*
 * Function name: init
 * Description:   inits actions
 */
void
init()
{
   add_action("smell_flower", "smell"); 
   ::init(); 
}

 
/*
 * Function name: set_fragrance
 * Description:   Sets whether flower is fragrant or not
 * Arguments:     i - 0 = not fragrant, 1 = yes it's fragrant
 */
void set_fragrance(int i) { is_fragrant = i; }
