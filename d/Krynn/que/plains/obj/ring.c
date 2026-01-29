
#include "../local.h"

inherit "/std/container";

int contains_paper = 0;

void
create_armour()
{
    set_name("ring");
    set_adj("little");
    add_adj("gold");
    set_short("little gold ring");
    set_long("This is an ordinary looking little gold ring.@@scroll_in_it@@\n");
}

void
set_contain_paper()
{
    contains_paper = 1;
}

string
scroll_in_it()
{
    if (contains_paper)
      return " The ring is used to keep a scroll wrapped up inside.";
    return "";
}
