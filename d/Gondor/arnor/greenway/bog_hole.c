/*
 *	/d/Gondor/arnor/greenway/bog_hole.c
 *	Coded by Elessar.
 *
 *	Modification log:
 *    Tigerlily, May 7, 2004: updated for recode
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include "/d/Gondor/defs.h"

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
        "are rising to the north of here, but the most dominant features " +
        "right here are the bogs and the insects living in them. No real " +
        "tracks are readily apparent, except possibly towards the west.");

    add_exit(ARNOR_DIR + "greenway/swamp", "west", 0, 3);
 
    add_item(({"hill","hills","north downs","downs"}), BSN(
      "The North Downs form a line of hills running from the northeast to " +
      "the southwest. Here, at its southern end, the ridge splits up into two " +
      "branches, and in-between, there lies a small valley. "));
    add_item(({"fornost","valley","field","ruins","field of ruins"}), BSN(
      "In the small valley lying between the southern hills of the North " +
      "Downs once must have stood a mighty fortress. All that is left now " +
      "are the overgrown ruins of wide walls, great halls, and many homes.\n"));
    add_item(({"dike","gates"}), BSN(
      "Across the swamp at the foot of the hills runs an ancient dike " +
      "straight up to what once must have been the gates of the fortress."));
    add_item(({"plain","plains","marsh","swamp"}), BSN(
      "The swamp continues north until it reaches the foot of the hills. " +
      "To the east and the south, there is no end visible from here. The " +
      "ground is damp and boggy, and over the treacherous marshes it is " +
      "impossible to find a trail."));
    add_item(({"pools","reed","rushes","quagmires","ground","marshes"}), BSN(
      "The ground is damp and boggy. Here and there are small pools and wide " +
      "stretches of reed and rushes filled with the warbling of hidden birds. " +
      "Through the shifting quagmires, it is impossible to find a trail, " +
      "except possibly towards the west."));
    add_item(({"bushes", "undergrowth",}), exa_bushes);
    add_item(({"ground", "marshes",}), exa_ground);
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
//remove references to old guild
/*
    if (pl->query_guild_name_occ() == GUILD_NAME)
        return 1;
    if (pl->query_prop(RANGER_NORTH_VISITOR))
        return 1;
*/
    return 0;
}

public string
enter_bushes()
{
    write("You cannot see a way to reach them from here.\n");
    return "";
}

public string
exa_bushes()
{
    string desc = "Towards the northern end of the marshes and by the foothills "
      + "on that side of the valley, there are indeed some bushes and undergrowth "
      + "of a different kind than the reeds and rushes in most of the rest of the "
      + "area. ";

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
      "except perhaps towards the west.";
    return BSN(desc);
}
