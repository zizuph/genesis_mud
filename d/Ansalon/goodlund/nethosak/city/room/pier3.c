#include "/d/Ansalon/goodlund/nethosak/city/local.h"
#include <stdproperties.h>
#include "/d/Ansalon/common/defs.h"
inherit MITHAS_OUT;

#include "/d/Krynn/common/herbsearch.h"
#define ONE_OF(x)     ((x)[random(sizeof(x))])
#define HERB_MASTER "/d/Krynn/common/herbs/herb_master"
 
string *herbs = HERB_MASTER->query_herbs( ({ "beach", }) ); 
object rat;

void 
reset_mithas_room()
{
    if(!objectp(rat))
    {
      rat = clone_object(MNPC + "rat");
      rat -> move(this_object());
   }
}

void
create_mithas_room()
{
   set_short("Old wooden pier");
   set_long("@@long_descr");
   add_item(({"water", "sea"}), "The water within the Blood Sea has "+
         "a strange and reddish color. Rumor has it that the color "+
         "is the result of the blood of many victims who lost their "+
         "lives during Krynn's most terrible hour, though it "+
         "could be the clay stirred up from the sea bottom by the "+
         "maelstrom.\n");

   add_exit(MROOM + "pier1","north",0); 
   add_exit(MROOM + "pier4","northeast",0);
   add_exit(MROOM + "pier5","south",0); 
  
   add_item(({"bay","horned bay","bloodsea","blood sea"}), "The horned bay "+
              "stretches itself towards the north, south and further out "+
              "to the west where it meets the Bloodsea.\n");   

    add_item(({"pier","wooden pier","small pier","small wooden pier"}), "It's a very "+
               "old and wooden pier, it looks very unstable.\n");

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

    add_item(({"grassy plains", "plains"}), "The grassy plains of Mithas "+
            "lies to the southeast, beyond the forest. This large area of "+
            "grass leads to the dreaded volcanic peaks, in the southern "+
            "part of Mithas.\n");

    add_item(({"peaks", "volcanoes", "volcanic peaks", "four peaks",
               "four volcanic peaks"}), "The four volcanic peaks rises high "+
               "above the forest and plains. The tall peaks stands adjacent "+
               "to eachother and some strange dark shapes seems to circle "+
               "the around them.\n");

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

   return tod_descr()+ "This is a small pier on the isle "+
          "of Mithas. The pier is very primitive "+
          "and actually seems like it can collapse "+
          "at any time. Looking to the west you can "+
          "see a small bay, and beyond it the great "+
          "blood sea. To the east lies a small village "+
          "and far to the south you see four volcanic "+
          "peaks, towering above the grassy plains and "+
          "forest. " +season_descr()+ "\n";
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

