/*
 *  Cirion 040296
 *
 *  Moved gallery statue code to a single source header.
 */
#ifndef __GALLERY_STATUES__
#define __GALLERY_STATUES__

#include <language.h>

public static int stsize;
public static string *statues = ({ });

public string
fixup_desc(string desc)
{
    string *arr = explode(implode(explode(desc, ". "), ".\n   "), "\n");

    desc = "";
    foreach(string str: arr)
    {
	if (str[0] != ' ')
	{
	    desc += str + "\n";
	    continue;
	}

	str = break_string(implode(explode(str, "  "), " "), 76);
	desc += implode(explode(str, "\n"), "\n    ") + "\n";
    }
    return desc;
}

public void
make_statues(int room, string str)
{
    int i, j;

    statues = GET_STATUES(room);
    stsize = sizeof(statues);

    if (!stsize)
    {
	set_long(str + "\n");
	return;
    }

    set_long(str + " Along the walls of the room are "+
	LANG_WNUM(stsize / 2) +" statues of various "+
	"materials and styles.\n");

    /* Item name: statue 1, first statue,
     *            statue of cirion, cirion
     */
    for(i = 0,j = 1; i < stsize; i += 2, j++)
    {
	str = fixup_desc(statues[i+1]);
	add_item(({"statue "+ j, LANG_WORD(j) +" statue",
	    "statue of "+ statues[i], statues[i] }), str);
    }

}

public string
exa_statues()
{
    string *names = ({});

    if (!stsize)
	return "There are no statues here.\n";

    for(int i = 0; i < stsize; i += 2)
	names += ({ CAP(statues[i]) });

    return "There are "+ LANG_WNUM(stsize/2) +" statues aligned "+
	"along the walls of great and noble heroes as well as "+
	"ancient powerful wizards. From the plaques at the base "+
	"of the statues, you see the names "+
	COMPOSITE_WORDS(names) +".\n";
}

#endif  __GALLERY_STATUES__
