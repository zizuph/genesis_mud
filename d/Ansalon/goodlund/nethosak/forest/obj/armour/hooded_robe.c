/**********************************************
 * Name: hooded silvery robe                  *
 * By  : Elmore.                              *
 * Date: Nov. 2000.                           *
 * Desc: A simple robe, that can be hooded to *
 *       add a sub-description to TP, or      *
 *       unhooded to remove it again.         *
 **********************************************/

/* few fixup done by Torqual - mainly hoodwearing routines */

inherit "/std/armour.c";

#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <ss_types.h> 
#include <files.h>
#include <formulas.h>
#include "/d/Ansalon/common/defs.h"
 
#define SUBLOC "ansalonRobe_subloc"

int robeHooded = 0;
string wearer_desc;

void
create_armour()
{ 
    set_name("robe");
    set_adj("hooden");
    add_adj("silvery");
    set_ac(35); 
    set_af(TO);
    set_at(A_ROBE);
    set_short("hooded silvery robe");
    set_long("This long robe has been made out of a soft silvery " +
             "material. A small hood has been attached to it making "+
             "for the wearer to hood themselves.\n");
    add_prop(OBJ_I_VOLUME, 525);
    add_prop(OBJ_I_WEIGHT, 540);
    add_prop(OBJ_I_VALUE, 700);
}
 
int
do_hood(string what)
{ 
    object wearer = TO->query_worn();

    /* if we do not wear that robe we fail to pull the hood */
   if (!objectp(wearer))
   {
	   NF("You must wear the robe first.\n");
	   return 0;
   }
   /* we do have it pulled on - we cannot do it one more time */
   if (robeHooded == 1)
   {
       NF("But you are already hooded!\n"); 
       return 0;
   }

   if ((what == "robe")  || (what == "the robe") || (what == "silvery robe"))
   {
       write("You glance suspiciously around, before slowly hooding yourself "+
             "with the robe, concealing your features.\n"); 
       robeHooded = 1;
       TP->add_subloc(SUBLOC, TO);
       return 1;
    }

    NF("Hood what? The robe?\n");
    return 0;
}

int
do_unhood(string what)
{
    object wearer = TO->query_worn();

   /* if we do not wear that robe we fail to remove the hood */
   if (!objectp(wearer))
   {
	   NF("You must wear the robe first.\n");
	   return 0;
   }
   /* ok we wear the robe but do not have it hooded */ 
   if (robeHooded == 0)
   {
       NF("But you aren't hooded!\n"); 
       return 0;
   }
  /* well we do have it worn and hooded, now lets see if we want to unhood it */
   if ((what == "robe")  || (what == "the robe") || (what == "silvery robe"))
   {
       wearer->catch_msg("You slowly unhood yourself, revealing " +
		       "your features again.\n"); 
       robeHooded = 0;
       TP->remove_subloc(SUBLOC);
       return 1;
   }
   NF("Unhood what?\n");
   return 0;
}
 
string
show_subloc(string subloc, object carrier, object for_obj)
{
    string str;

    if (carrier->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
        return "";

    if (for_obj == carrier)
        str = "Your features ";
    else
        str = capitalize(HIS(carrier)) + " features ";

    return str + "are hidden by the "+short()+".\n";
}



mixed 
wear(object what)
{
    return 0;
}


mixed
remove(object what)
{
    if (robeHooded == 1)
    {
	    do_unhood("robe");
    }
    return 0;
}


void
init()
{
    ::init();
    add_action(do_hood,"hood"); 
    add_action(do_unhood,"unhood");
}

