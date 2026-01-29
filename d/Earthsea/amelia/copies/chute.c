
 /*      Ice chute for quick travel 

   coder(s):     Digit
   history:      25.7.95     bug removed      Maniac
                 12/3/95     descr modified   Maniac
                 29.2.95     Modified - Maniac
                 23/2/95     created - Digit
   purpose:      connects hallway with bottom tunnel
   exits:        just down :)
   objects:      none
   npcs:         none
   quests:       none
   special:      Calls SET_PC function in TOP room when done
   to do:        nothing now
   bugs:         none known
 */

inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include <filter_funs.h>
#include <language.h>
#include "tunnels.h"

#define TOP "/d/Calia/mountain/cr_tunnel/rooms/hallway"
#define BOTTOM "/d/Calia/mountain/lower_tunnel/tun11"

object *going_down = ({ });

string *down_msgs = ({
           "Whee! You speed further down the ice chute.\n",
           "You whizz around a bend at high speed.\n",
           "Wow! Nearly took off there, better put the skids on!\n",
           "You continue down the ice chute rapidly.\n",
           "You're picking up even more speed, this is scary!\n" });


void
create_room()
{

    set_short("Sliding down an ice chute");
    set_long("You are sliding down a spiralling ice chute.  The walls "+
       "of the chute are very cold to the touch.\n");
    add_prop(ROOM_I_LIGHT,1);
    add_prop(ROOM_I_IS,1);
    add_prop(ROOM_I_INSIDE,1);
}


void
enter_inv(object ob, object from)
{
    int alive;

    ::enter_inv(ob, from);
    if (member_array(ob, going_down) == -1) {
        alive = living(ob);
        set_alarmv(1.0, 0.0, "down_chute", ({alive, ob, 0})); 
    }
}

void
down_chute(int alive, object ob, int stage)
{
    /* Player quit or object removed somehow */
    if (!ob) {
        going_down -= ({0});
        if (alive)
            TOP->set_pc(0);
        return;
    }
 
    if (environment(ob) != this_object()) /* linkdead or something */
    {
        going_down -= ({ ob });
        if (alive) 
            TOP->set_pc(0);
        return;
    }
        
    if (stage > 4) {
        if (living(ob)) {
          ob->catch_msg("You reach the bottom of the chute and fall "+
             "flat on your butt as you hit the ground.  You stand up "+
             "immediately.\n");
          tell_room(BOTTOM,QCTNAME(ob)+" flies out of the ice chute and "+
             "lands flat on "+ob->query_possessive()+" butt.\n", ob);
          TOP->set_pc(0);
          ob->move_living("M",BOTTOM);
        }
        else {
            tell_room(BOTTOM, capitalize(LANG_ASHORT(ob)) + 
                   " drops out of the " +
                   "ice chute.\n");        
            ob->move(BOTTOM);
        }
        going_down -= ({ob}); 
        return;
    }

    if (living(ob))
      ob->catch_msg(down_msgs[random(sizeof(down_msgs))] + "\n\n\n"); 
    set_alarmv(2.5, 0.0, "down_chute", ({alive, ob, stage+1})); 
}

