#include "/d/Ansalon/goodlund/nethosak/city/local.h"
#include "/d/Ansalon/common/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>

inherit MITHAS_OUT;

#include "/d/Krynn/common/herbsearch.h"
#define ONE_OF(x)     ((x)[random(sizeof(x))])
#define HERB_MASTER "/d/Krynn/common/herbs/herb_master"

#define HARD_TO_CLIMB 20

string *herbs = HERB_MASTER->query_herbs( ({ "beach", }) );

void 
reset_mithas_room()
{
    set_searched(0);
}

void
create_mithas_room()
{
    set_short("Pier of Nethosak.\nA ladder leads down to the water from here");
    set_long("@@long_descr"); 
    add_item(({"water", "sea"}), "The water within the Blood Sea has "+
      "a strange and reddish color. Rumor has it that the color "+
      "is the result of the blood of many victims who lost their "+
      "lives during Krynn's most terrible hour, though it "+
      "could be the clay stirred up from the sea bottom by the "+
      "maelstrom.\n");

   add_item("ladder","A ladder has been set up on the side of the pier here. It " +
      "leads down into the waters of the Bay for easy access to the smaller " +
      "sailing vessels.\n");

   add_item(({"water", "sea"}), "The water within the Blood Sea has "+
         "a strange and reddish color. Rumor has it that the color "+
         "is the result of the blood of many victims who lost their "+
         "lives during Krynn's most terrible hour, though it "+
         "could be the clay stirred up from the sea bottom by the "+
         "maelstrom.\n");

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


    add_item(({"ship", "huge ship", "deck", "hull", "stormseeker"}), "The "+
            "great ship 'Stormseeker' rises up before you. Its heavy sails "+
            "flutter violently in the wind. On the deck you can see some strong "+
            "minotaurs pulling ropes and shouting at each other. The massive "+
            "hull has been made out of thick wooden planks, that have been "+
            "coated with tar making it very water proof.\n");

    add_exit(MROOM + "pier5","north",0);
    add_exit(MROOM + "stormseeker_deck","south","@@enter_ship",0); 

    add_cmd_item(({"down ladder","ladder","down"}),"climb",
      "@@climb_ladder");

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
climb_ladder()
{
 
 
    if(this_player()->query_skill(SS_CLIMB) < HARD_TO_CLIMB)
    {
        write("You dont think you are skilled enough to try " +
          "and climb down this ladder.\n");
        say(QCTNAME(this_player()) + " attempts to climb the ladder but fails.\n");
        return "";
    }
    write("You skillfully climb down the ladder and into the waters of Horned Bay.\n");
    TP->move_living("down the ladder and into the waters of Horned Bay",
      "/d/Ansalon/goodlund/bloodsea/room/1b",1,0);
 
    return "";
}

string
long_descr()
{ 

    return tod_descr()+ "You are standing on a small wooden "+
    "pier on the isle of Mithas. The pier looks "+
    "rather old, but still very sturdy. A ladder has been set " +
    "up running down the side of the pier, allowing sailors easy " +
    "access to the smaller sailing ships. Far to the west "+
    "you can see the Horned Bay, which "+
    "sheltered this isle from the ravages of "+
    "the Blood Sea. To the south a huge ship "+
    "rises next to the pier. The ship has "+
    "the name 'Stormseeker' written on the hull and "+
    "you can see heavy activity on the deck. "+
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


int
enter_ship()
{
    write("You begin to walk towards the ship... suddenly " +
      "the planks beneath you creak alarmingly.\n" +
      "Fearfully you jump back to the pier!\n");
    return 1;
}

