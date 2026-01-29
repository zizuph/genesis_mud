/**********************************************************************
 * - train.c                                                        - *
 * - A training room                                                - *
 * - Created by Damaris@Genesis 3/2004                              - *
 * - New Standrad file for new area for guild. Typos fixed.         - *
 * - by Mirandus@Genesis 01/2018                                    - *
 **********************************************************************/

#pragma strict_types

#include "../guild.h"
#include <ss_types.h>
#include <stdproperties.h>
inherit THANAR_STD_ROOM; 
inherit "/lib/guild_support";
inherit "/d/Kalad/lib/train";


/*
 * Function name: set_up_skills()
 * Description  : Sets up the skills players can learn here.
 */
public void
set_up_skills()
{
  create_skill_raise();
  sk_add_train(SS_HERBALISM, "identify herbs", 0, 0, 40);
  sk_add_train(SS_ELEMENT_LIFE,  "cast life spells", 0, 0, 20);
  sk_add_train(SS_ELEMENT_AIR,  "cast air spells", 0, 0, 20);
  sk_add_train(SS_FORM_DIVINATION, "use the magic form divination", 0, 0, 20);
  sk_add_train(SS_FORM_CONJURATION, "use the magic form conjuration", 0, 0, 20);
  sk_add_train(SS_LOC_SENSE, "be aware of surroundings", 0, 0, 50);
  sk_add_train(SS_DEFENCE, "defend yourself", 0, 0, 30);
  sk_add_train(SS_WEP_SWORD, "use a sword in the service of Thanar", 0, 0, 50);
  sk_add_train(SS_AWARENESS, "notice your environment", 0, 0, 50);
  sk_add_train(SS_SPELLCRAFT, "use magical spells", 0, 0, 30);
  sk_add_train(SS_LANGUAGE, "understand and speak different languages", 0, 0, 30);
  sk_add_train(SS_APPR_MON, "appraise possible enemies", 0, 0, 40);

}

object meditate;

/*
 * Function name: create_std_thanar()
 * Description  : Creates the room from standard room file
 */
public void
create_std_thanar()
{
    set_short("Training room");
    set_long("This square-shaped room is dominated by the "+
      "massive ruby-red carpet that completely covers the floor. Hanging "+
      "from the walls are intricate tapestries depicting various "+
      "highlights in the history of Thanar's awareness. Golden "+
      "braziers lie at each of the four corners of the room, "+
      "incense burning from within them to fill this room with "+
      "its pungent yet intoxicating aroma.\n");
   add_item(({"massive ruby-red carpet",
   "massive carpet","ruby-red carpet","carpet"}),
      "A luxurious carpet that looks quite comfortable, perfect "+
      "for meditation.\n");
   
   add_item(({"intricate tapestries","intricate tapestry","tapestries",
   "tapestry"}),
      "Depicted are the following scenes...\n"+
      "A man in glistening black armour leading a host of human warriors "+
      "into a gnomish city freeing them from oppression.\n"+
      "A darkly robed wizard, face concealed, setting fire to a huge "+
      "section of forest saving the Elves from their false worship.\n "+
      "An obsidian-cloaked priest, arms raised to the darkened sky, "+
      "calling an apparition of Thanar, showing the Hobbits to what they "+
      "should aspire.\n"+
      "A towering figure of darkness, standing triumphant over the blasted "+
      "ruins of a dwarven city, preaching the compassion of Thanar.\n");
   add_item(({"golden braziers","braziers","golden brazier","brazier"}),
      "Set upon golden tripods, there is one at each corner of the room, "+
      "spreading a bare minimum of light and an over-abundance of incense.\n");
   add_item(({"corner"}),
      "Each of the four contains a brazier.\n");
   add_item(({"training hall", "hall", "room"}), query_long);
    
   add_item(({"sign"}),
      "Members may <meditate> here. For assistance in training "+
      "<help train>.\n");
   add_cmd_item("sign","read","Members may <meditate> here. For "+
      "assistance in training <help train>.\n");

    add_exit("start", "southeast");
    set_no_exit_msg(get_all_no_exits(({"se"})),
    "There is a wall blocking your path.\n");
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_NO_ATTACK, 1);
    add_prop(ROOM_I_NO_MAGIC_ATTACK, 1);  
    set_up_skills();
}

/*
 * Function name: init()
 * Description  : Initializes the commands for the room.
 */
public void
init()
{
    ::init();
    init_skill_raise();
    init_guild_support();
    add_action("help","help");
}

