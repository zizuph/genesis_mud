/*
 * Box for gifts
 * -- Finwe, November 2001
 */

inherit "/std/container";
#include "defs.h"
#include "/d/Shire/sys/defs.h"

string oname,gname;

void
set_box_name(string nam, string gnam)
{
    oname = nam;
    gname = gnam;
}


void
set_box_color(string color, string bow)
{
    set_short(color+" wrapped gift with a "+bow+" bow");
    set_long("This is a box wraped with beautiful "+color+" wrapping "+
    "paper. On the top, there sits a magnificant "+bow+" bow. There "+
    "is a little tag on the top.\n");
//    add_item("tag","To "+oname+", from "+gname+".\n");

    add_item("tag", "Maybe you should read it.\n");
    add_cmd_item("tag", "read", "@@read_tag@@");
            
    set_adj(color);
}

void
create_container()
{
    set_name("gift");
    add_name("box");
    set_short("white box");
    set_long("A plain white box.\n");
    add_prop(CONT_I_CLOSED,1);
    add_prop(CONT_I_WEIGHT,100);
}

void
init()
{
    ::init();
    add_action("do_unwrap","unwrap");
}

int
do_unwrap(string str)
{
    int i;
    object box,*contents;
    NF("Unwrap what?\n");
    if(!parse_command("unwrap "+str,TP,"'unwrap' %o",box))
        return 0;
    if(box != TO)
        return 0;
    write("You unwrap the "+short()+".\n");
    say(QCTNAME(TP)+" unwraps the "+short()+".\n");
    contents = all_inventory(TO);
    for(i=0;i<sizeof(contents);i++)
    {
        write("You discover a "+contents[i]->short()+" and "+
        "take it out of the box.\n");
        contents[i]->move(TP,1);
    }
    write("You discard the box.\n");
    remove_object();
    return 1;
}

string
read_tag()
{
    return "The simple tag reads:\n\n"+
        "\tTo "+CAP(oname)+", from "+CAP(gname)+".\n"+
        "\tEnjoy!\n\n";
    }