/* Name: minotaur.
 * Made by: Elmore.
 * Date: April 2000.
 * Equipment: random coins, and some standard minotaur equipment.
 * Description: A citizen that wanders around. He has
 * random description of both the first and second
 * adjectives.
 */

#include <options.h>
#include <money.h>
#include <ss_types.h>
#include "/d/Ansalon/goodlund/nethosak/city/local.h"

inherit "/d/Krynn/common/monster/minotaur_base";
#include "/d/Ansalon/common/defs.h";
string face(); 
string face2();
  
string
face()
{
    // Set first adjective.
    string *faces;
    faces = ({"black-haired", "brown-haired", "dark-haired",
              "light-haired", "long-haired", "thick-haired",
              "grey-haired", "chestnut-haired", "red-haired",
              "blemished", "dirty", "disheveled", "disfigured",
              "foul-looking", "foul-smelling", "friendly", 
              "furry", "wrinkled", "hairy", "leathery", "musky",
              "odd-smelling", "prim", "scarred", "slouchy", 
              "slovenly", "smooth-skinned", "squalid",
              "sweaty", "tidy-looking", "unkempt", "well-groomed",
              "wheezy", "bent-nosed", "big-lipped", "jug-eared",
              "bony-cheeked", "bony-faced", "buck-toothed",
              "bulbous-nosed", "chinless", "double-chinned", 
              "dimpled", "flat-chinned", "flat-nosed",
              "freckle-faced", "furry-eared", "gap-toothed", 
              "jut-jawed", "long-faced", "oval-faced",
              "purse-lipped", "red-cheeked", "round-faced",
              "slope-browed", "square-faced", "square-jawed", 
              "stone-faced", "thin-faced", "tight-jawed" });
    return faces[random(sizeof(faces))];
}

string
face2()
{
    // Set second adjective.
    string *faces2;
    faces2 = ({"impressive", "stout", "barrel-chested",
               "broad-chested", "broad-shouldered",
               "short", "squat", "heavy", "adolescent",
               "ancient", "elderly", "middle-aged", "old",
               "young", "wide-eyed", "yellow-eyed",
               "bandy-legged", "bony-legged", "bow-legged",
               "gangly-legged", "knob-kneed", "knock-kneed",
               "long-legged", "short-legged", "skinny-legged",
               "spindle-legged", "thin-legged", "thick-legged",
               "gangly-armed", "long-armed", "short-armed", 
               "thick-armed", "thin-armed", "black-eyed", 
               "blue-eyed", "brown-eyed", "cross-eyed", 
               "dark-eyed", "grey-eyed", "green-eyed", 
               "moon-eyed", "one-eyed", "poppy-eyed", 
               "red-eyed", "round-eyed", "skew-eyed", 
               "slant-eyed", "slit-eyed", "squinty-eyed" });

    return faces2[random(sizeof(faces2))];
}

void 
choose_gender()
{
   switch (random(2))
   {
      case 0:
        set_gender(1);
        break;
      case 1:
        set_gender(0);
        break;
      case 2:
        set_gender(0);
        break; 
   }
}

void
create_minotaur()
{ 
    set_race_name("minotaur"); 
    set_name(({"minotaur", "citizen", }));
    set_adj(face()); 
    add_adj(face2()); 
    choose_gender();
    set_short(face() + " " +face2()+ " minotaur");
    set_long("This is one of the minotaurs on the Island of Mithas. "+
             "It's extremely tall almost seven feet in height, short "+
             "fur covers his massive body and a thin fuzz hides their "+
             "faces and covers their forearms. It's bullish face is "+
             "brutish and ugly, with a broad snout and wide-set eyes. "+
             "It has long, wide hands with thick fingers ending in short "+
             "claws.\n");
    
    set_stats(({110+random(50),90+random(40),100+random(50),100,85,100}));
    set_alignment(random(50)-25); 

    add_prop(CONT_I_WEIGHT, 70000);
    add_prop(CONT_I_HEIGHT, 2000);
    add_prop(CONT_I_VOLUME, 65000);
    set_random_move(40); 

    // Set up build-in armour and hand damage.
    set_all_hitloc_unarmed(20);
    set_all_attack_unarmed(30,30);    

    // Set skills.
    set_skill(SS_PARRY, 10);
    set_skill(SS_WEP_KNIFE, 60);
    set_skill(SS_DEFENCE, 30);
    set_skill(SS_UNARM_COMBAT, 70);

    MONEY_MAKE(random(10) + 10,"copper")->move(this_object(),1); 
    MONEY_MAKE(random(5) + 5,"silver")->move(this_object(),1); 


   switch (random(2))
   {

      case 0:
      clone_object(MWEP + "side_dagger.c")->move(this_object(),1);
      break;
   }

   switch (random(2))
   {

      case 0:
      clone_object(MARM + "harness2.c")->move(this_object(),1);
      break;
   }

    clone_object(MARM + "belt.c")->move(this_object(),1); 
    command("wield all");
    command("wear all");

}
 
void
init_living()
{
     ::init_living();
}

