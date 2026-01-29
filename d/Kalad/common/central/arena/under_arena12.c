/* 
 * /d/Kalad/common/central/arena/under_arena12.c
 * Purpose    : The arenamasters office
 * Located    : /d/Kalad/common/central/arena/
 * Created By : Korat 1995
 * Modified By: 
 */ 

/* Under the arena */
/* made by Korat */

inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
object ob1;

int fight_on;

void
create_room()
{
    ::create_room();
    hear_bell = 1;
    add_prop(ROOM_I_INSIDE,1);
    set_short ("The managers office");
    set_long (
        "This is the office to the manager of the arena. "+
        "In the corner a lighted fireplace burns slowly, "+
        "radiating a welcomed heat into the room and sending "+
        "out a yellow light that mingles with the weaker ones "+
        "emanating from some lit candles. Except from a bed in "+
        "a corner and a weapon-rack on the left stone-wall, the "+
        "room contains only a wooden desk and a red sign.\n");
    
   
   add_item(({"red sign","sign"}),"It is covered with stains and "+
   "blood.\n");
   add_cmd_item(({"red sign","sign"}),"read","\n"+
     "           WELCOME TO THE ARENA OF KABAL        \n"+
     "Here, you may start a fight in the arena. There \n"+
     "are two options. Player vs player, or player vs \n"+
     "npc. If you are going to fight another player,  \n"+
     "both of you must be in this room when you set it\n"+
     "up. If you chose npc, a proper npc will be      \n"+
     "selected for you to fight.                      \n\n"+
     "setup myself with <player>  - For pfights       \n"+
     "setup myself solo           - For npc fight     \n\n"+
     "A record will be kept here in a book of you and \n"+
     "your fights. You will have an official title    \n"+
     "depending on your fights, and also on other     \n"+
     "player's fights.\n\n"+
     "After you setup yourself with a fight, you must \n"+
     "then enter <start fight>. If its player vs player\n"+
     "you both must enter it. If, after viewing your  \n"+
     "opponent, you want to change your mind, you can \n"+
     "then enter <cancle fight>. If, in the arena, you\n"+
     "wish to wimp out, you can enter <mercy>, and the\n"+
     "fight will end with you losing dishonorably.\n"+
     "Note: YOU WILL DIE IF YOU DIE!\n\n"+
     "Current fights:\n"+
     "@@show_current_fight@@\n");

    add_item ("fireplace","Its a normal fireplace with some "+
        "logs in it burning slowly.\n");
    
    add_item ("bed","The bed is made of wood. Nothing special "+
        "about it at all.\n");
    
    add_item ("desk","The large wooden desk is littered with "+
        "sheets of paper, feather pens and a small holder of ink.\n");
    
    add_item (({"sheet","sheets","paper","papers"}),
        "You study the papers carefully. Some of them seems "+
        "to be orders for food, tools and other things, while "+
        "three of them are letters from persons wanting to "+
        "participate in the gladiatoral games. One letter "+
        "attracts your attention though, since you notice "+
        "the seal of the Lord himself!.\n");
    
    add_item (({"candle","candles"}),"The two candles stands "+
        "on the corners of the large desk, casting a yellow "+
        "light on the items and persons around it.\n");
    
    add_item(({"weaponrack","weapon-rack","rack"}),
        "A normal rack mounted onto the wall. Some weapons "+
        "are locked into.\n");
    
    add_item (({"wall","walls"}),"The walls are made "+
        "of rough-cut stone, and are damp to the touch.\n");
    
    add_item ("stone","They are damp to the touch.\n");
    
    add_item ("letter","Its crumbeled up, but you can see a part of "+
        "the Lords seal on it.\n");
    
    add_cmd_item("letter","read","@@read");
    
    clone_object("/d/Kalad/common/central/doors/glad_door2")->move(TO);
    
    set_alarm (10.0,90.0,"flickering_fire");
    set_alarm (0.0,0.0,"reset_room");
}

string
show_current_fight()
{
    return "There is no fight at this time.\n";
}


void
reset_room()
{
    if(!objectp(ob1))
        {
        ob1 = clone_object("/d/Kalad/common/central/npc/karoth");
        ob1 -> arm_me();
        ob1 -> move_living("xxx", TO);
    }
}

flickering_fire()
{
    tell_room(TO,"The flames from the fire flare up and then "+
        "slowly dies down again.\n");
}

int
read(string str)
{
    write ("The letter is badly crumbeled up so you manage "+
        "to read only parts of it: Slave Karoth, manager of "+
        "the gl...ust provi...lio...easure of my peo."+
        "..if you do not do th....ou will have t...entert"+
        "ainment yourse...Do not fai...\n\n"+
        "On the bottom of the letter you see the seal of the "+
        "Lord of Kabal.\n");
    return 1;
} 
