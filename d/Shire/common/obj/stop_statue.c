/*
 * /d/Shire/common/obj/stop_statue.c
 *
 * This was originally coded in 1992 or so, probably by Tricky, 
 * since it was designed for the Hin Warrior Guild.
 *
 * The quest to obtain it was closed long, long ago.
 *
 * Modifications:    Lilith Dec 2007
 *                   Updated the statue so that it calls init_living()
 *                   when it departs, so that any aggressive npcs in
 *                   the room reinitiate combat as the aggressive 
 *                   code intends. Doesn't make sense to have them 
 *                   standing around stupidly while players pick them
 *                   off one-by-one, esp with a 'free' spell that most
 *                   guilds pay a fair amount of tax for.
 *
 *                   This change put in effect 2008-05-13 by Toby
 *                   Many thanks Lilith, a big hug to you!
 *                   
 */
inherit "/std/object";

#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include <filter_funs.h>
//  Prototypes
void half_way();
void self_destruct();
int  query_time_left();


mixed no_m_att, no_att;
int destruct_id, half_way_id, recheck_id;


void
create_object() {
   set_name(({"statue","statuette","statuette of nob nar"}));
   set_short("statuette of Nob Nar");
   set_pshort("statuettes of Nob Nar");
   set_long(break_string(
      "You are looking at the statuette of the Great Nob Nar, "
    + "founder of the glorious Hin Warrior Guild. An air of "
    + "peace and tranquility emanates from the statue.\n", 70));

   add_prop(OBJ_M_NO_GET,"@@my_get");
   add_prop(OBJ_S_WIZINFO,"@@wizinfo");
}

string
my_get() {
   object tp;

   tp = this_player();
   say(QCTNAME(tp) + " is struck by a lightning bolt for trying "
     + "to steal the statuette.\n",tp);

   /*
    * Do 10% damage as punishment. Bananaman, being a suicidal maniac,
    * asked for this. ;-)
    */
   tp->heal_hp(-1);
   return "You are struck by a lightning bolt when you try to get the "
        + "statuette.\n";
}

/*
 * Function name:   stop_fights
 * Description:     Stop all fighting in the room 
 *                  This is called via set_alarm 15 seconds after original peace.
 *                  Added since some guild specials by-pass peace via attack_object()
 * Arguments:       
 */

void 
stop_fights() 
{
   object *ob_arr;
   int i;

   ob_arr = FILTER_LIVE(all_inventory(environment()));

   /* Make 'em all stop */
   for (i=0; i < sizeof(ob_arr); i++)
      ob_arr[i]->stop_fight(ob_arr);

}
/*
 * Function name:   make_peace
 * Description:     Stop all fighting in the room and set properties
 *                  to make sure it stays peacefully.
 * Arguments:       active_time: The number of seconds the peace has to last.
 */
void
make_peace(int active_time) {
   object env = environment();

   no_att = env->query_prop_settings(ROOM_I_NO_ATTACK);
   no_m_att = env->query_prop_settings(ROOM_I_NO_MAGIC_ATTACK);
   env->add_prop(ROOM_I_NO_ATTACK, 1);
   env->add_prop(ROOM_I_NO_MAGIC_ATTACK, 1);
   half_way_id = set_alarm(itof((active_time*3)/4),0.0,&half_way());
   destruct_id = set_alarm(itof(active_time),0.0,&self_destruct());

   stop_fights();
   // This added since some guild specials by-pass peace via attack_object()
   // 15 seconds should be enough of a delay to call it again.
   recheck_id = set_alarm(15.0,0.0,&stop_fights());
}

int
filter_living(object obj)
{
   return living(obj);
}

void
half_way() {
   remove_alarm(half_way_id);
   tell_room(environment(),
      "The statue starts to show some cracks on its surface.\n");
}

int
remove_statue() {
    object env, size;
    object *liv;
   
    int i, j;
   
    if (env = environment())
    {
        env->add_prop(ROOM_I_NO_ATTACK, no_att);
        env->add_prop(ROOM_I_NO_MAGIC_ATTACK, no_m_att);
        tell_room(env, break_string(
         "The statue crumbles and falls apart. The air of peace and "
         + "tranquility is gone.\n", 70));
    }

    liv = 0;
    liv = filter(all_inventory(environment()), "filter_living", this_object());
    if(sizeof(liv) > 1)   
        for (i=0;i<sizeof(liv);i++)
        {
            set_this_player(liv[i]);
            for (j=0;j<sizeof(liv);j++)   
            {
                liv[j]->init_living();
            }
        }

    ::remove_object();
}

void
self_destruct() {
   remove_alarm(destruct_id);
   remove_alarm(recheck_id);
   remove_statue();
}

string
wizinfo() {
   return break_string(
     "This statuette is a magic object brought about by the Hin Warrior "+
     "peace spell. It will fall apart in "+query_time_left()+
    " seconds.\n",70);
/*
      "This statuette ensures the peace in this room. It will fall apart in "
    + query_time_left() + " seconds.\n",70);
*/
}

int
query_time_left()
{
   mixed *call;

   call = get_alarm(destruct_id);
   return ftoi(call[2]);
}

