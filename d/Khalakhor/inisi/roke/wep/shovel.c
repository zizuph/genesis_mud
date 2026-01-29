/*
 * shovel.c
 *
 * Used in npc/undertaker.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

/*
  
  shovel.c - by Gresolle 1993

  the shovel is able to dig a hole in any room that hasn't 
  set one of the following properties:

  ROOM_I_NO_DIG   (see shovel.h)
  ROOM_I_TYPE     when type = 1,2 (water) or 3 (air)
  
  The shovel performs an add_my_desc in the room with
  the description "Someone has dug a hole here.", which
  refers to the master shovel object. It also calls
  add_item("hole",query_hole_desc()) in the room, thus
  adding the description set in the shovel by set_hole_desc()

  If there is an added item in the room called "hole" no digging
  takes place.

  If you add the property ROOM_I_DIG_FUN (shovel.h) to the
  room with a function name (text) the shovel will call
  that function with <where> as argument. Alse, that function
  will recieve a second argument, which is 0 if 'dig', 1 if 'fill'
  and '2' if enlarge. 

  dig syntax: dig <where> with <shovelobject>

  functions:

  create_shovel()   create the shovel

  set_hole_desc()   set the description of the created holes
  query_hole_desc() query hole description

*/

#pragma save_binary
#pragma strict_types

inherit "/std/weapon";
inherit "/lib/keep";

#include <macros.h>
#include <stdproperties.h>
#include "defs.h"
#include <cmdparse.h>
#include <wa_types.h>

/* hold the long description of the created holes */

string hole_desc;

int
filter_shovel(object ob)
{
    if (function_exists("create_shovel", ob) == MASTER && 
        environment(ob) == this_player())
        return 1;
    return 0;
}

void
set_hole_desc(string s)
{
    hole_desc = s;
}

string
query_hole_desc()
{
    return hole_desc;
}

int
do_dig(string s)
{
    string where, what;
    object *ob;

    if (!s)
        s = "here with " + query_name();

    notify_fail("Dig where with what?\n");
    if (!parse_command(s, this_object(), "%s 'with' %s", where, what))
        return 0;
  
    ob = CMDPARSE_ONE_ITEM(what, "filter_shovel", "filter_shovel");

    if (sizeof(ob))
        return ob[0]->dig(where);
    else
        return 0;
}

int
check_dig_fail(object where)
{
    int rt, il;
    mixed *obj_items;
    object hole;

    obj_items = where->query_item();

    for (il = 0; il < sizeof(obj_items); il++)
        if (member_array("hole", obj_items[il][0]) > -1)
        {
            notify_fail("But there is already a hole here!\n");
            return 1;
        }

    notify_fail("Someone has already dug a hole there!\n");

    hole = present("hole", where);
    if (hole && !hole->query_prop(CONT_I_CLOSED))
        return 1;

    notify_fail("Dig nowhere? Be serious...\n");
    if (!where)
        return 1;

    notify_fail("You can't dig here!\n");
    if (where->query_prop(ROOM_I_NO_DIG))
        return 1;

    if (where->query_prop(ROOM_I_INSIDE))
    {
        notify_fail("You can't dig inside.\n");
        return 1;
    }
    
    notify_fail("You can't dig in water!\n");
    rt = where->query_prop(ROOM_I_TYPE);

    if (rt == 1 || rt == 2)
        return 1;

    notify_fail("You can't dig in air!\n");
    if (rt==3)
        return 1;

    return 0;
}

int
dig(string where)
{
    object digob, hole;
    string funct;

    if (!where)
        where = "here";

    digob = environment(this_player());
    if (!digob)
        return 0;

    if (funct = digob->query_prop(ROOM_I_DIG_FUN))
    {
        return call_other(digob, funct, where, 0, 0);
    }

  
    if (where == "here")
    {
        if (check_dig_fail(digob))
            return 0;

        this_player()->catch_msg("You dig a hole in the ground.\n");
        say(QCTNAME(this_player()) + " digs a hole in the ground.\n");

        seteuid(getuid(this_object()));

        hole = present("hole", digob);

        if (hole)
        {
            hole->remove_prop(CONT_I_CLOSED);
            //hole->enter_env(digob, 0);
            hole->set_long(query_hole_desc());
        }
        else
        {
            hole = clone_object(HOLEFILE);
            hole->move(digob);
            hole->set_long(query_hole_desc());
        }
        return 1;
    }

    return 0;
}

int
fill(string where)
{
    object hole, etp;
    string dig_fn;
  
    etp = environment(this_player());

    hole = present("hole", etp);
  
    notify_fail("Yeah right! Try to fill a non-existant hole!\n");
    if (!hole && 
        !(dig_fn = etp->query_prop(ROOM_I_DIG_FUN)))
        return 0;

    if (dig_fn)
        return call_other(etp, dig_fn, where, 1, 0);

    if (hole->query_prop(CONT_I_CLOSED))
        return 0;

    this_player()->catch_msg("You fill the hole.\n");
    say(QCTNAME(this_player()) + " fills the hole with dirt.\n");

    hole->add_prop(CONT_I_CLOSED, "What?\n");
    hole->set_long("You find no hole.\n");
    //    hole->leave_env(environment(this_player()), 0);

    return 1;
}

int
do_fill(string s)
{
    string where, what;
    object *ob;

    if (!s)
        s = "hole with " + query_name();

    notify_fail("Fill what with what?\n");
    if (!parse_command(s, this_object(), "%s 'with' %s", where, what))
        return 0;
  
    ob = CMDPARSE_ONE_ITEM(what, "filter_shovel", "filter_shovel");

    notify_fail("I would like to see you fill _that_ with the " +
                query_name() + ".\n");
    /*  if (where != "hole")
        return 0;
    */
    if (sizeof(ob))
        return ob[0]->fill(where);
    else
        return 0;
}

int
do_enlarge(string s)
{ 
    string where, what;
    object *ob;

    if (!s)
        s = "hole with " + query_name();

    notify_fail("Enlarge what with what?\n");
    if (!parse_command(s, this_object(), "%s 'with' %s", where, what))
        return 0;
  
    notify_fail("That is not possible to enlarge!\n");
    if (where != "hole")
        return 0;

    ob = CMDPARSE_ONE_ITEM(what, "filter_shovel", "filter_shovel");

    if (sizeof(ob))
        return ob[0]->enlarge(where);
    else
        return 0;
}

int
enlarge(string where)
{
    object hole, etp, dig_fn;

    etp = environment(this_player());

    hole = present("hole", etp);

    notify_fail("Enlarge what hole?\n");
    if (!hole &&
        !(dig_fn = etp->query_prop(ROOM_I_DIG_FUN)))
        return 0;

    if (dig_fn)
        return call_other(etp, dig_fn, where, 2, 0);

    if (hole->query_prop(CONT_I_CLOSED))
        return 0;

    this_player()->catch_msg("You enlarge the hole a little.\n");
    say(QCTNAME(this_player()) + " enlarges the hole.\n");

    hole->add_prop(CONT_I_MAX_VOLUME, hole->query_prop(CONT_I_MAX_VOLUME) * 2);
    hole->add_prop(CONT_I_MAX_WEIGHT, hole->query_prop(CONT_I_MAX_WEIGHT) * 2);

    return 1;
}

void create_shovel(){}

nomask void
create_weapon()
{
    set_name("shovel");
    set_adj("nice");
    set_short("nice shovel");
    set_long("A nice shovel, usable for digging holes.\n");

    set_hit(10);
    set_pen(10);
    set_hands(W_BOTH);
    set_wt(W_POLEARM);
    set_dt(W_BLUDGEON);

    add_prop(OBJ_I_WEIGHT, 5000);
    add_prop(OBJ_I_VOLUME, 2500);

    set_hole_desc("It's a rather large hole.\n");

    create_shovel();
    set_keep();
}

void
init()
{
    ::init();

    add_action(do_dig, "dig");
    add_action(do_fill, "fill");
    add_action(do_enlarge, "enlarge");
}
