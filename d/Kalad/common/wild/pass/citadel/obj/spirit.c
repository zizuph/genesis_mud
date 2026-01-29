inherit "/std/drink";
#include "/d/Kalad/defs.h"
/* by Sarr */

int open;

create_drink()
{
   set_soft_amount(100);
   set_alco_amount(0);
   set_name("pibb");
   add_name("can");
   add_adj("mr.");
   add_adj("mr");
   set_short("can of Mr. Pibb");
   set_pshort("cans of Mr. Pibb");
   set_long("This is a maroon colored tin can of soda. The odd looking "+
   "white face of a smiling geek that is the logo of the Pibb company "+
   "adorns the side. In bright white letters, the word 'Mr. Pibb' is "+
   "inscribed.\n");
    add_prop(HEAP_I_UNIT_WEIGHT, 20);
    add_prop(HEAP_I_UNIT_VOLUME, 10);
}

void
init()
{
    ::init();
    AA(do_open,open);
}

int
do_open(string str)
{
    object can;
    NF("Open what?\n");
    if(!parse_command("open "+str,TP,"'open' %o",can))
        return 0;
    if(can != TO)
        return 0;
    NF("The can is already open.\n");
    if(open)
        return 0;
    write("You pop open the "+short()+" with a loud hiss and "+
    "fizzle.\n");
    say(QCTNAME(TP)+" pops open the "+short()+" with a loud hiss "+
    "and fizzle.\n");
    open = 1;
    return 1;
}

void
consume_text(object *arr, string vb)
{
    write("You guzzle down "+COMPOSITE_DEAD(arr)+".\n");
    write("You beltch loudly, then crush the can in your hand and "+
    "throw it away.\n");
    say(QCTNAME(TP)+" guzzles down "+COMPOSITE_DEAD(arr)+".\n");
    say(QCTNAME(TP)+" beltches loudly, then crushes the can in "+
    HIS(TP)+" hand and throws it away.\n");
}

int
drink_it(string str)
{
    if(!open)
    {
        write("The "+short()+" is not opened!\n");
        return 1;
    }
    ::drink_it(str);
    return 1;
}

