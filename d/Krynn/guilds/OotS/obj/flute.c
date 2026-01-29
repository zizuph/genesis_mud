/* Flute for the Branchala branch of the OotS - Arman Feb 2018
 * Based on Celeste's Lyre, by Teth, March 29, 1996 
 */

inherit "/std/object";
#include "/d/Krynn/common/defs.h"
#include "../defs.h"
#include <macros.h>

public void
create_object()
{
    set_name("flute");
    add_name("_oots_instrument_flute");
    set_pname("flutes");
    set_short("traditional wooden flute");
    set_pshort("traditional wooden flute");
    set_adj("traditional");
    add_adj("wooden");
    set_long("This is a traditional three-piece wooden flute made from " +
        "boxwood found on the Balifor peninsula. A musical instrument " +
        "often carried by travellers and the common folk of Krynn, this " +
        "particular flute has been lovingly carved with images of the " +
        "celebration of life and music.\n");
   
   add_prop(OBJ_I_VOLUME, 200);
   add_prop(OBJ_I_WEIGHT, 200);
   add_prop(OBJ_I_VALUE, 0);

}

init()
{
   ::init();
   ADA("play");
   ADA("blow");
}

public int
is_valid_instrument(object user, object obj)
{
    if (!objectp(obj) || !obj->id("_oots_instrument_flute"))
    {
        return 0;
    }
    
    return 1;
}

int 
play(string str)
{
    object * instr = filter(all_inventory(TP), &is_valid_instrument(TP,));
    string flute = instr[0]->short();

    if(!str)
    {
        NF("Play what?\n");
        return 0;
    }

    if(parse_command(str, E(TO), "[the] %o", instr ))
    {
       if(!IS_OOTS(TP))
       {
            NF("For some reason you can't make any sound out of " +
                "this traditional wooden flute.\n");
            return 0;
       }

        write("You play a spritely tune on your " +flute+ " full of " +
            "mischief, wonder and fun!\n");
        say(QCTNAME(TP)+ " plays a spritely tune on " +HIS(TP)+ 
            " " +flute+ " full of mischief, wonder and fun!\n");
        return 1;
    }

    NF("Play what?\n");
    return 0;
}

int blow(string str)
{
    object * instr = filter(all_inventory(TP), &is_valid_instrument(TP,));
    string flute = instr[0]->short();

    if(!str)
    {
        NF("Play what?\n");
        return 0;
    }

    if(parse_command(str, E(TO), "[into] [the] %o", instr )) 
    {
       if(!IS_OOTS(TP))
       {
            NF("For some reason you can't make any sound out of " +
                "this traditional wooden flute.\n");
            return 0;
       }

     write("You gently blow into your " +flute+ ", playing a soulful " +
         "song of sadness and loss, ending it with a bright cadence " +
         "of hope and optimism.\n");
     say(QCTNAME(TP)+ " gently blows into " +HIS(TP)+
         " " +flute+ ", playing a soulful song of sadness and loss, but " +
         "ending with a bright cadence of hope and optimism.\n");
      return 1;
    }

    NF("Blow what?\n");
    return 0;
}



