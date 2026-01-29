/*
 * Filename:      militia.c
 * Description:   This file contains a soilder in the army of the free
 *                people ;) His job is to guard the newport area if the
 *                free people have it.
 *
 * Coded Oct 26 1999 by Daniel W. Mathiasen aka Boron
 *
 * Revision history:
 *
 */
#include "../local.h"
#include <ss_types.h>
#include <macros.h>
#include <money.h>

inherit M_FILE

#ifdef OBJ
#undef OBJ
#endif
#define OBJ  SOLAMN_DIR + "splains/obj/"
/* We use the standard weapons and armours here */

string color = "ocean blue";

void
set_color(string new_color)
{
    color = new_color;
}

#include ARM_ME

void
create_krynn_monster()
{
    int i;
    int alignment, j = random(6) + 2; /* We want difference in thier j */
    string str;

    set_name("militia");
    add_name("sailor");
    add_name("human");
    set_race_name("human");
    add_prop(OBJ_I_COLORABLE, 1);

#include LEVEL_ME

    set_short(query_adj(0) + " human militia");
    set_long("This person have strong muscles a long curley hair tied in his neck, "
               + "playing with his weapon like it was a toy, mastering it very well "
               + "it almost seems as if he knows what he is doing, though he might "
               + "be more experienced then actually trained in using his weapons. "
               + str + "\n");



    // He is smarter then he is strong...
    for(i=0; i<3; i++)
        set_base_stat(i, j * 10 + random(40));

    for(i=3; i<6; i++)
        set_base_stat(i, j * 8 + random(30));

    set_skill(SS_DEFENCE,     j * 6 + random(20)); // He might have learned a trick or two
    set_skill(SS_PARRY,       j * 4 + random(20)); // We cheat here, he needs parry too ;)
    set_skill(SS_WEP_SWORD,   j * 7 + random(20));
    set_skill(SS_WEP_KNIFE,   j * 7 + random(20));
    set_skill(SS_WEP_CLUB,    j * 7 + random(20));
    set_skill(SS_WEP_POLEARM, j * 7 + random(20));
    set_skill(SS_WEP_JAVELIN, j * 7 + random(20));
    set_skill(SS_WEP_AXE,     j * 7 + random(20));

    alignment = query_average_stat();
    alignment = alignment*alignment/12;
    set_alignment(alignment);

    set_knight_prestige(-alignment);

    if (IS_CLONE)
      set_alarm(1.0,0.0,"arm_me", j);

}

