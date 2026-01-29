inherit "/d/Gondor/common/room";

#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/lib/herbsearch.h"
#include "/d/Gondor/common/lib/herb_list.h"
#include "/d/Gondor/minas/quest/pw5_defs.h"

#define MT_PW5_I_SEEN_SAND	"_MT_PW5_i_seen_sand"

void
create_room()
{
    set_short("In a private garden in Fourth Circle of Minas Tirith");
    set_long(BSN("This is a private garden in the Fourth Circle of Minas "
      + "Tirith. It lies between a large house to the west and "
      + "the Fourth Wall of the city to the east and the north. A sandy "
      + "path is winding through beds planted with flowers and herbs "
      + "and along the foot of the city wall."));

    add_item(({"flowers", "white flowers", "yellow flowers", }), BSN(
        "The white and yellow flowers make the garden smell pleasant. They "
      + "are placed in well tended flowerbeds."));
    add_item(({"path","sandy path", }),BSN(
        "The path is well tended and has been raked recently. It is enclosed "
      + "on both sides by a row of small stones. The complete lack of weeds "
      + "on the path and between the stones tells a lot about the gardener "
      + "that is working here. Walking on the path along the mighty city "
      + "wall you notice several gratings in the ground."));
    add_item(({"flower-beds","flowerbeds"}), BSN(
        "The flowerbeds are well tended, and white and yellow flowers "
      + "fill the garden with a pleasant smell. Other beds have been planted "
      + "with many different herbs."));
    add_item(({"house", "building", }), BSN(
        "The garden obviously belongs to the house west of here. The thick "
      + "stone walls do not show any openings on the ground floor except "
      + "for an entrance further leading out into this garden south of here."));
    add_item(({"wall", "city wall", }), BSN(
        "The sandy path is following the foot of the city wall at the north "
      + "and east ends of the garden. Walking on the path under the mighty "
      + "wall you notice several gratings in the ground."));
    add_item(({"grating", "gratings", "grates", }), VBFC_ME("exa_grating"));
    add_item(({"northwest grating", "northwest drain", }),
        "You can see nothing special about the northwest grating.\n");
    add_item(({"northeast grating", "northeast drain", "northeast grate", }),
        VBFC_ME("exa_ne_grating"));
    add_item(({"east grating", "east drain", "east grate", }),
        "You can see nothing special about the east grating.\n");
    add_item(({"rod", "rods", "iron rod", "iron rods"}), BSN(
        "The iron rods are too thick to bend or break. They have been inserted "
      + "into holes in the walls of the drains with both ends so that it is "
      + "impossible to remove them."));
    add_item(({"sand"}), VBFC_ME("exa_sand"));

    add_exit(MINAS_DIR+"houses/g2ncrc4","south",0,1);

    add_prop(OBJ_S_SEARCH_FUN,"do_search");
    add_prop(OBJ_I_SEARCH_TIME,3);
    set_search_places(({"flowers","flower-beds","flowerbeds","garden"}));

    add_herb_file(ONE_OF_LIST(HERBS));
    add_herb_file(ONE_OF_LIST(HERBS));
    add_herb_file(ONE_OF_LIST(HERBS));
}

void
reset_room()
{
    set_searched(0);
}

void
hide_murder_weapon()
{
    object  sewer_room;

    FIX_EUID

    MT_PW5_SEWER_ROOM->load_me();

    if (!objectp(sewer_room = find_object(MT_PW5_SEWER_ROOM)))
    {
        write(" >>>> Error! Failed to load "+MT_PW5_SEWER_ROOM+"!\n");
        return;
    }

    MT_PW5_SEWER_ROOM->hide_murder_weapon();
}

string
exa_grating()
{
    return BSN("There are three gratings in total, each made of seven thick "
      + "iron rods that cover a hole in the ground. The holes are probably "
      + "drains leading surplus rain water into the sewers. One drain of "
      + "the three drains is at the northwest corner of the garden, one "
      + "at the northeast corner and the third is at the east end of the "
      + "garden, halfway between the northeast and the southeast corner.");
}

string
exa_ne_grating()
{
    int     aware = TP->query_skill(SS_AWARENESS);
    string  desc = "You can see nothing special about the northeast grating";

    switch (aware)
    {
        case 0..15:
            desc += ".";
            break;
        case 16..25:
            desc += ", but some sand from the path seems to have spilled over "
              + "onto the stones that enclose the drain.";
            TP->add_prop(MT_PW5_I_SEEN_SAND, 1);
            break;
        case 26..30:
            desc = "Some sand from the path seems to have spilled over "
             + "onto the stones that enclose the drain. Or perhaps someone "
             + "has thrown the sand onto the enclosure?";
            TP->add_prop(MT_PW5_I_SEEN_SAND, 1);
            break;
        case 31..45:
            desc = "Someone seems to have thrown sand from the path onto "
              + "the stones that enclose the drain and into the drain itself.";
            TP->add_prop(MT_PW5_I_SEEN_SAND, 1);
            break;
        case 46..100:
            desc = "Someone seems to have thrown sand from the path onto "
              + "the stones that enclose the drain and into the drain itself. "
              + "Under the sand on the enclosure you can still make out a "
              + "few drops of blood and you wonder if someone has thrown "
              + "something through the grate into the drain and tried to "
              + "hide that object inside the drain by covering it with sand.";
            TP->add_prop(MT_PW5_I_SEEN_SAND, 1);
            hide_murder_weapon();
            TP->add_prop(MT_PW5_I_SEEN_BLOOD, 1);
            break;
        default:
            desc += ".";
            break;
    }

    return BSN(desc);
}

string
search_ne_grating(object player, string str)
{
    
    if (!player->query_prop(MT_PW5_I_SEEN_SAND))
        return 0;

    if ((player->query_skill(SS_AWARENESS) <= 25) &&
        (player->query_stat(SS_INT) < 50))
        return BSN("You search the "+str+", but even though you notice "
          + "the sand on the grate and the enclosing stones, you "
          + "fail to make sense out of it.");

    TP->add_prop(MT_PW5_I_SEEN_BLOOD, 1);
    hide_murder_weapon();

    return BSN("Someone seems to have thrown sand from the path onto "
      + "the stones that enclose the drain and into the drain itself. "
      + "You carefully remove the sand from the stones and uncover a "
      + "few drops of blood. You wonder if someone has thrown "
      + "something through the grate into the drain and tried to "
      + "hide that object inside the drain by covering it with sand.");
}

string
do_search(object player, string str)
{
    if (str == "sand" || str == "northeast drain" ||
        str == "northeast grating" || str == "northeast grate" ||
        str == "stones")
        return search_ne_grating(player, str);

    return herb_search(player, str);

}

string
exa_sand()
{
    if (TP->query_prop(MT_PW5_I_SEEN_SAND))
        return exa_ne_grating();

    return "The sand on the path is very fine and almost white.\n";
}

