/* 
 * /d/Gondor/minas/npc/steward_horse.c  
 *
 * Horse of Steward Denethor II
 *
 * Alto, 12 April 2001
 *
 */

#pragma strict_types

inherit "/d/Gondor/minas/npc/mtirith_monster.c";
inherit "/std/act/domove";
inherit "/std/act/action";
inherit "/std/act/attack";
inherit "/std/combat/unarmed";

#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/bits.h"
#include "/d/Gondor/minas/lib/porter_defs.h"

/* Define some attack and hitloc id's */

#define A_GNASH  0
#define A_HHEAD 1
#define A_FHOOVES 2
#define A_RHOOVES 3

#define H_HEAD 0
#define H_BODY 1
#define H_LEGS 2

object actor, *inv;

public void
create_monster()
{
    int rnd;
    if (!IS_CLONE) return;
    seteuid(getuid());

    set_adj("proud");
    add_adj("chestnut-coloured");
    set_name("horse");
    set_pname("horses");
    add_name("stallion");
     add_name("_porter_q_horse_");
   set_race_name("horse");

    set_long("This is the horse of Steward Denethor II. It is obvious from "
        + "its confident stance and regal poise that this horse is from "
        + "the finest stock in Gondor, excepting the horses of Rohan "
        + "which have no compare. Although this animal appears to be in "
        + "battle-ready condition, long years have passed since its "
        + "master last rode it onto the plains beyond the city.\n");

    rnd = random(60);
    default_config_npc(100+rnd/2);
    set_base_stat(SS_DIS, 150 + rnd);
    set_alignment(100+rnd*10);

    set_gender(0);
    set_skill(SS_UNARM_COMBAT,60+random(10));
    set_skill(SS_DEFENCE,60+random(10));
    set_skill(SS_PARRY,60+random(10));
    set_whimpy(random(100));
    set_random_move(5);

    set_m_out("canters");
    set_m_in("canters confidently in");

    add_prop(LIVE_I_NEVERKNOWN, 1);


    set_act_time(10);
    add_act("emote flicks his tail.");
    add_act("emote tosses his head.");
    add_act("emote nibbles at some oats.");
    add_act("emote lets out an unexpected whinny.");
    add_act("emote lowers his head and snuffles about.");
    add_act("drink water from basin");

    set_cact_time(2);
    add_cact("emote rears up on his hind limbs and flails his forelegs.");
    add_cact("emote bucks and kicks as if possessed of madness.");
    add_cact("emote rolls his eyes and gnashes his teeth.");
    add_cact("emote looks about for a means of escape.");

    refresh_mobile();

}


/*
 * Add attacks and hitlocations:
 *     add_attack(int wchit, int wcpen, int damtype, int prcuse, int id)
 *     add_hitloc(int *ac, int prchit, string desc, int id)
 *
 * *ac == ({ ac-impale, ac-slash, ac-bludgeon })
 */

public void
cr_configure()
{
    add_attack(30+random(5),20+random(5),W_IMPALE,10,A_GNASH);
    add_attack(10+random(15),10+random(5),W_BLUDGEON,30,A_HHEAD);
    add_attack(20+random(5),15+random(5),W_SLASH,20,A_FHOOVES);
    add_attack(35+random(10),25+random(5),W_SLASH,40,A_RHOOVES);

    add_hitloc(({15+random(15),10+random(10),10+random(5)}),10,"head",H_HEAD);
    add_hitloc(({15+random(5),10+random(5),15+random(10)}),50,"body",H_BODY);
    add_hitloc(({15+random(15),10+random(5),15+random(10)}),40,"flank",H_LEGS);
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
    case A_GNASH:return "teeth";
    case A_HHEAD:return "forehead";
    case A_FHOOVES:return "front hoof";
    case A_RHOOVES:return "rear hoof";
    }
    return "mind"; /* should never occur */
}

public string
query_combat_file()
{
    return "/std/combat/cplain";
}


/* Make the horse brushable with the small wooden brush */

void
init_living()
{
   ::init_living();
   add_action("brush_horse", "brush");
}

int
brush_horse(string str)
{

    actor = TP;

    inv = all_inventory(TP);
    if (!sizeof(filter(inv, &->id("_minas_horse_brush_"))))
        NF0("You cannot groom a horse without the proper tools!\n");

    if (!strlen(str))
        NF0("Brush what?\n");

    if (!TP->query_prop(QUESTING_FOR_BRUSH))
        NF0("The Stablemaster has not given you permission to groom "
            + "the horses!\n");

    if (TP->test_bit("gondor", MTIRITH_PORTER_GROUP, MTIRITH_PORTER_BIT))
        NF0("The horse has already been groomed enough.\n");

    switch (str)
    {
    case "horse":
        NF0("What part of the horse do you want to brush? You "
            + "may brush the mane, body or tail.\n");
    case "mane":
        write("You run the small wooden brush gently through the "
            + "mane of the " + TO->short() + ". He seems to enjoy it so much "
            + "that he rests his warm velvet-smooth nose on your "
            + "shoulder and sighs deeply.\n");
        say(QTNAME(actor) + " runs the small wooden brush gently through "
            + "the mane of the " + TO->short() + ". The " + TO->short() 
            + " seems to "
            + "enjoy it so much that he rests his warm velvet-smooth "
            + "nose on " + QTNAME(actor) + "'s shoulder and sighs "
            + "deeply.\n");

        TP->add_prop(GROOMED_STEWARD_MANE, 1);

        return 1;
    case "tail":
        write("You brush the " + TO->short() + "'s tail with the small wooden "
            + "brush until it is free of tangles and snarls.\n");
        say(QTNAME(actor) + " brushes the " + TO->short() + "'s tail with the "
            + "small wooden brush until it is free of tangles and "
            + "snarls.\n");

        TP->add_prop(GROOMED_STEWARD_TAIL, 1);

        return 1;
    case "body":
        write("You brush the " + TO->short() + "'s body with the small "
            + "wooden brush. It trembles beneath your careful attentions.\n");
        say(QTNAME(actor) + " brushes the " + TO->short() + "'s body with "
            + "the small wooden brush. It trembles beneath "
            + actor->query_possessive() + " careful attentions.\n");

        TP->add_prop(GROOMED_STEWARD_BODY, 1);

        return 1;
    default:
        NF0("What do you want to brush?\n");
    }        

}


