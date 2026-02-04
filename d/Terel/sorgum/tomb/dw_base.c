/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * Tomb dweller common code
 *
 * This file should be inherited by all tomb dwellers
 *
 * some code based on the LoD guard and the monsters in
 * Mortricia's haunted house.
 *
 * Sorgum June 1994.
 */

inherit "/std/monster";
inherit "/std/act/action";     
inherit "/std/act/seqaction";
inherit "/std/act/domove";     
     
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <money.h>
#include <filter_funs.h>

#include "/d/Terel/common/terel_defs.h"     
#include "tomb.h"

#define ARM_DIR  SORGUMDIR + "armour/"
#define WEP_DIR  SORGUMDIR + "weapon/"

/*
 * Prototypes
 */

void set_spell_prop(object ob);

/*
 * Global variables
 */

string *chats = ({
"You don't belong here!  Get Lost!",
"Killing you would be easy for me.",
"You want to know how much blood juts out of a guy's neck when " +
	     "his throat's been cut?",
"You want to find out what happens to an eyeball when " +
	     "it's punctured?",
"Have you ever tried to pick up your teeth with broken " +
	     "fingers?",
"You would look pretty stupid with my sword sticking out of your ass!",    
"What?  Do you think you're tough?",
"Are you talking to me?",
"Mess with me and I'll break you in half!",
"You better walk on home now.",
"I'll snap your neck like a toothpick!",
"I am the last monster in Genesis that you ever want to mess with",
"What the hell are you looking at?",
"Open your trap again and I'll nail it shut!",
"I'll bash your ugly head in with the butt of my sword.",
"You want some of this?  Come and get it!",
"I eat people like you for breakfast!",
"I have been training with Benton, and I just keep getting tougher.",
"I know you... you love the killin' but you're an empty shell inside.",
"I'll pulp and splatter your head over a wide area!",
});

string *cchats = ({
"Yes!  That was almost a critical hit!  Next time you'll eat crow for sure!",
"You should have never come back!",
"Keep it up and I'LL SLIT YOUR THROAT!!!",
"I know more ways to kill you than you know ways to die!",
"I hope you brought a body bag!  You'll need it.",
"Come on!  My grandmother hits harder than that!",
"I own you now!  You are mine.",
"Had enough?  I'm just getting started.",
"HA!  Check your stats buddy, you are losing strength fast!",

});

int berzerked = 0;

go_berzerk()
{
    command("glare");
    tell_room(environment(TO), "A strange look comes over the face of the " +
	      "tomb deller, he looks completely insane now.\n");
    command("say Now I am pissed!  You are in trouble now.");
    set_whimpy(0);
}
     
create_monster()
{
    int i;
    
    if (!IS_CLONE) return;

    set_name("dweller");
    set_short("tomb dweller");
    set_long(
		"A being that dwells here in the tomb.  Its eaten away and " +
		"bone-revealing form is a leering abhorrent travesty of its " +
		"once human shape.\n"
		 );

    set_adj("decayed");
    set_race_name("dweller");
    set_gender(0);

    add_prop(LIVE_I_NEVERKNOWN, 1);

    set_all_hitloc_unarmed(35);
    set_all_attack_unarmed(20, 20);

    set_whimpy(63);
    set_act_time(30);
    add_act(({"frown"}));
    set_chat_time(1);
    set_cchat_time(1);

    for (i = 0; i < sizeof(chats); i++) {
	add_chat(chats[i]);
	add_cchat(chats[i]);
    }

    for (i = 0; i < sizeof(cchats); i++) {
	add_cchat(cchats[i]);
    }

    set_spell_prop(TO);
}

void
set_spell_prop(object ob)
{
    add_prop(LIVE_O_SPELL_ATTACK, ob);
}

public void
run_away()
{
    if (berzerked)
	::run_away();
    else {
	go_berzerk();
	berzerked = 1;
    }
}

     
     
