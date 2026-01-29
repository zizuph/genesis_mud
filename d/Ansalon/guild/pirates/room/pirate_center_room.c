/*
 * File Name        : pirate_center_room.c
 * By               : Elmore.
 * Inspiration from : -
 * Date             : Nov. 2000.
 * Description      : Just another guild room :)
 *
 */

#include "/d/Ansalon/goodlund/nethosak/city/local.h"
#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <stdproperties.h>

inherit MITHAS_IN;

int assume(string str);
 
void
create_mithas_room()
{
   set_short("Huge underground cave");
   set_long("@@long_descr");

   clone_object(GUILD_OBJ + "normal_board")->move(this_object());

   add_item(({"sign","small sign"}),
       "The sign reads:  To take over for an inactive Pirate King, "+
       "use <assume command>.\n");

   add_cmd_item(({"sign","small sign"}),
       "read",
       "The sign reads:  To take over for an inactive Pirate King, "+
       "use <assume command>.\n");

   add_exit("underground_cave","south",0,0);
   add_exit("pirate_drop_room","west",0,0);
   add_exit("pirate_train","north",0,0);
   add_exit("pirate_shop","east",0,0);
   add_exit("pirate_start","northeast",0,0);
   add_exit("p_office","southwest",0,0);
   add_exit("pirate_king_room","northwest","@@king_exit",0); 
}

string
long_descr()
{ 
   return "You are standing in a huge underground cave, beneath the isle of Mithas. The "+
          "cave must have been made by some sort of violent erosion of the stones that "+
          "form the bedrock of the isle. The black rock walls are drenched with water and "+
          "the smell of the fresh seawater and wet soil dominate this place. This might be "+
          "a good place to hide yourself or something. Seven exits lead to the east "+
          "towards a small shop, west towards some sort of big hall and south to the "+
          "entrance of the caves, north is a training hall, northeast a resting room and "+
          "a sort of grotto is a little way to the northwest. A small post office has been "+
          "made in the cave to the southwest.  A small sign is here.\n";

}

int
king_exit()
{
   if(PADMIN->query_pirate_king(TP) ||
      TP->query_prop(I_AM_ALLOWED))
   {
       return 0;
   }
   else
   {
       write("Only the King is allowed to enter this room.\n");
       return 1;
   }
   return 0;
}

int
assume(string str)
{
    object who = TP;
    int i;
    string king;

    if (!strlen(str) || !(str == "command")) {
        NF("Assume command?\n");
        return 0;
    }

    seteuid(getuid(TO));

    king = PADMIN->query_king();
    // No need for the king to assume command when he already has it.
    if(king && who->query_real_name() == king)
    {
        NF("You are already the king.\n");
        return 0;
    }

    // This allows 'who' to become king if the king has been too idle
    // or if we have no king.
    i = PADMIN->check_replace_king(who->query_real_name());

    // Has the king been too idle
    if (!i)
    {
        NF("You are unable to assume command. The current Pirate King "+
            "must have not logged in for at least two weeks (potentially "+
            "up to three weeks depending on realm resets!) " +
            "for someone else to take charge.\n");
        return 0;
    }

    write("You assume command as the Legendary Pirate King!\n");

    return 1;
}

void
init()
{
    ::init();
    add_action(assume, "assume");
}
