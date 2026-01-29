#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>
#include "/d/Ansalon/common/brewcraft/brewcraft.h"

#define BREWCRAFTBOARD "/d/Ansalon/estwilde/obj/brewcraft_board"

inherit DWARF_IN;

void
reset_dwarf_room()
{
}

void
create_dwarf_room()
{
    set_short("@@short_descr");
    set_long("@@long_descr");

    add_item(({"list","walls","wall","chart","outlets","parchments"}),
            "The walls of the room are festooned with "+
            "things to read including: brewing, barrels, brewers, royalties and outlets. "+
            "There is also a cork board for messages.\n");

    add_item(({"desk"}),
            "The oak desk is a fine example of dwarven outreach "+
            "to human craftsfolk.  On it sits an alembic and an engine.\n");

    add_item(({"alembic"}),
            "On the oak desk sits an old alembic still "+
            "bearing residue from use in distillation many years ago.\n");

    add_item(({"engine"}),
            "On the oak desk sits a gnomish calculation engine. It is well oiled "+
            "and seems in good order; though it is evidently locked "+
            "from use by casual visitors to this office.\n");

    add_item(({"rug"}),
            "The bearskin rug is expansive on the floor and appears "+
            "to have grizzly highlights in the wavering torchlight "+
            "of the office.\n");
    
    add_item(({"prizes","medallions"}),
            "Rows of medallions, ribbons and certificates adorn the "+
            "surrounds of the message board in the office; "+
            "testament to the quality of Iron Delving "+
            "brewing as adjudged across the Realms.\n");
    
    // Clone the brewcraft board
    room_add_object(BREWCRAFTBOARD, 1, 0);

    add_exit(IRON + "brewery3","south");

    reset_dwarf_room();

}

public void
hook_smelled(string str)
{
    write("The scents of old paper and dust prevail; "+
     "but underneath there are notes of age-ripened dwarf.\n");
}

void
init()
{
    ::init();
    add_action("read", "read");
}

int
read(string str)
{
    if (!str)
    {
        return 0;
    }

    if (!strlen(str))
    {
        write("Read what?\n");
        return 1;
    }

    if (str == "outlets")
    {
        write("" +
      " \n" +
      "   OUTLETS of the IRON DELVING BREWERY\n"+
      "       ORDERED by VOLUME of SALES\n\n" +
      "   Dwarvenfug Tavern             Iron Delving\n" +
      "   Pig 'n' Whistle               Port Balifor\n" +
      "   Sanction Tavern                   Sanction\n" +
      "   Inn of the Last Home                Solace\n" +
      "   Swan and Hedgehog Inn               Neraka\n" +
      "   Hawkstones Taproom                 Flotsam\n" +
      "   'Spartan' Tavern                   Kalaman\n" + 
      "   Scorched Scorpion               Kendermore\n" +
      "   Red Dragon Tavern                   Neraka\n" +
      "   Bronze Dragon Inn                 Vingaard\n\n" +
      "   Boars Head Tavern                  Sparkle\n" +
      "\n");
        return 1;
    }
    if (str == "barrels")
    {
        write("\n" +
      " BARREL MANIFEST of the IRON DELVING BREWERY by TIER NUMBER\n\n");
        write( BREWCRAFT_TIERLIST );
        write("\n\n");
        return 1;
    } 
    if (str == "brewers")
    {
        write("\n" +
      " BREWERS of IRON DELVING\n\n");
        write( BREWCRAFT_BREWERLIST );
        write("\n\n");
        return 1;
    } 
    if (str == "brewing" || str == "export" || str == "championship")
    {
        write("\n" +
         "Brewing takes a Krynnish month (24 hours in the Nether) from\n"+
         "the time of the Brewcrafter testing culture through to filling\n"+
         "of barrels for the great vault. Each month, all new brews are\n"+
         "judged by a panel of experts, and results sent out by mail.\n"+
         "\n\n"+ 
         "The IRON DELVING BREWERY selects the best culture submitted\n"+
         "*each* Krynnish month, to brew its EXPORT brew for sale at\n"+
         "good beer outlets across the Realms. Usually, the export brewer\n"+
         "is owed a royalty from the Brewcrafter for the month in which\n"+
         "it is sold. Sometimes the panel selects the brew of a questing\n"+
         "beginner to encourage a more diverse culture in the vats. For\n"+
         "these brewers, they can take SOLACE enough in being selected.\n\n"+
         "The CHAMPIONSHIP title goes to the best-ever brew still in stock.\n"+
         "The champion brewer is owed a royalty from the Brewcrafter each\n"+
         "Krynnish month for which it remains the best and in stock.\n");
        return 1;
    } 
    if (str == "royalties" || str == "royalty")
    {
        write("\n" +
         "BREWERS owed ROYALTIES from IRON DELVING\n\n");
        write(sprintf("For the Championship Brew:   %15-s\n", capitalize(BREWCRAFT_NAMEG)));
        if ( !BREWCRAFT_QUESTER ) 
            write(sprintf("For the current Export Brew: %15-s\n\n", capitalize(BREWCRAFT_NAME)));
        write("The Brewcrafter gifts royalties in person.\n\n");
        if ( BREWCRAFT_QUESTER ) 
            write("\nThis month's Export Brewer is not owed a royalty "+
                    "-- questing is its own reward!\n");
        return 1;
    } 

    // not openly mentioned
    if (str == "styles")
    {
        write("\n" +
      "BREWING STYLES of the IRON DELVING BREWERY\n\n");
        write( BREWCRAFT_STYLELIST );
        write("\n\n");
        return 1;
    } 

}

string
short_descr()
{
    return "office of the Brewcrafter of the Iron Delving Brewery";
}

string
long_descr()
{
    return "The Brewcrafter's office betrays the love "+
     "of gold and silver in dwarves. "+
     "A board on the wall seems to be a place for brewers "+
     "and brew drinkers to share messages. Medallions for "+
     "prizes won by the brewery hang all about the board. "+
     "There is a " +
     "well-made oak desk bearing an intricate disused alembic, "+
     "of some antiquity, beside a gnomish calculation "+
     "engine. The walls are dark mahogany; the plush bearskin "+
     "rug on the stone floor has a feel of luxury that beats the "+
     "softness of the best of any green sward sought by elves "+
     "in summertime. It is clear that brewers are held in high "+
     "regard among the Hill Dwarves -- no expense was spared in "+
     "making this a comfortable place from which to lead the "+
     "important work of the Iron Delving Brewery. "+
     "The walls are covered in parchments containing "+
     "detailed information in a tight neat hand.\n";
}
