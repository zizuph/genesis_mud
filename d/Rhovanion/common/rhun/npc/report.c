inherit "/std/object";

#include <stdproperties.h>
#include "/d/Rhovanion/defs.h"
#include <macros.h>

void create_object()
{
  add_prop("_seal_is_intact_",1);
  set_short("official report");
  set_name("report");
  set_adj("official");
  set_long("This is a report of some kind. It is sealed so you can't "+
           "read it unless you break the seal.\n");
  add_item(({"seal","wax","red wax"}), "@@seal_desc");
}

string seak_desc()
{
  if(query_prop("_seal_is_intact_"))
    return "The simple red wax seal disables anyone from reading report.\n";
  return "It has been broken so report is readable now.\n";
}

void init()
{
  ::init();
  add_action("report_break","break");
  add_action("report_read","read");
}

int report_break(string str)
{
    NF("Break what?\n");
    if((str != "seal") && (str != "wax")) return 0;

    if(query_prop("_seal_is_intact_"))
    {
      write("You break the seal, enabling you to read the report.\n");
      say(QCTNAME(TP)+" breaks the seal on a report "+HE(TP)+"'s holding.\n");
      remove_prop("_seal_is_intact_");
      set_long("This is a report of some kind. The seal has been broken.\n");
    }
    else write("The seal is already broken.\n");
    return 1;
}

int report_read(string str)
{
  NF("Read what?\n");
  if(str != "report") return 0;
  
  if(query_prop("_seal_is_intact_"))
  {
    write("The report is sealed with red wax.\n");
    return 1;
  }

  write("You are not sure if you are supposed to do this, but you do it"
        + " anyway. The report reads :\nSorry about being late with the"
	+ " report. It's pretty much the usual around here, we've seen a"
        + " couple of Easterlings. By the way, that fella you sent down"
	+ " here to remind me seemed really untrustworthy.\n");
  say(QCTNAME(TP) + " reads a report.\n");
  return 1;
}


