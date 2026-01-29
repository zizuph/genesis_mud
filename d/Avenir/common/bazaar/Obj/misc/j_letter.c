// Letter that Jadestone needs delivered to Mergula
// -Ilyian, Oct 1995

inherit "/std/object";
#include "/d/Avenir/common/common.h"

int do_open(string str);

create_object()
{
   set_name("letter");
   add_name("_letter_from_jadestone");
   set_adj(({"sealed","white"}));
   set_short("white sealed letter");
   set_long("This is a letter, folded into thirds on a "
           +"crisp and strong white paper. On the front, "
           +"written in an elegant flowing script, is:\n"
           +"To: Galerin icu Ra'let.\n"
           +"    For your eyes only.\n");
   add_item("seal","The seal on the letter is made from "
           +"red wax, and inscribed in the seal is a cursive "
           +"letter J.\n");
   add_cmd_item("letter","read","The white letter is sealed closed.\n");
 
   add_prop(OBJ_I_VOLUME, 10);
   add_prop(OBJ_I_WEIGHT, 10);
   add_prop(OBJ_I_VALUE, 0);
}

init()
{
   add_action("do_open","open");
   add_action("do_open","unseal");
   add_action("do_open","break");
   ::init();
}

int
do_open(string str)
{
    if(!str || str == "")
        return 0;
    if(str == "letter" || str == "seal")
    {
        TP->catch_msg("You break the seal on the white letter.\n"
                    +"The white letter suddenly bursts into "
                    +"a pale violet flame and is consumed.\n");
        remove_object();
        return 1;
    }
    return 0;
}
