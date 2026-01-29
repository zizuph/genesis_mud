#include "defs.h"
inherit "/std/object";

int paper;

void
create_object()
{
    paper = 1;
    set_name("book");
    set_adj("strange");
    add_adj("red");
    set_short("strange red book");
    set_long("The book is bound in a glossy red material and imprinted with " +
           "strange-looking sybols on the cover and spine.\n");
    add_item(({"symbols", "strange-looking symbols", "strange symbols", 
                "cover", "spine", "letters"}),
            "The symbols look like arcane letters of some kind.\n");
    add_cmd_item(({"symbols", "strange-looking symbols", "strange symbols", 
                "cover", "spine", "letters"}), "read",
            "You do not understand the arcane language.\n");
    add_cmd_item(({"book", "strange book", "red book", "strange red book"}),
            "read", "@@read_book@@");
    add_prop(OBJ_I_WEIGHT,100);
    add_prop(OBJ_I_VOLUME,200);
    add_prop(OBJ_I_VALUE,10);
}

string
read_book()
{
    if(paper)
    {
        clone_object(MTRAIL_DIR + "paper")->move(TP);  
        paper = 0;
        return "As you start flipping through the pages, a folded sheet of " +
            "paper drops out of the pages and into your hands!\n";
    }
    else
    {
        return "You flip through these pages, but you begin to realize you "+
            "have no idea what these strange arcane magical words mean.\n";
    }
}

