/*     The standard Field-of-Gondor-file, made by Elessar for Genesis      */
/*     February 1992. No copyrights, but would like to have my name     */
/*     mentioned if anyone modifies this file for own use.                	    */
/*
* Modification log:
* - Converted from a field file to a village-maker file for use in the Shire.
*    Elix January 1995
*/

#pragma save_binary

inherit "/d/Shire/room";
inherit "/d/Gondor/common/lib/herbsearch.c";

#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Shire/common/defs.h"

int  areatype;   	/* 1=hamlet 2=village 3=town 4=city 
			* (0 means no type-desc)
			*/

string areadesc,  	/*eg "track", "path", "street", "road" */
	areaname,  	/* eg "Mithlond", "Michel Delving", "Hobbiton", "Bree" */
	land,      	/* "the Shire" */
	areatype1, 	/* calculated from areatype */
	extraline; 	/* additional room description */


string short_func()
{
   switch(areatype)
   {
      case 1:
      areatype1 =  "hamlet";
      return "A "+areadesc+" running through the small hamlet of "
      			+areaname+" in "+land;
      case 2:
      areatype1 =  "village";
      return "A "+areadesc+" running through the village of "
      			+areaname+" in "+land;
      case 3:
      areatype1 =  "town";
      return "A "+areadesc+" running through the town of "
      			+areaname+" in "+land;
      case 4:
      areatype1 =  "city";
      return "A "+areadesc+" running through the city of "
      			+areaname+" in "+land;
   }
}

void make_the_room()
{
   set_short("@@short_func@@");
   set_long("@@describe@@");
   
   switch(areatype)
   {
      case 1:
      add_item(" ",".\n");
      break;
      case 2:
      add_item(" ",".\n");
      break;
      case 3:
      add_item(" ",".\n");
      break;
      case 4:
      add_item(" ",".\n");
      break;
   }
   add_prop(ROOM_I_INSIDE,0);
   add_prop(ROOM_I_LIGHT,"@@check_lightlevel");
}

string describe() 
{
   object  clock      = find_object(CLOCK);
   string  time       = clock->query_time_of_day(),
   long_descf = short_func() + ". ";
   
   if (!clock->query_war()) 
      {
      switch(time)
      {
         case "night":
         long_descf += "Darkness covers the "+areatype1+", as it is night in "
         			+land+". Here and there, you can see glimmers "
         			+"of light from indoors, and you can smell the "
         			+"cooking fires. ";
         
         switch(clock->query_moon())
         {
            case "full":
            long_descf += "The darkness is not complete, as a full moon "
            			+"high overhead illuminates the area with "
            			+"a soft light, casting shadows across the "
            			+areadesc+". ";
            break;
            case "waxing crescent":
            case "waxing gibbous":
            case "waning gibbous":
            case "waning crescent":
            long_descf += "The blackness of the night is lessened "
            			+"somewhat by the moon above casting "
            			+"a pale and wan light over the "
            			+areatype1+". ";
            break;
            default:
            long_descf += "The sky above is covered from east to west with "
            			+"fast-moving storm clouds that cover "
            			+"the face of the moon. ";
            break;
            }
         break;
         case "afternoon":
         long_descf += "The sun casts its warmth down upon you as it "
         			+"makes its way to its home in the west. "
         			+"It is afternoon in "+land+", and the smell "
         			+"of cakes cooking drifts from indoors. ";
         break;
         case "morning":
         long_descf += "The sun is on its way up in the morning sky to "
         			+"the east. From indoors, you can hear "
         			+"hobbits waking, and cooking their first "
         			+"meals for the day. ";
         break;
         case "noon":
         long_descf += "The sun is almost at its peak on its way across the "
         			+"sky. It is the middle of the day in "
         			+"Middle-Earth, and most hobbits are indoors "
         			+"feasting on their lunches. ";
         break;
         case "evening":
         long_descf += "The sun is setting in the west, coloring the sky with "
         			+"a palette of golds and reds and pinks.  These "
         			+"colours are reflected in the windows of the "
         			+areatype1+". ";
         break;
         case "early morning":
         long_descf += "The sun is rising in the east, casting long shadows "
         			+"across the "+areatype1+". ";
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
         long_descf += "Massive dark clouds cover the sky, making it "
         			+"difficult to tell night from day. The clouds "
         			+"seem to be coming from the mountains to "
         			+"the east, where the land of Mordor lies. "
         			+"You suspect it is night now, as it is as dark "
         			+"as it can get. ";
         break;
         case "morning":
         long_descf += "A thick cover of clouds prevent the sun from "
         			+"shining over "+land+", and it is "
         			+"almost as dark as nightime. However you "
         			+"gather that it is probably morning, as it is "
         			+"getting a bit lighter than earlier. ";
         break;
         case "noon":
         long_descf += "A dark mass of boiling clouds seems to be rolling "
         			+"in from the east, covering the sky above "
         			+land+". It is not much lighter now than it "
         			+"usually is at night, but still you suspect it is "
         			+"the middle of the day. ";
         break;
         case "afternoon":
         long_descf += "A thick mass of clouds cover the sky, making it "
         			+"difficult to see far. You suspect that it is "
         			+"afternoon, as it is getting a bit darker than "
         			+"earlier. ";
         break;
      }
   }
   if (extraline) 
      long_descf += extraline;
   return (BSN(long_descf));
}

int check_lightlevel()
{
   return 1;
}
