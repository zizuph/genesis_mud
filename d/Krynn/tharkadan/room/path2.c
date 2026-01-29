#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>
#include <composite.h>
#include "/d/Krynn/common/clock/clock.h"

inherit THARK_OUT;
inherit HERBSEARCHNEW

object fizban, drac1, drac2, drac3, drac4;
string *herbs = HERB_MASTER->query_herbs(({"mountains","hills",}));

#define DIALOG_PROP     "_fizban_currently_dialoguing"
#define WOHS_MANAGER    ("/d/Krynn/guilds/sohm/lib/sohm_manager")
#define DEBUG(x)   find_player("arman")->catch_msg("[Fizban] " + x + "\n")

void
reset_tharkadan_room()
{
    if(!objectp(fizban))
    {
        setuid();
        seteuid(getuid());
        fizban = clone_object(LIVING + "fizban");
        fizban->arm_me();
        fizban->move(this_object());        
    }

    set_searched(random(2));
}

create_tharkadan_room()
{
    set_short("@@short_descr");
    set_long("@@long_descr");

    add_item(({"lonely oak tree","oak tree","tree","oak","canopy"}),
        "To one side of the road grows a solitary oak tree. It is " +
        "not particularly tall and its canopy is sparse... far from " +
        "the most impressive oak tree you have seen. One limb has grown " +
        "above the path, casting a long shadow across it.\n");

    add_item(({"limb","tree limb"}), "One limb of the oak tree grows " +
        "out from its side, hanging over the path and casting a long " +
        "shadow across it.\n");

    add_item(({"long shadow"}),"A long shadow is cast across the " +
        "path by the limb of a nearby oak tree. Interestingly, you " +
        "wouldn't be able to continue to the southeast without " +
        "crossing the shadow.\n");

    add_cmd_item(({"lonely oak tree","oak tree","tree","oak"}),
        "climb","The limbs of the oak tree don't look sturdy " +
        "enough to climb.\n"); 

    add_item(({"snow","snow-covered","snow-covered ground",
	"white","snow-covered land","winters snow","winter's snow"}),
        "@@add_item_snow");
    add_item(({"path","road","rugged pass","rugged path","trail"}),
        "@@add_item_path");

    add_exit(ROOM + "path3", "southeast", "@@check_passage");
    add_exit(ROOM + "path1", "northwest", 0);

    seteuid(getuid(TO));
    set_up_herbs( ({ ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
        ONE_OF(herbs), ONE_OF(herbs) }), ({ "pass","ground" }), 6);

    reset_tharkadan_room();
}

// Room descriptors

string
short_descr()
{
    return short_mountain_desc() + ".\nA lonely oak tree";
}

string
long_descr()
{
    return long_mountain_desc()+"Growing to the side of the road is a " +
    "lonely oak tree, its limbs casting a long shadow across the path.\n";
}

void
fizban_whispers_hint(object player)
{
    if(E(player) == TO)
    {
       fizban->command("whisper to " +player->query_real_name()+ " You " +
          "need more narrative... or storyline progression... before " +
          "you can pass.");

       if(!player->test_bit("krynn", 2, 2))
       {
         fizban->command("whisper to " +player->query_real_name()+ 
             " The disks of Mishakal need to be recovered - for good or " +
             "evil.");
         if(player->query_alignment() > 0)
             fizban->command("whisper to " +player->query_real_name()+ 
                 " You should seek out Lord Gunthar in Vingaard Keep " +
                 "and assist him in the recovery.");
         else
            fizban->command("whisper to " +player->query_real_name()+ 
                " Being of dark heart, perhaps Dragon Highlord " +
                "Verminaard in Pax Tharkas is the path you should take.");
       }
       if(!player->test_bit("krynn", 2, 3))
       {
         fizban->command("whisper to " +player->query_real_name()+ " In " +
             "the fortress of Pax Tharkas to our northwest is a family " +
             "needing rescuing.");
         fizban->command("whisper to " +player->query_real_name()+ 
             " Help them out, and you will have the 'narrative' you " +
             "need to continue down this trail.");
       }

     fizban->command("wink conspir");
     }

     fizban->command("say Now where was I? Ah yes... fireball...");
     fizban->command("read spellbook");
     fizban->remove_prop(DIALOG_PROP);

     return;
}


void
fizban_blocks_tharkadan_entry(object player)
{

    player->catch_tell(C(COMPOSITE_LIVE(fizban)) + " blocks you from " +
        "going southeast with his staff.\n");
    tell_room(environment(player), C(COMPOSITE_LIVE(fizban)) + " blocks " +
	    QTNAME(player)+ " from going southeast with his staff.\n",
	    ({ player }), fizban);
    fizban->add_prop(DIALOG_PROP, 1);
    set_alarm(1.5,0.0, &fizban->command("say No! No! You cannot pass!"));
    set_alarm(1.5,0.0, &fizban->command("emote points to the shadow of " +
        "the tree limb that stretches across the path."));
    set_alarm(4.0,0.0, &fizban->command("say Don't you see?"));
    set_alarm(4.0,0.0, &fizban->command("eyebrow wildly"));
    set_alarm(8.0,0.0, &fizban->command("say The tree! " +
        "You were about to stumble in to its cunning trap!"));
    set_alarm(8.0,0.0, &fizban->command("emote beats the lonely oak " +
        "tree vigorously with his staff."));
    set_alarm(11.0,0.0, &fizban->command("emote yells at the lonely oak " +
        "tree: I know " +HE(player)+ " needs more narrative before " +
        HE(player)+" can pass you, you gnarled fool!"));
    set_alarm(15.0,0.0, &fizban_whispers_hint(player));

    return;

}

int
check_passage()
{
   //  Need to have completed the Disks of Mishakal quest and
   //  Rescue Prisoner quest before continuing down this path.

   if (!TP->test_bit("krynn", 2, 2) || !TP->test_bit("krynn", 2, 3))
   {
      if(!objectp(fizban))
      {
         write("As you begin to head southeast you notice a long dark "+
            "shadow lying across your path - like a dark serpent in " +
            "wait for its prey. For some reason you develop an " +
            "irrational fear of crossing that shadow!\n");
         return 1;
      }

      if(fizban->query_prop(DIALOG_PROP))
      {
         write(C(COMPOSITE_LIVE(fizban)) + " is currently in a vigorous " +
            "conversation and is currently blocking the way to the " +
            "southeast. You'll have to wait until he has finished " +
            "before you can pass by him.\n");
         return 1;
      }

      fizban_blocks_tharkadan_entry(TP);
      return 1;
   }

   return 0;
}


// Functions relating to learning the WoHS fireball spell

void
wohs_learn_fireball(object player)
{

  if((!WOHS_MANAGER->query_scribed_spell(player,"ixengarmth")) && 
     (E(player) == TO))
  {
     player->catch_msg("\nYou observe closely the casting of the " +
        "advanced fireball spell, copying your observations of the " +
        "spell into your spellbook.\n\n");

     WOHS_MANAGER->scribe_spell_to_spellbook(player, "ixengarmth");

     player->catch_msg("\nYou scribe the spell ixengarmth into your " +
         "spellbook!\n\n");
  }

  set_alarm(1.5,0.0, &fizban->command("cackle"));
  set_alarm(1.5,0.0, &fizban->command("say That got 'em. Wonderful " +
       "spell, fireball!"));
  set_alarm(3.0,0.0, &fizban->command("say Now where was I? Oh yes..." +
        " Vagrant poor excuse for a shrub! Move your shadow!"));
  set_alarm(3.0,0.0, &fizban->command("emote starts vigorously " +
        "whacking the lonely oak tree with his staff."));
  set_alarm(3.0,0.0, &fizban->remove_prop(DIALOG_PROP));
  return;
}

void
summon_dragonarmy_patrol3(object player)
{
   fizban->command("say That's right! FIREBALL!");
   fizban->command("read spellbook");
   fizban->command("cast ixengarmth");

   set_alarm(16.0, 0.0, &wohs_learn_fireball(player));
   return;
}

void
summon_dragonarmy_patrol2(object player)
{
    setuid();
    seteuid(getuid());

    if(!objectp(drac1))
    {

        drac1 = clone_object("/d/Krynn/std/baaz");
        drac1->set_color("red");
        drac1->set_stats(({40,40,40,40,40,280}));
        drac1->add_prop(OBJ_I_RES_FIRE, -100);
        drac1->move(this_object());
        drac1->set_act_time(200);
        drac1->command("emote arrives leading a draconian patrol from " +
            "the northwest.\n");
        drac1->command("point befuddled human");
        set_alarm(1.5,0.0, &drac1->command("say THERE IS THE INTRUDER! " +
            "GET HIM!"));
        set_alarm(3.0,0.0, &drac1->command("kill befuddled human"));        
    }
    if(!objectp(drac2))
    {
        drac2 = clone_object("/d/Krynn/std/baaz");
        drac2->set_color("red");
        drac2->set_stats(({40,40,40,40,40,280}));
        drac2->add_prop(OBJ_I_RES_FIRE, -100);
        drac2->move(this_object());  
        drac2->set_act_time(200);
        set_alarm(3.0,0.0, &drac2->command("kill befuddled human"));     
    }

    if(!objectp(drac3))
    {
        drac3 = clone_object("/d/Krynn/std/baaz");
        drac3->set_color("red");
        drac3->set_stats(({40,40,40,40,40,280}));
        drac3->add_prop(OBJ_I_RES_FIRE, -100);
        drac3->move(this_object());
        drac3->set_act_time(200); 
        set_alarm(3.0,0.0, &drac3->command("kill befuddled human"));     
    }

    if(!objectp(drac4))
    {
        drac4 = clone_object("/d/Krynn/std/baaz");
        drac4->set_color("red");
        drac4->set_stats(({40,40,40,40,40,280}));
        drac4->add_prop(OBJ_I_RES_FIRE, -100);
        drac4->move(this_object());
        drac4->set_act_time(200);   
        set_alarm(3.0,0.0, &drac4->command("kill befuddled human"));    
    }

   set_alarm(7.0, 0.0, &summon_dragonarmy_patrol3(player));

   return;
}

public void
summon_dragonarmy_patrol(object player)
{
   set_alarm(3.0, 0.0, &summon_dragonarmy_patrol2(player));
   return;
}

