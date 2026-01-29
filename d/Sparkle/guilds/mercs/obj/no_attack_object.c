/*
 * /d/Genesis/guilds/merc/obj/retreat_object.c, by Morrigan October, 2002
 * 
 * This object is to allow for the environment to use the 'retreat' 
 *     command, as relevant to the mercenary guild special 'advance'.
 */

inherit "/std/object";

#include "/d/Krynn/common/defs.h"
#include "../merc.h"
#include <stdproperties.h>
#include <composite.h>
#include <cmdparse.h>
#include <macros.h>

int gDuration = 5, gFailed = 0;
object gAdvancer, gRetreater, gRoom;

public void set_duration(int i) { gDuration = i; }
public void set_advancer(object ob) { gAdvancer = ob; }
public void set_retreater(object ob) { gRetreater = ob; }
public void set_noatt_room(object ob) { gRoom = ob; }
public int query_duration() { return gDuration; }
public object query_advancer() { return gAdvancer; }
public object query_retreater() { return gRetreater; }
public object query_noatt_room() { return gRoom; }

public void remove_noatt_stun() { E(TO)->remove_stun(); }

public void no_attack_duration_exceeded()
{
    E(TO)->remove_prop(OBJ_M_NO_ATTACK);
    remove_object();
}

public mixed check_noatt_prop()
{
    if (!objectp(query_advancer()) || gFailed)
    {
        gFailed = 1;
	return 0;
    }

    if (E(query_advancer()) == E(query_retreater()) &&
	query_noatt_room() == E(query_retreater()))
    {
    return query_advancer()->query_The_name(TP)+
        " is standing between you and "+
        query_retreater()->query_the_name(TP)+", preventing your attack.\n";
    }

    gFailed = 1;
    return 0;
}

public void create_object()
{
    set_name("_merc_no_attack_object_");
    set_short("_merc_no_attack_object_");
    set_long("This object should not be visible.");
    add_prop(OBJ_M_NO_DROP, "The poster cannot be taken.\n");
    set_no_show();
}

public void setup_noatt_object()
{
    set_noatt_room(E(E(TO)));
    E(TO)->add_stun();
    E(TO)->add_prop(OBJ_M_NO_ATTACK, &check_noatt_prop());
}

public void init()
{
    ::init();

    set_alarm(0.1, 0.0, &setup_noatt_object());
    set_alarm(5.0, 0.0, &remove_noatt_stun());
    set_alarm(10.0, 0.0, &no_attack_duration_exceeded());
}
