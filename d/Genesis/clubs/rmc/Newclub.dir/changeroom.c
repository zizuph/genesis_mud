inherit "/std/room";

#include "xdefs.h"
#include <std.h>
#include <stdproperties.h>

mixed *rdata;
static int leava = 0;
static int mbwealth;
int howmuch;
int president, vicepres;
string npresident, nvicepres;
mapping richdata;


public void
create_room()
{
  seteuid(getuid(TO));

  set_short("The Rich Men's ClubVar Changer Room");
  set_long(break_string("This is th RMC Var Changer Room. It can "+
			"change the huge mixed array containing the "+
			"member vars to a mapping instead. The command "+
			"for that is 'changevars'.\n",60));
  
  INSIDE;

  rdata = ({});
  
  restore_object(RICH_OBJ);
}

void
init()
{
    ::init();

    add_action("changevars", "changevars");
}

int
changevars()
{
    int sz, i;
    string *s, *t;

    npresident = rdata[president][0];
    nvicepres  = rdata[vicepres][0];

    sz = sizeof(rdata);

    s = (({ rdata[0][0], }));
    t = (({
	     ({rdata[0][1], 0, rdata[0][2], rdata[0][3], rdata[0][4],
	       rdata[0][5], rdata[0][6], rdata[0][7], rdata[0][8],}),
        }));
	  
    for (i = 1; i < sz; i++)
    {
	s += (({ rdata[i][0], }));
	t += (({
	         ({rdata[i][1], i, rdata[i][2], rdata[i][3], rdata[i][4],
	           rdata[i][5], rdata[i][6], rdata[i][7], rdata[i][8],}),
	     }));
    }

    richdata = mkmapping(s, t);
    
    save_object("/d/Immortal/rclub/Newclub.dir/newrich");
    write("Ok. Variable change done.\n");

    return 1;
}
