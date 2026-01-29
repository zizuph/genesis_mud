/*
 *	/d/Gondor/ithilien/road/crossroads.c
 *
 */
#pragma strict_types

inherit "/d/Gondor/ithilien/road/road.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public string  exa_figure();

int     head_placed,
        flowers;

string exa_head(int i);
int warning(string dir);

public void
create_area_room()
{
    set_areatype(8);
    set_areadesc("forest");
    set_area("central eastern");
    set_areaname("Ithilien");
    set_land("Gondor");
    set_extraline("You have entered a great roofless ring of trees, "
      + "open in the middle to the sombre sky, and the spaces "
      + "between their immense boles are like the great dark arches "
      + "of some ruined hall. In the very centre four ways meet. "
      + "North the road leads to Morannon, south it continues its "
      + "journey towards Harad, west the road from old Osgiliath "
      + "comes climbing, and crossing, it passes eastwards into the "
      + "shadow of the mountains. There is a huge, sitting stone "
      + "figure here.");
    add_mountains(1, "only about half a mile");
    add_item( ({ "valley", "cleft", }), BSN(
        "You do not see much of it from this distance; it is a deep "
      + "gulf of shadow, and whatever is in there lies hidden in the "
      + "darkness. Your guess is that this is the Imlad Morgul, the "
      + "Valley of Dark Sorcery."));
    add_item(({"road","roads","crossroads"}), BSN(
        "The long straight road starts sloping down to the west, "
      + "and continues east towards the mountains. Another road "
      + "crosses here, being of the same standard as the east-west "
      + "road. It runs north towards the Morannon, the Black Gates of "
      + "Mordor, while in the other direction it goes through South "
      + "Ithilien towards the land of Harad. The road is well crafted, "
      + "cobbled with stones and lined with high banks."));
    add_item(({"trees","ring of trees","belt of trees"}), BSN(
        "You are standing within a great roofless ring of trees. The "
      + "trees are vast of size, very ancient it seems, and still "
      + "towering high, though their tops are gaunt and broken, as if "
      + "tempest and lightning-blast had swept across them, but had "
      + "failed to kill them or to shake their fathomless roots. Four "
      + "roads meet in the centre of the circle."));
    add_item(({"symbols","foul symbols","scrawls"}), BSN(
        "Among some scrawl obviously merely intended to disfigure the "
      + "statue you can recognize some runes in orc script. But most "
      + "of them are illegible, and those you can decipher do not make "
      + "any sense."));
    add_item(({"figure","stone figure"}), exa_figure);
    add_item(({"stone head","head"}), &exa_head(0));
    add_item(({"king's head","kings head"}), &exa_head(1));
    add_item(({"old king's head","old kings head"}), &exa_head(1));

    add_exit(ITH_DIR + "road/nr1",     "north", &warning("north"), 3);
    add_exit(MORGUL_DIR + "road/mrd1", "east",                  0, 3);
    add_exit(ITH_DIR + "road/sr1",     "south", &warning("south"), 3);
    add_exit(ITH_DIR + "road/er7",     "west",                  0, 3);
    (ITH_DIR + "road/nr4")->load_me();
}

public string
exa_figure()
{
    if (!head_placed)
        return BSN("It is a huge sitting stone figure, still and solemn. "
          + "The years have gnawed it, and violent hands have maimed it. "
          + "Its head is gone, and in its place is in mockery set a "
          + "round rough-hewn stone, rudely painted by savage hands in "
          + "the likeness of a grinning face with one large red eye in "
          + "the midst of its forehead. Upon the knees and the mighty "
          + "chair of the stone king, and all about the pedestal, are "
          + "idle scrawls mixed with the foul symbols that the orcs of "
          + "Mordor use. You spot the old king's head by the roadside.");
    return BSN("It is a huge sitting stone figure, shaped as a still and "
      + "solemn king. Its head sits loosely upon its shoulders. The "
      + "years have gnawed it, and violent hands have maimed it, but it "
      + "still looks impressing. The eyes are hollow and the carven "
      + "beard is broken, but about the high stern forehead there is a "
      + "coronal of silver and gold; a trailing plant with flowers like "
      + "small white stars has bound itself across its brows as in "
      + "reverence for the fallen king. And in the crevices of his "
      + "stony hair yellow stonecrop gleams.");
}

string
exa_head(int i)
{
    string desc;
    if (!head_placed && !i)
        return BSN("The head of the figure is a pure mockery, a round "
          + "rough-hewn stone painted by savage hands in the likeness "
          + "of a grinning face with one large red eye in the midst "
          + "of its forehead. Suddenly you spot the old king's head; "
          + "it is rolled away by the roadside.");
    if (head_placed)
        desc = "The old king's head sits loosely upon its shoulders.";
    else
      desc = "The old king's head lies by the roadside.";

    desc += " The eyes are hollow and the carven beard is broken, "
      + "but about the high stern forehead there is a coronal of "
      + "silver and gold";
    if (!flowers)
        desc += "; a trailing plant with flowers like small "
      + "white stars has bound itself across its brows as in "
      + "reverence for the old king";
    desc += ". And in the crevices of his stony hair, yellow "
      + "stonecrop gleams.";
    if (head_placed)
        desc += " A round, rough-hewn stone lies by the roadside, its "
          + "mocking features showing a grinning face with one red eye.";
    return BSN(desc);
}

public int
change_head(string str)
{
    NFN(CAP(query_verb())+" what?");
    if (!strlen(str)) 
        return 0;

    if (member_array(str, ({ "head", "stone head", "figure", 
			     "stone figure", "head on figure", })) < 0)
        return 0;
    write("You replace the stone head of the figure with the one that " +
	  "was lying by the roadside.\n");
    say(QCTNAME(TP)+" replaces the stone head of the figure with another "
      + "which was lying by the roadside.\n",TP);

    if (!flowers && !head_placed) 
    {
        tell_room(TO,"A trailing plant was clinging to the stone head, and "
          + "some flowers fall to the ground.\n");
        clone_object(HERB_DIR + "ithilgil")->move(TO);
        flowers = 1;
    }

    head_placed = !head_placed;
    return 1;
}

void
reset_room()
{
    flowers = 0;
}

int
warning(string dir)
{
    switch(dir)
    {
        case "north":
            write("\nYou are now walking on the road to the Morannon!\n");
            break;
        case "south":
            write("\nYou are now walking on the road to Harad!\n");
            break;
    }
    write("The armies of the Dark Lord are using this road, too, and they don't like spies!\n\n");
    return 0;
}

void
init()
{
    ::init();

    add_action(change_head, "repair");
    add_action(change_head, "fix");
    add_action(change_head, "change");
    add_action(change_head, "replace");
    add_action(change_head, "reinstall");
    add_action(change_head, "place");
}
