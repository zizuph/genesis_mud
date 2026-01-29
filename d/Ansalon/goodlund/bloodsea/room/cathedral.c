#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/goodlund/bloodsea/local.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "/d/Krynn/guilds/OotS/defs.h"

inherit BLOODSEA_OUT;

object hag;
int desecrated_altar = 1;
int medallion_found = 1; /*Needs to be reset to 0 when medallion coded */

void
reset_bloodsea_room()
{
   if(!objectp(hag))
   {
      hag = clone_object(BNPC + "sea_hag");
      hag->arm_me();
      hag->move(TO);
   }

}

create_bloodsea_room()
{
    set_short("@@short_descr");
    set_long("@@long_descr");

    add_item(({"chapel","cathedral","submerged cathedral","sunken cathedral"}),
       "You float in the chapel of a submerged cathedral. Once it would have " +
       "been a testiment to beauty and goodness, filled with worshippers of the " +
       "old gods. Now its former beauty has long left with the turning of the tides, " +
       "and all that fills it now is sand.\n");

    add_item(({"sand","ground","floor"}), "The floor is carpeted with sand that has " +
       "over time shifted with the tides throughout the cathedral.\n");

    add_item(({"pew","pews","beautiful pews","holy artifacts","artifacts","tapestries",
       "exquisite tapestries"}), "You cannot see that here... only in your imagination " +
       "of what this cathedral was like in the past.\n");

    add_item(({"stone altar","altar","simple stone altar"}),
       "This simple stone altar has a single triangle carved onto the side of it, " +
       "inlayed with silver or platinum. Under it in some old form of the common " +
       "tongue has been carved the mantra 'Khara et Bah'Mut'. @@desecrated@@\n");

    add_item("faeces","@@faeces_desc");


    add_swim_exit(BROOM +"uw2", "out", 0, 2);

    add_prop(ROOM_I_TYPE, ROOM_UNDER_WATER);
    add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_S_DARK_LONG,                   
     "Within a dark, sunken cathedral. It is impossible "+
     "to see anything in the gloom without a light source.\n");

    DARK;
    add_cmd_item(({"altar","the altar"}),"clean","@@clean_altar");
    add_cmd_item(({"altar","at altar","stone altar","paladine"}),
         ({"pray","worship"}),"@@pray_altar");


    reset_bloodsea_room();

}

string
desecrated()
{
    if(desecrated_altar)
      return "You notice the altar has been desecrated, with faeces smeared all over it.";
    else
      return "";
}

string
faeces_desc()
{
    if(desecrated_altar)
      return "Faeces has been smeared all over the altar.\n";
    else
      return "You find no faeces.\n";
}

string
clean_altar()
{

    if(objectp(hag))
      return "You can't clean the altar while the sea hag is here!\n";

    if(!desecrated_altar)
      return "The altar does not seem to need cleaning.\n";

    write("You clean the faeces off the altar.\n");
    say(QCTNAME(TP)+ " cleans the faeces off the altar.\n");
    desecrated_altar = 0;

    return "";
}

string
pray_altar()
{
    if(objectp(hag))
      return "You can't pray before the altar while the sea hag is here!\n";

    if(desecrated_altar)
    {
      write("You kneel before the desecrated altar and pay homage to the god of this chapel.\n");
      say(QCTNAME(TP)+ " kneels before the desecrated altar and pays homage to the " +
        "god of this chapel.\n");
      return "";
    }

    if((!medallion_found) && (TP->query_alignment() > 1100))
    {
      write("You kneel before the stone altar and pay homage to the god of this chapel. " +
        "While kneeling, you notice out of the corner of your eye something glimmering " +
        "brightly, half buried in the sand. You dig out a curious silver medallion!\n");
      say(QCTNAME(TP)+ " kneels before the stone altar and pays homage to the god of " +
        "this chapel. You notice that while " +HE(TP)+ " is kneeling he finds something.\n");
      medallion_found = 1;
      return "";
    }

    write("You kneel before the stone altar and pay homage to the god of this chapel.\n");
    say(QCTNAME(TP)+ " kneels before the stone altar and pays homage to the god of this " +
       "chapel.\n");

    if(IS_OOTS(TP))
    {
          if(!OOTS_QUERY_REV(TP, "paladinechurch"))
          {
            TP->catch_msg("\n\nAs you pray before the stone altar, a revelation is " +
                "granted to you on the Church of Paladine...\n\n\n");
            OOTS_ADD_REV(TP,"paladinechurch","edification - the church of paladine");  
          }
    }

    return "";
}
    
 

string
short_descr()
{
    return "chapel to an ancient god in a sunken cathedral";
}
 
string
long_descr()
{
    return "You find yourself floating in a chapel within a submerged cathedral at the bottom " +
      "of the Bloodsea of Istar. The chapel would have once been filled with beautiful pews, " +
      "exquisite tapestries and priceless holy artifacts. However time and the shifting tides of three " +
      "centuries has carpeted the chapel floor with sand, rotted away the pews and tapestries, " +
      "and swept the priceless artifacts away. Little is left of this cathedrals former glory, " +
      "except for a simple stone altar.\n";
}