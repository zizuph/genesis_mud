/* Ashlar
   Catches the kills from the attackdragon
 */
inherit "/std/object";
#include <macros.h>
#include <composite.h>

#define LOGFILE "/d/Genesis/log/KILLS"
#define LOGFILE2 "/d/Genesis/log/KILLS.old"

string *gNames;

void
clear_results()
{
    gNames = ({ });
}

void
calc_sum()
{
}

void
sort_results()
{
}

string
show_results()
{
	int i;
	string s = "Killed by the attackdragon are; ";

	s +=
	  COMPOSITE_WORDS(gNames) + ".\n";
	return s;
}

int
read_results(string file)
{
	int i,j;
	string s,d;
	string *l,*t;

	s = read_file(file);
	if (!stringp(s) || (s==""))
		return 0;
	l = explode(s, "\n");
	for(i=0; i<sizeof(l); i++)
	{
	    string scrap1, name, monster;
	    int scrap2, scrap3;

	    sscanf(l[i], "%s (%d) by %s", name, scrap3, monster);
	    if (stringp(monster) && (monster == "/d/Ansalon/taman_busuk/neraka/npc/attackdragon"))
	    {
	    	
	    	if (stringp(name))
	    	{
	    	    t = explode(name, " ");
	    	    gNames += ({ t[sizeof(t)-1] });
	    	}
	    }
	}
	return 1;
}

void
create_object()
{
	set_name("kills");
	add_name("compiler");
	set_adj("dragon");
	set_adj("kills");
	set_short("dragon kills compiler");
	set_long("This object checks " + LOGFILE + " and " + LOGFILE2 + " for kills by the attackdragon.\n\n" +
	    "@@show_results@@\n");
	clear_results();
	set_alarm(0.5,0.0,&read_results(LOGFILE2));
	set_alarm(1.0,0.0,&read_results(LOGFILE));
	
}
