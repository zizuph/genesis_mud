/* Ashlar, 21 Jul 97
   Compiles the results of the KILLS log and displays them
 */
inherit "/std/object";
#include <macros.h>

#define LOGFILE "/d/Genesis/log/KILLS"

mapping gResults;
string *gDomains;
int gSum;

void
clear_results()
{
	gResults = ([ ]);
	gDomains = ({ });
	gSum = 0;
}

void
calc_sum()
{
    int i;
    gSum = 0;

	for(i=0; i<sizeof(gDomains); i++)
	{
		gSum += gResults[gDomains[i]];
	}
}

void
sort_results()
{
    int i,j,passagain;
    string t;
    
    for(j = sizeof(gDomains)-1; j > 0; j--)
    {
        passagain = 0;
        for(i=0; i<j; i++)
        {
            if (gResults[gDomains[i]] < gResults[gDomains[i+1]])
            {
                t = gDomains[i];
                gDomains[i] = gDomains[i+1];
                gDomains[i+1] = t;
                passagain = 1;
            }
        }
        if (!passagain)
            break;
    }
}

string
show_results()
{
	int i,p;
	string s,*domains;

	s = "No Domain       Kills % of total\n" +
	    "-- ------------ ----- ----------\n";
	for(i=0; i<sizeof(gDomains); i++)
	{
		p = gResults[gDomains[i]];
		s += sprintf("%2d %-12s %5d ",i+1,gDomains[i],p);
		if (gSum)
			s += sprintf("%10.3f", itof(p)/itof(gSum)*100.0);
		s += "\n";
	}
	s +=
	  "\nPlayers killed: " + sprintf("%5d",gSum) + "\n";
	return s;
}

int
read_results()
{
	int i,j;
	string s,d;
	string *l,*t;
    setuid();
    seteuid(getuid());

	s = read_file(LOGFILE);
	if (!stringp(s) || (s==""))
		return 0;
	l = explode(s, "\n");
	for(i=0; i<sizeof(l); i++)
	{
	    t = explode(l[i], " by ");
	    if (sizeof(t) != 2)
	        continue;
        if (t[1] == "poison")
            d = "<POISON>";
		else if(sscanf(t[1],"/d/%s/",d) != 1)
			continue;
	    if(member_array(d,gDomains) == -1)
	    {
	        gResults += ([ d : 1 ]);
	        gDomains = m_indexes(gResults);
        }
	    else
	        gResults[d] += 1;
	}
	sort_results();
	calc_sum();
	return 1;
}

void
create_object()
{
	set_name("kills");
	add_name("compiler");
	set_adj("kills");
	set_short("kills compiler");
	set_long("This object compiles " + LOGFILE + " in domain order.\n\n" +
	    "@@show_results@@\n");
	clear_results();
	set_alarm(0.5,0.0,read_results);
}
