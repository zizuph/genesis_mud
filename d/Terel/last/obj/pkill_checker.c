
#include "/d/Terel/include/Terel.h"
inherit "/std/object";

#define M_ORDER ([ \
 "Jan":1, "Feb":2, "Mar":3, "Apr":4, "May":5, "Jun":6, \
 "Jul":7, "Aug":8, "Sep":9, "Oct":10, "Nov":11, "Dec":12 ])

#define PKILL_LOG "/d/Genesis/log/PKILLS"

/* Returns 1 if killer ever pkilled victim after given date.
	*/
public int check_kill(string victim, string killer, string date);

/* Returned 1 if date1 is smaller(before) date2 */
int date_smaller(string date1, string date2);


create_object()
{
	set_name("pkill_checker");
}

int date_smaller(string date1, string date2)
{
	string *s1 = explode(date1, " ");
	string *s2 = explode(date2, " ");
	int y1, y2, d1, d2, hh1, hh2, mm1, mm2, ss1, ss2;
	
	/* I don't need day of the week */
	s1 -= ({s1[0]});
	s2 -= ({s2[0]});
	
	/* I don't need white spaces*/
	s1 = filter(s1, &strlen());
	s2 = filter(s2, &strlen());
	
	/* Sanity check */
	if(sizeof(s1) != 4 || sizeof(s2) != 4)
		return -1;
	
	sscanf(s1[3], "%d", y1);
	sscanf(s2[3], "%d", y2);
	/*year*/
	if(y1 < y2)
		return 1;
	if(y1 > y2)
		return 0;
	
	/*month*/
	if(M_ORDER[s1[0]] < M_ORDER[s2[0]])
		return 1;
	if(M_ORDER[s2[0]] < M_ORDER[s1[0]])
		return 0;
	
	sscanf(s1[1], "%d", d1);
	sscanf(s2[1], "%d", d2);
	/*day*/
	if(d1 < d2)
		return 1;
	if(d1 > d2)
		return 0;
	
	/*hour*/
	sscanf(s1[2], "%d:%d:%d", hh1, mm1, ss1);
	sscanf(s2[2], "%d:%d:%d", hh2, mm2, ss2);
	if((3600 * hh1 + 60 * mm1 + ss1) < (3600 * hh2 + 60 * mm2 + ss2))
		return 1;
	return 0;
}
	
public int check_kill(string victim, string killer, string date)
{
	/* line from log, names taken from log */
	string line, t_who, t_whom;
	/* iterator, index in exploded line, index of last date part in line*/
	int tmp  = 1, line_index, date_end;
	/* exploded line */
	string *s ;
	victim = capitalize(victim);
	killer = capitalize(killer);
	
	while(tmp > 0)
	{
		if(stringp(read_file(PKILL_LOG, tmp, 1)))
		{
			line = read_file(PKILL_LOG, tmp, 1);
			if(strlen(line))
			{
				s = explode(line, " ");
				if(sizeof(s) < 3)
					return 0;
				line_index = 2; //0 is for day of the week, 1 is for month
				while(!strlen(s[line_index]) || s[line_index][0] < 65) // 65 is A - players have names above that.
				{
					++line_index;
					if(line_index >= sizeof(s))
						return 0;
				}
				date_end = line_index - 1;
				t_who = s[line_index];
				line_index = member_array("by", s);
				/* Second check to avoid leaving vector range */
				if(line_index == -1 || line_index == sizeof(s) - 1)
					return 0;
				++line_index;
				while(!strlen(s[line_index]) || s[line_index][0] < 65)
				{
					++line_index;
					if(line_index >= sizeof(s))
						return 0;
				}
				t_whom = s[line_index];
				
				/* Kill confirmed */
				if(t_who == victim && t_whom == killer)
				{
					/* he killed him after the bounty was declared */
					if(date_smaller(date, implode(s[0..date_end], " ")))
						return 1;
				}
				
			}
			++tmp;
		}
		else
			tmp = 0;
	}
	return 0;
}
