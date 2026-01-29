#include "/d/Raumdor/defs.h"
inherit "/std/object.c";


void
create_object()
{
    set_name("book");
    add_adj("dusty");
    add_adj("black");
    set_short("black dusty book");

    set_long("This book is very old and tattered. It is covered with "+
    "smooth black leather such as you have never seen before. However, "+
    "all its pages have been torn out, save one. You can 'read book' "+
    "to read it. On the cover is a large circle and pentagram, and the "+
    "letters under it reading 'Daemonialitas ex Sinistrari'\n");

}


int
do_read(string str)
{
    NF("Read what?\n");
    if(str != "book")
        return 0;
    if(TP->query_skill(SS_LANGUAGE) < 45)
    {
        write("You read the page, but have no idea what it says, it is "+
        "in some ancient language long forgotten:\n"+
        "Promittunt Diabolo statis temporibus sacrificia, et oblationes; "+
        "singulis quindecim diebus, vel singulo mense saltem, necem "+
        "alicujus infantis, aut mortale veneficium, et singulis hebdomadis "+
        "alia mala in damnum humani generis, ut grandines, tempestates, "+
        "incendia, mortem animalium. \n");
        return 1;
    }    
    write("You read the torn page:\n"+
    "Most of the demons of the Hell do not come to our mortal plane, "+
    "for fear of being too vulnurable to the powers of Heaven. Thus, "+
    "one must entice or trick one into this plane. To do so, you must "+
    "be able to communicate with one. If you construct a communing "+
    "chamber, and etch the pentagram and circle in its center, with "+
    "the proper magical items along its edge and center, you can "+
    "try to commune with one. To do so you will need protection, and "+
    "the --\n"+
    "The page breaks here, the bottom half seems to have been ripped "+
    "out.\n");
    return 1;
}

void
init()
{
    ::init();
    add_action("do_read","read");
}


