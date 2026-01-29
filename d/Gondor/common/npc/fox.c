/*
* A fox for the plains of Lebennin
* If you want to clone this fox somewhere else, then
   * set another restrain path using:
* fox->set_restrain_path(<pathname>);
* modified from /d/Gondor/common/npc/wolf.c
   *
* Olorin              Feb 1993
 * Gwyneth 4 November 2000 - Replaced ~elessar/lib/goodkill.h with
 *                           /d/Gondor/common/lib/logkill.c
*/
inherit "/std/creature";
inherit "/std/combat/unarmed";   /* This gets us standard unarmed routines */
inherit "/std/act/domove";
inherit "/std/act/action";
inherit "/std/act/attack";
#include "/d/Gondor/common/lib/logkill.c"
#include <wa_types.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
/*
* Define some attack and hitloc id's (only for our own benefit)
*/
#define A_BITE  0
#define A_LCLAW 1
#define A_RCLAW 2

#define H_HEAD 0
#define H_BODY 1
#define H_LEGS 2

public void
create_creature()
{
   set_name("fox");
   set_race_name("fox");
   set_short("red fox");
   set_pshort("red foxes");
   set_pname("foxes");
   set_adj(({"red", "hungry", "wild" }));
   set_long(BSN("This is a wild fox, not very large, but dangerous "
         + "nevertheless. He looks rather hungry! He is lean and "
	 + "scrawny and has thick, red fur and sharp fangs."));
   
   set_stats(({8+random(5), 10+random(7), 5+random(5), 6, 5, 15}));
   set_alignment(0);
   
   set_skill(SS_DEFENCE, 17);
   set_skill(SS_UNARM_COMBAT,9);
   set_skill(SS_SWIM, 80);
 
   add_leftover("/d/Gondor/common/obj/foxskin", "skin", 1, 0, 1, 1);
    if (!random(5))
        add_leftover("/std/leftover", "heart", 1, 0, 0, 1);
    if (!random(5))
        add_leftover("/std/leftover", "nose", 1, 0, 0, 0);
    if (!random(5))
        add_leftover("/std/leftover", "eye", 2, 0, 0, 0);
    if (!random(5))
        add_leftover("/std/leftover", "kidney", 2, 0, 0, 1);
    if (!random(5))
        add_leftover("/std/leftover", "intestine", 2, 0, 0, 1);
    if (!random(5))
        add_leftover("/std/leftover", "tooth", random(5) + 1, 0, 1, 0);
    if (!random(5))
        add_leftover("/std/leftover", "skull", 1, 0, 1, 1);
    if (!random(5))
        add_leftover("/std/leftover", "thighbone", 2, 0, 1, 1);
    if (!random(5))
        add_leftover("/std/leftover", "kneecap", 2, 0, 0, 1);
    if (!random(5))
        add_leftover("/std/leftover", "rib", 2, 0, 1, 1);
    if (!random(5))
        add_leftover("/std/leftover", "ear", 2, 0, 0, 0);
    if (!random(5))
        add_leftover("/std/leftover", "scalp", 1, 0, 0, 1);

  
   set_attack_unarmed(A_BITE,  8, 15, W_IMPALE, 60, "jaws");
   set_attack_unarmed(A_LCLAW, 12, 9, W_SLASH,  20, "left paw");
   set_attack_unarmed(A_RCLAW, 12, 9, W_SLASH,  20, "right paw");
   
   set_hitloc_unarmed(H_HEAD, ({ 10, 8, 10 }), 20, "head");
   set_hitloc_unarmed(H_BODY, ({ 8, 8, 10 }), 80, "body");
   
   add_prop(CONT_I_WEIGHT,4500+random(2500));
   add_prop(CONT_I_VOLUME,TO->query_prop(CONT_I_WEIGHT)*75/100);
   
   seq_new("do_first");
   seq_addfirst("do_first",({"@@arm_me","stare","emote peers hungrily at you.","growl"}));
}

arm_me()
{
   set_m_out("quickly trots");
   set_m_in("stealthily trots into view");
}

query_combat_file()
{
   return "/std/combat/cplain";
}

query_knight_prestige() {return 50;}
