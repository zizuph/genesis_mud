/*
 * /d/Emerald/blackwall/delrimmon/del_rimmon_room.c
 *
 * This is a library module which certain outdoor rooms in the
 * Blackwall Mountains are meant to inherit. It provides items and
 * certain special functions. Thanks to Elessar for his
 * wonderful design of the lorien.c file, in part upon which
 * this file was inspired.
 *
 * Copyright (c) Cooper Sherry (Gorboth),
 *           February 1996 - January 1999
 *
 * TODO:
 *       Add herbs
 *       Tree/cliff climbing?
 *       Items for loc = 4
 */
#pragma strict_types

#include <composite.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Emerald/blackwall/delrimmon/defs.h"

/* definitions */
#define IN_TREE             TP->query_prop("_live_s_sitting")

/* global variables */
object  Climber;
mixed   Extraline,
       *Rope_Ties;
string  Side;
int     Loc,            /* 1 = lake shore, 2 = forest      */
                        /* 3 = cliff base, 4 = high cliffs */
                        /* 5 = on lake                     */
        Ground,
        Tree = 0,
        Climbed = 0,
        Beacon_Lit = 0,  /* has the beacon atop Melan Earl been lit? */
        Show_area_desc;

/* prototypes */
public string          del_rimmon_short();
public varargs string  del_rimmon_long(int time_desc_only = 0);
public void            add_lakeview();
public void            add_view();
public string          exa_sky();
public string          exa_illumination();
public string          exa_shadows();
public string          exa_ground();
public mixed           check_get();
public string          exa_melan_earl();
public string          exa_beacon();

public void    set_loc(int i) { Loc = i; }
public void    set_beacon(int i) { BEACON->set_beacon(i); }
public int     query_beacon() { return BEACON->query_beacon(); }
public void    set_side(string s) { Side = s; }
public void    set_extraline(mixed s) { Extraline = s; }
public void    set_show_area_desc(int i = 1) { Show_area_desc = i; }
public void    set_rope_tie(mixed m) { Rope_Ties = m; }
public mixed   query_rope_tie() { return Rope_Ties; }

public void    light_beacon() { this_object()->set_beacon(1); }
public void    extinguish_beacon() { this_object()->set_beacon(0); }

public int     query_loc() { return Loc; }
public string  query_side() { return Side; }

/*
 * function name:        del_rimmon_short
 * description  :        provide a short description for rooms in
 *                       the Del Rimmon area.
 * returns      :        string locstr -- the short description
 */
public string
del_rimmon_short()
{
    string  locstr;

    switch (Loc)
    {
        case 1:
            locstr = "on a grassy green lake shore along the " +Side+
                     "ern rim of Del Rimmon";
            break;
        case 2:
            locstr = "on a hillside in the tree covered slopes along"
                   + " the " +Side+ "ern side of Del Rimmon";
            break;
        case 3:
            locstr = "before sheer cliffs on the " +Side+ "ern slopes"
                   + " surrounding Del Rimmon";
            break;
        case 4:
            locstr = "in the high rocky ridges of the Blackwall"
                   + " Mountains";
            break;
        default:
            locstr = "in the Blackwall Mountains of Emerald";
            break;
    }


    if (BEACON->query_beacon())
    {
        if (TO->query_prop(ROOM_I_INSIDE))
        {
            return locstr;
        }

        locstr += ". A dazzling illumination fills the entire area,"
                + " casting long shadows along the ground";
    }

    return locstr;
} /* del_rimmon_short */

/*
 * function name:        del_rimmon_long
 * description  :        provides a long description for rooms in the
 *                       Del Rimmon area
 * arguments    :        time_desc_only -- true if XXX
 * returns      :        the room description
 */
public varargs string
del_rimmon_long(int area_desc_only = 0)
{
    string  long_desc,
            area_desc;

    if (IN_TREE)
    {
        long_desc = "In a tree " + del_rimmon_short() + ".";
    }

    else
    {
        long_desc = CAP(del_rimmon_short()) + ".";
    }

    if (!TO->query_prop(ROOM_I_INSIDE))
    {
        if (query_beacon())
        {
            area_desc = " The entire sky is lit by brilliant light,"
                      + " its glare";
        }
        else
        {
            area_desc = " The sky is filled with a steady illumination"
                      + " from this region, its soft light";
        }

        switch(Loc)
        {
            case 1:
               area_desc+= " reflecting off of the rippling"
                           + " water.";
                break;
            case 2:
               area_desc+= " peering through the overhead"
                           + " branches.";
                break;
            case 3:
               area_desc+= " gazing down on the sheer cliff"
                           + " faces.";
                break;
            case 4:
               area_desc+= " shining over the rocky"
                           + " terrain.";
                break;
            case 5:
               area_desc+= " shimmering on the surface"
                           + " of the lake.";
                break;
            default:
               area_desc+= " shining over the area.";
        }
    }

    if (Show_area_desc)
    {
        long_desc += area_desc;
    }

    if (Extraline)
    {
        long_desc += " " + TO->check_call(Extraline);
    }
 
    if (area_desc_only)
    {
        return area_desc;
    }
    else
    {
        return BSN(long_desc);
    }
} /* del_rimmon_long */

/*
 * function name:        add_lakeview
 * description  :        provides items that should be visible
 *                       when a clear view of the lake is available
 */
public void
add_lakeview()
{
        TO->try_item(({"lake","river","del rimmon","view"}), BSN(
            "Del Rimmon spreads out as a wide oval lake fenced by"
          + " steep grey hills on all sides. At the far southern end"
          + " of the lake, three tall peaks rise above the water."));
        TO->try_item(({"hills","hill","grey hills","steep grey hills",
                   "slope","slopes","hillside","hillsides","rim",
                   "grey hill","steep grey hill","steep hill"}),
            BSN("The lake is surrounded by steep grey hills, whose"
          + " sides are clad with trees, but their heads are bare,"
          + " cold-gleaming against the sky."));
        TO->try_item(({"trees","tree","forest","woods","wood"}),
            BSN("A thin forest of trees rings the lake, rising on the"
          + " steep slopes of hills which jut out as feet from the"
          + " frowning cliffs of the Blackwall Mountains."));
        TO->try_item( ({ "cliffs", "cliff", "head", "heads",
                         "blackwall mountains", "top", "tops", "ridge",
                         "ridges", "rocky ridge", "rocky ridges",
                         "high ridge", "high ridges", "mountains",
                         "high rocky ridge", "righ rocky ridges",
                         "towering cliff", "towering cliffs" }),
            BSN("The towering cliffs of the Blackwall Mountains rise abruptly"
          + " from the steep slopes surrounding the lake. Their"
          + " jagged tops collide with the sky in all directions."));
        TO->try_item(({"peak","peaks","tall peak","tall peaks"}),
            BSN("Three tall peaks rise at the southern end of the"
          + " basin which holds the waters of the lake. The midmost"
          + " stands somewhat forward from the others and sundered"
          + " from them, an island in the waters, about which the"
          + " river swings pale shimmering arms. Ael Rannath, as this"
          + " peak is called, rises between Melan Earl on the left,"
          + " and Melan Rath on the right."));
        TO->try_item(({"ael rannath","midmost peak","middle peak","island"}),
            BSN("Ael Rannath is truly a wonder to behold. Its"
          + " sides spring sheer out of the running water. High up"
          + " above its tall cliffs are steep slopes upon which trees"
          + " climb, mounting one head above another; and above them"
          + " again are grey faces of inaccessible rock, crowned by"
          + " a great spire of stone."));
        TO->try_item(({"spire","great spire"}), BSN(
            "Atop Ael Rannath, a spire of barren stone rises high above"
          + " the waters of the lake. An occasional seagull can be seen"
          + " circling its heights."));
        TO->try_item(({"seagull","gull","bird","birds","gulls","seagulls"}),
            BSN("The seagulls are barely visible in the mist which" 
          + " surrounds the great spire of Ael Rannath."));
        TO->try_item(({"mist","haze","vapour","vapours","mists"}), BSN(
            "A slight haze of mist envelopes the great spire of Del"
          + " Rimmon. Small shadows which must be seagulls lilt to"
          + " and fro amidst the vapour."));
        TO->try_item( ({ "melan earl", "left peak" }), exa_melan_earl);
        TO->try_item( ({ "beacon", "summit of melan earl",
                         "dazzling beacon", "beacon of light",
                         "dazzling beacon of light" }),
            exa_beacon);
        TO->try_item(({"melan rath","right peak"}),
            "Melan Rath rises from the southern end of the lake,"
          + " meeting with a range of cliffs which run from its own"
          + " western flank far to the west. Its sheer sides frame the"
          + " western edge of the waterfall, rising high above to be"
          + " crowned by a flat summit of barren rock.\n");
        TO->try_item( ({ "summit", "summit of melan rath",
                         "flat summit", "barren rock" }),
            "The summit of Melan Rath is flat and barren. Your eye"
          + " catches a momentary red flash of light as you gaze at"
          + " its heights.\n");
        TO->try_item( ({ "flash", "flash of red", "red flash",
                         "flash of light", "red flash of light",
                         "flash of red light" }),
            "You peer at the summit of Melan Rath for a time ... yes,"
          + " there it was again - a definite flash of red light.\n");
} /* add_lakeview */

/* 
 * function name:        add_view
 * description  :        adds items to the room based on the global
 *                       variable Loc (see declaration for details)
 */
public void
add_view()
{
    switch(Loc)
    {
        case 1:
            add_lakeview();
            TO->try_item( ({"water", "edge", "surface", "wave", "waves",
                        "rippling water"}),
                BSN("The water of the lake is peaceful and grey. Calm waves"
              + " lap softly against the bank here."));
            TO->try_item( ({"pebble", "pebbles", "beach", "beaches",
                        "pebbled beach", "pebbled beaches"}), BSN(
                "Smooth pebbles of various shapes and sizes are scattered"
              + " along the bank, casting a greyish hue to the shoreline."));
            TO->try_item( ({"bank", "shore", "side", "shoreline",
                        "riverbank", "lake shore", "lake shores",
                        "shores", "lakeshore", "lakeshores",
                        "curving shore", "curving shores",
                        "shore of the lake", "shores of the lake"}),
                BSN("A bank has been eroded away by the constant breaking of"
            + " the waves of the lake. It rises unevenly along the"
            + " edge of the water."));
            TO->try_item(({"grass","grasses","turf","grassy turf"}), BSN(
                "In many places along the lake shore, areas of green grass"
              + " lie scattered underfoot. The long and lush blades are"
              + " most likely a result of the constant nourishment which"
              + " the lake water provides."));
            break;
        case 2:
            TO->try_item( ({"slope", "slopes", "hills", "hill",
                        "hillside", "hillsides"}),
                BSN("Here along the "+Side+"ern rim of Del Rimmon, the"
              + " slope of the hills increases with the distance from the"
              + " lake. Many trees cover these slopes in a grey belt of"
              + " thin glades and forests surrounding the water."));
            TO->try_item( ({"rim", "rim of del rimmon"}), BSN(
                "From here, the slopes amble up towards cliffs which"
              + " peek now and again between the branches of the "
              + "trees."));
            TO->try_item( ({"belt", "grey belt", "glade", "glades",
                        "thin glade", "thin glades"}), BSN(
                "The trees which surround the lake grow more thickly in"
              + " some places than in others."));
            TO->try_item( ({"lake", "del rimmon", "water"}),
                BSN("Though not clearly visible through the trees,"
              + " reminders of Del Rimmon, the lake of the Blackwall Mountains"
              + " are ever present. The distant rumble of the waterfall,"
              + " and coiling mists amongst the trees serve as a constant"
              + " indication of the nearby water."));
            TO->try_item(({"mists","mist","fog","haze"}),
                BSN("Mist winds through these forests and over the ground"
              + " here along the " + query_side() + "ern slopes"
              + " of the lakeside. In"
              + " places are dense patches of fog, while elsewhere are"
              + " winding tendrils of moisture."));
            TO->try_item( ({"forest", "forests", "trees", "woods"}),
                BSN("Trees have grown to cover the lower slopes of these"
              + " hills as a ring of foliage surrounding the lake. Tree"
              + " trunks are scattered throughout the area, sometimes"
              + " growing in clusters, sometimes in sparse array. Above,"
              + " a leafy canopy frames the sky."));
            TO->try_item(({"trunk","trunks","cluster","clusters",
                       "tree trunk", "tree trunks", "ring",
                       "ring of foliage",}),
                BSN("The trunks grow tall and strong. Many of these trees"
              + " seem very ancient, having lived through many"
              + " generations of sun and rain."));
            TO->try_item(({"leaf","leaves"}),
                BSN("Leaves hang coldly in the cool air surrounding"
              + " the lake. Drops of moisture cling to their soft"
              + " sides."));
            TO->try_item(({"drop","droplet","droplets","dew","drops",
                       "drop of moisture","drops of moisture"}), BSN(
                "Tiny droplets of dew and moisture cling to the foliage"
              + " here. They sparkle and twinkle as light catches them."));
            TO->try_item(({"branch","branches"}),
                BSN("Branches splay out overhead in what seems to be"
              + " a carefully woven pattern of nature. The sky is"
              + " dimly visible between their many shapes and sizes."));
            TO->try_item(({"tree tops","tree top","canopy","leafy canopy",
                       "foliage"}),
                BSN("Leaves and branches are all about overhead, drawing"
              + " a quietly rustling foreground against the distant sky."));
            TO->try_item(({"moss","mosses","undergrowth"}),
                BSN("There are many variations of moss here, but most are"
              + " thick and matted, adding a bouyant quality to the"
              + " stepping foot."));
            TO->try_item(({"blackwall mountains","cliffs","cliff"}),
                BSN("Though not clearly visible through the branches and"
              + " trunks, the cliffs of the Blackwall Mountains can be seen through"
              + " the occasional gap in foliage along these slopes."));
            break;
        case 3:
            TO->try_item(({"cliffs","sheer cliffs","cliff","sheer cliff",}),
                BSN("Along the brink of this "+Side+"ern rim of the bowl"
              + " surrounding the lake of Del Rimmon stretches a wide"
              + " tumbled flat of scored and weathered rock, cut every"
              + " now and again by deep notches in the cliff face that"
              + " slope steeply up to trench-like gullies high above."));
            TO->try_item( ({"brink", "brink of the cliffs"}), BSN(
                "High above, the brink of the cliffs peers over the"
              + " valley which nestles Del Rimmon."));
            TO->try_item( ({"bowl", "valley"}), BSN(
                "The valley of Del Rimmon spreads out between the"
              + " encircling cliffs provides both protection from the"
              + " elements and a sense of remoteness to the lake"
              + " and its surrounding slopes."));
            TO->try_item( ({"rim", "rim of the bowl"}), BSN(
                "The rim of this "+Side+"ern portion of the slopes"
              + " which surround Del Rimmon is comprised mostly of"
              + " tall cliffs."));
            TO->try_item( ({"flat"}), BSN(
                "The cliffs roll along, fencing the entire area with"
              + " their rock walls."));
            TO->try_item( ({"covering", "green covering"}), BSN(
                "The green covering along the ground which extends"
              + " from the trees up the slope stops short of the"
              + " looming cliff walls."));
            TO->try_item(({"notch","notches","gully","gullies",
                       "trench-like gully","trench-like gullies"}),
                BSN("These clefts in the rock face form a jagged edge"
              + " to an already heavily scored surface."));
            TO->try_item( ({"rock", "rock face", "cleft", "clefts",
                        "cliff face", "cliff faces", "cliff wall",
                        "cliff walls", "face", "faces", "wall", "walls",
                        "rock walls", "rock wall", "cliffside",
                        "cliff side", "side of the cliff", 
                        "side of the cliff", "wall of the cliff",
                        "walls of the cliff", "face of the cliff",
                        "face of the cliffs" }),
                BSN("The rock of these cliffs is rent and cracked by"
              + " numerous clefts and fissures."));
            TO->try_item(({"fissure","fissures"}),
                BSN("Fissures run from the foot of the cliffs down into"
              + " the slope of the ensuing hillside, making their way for a"
              + " short distance towards the line of trees which extends"
              + " down towards the lake."));
            TO->try_item(({"trees","woods","tree","forest","forests",}),
                BSN("Trees grow close to these cliffs, and form a forest"
              + " of varying density which runs down the slopes of the"
              + " hillside towards the lake."));
            TO->try_item(({"lake","del rimmon",}),
                BSN("Through the occasional gap in the treetops, the"
              + " still waters of Del Rimmon can be seen glistening in"
              + " the distance."));
            TO->try_item(({"water","waters"}), BSN(
                "The waters of Del Rimmon glitter quietly in the"
              + " distance between the tops of the trees."));
            TO->try_item( ({"top", "tops", "treetop", "treetops",
                        "top of the trees",
                        "tops of the trees"}), BSN(
                "The tops of the forest trees rim the horizon in"
              + " the direction of the lake shore."));
            TO->try_item(({"hill","hills","slope","slopes","hillside"}),
                BSN("The slopes which rim the lake have run up against"
              + " sheer cliffs which form the "+Side+"ern edge of the"
              + " basin in which Del Rimmon rests here in the Blackwall"
              + " Mountains."));
            TO->try_item( ({"mist", "mists", "thin mists"}), BSN(
                "In certain places along the faces of the cliff,"
              + " moisture can be seen rising off the rock in"
              + " thin trails of mist which waft drowsily upward."));
            TO->try_item(({"blackwall mountains"}),
                BSN("The cliffs of the Blackwall Mountains rise sheer before these"
              + " slopes and continue for some distance to the "+Side+
                "."));
            break;
        case 4:
            TO->add_lakeview();
            break;
        case 5:
            TO->add_lakeview();
            break;
        default:
    }

    TO->try_item("sky", exa_sky);
    TO->try_item( ({ "illumination", "steady illumination", "light",
                     "brilliant light", "brilliant illumination",
                     "unusual light", "unusual illumination",
                     "dazzling light", "unusual dazzling light" }),
        exa_illumination);
    TO->try_item( ({ "shadow", "shadows" }), exa_shadows);
    TO->try_item( ({ "ground", "terrain", "down" }), exa_ground);
} /* add_view */


/*
 * function name:        exa_sky
 * description  :        provides a description for the sky
 * returns      :        the sky description
 */
public string
exa_sky()
{
    string  txt = "Peering upwards, you can see that"
                + LOW(del_rimmon_long(1));

    if (query_beacon())
    {
        txt += " An unusual dazzling light is filling the area.";
    }

    return txt + "\n";
} /* exa_sky */


/*
 * Function name:        exa_illumination
 * Description  :        provide the player with a description of the
 *                       light level in the area. If the beacon is lit,
 *                       we describe its brilliance.
 * Returns      :        string - the description
 */
public string
exa_illumination()
{
    if (query_beacon())
    {
        if (TO->id("emerald_lakeshore") || TO->id("del_rimmon_cliffs"))
        {
            return "The area is lit by a brilliant and unusual"
                 + " illumination, which casts long shadows across the"
                 + " ground. It appears to be coming from the direction"
                 + " of Melan Earl.\n";
        }

        return "The area is lit by a brilliant and unusual illumination,"
             + " which casts long shadows across the ground.\n";
    }

    return "The steady illumination which fills this region does not"
         + " appear to come from any single source, as there are no"
         + " distinct shadows cast.\n";
} /* exa_illumination */


/*
 * Function name:        exa_shadows
 * Description  :        allow the player to examine the shadows,
 *                       assuming that the beacon has been lit. If
 *                       it has not, we give a different answer.
 * Returns      :        string - the description
 */
public string
exa_shadows()
{
    if (query_beacon())
    {
        return "The shadows which are cast by the brilliant illumination"
             + " all point west northwest, as if the source of the"
             + " light were coming from the southeastern end of the"
             + " lake.\n";
    }

    return "There are no distinct shadows in this region. It is as"
         + " if the light comes from all directions at once.\n";
} /* exa_shadows */


/*
 * function name:        exa_ground
 * description  :        provides a generic description for the ground,
 *                       based on the global variable Loc
 * returns      :        string gtxt -- the ground description
 */
public string
exa_ground()
{
    string gtxt;

    switch (Loc)
    {
        case 1:
            gtxt = "Small pebbles litter the ground where the water"
                 + " meets the grassy hillside. Water is calmly lapping"
                 + " against the shore.";
            break;
        case 2:
            gtxt = "The ground is grassy and covered with patchy mosses"
                 + " and undergrowth amongst the many tree trunks.";
            break;
        case 3:
            gtxt = "The green covering which carpets the forested"
                 + " hillside stops just yards short of the looming"
                 + " cliff face.";
            break;
        case 4:
            gtxt = "The ground spreads out as a rugged and rocky surface,"
                 + " its texture riddled with cracks and grooves.";
            break;
        case 5:
            gtxt = "The waters of the lake are all that lie underfoot"
                 + " here.";
            break;
        default:
            gtxt = "The ground underfoot is firm and steady here.";
    }

    return BSN(gtxt);
} /* exa_ground */

/*
 * function name:        check_get
 * description  :        called by:
 *                        /d/Emerald/blackwall/delrimmon/obj/wep/catapult_arm.c
 *                       when a player tries to pick up the catapult.
 *                       If the curious orcs are in the room, and
 *                       they are able to see the player, they
 *                       prevent the player from taking it.
 * returns      :        0 -- the player can get the catapult arm
 *                       string -- the orcs prevent it
 */
public mixed
check_get()
{
    object  orc = present("_catapult_orc", environment(this_player()));

    if (!orc)
        return 0;

    if (!CAN_SEE_IN_ROOM(orc) || !CAN_SEE(orc, this_player()))
        return 0;


    return BSN("As you reach for the catapult arm, the "
      + orc->query_nonmet_name() + " shoves you roughly back, yelling:"
      + " You there! Stay away from that!");
} /* check_get */


/*
 * Function name:        exa_melan_earl
 * Description  :        provide a description of Melan Earl. This will
 *                       change if the beacon has been lit.
 * Returns      :        string - the description
 */
public string
exa_melan_earl()
{
    string      txt;

    txt = "Melan Earl frames the eastern edge of the waterfall at the"
        + " southern end of Del Rimmon, rising many hundreds of feet"
        + " above the water to face its sister spire, Melan Rath. Its"
        + " summit has a narrow point, and is devoid of any trees or"
        + " vegetation. ";

    if (query_beacon())
    {
        txt += "A dazzling beacon of light shines there, apparently"
             + " creating a massive source of illumination which casts"
             + " shadows throughout the area. ";
    }

    return txt + "The cliffs which ring the lake join with its eastern"
               + " flank.\n";
} /* exa_melan_earl */


/*
 * Function name:        exa_beacon
 * Description  :        allow players to examine the beacon
 * Returns      :        string - the description
 */
public string
exa_beacon()
{
    if (!query_beacon())
    {
        return "The summit of Melan Earl is rocky and bare.\n";
    }

    return "The summit of Melan Earl glows brilliantly with a massive"
         + " amount of light. Whatever has been placed there, it must"
         + " have a great magical power of illumination.\n";
} /* exa_beacon */
