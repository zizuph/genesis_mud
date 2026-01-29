/*
 * Originally a statuette of Nob Nar of the Hin Guild
 * Rewrote it as a statuette of a peace lily
 * Finwe January 2004
 */

inherit "/std/object";
#include "/d/Shire/sys/defs.h"

#include "/sys/stdproperties.h"
#include "/sys/macros.h"
//  Prototypes
void half_way();
void self_destruct();
int  query_time_left();


mixed no_m_att, no_att;
int destruct_id, half_way_id;

void
create_object() 
{
    set_name(({"statue","statuette","statuette of a serene human"}));
    set_short("statuette of a serene human");
    set_pshort("statuettes of a serene human");
    set_long("This is a statuette of a serene human. It has been carve " +
        "from a block of marble and is very life-like. The human wears a " +
        "loose robe with the cowl thrown back. Its face is peaceful " +
        "and its eyes are closed. Both arms cross the chest with the " +
        "hands meeting and clasped together. A large white lily lays " +
        "at its feet. An air of peace and tranquility emanates from " +
        "the statue.\n");

    add_item(({"lily", "white lily", "large white lily"}),
        "The large white lily lays at the feet of the serene human. " +
        "The flower has six points and a long, graceful stem. It is " +
        "very life-like and delicately carved from pure white marble " +
        "and contrasts with the rest of the statue.\n");
    add_item(({"robe", "loose robe"}),
        "The robe hangs from the serene human loosely. It reaches to " +
        "the ground, concealing the body completely. There are natural " +
        "looking folds and wrinkles in the robe. The hood has been " +
        "thrown back behind the head.\n");
    add_item(({"cowl", "hood"}),
        "The hood has been thrown back behind the head. It is round " +
        "and oversized as reaches halfway down the back.\n");
    add_item(({"face"}),
        "The face is very calm looking. Loose, curly hair frames the " +
        "face and cascade gracefully down to the shoulders. The eyes " +
        "are closed. The face looks strong and proud though, yet gentle " +
        "and wise.\n");
    add_item(({"arms"}),
        "The arms of the statue are raised to the chest and horizontal " +
        "to the body. The robe covers both arms completely and hangs " +
        "loosely from the body.\n");
    add_item(({"fingers", "hands"}),
        "Both hands meet together and the fingers alternately cross " +
        "each other in a prayerful mode. The hands and fingers are " +
        "strong yet delicate looking. Every ridge and wrinkle has been " +
        "expertly carved into them, making this a piece of art.\n");

    add_prop(OBJ_M_NO_GET,"@@my_get");
    add_prop(OBJ_S_WIZINFO,"@@wizinfo");
}

string
my_get() 
{
    say(QCTNAME(TP) + " is struck by a lightning bolt as "+ HE_SHE(TP) + 
        " reaches out and tries to take the statuette.\n",TP);

   /*
    * Do 10% damage as punishment. Bananaman, being a suicidal maniac,
    * asked for this. ;-)
    */
    TP->heal_hp(-1);
    return "You are struck by a lightning bolt as your reach out and " +
        "try to take the statuette.\n";
}

/*
 * Function name:   make_peace
 * Description:     Stop all fighting in the room and set properties
 *                  to make sure it stays peacefully.
 * Arguments:       active_time: The number of seconds the peace has to last.
 */
void
make_peace(int active_time) 
{
    object *ob_arr, env;
    int i;

    ob_arr = all_inventory(env = environment());
    ob_arr = filter(ob_arr,"filter_living",this_object());

   /* Make 'em all stop */
    for (i=0; i < sizeof(ob_arr); i++)
        ob_arr[i]->stop_fight(ob_arr);

    no_att = env->query_prop_settings(ROOM_I_NO_ATTACK);
    no_m_att = env->query_prop_settings(ROOM_I_NO_MAGIC_ATTACK);
    env->add_prop(ROOM_I_NO_ATTACK, 1);
    env->add_prop(ROOM_I_NO_MAGIC_ATTACK, 1);
    half_way_id = set_alarm(itof((active_time*3)/4),0.0,&half_way());
    destruct_id = set_alarm(itof(active_time),0.0,&self_destruct());
}

int
filter_living(object obj)
{
    return living(obj);
}

void
half_way() 
{
    remove_alarm(half_way_id);
    tell_room(environment(),
        "Fine lines and cracks begin to form on the surface of the " +
        "statuette.\n");
}

int
remove_object() 
{
    object env;

    if (env = environment())
    {
        env->add_prop(ROOM_I_NO_ATTACK, no_att);
        env->add_prop(ROOM_I_NO_MAGIC_ATTACK, no_m_att);
        tell_room(env, "The statue crumbles and falls apart. The air " +
            "of peace and tranquility is gone.\n");
    }
    ::remove_object();
}

void
self_destruct() 
{
    remove_alarm(destruct_id);
    remove_object();
}

string
wizinfo() 
{
    return "This statuette is a hallowed object. It prevents discord " +
        "from arising and will fall apart in " + query_time_left() +
        " seconds.\n";
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
