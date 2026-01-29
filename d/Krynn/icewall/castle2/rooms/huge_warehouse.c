#pragma strict_types
#include "/d/Krynn/icewall/castle2/local.h"
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
inherit ICEINROOM;

int    rack_unsteady = 1;
int    rack_leaning_east = 0;
int    rack_leaning_west = 0;
int    rack_destroyed = 0;
int    rack_fixed = 0;
int    xp_base = 750;

object minotaur1, minotaur2, minotaur3, minotaur4, minotaur5, minotaur6;

public void
reset_icewall_room()
{

    rack_unsteady = 1;
    rack_leaning_east = 0;
    rack_leaning_west = 0;
    rack_destroyed = 0;
    rack_fixed = 0;


    if (!minotaur1)
    {
	minotaur1 = clone_object(NPCK + "ware_mino.c");
	minotaur1->move_living("xx", TO);
    }
    if (!minotaur2)
    {
	minotaur2 = clone_object(NPCK + "ware_mino.c");
	minotaur2->move_living("xx", TO);
    }
    if (!minotaur3)
    {
	minotaur3 = clone_object(NPCK + "ware_mino.c");
	minotaur3->move_living("xx", TO);
    }
    if (!minotaur4)
    {
	minotaur4 = clone_object(NPCK + "ware_mino.c");
	minotaur4->move_living("xx", TO);
    }
    if (!minotaur5)
    {
	minotaur5 = clone_object(NPCK + "ware_mino.c");
	minotaur5->move_living("xx", TO);
    }
    if (!minotaur6)
    {
	minotaur6 = clone_object(NPCK + "ware_mino.c");
	minotaur6->move_living("xx", TO);
    }


}

void
create_icewall_room()
{
    set_short("Huge supply warehouse");
    set_long("@@long_descr");


    add_exit("dark_tunnel","west");
    add_exit("storage1","up","@@up");

    add_item(({"wall","walls"}),"This was once a normal castle " +
     "cellar, used to store meats, wines, and vegetables for the " +
     "winter. Someone has put in many a hour to widen the room " +
     "into a huge warehouse, and stacked it well with basic " +
     "army supplies, that is food, weapons, and cheap wine.\n");
    add_item(({"crate","crates"}),"Solid planking hides " +
     "leathery strips of meat, hides, furs, and a whole " +
     "lot of crude, iron maces and axes. Someone obviously " +  
     "is preparing for war, but this doesnt look like the " +
     "supplies of any elite, or at least regular troops.\n");  
    add_item(({"barrel","barrels"}),"Balanced sideways one " +
     "upon another, and supported by wooden racks, the " +
     "barrels contain a sea of cheap wine. You can see more " +
     "then a hundred of them, each as large as a good sized cow. " +
     "You guess noone would notice if you took a swig from the " +
     "barrel.\n");
    add_item(({"rack","racks","wooden rack","wooden racks"}),"@@racks_desc");
    add_item(({"huge rack","northeast rack","northeast corner"}), "@@n_rack");
    add_item(({"collapsed rack","thick pool","pool"}),"@@pool_desc");
    add_item(({"corner","corners"}), "Only the northeast corner " +
     "holds anything of interest, namely the huge wine rack\n");
    add_item(({"stairs","stairway"}),"The stairway consists of " +
     "old, solid stone blocks cemented in a spiral fashion. " +
     "Despite their age, the stairs appear in better shape then " +
     "the wine racks.\n");
    add_item(({"ceiling","shadows"}),"The architect of this " +
     "warehouse never thought about smoothing the ceiling. " +
     "Rough and cracked, it sports an amazing collection of " +
     "niches and shadowy places.\n");
    add_item(({"niches","shadowy places"}),"There are many of " +
     "those, but the worst they could breed are bats - " +
     "and in this climate, that is virtually impossible.\n");

    set_tell_time(400);

    add_tell("Horrible smell of rotting barrels and cheap wine " +
     "gone bad assaults your nosdrils. You feel distaste.\n");
    add_tell("You are quite sure you have just heard the sound " +
     "of heavy, iron soles pounding the ground above you.\n");
    add_tell("Something moved above you, in the shadows...\n");
    
    reset_icewall_room();
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
        start_room_tells();
}

int
up()
{
   write("As you head up the stone stairway, a cold draft " +
    "buffets you.\n");
}

string
racks_desc()
{
     if(rack_destroyed)
        {
        return "The " +
        "racks are made of ancient ironwood, and in several places " +
        "patched with a haphazardous collections of wooden planks. " +
        "Despite the poor attempt at repair, they appear to be in a " +
        "very bad shape. The northeast corner of the room contains " +
        "a wooden heap - the remains from a collapsed rack. Around " +
        "it a thick pool of " +
        "cheap wine is slowly draining into the cold earth.\n";
        }
     return "The " +
        "racks are made of ancient ironwood, and in several places " +
        "patched with a haphazardous collections of wooden planks. " +
        "Despite the poor attempt at repair, they appear to be in a " +
        "very bad shape. The northeast corner of the room contains " +
        "a huge rack that holds especially large number of wine " +
        "barrels.\n";
}

string
pool_desc()
{
    if(rack_destroyed)
        {
        return "One of the racks, a huge one judging by the amount " +
        "of debris left, has collapsed, smashing all the barrels " +
        "stored within it. The catastrophe must have occured only " +
        "recently, for a thick pool of stinking wine mixed with " +
        "dirt still stands hand-deep in the northeast corner of the " +
        "room, slowly draining into the frozen earth.\n";
        }
    return "There is no such thing here.\n";
}

string
n_rack()
{
      if(rack_unsteady)
        {
        return "The huge wine rack standing in the northeast corner " +
        "appears to be in especially bad " +
        "condition. It sways dangerously and looks ready to " +
        "topple towards either side just about anytime now, " +
        "especially if it was given a slight push. However, " +
        "the east side of the rack stands very close to a wall, and " +
        "if the wooden construction swayed that way, the wall " +
        "might prop it for some " +
        "time to come. Such a trick would keep the wine safe, at " +
        "least until the " +
        "Thanoi returned for a drunken feast after their usual " +
        "bloody raid against the hard-pressed ice-folk. Was the " +
        "rack to sway to the west, it would most certainly crash to " +
        "the ground, smashing quite a few barrels of cheap wine.\n";
        }

    if(rack_leaning_east)
        {
        return "The huge wine rack standing in the northeast corner " +
        "appears to be in especially bad " +
        "condition. The wooden construction creaks under the weight " +
        "of the wine barrels, and is clearly leaning east, towards " +
        "the nearby wall of the warehouse. However, one could still " +
        "sway it to either side with a push.\n";
        }

    if(rack_leaning_west)
        {
        return "The huge wine rack standing in the northeast corner " +
        "appears to be in especially bad " +
        "condition. The wooden construction creaks under the weight " +
        "of the wine barrels, and is clearly leaning west, away " +
        "from the nearby wall of the warehouse. However, one could still " +
        "sway it to either side with a push.\n";
        }

    if(rack_fixed)
        {
        return "The huge wine rack standing in the northeast corner " +
        "appears to be in especially bad " +
        "condition. The wooden construction has leaned far to the " +
        "east, coming to rest heavily against the nearby wall of the " +
        "warehouse. Although the rack creaks under its burden, it " +
        "looks firmly wedged into the wall, and holds steadily.\n";
        }

    if(rack_destroyed)
        {
        return "The northeast corner of the room contains " +
        "a wooden heap - the remains from a collapsed rack. Around " +
        "it a thick pool of " +
        "cheap wine is slowly draining into the cold earth.\n";
        }
}


string
long_descr()

{ return ("" +
  "You stand in a huge warehouse carved out of solid rock. Frost lines " +
  "the walls, but several crates stashed around appear as if " +
  "they were brought in here just recently. Likewise, judging by the " +
  "reddish pools and smell of cheap wine you assume that the " +
  "large barrels stacked on the wooden racks were not " +
  "brought here for decoration, but see a lot of use. The whole " +
  "place reeks of dirty furs and unwashed bodies. To the west, " +
  "a tunnel has been carved in rock, and on the east end of the " +
  "warehouse, old stone stairway leads up.\n");


}

int
push(string str)
{
    if(rack_destroyed)
      {
        notify_fail("You do not see anything easily pushable around" +
          "here.\n");
        return 0;
      }

    if(rack_fixed)
      {
         if(str == "huge rack east")
            {
              notify_fail("You cannot push the rack further into the wall! " +
                "It is already leaning heavily on the cold rock.\n");
              return 0;
            }
         if(str == "huge rack west")
            {
              notify_fail("It would take a giant to lift the rack to the " +
                "west, away from the wall. The wooden construction is " +
                "safely wedged against cold rock.\n");
              return 0;
            }
         notify_fail("What do you wish to push? The huge rack? If so, " +
           "which way?\n");
         return 0;
       }

    if(rack_unsteady)
      {
         if(str == "huge rack east")
            {
              write("Putting your back to it, you press hard on the " +
                "left side of the huge rack, and creaking omniously, it " +
                "leans a bit to the east!\n");
              say(QCTNAME(TP) + " pushes hard against the left side of " +
                "the huge rack, and with a dangerous creak, the wooden " +
                "construction leans a bit to the east!\n"); 
              rack_unsteady = 0;
              rack_leaning_east = 1;
              return 1;
            }
         if(str == "huge rack west")
            {
              write("Putting your back to it, you press hard on the " +
                "right side of the huge rack, and creaking omniously, it " +
                "leans a bit to the west!\n");
              say(QCTNAME(TP) + " pushes hard against the right side of " +
                "the huge rack, and with a dangerous creak, the wooden " +
                "construction leans a bit to the west!\n"); 
              rack_unsteady = 0;
              rack_leaning_west = 1;
              return 1;
            }
         notify_fail("What do you wish to push? The huge rack? If so, " +
           "which way?\n");
         return 0;
       }

     if(rack_leaning_east)
      {
         if(str == "huge rack east")
            {
              write("Putting your back to it, you press hard on the " +
                "left side of the huge rack, and creaking omniously, it " +
                "collapses to the east! Before it manages to gain " +
                "much momentum though, it connects with the stone wall, and " +
                "wedges hard against it! The rack appears much more stable " +
                "now, and should stand at least until the wood rots " +
                "completely through... You feel that by saving the wine " +
                "you have done an evil deed, helping the White Dragonarmy " +
                "keep its thanoi warriors loyal, drunk, and mercilessly " +
                "raiding the ice folk who still refuse to surrender before " +
                "the Dark Queen's might!\n");
              say(QCTNAME(TP) + " pushes hard against the left side of " +
                "the huge rack, and with a dangerous creak, the wooden " +
                "construction collapses to the east! Before it gains " +
                "much momentum though, it connects with the stone wall, and " +
                "wedges hard against it! The rack appears much more stable " +
                "now, and should stand at least until the wood rots " +
                "completely through...\n" + QCTNAME(TP) + " appears mighty " +
                "pleased about this deed.\n"); 
              rack_leaning_east = 0;
              rack_fixed = 1;

              if(TP->test_bit("krynn", 3, 10))
                  {
                    TP->catch_msg("You feel strange... as if you repeated " +
                     "your own footsteps.\n");
                     return 1;
                  }

              TP->catch_msg("You feel more experienced.\n");
              tell_room(E(TP), QCTNAME(TP) + " looks more experienced.\n", TP);

              TP->add_exp(xp_base, 0);
              TP->set_bit(3, 10);
              TP->set_alignment(TP->query_alignment() - 300);
              TP->change_prestige(-1);

              K_QUEST_LOG("quest", "Thanoi Wine (evil)", TP, xp_base);       

              return 1;
            }
         if(str == "huge rack west")
            {
              write("Putting your back to it, you press hard on the " +
                "right side of the huge rack, and creaking omniously, it " +
                "leans to the west, away from the wall, returning to a very unstable " +
                "vertical position. As you move away, the wooden construction " +
                "appears ready to sway on its own towards either side " +
                "any second now...\n");
              say(QCTNAME(TP) + " pushes hard against the right side of " +
                "the huge rack, and with a dangerous creak, the wooden " +
                "construction leans to the west, away from the wall, " +
                "returning to a very unstable vertical position.\n"); 
              rack_leaning_east = 0;
              rack_unsteady = 1;
              return 1;
            }
         notify_fail("What do you wish to push? The huge rack? If so, " +
           "which way?\n");
         return 0;
       }

     if(rack_leaning_west)
      {
         if(str == "huge rack west")
            {
              write("Putting your back to it, you press hard on the " +
                "right side of the huge rack, and creaking omniously, it " +
                "collapses to the west! Gaining momentum, the huge rack " +
                "arches towards the floor and...\n\n\nSMASH!!!\n\n\n" +
                "...crashes heavily! Barrels break from the impact, and " +
                "the stench of cheap wine gushing from them hits the air " +
                "with the force of a hurricane! The wine quickly " +
                "gathers in a large pool around the heap of debris left " +
                "from the rack and begins to drain into the frozen earth. " +
                "The loss of so much wine is a severe blow to the " +
                "White Dragonarmy's thanoi morale!\nYou feel you have " +
                "done a good deed, perhaps even granting the " +
                "hard-pressed ice folks a brief respite from the " +
                "ruthless thanoi!\n");
              say(QCTNAME(TP) + " pushes hard against the right side of " +
                "the huge rack, and with a dangerous creak, the wooden " +
                "construction collapses to the west! Gaining momentum, " +
                "the huge rack " +
                "arches towards the floor and...\n\n\nSMASH!!!\n\n\n" +
                "...crashes heavily! Barrels break from the impact, and " +
                "the stench of cheap wine gushing from them hits the air " +
                "with the force of a hurricane! The wine quickly " +
                "gathers in a large pool around the heap of debris left " +
                "from the rack and begins to drain into the frozen earth. " +
                "The loss of so much wine is a severe blow to the " +
                "White Dragonarmy's thanoi morale!\n" + QCTNAME(TP) + " looks " +
                "mighty pleased about the deed!\n"); 
              rack_leaning_west = 0;
              rack_destroyed = 1;

        if (present("_ware_mino", TO))
          {  
            say("A minotaur exclaims: Sargonnas damn it! I told " +
             "them it would collapse!\n" +
             "Apparently noone noticed " + QTNAME(TP) + " helping the " +
             "rack a little.\n");
            write("A minotaur exclaims: Sargonnas damn it! I told " +
             "them it would collapse!\n" +
             "Apparently noone noticed you helping the rack a little.\n");
          }

              if(TP->test_bit("krynn", 3, 10))
                  {
                    TP->catch_msg("You feel strange... as if you repeated " +
                     "your own footsteps.\n");
                     return 1;
                  }

              TP->catch_msg("You feel more experienced.\n");
              tell_room(E(TP), QCTNAME(TP) + " looks more experienced.\n", TP);

              TP->add_exp(xp_base, 0);
              TP->set_bit(3, 10);
              TP->set_alignment(TP->query_alignment() + 300);
              TP->change_prestige(300);

              K_QUEST_LOG("quest", "Thanoi Wine (good)", TP, xp_base);       

              return 1;
            }

         if(str == "huge rack east")
            {
              write("Putting your back to it, you press hard on the " +
                "left side of the huge rack, and creaking omniously, it " +
                "leans to the east, towards the wall, returning to a very unstable " +
                "vertical position. As you move away, the wooden construction " +
                "appears ready to sway on its own towards either side " +
                "any second now...\n");
              say(QCTNAME(TP) + " pushes hard against the left side of " +
                "the huge rack, and with a dangerous creak, the wooden " +
                "construction leans to the east, towards the wall, " +
                "returning to a very unstable vertical position.\n"); 
              rack_leaning_west = 0;
              rack_unsteady = 1;
              return 1;
            }
         notify_fail("What do you wish to push? The huge rack? If so, " +
           "which way?\n");
         return 0;
       }
  return 0;
}


int
swig(string str)
{
    if(str != "wine from barrel")
      {
        notify_fail("Swig what from where?\n");
        return 0;
      }
  
    if (TP->query_race_name() == "goblin" || TP->query_race_name() == "hobgoblin")
      {
        say(QCTNAME(TP) + ", true to his goblin heritage, " +
         "breaks open a lid of a full barrel and with a yellow " +
         "glint in " + HIS(TP) + "eyes, stuffs " + HIS(TP) + " head " +
         "inside , slurping noisily! Breathtaking smell of " +
         "cheap, moldy wine quickly thickens the air here.\n");
        write("Amazed at the opportunity, you pound open a lid " +
         "of a full barrel and quickly stuff your head inside! " +
         "Mouth wide open, you slurp and suck as much of the " +
         "booze as you can possibly stomach. Quickly, you begin " +
         "to feel delightfully dizzy, and the feeling grows on " +
         "you...\n");
   
        TP->set_intoxicated(TP->intoxicated_max());
        
        if (present("minotaur", TO))
          {  
            say("A minotaur snorts: Look, a stoned gobbo... What a " +
             "pitiful wretch.\n");
            write("A minotaur snorts: Look, a stoned gobbo... What a " +
             "pitiful wretch.\n");   
      
            return 1;
          }

        return 1;
      }        
      
    if (TP->query_race_name() == "elf")
      {
        say(QCTNAME(TP) + " takes one look at the wine and sets " +
         HIS(TP) + " elven nose high. You get the impression that " +
         HE(TP) + " would prefer the torture rack to this vintage.\n");
        write("One look is enough. You'd sooner abandon your elven " +
         "heritage then disgrace yourself with this... fluid.\n");


        if (present("minotaur", TO))
          {  
            say("A minotaur snorts: Too strong for ya, elfie?\n" +
             "The minotaur laughs in true amusement.\n");
            write("A minotaur snorts: Too strong for ya, elfie?\n" +
             "The minotaur laughs in true amusement.\n");
      
            return 1;
          }

        return 1;
      }

    if((TP->query_stat(3)) > 100)
      {
        say(QCTNAME(TP) + " is visibly revolted by the sight " +
         "and smell of the wine.\n"); 
        write("Try as you might, you cannot bring yourself " +
         "to drink this horrible excuse for a wine. Your " +
         "stomach revolts from the very sight of the moldy " +
         "color and vinegar-like aroma. This spirit " +
         "might be satisfactory for less inteligent creatures " +
         "but you definitely deserve better.\n");
         return 1;
      }
    
    if((TP->query_stat(2)) < 100)
      {  
        say(QCTNAME(TP) + " pulls a cork from a previously opened " +
         "barrel and takes a swig of the cheap, heavily fermented " +
         "acidic wine. Almost instantly, " + HIS(TP) + " eyes " +
         "widen in shock and " + HE(TP) + " sputters the wine, " +
         "as well as most of " + HIS(TP) + " last meal, not a " +
         "pretty sight.\n");
        write("You pull a cork from a previously opened barrel and " +
         "take a long swig of it. Instantly, blackness clouds " +
         "your vision, and the burning sensation seems to be " +
         "setting your stomach aflame. Sick to the bone, you puke, " +
         "losing the wine, and most of your last meal.\n");

        TP->set_intoxicated((TP->query_intoxicated())/2);
        TP->eat_food(-((TP->query_stuffed())/2));   

        if (present("minotaur", TO))
          {  
            say("A minotaur snorts: Clears your sinuses, and " +
             "other places, doesnt it?\n" +
             "The minotaur laughs in pure amusement.\n");
            write("A minotaur snorts: Clears your sinuses, and " +
             "other places, doesnt it?\n" +
             "The minotaur laughs in pure amusement.\n");
      
            return 1;
          }

        return 1;

      }

    write("Pulling a cork from a previously opened barrel, you " +
     "take a long sip of the cheap wine. The smell and taste of " +
     "acidic vinegar burns through your throat straight into your " +
     "stomach, instantly setting your inards aflame.\n\n" +
     "You cough noisily and tears stream down your cheeks.\n");
    say("Pulling a cork from a previously opened barrel " + 
      QTNAME(TP) + " takes a long sip of the cheap wine. " +
      HIS(TP) + " eyes widen, and face goes red. The horrible " +
      "smell of vinegar thickens in the air.\n\n" +
      QCTNAME(TP) + " coughs noisily, and tears stream down " +
      HIS(TP) + " cheeks.\n");

     TP->set_intoxicated(TP->intoxicated_max());

     if (present("minotaur", TO))
          {  
            say("A minotaur snorts: You think you're tough?\n" +
             "I can drink half a barrel on my own!\n" +
             "The minotaur laughs in pure delight.\n");
            write("A minotaur snorts: You think you're tough?\n" +
             "I can drink half a barrel on my own!\n" +
             "The minotaur laughs in pure delight.\n");
      
            return 1;
          }

    return 1;

}

void
init()
{
    ::init();

    add_action(swig, "swig");
    add_action(push,"push");
}        

              
