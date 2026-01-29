inherit "/std/book";

#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#define MORE_OBJECT "/obj/more.c"

#define RED_BOOK "/d/Earthsea/obj/book_chapters/"
object TO = this_object();



void
create_book()
{
    set_name("book");
    set_adj(({"red", "leather"}));
    set_short("red leather-bound book");
    set_long(break_string("A book with red leather binding. "+
	"On the cover is etched a figure of a golden fiery dragon. "+
	"The pages appear to be made from fine parchment. "+
	"Clearly this is a valuable treasure, since it is bound by "+
	"a gold chain to the table.\n", 70));

    set_max_pages(7);
    add_prop(OBJ_I_WEIGHT, 150);
    add_prop(OBJ_M_NO_GET, "The book cannot be taken.\n");
}



int
read_book_at_page(int page_no)
{
    object tp = this_player();
    object m;


    setuid();
    seteuid(getuid(TO));
    m = clone_object(MORE_OBJECT);
    switch(page_no)
    {
    case 1: 
	m->more(RED_BOOK + "index.txt", 1);
	break;

    case 2:
	m->more(RED_BOOK + "fog.txt", 1);
	break;

    case 3:
	m->more(RED_BOOK + "ged1.txt", 1);
	break;

    case 4:
	m->more(RED_BOOK + "hawk.txt", 1);
	break;

    case 5:
	m->more(RED_BOOK + "kemay.txt", 1);
	break;

    case 6:
	m->more(RED_BOOK + "tenar.txt", 1);
	break;

    case 7:
	m->more(RED_BOOK + "liliths_story.txt", 1);
    default:
	break;
    }
    return 1;
}
