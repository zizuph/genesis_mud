inherit "/std/object";

#include "/d/Shire/common/defs.h"

void
create_object()
{
    set_name("finder");
    set_short("herb finder");
    set_long("Igneous' Herb Finder.  Type 'find' or 'find <herb>' "+
      "to see if herbs grow in the room your in.\n");
}

void
init()
{
    ::init();
    add_action("find","find");
}


int
find(string str)
{
    int i;
    string *filenames;

    filenames = ENV(TP)->query_herb_files();

    if (!filenames)
    {
	notify_fail("Sadly this area is to hostile to grow herbs.\n");
	return 0;
    }
    if (!str || str == "all" || str == "herbs")
    {
	for (i == 1;i < sizeof(filenames);i++)
	    write(filenames[i]->query_herb_name()+".\n");
	return 1;
    }
    if (member_array(str,filenames->query_herb_name()) == -1)
    {
	notify_fail("The herb known as "+str+" does not grow here.\n");
	return 0;
    }
    write("The herb known as "+str+" is known to grow in this area.\n");
    return 1;
}
