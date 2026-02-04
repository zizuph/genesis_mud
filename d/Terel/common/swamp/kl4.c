inherit "/d/Terel/common/swamp/kl";

#include <stdproperties.h>
#include <macros.h>
#include <filter_funs.h>

#define PATH "/d/Terel/common/swamp/"

#define TP   this_player()
#define TO   this_object()
#define ETP  environment(TP)

int aid;

/*
 * Function name: query_moving_object_list
 * Description:   return list of moving objects to clone at each reset.
 */
public string*
query_moving_object_list()
{
    return ({PATH + "kobold2", PATH + "kobold2",
             PATH + "kobold2", PATH + "chiefkob"});
}

public void
create_room()
{
   ::create_room();
   
   set_short("Lair tunnel");
   set_long("A dank and dismall tunnels, crudely formed. The " +
            "walls are more mud than stone. A small stream of " +
            "water fills the floor.\n");

   add_item("mud",   "Much of the tunnel is packed mud.\n");
   add_item("water", "It is stagnant and coats the floor.\n");
   add_item("walls", "Crudely carved from mud and stone.\n");
   add_item("stream",
            "A small stream of filthy water that runs through the cave.\n");
   add_exit(PATH + "kl2", "west", &CheckExit("west"));
   
   reset_room();
}

public void
do_stuff(object who)
{
    int i;
    object *o, m=0, f=0;
    
    o = FILTER_LIVE(all_inventory(TO));
    if (!sizeof(o))
        return;
    
    o -= FILTER_PLAYERS(o);
    if (!sizeof(o))
        return;
    
    if (sizeof(o) == 1) {
        o[0]->command("emote looks at you longingly.");
        return;
    }
    for (i=0; i<sizeof(o); i++) {
        if (o[i]->query_gender() == 0)
            m = o[i];
        else
            f = o[i];
    }
    
    if (m && f) {
        tell_room(TO, QCTNAME(f) + " kisses " + QTNAME(m) + ".\n");
    } else {
        if (!m) m = f;
        m->command("emote looks at you longingly.");
    }
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    
    if (!ob || !living(ob) || aid) return;
    
    aid = set_alarm(itof(3 + random(3)), itof(20 + random(20)), &do_stuff(ob));
}

public void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);
    
    if (!ob || !living(ob) || !aid) return;
    
    if (sizeof(FILTER_PLAYERS( all_inventory(TO) - ({ob}) ))) return;
    
    remove_alarm(aid);
    aid = 0;
}
