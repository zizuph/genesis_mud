/* Dig code borrowed from Emerald  */

// Navarre July 2008: Fixing hole being removed on room reset.

// Arman Mar 2017: Added beach herbs

#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/goodlund/nethosak/city/local.h"
#include "/d/Ansalon/goodlund/bloodsea/local.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <money.h>   
 
inherit MITHAS_OUT;

#include "/d/Krynn/common/herbsearch.h"
#define ONE_OF(x)     ((x)[random(sizeof(x))])
#define HERB_MASTER "/d/Krynn/common/herbs/herb_master"
 
#define HARD_TO_SWIM 20
#define FIXED_MAP1  "_ansalon_bloodsea_map1"
#define FIXED_MAP2  "_ansalon_bloodsea_map2"
#define FIXED_MAP3  "_ansalon_bloodsea_map3"
#define DIAMOND "/d/Genesis/gems/obj/diamond"
#define PEARL "/d/Genesis/gems/obj/pearl_black"

string *herbs = HERB_MASTER->query_herbs( ({ "beach","intertide", }) );

public int         do_dig(string str);  
object chest, gem1, gem2, gem3, gem4, gem5, money1, money2;
object hole;

void 
reset_mithas_room()
{
    // Dont want to remove the hole if player is doing the quest.
    object* players = filter(all_inventory(TO), interactive);
    if(!sizeof(players))
    {
        hole->remove_object();
    }

    set_searched(0);
}

void
create_mithas_room()
{
   set_short("stretch of sandy beach on the isle of Karthay");
   set_long("@@long_descr"); 
   add_name( ({ "_special_digging_room" }) );

   add_item(({"sandy beach","beach","coastline"}),
         "This is a small stretch of beach on the isle of Karthay. " +
         "Consisting of pure white sand, it stands out starkly to the " +
         "black cliffs that make up most of the coastline of this island.\n");

   add_item(({"sand","pure white sand","white sand"}),
         "Fine and pure is the white sand that makes up this stretch of beach.\n");

   add_item(({"black rocky cliffs","black cliffs","rocky cliffs","cliffs","cliff"}),
         "To the northeast and west the sandy beach ends, and black rocky " +
         "cliffs rise out of the Bloodsea in its place. They rise high out of the " +
         "sea, and look impossible to climb.\n");

   add_item(({"isle","island","isle of karthay","karthay"}),
         "You stand on a beach of the isle of Karthay, the largest and northernmost " +
         "island of the Bloodsea. This island is known for its barren, hot plains and " +
         "high, rain-forested Worldscap mountains.\n");

   add_item(({"worldscap mountains","mountains"}), 
         "From where you stand down beneath the cliffs of the island, you cannot see " +
         "the Worldscap mountains.\n");

   add_item(({"grasses","hardy grasses"}),
         "Thick and hardy grasses grow tall at the edge of the sandy beach.\n");

   add_item(({"trail","small trail"}),
         "A small trail between the hardy grasses climbs up the side of the cliffs to " +
         "the north here.\n");

   add_item(({"bloodsea","sea","water"}),
         "To the south is the Bloodsea of Istar. Great waves rise near to the shore, " +
         "crashing down with a roar as they reach the sandy beach. A skilled swimmer " +
         "could swim out past these breakers to the south.\n");

   add_item(({"waves","wave","great waves"}),
         "Great waves swell majestically from the Bloodsea as they approach the beach. " +
         "Slowly they crest and roll over upon themselves, creating perfect barrels of " +
         "water that roar towards you. A dolphin appears upon one, effortless riding the " +
         "wave towards the shore.\n\nFor a moment you imagine yourself balanced upon its back, " +
         "surfing the wave... the glorious master of these mighty waves. The image sticks... " +
         "Perhaps it is possible and not such a flight of fancy?\n");

   add_item("dolphin","The dolphin has vanished back under the water. You think it would be " +
         "easier to catch a wave with something of your own invention than try and tame one " +
         "of those creatures of the sea!\n");

    add_cmd_item(({"out past breakers","south","sea","bloodsea","water"}),"swim",
      "@@swim_sea");

    add_cmd_item(({"waves","great waves","on waves","wave","on wave","the wave"}),
      ({"surf","catch", "ride"}), "@@catch_wave");

   add_exit(BISLAND + "cliff01","north",0);

    seteuid(getuid(TO));
    set_up_herbs( ({ ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
       ONE_OF(herbs) }), ({"trail","beach","sand","sandy beach",
        "coastline","sea","water"}), 2);

   reset_mithas_room();     
}

string
long_descr()
{ 
   return "You stand on a small stretch of sandy beach on the isle of " +
          "Karthay, a rare stretch of pure white amongst the black " +
          "rocky cliffs that make up the coastline of this island. To " +
          "your north a small trail winds up the the top of the cliff " +
          "between the hardy grasses that grow on the edge of the beach. " +
          "To your south is the Bloodsea, its waves ever racing towards " +
          "the island.\n";
}

string
swim_sea()
{
 
 
    if(this_player()->query_skill(SS_SWIM) < HARD_TO_SWIM)
    {
        write("You look out at the rough surf and know you would drown if you swam out there!\n");
        say(QCTNAME(this_player()) + " thinks about swimming out into the sea, but decides " +
              "it would be a very bad idea.\n");
        return "";
    }
    write("You dive into the surf and swim out into Bloodsea of Istar.\n");
    TP->move_living("dives into the surf and swims out into the Bloodsea of Istar",
      "/d/Ansalon/goodlund/bloodsea/room/6r",1,0);
 
    return "";
}

string
catch_wave()
{
 
 
    if(this_player()->query_skill(SS_SWIM) < HARD_TO_SWIM)
    {
        write("You look out at the rough surf and know you would drown if you swam out there!\n");
        say(QCTNAME(this_player()) + " thinks about swimming out into the sea, but decides " +
              "it would be a very bad idea.\n");
        return "";
    }
    write("To catch a wave you'll need something sleek and dolphin-shaped, yet also light and " +
        "able to float on water.\n");
 
    return "";
}

public void
init()
{
  ::init();
 
  add_action(do_dig, "dig");
} 
 
void
remove_chest()
{
   if(!objectp(chest))
     return;

   tell_room(this_object(), "The old pirate chest decays into dust.\n");
   chest->remove_object();
}

public int
do_dig(string str)
{
  object room = TO;

  int xp_base = 14000;

    if(!P("shovel",TP))
    {
        notify_fail("Dig? With only your hands?\n");
        return 0;
    }
 
    if (!strlen(str))
    {
        notify_fail("Where do you want to dig with what?\n");
        return 0;
    }
 
    if (!parse_command(str, ({}),
        "[a] [hole] [in] [the] 'hole' / 'here' / 'sand' [in] [the]"
      + " [sand] [with] [the] [shovel]"))
    {
        notify_fail("Where do you want to dig with what?\n");
        return 0;
    }
 
    if (this_player()->query_fatigue() < 40)
    {
        write("You are too tired to dig right now.\n");
        return 1;
    }
 
    this_player()->add_fatigue(-40);

    if (hole = present("_hole_", room))
    {
        write("Taking the shovel, you dig deeper, increasing the"
            + " size of the hole.\n");
        say(QCTNAME(this_player()) + " spends some time digging"
            + " in the ground, increasing the size of the hole.\n");
 
        hole->increase_size();

        if((hole->query_size() >= 2) && P("_ansalon_full_map",TP))
        {

           if(TP->test_bit("ansalon", 0, 18))
           {
              write("Ah, thats right... you have already dug up the treasure " +
                 "previously! It must have slipped your mind!\n\nThe fragile treasure " +
                 "map suddenly turns to dust!\n");
              P("_ansalon_full_map",TP)->remove_object();
              return 1;
           }

            write("After considerable digging, your shovel hits something solid. " +
                "With a bit of huffing and puffing, you uncover an old pirate " +
                "chest, and pull it out of the hole!\n\nYou feel more experienced!\n\n");
            say(QCTNAME(this_player()) + " hits something solid with " +HIS(TP)+
                " shovel. With a bit of huffing and puffing, " +HE(TP)+ " pulls " +
                "from the hole an old pirate chest!\n"); 

            chest = clone_object(BOBJ + "chest");
            chest->set_short("old pirate chest");
            chest->set_long("This old pirate chest looks like it has been buried " +
                "under the sand for a long time!\n");
            chest->add_prop(CONT_I_LOCK, 0);
            chest->move(TO);
            MONEY_MAKE_GC(200)->move(chest, 1);
            clone_object(DIAMOND)->move(chest, 1);
            clone_object(DIAMOND)->move(chest, 1);
            clone_object(DIAMOND)->move(chest, 1);
            clone_object(DIAMOND)->move(chest, 1);
            clone_object(PEARL)->move(chest, 1);

            set_alarm(1800.0, 0.0, "remove_chest");

            xp_base -= (TP->query_prop(FIXED_MAP1) ? 0 : 3000);
            xp_base -= (TP->query_prop(FIXED_MAP2) ? 0 : 3000);
            xp_base -= (TP->query_prop(FIXED_MAP3) ? 0 : 3000);


            if (TP->query_wiz_level())
            {
               TP->catch_msg("xp : " + xp_base + "\n");
            }
 
            TP->add_exp(xp_base, 0);
            TP->set_bit(0, 18);
            P("_ansalon_full_map",TP)->remove_object();
            write("The fragile treasure map suddenly turns to dust!\n");
 
            A_QUEST_LOG("quest","Bloodsea Treasure Quest", TP, xp_base);
            return 1;          
         }  
 
    }
    else
    { 
        seteuid(getuid(TO));
  
        write("Taking the shovel, you begin digging a hole in the ground."
            + " After a short while, you grow weary, and stop to rest.\n");
        say(QCTNAME(this_player()) + " takes a shovel, and begins to dig"
            + " a hole in the ground. After a bit of time, "
            + this_player()->query_pronoun() + " stops and wipes "
            + this_player()->query_possessive() + " brow.\n");
 
        hole = clone_object("/d/Emerald/obj/hole");
        hole->move(room);
    }

    return 1;
}
