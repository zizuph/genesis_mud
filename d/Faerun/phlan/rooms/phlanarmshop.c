/* /d/Faerun/phlan/rooms/phlanarmshop.c
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

    set_short("The Phlan armour shop");
    
    set_long("Armour racks and dummies dominate the shop. Windows"
    +" in the eastern and western walls allow sunlight to supplement."
    +" the lamps suspended from the ceiling. A display board near"
    +" the counter displays various types of armour for comparison. The"
    +" workroom is just a corner of the shop itself. Blacksmithing work"
    +" is done off the premesis, but it is obvious a lot of fastening,"
    +" joining and sizing is done on site. The floor is clean and polished"
    +" and there is not a trace of dust or cobweb in any corner. A smiling"
    +" heavy-armed man behind the counter looks anxious to help you. A"
    +" plaque with instructions stands on the counter itself.\n");

    add_item(({"rack", "racks"}),
    "The racks hold pieces of armour for display. They are constructed"
    +" of sturdy oak and look capable of holding very heavy objects"
    +" securely. The plaque on the counter tells how to display what"
    +" is available for sale.\n");
    
    add_item(({"dummy", "dummies"}),
    "The armour dummies consist of various combinations of head, torso,"
    +" arms, legs, hands and feet. They are made of plain dark wood with"
    +" articulated joints allowing them to be posed. They display armours"
    +" in their more native appearance. The plaque on the counter tells"
    +" how to display what is available for sale.\n");    
    
    add_item(({"wall", "walls"}),
    "The walls are of knotty pine, both attractive and fragrant. They"
    +" are kept polished to a high shine. There are windows in the"
    +" eastern and western walls.\n");
    
    add_item(({"floor", "floors", "ground"}),
    "The floor is made of tight-fitting tiles. This would help in"
    +" the case of dropping any small item. There are no cracks for it to"
    +" become lodged or lost in.\n");
    
    add_item(({"tile", "tiles"}),
    "The tiles are tight fitting black slate. They are swept clean and"
    +" polished. The tiles are so tight there are effectively no cracks"
    +" between them.\n");   

    add_item(({"crack", "cracks"}),
    "The tiles fit so tigtly and perfectly together that there are no"
    +" cracks between them.\n");    
    
    add_item(({"window", "windows"}),
    "There are wooden framed windows in the east and west walls. These"
    +" allow both illumination and ventilation.\n");
    
    add_item(({"eastern window"}),
    "The eastern window catches the morning sunlight and the offshore"
    +" breeze. Through the window you can make out the wall of the"
    +" weapon shop but no details.\n");  

    add_item(({"western window"}),
    "The western window allows in the light of the setting sun. Through"
    +" the window you can both see the wall of the pub and hear the sounds"
    +" of happy patrons.\n");      
    
    add_item(({"counter"}),
    "The counter is deep polished mahogany. The layers of varnish make it"
    +" look as if it is plated in glass. One end of the counter holds a"
    +" display board showing various armour types and the other has a"
    +" plaque with instructions for use of the shop.\n");
    
    add_item(({"ceiling"}),
    "The ceiling is of the same pine as the walls. Two lamps are suspended"
    +" from it, providing light to the shop.\n");    
    
    add_item(({"lamp", "lamps"}),
    "There are two elaborate brass lamps suspended from the ceiling. They"
    +" are intricately decorated with engravings of trees, stags, bear"
    +" and other forest scenes. The provide well lit environment.\n");   

    add_item(({"workroom", "corner"}),
    "One corner of the shop is obviously a workroom. There is a toolrack as"
    +" well as boxes of materials for the armourer to size, repair or put"
    +" other finishing touches on pieces of armour.\n");     
    
    add_item(({"toolrack"}),
    "The toolrack holds tongs, hammers, pliers, and hand vices to"
    +" repair rent chain links, replace broken straps and buckles"
    +" or relace fittings.\n");  

    add_item(({"tongs"}),
    "Several pairs of tongs, long and short handled, hang on the toolrack"
    +" to assistt the armourer in holding the pieces he is working on.\n"); 

    add_item(({"hammer", "hammers"}),
    "There are hammers of various sizes hanging on the toolrack. Everything"
    +" from small metal shot-peen to large wooden and leather mallets"
    +" provide the armourer with all he needs to affix a plate or rivet"
    +" a chainmail link.\n");  

    add_item(({"pliers"}),
    "Wire cutting, needle nosed, or blunt channel locks, the armourer"
    +" has an array of any he may need hanging on the toolrack.\n");   

    add_item(({"vise", "vices"}),
    "The armourer has an assortment of hand vices, C-clamps and other"
    +" devices to keep the pieces he is working on immobile while he"
    +" practices his precision craft.\n");       

    add_item(({"box", "boxes", "materials"}),
    "Wooden boxes hold all manner of armour repair materials. There"
    +" are leather strips, buckles, wires and rivets, all organized"
    +" by size and material.\n"); 

    add_item(({"strips", "leather strips"}),
    "Leather strips can be used as lacing, attachment or cinches and there"
    +" are all different lengths and thicknesses in the boxes of the"
    +" workroom.\n"); 

    add_item(({"buckle", "buckles", "clasp", "clasps"}),
    "Buckles are the most often broken piece of hardware on armour."
    +" In the boxes in the workroom are buckles and clasps of brass"
    +" copper, iron, steel and even decorative silver and gold. The"
    +" armourer has everything he needs to custom fit whatever you"
    +" buy.\n");  

    add_item(({"wire", "wires"}),
    "Sometimes you don't need a full row of new rings to repair or size"
    +" a suit of chainmail when stout wire will work. The boxes have many"
    +" different sizes, lengths and materials.\n");   

    add_item(({"rivet", "rivets"}),
    "Sometimes the only way to fix a split chain link in a suit of mail"
    +" is just to rivet the ends together. These rivets are small and you"
    +" marvel at the skill and patience needed to do this work.\n");   

    add_item(({"board", "display board"}),
    "A display board mounted to the counter shows samples of leather"
    +" scale, chain and plate for the discerning buyer to make"
    +" an informed choice.\n"); 

    add_item(({"scale"}),
    "Overlapping metal scales attached to a leather and padded backing"
    +" allow the impact of a blow to be distributed to a larger area,"
    +" lessening the intensity of the blow. The coverage is good, but"
    +" the way the scales are affixed makes it possible for a blade or"
    +" point to slip between them.\n"); 

    add_item(({"chain"}),
    "Interlocking chain links in a 4 to 1 pattern, riveted on the"
    +" overlapping ends provide a superb defense against slashing and"
    +" thrusting weapons. The biggest modifier in effectiveness is material"
    +" used, weave density and ring thickness. Its flexibility means blunt"
    +" and bashing weapons can cause serious bruising and fractures.\n"); 

    add_item(({"leather"}),
    "Leather, formed and hardened in by immersion in water is shaped to"
    +" the wearer. While soft leather is easily slashed or pierced,"
    +" examples hardened this way proved good resistance but are prone"
    +" to durability issues.\n");   

    add_item(({"plate"}),
    "The ultimate in protection, steel plate contoured to the body and covering"
    +" the majority of the body, mounted on a chain and padded backing that"
    +" reinforce vital areas an joints, is rare and expensive. It is beyond"
    +" the means of the armourer here to construct.\n");       
    
    add_item(({"man", "smiling man", "heavy-armed man", "smiling heavy-armed man"}),
        "The armourer is powerfully built from years of physical work. He"
        +" looks as if he could swing a hammer for hours. He has been"
        +" perfecting his craft for years.\n");    
    
    add_item(({"plaque"}),
    "Please 'list equipment' to see what is currently in stock.\n");
    
    add_cmd_item( ({ "plaque", "the plaque" }),
                  ({ "read", }), 
    "Please 'list equipment' to see what is in store. Note that this shop"
    +" does not purchase any items.\n");
    
    /*
    *   This needs to be set up so it is sell only
    */
    

    config_default_trade();
    
    set_standard_equip(PHLAN_SHOP_1);
    set_money_greed_sell(100);
    set_money_greed_buy(100);
    set_store_room(ROOM_DIR + "storephlanarm");
    
    add_exit(ROOM_DIR + "road17", "north");

    reset_faerun_room();
}


int
deny_sell()
{
    write("The shopkeeper says: I only sell armours to you. I "
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
