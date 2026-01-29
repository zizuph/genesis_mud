/*
 * /d/Sparkle/area/city/bank/npc/ornithopter.c
 *
 * Gnomish ornithopter.
 * 
 * Created March 2008, by Aeg (Matthew Morin)
 */
#pragma strict_types

#include "../defs.h"
#include <macros.h>         /* General purpose */
#include <stdproperties.h>  /* References */
#include <ss_types.h>       /* Skills */
#include <wa_types.h>       /* Attack+Hitloc */
#include <cmdparse.h>       /* actions */ 
 
inherit "/d/Sparkle/area/city/bank/npc/machine_npc";
 
/* prototypes */
public void     create_machine();

/* 
 * Function name:       create_machine
 * Description  :       creates NPC with machine settings 
 */
public void
create_machine()
{
    
    seteuid(getuid());
    int x,y;
    string *phys, *mech;
    
    phys    = ({"unpainted", "shiny", "poorly-painted",
                "small", "mechanical", "paper-winged"});
    mech    = ({"clanking", "whirring", "buzzing", "zipping", "chugging", 
                "clunking", "humming", "droning" });
                
    x = random(sizeof(phys));
    y = random(sizeof(mech));
    set_short(phys[x] + " " + mech[y] + " ornithopter");
    set_adj(phys[x]);
    set_adj(mech[y]);
    
    
    set_name("ornithopter");
    add_name( ({"machine", "orni"}) );
    set_adj( ({"paper-winged", "gnomish"}) );
    set_long("It is an ornithopter, that is so small and fragile "
        + "that it appears to be utterly useless. It is a "
        + "machine that can fly by imitating the movements of a bird. "
        + "It is outfitted with dual fully mobile wings, a tail for "
        + "balance, and a light claw for gripping and landing. The wings "
        + "resemble a bat's more than bird's wings, because they are "
        + "webbed instead of feathered. The wings are crafted of very "
        + "thin wood and the webbing is a paper-like substance. The "
        + "wooden, hollow frame connects the wings and the tail to "
        + "create the gizmo. The wings appear to move by strings "
        + "of a gummy, stretchy substance and are given motion by a "
        + "central wheel in the frame. The frame conceals the workings "
        + "behind the central wheel, which hides all other moving parts. "
        + "Without inspecting the internals of this machine, it is unable "
        + "to determine if this thing is alive... or not.\n");

    /* Stats!    STR, CON, DEX, INT, WIS, DIS */
    set_stats(({ 10,  10,  100, 10,  10,  10 }));
    set_hp(20000); /* Heal it */
    
    /* skills */
    set_skill(SS_DEFENCE,       75);
    set_skill(SS_AWARENESS,     15);
    
    /* Combat attacks:  ID  HIT     PEN     DMG TYPE    %USE    DESCRIPTION */
    set_attack_unarmed( 0,   5,      5,     W_SLASH,     5,     "right wing");
    set_attack_unarmed( 1,   5,      5,     W_SLASH,     5,     "left wing");
    set_attack_unarmed( 2,  15,     15,     W_BLUDGEON, 40,     "wooden frame");
    set_attack_unarmed( 3,  15,     15,     W_IMPALE,   50,     "gripping claw");

    /* Hit Locations:   ID  AC(IMP  SLA  BLU ),     %HIT    DESCRIPTION  */
    set_hitloc_unarmed( 0,  ({ 10,  10,  10 }),     50,     "wooden frame");
    set_hitloc_unarmed( 1,  ({  1,   1,   1 }),     20,     "right wing");
    set_hitloc_unarmed( 2,  ({  1,   1,   1 }),     20,     "left wing");
    set_hitloc_unarmed( 3,  ({  1,   1,   1 }),     20,     "tail");
    
    add_prop(CONT_I_WEIGHT, 1000);
    
    /* Machine leftovers */
    add_leftover(BANK_OBJ + "dowel_s",    "dowel",    random(1), 0, 1, 0, 0);
    add_leftover(BANK_OBJ + "nail",       "nail",     random(7), 0, 1, 0, 0);
    add_leftover(BANK_OBJ + "paper",      "paper",    random(3), 0, 1, 0, 0);
        
    /* Actions */
    set_act_time(5); /* action every 5 'beats' */
    add_act("emote flaps it's wings evenly, with full, broad sweeps.");
    add_act("emote flies in circles.");
    add_act("emote flies irratically in the air.");
    add_act("emote extends it's gripping claw to land briefly, only to "
        + "soar into the air moments later.");
    add_act("emote emits a high pitched whirring sound.");
    add_act("emote causes a slight breeze with its wings.");
    
    /* Combat Actions */
    set_cact_time(2); /* combat action every 2 'beats' */
    add_cact("emote flaps it's wings frantically, as if it were "
          + "trying to escape.");
    add_cact("emote extends it's gripping claw menacingly.");
    add_cact("emote flies irratically, like an angry butterfly.");
    add_cact("emote seems to circle about, looking for a high place to "
          + "perch.");
       
} /* create machine */

   
public object
make_corpse()
{
    object corpse;
    
    corpse = clone_object("/d/Sparkle/area/city/bank/obj/machine_corpse");
    corpse->set_leftover_list(query_leftover());
    corpse->add_prop(CORPSE_S_RACE, "machine");
    
    return corpse;
}