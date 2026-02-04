/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * evil_thang.c
 *
 * The evil dragon of Ribos.
 *
 * Vader
 * recoded by Sorgum 950707
 *
 * Lilith Oct 2021: White hits too powerful now, changed the hit and pen.
 *          Modified skills-- dargon was "groundrolling away" which seemed
 *          too odd.
 */

#include "/d/Terel/include/Terel.h"
#include "/d/Terel/include/quest_bits.h"
inherit STDMONSTER;

#include <files.h>
#include <ss_types.h>
#include <wa_types.h>
                                      

#define H_HEAD 0
#define H_BODY 1

#define WEAKENED_BY    "_thariderius_weakened_by"

/*
 * Function name: create_monster
 * Description:   Create the monster. (standard)
 */
public void
create_monster()
{
    ::create_monster();
    set_name("evil dragon");
    set_living_name("thariderius");
    add_name(({"Evil", "evil", "dragon", "evil_thang"}));
    set_adj("huge");
    set_race_name("dragon");
    set_short("huge evil dragon");
    set_long("This HUGE dragon is the epitome of all evil.  His " +
	     "claws are razor sharp, as are his teeth.  His scaly " +
	     "skin is so tough that no ordinary sword will " +
	     "penetrate it very well, making it quite difficult " +
	     "to kill.  His breath is so hot that your " +  
	     "eyebrows singe.  You'd better get the heck out of here.\n");
    
    set_stats(({500, 500, 500, 500, 500, 500}));
    
    set_skill(SS_DEFENCE, 100);
	set_skill(SS_UNARM_COMBAT, 40);
	set_skill(SS_ACROBAT, 10); // don't want him "Groundrolling away", etc
    set_alignment(-800);
    set_aggressive(0);
    set_gender(2); 

    SET_MAX_HP;
	
    // reduced hit and pen since white hits do more damage. Lilith
    set_all_attack_unarmed(30, 30);   
    set_hitloc_unarmed(H_HEAD, ({ 15, 25, 20, 20 }), 20, "head");
    set_hitloc_unarmed(H_BODY, ({ 10, 15, 30, 20 }), 80, "body");
    set_act_time(5);
    
    add_act("growl");
/*    set_random_move(10); */
}

string
reward_msg(object k)
{
    return "With a scream of pain and horror, you solidly massacre " +
	"the evil dragon.  Cheers can be heard from across the " +
	"land.  A group from the castle, led by the King, " +
	"arrives.  They have made this day " + k->query_name() +
	" appreciation from now till forever.  The streets erupt " +
	"in celebration.  You are now a hero, and a more " +
	"experienced "+ k->query_race_name() + ".\n";
}

string
solved_before_msg()
{
    return "With one mighty blow, you solidly massacre the evil " +
	"dragon.  The people are mildly ammused, this not being " +
	"the first time.  They kinda wish you'd take that monster " +
	"and play games somewhere else.\n";
}
    
void
do_die(object killer)
{
    // Check who has weakened the dragon to see if they get a reward
    string * weakened_list = query_prop(WEAKENED_BY);
    if (!pointerp(weakened_list))
    {
        weakened_list = ({ });
    }
            
    if(IN_ARRAY(killer->query_real_name(), weakened_list))
    {
        if (!killer->test_bit("Terel", QUEST_RIB_GROUP, QUEST_RIB_BIT)) 
        {
            killer->set_bit(QUEST_RIB_GROUP, QUEST_RIB_BIT);
            killer->add_exp(QUEST_RIB_EXP, 0);
            FIX_EUID;
            write_file(QUEST_LOG, killer->query_name() +
            " solved the Evil in Ribos quest (" +
            ctime(time()) + ")\n");
    
            killer->catch_msg(reward_msg(killer));
            remove_object();
        }
        else
        {
            killer->catch_msg(solved_before_msg());
            remove_object();
        }
    }
    else
    {
        ::do_die(killer);
    }
}

weaken()
{
    write("Your green striped amulet starts to glow bright green.\n");
    say(QCTNAME(TP) + "'s amulet starts to glow bright " +
	"green.\n");
    write("A beam of supernatural energy erupts from your amulet, striking " +
	  "the evil\ncreature and immersing its entire body in a pale " +
	  "green glow.\n");
    say("A beam of supernatural energy erupts from " +
	QCTNAME(TP) + "'s amulet, striking the\nevil creature and " +
	"immersing its entire body in a pale green glow.\n");
    
    write("The evil creature cries out in great pain.  It looks " +
	  "significantly weakened.\n");

    say("The evil creature cries out in great pain.  It looks significantly " +
	"weakened.\n");
    set_skill(SS_DEFENCE, 25);
    set_stats(({75, 75, 75, 75, 75, 75}));
	refresh_living(); // resets hitpoints to lower level.
    
    // Add a prop to this NPC to indicate who has weakened it.
    string * weakened_list = query_prop(WEAKENED_BY);
    if (!pointerp(weakened_list))
    {
        weakened_list = ({ });
    }    
    weakened_list += ({ TP->query_real_name() });
    add_prop(WEAKENED_BY, weakened_list);
    
    return;
}

// Added Oct 2021 by Lilith:
// Since this is a monster and not a creature, the slots are different.
// Dragon has been hitting with this "mind" andd this should fix it.
public string cr_attack_desc(int id)
{
    if (id == W_LEFT)
    {
        return "massive jaws";
    }
    if (id == W_RIGHT)
    {
        return "huge paw";
    }
    if (id == W_FOOTL)
    {
        return "massive jaws";
    }
    if (id == W_FOOTR)
    {
        return "huge paw";
    }
	
    return ::cr_attack_desc(id);
}