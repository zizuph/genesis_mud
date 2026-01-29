
// file: trans_card
// creator: Ilyian, October 11, 1995
// purpose: Card that teleports player to a random
//          area.
// note:
// todo:

inherit "/d/Avenir/common/dead/obj/deck/card.c";
#include "/d/Avenir/common/dead/dead.h"

string *places_to_go = ({"/d/Avenir/common/bazaar/green/green9",
                         "/d/Gondor/pelargir/street/statue",
                         "/d/Gondor/ithilien/nforest/slope",
                         "/d/Genesis/start/human/town/jetty2",
                         "/d/Genesis/start/elf/room/swamp_1",
                         "/d/Terel/common/town/temple/temple",
                         "/d/Terel/common/swamp/sw2",
                         "/d/Krynn/solamn/splains/room/mount5",
                         "/d/Krynn/xak/marsh6",
                         "/d/Shire/evendim/ev6",
                         "/d/Shire/rhudaur/plains/path2",
                         "/d/Kalad/common/caravan/caravan-wayfar",
                         "/d/Kalad/common/wild/pass/w21",
                         "/d/Calia/zima/argos/metro/rooms/lroad9",
                         "/d/Calia/mountain/croad/croad25",
                         "/d/Emerald/telberin/house/house1",
                         "/d/Emerald/inn/closet",
                         "/d/Rhovanion/common/rhun/forest/k5"});                         
string myadj = "thin";
string mycolor = "grey";
string oldmmin, oldmmout;

void create_object()
{
    set_name("card");
    add_name("_avenir_card");
    set_myadj(myadj);
    set_mycolor(mycolor);
    set_adj(({myadj, mycolor}));
    set_short(myadj+" "+mycolor+" card");

    set_long("One one side, this thin card is a dull flat "
            +"grey.\nOn the other side, there is a "
            +"map of many large islands, all far away.\n");

    set_mana_cost(150);

    add_prop(MAGIC_AM_MAGIC,({20, "air"}));

    add_prop(MAGIC_AM_ID_INFO,({
       "The "+short()+" seems to be quite magical.\n",1,
       "Holding it against the forehead activates its magic.\n",10,
       "The card will carry you far away.\n",30}));

    add_prop(OBJ_S_WIZINFO,"This card is one of the "
        +"cards given out by the Cahor quest in Avenir. It "
        +"is autoloadable, but it can only be use once, and "
        +"then it is destroyed.\n"
        +"Its effect is: Transport a player to one of "
        +"a random location. Note that the location "
        +"will sometimes be dangerous.\n");

    add_prop(OBJ_I_WEIGHT, 2);
    add_prop(OBJ_I_VOLUME, 10);
    add_prop(OBJ_I_VALUE, 0);
}
 
query_allowed()
{
    if(TP->query_attack() )
       {
         write("You cannot use the "+short()+" while in "
              +"battle.\n");
         return 0;
       }
    return(::query_allowed());
}

query_fail()
{
    if(TP->query_prop(MAGIC_I_RES_MAGIC) ||
       TP->query_prop(MAGIC_I_RES_AIR)  ||
       ENV(TP)->query_prop(ROOM_M_NO_TELEPORT) )
       {
         write("Something prevents the "+query_short()
              +"from working.\n");
         return 1;
       }
    return(::query_fail());
}

success_effect()
{
    oldmmin = TP->query_mm_in();
    oldmmout = TP->query_mm_out();
    TP->set_mm_out("is enshrouded for a moment in a thick "
                 +"grey mist, and then is suddenly gone.");
    TP->set_mm_in("suddenly appears in a flash of greyish "
                 +"light.");
    write("The "+query_short()+" turns to mist in your "
         +"hand.\nThe mist rises to engulf you.\n");
    TP->move_living("X",places_to_go[random(sizeof(places_to_go))],1);
    TP->set_mm_in(oldmmin);
    TP->set_mm_out(oldmmout);
    remove_object();
    return;
}

