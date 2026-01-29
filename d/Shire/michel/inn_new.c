#include "/d/Shire/sys/defs.h"
#include HOBBIT_FILE

inherit SHIRE_ROOM;
inherit INN_LIB;

#define PRICELIST_ID  ({"pricelist","list","prices", "menu"})
#define SUPL_DIR "/d/Shire/michel/supplies/"

static object innkeeper, hob, hob2, hob3, dwarf, hob4;
void add_stuff();

void
create_shire_room()
{

    object infoman;
    set_short("The Pipe and Fork");
    set_long(
   "You have entered the Pipe and Fork. In the tradition of the hobbits it is "+
    "underground in a small hill. The doors are all round as are the few " +
    "windows. The air is filled with smoke coming from the numerous "+
    "pipes being smoked by the hobbits. You almost have trouble finding "+
    "the innkeeper in the dark room. On the wall you can see a pricelist. "+
    "West is a room separated from the main inn by curtains.\n");

    add_item(({"chair", "chairs"}), "The chairs are made out of wood.\n");
    add_item("counter", "It's made out of wood. There is a hobbit standing "+
      "behind it.\n");

    add_item(PRICELIST_ID, "@@pricelist_desc");

    add_prop(ROOM_I_INSIDE,1);
    add_exit(MICH_DIR  + "gamroad4", "northeast");
    add_exit(MICH_DIR + "kitchen","west");

    infoman = clone_object(MICH_DIR + "npc/info_man");
    infoman->move(TO);
    reset_shire_room();

    configure_shire_inn();
}

string
pricelist_desc()
{
    return "\nDrinks:\n\n"+
    " 1. 'A nice cold beer' .............   20 cc\n"+
    " 2. 'A pint of ale' ................   50 cc\n"+
    " 3. 'A glass of red wine' ..........   80 cc\n"+
    " 4. 'A stout whiskey' ...  180 cc\n"+
    "\nSnacks:\n\n"+
    " 5. 'A bag of cookies' .............   21 cc\n"+
    " 6. 'A ham sandwich' ...............   42 cc\n"+
    "\nMeals:\n\n"+
    " 7. 'A veggie delight' .............   65 cc\n"+
    " 8. 'Some wabbit stew' .............  109 cc\n"+
    " 9. 'Steak a la maison' ............  239 cc\n"+
    "10. 'The big meat medley' ..........  556 cc\n"+
    "11. 'Pot of chocolate' .............   60 cc\n\n";
}
void
reset_shire_room()
{
    if (!innkeeper) innkeeper = clone_object(COMMON_NPC + "innkeeper_hob");
    if (!present(innkeeper)) innkeeper->move(this_object());
    set_alarm(2.0,0.0,"add_stuff");
}

void
add_stuff()
{
    if(!hob)
    {
        hob = clone_object(HOBBITMAKER);
        hob->set_type(CITIZEN);
        hob->set_power(150);
        hob->move(TO);
    }
    if(!hob2)
    {
        hob2 = clone_object(HOBBITMAKER);
        hob2->set_type(MAIDEN);
        hob2->set_power(100);
        hob2->move(TO);
    }
    if(!hob3)
    {
        hob3 = clone_object(HOBBITMAKER);
        hob3->set_type(MILITA);
        hob3->set_power(150);
        hob3->move(TO);
    }
    if(!hob4)
    {
        hob4 = clone_object(HOBBITMAKER);
        hob4->set_type(CITIZEN);
        hob4->set_power(60);
        hob4->move(TO);
    }
    if(!dwarf)
    {
        dwarf = clone_object(MICH_DIR + "npc/dark_dwarf");
        dwarf->move(TO);
    }
}

init() {
    ::init();
    add_action("do_read", "read", 0);
    init_shire_inn();
}

int
do_read(string str)
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

mixed
get_order(string str1)
{
    object order;
    int price;

    switch (str1) {
    case "beer": case "cold beer": case "nice cold beer": case "1":
        order = clone_object(SUPL_DIR + "beer");
        price = 20;
        break;
    case "ale": case "pint": case "pint of ale": case "2":
        order = clone_object(SUPL_DIR + "ale");
        price = 50;
        break;
    case "wine": case "red wine": case "glass of wine": case "3":
        order = clone_object(SUPL_DIR + "rwine");
        price = 80;
        break;
    case "whiskey": case "stout whiskey": case "4":
        order = clone_object(SUPL_DIR + "whiskey");
        price = 180;
        break;
    case "cookies": case "bag of cookies": case "bag": case "5":
        order = clone_object(SUPL_DIR + "cookies");
        price = 21;
        break;
    case "sandwich": case "ham sandwich": case "6":
        order = clone_object(SUPL_DIR + "ham");
        price = 42;
        break;
    case "delight": case "veggie delight": case "7":
        order = clone_object(SUPL_DIR + "vd");
        price = 65;
        break;
    case "stew": case "wabbit stew": case "rabbit stew": case "8":
        order = clone_object(SUPL_DIR + "stew");
        price = 109;
        break;
    case "steak": case "steak a la maison": case "9":
        order = clone_object(SUPL_DIR + "steak");
        price = 239;
        break;
    case "medley": case "meat medley": case "big meat medley": case "10":
        order = clone_object(SUPL_DIR + "medley");
        price = 556;
        break;

    case "chocolate": case "pot": case "pot of chocolate": case "11":
        order = clone_object("/d/Shire/common/obj/chocolate");
        price = 60;
        break;
    }
    return ({order}) + ({price});
}
