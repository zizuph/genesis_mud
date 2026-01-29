#pragma strict_types
/*
 * This is the book used by the Union Archives.
 */
#include <math.h>
#include <language.h>
#include <composite.h>

#include "../defs.h"
inherit (LIB + "book");

public string
vbfc_long(void)
{
    return "This is "+ LANG_ADDART(short()) +
	" from the Union Archives. Printed in large bold letters "+
	"along the spine of this "+ book_type +" is '"+ book_title +"'. "+
	"Along the cover, writ in a flowing and elegant script is:\n\t"+
	(strlen(book_summary) ? book_summary : book_title) + "\n\tWritten by "+
	COMPOSITE_WORDS_WITH(map(book_authors, capitalize), "and") +"\n";
}

private string *book_adjs = ({
  "black", "blue", "red", "parchment",
  "dusty", "heavy", "leather-bound", "white",
  "iron-bound", "silver-clasped", "hide-bound",
  "steel-bound", "brass-clasped", "elegant",
});

/*
 * Create adjectives based on book title and size.
 */
private string *
get_book_adjs(void)
{
    string *result = ({"",""});

    switch(file_size(scroll_file))
    {
    case 0..1000:      result[0] = "tiny";		break;
    case 1001..2500:   result[0] = "small";		break;
    case 2501..5000:   result[0] = "thin";		break;
    case 5001..8000:   result[0] = "medium-sized";	break;
    case 8001..12000:  result[0] = "large";		break;
    case 12001..20000: result[0] = "heavy";		break;
    default: result[0] = "massive";			break;
    }

    result[1] = book_adjs[NAME_TO_RANDOM(book_title, 1973, sizeof(book_adjs))];

    return result;
}

public void
finalize_book(void)
{
    string *adjs = get_book_adjs();

    set_adj(adjs);
    set_short(implode(adjs, " ") + " " + book_type);
    set_long("@@vbfc_long@@");
    add_name("Union_book_id");
}
