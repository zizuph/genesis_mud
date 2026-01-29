/*
 * Soul to filter the users list by guild or domain
 */

inherit "/cmd/std/soul_cmd";

#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <cmdparse.h>
#include <filter_funs.h>
#include <composite.h>
#include <filepath.h>

#define TP             this_player()
#define ETP            environment(TP)
#define TO             this_object()
#define NF(xx)         notify_fail(xx)

#define OCC  (0)
#define LAY  (1)
#define RACE (2)

#define R1   return 1;

string get_soul_id() { return "Sorgum User Filter"; }

mapping
query_cmdlist()
{
     seteuid(getuid(TO));
     return ([
         "vamps":"vamps",
        "rangers":"rangers",
        "calians":"calians",
        "knights":"knights",
        "glads":"glads",
        "mystics":"mystics",
        "bards":"bards",
        "druids":"druids",
        "squires":"squires",
        "brothers":"brothers",
        "monks":"monks",
        "wilds":"wilds",
        "travel":"travel",
        "grunts":"grunts",
        "hins":"hins",
	"rocks":"rocks",
	"bloods":"bloods",
	 "angmars":"angmars",
	"langmars":"langmars",	 
	 "mages":"mages",
	 "tricksters":"tricks",
	"thanars":"thanars",	      	      	 	 

	"onterel":"onterel",
	"ongen":"ongen",
	"onshire":"onshire",
	"onroke":"onroke",
	"onavenir":"onavenir",
	"ongondor":"ongondor",
	"onkrynn":"onkrynn",
	"onrhov":"onrhov",
	"oncalia":"oncalia",
	"onkalad":"onkalad",
	"oncirath":"oncirath",	      	      
         "onemerald":"onemerald",
	 "oncity":"oncity",
	"onimmortal":"onimmortal",	      	 	 
	      
            ]);
}

string display(object player, string loc)
{
    if (player->query_wiz_level()) 
	return sprintf("%11s (wiz) %s\n", player->query_name(), loc);

     return sprintf("%11s (%3d) %s\n", player->query_name(),
		   player->query_average_stat(), loc);
     
}

string find_and_display(object player)
{
     string loc;
     loc = environment(player) ? RPATH(file_name(environment(player))) :
	  "In the big black void.";
     return display(player, loc);
}
     
void pl(string long_name, string short_name, int guild_type)
{
     object *ul, *vm;
     int i;

     ul = users();
     vm = ({ });
     for (i = 0; i < sizeof(ul); i++)
          switch (guild_type) {
          case OCC:
               if (ul[i]->query_guild_name_occ() == long_name)
                    vm += ({ ul[i] });
               break;
          case LAY:
               if (ul[i]->query_guild_name_lay() == long_name)
                    vm += ({ ul[i] });
               break;
          case RACE:
               if (ul[i]->query_guild_name_race() == long_name)
                    vm += ({ ul[i] });
               break;
          }               
     
     if (!sizeof(vm)) {
          TP->catch_msg("No " + short_name + " are logged in.\n");
          return;
     }
     TP->catch_msg("The following " + short_name + " are logged in:\n");
     for (i = 0; i < sizeof(vm); i++) {
          TP->catch_msg(find_and_display(vm[i]));
     }
}

int vamps()    { pl("Vampyr guild",                  "vamps",      OCC);  R1}
int rangers()  { pl("Gondorian Rangers Guild",       "rangers",    OCC);  R1}
int calians()  { pl("Calian warrior's guild",        "calians",    OCC);  R1}
int monks()    { pl("Ancient Kaheda Order",          "monks",      OCC);  R1}
int glads()    { pl("Gladiator guild",               "glads",      OCC);  R1}
int knights()  { pl("Solamnian Knights",             "knights",    OCC);  R1}
int hins()     { pl("Shire",                         "hins",       OCC);  R1}
int mystics()  { pl("The Ancient Mystic Order",      "mystics",    OCC);  R1}
int angmars()  { pl("Angmar Army",                   "angmars",    OCC);  R1}
int mages()    { pl("Morgul Mages",                  "mages",      OCC);  R1}
int langmars() { pl("Angmar Army",                   "langmars",   LAY);  R1}
int bards()    { pl("The August Order of Minstrels", "bards",      LAY);  R1}
int brothers() { pl("Ancient Kaheda Order",          "brothers",   LAY);  R1}
int druids()   { pl("Sacred Order of Druids",        "druids",     LAY);  R1}
int squires()  { pl("Sentries of Solamnia",          "squires",    LAY);  R1}
int bloods()   { pl("Bloodguard guild",              "bloods",     LAY);  R1}
int tricks()   { pl("Tricksters",                    "tricksters", LAY);  R1}
int travel()   { pl("Traveller guild",               "travellers", RACE); R1}
int grunts()   { pl("Grunts guild",                  "grunts",     RACE); R1}
int wilds()    { pl("Wildrunner guild",              "wilds",      RACE); R1}
int rocks()    { pl("Rockfriend guild",              "rocks",      RACE); R1}
int thanars()  { pl("Thanarian human race guild",    "thanarians", RACE); R1}


/***************************************************************************/

void domain_filter(string domain)
{
     object *ul;
     string *path;
     string loc;
     int i;

     ul = users();
     for (i = 0; i < sizeof(ul); i++) {
	  if (environment(ul[i])) {
	       loc = file_name(environment(ul[i]));
	       path = explode(loc, "/");
	       if ((sizeof(path) >= 3) &&  (path[2] == domain))
		    TP->catch_msg(display(ul[i], loc));
	  }
     }
}

int onterel()   { domain_filter("Terel");     R1 }
int ongen()     { domain_filter("Genesis");   R1 }
int onshire()   { domain_filter("Shire");     R1 }
int onroke()    { domain_filter("Roke");      R1 }
int onavenir()  { domain_filter("Avenir");    R1 }
int ongondor()  { domain_filter("Gondor");    R1 }
int onkrynn()   { domain_filter("Krynn");     R1 }
int onrhov()    { domain_filter("Rhovanion"); R1 }
int oncalia()   { domain_filter("Calia");     R1 }
int onemerald() { domain_filter("Emerald");   R1 }
int onkalad()   { domain_filter("Kalad");     R1 }
int oncirath()  { domain_filter("Cirath");    R1 }
int oncity()    { domain_filter("City");      R1 }
int onimmortal(){ domain_filter("Immortal");  R1 }
