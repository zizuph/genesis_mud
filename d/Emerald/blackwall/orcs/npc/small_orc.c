/* Small orc, found in the blackwall mountains.
   Code (c) 2000 Damian Horton. BKA Casimir. */

#pragma strict_types
#pragma save_binary 

inherit "/d/Emerald/std/orc.c";
inherit "/d/Emerald/lib/aid_npc"; //he assists other orcs, and will 
                                 //assist other orcs
#include <wa_types.h>
#include <options.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

#define ORC_DIR "/d/Emerald/blackwall/orcs" 


void
create_orc() 
{
    int weapon;
    string adj= ({"mean", "crude", "ugly", "ill-tempered"}) [random(4)];

    config_orc(50);
    set_adj(adj);
    set_short(adj  + " orc");
    set_long("An ugly black skinned humanoid with an evil temperment. "+
	     "He is approximatly the size of a human, though his build "+
	     "is apt to be a little broader and a little more muscular. "+
	     "Orcs are known for their crudeness.\n");
    
    set_act_time(8);
    add_act("emote snarls.");
    add_act("emote has a malevolent glare in his red eyes.");
    add_act("emote makes a crude gesture.");

    set_cact_time(8);

    weapon = random(3);
    
    if (weapon == 0) {add_equipment(ORC_DIR + "/wep/orc_mace");}
    if (weapon == 1) {add_equipment(ORC_DIR + "/wep/orc_spear");}
    if (weapon == 2) {add_equipment(ORC_DIR + "/wep/orc_axe");}
    if ((! weapon == 1) && random(2))
    {
	add_equipment(ORC_DIR + "/arm/small_shield");
    }
    if (random(3) > 1) {add_equipment(ORC_DIR + "/arm/crude_helmet");}
    if (random(5) > 1) {add_equipment(ORC_DIR + "/arm/studded_leather");}
   
    set_give_aid(1); //aids npcs who ask for it
    set_exp_factor(100); 
}

/* Modified so that he asks for aid from fellow npcs (orcs).*/
public void
attacked_by(object ob)
{
    ::attacked_by(ob);
    get_assistance(ob); //asks for assistance from nearby orcs
}
 
/* sets unarmed combat off, giving more weapon attacks */
int
query_option(int opt)
{
  return (opt == OPT_UNARMED_OFF);
}




