#pragma strict_types

inherit "/d/Gondor/std/room.c";
inherit "/d/Gondor/common/lib/herbsearch";

#include "/d/Gondor/common/lib/herb_list.h"
#include "/d/Gondor/defs.h"
#include "/d/Gondor/elessar/lib/clock.h"

//  Global Variables
static string  extra_long = "";
static string  flow;
static string  plains;
static string  sky;
static string  River = "Entwash";

varargs void  set_river(string i) { River = i; }
varargs void  set_flow(string i)   { flow =i; }

string sh_desc();
string long_desc();
string exa_sky();

void
set_extra_long(string s)
{
    if(strlen(s))
        extra_long = " "+s;
}

string query_extra_long() { return extra_long; }

void
create_stream()
{
}

nomask void
create_gondor()
{
    set_name("plains");
    set_short(sh_desc);
    set_long(long_desc);

    create_stream();
    sh_desc();

    switch(random(4))
    {
        case 0:
            add_item(({"river","rivers","entwash","river entwash"}),
                BSN("The " +River+ " flows swiftly to the "+flow+" here,"
              + " making its way through the plains of Rohan with"
              + " a silent urgency. Numerous trees and plants grow"
              + " along its banks."));
            add_item(({"trees","tree"}), BSN(
                "The trees vary in size and variety. It seems that the"
              + " river is a rich supplier of nutrients and healthy"
              + " soil in which the foliage might take root."));
            add_item(({"plant","plants"}), BSN(
                "There are many plants growing along the river here."
              + " Most of them are tall and reedlike, and you notice"
              + " that the farther east you look, the thicker the"
              + " growth becomes."));
            break;
        case 1:
            add_item(({"river","rivers","entwash","river entwash"}),
                BSN("Large boulders and debris are strewn throughout"
              + " the " +River+ " here as it makes its way in a gradual"
              + " "+flow+"erly direction."));
            add_item(({"boulder","boulders","rock","rocks"}), BSN(
                "These large rocks are likely the result of erosion"
              + " and are perhaps even glacial deposits from some long"
              + " forgotten age. They make for a rougher flow of the"
              + " river here, but is not clear whether or not they are"
              + " present farther down the length of the " +River+ "."));
            add_item(({"debris","husk","husks","log","logs"}), BSN(
                "A number of logs and fallen husks of trees have"
              + " lodged amongsts the rocky boulders in the river"
              + " here. No doubt they were carried from some distant"
              + " bank of the river off to the north and east."));
            break;
        case 2:
            add_item(({"river","rivers","entwash","river entwash"}),
                BSN("The river divides slightly here to make its way"
              + " around a small island which has survived against"
              + " the years of erosion."));
            add_item(({"island","islands"}), BSN(
                "The island is relatively small and seems barely large"
              + " enough for the handfull of trees that can be seen"
              + " growing upon it."));
            add_item(({"tree","trees"}), BSN(
                "These trees do not look as strong as many of the"
              + " others in this region. It is likely that their roots"
              + " do not easily tap into the rocky bed of the island."));
            break;
        case 3:
            add_item(({"river","rivers","entwash","river entwash"}),
                BSN("The "+flow+"ward flow of the " +River+ " is clear and"
              + " calm at this point. Leaves and other small bits of"
              + " debris float silently by, sometimes spinning off"
              + " the shoot of a tall reed extending from the glassy"
              + " surface."));
            add_item(({"leaf","leaves","debris"}), BSN(
                "They float by in silent procession. It gives a rather"
              + " peaceful feeling to watch them."));
            add_item(({"reed","reeds"}), BSN(
                "Numerous reed-like plants are growing along the river"
              + " here, and for a ways to the "+flow+". Every so often"
              + " a sudden gust of wind will bend them slightly."));
            break;
    }

    add_item(({"plains","plain","ground"}), BSN(
        "These plains extend for miles to the north and west. Tall"
      + " grass bows like wheat in the occasional breeze, and"
      + " to the south and east, the mouths of the Entwash can be seen"
      + " extending to meet the Anduin."));
    add_item(({"grass"}), BSN("This grass is tall and strong,"
      + " almost resembling wheat in its shaft and height."));
    add_item(({"marshes","marsh","mouths","mouths of the entwash"}), BSN(
        "A bit to the south and south and east the Entwash can be seen fracturing into many"
      + " smaller streams which wind through a marshy area on their"
      + " way to eventually join with Anduin the Great."));
    add_item(({"hill","hills","emyn muil"}), BSN(
        "The tops of the dim hills of the Emyn Muil are visible quite some distance"
      + " to the north. Though too far off to see"
      + " from here, the great Rauros Falls flow from those hills where"
      + " the mighty Anduin spills over into the lowlands."));

    if (River == "Entwash")
    {
        add_item(({"anduin","river anduin","mighty anduin"}), BSN(
            "Occasionally a low lying area of the plains will allow for a"
          + " look at the great river Anduin, which flows far off to the"
          + " east. Even from this distance, the breadth and majesty of"
          + " that river is evident."));
    }

    add_item(({"sky","sun","sunlight","star","stars"}), exa_sky);

    set_up_herbs( ({ ONE_OF_LIST(HERBS),
                     ONE_OF_LIST(HERBS),
                     ONE_OF_LIST(HERBS), }),
                         ({ "ground","plains","grass","grasses" }),
                  3 );
}

string
sh_desc()
{
    string  desc;

    switch(random(4))
    {
        case 0:
            desc = "Quiet";
            break;
        case 1:
            desc = "Muddy";
            break;
        case 2:
            desc = "Grassy";
            break;
        case 3:
            desc = "Wide";
            break;
    }

    plains = (desc + " plains beside the "+flow+" bound River " + River);
    return plains;
}

string
long_desc()
{
    exa_sky();

    return BSN(plains +". "+ sky + extra_long);
}

string
exa_sky()
{
    switch(tod())
    {
        case "early morning":
            sky = "Stars are still visible twinkling in the early"
                 + " morning sky. Only a very faint glow in the horizon"
                 + " gives any indication that daylight approaches.";
            break;
        case "morning":
            sky = "The sun is slowly climbing the morning skyline,"
                 + " casting a bit of warmth amidst the dewdrops.";
            break;
        case "noon":
            sky = "Noon has come over the plains, and the sun burns"
                + " brightly overhead.";
            break;
        case "afternoon":
            sky = "The afternoon sunlight has burned off much of the"
                + " morning chill and dew.";
            break;
        case "evening":
            sky = "The sun has sunk beneath the horizon now as evening"
                + " draws on.";
            break;
        case "night":
            sky = "Night has descended on the plains, and stars"
                + " are now visible spread across the broad skyline.";
            break;
        case "midnight":
            sky = "All is still, for it is midnight on the plains.";
            break;
    }

    return BSN(sky);
}
