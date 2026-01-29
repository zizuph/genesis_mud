
 /*  
  
    The Smithy for Thalassia

    coder(s):    Jaacar, Sarr

    Based off of the Smithy Code by Sarr

    history:   17.7.03    created                      Jaacar
               5.09.03    added acceptance of bullion
                          for Thalassian Staff quest   Jaacar
 * 2021-06-12 - Cotillion
 * - Added adjectives so the smithy doesn't look differently
 *   each reset.
 */


# pragma strict_types

#include <language.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <const.h>   
#include <macros.h>  
#include <files.h>
#include <std.h>
#include "defs.h"
#include GLYKDEF
inherit "/d/Calia/std/intro";
inherit SEA_CREATURES+"triton";

#define LIVE_I_GOT_BULLION "_live_i_got_bullion"
#define LIVE_I_GOT_BLOCK   "_live_i_got_block"

void
create_triton()
{
    if (!IS_CLONE)
	return;

    ::create_triton();
    add_name(({"smithy","triton","smith","blacksmith"}));
    set_race_name("triton");
    set_adj(({ "green-bearded", "chestnut-haired" }));
    set_gender(G_MALE);
    set_title("the Blacksmith of Thalassia");
    set_long("He is a strikingly beautiful creature with long "+
        "black hair.  He is human in appearance above the waist, "+
        "but has a large fish-like tail instead of legs.  He is "+
        "covered in dark green scales, and has long, sharp claws on "+
        "his webbed fingers.  His friendly smile reveals what look "+
        "like very sharp fish teeth.\n");

    set_all_hitloc_unarmed(50);
    set_stats(({140,80,110,76,88, 100}));
    add_prop(CONT_I_WEIGHT,48000);
    add_prop(CONT_I_HEIGHT,190);
    add_prop(NPC_I_NO_RUN_AWAY,1);
    add_prop(NPC_M_NO_ACCEPT_GIVE, 0);
    set_skill(SS_UNARM_COMBAT, 80);
    set_alignment(500);

    MONEY_MAKE_SC(random(40))->move(this_object());

    set_act_time(15);
    add_act("emote hammers on the anvil.");
    add_act("smile slow");
    add_act("emote bubbles: I can turn bullion into blocks of metal.");
}

void
accept_bullion(object bullion, object tp)
{
    object block;
    string name;

    name = tp->query_real_name();

    command("smile");
    command("emote bubbles: Yes, I can do something with this!");
    bullion->add_prop(OBJ_M_NO_STEAL,1);
    if (tp->query_prop(LIVE_I_GOT_BLOCK))
    {
        command("emote bubbles: I already gave you a block.");
        return;
    }
    command("emote quickly melts down the raw bullion and places it "+
        "into a mold. Once there, he opens the sides of the mold, one "+
        "at a time, allowing the water around you to cool the hot "+
        "metal, solidifying it very quickly.");
    block = clone_object(SEA_OBJECTS+"metal_block");
    block->move(TO);
    command("emote says: Here you go. Perhaps you can find another smithy "+
        "that can make use of that.");
    command("give block to "+name);
    tp->remove_prop(LIVE_I_GOT_BULLION);
    tp->add_prop(LIVE_I_GOT_BLOCK,1);
}

void
drop_stuff(object ob)
{
     if (!objectp(ob))
         return;

     command("emote looks curiously at " + LANG_THESHORT(ob) + "."); 
     command("shrug");
     command("emote says: What would I want this for?");
     command("drop " + OB_NAME(ob));
}

void
do_smile()
{
    command("smile");
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from); 

    if (ob->id("_cylinder_of_silver_bullion_"))  
        set_alarm(1.0, 0.0, &accept_bullion(ob,from));

    else if (ob->id("_block_of_silver_"))
        set_alarm(1.0, 0.0, &do_smile());

    else if (ob->id("coin"))
        set_alarm(1.0, 0.0, &do_smile());

    else 
        set_alarm(1.0, 0.0, &drop_stuff(ob));
}

