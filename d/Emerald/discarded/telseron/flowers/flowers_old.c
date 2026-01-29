/*
 *  The basic flower flower file.
 *  It is based on /std/herb.c, originally created by 
 *  Elessar Telcontar of Gondor, from April to July of 1992
 *
 */
 
inherit "/std/object";
 
#include "/d/Emerald/defs.h"
#include <cmdparse.h>
#include <composite.h>
#include <files.h>
#include <language.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
 
/*
 * Prototypes used
 */ 
int wilt();
 
/*
 * Variables used
 */
 
string   flower_name;
int      wilt_time, wilt_left, wilt_stopped, wilt_alarm;
int      flower_value, is_fragrant, inited_once; 
 
 
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
 * Description:   Sets wheter flower is fragrant or not
 * Arguments:     i - 0 = not fragrant, 1 = yes it's fragrant
 */
void
set_fragrance(int i) { is_fragrant = i; }
 
/*
 * Function name: set_flower_value
 * Description:   Set the value of the flower
 * Arguments:     i - The value
 */
void
set_flower_value(int i) { flower_value = i; }
 
 
 
/*
 * Function name: set_wilt_time
 * Description:   Set the wilting time of the flower
 * Argumetns:     i - The time (in seconds)
 */
void
set_wilt_time(int i) { wilt_time = i; }
 
/*
 * Function name: query_wilt_time
 * Description:   Checks how long it takes for the flower to wilt
 * Returns:       The time in seconds
 */
int                             
query_wilt_time() { return wilt_time; }
 
 
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
            "fragrance of the " + short() + ". You smile " +
            "as you enjoy the lingering perfume.\n");
        say (QCTNAME(this_player()) + " smells a flower.\n");
        return 1;
    }
    else
    {
        write ("You close your eyes to smell the " + short() + 
            ". It seems it isn't fragrant after all. " +
            "Nonetheless, it's still a pretty flower.\n");
        (QCTNAME(this_player()) + " tries to smell a flower.\n");
        return 1;
    }
}
 
 
/*
 * Function name: wilt
 * Description:   This function is called with an alarm, and simulates the
 *                wilting of flowers
 */
int
wilt()
{
    object env;
    string mess;
 
    wilt_alarm = 0;
 
    if (env = environment())
    {
        mess = "The " + short() + " slowly dries up and dies from lack " +
            "of water.\n";
        if (living(env))
            tell_object(env, mess);
        else if (env->query_prop(ROOM_I_IS))
            tell_room(env, mess);
    }
            
    remove_object();
    return 1;
}
 
 
void
enter_env(object dest, object old)
{
 
    if (dest && living(dest) && !inited_once)
    {
        if (wilt_time)
            wilt_alarm = set_alarm(itof(wilt_time), 0.0, wilt);
        inited_once = 1;
    }
 
    ::enter_env(dest, old);
}
 
/*
 * Function name: create_flower
 * Description:   This is the create-function of for flowers. Redefine 
 *                and set the flower up from this function.
 */
 
void
create_flower() {}
 
nomask void
create_object()
 
{
    set_name("ugly flower");
    set_short("ugly flower");
    add_name("flower");
    set_pname("flowers");
    set_adj("yellow");
    set_long("This is an ugly weed flower.\n");
    set_flower_value(10);
    set_wilt_time(500);
    set_fragrance(0);
 
    add_prop(OBJ_I_VALUE,   0);
    add_prop(OBJ_I_WEIGHT, 25);
    add_prop(OBJ_I_VOLUME, 25);
    create_flower();
}
