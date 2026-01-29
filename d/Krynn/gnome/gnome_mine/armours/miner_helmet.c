/* 	
    Miner Helmet

    Made by: Maelstrom, 2016/05/18

    TODO:
    put oil into lamp
    turn off when oil runs out

*/

inherit "/std/armour"; 
#include <stdproperties.h> 
#include <ss_types.h> 
#include <wa_types.h> 

#include <macros.h>
 
//#include "/w/maelstrom/gnome_mine/common.c";

#define ACMIN   15                  /* min value armour class */ 
#define ACDIFF  5                   /* diff between max an min */ 

int helmetLight = 0;
 
create_armour()
{ 
 
    set_name(({"helmet","miner_helmet"})); 
 
    set_adj("miner");
    set_adj("steel"); 
 
    set_short("miner helmet"); 
    set_pshort("miner helmets"); 
 
    set_long("It's a miner helmet. You notice a " 
              + "small lamp on top of it. You may <hlight> to turn it on or off\n"); 
 
    add_prop(OBJ_I_WEIGHT, 2000); 
    add_prop(OBJ_I_VOLUME, 256);
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_M_NO_SELL, 1);
 
    set_default_armour( 
        ACMIN + random(ACDIFF),                 /* armour class */ 
        A_HEAD,                                 /* armour type */ 
        ({0,0,0}),                              /* modifier list */ 
        0);                                     /* special wear remove func */ 
 
}

int
do_light()
{
    object tp = this_player();

    if(!helmetLight)
    {
        add_prop(OBJ_I_LIGHT, 2);
        tp->catch_msg("You light the lamp on the helmet.\n");
        tell_room(environment(tp), QCTNAME(tp) + " lights " +
            "the lamp on the helmet.\n", tp);
    }
    else
    {
        add_prop(OBJ_I_LIGHT, 0);
        tp->catch_msg("You extinguish the lamp on the helmet.\n");
        tell_room(environment(tp), QCTNAME(tp) + " extinguishes " +
            "the lamp on the helmet.\n", tp);
    }
    helmetLight = !helmetLight;
    return 1;
}

void
init()
{
    ::init();
    add_action(do_light, "hlight");
}
