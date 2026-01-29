// Letter that Galerin returns to Jadestone Doll
// -Ilyian, Oct 1995

inherit "/std/object";
#include <macros.h>
#include <stdproperties.h>

int do_open(string str);

create_object()
{
   set_name("letter");
   add_name("_letter_from_galerin");
   set_adj(({"sealed","white"}));
   set_short("white sealed letter");
    add_item("seal","The seal on the letter is made from "
           +"red wax, and inscribed in the seal is a cursive "
           +"letter J.\n");
   add_cmd_item("letter","read","The white letter is sealed closed.\n");
   set_long("This letter is folded in thirds, and is written "
           +"on heavy white paper, with a blood red seal "
           +"holding it closed. On the front several words "
           +"have been crossed out, and written near them, "
           +"in a heavy-handed script:\n"
           +"Deliver only to Jadestone Doll, High Mistress "
           +"of the Black Flower.\n");
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
        this_player()->catch_msg("You break the seal on the white letter.\n"
                    +"The white letter suddenly bursts into "
                    +"a menacing black flame and is consummed.\n");
        remove_object();
        return 1;
    }
    return 0;
}
