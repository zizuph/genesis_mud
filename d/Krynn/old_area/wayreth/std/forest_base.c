/*
   Wayreth forest base.

   forest_base.c
   -------------

   Coded ........: 95/05/12
   By ...........: Jeremiah

   Latest update : 96/11/29
   By ...........: Teth


   long_descr()   (description of the room to the uninvited player.) 
   long_i_descr() (description of the room to the invited player.)   

                     - These functions can be defined in the actual room 
                       file. The description there will then override the 
                       default description from this file.



*/


#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <composite.h>
#include "/d/Krynn/wayreth/local.h"
#include CLOCKH

inherit WAYOUTROOM;
inherit HERBSEARCHNEW

int welcome(object who);

string *herbs = HERB_MASTER->query_herbs(({"mixedforest","conifforest",}));

string normal_room;  /* the room where the player goes to if s/he is */
                     /* walking in the forest UNinvited.             */


string special_room; /* the room where the player goes if s/he is */
                     /* walking in the forest invited.            */


void
reset_wayreth_room()
{
   set_searched(random(2));
}


void
create_forest_room() { }


void
create_wayreth_room()
{
   reset_wayreth_room();

   set_short("@@short_descr");
   set_long("@@query_descr");
	
   OUTSIDE;

   add_item(({"tree", "trees"}), "@@tree_descr");
   add_item("canopy", "@@canopy_descr");
   add_item(({"leaf", "leaves"}), "@@leaf_descr");

   seteuid(getuid(TO));
   set_up_herbs( ({ ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
       ONE_OF(herbs), ONE_OF(herbs) }), ({ "soil","ground" }), 6);

   set_tell_time(240);
   add_tell("A scream is heard from deep within the forest.\n");
   add_tell("A whisper of magic floats upon a deadened wind.\n");
   add_tell("The branch of a nearby tree groans, as it twists downwards.\n");
   add_tell("A small creature skitters away, out of view.\n");
   add_tell("An air of mystery and magic surrounds you.\n");
   add_tell("All is silent.\n");
   add_tell("Something springs up from the ground, then flies away into " +
      "the distance!\n");

   create_forest_room();
}


int
welcome(object who)
{
   if(TP->query_guild_name_occ() == "Wizards of High Sorcery")
      return 1;
	
   if(who->query_prop("_live_i_am_invited"))
      return 1;

   return 0;
}


string
short_descr()
{
   if(welcome(TP))
      return "light forest";

   return "gloomy forest";
}


string
extra_descr()
{
   return "";
}


string
query_descr()
{
    string desc, time, str;

    if(welcome(TP))
    {
        desc = TO->long_i_descr();

        if (desc) 
            return desc;

        str = " filtering through the canopy of leaves formed by the "
            + "tree crowns, ";

        switch (GET_TIMEOFDAY)
        {
            case TOD_NIGHT:
                time = "The moon light from the two moons, " + str
                  + "casts a strange but pleasant light in the forest, "
                  + "making long dark strange shadows. ";
            break;

            case TOD_DAWN:
                time = "The rising sun," + str + "casts a strange but "
                  + "pleasant dim greenish light in the forest. ";
            break;

            case TOD_DAY:
                time = "The sun," + str + "casts a strange but  "
                  + "pleasant greenish light in the forest. ";
            break;

            case TOD_TWILIGHT:
                time = "The sinking sun," + str + "casts a strange "
                  + "but pleasant dim greenish light in the forest, "
                  + "making long dancing shadows. ";
            break;
        }

        return "You are walking in a light forest. " + time
          + extra_descr() + "There is an aura of tranquility that "
          + "makes you feel well here.\n";
     }

     desc = TO->long_descr();

     if (desc)
         return desc;  

     switch (GET_TIME_STRING)
     {
         case MIDNIGHT:
         case NIGHT:
             time = "letting almost no moon light into the forest. " +
	            "The dim light makes the shadows seem to reach out " + 
		    "with long arms to touch you. ";
             break;

         case EARLY_MORNING:
             time = "letting almost no light of the rising sun into " +
	            "the forest. ";
             break;

         case MORNING:
         case NOON:
         case AFTERNOON:
             time = "letting almost no light of the sun into the forest. ";
             break;

         case EVENING:
             time = "letting almost no light of the sinking sun into the " +
	            "forest. The dim light starts to form strange shadows. ";
             break;
    }


    return "You are walking around in a dark gloomy forest. The trees " +
           "seems to lean over you, the leaves of their crowns forming " +
           "an opaque canopy above you, " + time + extra_descr() + "This " +
	   "place is dim, and there is an oppressive hostile atmosphere " +
	   "here. You do not feel welcome.\n"; 
}

string
tree_descr()
{
   if(welcome(TP))
      return "The trees are mostly tall hardwood trees, standing " +
             "with plenty space between each, to allow light to " +
             "filter though the leaves.\n";

   return "The trees are tall dark hardwood trees, They seem to be " +
          "moving closer towards you, shutting out the light, as if " +
          "they intended to harm you.\n"; 
}


string
canopy_descr()
{
   if(welcome(TP))
      return "A soft looking, bright canopy formed by the crowns of " +
             "the trees in the forest. The sprigs and leaves interwoven " +
             "forming a light green blanket above you.\n";

   return "A murky looking canopy formed by the twisted crowns of the " +
          "trees in the forest. The twigs and leaves interwoven forming " +
          "a dark blanket above you.\n";
}


string
leaf_descr()
{
   if(welcome(TP))
      return "Bright green leaves, through which the sun filters, " +
             "casting a pleasant bright green light into the forest.\n";

   return "Deformed dark green leaves, blocking out the sunlight, " +
          "leaving the forest dim and uncomforting.\n";
}


void
set_special_room(string room)
{
   special_room = room;
}


void
set_normal_room(string room)
{
   normal_room = room;
}


int
passage()
{
    if (welcome(TP))
    {
        write("You easily move through the underbrush of the forest.\n");
        return 0;
    }

    write("The underbrush prevents your passage in that direction.\n");
    return 1;
}


int
fatigue()
{
    if (welcome(TP))
        return 1;

    return 3;
}


string
connecting_room()
{
   if(welcome(TP))
      return special_room;

   return normal_room;
}

public void
enter_inv(object ob, object from)
{
   ::enter_inv(ob, from);

   if (interactive(ob))
   start_room_tells();
}

