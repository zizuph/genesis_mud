/*
 *	This file is obsolete and should not be used
 *	in new code anymore!
 *	Please use /d/Gondor/common/lib/area_room.c instead!
 *
 *	Olorin, June 1995
 */
/*     The standard Field-of-Gondor-file, made by Elessar for Genesis
 *     February 1992. No copyrights, but would like to have my name
 *     mentioned if anyone modifies this file for own use.  :-)
 */
/*
 *
 * Modification log:
 * - added reset_room() to reset seached to 0, so new herbs will grow.
 *   files which inherit this file should include ::reset_room() if
 *   reset_room() is redefined.
 *   Olorin, October 1993
 * - added a standard fail message for 'climb ....' *   when areatype is 
 *   'Trees' (3) or 'Forest' (7), or the rooms has the item 'tree' added.
 *   Olorin, November 1993
 * - added functions to set the global variables
 *   Olorin, June 1995
 * - changed include herbsearch.h to inherit herbsearch.c
 *   removed reset_room() function, as this is defined in herbsearch.c
 *   Olorin, June 1995
 *
 */
#pragma save_binary

inherit "/d/Gondor/common/room.c";
inherit "/d/Gondor/common/lib/herbsearch.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

int     areatype,      /* 1=Grass 2=Bushes 3=Trees 4=Farmland 5=Rocky */
                       /* 6=Snow 7=Forest 8=Road 9=Barren (0 means no type-desc) */
        forest_density;
string  area,          /* eg "northern" */
        areadesc,      /* eg "green, grassy field", "dense thicket", "small clearing" */
        areaname,      /* eg "Anorien", "Lebennin", "Rohan", "Ithilien" */
        land,          /* "Gondor" */
        grass,         /* (1), (2), (3): eg "soft, light green grass" */
        extraline,     /* additional room description */
        treetype;      /* (3), (7): eg "oak" - NOT: "oak " (!) */
string  forest,           /* not used in the master */
        mountain;         /* not used in the master */
function vbfc_extra;

void
set_vbfc_extra(function f)
{
    vbfc_extra = f;
}

string
short_func()
{
    switch(areatype)
    {
        case 1:
            return "a grassy "+areadesc+" in the "+area+" parts of "+areaname+" in "+land;
        case 2:
            return "a bushy "+areadesc+ " in the "+area+" parts of "+areaname+" in "+land;
        case 3:
            return "a "+areadesc+" with some trees in the "+area+" parts of "+areaname+" in "+land;
        case 4:
            return "an agricultural "+areadesc+" in the "+area+" parts of "+areaname+" in "+land;
        case 5:
            return "a rocky "+areadesc+ " in the "+area+" parts of "+areaname+" in "+land;
        case 6:
            return "a snowy "+areadesc+ " in the "+area+" parts of "+areaname+" in "+land;
        case 7:
            return LANG_ADDART(areadesc)+" in a forest in the "+area+" parts of "+areaname+" in "+land;
        case 8:
            return "a road across "+LANG_ADDART(areadesc)+" in the "+area+" parts of "+areaname+" in "+land;
        case 9:
            return "a barren "+areadesc+" in the "+area+" parts of "+areaname+" in "+land;
        default:
            return LANG_ADDART(areadesc)+" in the "+area+" parts of "+areaname+" in "+land;
    }
}

void
make_the_room()
{
    log_file("field", MASTER + " inherits /d/Gondor/common/lib/field.c.\n", -1);
    set_short("@@short_func@@");

    set_long("@@describe@@");

    switch(areatype)
    {
        case 1:
            add_item("field","The field is covered by "+grass+" grass all over.\n");
            add_item("grass","The "+grass+" grass grows all over the field.\n");
            break;
        case 2:
            add_item(areadesc, "On the green "+areadesc+" "+grass+
                " grass grows, along with some bushes here and there.\n");
            add_item("bushes","Some bushes growing here on the "+areadesc+".\n");
            break;
        case 3:
            add_item(areadesc,BSN("The "+areadesc+" is overgrown with "+grass+" grass, " +
                "and some trees also stand here."));
            add_item("trees","A few "+treetype+" trees also grow here.\n");
            break;
        case 4:
            add_item("field",BSN("You see a field used for agriculture by the people of "+
                land+", as there are covered by furrows and plough-marks here and there."));
            add_item("furrow","The furrows clearly indicate that this is farmland.\n");
            break;
        case 5:
            add_item("ground","The ground is quite rocky and barren.\n");
            add_item(({"grass","trees","bushes","herbs"}),
                "There's no green growth here, the ground is too rocky and hard.\n");
            break;
        case 6:
            add_item("ground","The ground is covered with snow here.\n");
            add_item("snow","The snow is white and cold.\n");
            break;
        case 7:
            add_item("ground","There's mostly dry leaves and moss on the forest floor.\n");
            add_item("moss","It's soft green moss, a bit yellow in patches perhaps.\n");
            add_item("leaves","They have fallen down from the "+treetype+" trees.\n");
            add_item(({treetype,treetype+" trees","trees"}),
                "The "+treetype+" trees that grow here make up the most of the forest here.\n");
            add_item("forest","A forest made up of "+treetype+" trees is all around you.\n");
            break;
        case 8:
            add_item("road","You're on a dusty road in "+land+". You're not sure where it leads.\n");
            add_item("ground","You see a dusty road.\n");
            break;
        case 9:
            add_item("ground","The ground is quite barren, so there's not much grows here.\n");
            break;
    }
    add_prop(ROOM_I_INSIDE,0);
    add_prop(ROOM_I_LIGHT,"@@check_lightlevel");
}

string
describe() 
{
    object  clock      = find_object(CLOCK);
    string  time       = clock->query_time_of_day(),
            long_descf = CAP(short_func()) + ". ";

    if (!clock->query_war()) 
    {
        switch(time)
        {
            case "night":
                long_descf += "Darkness covers "+areaname+" now at night. ";
                switch(clock->query_moon())
                {
                    case "full":
                        long_descf += "A full moon gives some light though. ";
                        break;
                    case "waxing crescent":
                    case "waxing gibbous":
                    case "waning gibbous":
                    case "waning crescent":
                        long_descf += "The moon gives a little light though. ";
                        break;
                    default:
                        long_descf += "The sky is covered with dark clouds, " +
                            "and not even the moon shines through. ";
                        break;
                }
                break;
            case "afternoon":
                long_descf += "The light of day shines across "+areaname+". "+
                    "It is afternoon. ";
                break;
            case "morning":
                long_descf += "The sun is on its way up in the morning sky to the east. ";
                break;
            case "noon":
                long_descf += "The sun is almost at its peak on its way across the sky. "+
                    "It is the middle of the day in Middle-Earth. ";
                break;
            case "evening":
                long_descf += "The sun is setting in the west, coloring the sky golden red. ";
                break;
            case "early morning":
                long_descf += "The sun is rising in the east, casting long shadows "+
                    "across "+areaname+". ";
                break;
        }
    }
    else 
    {
        switch(time)
        {
            case "evening":
            case "night":
            case "early morning":
                long_descf += "Massive dark clouds cover the sky, making it "+
                    "difficult to distinguish night and day. The clouds seem " +
                    "to be coming from the east, where Mordor lies. You suspect " +
                    "it is night now, as it is as dark as it can get. ";
                break;
            case "morning":
                long_descf += "A thick cover of clouds prevent the sun from "+
                    "shining on the lands of "+land+", and it is almost as dark " +
                    "as at night. However you gather that it is probably morning, " +
                    "as it is getting a bit lighter than earlier. ";
                break;
            case "noon":
                long_descf += "A dark mass of clouds seems to be rolling in from "+
                    "the east, covering the sky above "+land+". It is not much " +
                    "lighter now than it usually is at night, but still you suspect " +
                    "it is the middle of the day. ";
                break;
            case "afternoon":
                long_descf += "A thick mass of clouds cover the sky, making it "+
                    "difficult to see far. You suspect that it is afternoon, as it " +
                    "is getting a bit darker than earlier. ";
                break;
        }
    }
    if (strlen(extraline))
        long_descf += extraline;
    if (functionp(vbfc_extra))
        long_descf += vbfc_extra();
    return (BSN(long_descf));
}

int
check_lightlevel()
{
    return 1;
}

int
query_road()
{
    if (areatype == 8) 
        return 1;
    return 0;
}

void
init()
{
    ::init();
    if(areatype == 3 || areatype == 7 || item_id("tree"))
        add_action("do_climb","climb");
}

int
do_climb(string str)
{
    if(!str || (str != "tree" && str != "trees" && str != treetype && 
        str != treetype+" tree" && str != treetype+" trees"))
    {
        NF("Climb what?\n");
        return 0;
    }
    NF("You cannot climb the " + str + ", as even the lowest branches are too high.\n");
    return 0;
}
int     areatype,      /* 1=Grass 2=Bushes 3=Trees 4=Farmland 5=Rocky */
                       /* 6=Snow 7=Forest 8=Road 9=Barren (0 means no type-desc) */
        forest_density;
string  area,          /* eg "northern" */
        areadesc,      /* eg "green, grassy field", "dense thicket", "small clearing" */
        areaname,      /* eg "Anorien", "Lebennin", "Rohan", "Ithilien" */
        land,          /* "Gondor" */
        grass,         /* (1), (2), (3): eg "soft, light green grass" */
        extraline,     /* additional room description */
        treetype;      /* (3), (7): eg "oak" - NOT: "oak " (!) */
string  forest,           /* not used in the master */
        mountain;         /* not used in the master */

void    set_areatype(int i)	{ areatype = i; }

void    set_area(string s)	{ area     = s; }
void    set_areadesc(string s)	{ areadesc = s; }
void    set_areaname(string s)	{ areaname = s; }
void    set_land(string s)	{ land = s; }
void    set_grass(string s)	{ grass = s; }
void    set_extraline(string s)	{ extraline = s; }
void    set_treetype(string s)	{ treetype = s; }
void    set_forest(string s)	{ forest = s; }
void    set_mountain(string s)	{ mountain = s; }
