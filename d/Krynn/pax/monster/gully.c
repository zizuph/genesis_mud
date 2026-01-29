/*
   gully.c
   -------

   Coded ........: 95/03/26
   By ...........: Jeremiah
 
   Latest update : 95/07/04
   By ...........: Jeremiah


   Gully dwarf used Pax Tharkas  

*/


#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/pax/local.h"
inherit M_FILE

inherit "/std/act/domove"; /* allows gully to move */ 
inherit "/std/act/action"; /* allows gully to act  */

int adj1, adj2, adj3;
int gender;

void
create_krynn_monster()
{
   int i;

   gender = random(2);
   adj1   = random(4);
   adj2   = random(4);

   set_name(({"gully dwarf", "dwarf", "gully"}));
   set_pname("gully dwarves");
   set_pname("dwarves");
   set_pname("gullies");
   set_adj("filthy");
   set_race_name("dwarf");
   set_pshort("gully dwarves");
   set_long("@@long_descr"); 

   for (i = 0; i < 6; i++)
      set_base_stat(i,10 + random(10));

   set_skill(SS_DEFENCE,      10);
   set_skill(SS_PARRY,        10);
   set_skill(SS_WEP_CLUB,     10);
   set_skill(SS_WEP_KNIFE,    10);
   set_skill(SS_WEP_AXE,      20);

   set_all_attack_unarmed(10, 10);
   set_all_hitloc_unarmed(10);
   set_alignment(50);
   set_knight_prestige(-2);
   set_gender(gender);

   default_config_mobile(15);
   set_random_move(25);

   set_default_answer("The gully dwarf says: Hrrmpf! .. why you want to " + 
                      "know that?\n");

   add_prop(NPC_I_NO_RUN_AWAY, 1);
   add_prop(NPC_I_NO_LOOKS, 1);
   add_prop(LIVE_I_NEVERKNOWN, 1);

   set_act_time(3);
   add_act("kill rat");
   add_act("giggle");
   add_act("emote chews on a piece of rat tail.");
   add_act("peer");
   add_act("swing");
   add_act("scratch head");
   add_act("scratch behind"); 

   seteuid(geteuid(TO));
}


void
arm_me()
{
   string *weapon = ({"meatcleaver", "breadknife", "fryingpan"});

   clone_object(PWEAPON + weapon[random(3)])->move(TO);
   command("wield all");
}


string
long_descr()
{
    string ret_str;
    string *looks = ({"dirty", "filthy", "messy", "ugly"});

    string *face  = ({"a large tousled beard. ",
                      "long and tangled hair. "});

    string *dress = ({"a very greasy looking apron.", 
                      "a small pot on the head.",
                      "a pair of far too large boots.",
                      "a dirty sheep skin waistcoat."});

    ret_str = "This is a small " + looks[adj1] + " looking gully dwarf. " +
              C(POSSESSIVE(TO)) + " face is almost hidden by " + 
              face[gender] + C(PRONOUN(TO)) + " is wearing filthy " +
              "ragged clothings and " + dress[adj2] + "\n";

    return ret_str;
}
