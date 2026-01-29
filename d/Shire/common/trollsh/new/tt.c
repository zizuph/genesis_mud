inherit "/d/Shire/std/room";

#include "/d/Shire/sys/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <filter_funs.h>
#include <ss_types.h>

#define PLAYER_I_FOUND_CREVICE "_player_i_found_crevice"

//** Global Variables **//
int gDoorState;
int gRockAmount;

//** Prototypes **//
int check_door();
int do_enter(string s);
int do_get(string s);
int do_push(string s);
int door_state();
string do_search(object o, string s);

void
create_shire_room()
{
    FIXEUID

    set_short("At the end of a dark tunnel");
    set_long("You stand at the end of a dark tunnel. The "+
        "rocky walls loom above you, echoing the slightest of sounds.\n");

    add_item(({"walls","rocky walls","wall","rocky wall"}),
        "Which wall?\n");

    add_item(({"north wall","northern wall","south wall","southern wall"}),
        "The uneven wall consists of solid rock and dirt. A few large "+
        "crevices can be found along this wall. As it rises "+
        "into the darkness above it rapidly slopes inwards.\n");

    add_item(({"west wall","western wall"}),
        "It rises straight up to the ceiling and appears very "+
        "smooth. A slender crack runs from the bottom of the "+
        "wall stopping near the ceiling.\n");

    add_item(({"crevice","crevices"}),
        "There are a number of crevices around this area ranging "+
        "greatly in size.\n");

    add_item(({"crack","slender crack"}),
        "Upon closer inspection you determine the inch-wide "+
        "crack running perfectly straight up the center of the wall "+
        "is not a natural occurance. While close to the "+
        "crack you perceive a slight rumbling sound and "+
        "feel the faintest of breezes brush against your face.\n");

    add_item(({"ground","floor"}),
        "The ground around you is coverd with loose stones. "+
        "Towards the center of the tunnel a wide path seems "+
        "to have been worn smooth.\n");

    add_item(({"rock","rocks","stone","stones"}),
        "You could pick one up if you are really that "+
        "interested.\n");

    add_item(({"path","wide path"}),
        "This area of the tunnel is smoother than the rest "+
        "and is slightly lower in elevation.\n");

    gDoorState = 0; // door loads as closed
    gRockAmount = 3 + random(7);

    add_prop(OBJ_S_SEARCH_FUN, "do_search");
    add_prop(ROOM_I_INSIDE, 1);

    add_exit("/d/Shire/common/trollsh/new/tm","west",check_door,1,door_state);
}

int
check_door()
{
    if (!gDoorState)
    {
        write("There is no obvious exit west.\n");
        return 1;
    }

    return 0;
}

int door_state() { return !gDoorState; }

void
init()
{
    ::init();

    add_action(do_get,"get");
    add_action(do_push,"push");
    add_action(do_enter,"enter");
}

int
do_enter(string s)
{
    object crevice, *pl = ({});

    if (!stringp(s))
        return 0;

    if (s != "crevice" && s != "large crevice")
    {
        NF("Enter what?\n");
        return 0;
    }

    if (!TP->query_prop(PLAYER_I_FOUND_CREVICE))
    {
        NF("What crevice!?\n");
        return 0;
    }

    crevice = find_object("/d/Shire/common/trollsh/new/crevice");
    if (!objectp(crevice))
    {
        ("/d/Shire/common/trollsh/new/crevice")->load_object();
        crevice = find_object("/d/Shire/common/trollsh/new/crevice");
    }

    pl = FILTER_LIVE(deep_inventory(crevice));
    if (sizeof(pl))
    {
        NF("There seems to be someone in there already!\n");
        return 0;
    }

    write("You attempt to hide yourself in a large crevice "+
        "in the northern wall.\n");
    tell_room(TO, QCTNAME(TP)+" steps off into the shadows "+
        "near the northern wall.\n",TP);
    if (TP->move_living("M","/d/Shire/common/trollsh/new/crevice",1,0))
    {
        NF("For some reason you can't get into the crevice.\n");
        return 0;
    }

    return 1;
}

int
do_get(string s)
{
    object rock;

    if (!stringp(s))
        return 0;

    if ((s != "stone") && (s != "rock"))
        return 0;

    if (gRockAmount < 1)
    {
        write("You can't find any worth picking up.\n");
        return 1;
    }

    rock = clone_object("/d/Shire/common/obj/rock");
    if (rock->move(TP,1))
    {
        rock->remove_object();
        write("You can't seem to carry anything more.\n");
        return 1;
    }

    write("You pick up a small rock.\n");
    tell_room(TO, QCTNAME(TP)+" picks up something from "+
        "the ground.\n", TP);
    gRockAmount--;
    return 1;
}

int
do_push(string s)
{
    if (!stringp(s))
        return 0;

    if ((s != "doors") && (s != "west wall") && (s != "western wall"))
    {
        NF("Push what?\n");
        return 0;
    }

    if (gDoorState)
    {
        NF("The doors are already open!\n");
        return 0;
    }

    if (TP->query_stat(SS_STR) < 299)
    {
        NF("You push with all your might but fail to move "+
        "the doors an inch.\n");
        return 0;
    }

    write("You push open the western wall.\n");
    tell_room(TO,QCTNAME(TP)+" pushes open the western wall.\n",TP);
    gDoorState = 1;
    return 1;
}

string
do_search(object pl, string what)
{
    if (!stringp(what) || what != "crevices")
        return 0;

    pl->add_prop(PLAYER_I_FOUND_CREVICE, 1);
    return "You find a large crevice you may be able to enter.\n";
}
