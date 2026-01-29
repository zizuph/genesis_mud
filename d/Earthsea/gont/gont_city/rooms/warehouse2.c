/*
* Warehouse in Gont Port
*
* coded by Porta 971016.
*/

#pragma strict_types
#pragma no_clone

inherit "/std/room";

#include <stdproperties.h>

private object *workers = allocate(2);

public void
reset_room()
{
    int i;

    for(i = 0; i < 2; i++)
    {
        if(workers[i])
        {
            continue;
        }

        workers[i] = clone_object(
            "/d/Earthsea/gont/gont_city/liv/dockworker" + (random(4)+1)
        );
        workers[i]->move(this_object());
    }
}

public void
create_room()
{
    add_prop(ROOM_S_MAP_FILE, "earthsea_map.txt");
    set_short("Inside a warehouse");
    set_long("You enter a large warehouse, where"+
        " many harbour workers are busy carrying crates and"+
        " stacking them in huge piles. The only light in"+
        " here comes from outside, between gaps in the"+
        " board walls and from the large open door, making"+
        " the clouds of dust in the air clearly visible."+
        " Under your feet is the bare earth, sterile"+
        " and compact from constant use. There are large"+
        " crates and sacks"+
        " everywhere, piled on top of each other all the"+
        " way up to the ceiling.\n");
    add_item("walls","The walls are made by boards,"+
        " crudely fitted together leaving wide gaps between"+
        " them.\n");
    add_item("floor","The floor is the bare earth, made"+
        " compact through the years by hundred of harbour"+
        " workers walking it.\n");
    add_item(({"sacks","crates"}),"The sacks and crates"+
        " are full of the goods this particular merchant"+
        " company trades with.\n");
    add_item("dust","Clouds of dust are in the air, clearly"+
        " visible in the light coming in from outside.\n");
    add_item("ceiling","The ceiling is high above your head,"+
        " and the weak light makes it impossible to make out"+
        " anything more.\n");
    add_item("piles","The sacks and crates are piled on top"+
        " of each other, all the way up to the ceiling.\n");
    add_item("workers","Muscular men carrying heavy crates"+
        " and sacks from a newly arrived ship to this warehouse.\n");
    add_prop(ROOM_I_INSIDE,1);
    add_exit("city_street/city_road16", "southeast");
    reset_room();
}
