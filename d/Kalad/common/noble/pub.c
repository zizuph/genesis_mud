inherit "/d/Kalad/room_std.c";
inherit "/lib/pub";
#include "/d/Kalad/defs.h"

object ob;
void reset_room();

void
create_room()
{
    set_short("The Royal Pub");
    set_long("You are now in the Royal Pub. The fresh, clean white "+
        "walls around you reflect the bright lamp light that comes from "+
        "the various lamps around the pub. Many tables are scattered "+
        "about the room, and a very fine looking bar is up against the "+
        "the north wall. A harp player plays sweet music in the corner "+
        "of the room to the south, and the air smells of fresh wine.\n");
    add_item("bar", "A nice looking wooden bar with a menu on it.\n");
    add_item("menu", "It has a lot of readable words on it.\n");
    add_item("chairs",
        "They are made out of wood.\n"); 
    add_item("tables", "They are fine oak tables and are kept "+
        "very clean.\n");
    add_cmd_item("menu", "read", "@@read");
    add_prop(ROOM_I_INSIDE,1); 
    add_drink( ({ "wine", "wines", "white", "white wine" }),
        "wine", "white", 100, 20, 100, 0, 0,
        "It has a light white color and smells fresh and pure.\n", 0);
    add_drink( ({ "wine", "wines", "red", "red wine" }),
        "wine", "red", 100, 20, 100, 0, 0,
        "It has a deep red color and smells very sweet.\n", 0);
    add_drink( ({ "wine", "wines", "emerald", "emerald wine" }),
        "wine", "emerald", 100, 30, 200, 0, 0,
        "This wine is light green, but when it reflects light, "+
        "it seems to sparkle like an emerald.\n", 0);
    add_drink( ({ "wine", "wines", "blue", "blue wine" }),
        "wine", "blue", 100, 40, 300, 0, 0,
        "This strange wine has a very dark blue color. It smells "+
        "like rasberies, only with a more potent alchoholic scent.\n", 0);
    add_food( ({ "leg", "frog","fresh frog leg", "frog leg" }),
        "leg","frog", 60, 200, "frog leg", "frog legs",
        "Tiny fried frog leg.\n", 0);
    add_food( ({ "leg","crab", "fresh crab leg", "crab leg" }),
        "leg", "crab", 120, 300, "fresh crab leg",
        "fresh crab legs",
        "Tender crab mean encased in a steamy hot shell.\n", 0);
    add_food(({"lobster","delicious","plate of delicious lobster","plate","plates"}),
        "lobster","delicious",160,350,"plate of delicious lobster",
        "plates of delicious lobster","A very fancy plate with a freshly "+
        "cooked red lobster. Your mouth waters.\n",0);
    add_exit(NOBLE(wayfarer/s5),"south",0,-1,-1);
    reset_room();
}
void
reset_room()
{
    if(!ob)
        {
        ob = clone_object(NOBLE(npc/khraal));
        ob->move(TO);
    }
}


void
init()
{
    ::init(); 
    init_pub();
}

int
read(string str)
{
    write(
        "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n"+
        "@          The Royal Pub            @\n"+
        "@-----------------------------------@\n"+
        "@ White wine     - 100 cc           @\n"+
        "@ Red wine       - 100 cc           @\n"+
        "@ Emerald wine   - 200 cc           @\n"+
        "@ Blue wine      - 300 cc           @\n"+
        "@                                   @\n"+
        "@ Fresh frog leg   -  200 cc        @\n"+
        "@ Fresh crab leg   -  300 cc        @\n"+
        "@ Delicious Lobster - 350 cc        @\n"+   
        "@                                   @\n"+
        "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
    return 1;
}

