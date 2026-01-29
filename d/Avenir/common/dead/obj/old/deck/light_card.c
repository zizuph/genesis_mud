// file: light_card
// creator: Ilyian, October 11, 1995
// purpose: Card glows with a light value of 3 for a
//          duration depenadant on the player's wis, and
//          then vanishes. 
// note:
// todo:

inherit "/d/Avenir/common/dead/obj/deck/card.c";
#include "/d/Avenir/common/dead/dead.h"

string myadj = "dazzling";
string mycolor = "white";
int is_used = 0;
int time_to_go = 1;  //Default

void fade_away();

void create_object()
{
    set_name("card");
    add_name("_avenir_card");
    set_myadj(myadj);
    set_mycolor(mycolor);
    set_adj(({myadj, mycolor}));
    set_short(myadj+" "+mycolor+" card");

    set_long("One one side, that card is just painted "
            +"a bright white.\nOn the other side, there "
            +"is a picture of an elf holding aloft "
            +"a bright torch inside a dark cavern.\n");

    set_mana_cost(70);

    add_prop(MAGIC_AM_MAGIC,({20, "fire"}));

    add_prop(MAGIC_AM_ID_INFO,({
       "The "+short()+" seems to be quite magical.\n",1,
       "Holding it against the forehead activates its magic.\n",10,
       "The card bring light to your surroundings.\n",30}));

    add_prop(OBJ_S_WIZINFO,"This card is one of the "
        +"cards given out by the Cahor quest in Avenir. It "
        +"is autoloadable, but it can only be use once, and "
        +"then it is destroyed.\n"
        +"Its effect is: Becomes bright to a light "
        +"value of 3 for a time dependant on the "
        +"players wisdom.\n");

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
       TP->query_prop(MAGIC_I_RES_FIRE)  ||
       ENV(TP)->query_prop(MAGIC_I_RES_LIGHT) ||
       ENV(TP)->query_prop(OBJ_I_RES_LIGHT) )
       {
         write("Nothing seems to happen.\n");
         return 1;
       }
    if(is_used)
       {
         write("The "+query_short()+" is already glowing "
              +"brightly.\n");
         return 1;
       }
    return(::query_fail());
}

success_effect()
{
    time_to_go = TP->query_stat(4);  // Wisdom
    is_used = 1;
    add_prop(OBJ_I_LIGHT, 3);
    set_alarm(itof(time_to_go), 0.0, fade_away);
    write("The "+query_short()+" starts to emit a "
         +"painfully bright glow.\n");
    say("The "+query_short()+" starts to emit a "
         +"painfully bright glow.\n");
    set_short("glowing card");
    set_long("The "+query_short()+" is glowing with a white fire so "
         +"bright it is painful to look at.\n");
    set_myadj("glowing");
    return;
}

fade_away()
{
    remove_alarm(time_to_go);
    time_to_go = 0;
    is_used = 0;
    write("The "+query_short()+" is suddenly consummed in "
         +"its own pale fire.\n");
    say("The glow around "+QTNAME(TP)+" fades away.\n");
    remove_prop(OBJ_I_LIGHT);
    remove_object();
    return;
}

