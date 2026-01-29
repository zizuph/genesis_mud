inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/attack";
inherit "/std/act/action";

#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>;
#include "/d/Emerald/defs.h";

#define A_HORN 0
#define A_RCLAW 1
#define A_LCLAW 2
#define A_TAIL 3

#define H_HEAD 0
#define H_RWING 1
#define H_LWING 2
#define H_BODY 3
#define H_TAIL 4

void
create_creature()
{
    set_name("gargoyle");
    set_race_name("gargoyle");
    set_short("stony gargoyle");
    set_adj(({"stony"}));
    set_long("Much to your dismay, this vision of horror comes to life. "+
       "The huge gargoyle appears to be made of solid rock "+
       "but moves as lithely as if it were of hobbit flesh. The "+
       "horn on its forehead is aimed straight at your heart.\n");
    add_item("horn", "It looks sharpened!\n");

    set_stats(({ 110, 60, 100, 30, 20, 140 }));
    set_hp(query_max_hp());
    set_skill(SS_DEFENCE, 50);
    set_skill(SS_AWARENESS, 40);

    set_attack_unarmed(A_HORN,  25, 50, W_IMPALE, 20, "horn");
    set_attack_unarmed(A_RCLAW, 30, 30, W_SLASH, 30, "right claw");
    set_attack_unarmed(A_LCLAW, 30, 30, W_SLASH, 30, "left claw");
    set_attack_unarmed(A_TAIL,  25, 35, W_BLUDGEON, 20, "tail");

    set_hitloc_unarmed(H_HEAD, ({ 30, 30, 25, 15}), 20, "head");
    set_hitloc_unarmed(H_RWING, ({ 25, 20, 20, 15}), 25, "right wing");
    set_hitloc_unarmed(H_LWING, ({ 25, 20, 20, 15}), 25, "left wing");
    set_hitloc_unarmed(H_BODY, ({ 30, 30, 30, 20}), 20, "body");
    set_hitloc_unarmed(H_TAIL, ({ 20, 20, 15, 15}), 10, "tail");

    set_aggressive(1);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_act("snarl all");
    add_act("growl");
}
