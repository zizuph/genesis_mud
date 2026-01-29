// file: invis_card
// creator: Ilyian, October 11, 1995
// purpose: Card that makes the player invisible for
//          a time dependant on his wisdom
// note:
// todo:

inherit "/d/Avenir/common/dead/obj/deck/card.c";
#include "/d/Avenir/common/dead/dead.h"

string myadj = "translucent";
string mycolor = "yellow";
object invis_obj;

void create_object()
{
    set_name("card");
    add_name("_avenir_card");
    set_myadj(myadj);
    set_mycolor(mycolor);
    set_adj(({myadj, mycolor}));
    set_short(myadj+" "+mycolor+" card");

    set_long("Is a translucent yellowish color with thin "
            +"silver gilt designs.\nOn "
            +"the other side, there is a very faint "
            +"outline of a humanoid standing straight.\n");

    set_mana_cost(200);

    add_prop(MAGIC_AM_MAGIC,({30, "air"}));

    add_prop(MAGIC_AM_ID_INFO,({
       "The "+short()+" seems to be quite magical.\n",1,
       "Holding it against the forehead activates its magic.\n",10,
       "This card will turn the bearer invisible for "
      +"a short while.\n",30}));

    add_prop(OBJ_S_WIZINFO,"This card is one of the "
        +"cards given out by the Cahor quest in Avenir. It "
        +"is autoloadable, but it can only be use once, and "
        +"then it is destroyed.\n"
        +"Its effect is: The bearer will turn invisible "
        +"for a time dependant on the player's wisdom.\n");

    add_prop(OBJ_I_WEIGHT, 2);
    add_prop(OBJ_I_VOLUME, 10);
    add_prop(OBJ_I_VALUE, 0);
}

query_allowed()
{
    return(::query_allowed());
}

query_fail()
{
    object invis = present("_card_invis_object", TP);

    if(TP->query_prop(MAGIC_I_RES_MAGIC) ||
       TP->query_prop(MAGIC_I_RES_AIR) )
       {
         write("You are somehow immune to the effect "
              +"of the card.\n");
         return 1;
       }
    if(invis)
      {
        write("Something prevents the card from working.\n");
        return 1;
      }
    if(TP->query_prop(OBJ_I_INVIS))
      {
        write("You are already invisible!\n");
        return 1;
      }
    return(::query_fail());
}

success_effect()
{
    write("The "+query_short()+" suddenly feels very "
         +"warm in your hand.\n");
    seteuid(getuid());
    invis_obj = clone_object(DECK + "invis_obj");
    invis_obj->move(TP, 0);
    invis_obj->start_me(TP);
    write("The "+query_short()+" melts away into nothingness.\n");
    remove_object();
    return;
}

