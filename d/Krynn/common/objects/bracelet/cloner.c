/*
 * This object clones the Bracelet of Charms and moves it
 * to a suitable location.
 */
#pragma no_clone
#pragma strict_types

inherit "/std/object";

#include <stdproperties.h>

#define BRACELET "/d/Krynn/common/objects/bracelet/bracelet"

string *files = ({
    "/d/Krynn/solace/new_village/npc/shindig",
        "/d/Krynn/qualinesti/npc/qualthas",
        "/d/Krynn/pax/monster/verminaard",
        "/d/Krynn/haven/dwarf_camp/npc/colin",        
        //        "/d/Krynn/solamn/splains/living/highlord",
        "/d/Krynn/icewall/castle2/npc/fael-thas",
        "/d/Ansalon/balifor/flotsam/living/d_officer",
        "/d/Ansalon/kalaman/living/calof", 
        "/d/Ansalon/balifor/steppe/living/warrior" });

void reset_object();

void
create_object()
{
    set_name("cloner");
    set_short("cloner");

    enable_reset(120);

    setuid();
    seteuid(getuid());

    reset_object();
}

int
count_unique(string item)
{
    object ob, *obs;
    
    if (!objectp(ob = find_object(item)))
        return 0;
    
    obs = object_clones(ob);
    obs -= filter(obs, &->query_prop(OBJ_I_BROKEN));
    
    return sizeof(obs);
}

void
reset_object()
{
    object ob, *obs, *targets, target;
    int index;
    
    if (count_unique(BRACELET) >= random(3))
        return;
    
    targets = ({ });

    obs = map(files, find_object) - ({ 0 });
    index = sizeof(obs);
    while (index--)
    {
        targets += object_clones(obs[index]);
    }


    /* We don't want a number of npcs with lots of bracelets */
    if (objectp(ob = find_object(BRACELET)))
    {
        obs = object_clones(ob);
        targets -= map(obs, environment);
    }
    
    if (!(index = sizeof(targets)))
        return;

    target = targets[random(index)];
    
    ob = clone_object(BRACELET);
    ob->move(target);
}
