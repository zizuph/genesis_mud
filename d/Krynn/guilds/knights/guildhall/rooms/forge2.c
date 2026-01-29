/* The Redhammer Smithy */

#include <money.h>
#include <stdproperties.h>
#include <cmdparse.h>
#include <language.h>
#include <formulas.h>
#include <ss_types.h>
#include <macros.h>
#include "../../guild.h"

inherit IN_BASE;
inherit "/lib/trade";

/* prototypes are here */
object gSmith;


public void
reset_vin_room()
{
    if (!gSmith)
    {
        gSmith = clone_object(VNPC + "bjorn");
        gSmith->move_living("xx", TO);
        gSmith->seq_new("do_thing");
        gSmith->seq_addfirst("do_thing","@@arm_me");

        gSmith->update_commerce();
    }
}

public string
read_sign()
{
    return("          Armour Replicas\n" +
           "         -----------------\n" +
    "\n" +
    "\tHere you can get armour replicas, all you have to do\n" +
    "\tis 'order <armour> [crest]' where crest is one of the\n" +
    "\tfollowing:\n\n"+
    "\t'Kingfisher' - crest with a deep blue kingfisher\n"+
    "\t'Crown' - crest with a bronze crown\n"+
    "\t'Phoenix' - crest with a flaming phoenix\n"+
    "\t'Dolphin' - crest with a deep blue dolphin\n"+
    "\t'Sword' - crest with a silver sword\n"+
    "\t'Bison' - crest with a red-brown bison's horn\n"+
    "\t'Rose' - crest with a platinum rose\n"+
    "\t'Dragon' - crest with a platinum dragon\n"+
    "\t'Triangle' - crest with a silver triangle\n"+
    "\t'Black' - crest with a black rose\n\n" +
    "\t'Solamnian' - To get an uncrested solamnian armour\n\n" +
    "\n\tNOTE: This is not easy, and I will need to use material\n"+
    "\tfrom the original armour, so don't expect to get it back!\n");
}

public void
create_vin_room()
{
    set_short("The lower forge in the Redhammer Smithy");
    set_long("The heat in the Redhammer Smithy is almost unbearable. " +
      "It radiates from the forge and the walls, bathing you in " +
      "a parching warmth. There are various items spread around " +
      "the smithy. Among those that catch your attention are the " +
      "bellows, and a large basin of water as well as " +
      "a few piles of iron, carbon and silver. The forge divides the " +
      "room into two, this one and one further to the north. " +
      "A bit of white powder is spread on the floor, here and there.\n" +
      "A small sign is placed near the forge.\n");

    AI("forge","The forge glows a fiery-red colour. Obviously, it " +
      "has been well-stoked, and has had much coke added.\n");
    AI(({"powder","white powder","bit of white powder"}),"The white " +
      "powder is actually coke, a crushed carbonate rock which " +
      "allows the forge to reach the heat it requires to do its " +
      "purpose.\n");
    AI(({"walls","wall"}),"The walls radiate warmth, reflecting it back " +
      "to the forge.\n");
    ACI(({"walls","wall"}),"touch","The walls are warm to the touch.\n");
    AI("various items","The most interesting are the bellows, the " +
      "anvil, and the basin of water.\n");
    AI("ceiling","Above your head, the ceiling is made of volcanic rock.\n");
    AI(({"volcanic rock","rock"}),"It is most likely granite that makes " +
      "up the foundations and walls of the room.\n");
    AI("bellows","The bellows are used to stoke the fire.\n");
    ACI("bellows","use","You stoke the fire, making it glow a little " +
      "brighter.\n");
    AI(({"water","basin of water","large basin of water"}),"This is " +
      "where glowing-hot materials are cooled. It is half-empty " +
      "at the moment.\n");
    AI("sign", "The sign have letters on it,\n");
    ACI("water","drink","The water from the basin is not potable.\n");
    ACI( ({"sign", "poster"}), "read", read_sign);
    AI(({"iron pile","iron"}), "@@check_iron");
    AI(({"silver pile","silver"}), "@@check_silver");
    AI(({"carbon pile","carbon"}), "@@check_carbon");
    AI(({"piles"}), "@@check_piles");



    AE(VROOM + "forge","north",0);

    reset_room();

    INSIDE;

    config_default_trade();  /* Set up the trading system */
    set_money_give_max(100000); /* Else things go wrong with "sell all" */
    /* Copper Silver Gold Platinum  */
    set_money_give_out(   ({ 10000,   700,  40,    1 })); /* Max_pay   */
    set_money_give_reduce(({     0,     7,   4,    4 })); /* Threshold */

}

string
check_iron()
{
    string str = "";
    int stock;

    stock = gSmith->query_stock("iron bar");

    switch (stock)
    {
        case 0:
          str = "There are only few pieces of cast iron there, nothing useful for " +
          "a smith.";
          break;
        case 1..15:
          str = "There are almost no iron bars in the little heap in " +
          "the corner of the forge.";
          break;
        case 16..35:
          str = "The little heap in the corner of the forge contains some iron bars.";
          break;
        case 36..60:
          str = "This heap seems fairly impressive, it contains a fair amount of " +
          "iron bars";
          break;
        case 61..99:
          str = "The heap of iron bars seems to leave the smith well supplied for " +
          "time being. ";
        case 100:
          str = str + "You don't think he will be needing any more iron!";
          break;
        default:
          str  =  "There are some iron bars in the little heap in " +
          "the corner of the forge.";;
    }

    return str + "\n";
}

string
check_silver()
{
    string str = "";
    int stock;

    stock = gSmith->query_stock("silver bar");

    switch (stock)
    {
        case 0:
          str = "You can only spot some silver dust, nothing really useful for a " +
          "smith.";
          break;
        case 1..15:
          str = "There are almost no silver bars in the little heap in " +
          "the corner of the forge.";
          break;
        case 16..35:
          str = "The little heap in the corner of the forge contains some silver bars.";
          break;
        case 36..60:
          str = "This heap seems fairly impressive, it contains a fair amount of " +
          "silver bars";
          break;
        case 61..99:
          str = "The heap of silver bars seems to leave the smith well supplied for " +
          "time being. ";
        case 100:
          str = str + "You don't think he will be needing any more silver!";
          break;
        default:
          str  =  "There are some silver bars in the little heap in " +
          "the corner of the forge.";;
    }

    return str + "\n";
}

string
check_carbon()
{
    string str = "";
    int stock;

    stock = gSmith->query_stock("carbon bar");

    switch (stock)
    {
        case 0:
          str = "There is only some carbon powder there, nothing useful for " +
          "a smith.";
          break;
        case 1..15:
          str = "There are almost no carbon chunks in the little heap over in " +
          "the corner of the forge.";
          break;
        case 16..35:
          str = "The little heap in the corner of the forge contains some carbon chunks.";
          break;
        case 36..60:
          str = "This heap seems fairly impressive, it contains a fair amount of " +
          "carbon chunks";
          break;
        case 61..99:
          str = "The heap of carbon chunks seems to leave the smith well supplied for " +
          "time being. ";
        case 100:
          str = str + "You don't think he will be needing any more carbon!";
          break;
        default:
          str  =  "There are some carbon chunks in the little heap in " +
          "the corner of the forge.";;
    }

    return str + "\n";
}

string
check_piles()
{
    return check_iron() + check_silver() + check_carbon();
}

void
enter_inv (object ob, object from)
{
    ::enter_inv(ob, from);
    if (interactive(ob))
    {
      start_room_tells();
      gSmith->update_commerce();
    }
}
