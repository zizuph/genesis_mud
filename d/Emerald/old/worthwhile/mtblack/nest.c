inherit "/std/room";
#include "/d/Emerald/defs.h";
#define FAIL "Your search reveals nothing special.\n"

void
reset_room()
{
    set_searched(0);
}

void
create_room()
{
    set_short("In the nest");
    set_long("You are in the middle of the eagles' nest. They are "+
       "out right now enjoying the freedom of the skies you think. "+
       "The walls of the nest are made from branches and loose limbs "+
       "of dead trees.\n");
    add_exit(MBLACK_DIR + "east_shelf", "out");
    add_item(({"nest", "branches", "limbs", "walls"}),
        "The walls of the nest have multitudes of nooks and crannies "+
        "in them.\n");
    add_item(({"nook", "nooks", "crannies", "crannie"}), "They could "+
        "be holding anything there...You just can't see anything.\n");
    add_prop(OBJ_S_SEARCH_FUN, "search_fun");
}
string
search_fun(object player, string what)
{
    object bracelet;
    if(what=="crannies"||what=="crannie"||what=="wall"||what=="walls")
    return FAIL;
    if(what !="nest"&&what !="nook"&&what!="nooks")
    return FAIL;
    if(query_searched()>=1)
    return FAIL;
    seteuid(getuid());
    bracelet=clone_object(MBLACK_DIR + "arm/bracelet");
    bracelet->move(player);
    set_searched(1);
    return "In the nest's nooks you find an old bracelet.\n";
}
