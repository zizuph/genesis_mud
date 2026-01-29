/*
 *  /d/Gondor/arnor/greenway/swamp.c
 *
 *  Coded by Olorin.
 *
 *  Modification log:
 *   6-Feb-1997, Olorin:	Changed inheritance.
 *   7-May-2004, Tigerlily, tweaked slightly for recode
 *     (keeping old descriptions-block wizard entrance)
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include "/d/Gondor/defs.h"
#include <std.h>
#include <stdproperties.h>
#include <macros.h>
#define GUILD_NAME   "Rangers of the North"
#define RON_ENTER    "/d/Gondor/common/guild/north/log/entry"
#define RANGER_NORTH_VISITOR   "_ranger_i_north_visitor"

static object *Midges = allocate(4 + random(5));

public string enter_bushes();
public string exa_bushes();
public string exa_ground();

public void
create_area_room() 
{
    set_areadesc("swamp");
    set_areatype(1);
    set_area("northern");
    set_areaname("the Fornost swamps");
    set_land("the lost realm of Arnor");
    set_mountain("");
    set_grass("long grass");
    set_forest("Chetwood");
    set_extraline("The bleak and treeless hills of the North Downs " +
        "are rising to the north of here. An old, overgrown road comes up " +
        "from the south and crosses the swamp over a dike not far to the " +
        "west. The ground is damp and boggy, and there is no way out of it " +
        "except towards the road.");

    add_exit(ARNOR_DIR + "greenway/nr5", "west", 0, 3);
 
    add_item(({"hill","hills","north downs","downs"}), BSN(
      "The North Downs form a line of hills running from the northeast to " +
      "the southwest. Here, at its southern end, the ridge splits up into two " +
      "branches, and in-between, there lies a small valley. "));
    add_item(({"fornost","valley","field","ruins","field of ruins"}), BSN(
      "In the small valley lying between the southern hills of the North " +
      "Downs once must have stood a mighty fortress. All that is left now " +
      "are the overgrown ruins of wide walls, great halls, and many homes. " +
      "The road enters the field of ruins running over the dike.\n"));
    add_item(({"dike","gates"}), BSN(
      "Across the swamp at the foot of the hills runs an ancient dike " +
      "straight up to what once must have been the gates of the fortress."));
    add_item(({"plain","plains","marsh","swamp"}), BSN(
      "The swamp continues north until it reaches the foot of the hills. " +
      "To the east and the south, there is no end visible from here. The " +
      "ground is damp and boggy, and over the treacherous marshes it is " +
      "impossible to find a trail except back toward the road."));
    add_item(({"pools","reed","rushes","quagmires","ground","marshes"}), BSN(
      "The ground is damp and boggy. Here and there are small pools and wide " +
      "stretches of reed and rushes filled with the warbling of hidden birds. " +
      "Through the shifting quagmires, it is impossible to find a trail, " +
      "except back towards the road."));
    add_item(({"road","greenway"}), BSN(
      "The ancient, overgrown road to the west is the Greenway, " +
      "coming up from Bree."));
    add_item(({"bushes", "undergrowth",}), exa_bushes);
    add_item(({"ground", "marshes",}), exa_ground);
    add_cmd_item(({"bushes", "undergrowth", }), "enter",
        enter_bushes);
    seteuid(getuid());
    reset_room();
}

public void
reset_room()
{ 
    clone_npcs(Midges, NPC_DIR + "midge", 2.0 + rnd() * 10.0);
}

private int
query_allowed(object pl)
{
/*
    if (pl->query_guild_name_occ() == GUILD_NAME)
        return 1;
    if (pl->query_prop(RANGER_NORTH_VISITOR))
        return 1;
*/
    if (SECURITY->query_wiz_dom(pl->query_real_name()) == "Gondor")
        return 1;
     return 0;
}

public int
enter_tunnel(object pl)
{
    pl->move_living("across the marshes and into the bushes on the north side",
        RANGER_NORTH_DIR + "tunnel_entr");
    write_file(RON_ENTER, pl->query_name() + " entered Fornost through "
      + "the secret entrance. " + ctime(time()) + ".\n");
    return 1;
}

public int
enter_wrong(object pl)
{
    pl->move_living("across the marshes and into the bogs",
        ARNOR_DIR + "greenway/bog_hole");
    write_file(RON_ENTER, pl->query_name() + " tried to enter Fornost. "
      + ctime(time()) + ".\n");
    return 1;
}

public string
enter_bushes()
{
    write("You make your way carefully around the bogs, and push into the "
      + "bushes by the northern side of the marshes.\n");
// Take out old entrance, however, let people still think it's there
// so we can use it as camouflage
/*
    if (query_allowed(TP))
        enter_tunnel(TP);
    else
        enter_wrong(TP);
*/
    enter_wrong(TP);

    return "";
}

public string
exa_bushes()
{
    string desc = "Towards the northern end of the marshes and by the foothills "
      + "on that side of the valley, there are indeed some bushes and undergrowth "
      + "of a different kind than the reeds and rushes in most of the rest of the "
      + "area. ";
/*
    if (query_allowed(TP))
        desc += "You are quite certain that a hidden entrance to the Ranger hideout "
          + "in Fornost can be found behind those bushes. ";
*/
     desc += "Beyond them are the slopes of the North Downs, desolate and treeless. ";
    return BSN(desc);
}

public string
exa_ground()
{
    string desc = 
      "The ground is damp and boggy. Here and there are small pools and wide " +
      "stretches of reed and rushes filled with the warbling of hidden birds. " +
      "Through the shifting quagmires, it is impossible to find a trail, " +
      "except back towards the road.";
    return BSN(desc);
}
