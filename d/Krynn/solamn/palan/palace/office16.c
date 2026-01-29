/* created by Aridor 09/14/93 */

#include "../local.h"

inherit ROOM_BASE

#include <macros.h>

string *give_form, *give_form_2;

string
query_to_jail()
{
  return "south";
}

void
create_palan_room()
{
    set_short("Office");
    set_long(BS("This is a small office. A window lets in light from the "
          +  "north. There is a wooden desk and a chair here, but you "
          +  "can't see anybody around.", SL));

    add_item("desk",BS("There are a lot of papers laying on the desk. You "
          +  "can make out some empty form sheets.", SL));
    add_exit(PALACE + "hall10","south",0,0);
    reset_room();
}

init()
{
    add_action("take_form","get");
    add_action("take_form","take");
    ::init();
}

void
reset_palan_room()
{
    give_form = ({});
    give_form_2 = ({});
}


int
take_form(string str)
{
    string the_name = TP->query_real_name();
    if (str != "form" && str != "sheet" &&
        str != "form sheet" && str != "paper" &&
        str != "form from desk" && str != "sheet from desk" &&
        str != "form sheet from desk" && str != "paper from desk")
    {
        NF("Take what?");
        return 0;
    }
    if ((member_array(the_name, give_form) != -1) && (member_array(the_name, give_form_2) != -1))
    {
         write("You already got yourself some forms not too long ago!\n");
         write("We have to keep an eye on our money even if you don't!\n");
         return 1;
    }
    if (member_array(the_name, give_form) == -1)
      give_form += ({ the_name });
    else
      give_form_2 += ({ the_name });
    write("You take a form from the desk.\n");
    say(QCTNAME(TP) + " takes a form from the desk.\n");
    clone_object(OBJ + "aform")->move(TP);
    return 1;
}


