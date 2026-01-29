
/* 
   Lavatory object that stops player from doing anything except looking, 
   reading, writing graffiti and "stop"ping. 

   Coded by Maniac 10/11/95. 

   Checks for CMDPARSE_PARALYZE_ALLOWED verbs, Maniac, 7/8/01 
   Use of CMDPARSE_PARALYZE_CMD_IS_ALLOWED instead, Mercade, 16/02/2008
*/ 

#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include "/d/Calia/sys/lav.h"

#pragma save_binary

inherit "/std/object";


string doing;


void
create_object()
{
    set_name(LAV_OB_NAME);
    set_short("lavatory object");
    set_long("Lavatory object, should be invisible.\n"); 
    set_no_show(); /* Don't show it */
    doing = "using the lavatory"; 
    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_M_NO_GIVE, 1);
    add_prop(OBJ_M_NO_INS, 1);
    remove_prop(OBJ_I_WEIGHT);
    remove_prop(OBJ_I_VOLUME);
}


/* What the player is doing (urinating or defecating) */
void
set_doing(string d)
{
    doing = d;
}


/* Can't do most things when in the pillory. */
void
not_now(object tp)
{
    tp->catch_tell("Not while " + doing + "! " +
                   "You will have to stop first.\n"); 
}


/* Catch player's input when using the lav. */
int
lav_block(string str)
{
    string dummy, v; 
    object p; 

    v = query_verb(); 

    if ((v == "read") || (v == "graffiti") || 
        (v == "look") || (v == "examine") || 
        (v == "exa")) 
        return 0; 

    if (CMDPARSE_PARALYZE_CMD_IS_ALLOWED(v)) 
        return 0; 

    p = environment(this_object()); 

    if (v == "stop") 
    {
        environment(p)->stop_using_lav(p);
        remove_object();
        return 1;
    }

    not_now(p);
    return 1;
}


void
init()
{
    ::init();
    add_action(lav_block, "", 1);
}
