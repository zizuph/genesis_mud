// file: heal_card
// creator: Ilyian, October 11, 1995
// purpose: Card that heals a player 1/2 of his
//          hp, with a mana cost of 1/3 max mana
// note:
// todo:

inherit "/d/Avenir/common/dead/obj/deck/card.c";
#include "/d/Avenir/common/dead/dead.h"

string myadj = "pale";
string mycolor = "blue";

void
create_object()
{
    set_name("card");
    add_name("_avenir_card");
    set_myadj(myadj);
    set_mycolor(mycolor);

    set_adj(({myadj, mycolor}));
    set_short(myadj+" "+mycolor+" card");

    set_long("One one side, this card has swirling designs "
            +"of blue and green.\nOn the other side, there "
            +"is a picture of a kind hearted woman tending "
            +"to the wounds of an injured warrior.\n");

    add_prop(MAGIC_AM_MAGIC,({40, "life"}));

    add_prop(MAGIC_AM_ID_INFO,({
       "The "+short()+" seems to be quite magical.\n",1,
       "Holding it against the forehead activates its magic.\n",10,
       "The card heals many injuries.\n",30}));

    add_prop(OBJ_S_WIZINFO,"This card is one of the "
        +"cards given out by the Cahor quest in Avenir. It "
        +"is autoloadable, but it can only be use once, and "
        +"then it is destroyed.\n"
        +"Its effect is: It either heals one poison (if "
        +"present) or else it heals the character 2/3 "
        +"of his max_hp, with a mana cost of 1/3 max_mana.");

    set_mana_cost(333);
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
       TP->query_prop(MAGIC_I_RES_LIFE) )
       {
         write("You are somehow immune to the effect "
              +"of the card.\n");
         return 1;
       }
     return(::query_fail());
}


success_effect()
{
    object poison = present("poison", TP);
    if(poison)
      {
        write("The card wavers and you feel a rush of "
             +"energy enter your blood stream.\n");
        poison->remove_object();
        write("The card fades into nothingness.\n");
        remove_object();
        return;
      }
    write("The "+query_short()+" glows with a blue flash, and you feel "
         +"your wounds closing up.\n");
    say(QCTNAME(TP)+"'s wounds quickly close up.\n");
    TP->heal_hp(TP->query_max_hp()*2/3);
    write("The "+query_short()+" fades into nothingness.\n");
    remove_object();
    return;
}

