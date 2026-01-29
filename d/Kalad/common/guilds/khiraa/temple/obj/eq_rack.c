#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/guilds/khiraa/khiraa_defs.h"
#include <composite.h>
#pragma strict_types
#pragma save_binary

inherit "/std/object";

/* The equipment rack of the Khiraa */
/* Sarr 2.Apr.97 */

object storage_room;

int is_weapon(object ob);
int is_other(object ob);
int is_armour(object ob);
int do_rack_items(string str);
void rack_weapons(object *obs);
void rack_armours(object *obs);
void rack_others(object *obs);


void 
load_storage_room()
{
    if(!objectp(storage_room))
    {
        call_other(KHIRAA_DIR(temple/rooms/storage),"??");
        storage_room = find_object(KHIRAA_DIR(temple/rooms/storage));
    }
    if(!objectp(storage_room))
    {
        tell_room(E(TO),"Error in loading storage room.\n");
        remove_object();
    }
}

void
create_object()
{
    set_name("rack");
    set_adj("equipment");
    add_adj("storage");
    set_short("equipment storage rack");
    set_long("The rack contains weapons, armours and other items. You "+
    "can view them seperately with 'exa weapons rack', 'exa armour rack' "+
    "and 'exa other rack'.\n");
    add_item("weapons rack","@@weapons_rack@@");
    add_item("armour rack","@@armour_rack@@");
    add_item("other rack","@@other_rack@@");
    add_prop(OBJ_M_NO_GET,"It is much too heavy.\n");
    load_storage_room();
}

void
init()
{
    ::init();
    AA(do_rack,rack);
    AA(do_unrack,unrack);
}

int
do_unrack(string str)
{
    int i;
    object *items,*mov_its;
    NF("There is no such item in the rack.\n");
    items = FIND_STR_IN_OBJECT(str,storage_room);
    if(!sizeof(items))
        return 0;
    mov_its = ({});
    for(i=0;i<sizeof(items);i++)
    {
        if(items[i]->move(TP) == 1)
            write("The "+items[i]->short()+" is too heavy!\n");
        else
            mov_its += ({items[i]});
    }
    if(!sizeof(mov_its))
    {
        write("You didn't unrack anything.\n");
        return 1;
    }
    write("You unracked "+COMPOSITE_DEAD(mov_its)+" from the rack.\n");
    say(QCTNAME(TP)+" unracked "+COMPOSITE_DEAD(mov_its)+" from the rack.\n");
    return 1;
}

int
do_rack(string str)
{
    return do_rack_items(str);
}

int
do_rack_items(string str)
{
    object *items,*weps,*arms,*oths;
    items = FIND_STR_IN_OBJECT(str,TP);
    if(!sizeof(items))
    {
        write("Rack what?\n");
        return 1;
    }
    weps = filter(items,"is_weapon",TO);
    arms = filter(items,"is_armour",TO);
    oths = filter(items,"is_other",TO);
    if(!sizeof(weps) && !sizeof(arms) && !sizeof(oths))
    {
        write("They are not rackable!\n");
        return 1;
    }
    if(sizeof(weps))
        rack_weapons(weps);
    if(sizeof(arms))
        rack_armours(arms);
    if(sizeof(oths))
        rack_others(oths);
    return 1;
}

void
rack_weapons(object *weps)
{
    int i;
    for(i=0;i<sizeof(weps);i++)
        weps[i]->move(storage_room);
    write("You put "+COMPOSITE_DEAD(weps)+" in the weapons rack.\n");
    say(QCTNAME(TP)+" puts "+COMPOSITE_DEAD(weps)+" in the weapons rack.\n");
}

void
rack_armours(object *weps)
{
    int i;
    for(i=0;i<sizeof(weps);i++)
        weps[i]->move(storage_room);
    write("You put "+COMPOSITE_DEAD(weps)+" in the armours rack.\n");
    say(QCTNAME(TP)+" puts "+COMPOSITE_DEAD(weps)+" in the armours rack.\n");
}
void
rack_others(object *weps)
{
    int i;
    for(i=0;i<sizeof(weps);i++)
        weps[i]->move(storage_room);
    write("You put "+COMPOSITE_DEAD(weps)+" in the others rack.\n");
    say(QCTNAME(TP)+" puts "+COMPOSITE_DEAD(weps)+" in the others rack.\n");
}

int
is_weapon(object ob)
{
    if(ob->id("weapon") )
    {
        if(ob->query_wielded() || ob->query_prop(OBJ_M_NO_DROP) )
            return 0;
        else 
            return 1;
    }
    return 0;
}

int
is_armour(object ob)
{
    if(ob->id("armour"))
    {
        if(ob->query_worn() || ob->query_prop(OBJ_M_NO_DROP) )
            return 0;
        return 1;
    }
    return 0;
}

int
is_other(object ob)
{
    if(ob->id("weapon") || ob->id("armour") || ob->query_prop(OBJ_M_NO_DROP) ||
       MASTER_OB(ob) == "/std/coins")
        return 0;
    return 1;
}

string
weapons_rack()
{
    object *weapons;
    weapons = filter(all_inventory(storage_room),"is_weapon",TO);
    if(!sizeof(weapons))
        return "The weapons rack is empty.\n";
    return "You see the following weapons in the rack:\n"+
    C(COMPOSITE_DEAD(weapons))+".\n";
}

string
armour_rack()
{
    object *arms;
    arms = filter(all_inventory(storage_room),"is_armour",TO);
    if(!sizeof(arms))
        return "The armour rack is empty.\n";
    return "You see the following armours in the rack:\n"+
    C(COMPOSITE_DEAD(arms))+".\n";
}

string
other_rack()
{
    object *others;
    others = filter(all_inventory(storage_room),"is_other",TO);
    if(!sizeof(others))
        return "The other rack is empty.\n";
    return "You see the following items in the rack:\n"+
    C(COMPOSITE_DEAD(others))+".\n";
}
