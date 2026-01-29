/* An creature owl. */

inherit "/std/creature";
inherit "/std/combat/unarmed";   /* This gets us standard unarmed routines */

inherit "/std/act/domove";
inherit "/std/act/chat";
inherit "/std/act/action";

#include "/sys/macros.h"
#include <wa_types.h>
#include <ss_types.h>

/*
 * Define some attack and hitloc id's (only for our own benefit)
 */
#define A_BITE  0
#define A_LCLAW 1
#define A_RCLAW 2

#define H_HEAD 0
#define H_BODY 1

#define OBJ "/d/Gondor/common/obj/feather"

create_creature()
{
 if (!IS_CLONE) 
        return;

    set_name(({"owl","Owl","shorteared owl","Shorteared owl"})); 
    set_race_name("owl");
    set_short("shorteared owl");
    set_adj("tiny");
    set_long("This is one of the famous shorteared owlings. The owls have\n"
           + "their own language, that they were taught by the Elves.\n");

    /* str, con, dex, int, wis, dis
    */
    set_stats(({ 7, 8, 20, 15, 15, 5 }));

    set_hp(350);

    set_skill(SS_DEFENCE, 30);
    set_skill(SS_ACROBAT, 65);
    set_skill(SS_PARRY, 53);

    set_attack_unarmed(A_BITE,  8, 15, W_IMPALE, 40, "bill");
    set_attack_unarmed(A_LCLAW, 6, 10, W_SLASH,  30, "left claw");
    set_attack_unarmed(A_RCLAW, 6, 10, W_SLASH,  30, "right claw");
   
    set_hitloc_unarmed(H_HEAD, ({ 2, 2, 2, 2  }), 20, "head");
    set_hitloc_unarmed(H_BODY, ({ 8, 8, 8, 8 }), 80, "body");

    set_random_move(5);

    add_leftover(OBJ, "feather", 2, 0, 1, 0);

    if (!random(5))
        add_leftover("/std/leftover", "skull", 1, 0, 1, 1);
    if (!random(5))
        add_leftover("/std/leftover", "thighbone", 2, 0, 1, 1);
    if (!random(5))
        add_leftover("/std/leftover", "rib", 2, 0, 1, 1);
    if (!random(5))
        add_leftover("/std/leftover", "heart", 1, 0, 0, 1);
    if (!random(5))
        add_leftover("/std/leftover", "eye", 2, 0, 0, 0);
    if (!random(5))
        add_leftover("/std/leftover", "kidney", 2, 0, 0, 1);
    if (!random(5))
        add_leftover("/std/leftover", "intestine", 2, 0, 0, 1);

    /* He wants to talk */
    set_chat_time(7);
    add_chat("Nhhsadt qwolkam!");
    add_chat("Opowej hjksa lka?");
    add_chat("Tueyer usagsy.");
    add_chat("Sjditeg!!!");

    seq_new("do_things");
    seq_addfirst("do_things", "say Vretigrl!");
}
