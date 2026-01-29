#include "/d/Ansalon/goodlund/nethosak/city/local.h"
#include <stdproperties.h>
#include "/d/Ansalon/goodlund/nethosak/city/obj/door.h"
#include "/d/Ansalon/common/defs.h"

inherit MITHAS_OUT;

#include "/d/Krynn/common/herbsearch.h"
#define ONE_OF(x)     ((x)[random(sizeof(x))])
#define HERB_MASTER "/d/Krynn/common/herbs/herb_master"
 
string *herbs = HERB_MASTER->query_herbs( ({ "beach", }) );

void 
reset_mithas_room()
{
    set_searched(0);
}
void
create_mithas_room()
{
   object gate;  
   set_short("The beach");
   set_long("@@long_descr"); 
   add_item(({"water", "sea"}), "The water within the Blood Sea has "+
         "a strange and reddish color. Rumor has it that the color "+
         "is the result of the blood of many victims who lost their "+
         "lives during Krynn's most terrible hour, though it "+
         "could be the clay stirred up from the sea bottom by the "+
         "maelstrom.\n");

   add_item(({"sand"}), "The sand is very fine grained. It is even "+
                         "rumoured that this is used by the Wizard "+
                         "of The Tower of High Sorcery to cast "+
                         "arcane spells.\n");

    add_item(({"mithas", "isle", "village", "nethosak"}), "The great Imperial "+
            "city of Nethosak, home of the minotaurs of Ansalon, lies to the "+
            "east. This great city is the home of the Emperor of the Minotaurs "+
            "and the Great Arena, where minotaurs and other lucky 'volunteers' "+
            "fight against each other, sometimes to the death. This is also the "+
            "place of the Temple of the Stars, where the High Priest of the "+
            "minotaurs performs rituals to their god. A strong smell of "+
            "smoke and sweat fills the air.\n");


   add_item(("forest"), "The thick green forest of Mithas lies to the "+
           "southeast. You notice a small trail leading through it, and "+
           "exiting to the plains south of the forest.\n");

   add_item(({"stones","large"}), "The stones have been "+
                          "put along the shore of the beach. These "+
                          "stones look quite large and you can't stop "+
                          "wondering who could have the strength to "+
                          "put them there.\n");

    add_item(({"vegetation","plants"}), "The vegetation "+
                          "is scattered all over the beach "+
                          "however most of the plants grow near the "+
                          "edge of the beach.\n");

    add_item(({"pier","wooden pier","small pier","small wooden pier"}), "It's a very "+
               "old and wooden pier, it looks very unstable.\n");
    
    add_item(({"footprints","prints"}), "You recognize the "+
                         "footprints as the prints of minotaurs. They "+
                         "actually cover the entire trail.\n");

    add_item(({"trail","road"}), "This trail is very worn down, "+
                        "you can see some large footprints in the mud, "+
                        "leading both to the east and west.\n");

   add_exit(MROOM + "pier2","northwest",0);
   add_exit(MROOM + "pier3","southwest",0);
   add_exit("/d/Ansalon/goodlund/nethosak/"+
            "forest/room/forest1","south",0);   

   gate = clone_object(MOBJ + "city_gate1");
   gate->move(this_object());
   
   set_tell_time(100);
   add_tell(({
       "The fresh breeze of the sea caresses your face.\n",
       "The waves from the sea slams violently into the pier.\n",
       "You hear the screams of seagulls nearby.\n", }));

    seteuid(getuid(TO));
    set_up_herbs( ({ ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
       ONE_OF(herbs) }), ({"trail","beach","sand","pier",
        "coastline","sea","water"}), 2);

   reset_mithas_room();
}

string
long_descr()
{ 

   return tod_descr()+ "You are standing on a beach on the isle "+
          "of Mithas. The vegetation of this area is very "+
          "sparse however there seems to be a few plants "+
          "that actually live in this dry habitat. Some "+
          "large stones have been placed here to stop the "+
          "countinous erosion from the sea, but it doesn't "+
          "seem to help much. To the "+
          "northwest and southwest a small wooden pier has "+
          "been built, and to the east a worn down trail "+
          "stretches through the village of Nethosak. The "+
          "trail looks very muddy and dirty it must "+
          "obviously be used a lot. The road to the north "+
          "and south countinues into a forest. " +
           season_descr()+ "\n";
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (interactive(ob))
    {
       start_room_tells();
    }
}

