/* shdwsqre: east section of Shadow Square, Serpine 12/24/96. */
 
#pragma strict_types
 
inherit "/std/room";
#include "defs.h"
inherit "/d/Cirath/std/Cirath_magic_room_std";
#include "/d/Cirath/common/mobber.h"


void
reset_room()
{
    bring_room_mob("traders",TYR_NPC+"mrkt_mob.c",1);
}
 
void
create_room()
{
    ::create_room();
    set_short("east section of Shadow Square");
    set_long("You are confronted with the sights and the sounds of Shadow "
            +"Square's eastern quarter first-hand. Rugs and tapestries "
            +"of all sorts hang on every booth, and great rolls of cloth, "
            +"string, rope, and twine are spread out on the sandy ground. "
            +"Traders and customers both mill around, yelling or "
            +"whispering as the need strikes them. Satisfied members of "
            +"both classes head east to the relative calm of Market Road, "
            +"while others move deeper into the square. Southwest lurks "
            +"the Elven Market, while the Bard's Quarter lends an ominous "
            +"air to more northern paths.\n");
 
    add_item(({"customer","customers"}),"All classes buy material here.\n");
    
    add_item(({"rugs","tapestries","tapestry","booth","booths","cloth"}),
             "The cloth is of decent quality and filled with color.\n");
    add_item(({"rolls","roll","string","rope","twine","ground"}),
             "Tough, fragile, thick, thin: Every possible form of twine, "
            +"rope, or string seems to be available.\n");
    add_item(({"market","elven market"}), "Elves offer great variety of "
            +"goods, but their sources and legality are suspect.\n");
    add_item(({"quarter","bard's quarter","northern paths","northern path"}),
             "The bards of Athas are renowned as much for their "
             +"skill at assassination and poison as their entertaining.\n");
 
    OUTSIDE
    ADD_SUN_ITEM
    ADD_ZIG_ITEM
 
    add_exit(TYR_MARKET+"bardqrtr.c","north",0,1);
    add_exit(TYR_MARKET+"rd_mr_03.c","east",0,1);
    add_exit(TYR_MARKET+"shdwsqrs.c","south",0,1);
    add_exit(TYR_MARKET+"elfmkt.c","southwest",0,1);
    add_exit(TYR_MARKET+"shdwsqrw.c","west",0,1);
    add_exit(TYR_MARKET+"shdwsqrn.c","northwest",0,1);
 
    reset_room();   
}
