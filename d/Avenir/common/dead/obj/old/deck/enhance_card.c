// file: enhance_card
// creator: Ilyian, October 11, 1995
// purpose: Card that raises the strength, dex, and con
//          of a player by 1/5th for a short time
// note:
// todo:

inherit "/d/Avenir/common/dead/obj/deck/card.c";
#include "/d/Avenir/common/dead/dead.h"

string myadj = "swirling";
string mycolor = "green";
object enhance_obj;

void create_object()
{
    set_name("card");
    add_name("_avenir_card");
    set_myadj(myadj);
    set_mycolor(mycolor);
    set_adj(({myadj, mycolor}));
    set_short(myadj+" "+mycolor+" card");

    set_long("One one side, the card is covered "
            +"with strange swirling shapes.\nOn "
            +"the other side, there is a picture "
            +"of a large warrior with enormous "
            +"muscles slaying a green dragon.\n");

    set_mana_cost(200);

    add_prop(MAGIC_AM_MAGIC,({40, "earth"}));

    add_prop(MAGIC_AM_ID_INFO,({
       "The "+short()+" seems to be quite magical.\n",1,
       "Holding it against the forehead activates its magic.\n",10,
       "The card will make you great in power and "
      +"agility for a short time.\n",30}));

    add_prop(OBJ_S_WIZINFO,"This card is one of the "
        +"cards given out by the Cahor quest in Avenir. It "
        +"is autoloadable, but it can only be use once, and "
        +"then it is destroyed.\n"
        +"Its effect is: The stats of str con and dex are "
        +"all raised by 1/5th for a time dependant on "
        +"the wisdom of the player.\n");

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
    object enhance = present("_enhance_object", TP);

    if(TP->query_prop(MAGIC_I_RES_MAGIC) ||
       TP->query_prop(MAGIC_I_RES_EARTH) )
       {
         write("You are somehow immune to the effect "
              +"of the card.\n");
         return 1;
       }
    if(enhance)
      {
        write("You are already enhanced physicaly!\n");
        return 1;
      }

    return(::query_fail());
}

success_effect()
{
    write("The "+query_short()+" glows briefly with "
         +"a greyish light.\n");
    say("The "+query_short()+" glows briefly with "
         +"a greyish light.\n");
    seteuid(getuid());
    enhance_obj = clone_object(DECK + "enhance_obj");
    enhance_obj->move(TP, 0);
    enhance_obj->start_me(TP);
    write("The "+query_short()+" vanishes within a "
         +"pale gloaming.\n");
    remove_object();
    return;
}

