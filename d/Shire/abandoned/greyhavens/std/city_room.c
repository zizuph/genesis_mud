#pragma save_binary
#pragma strict_types

#include "/d/Shire/sys/defs.h"
#include <ss_types.h>

#define AREATYPE_NONE            0
#define AREATYPE_WALLS           1
#define AREATYPE_BELOW_WALLS     2
#define AREATYPE_BOARDWALK       3
#define AREATYPE_MARKET_SHORLINE 4
#define AREATYPE_MARKET_CENTRAL  5
#define AREATYPE_RESIDENTIAL     6
#define AREATYPE_GOVERMENT       7
#define AREATYPE_ROAD            8
#define AREATYPE_VILLAGE         9

inherit SHIRE_ROOM;

// Prototypes:

public int     check_lightlevel();


// Global variables:
 
static int areatype;

static string  area = "boardwalk" ,
               areadesc = "shorline",  
               areaname = "City of Mithlond",
               land = "Eriador", 
               extraline = "Someplace in the city of Mithlond.",
               treetype = "eucalyptus",
	       population = "busy";


function vbfc_extra;

void
set_vbfc_extra(function f)
{
    vbfc_extra = f;
}

void   set_areatype(int i)       { areatype = i; }
void   set_area(string str)      { area = str; }
void   set_areadesc(string str)  { areadesc = str; }
void   set_areaname(string str)  { areaname = str; }
void   set_land(string str)      { land = str; }
void   set_extraline(string str) { extraline = str; }
void   set_treetype(string str)  { treetype = str; }
void   set_population(string str) { population = str; }

static string
short_desc()
{
    string  desc;

    switch (areatype)
    {
    case AREATYPE_WALLS:
        if (!item_id("walls"))
            add_item("walls","The walls are made of white stone.\n");
        desc = "atop the walls "+areadesc+" "+area+" "
        + areaname+" in "+land;
        break;
	
    case AREATYPE_BELOW_WALLS:
        if (!item_id("walls"))
            add_item("walls","The walls are made of white stone.\n");
        desc = "atop the walls "+areadesc+" "+area+" "
        + areaname+" in "+land;
        break;

    case AREATYPE_ROAD:
        if (!item_id("road"))
            add_item("road", "You are on a well-kept road in "+land
                + ".\n");
        if (!item_id("ground"))
            add_item("ground","You see a well-kept road.\n");
        desc = "a road across "+LANG_ADDART(areadesc)+" "
        + area+" "+areaname+" in "+land;
        break;
	

   case AREATYPE_VILLAGE:
        if (!item_id("road"))
            add_item("road", "You're on a dusty road passing through "+
                "the "+areadesc+" of "+areaname+".\n");
        desc = "a road passing through the "+areadesc+" of "+
        areaname +" in " + land;
        break;


   default:
   desc = LANG_ADDART(areadesc)+" "+area+" "
   + areaname+" in "+land;
   break;
    }
    return desc;
}

string
describe_time(string time)
{
    string desc;

    switch (time)
    {
    case "night":
   desc = "Night time covers "+areaname+". ";
   switch (CLOCK->query_moon())
   {
   case "full":
       desc += "A full moon sheds some light across the land. ";
       break;
   case "waxing crescent":
   case "waxing gibbous":
   case "waning gibbous":
   case "waning crescent":
       desc += "The moon sheds a little light across the land. ";
       break;
   default:
       desc += "The sky is covered with dark clouds, and "+
       "not even the moon shines through. ";
       break;
   }
   break;
    case "afternoon":
   desc = "The light of day shines across " + areaname + "."+
   " It is afternoon. ";
   break;
    case "morning":
   desc = "The sun is on its way up in the morning sky "
   + "to the east. ";
   break;
    case "noon":
   desc = "The sun is almost at its peak on its way across "
   + "the sky. It is noon in " + areaname + ". ";
   break;
    case "evening":
   desc = "The sun is setting in the west, colouring the sky "
   + "golden red. ";
   break;
    case "early morning":
   desc = "The sun is rising in the east, casting long shadows "
   + "across "+areaname+". ";
   break;
    }
    return desc;
}


public string
long_desc()
{
    string  time  = CLOCK->query_time_of_day(),
    desc = CAP(query_short()) + ". ";

    if (strlen(extraline))
        desc += extraline;
    if (functionp(vbfc_extra))
        desc += " " + vbfc_extra();
    return (BSN(desc));
}


void
create_area_room()
{
}

nomask void
create_shire_room()
{
    remove_prop(ROOM_I_INSIDE);
    add_prop(ROOM_I_LIGHT, check_lightlevel);

    create_area_room();

    set_short(short_desc());
    set_long(long_desc);
}

public int
check_lightlevel()
{
    switch (tod())
    {
    case "night":
   return 1;
   break;
    case "early morning":
    case "evening":
   return 2;
   break;
    case "morning":
    case "noon":
    case "afternoon":
   return 3;
   break;
    default:
   return 1;
    }
}

int
query_road()
{
    if (areatype == AREATYPE_ROAD || areatype == AREATYPE_VILLAGE)
   return 1;
    return 0;
}

