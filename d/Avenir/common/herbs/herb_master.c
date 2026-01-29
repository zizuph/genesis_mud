#pragma strict_types
// file name:        /d/Avenir/common/herbs/herb_master.c
// creator(s):       Lilith, Nov 96
// purpose:          Ease of adding herbs to areas. No more need to 
//                   hunt around, trying to decide which of the 100+
//                   available herbs are suitable for your area.
// note:             Adapted from Gondor's herb_master.c
//                   See example_herb_room.c for help
//
//   POSSIBLE AREA TYPES ARE AS FOLLOWS:
//   arctic (artic); beach (shore, seashore); boreal (forest); 
//   cave (dark, Utterdark); desert; garden; jungle; pine; 
//   river (riverbank, stream); saltmarsh (estuary);
//   sea (ocean, underwater); wetland (bog, marsh, swamp);
/*
 * Revisions:
 * 	Lucius, Jul 2017: Re-coded and made more efficient.
 * 			  Also modified to not return duplicate
 * 			  entries when querying multiple areas.
 */
#pragma no_clone

#include "herb_list.h"

public static string *herbs = HERBS;
public static mapping herb_areas = HERB_AREAS,
		      area_alias = AREA_ALIAS;

public void
remove_object(void)
{
    destruct();
}

public varargs string *
query_herbs(mixed areatype)
{
    string *area_herbs = ({ });

    if (!areatype)
        return secure_var(herbs);

    if (stringp(areatype))
	areatype = ({ areatype });

    foreach(string area: map(areatype, lower_case))
    {
	if (strlen(area_alias[area]))
	    area = area_alias[area];

	if (sizeof(herb_areas[area]))
	    area_herbs |= herb_areas[area];
    }

    return area_herbs;
}

/*
 * Validate that file paths are all correct,
 * does not test loading.
 */
public int
validate_herbs(string area)
{
    if (area == "herbs")
    {
	foreach(string file: herbs)
	{
	    write(sprintf(" [%1d] %s\n",
		    file_size(file + ".c") > 0, file));
	}
    }

    if (area == "areas")
    {
	foreach(string key, string *data: herb_areas)
	{
	    write(upper_case(key) + ":\n");
	    foreach(string file: data)
	    {
		write(sprintf("  [%1d] %s\n",
			file_size(file + ".c") > 0, file));
	    }
	}
    }

    write("Argument should be one of either 'herbs' or 'areas'.\n");
    return 1;
}
