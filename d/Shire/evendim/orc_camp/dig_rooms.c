/*
 * Many thanks to Rhyn for helping with this.
 *
 * This file is inherited in every room that is used in the 
 * Free the Prisoner quest, formally known as the Spell Tome 
 * quest. The most important thing about this file is that it 
 * enables us to add or subtract room that can be dug in. 
 *
 * Here's how this works.
 *
 * Everytime the game reboots, this file randomly chooses a 
 * room to hold the treasure. This treasure room is active 
 * until the next reboot. This way it's theoretically harder 
 * for quest run throughs. This also enables us to add or rooms 
 * or remove rooms as necessary.
 *
 * To activate this file in a room, add the exact room path 
 * below in the list of possible treasure rooms and inherit 
 * this file in that room like this:
 *
 *      inherit "/d/Shire/evendim/orc_camp/dig_rooms";
 *
 * Reload the room and you're done. If the file isn't in the 
 * List of possible treasure rooms, this file does nothing.
 *
 * -- Finwe, May 2001
 */

//#pragma strict_types

#include "local.h"
#include "/d/Shire/sys/defs.h"
#include <language.h>
#include </sys/stdproperties.h>
#include </sys/ss_types.h>
#include </sys/macros.h>
inherit TENT_BASE;

#define PRISONER_QUEST  "_freed_orc_prisoner_"
#define STAND_PARENT    "/d/Shire/common/obj/"

// List of possible treasure rooms. 

string *dig_rooms = ({
	"/w/finwe/workroom",
    "/w/finwe/hell",
});

/*
string *dig_rooms = ({
	"/d/Shire/annuminas/amc2",
	"/d/Shire/annuminas/amc5",
	"/d/Shire/annuminas/amc9",
    "/d/Shire/annuminas/am9",
    "/d/Shire/evendim/ev8",
});
*/
/* array counter for treasure room */
int selected_room;

/* quest bits defined */
#define QUEST_GROUP 0
#define QUEST_BIT   1

int solved;

/* creates 'psuedo' tent room */
void
create_tent_room()
{

/* gets corresponding room number. 
 * numbering starts with 0, not 1
 */
   selected_room = random(sizeof(dig_rooms));
//   set_vbfc_extra("@@room_long");
    add_my_desc("@@room_long@@");

   add_item("hole","@@hole_long@@");

}

init() 
{
   ::init();
   add_action("do_dig","dig");
}


room_long() 
{
    string the_long;

//    the_long = "";

    if (solved)
        the_long += " Someone has dug a hole here.\n";

    return the_long;
}


hole_long() {
    if (solved)
        return "The hole is not too deep, and does not look interesting.\n";
    else
        return "What hole?";
}


/* actual treasure room pointer */
string
query_selected_room()
{
   return dig_rooms[selected_room];
}



/* digging code */
do_dig() 
{
   object *arr;
   int i,s, amount;
   object shovel;

   seteuid(getuid());

   notify_fail("You see no reason to dig here.\n");
   if (TP->query_prop("PRISONER_QUEST") != 1)
      return 0;
/*
   // Are there orcs present? 
   if (!sizeof(arr = all_inventory(this_object())) ||
       (s = sizeof(filter(arr, "is_orc", this_object()))) > 0)
   {
      if (s == 1)
      {
         write("The orc stops you from digging here.\n");
         say("The orc stops " + QCTNAME(TP) + " from digging here.\n");
         return 1;
      }
      else
      {
         write("One of the orcs stops you from digging here.\n");
         say("One of the orcs stops " + QCTNAME(TP) + " from digging here.\n");
         return 1;
      }
   }
*/
   // Too late? 
    if (solved)
    {
        notify_fail("It looks like someone has been digging " +
            "here before. You find nothing.\n");
    return 0;
    }

   // Does the player have a shovel?
    if (!(shovel = present("shovel", TP)))
    {
        write("The ground is too hard to dig in with your hands.\n");
        say(QCTNAME(TP) + " tries to dig in the ground with " + 
            HIS_HER(TP) + " hands, but fails\n");
    return 1;
    }

    if (MASTER_OB(shovel) != "/d/Shire/common/obj/shovel2")
    {
        write("You start to dig. Suddenly strong magic prevents " +
            "you from digging further.\n");
    return 1;
    }
    write("You start digging a hole in the ground with your " +
        "shovel and discover a sack!\n"
        + "You quickly get the sack.\n"
        + "Your shovel has lost its aura of enchantment.\n");
    say(QCTNAME(TP) + " starts to dig in the ground with "
        + HIS_HER(TP) + " shovel and discovers a sack!\n"
        + CAP(HE_SHE(TP)) + " quickly gets the sack.\n");

    shovel->remove_object();
    clone_object(STAND_PARENT + "obj/shovel")->move(this_player());
    TP->add_prop("PRISONER_QUEST",1);

   // Only add experience if not solved before 
    if (!(TP->test_bit("Shire", QUEST_GROUP, QUEST_BIT)))
    {
        TP->set_bit(QUEST_GROUP, QUEST_BIT);

        // NEVER add more exp than the player has 
        if (TP->query_exp() < 7000)
            amount = TP->query_exp()*3/4;
        else
            amount = 7000;

        // add quest experience
        TP->add_exp(amount,0);
        log_file("QUESTS", "free prisoner: " + extract(ctime(time()), 4, 15)+ " "
	     + capitalize(TP->query_real_name()) + " got "
	     + amount + "xp.\n");
    }

    solved = 1;
    clone_object(EVENDIM_DIR + "obj/sack")->move(TP);
    return 1;
}