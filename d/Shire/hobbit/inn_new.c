/*
 * Changed supplies cloning process and to include ~Shire/sys/defs.h
 */
#pragma save_binary

inherit "/d/Shire/room";
inherit "/d/Shire/lib/inn.c";
#include "/d/Shire/sys/defs.h"
#include "hobbit.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/money.h"
#include "/d/Shire/hobbitmaker/hobbitmaker.h"

#define NUM           sizeof(MONEY_TYPES)
#define PRICELIST_ID  ({"pricelist","list","prices", "menu"})
#define TOB_DIR   HOBGLD_DIR + "tobacco/" 
#define SUPL_DIR "/d/Shire/hobbit/supplies/"

static object innkeeper;
void add_stuff();
void reset_room();

void
create_shire_room()
{

    configure_shire_inn();
    set_short("The Ploughed Field");
    set_long("You have entered a small inn, known as the Ploughed Field.  "+ 
      "Chairs and tables litter this inn whose purpose is to serve the "+
      "Adventuresome Hobbits their food and drink. "+
      "A pricelist, or menu is posted to the wall.\n");

    add_item(({"chair", "chairs"}), "The chairs are made out of wood.\n");
    add_item("counter", "It's made out of wood. There is a hobbit standing "+
      "behind it.\n");

    add_item(PRICELIST_ID, "@@pricelist_desc");

    add_prop(ROOM_I_INSIDE,1);
    add_exit(HOBGLD_DIR + "hall", "northwest");
    add_exit(HOBGLD_DIR + "libraryroom","southwest");
    reset_room();
}

string
pricelist_desc()
{
    return "\nDrinks:\n"+
    " 1. 'A fresh delicous beer' ............   10 cc\n"+
    " 2. 'A pint of red ale' ................   25 cc\n"+
    " 3. 'A glass of brandywine' ............   40 cc\n"+
    " 4. 'A shot of Gamwich whiskey' ........   90 cc\n"+
    "\nSnacks:\n"+
    " 5. 'A cracker' ........................   10 cc\n"+
    " 6. 'A turkey sandwich' ................   21 cc\n"+
    "\nMeals:\n"+
    " 7. 'A vegetable soup' .................   38 cc\n"+
    " 8. 'A beef stew' ......................   54 cc\n"+
    " 9. 'A large t-bone' ...................  120 cc\n"+
    "10. 'A roast chicken' ..................  350 cc\n"+
    "\nTobacco:\n"+
    "11. 'Longbottom leaf tobacco' ..........  15 cc\n"+
    "12. 'Old Toby tobacco' .................  35 cc\n"+
    "13. 'Southern star tobacco' ............  50 cc\n"+
    "14. 'Tobacco pouch' ....................  75 cc\n\n";
}

void
reset_room() 
{
    if (!innkeeper) innkeeper = clone_object(HOBGLD_DIR + "innkeeper");
    if (!present(innkeeper)) innkeeper->move(this_object());
    set_alarm(0.4,0.0,"add_stuff");
}

init() {
    ::init();
    add_action("do_read", "read", 0);
    init_shire_inn();
}

do_read(str)
{
    if (!str) return 0;
    if (member_array(str, PRICELIST_ID) == -1) return 0;
    write(pricelist_desc());
    return 1;
}

int
do_order(string str)
{
    if (!innkeeper || !present(innkeeper)) {
        notify_fail("There is no one here to buy anything from.\n"+
          "The innkeeper has been killed!\n");
        return 0;
    }
    return ::do_order(str);
}

mixed *
get_order(string str1)
{
    int price;
    object order;

    switch (str1) {
    case "beer": case "cold beer": case "nice cold beer": case "1":
        order = clone_object(SUPL_DIR + "beer");
        price = 10;
        break;
    case "ale": case "pint": case "red ale": case "2":
        order = clone_object(SUPL_DIR + "ale");
        price = 25;
        break;
    case "wine": case "brandywine": case "glass of brandywine": case "3":
        order = clone_object(SUPL_DIR + "bwine");
        price = 40;
        break;
    case "whiskey": case "gamwich whiskey": case "4":
        order = clone_object(SUPL_DIR + "gwhiskey");
        price = 90;
        break;
    case "cracker": case "5":
        order = clone_object(SUPL_DIR + "cracker");
        price = 10;
        break;
    case "sandwich": case "turkey sandwich": case "6":
        order = clone_object(SUPL_DIR + "sandwich");
        price = 21;
        break;
    case "soup": case "vegetable soup": case "7":
        order = clone_object(SUPL_DIR + "soup");
        price = 38;
        break;
    case "stew": case "beef stew": case "8":
        order = clone_object(SUPL_DIR + "bstew");
        price = 54;
        break;
    case "steak": case "t-bone": case "large t-bone": case "9":
        order = clone_object(SUPL_DIR + "steak");
        price = 120;
        break;
    case "medley": case "chicken": case "roast chicken": case "10":
        order = clone_object(SUPL_DIR + "chicken");
        price = 556;
        break;
    case "tobacco": case "longbottom leaf": case "longbottom leaf tobacco":
case "11":
        order = clone_object(TOB_DIR +"tob_longbottom");
        price = 15;
        break;
    case "old toby": case "old toby tobacco": case "12":
        order = clone_object(TOB_DIR +"tob_oldtoby");
        price = 35;
        break;
    case "southern star": case "southern star tobacco": case "13":
        order = clone_object(TOB_DIR +"tob_star");
        price = 50;
        break;
    case "tobacco pouch": case "pouch": case "14":
        order = clone_object(TOB_DIR + "tob_pouch");
        price = 75;
        break;
    }
    return (({order}) + ({price}));
}


void
add_stuff()
{
    object hobbit1, hobbit2, hobbit3;
    if(!present("billyjoe"))
    {
        hobbit1 = clone_object(HOBBITMAKER);
        hobbit1->set_power(140);
        hobbit1->set_type(CITIZEN);
        hobbit1->add_name("billyjoe");
        hobbit1->move(TO);
    }

    if(!present("bobbysue"))
    {
        hobbit2 = clone_object(HOBBITMAKER);
        hobbit2->add_name("bobbysue");
        hobbit2->set_power(85);
        hobbit2->set_type(CITIZEN);
        hobbit2->move(TO);
    }

    if(!present("bobbybilly"))
    {
        hobbit3 = clone_object(HOBBITMAKER);
        hobbit3->add_name("bobbybilly");
        hobbit3->set_type(ELDER);
        hobbit3->set_power(95);
        hobbit3->move(TO);
    }

}
