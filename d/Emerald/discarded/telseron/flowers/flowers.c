/*
 *  The basic flower file.
 *  It is based on /std/herb.c, originally created by 
 *  Elessar Telcontar of Gondor, from April to July of 1992.
 *  As such, many of the routines are based on the same routines
 *  as herb.c.
 *
 *  Written by Finwe
 *
 *
 * This is designed to be inherited into any flower that is 
 * used by the garden in Telseron. As such, certain characteristics
 * have been written into this file to make it easier to use the
 * flowers. 
 * 
 * Creating flowers is designed to be a simple process. As an example,
 * the bird of paradise flower (BOP.C) is written like this:
 *
 * inherit "/d/Emerald/telseron/flowers/flowers.c";
 * #include "/sys/language.h"
 * #include "/sys/wa_types.h"
 * #include "/sys/stdproperties.h"
 * #include "/sys/macros.h"
 * 
 * public void
 * create_flower()
 * {
 * 
 *     set_name("bird of paradise");
 *     set_short("flower");
 *     set_short("bird of paradise flower");
 *     set_pname("bird of paradise flowers");
 *     set_fragrance(0);
 *     set_adj("beautiful");
 *     set_long("This lovely flower is shaped like a tropical " +
 *         "bird. It has a colourful crown and a beak-like tip.\n");
 *     set_wilt_time(500);
 *     set_flower_value(25);
 * }
 *
 *
 * Below are the functions used.:
 *
 * wilt                 -  starts the wilting process of the flower
 * set_wilt_time        -  sets the wilting time of the flower
 * query_wilt_time      -  checks how long it takes for the flower to wilt
 * stop_wilt            -  disables wilt time
 * start_wilt           -  begins wilt time
 * set_fragrance        -  sets whether flower is fragrant or not 
 * set_flower_value     -  sets the value of the flower
 * smell_flower         -  lets player smell the flower
 * create_flower        -  creates the flower
 *
 * Flowers will stop wilting when placed in a vase. Vases are available
 * at the florist.
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

#define EMERALD_FLOWER          "_garden_flower"
 
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
 * Function name: stop_wilt
 * Description:   halts the wilting process of the flower temporarily.
 *                use start_wilt to have the flower resume wilting.
 */
void
stop_wilt(object obj)
{
    if (!inited_once || wilt_stopped)
        return;
    wilt_left = ftoi(get_alarm(wilt_alarm)[2]);
    remove_alarm(wilt_alarm);
    wilt_alarm = 0;
    wilt_stopped = 1;
} 
 
 
/*
 * Function name: restart_wilt
 * Description:   Starts the wilting process of a flower
 *                by stop_wilt.
 */
void
restart_wilt(object obj)
{
  if (!wilt_stopped) return;
  wilt_alarm = set_alarm(itof(wilt_left), 0.0, wilt);
  wilt_stopped = 0;
}
 
 
/*
 * Function name: start_wilt
 * Description:   Start the wilt process of a herb
 */
void
start_wilt(object obj)
{
    if (!inited_once)
    {
        if (wilt_time)
            wilt_alarm = set_alarm(itof(wilt_time), 0.0, wilt);
        inited_once = 1;
    }
}
 
 
/*
 * Function name: set_fragrance
 * Description:   Sets whether flower is fragrant or not
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
