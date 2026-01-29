/* /d/Faerun/phlan/rooms/phlanwepshop.c
 *
 * 
 * Nerull 2019
 *
 * Modified by Tharizdun 2021
 */

#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include <defs.h>
#include "/d/Faerun/sys/shop_items.h"

inherit "/d/Faerun/sys/shop_items.c";
inherit BASE_PHLAN_INDOOR;

/*
 * Description  : Constructor, redefine this to configure your room
 */

public void
create_phlan_room()
{
    add_prop(ROOM_I_INSIDE, 1);

    set_short("The Phlan weapon shop");
    
    set_long("Weapon racks line the walls of this shop. Windows"
    +" in the eastern and western walls allow sunlight to supplement."
    +" the lamps suspended from the ceiling. Paintings of valiant"
    +" adventurers demonstrating the proper use of various tools of the"
    +" trade adorn the southern wall behind the counter. There are opened"
    +" crates and packing materials discretely tucked behind the counter."
    +" This combined with the obvious lack of any casting or forging equipment"
    +" indicates the shop is just a store, selling goods procured from"
    +" another source. That being said, a plaque with instructions"
    +" indicates you cannot sell your equipment here. The floor is clean and"
    +" polished without a trace of dust. A fastidious proper man stands"
    +" behind the counter to show you what is currently in stock.\n");

    add_item(({"rack", "racks"}),
    "The racks hold display models of various swords, knives,"
    +" axes, polearms and clubs. The plaque mounted to the counter"
    +" tells how to see what is in stock at the moment.\n");
    
    add_item(({"material", "materials", "packing materials"}),
    "Paddings, wrappers and paper that would keep items protected"
    +" in storage or shipping. Many seem to be oiled or otherwise"
    +" made to keep metal items from rusting or corroding.\n");    
    
    add_item(({"wall", "walls"}),
    "The walls are of knotty pine, both attractive and fragrant. They"
    +" are kept polished to a high shine. There are windows in the"
    +" eastern and western walls and several paintings on the"
    +" south wall.\n");
    
    add_item(({"floor", "floors", "ground"}),
    "The floor is made of mortared flattened stones. It is not polished"
    +" but naturally reflective elements in the rocks reflect the light"
    +" from the lamps and windows in a dazzling display.\n");
    
    add_item(({"stone", "stones"}),
    "The stones are flattened so as to make an even floor. There are"
    +" pieces of granite, puddingstones, limestone and even pieces of"
    +" fossilized corals from the depths of the Moonsea. Bits of mica,"
    +" quartz and galena reflect the light in a sparkling display.\n");
    
    add_item(({"display"}),
    "The light reflecting off the shining minerals in the rocks of the floor"
    +" remind you of stars reflected on a smooth sea.\n");    
    
    add_item(({"window", "windows"}),
    "There are wooden framed windows in the east and west walls. These"
    +" allow both illumination and ventilation.\n");
    
    add_item(({"eastern window"}),
    "The eastern window catches the morning sunlight and the offshore"
    +" breeze. Through the window you can make out the wall of the"
    +" forge but no details.\n");  

    add_item(({"western window"}),
    "The western window allows in the light of the setting sun. Through"
    +" the window you can both see the wall of the armour shop.\n");      
    
    add_item(({"counter"}),
    "The counter has a polished granite surface. The cost of this"
    +" piece makes you wonder about the proprietor's prices. On one end"
    +" of the counter is a plaque with instructions for use of the shop.\n");
    
    add_item(({"ceiling"}),
    "The ceiling is of the same pine as the walls. Two lamps are suspended"
    +" from it, providing light to the shop.\n");    
    
    add_item(({"lamp", "lamps"}),
    "There are two silver lamps suspended from the ceiling. They"
    +" are intricately engraved with a geometric pattern of curious"
    +" design.\n");   

    add_item(({"crate", "crates"}),
    "Shipping crates of various sizes are neatly stacked behind the"
    +" counter. The weapons for sale here must be brought in from"
    +" other sources this way.\n");     
    
    add_item(({"granite"}),
    "Rich in potassium feldspar, this granite has a pink hue with white"
    +" quartz and dark biotite crystals.\n");  

    add_item(({"puddingstone", "puddingstones"}),
    "A coarse-grained clastic conglomerate of rounded rock fragments in"
    +" a chert sediment.\n"); 

    add_item(({"limestone", "limestones"}),
    "A crystalized limestone of the sparite family with interlocking"
    +" calcite crystals.\n");  

    add_item(({"coral"}),
    "A fossiliferous limestone with large coral pieces in microcrystalline"
    +" calcite, weathered somewhat to expose the fossils.\n");   

    add_item(({"mica", "micas"}),
    "A silver-grey mineral with perfect basal cleavage.\n");       

    add_item(({"quartz", "quartzes"}),
    "Colorless hexagonal crystals that terminate in in a pyramid.\n"); 

    add_item(({"galena", "galenas"}),
    "Cube-like crystals of lead sulfide.\n");   

    add_item(({"picture", "pictures"}),
    "There are three. Would you like to examine the first, second or"
    +" third picture?\n");    

    add_item(({"first picture"}),
    "The first picture shows a man wielding a single handed sword easily"
    +" penetrating the leather armour of an orcish warrior.\n");   

    add_item(({"second picture"}),
    "The second picture shows a woman wielding a mace causing"
    +" impressive damage to a hobgoblin in a platemail hauberk.\n");  

    add_item(({"third picture"}),
    "The third picture shows a man wielding a long spear impaling"
    +" a gnoll in scalemail armour.\n");      
    
    add_item(({"man", "fastidious man", "proper man", "fastidious proper man"}),
        "The salesman is definitely not an adventurer or weaponsmith. He"
        +" looks absolutely at home behind this counter or drinking a cup of"
        +" tea on a veranda somewhere.\n");    
    
    add_item(({"plaque"}),
    "Please 'list equipment' to see what is currently in stock.\n");
    
    add_cmd_item( ({ "plaque", "the plaque" }),
                  ({ "read", }), 
    "Please 'list equipment' to see what is in store. Note that this shop"
    +" does not purchase any items.\n");
    

    config_default_trade();
    
    set_standard_equip(PHLAN_SHOP_2);    
    set_money_greed_sell(100);
    set_money_greed_buy(100);
    set_store_room(ROOM_DIR + "storephlanwep");
    
    add_exit(ROOM_DIR + "road16", "north");

    reset_faerun_room();
}

int
deny_sell()
{
    write("The shopkeeper says: I only sell weapons to you. I "
    +"won't buy anything.\n");
    return 1;
}


void
init()
{
    ::init();
    init_shop();
    add_action(deny_sell, "sell");
}


void
reset_faerun_room()
{
    ::reset_faerun_room();
    
}

