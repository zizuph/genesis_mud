//
// srmaster - master object (room) for Sean-Rhian information
//
// History:
// Date        Coder            Action
// ----------  ---------------  -----------------------------------
// 7/4/98      Zima             Started
//
inherit "/d/Khalakhor/std/room";
#include "defs.h"
 
// indices should match constants in srguild.h
public string *kirks  =
       ({
       "Kirk Maighal",
       "Kirk Seanchan-Tor"
       });
 
//
// query_kirk
//
public string query_kirk(int kirk)
{
   if ((kirk<1)||(kirk>SR_NUM_KIRKS)) return "";
   return kirks[kirk-1];
}
 
//
// query_sr_title
//
public string query_sr_title(int level, int kirk)
{
   string t="";
   switch (level)
      {
      case 10:  t = "Novishagh";             break;
      case 11:  t = "Scoillar";              break;
      case 12:  t = "Shirreyder";            break;
      case 13:  t = "Ebbeyder";              break;
      case 20:  t = "Searmanagh";            break;
      case 21:  t = "Pious Searmanagh";      break;
      case 22:  t = "Reverent Searmanagh";   break;
      case 23:  t = "Elder Searmanagh";      break;
      case 30:  t = "Diaghin";               break;
      case 31:  t = "Devout Diaghin";        break;
      case 32:  t = "Worshipful Diaghin";    break;
      case 33:  t = "Ard-Diaghin";           break;
      case 40:  t = "Saggart";               break;
      case 41:  t = "Venerable Saggart";     break;
      case 42:  t = "Reverend Saggart";      break;
      case 43:  t = "Ard-Saggart";           break;
      case 50:  return "Ard-Saggart of Sean-Rhian and Presbytair of "+
                query_kirk(kirk);
      case 60:  t = "Ard-Athair of "+query_kirk(kirk); break;
      case 70:  return "Seirsanach of the Order of Sean-Rhian and "+
                       "Ard-Athair of "+query_kirk(kirk);
      default:  return "Disciple of Sean-Rhian";
      }
   return t+" of the Order of Sean-Rhian";
}
 
//
// create_khalakhor_room
//
void create_khalakhor_room()
{
   set_short("Sean-Rhian master room");
   set_long("Sean-Rhian master room.\n");
}
