/* 
 * /d/Gondor/common/npc/buck.c  
 * an animal for the forests of Ithilien
 *
 * Olorin		feb 1993
 */

inherit "/std/creature";

inherit "/std/act/domove";
inherit "/std/act/action";
inherit "/std/act/attack";
inherit "/std/combat/unarmed";
inherit "/d/Gondor/common/lib/logkill";

#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>

/*
 * Define some attack and hitloc id's (only for our own benefit)
 */
#define A_BITE  0
#define A_CHARGE 1
#define A_FHOOVES 2
#define A_RHOOVES 3

#define H_HEAD 0
#define H_BODY 1
#define H_LEGS 2

void
create_creature()
{
    if (!IS_CLONE) return;
    set_name("buck");
    set_pname("deer");
    add_name("animal");
    add_name("creature");
    add_name("beast");
    add_name("deer");
    set_short("red brown deer");
    set_pshort("red brown deer");
    set_long("This is a male deer. Its fur is reddish brown and shiny.\n");
    set_adj(({"female","brown","red"}));
    set_race_name("deer");
    set_alignment(0);
    set_stats(({20+random(10),20+random(10),15+random(15),5+random(5),5+random(10),5+random(5)}));
    set_hp(5000);
    set_gender(0);
    set_skill(SS_UNARM_COMBAT,30+random(10));
    set_skill(SS_DEFENCE,30+random(10));
    set_skill(SS_PARRY,30+random(10));
    set_skill(SS_SWIM,50+random(20));
    set_skill(SS_CLIMB,50+random(20));
    set_whimpy(random(100));
    set_random_move(5);

    add_leftover("/d/Gondor/common/obj/deerfur", "fur", 1, 0, 0, 1);

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
    if (!random(5))
        add_leftover("/std/leftover", "heart", 1, 0, 0, 1);
    if (!random(5))
        add_leftover("/std/leftover", "eye", 2, 0, 0, 0);
    if (!random(5))
        add_leftover("/std/leftover", "kidney", 2, 0, 0, 1);
    if (!random(5))
        add_leftover("/std/leftover", "intestine", 2, 0, 0, 1);

    seq_new("do_first");
    seq_addfirst("do_first",({"@@arm_me","stare","emote nibbles at the grass.","emote holds its head into the wind and sniffs."}));
}

arm_me() 
{
    set_m_out("stalks");
    set_m_in("stalks into view");
}

/*
 * Here we add attacks and hitlocations:
 *     add_attack(int wchit, int wcpen, int damtype, int prcuse, int id)
 *     add_hitloc(int *ac, int prchit, string desc, int id)
 *
 * *ac == ({ ac-impale, ac-slash, ac-bludgeon })
 */
public void
cr_configure()
{
    add_attack(5+random(5),15+random(5),W_IMPALE,10,A_BITE);
    add_attack(15+random(15),5+random(5),W_BLUDGEON,30,A_CHARGE);
    add_attack(15+random(5),15+random(5),W_SLASH,20,A_FHOOVES);
    add_attack(15+random(10),15+random(5),W_SLASH,40,A_RHOOVES);

    add_hitloc(({15+random(15),10+random(10),5+random(5)}),10,"head",H_HEAD);
    add_hitloc(({5+random(5),5+random(5),10+random(10)}),50,"body",H_BODY);
    add_hitloc(({15+random(15),5+random(5),10+random(10)}),40,"legs",H_LEGS);
}

/*
 * Give description of each attack. We could also redefine the entire
 * hitdescription by redefining 'cr_did_hit'
 */
public string
cr_attack_desc(int aid)
{
    switch(aid)
    {
    case A_BITE:return "bite";
    case A_CHARGE:return "charge";
    case A_FHOOVES:return "front hooves";
    case A_RHOOVES:return "rear hooves";
    }
    return "mind"; /* should never occur */
}

query_combat_file()
{
    return "/std/combat/cplain";
}

