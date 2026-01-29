/* sh_lobby.c: The noble's restaurant in Tyr: Serpine, 4-23-95. */

inherit "/std/room";
inherit "/lib/pub";
#include "defs.h"
#include "/d/Cirath/common/teamer.h"

void
reset_room()
{
    bring_room_team(TYR_NPCS+"drabakk.c", 1, 7, ATH_PERSON+"rich_eat.c", 1);
}

void
create_room()
{
    set_short("senators' hall");
    set_long("Little more than a glorified tavern, the Senator's Hall is "+
             "a fine example of misleading names. The senators are in "+
             "truth merely spoiled nobles, the senate merely ratifies the "+
             "decisions of the King, and the hall itself is more a fancy "+
        "restaurant than a meeting place. The workers and customers "+
             "do their best to ignore your presence, instead focusing on "+
             "the strange art covering the walls and the fabulously "+
             "expensive cuisine on the menu.\n");
             
    add_item(({"worker", "workers", "costomer", "costomers"}), "Richly "+
      "dressed, they seem intent on ignoring you.\n");
    add_item(({"wall", "walls", "art", "strange art"}), "Much of the art is "+
             "erotic, abstract, or both. You hear several nobles point out "+
             "facts about the material, but realise that they are mearly "+
             "rattling off meaningless trivia to sound intelligent.\n");
    add_item("menu", "Since only a fool would be willing to break the law "+
             "restricting reading to nobles and templars, the menu is "+
             "written out in flowing letters.\n");

    add_cmd_item("menu", "read", "Its hard to make out the fancy lettering, "+
             "but the following are offered:\n"+
             "  Food                          Drinks\n"+
             "    Mekillot steak     150 cc     Broy            40 cc\n"+
             "    Cha'thrang cutlet  275 cc     Tyrian ale      75 cc\n"+
             "    Ray filet          500 cc     Asticles wine  150 cc\n"+
             "If you wish you may make special orders like 'buy steak with "+
             "platinum', 'test buy wine', 'buy 9 cutlet', etc\n");

    add_drink(({"broy", "smooth broy", "broys"}),"broy", "smooth", 50, 10,
             40, 0, 0, "This dry drink is made from the purest nectar "+
             "found in a kank, which can only be gained by killing it.\n", 0);
    add_drink(({"ale", "tyrian ale", "ales"}), "ale", "tyrian", 100, 20, 75,
             "Tyrian ale", "Tyrian ales", "Warm, heavy, and sickeningly "+
             "sweat: This blue-purple liquid is a Tyr favorite.\n", 0);
    add_drink(({"wine", "asticles wine", "wines"}), "wine", "asticles", 200,
             40, 150, "Asticles wine", "Asticles wines", "This tart wine, "+
             "favored by nobles, is as gold and dry as the desert.\n", 0);

    add_food(({"steak", "mekillot steak", "steaks", "mekillot steaks"}),
             "steak", "mekillot", 25, 150, 0, 0, "Requiring the slaughter "+
             "of a large and important beast of burden, such steak is very "+
             "costly, but the tangy taste is worth the cost.\n", 0); 
    add_food(({"cutlet", "cha'thrang", "cutlets", "cha'thrang cutlets"}),
             "cutlet", "cha'thrang", 50, 275, 0, 0, "Since the lime of the "+
             "turtle-like cha'thrang makes the meat deadly poison unless "+
             "prepared right, it is standard to have slaves taste it first, "+
             "raising the cost significantly.\n", 0);
    add_food(({"filet", "ray filet", "filets", "ray filets"}), "filet", "ray",
             100, 500, 0, 0, "The 30 meter Cloud Ray is a dangerous beast "+
             "known to decend from the sky and eat whole villages. However "+
             "some are captured to grace the plates of wealthy Tyrians. The "+
             "bait used is a trade secret.\n", 0);

    INSIDE

    add_exit(TZ_NOBLE+"rd_ds_01.c", "north", 0, 1);
    reset_room();
}

void
init()
{
    ::init();
    init_pub();
}
