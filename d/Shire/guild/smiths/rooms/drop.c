/*
     The improvement room for the smiths guild
     smiths improve and meditate here

     15 Aug 2006 - Palmer
        Removed unused init()
*/


inherit "/d/Shire/room";

#include "smiths.h"
#include "/d/Shire/common/defs.h"
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

void
create_room() 
{
    FIXEUID;

   set_short("Resting room");
   set_long("This large room is designated for advanced Smiths. " +
       "It is a place where they come to relax and swap adventures " +
       "with others. A large crate for storing equipment sits against " +
       "a wall and is out of the way. A barrel sits next to the door " +
       "for smiths to drop broken equipment. An entrance leads west to " +
       "the library.\n");

   add_item("carpet","It is a handwoven carpet made by humans.\n");

   add_prop(ROOM_I_INSIDE,1);
   add_prop(ROOM_I_NO_ATTACK, 1);
   add_prop(OBJ_M_NO_ATTACK,1);
   add_prop(ROOM_I_NO_MAGIC_ATTACK, 1); 

   add_exit(SMITHSDIR_ROOMS + "improve","north");
   add_exit(SMITHSDIR_ROOMS + "adv_hall","west");
   
   clone_object("/d/Shire/guild/smiths/obj/sm_adv_box")->move(this_object(), 1);
   clone_object("/d/Shire/guild/smiths/obj/sm_rec_barrel")->move(this_object(), 1);

}


public void
pick_up(object ob)
{
    object cleaner;
    FIXEUID;   
    if(!present(ob, this_object()))
        return;

    cleaner = clone_object("/std/monster");
    cleaner->set_name("guild_cleaner");
    cleaner->set_base_stat(SS_STR, 350);
    cleaner->set_base_stat(SS_DEX, 10);
    cleaner->set_base_stat(SS_CON, 150);
    cleaner->set_base_stat(SS_WIS, 10);
    cleaner->set_base_stat(SS_INT, 10);
    cleaner->set_base_stat(SS_DIS, 30);
    cleaner->set_pname("smiths");
    cleaner->set_race_name("smith");
    cleaner->set_adj(({"charming", "neat"}));
    cleaner->set_short("charming neat smith");
    cleaner->add_prop(LIVE_I_NEVERKNOWN, 1);
    cleaner->move(TO, 1);
    tell_room(TO, QCNAME(cleaner)+" arrives.\n");
    cleaner->command("get all");
    cleaner->command("sigh");
    cleaner->command("drop items in box"); 
    cleaner->command("say Allow me to lend you a hand and put " +
        "this in the box for you.");
    cleaner->command("smile");
    tell_room(TO, QCNAME(cleaner)+" leaves.\n");
    cleaner->remove_object();
}


int
armageddon_it()
{
    return ARMAGEDDON->shutdown_active();  
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);


    if (armageddon_it())
        return; 

    if(living(ob)) return;

    set_alarm(3.0, 0.0, &pick_up(ob));
}

